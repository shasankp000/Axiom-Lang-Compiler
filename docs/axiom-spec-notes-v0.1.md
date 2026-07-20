---
tags:
  - lang-spec
---
---
# Axiom Language -- Design Notes & Open Decisions (v0.1 addendum)

> Companion notes to the main `v0.1` spec. Captures decisions made during
> keyword/type discussion, plus explicitly flagged open questions so they
> aren't lost before implementation catches up.

---

## 1. Keywords (control flow / declarations) -- reconciled, complete list

```
if, let, for, while, do, loop, fn, ret, brk, cont, const, true, false
```

13 keywords, verified against implementation (`enum KEYWORD` in `keywords.h`).

- `endif` was considered and **rejected** -- braces already close blocks
  unambiguously (per Section 3: "Blocks use braces"). Adding `endif` would
  require two closing markers to always agree, which contradicts the
  "avoid unnecessary magic" / "keep syntax explicit" goals (Section 0).
  
- `for`, `while`, `do`, `loop` are **four distinct keywords**, not synonyms.
  Each represents its own looping construct with its own grammar, still TBD:
  - `for` -- counted iteration
    
  - `while` -- conditional pre-check iteration
    
  - `do` -- presumably `do { ... } while (...)`, post-check iteration
    
  - `loop` -- infinite / manual-break iteration (pairs with `brk`)
    
- `true` / `false` both fit the `<=5` character keyword cap (`true` = 4,
  `false` = 5) -- no exception needed. *(Left here as a note in case the
  cap is ever tightened below 5.)*

## 2. Type keywords -- reconciled, complete list

```
int, float, dloat, sint, lint, char, bool, str
```

8 type keywords, verified against implementation (`enum KEYWORD` in
`keywords.h`, disambiguated at runtime via `KEYWORD_TYPE == DATA_TYPE`).

- `dloat` = double, `sint` = short int, `lint` = long int. Naming
  convention: prefix letter + shortened base word (`d`+`loat`, `s`/`l`+`int`).
  Future type names should probably follow the same scheme for consistency.
  
- `bool` is a real type keyword (4 chars, fits the cap) -- see Section 5.
  
- `str` is a composite type, not primitive -- see Section 3.
  
- `byte` -- **deferred**, not in v0.1. Axiom isn't tackling advanced/raw
  byte-manipulation topics yet. Cheap to add later (purely additive);
  costly to remove once code depends on it -- hence deferring rather than
  guessing now.
  
- No signed/unsigned distinction yet. `sint` and `lint` are **signed for
  now**. Unsigned variants are an open future item, not yet scoped.

## 2a. `NONE` -- null/absence keyword

- `NONE` (4 chars, fits the cap) is Axiom's null/absence keyword,
  conceptually mirroring C's `NULL`.
  
- Open semantic question, not yet resolved: C's `NULL` is specifically a
  *pointer* value. Does `NONE` in Axiom apply to any type generally, or
  specifically to reference/pointer-like types once those exist? Needs a
  decision once Axiom's type system (especially anything pointer-like)
  is designed further.
  
- **Not to be confused with `NULL_KEYWORD`** -- an unrelated internal lexer
  sentinel, see Section 6a. `NONE` is a real, user-facing Axiom keyword;
  `NULL_KEYWORD` is never something an Axiom programmer types.

## 2b. Full reconciled keyword count

21 real keywords total (13 control/declaration + 8 type) + `NONE` = 22,
plus the internal-only `NULL_KEYWORD` sentinel (23rd enum value, not a
real keyword -- see Section 6a).

## 3. `str` type -- design decisions

- `str` is a **composite type**, built from `char`, not a true primitive.
  This is a deliberate choice consistent with Axiom's philosophy (Section 1:
  manual memory management, expose systems concepts rather than hide them).
  
- Declaration requires an explicit capacity, e.g.:
  
  ```
  str[10] name = "Hello!";
  ```
  
- **Null-termination** (Pascal-style, store string along with a length field at the end) is the chosen approach for
  determining actual string length vs declared capacity -- decided over C-style scanning for a delimiter `\0` to determine where the string ends, mainly because of `O(1)` lookup time in Pascal-style vs `O(N)` lookup time in C-style string.


- Unused capacity (e.g. 3 wasted bytes in `str[10]` holding `"Hello!"`) is
  **allowed to compile** -- the programmer owns that tradeoff, consistent
  with "no magic." However:
  
  - The compiler should emit a **non-fatal diagnostic hint** pointing out
    under-utilized `str` capacity, similar in spirit to Rust's compiler
    hints. Compilation should not be blocked by this.
    
  - This diagnostic-hints feature is **future work** -- needs a working
    parser and some notion of a symbol table before it's buildable. Noted
    here so the idea isn't lost.

---
## 4. Lexer implication: string literals (not yet implemented)

Flagged during discussion, **not yet built**:

- Currently, `"` tokenizes as `PUNCTUATION`, which the lexer treats as a
  delimiter -- meaning `"Hello!"` would currently lex as multiple separate
  lexemes (delimiter `"`, word `Hello`, punctuation `!`, delimiter `"`),
  not one string literal.
  
- String literals need a **distinct scanning mode**: once an opening `"`
  is seen, consume characters verbatim (including characters that would
  normally act as delimiters) until a matching closing `"` is found: the
  whole span becomes one `STRING_LITERAL` lexeme.
  
- This is a different algorithm shape from the current delimiter-driven
  `assign_large_token` walk -- likely needs its own function (e.g.
  `scan_string_literal`), invoked when the outer walk hits a `"`.
  
- Comments support has been added, (check section 6b).
  
- **Status: designed, not implemented.** Next concrete lexer task when
  string support is picked up.

---
## 5. Boolean type

- Axiom will have a **real `bool` type**, conceptually mirroring C's
  `stdbool.h` (`bool`/`true`/`false`) -- not raw C-style integer truthiness
  (0/1). `true` and `false` are values of a genuine boolean type.

---
## 6. Keyword recognition -- lexer data model

Decision: the lexer should collect any fact about a lexeme determinable
from the lexeme's own characters alone, with no surrounding context
needed. Whether a WORD matches a keyword (and which one) fits this test,
so keyword recognition -- not just "is this a keyword" but "which specific
keyword" -- happens at lex time, not deferred to the parser.

**Enums (`keywords.h`):**

```c
enum KEYWORD {
  IF, LET, FOR, WHILE, LOOP, DO, FN, RET, BRK, CONT, CONST, TRUE, FALSE,
  INT, FLOAT, DLOAT, SINT, LINT, CHAR, BOOL, STR,
  NONE,          // real Axiom keyword (null/absence) -- see Section 2a
  NULL_KEYWORD,  // internal sentinel only -- see Section 6a
};

enum KEYWORD_TYPE {
  SYSTEM_RESERVED,             // control/declaration keyword
  DATA_TYPE,                   // primitive or composite type keyword
  PURPOSELY_UNDEFINED_KEYWORD, // sentinel: no keyword assigned/applicable
};
```

**`LexerNode` fields added:**
```c
enum KEYWORD_TYPE keyword_type;  // category: is this node a keyword at all, and which kind
enum KEYWORD keyword;            // specific keyword, valid only when keyword_type != PURPOSELY_UNDEFINED_KEYWORD
```

- `keyword_type` acts as the discriminator: a reader must check
  `keyword_type` first; `keyword` is only meaningful when `keyword_type`
  indicates an actual keyword match.
  
- Both fields are explicitly initialized for every node in `fill_pool`
  (`keyword = NULL_KEYWORD`, `keyword_type = PURPOSELY_UNDEFINED_KEYWORD`),
  same discipline as `token`/`largetoken`. Because initialization is
  explicit and unconditional, enum declaration order (which value is
  numerically 0) is no longer load-bearing -- unlike the earlier
  `token`/`largetoken` case where zero-init via `calloc` was the original
  motivation for careful sentinel placement.
  
- This means: the parser can read `keyword_type` + `keyword` directly off
  a node and know exactly which keyword it is, without re-scanning or
  re-comparing the lexeme's characters itself. Front-loads the matching
  work at lex time, per the "collect as much info as possible" principle.

### 6a. `NULL_KEYWORD` vs `NONE` -- do not confuse

- `NULL_KEYWORD`: internal-only sentinel value for `LexerNode.keyword`,
  meaning "this node is not a keyword, or hasn't been classified yet."
  Never appears as something an Axiom programmer writes in source.
  
- `NONE`: a real, user-facing Axiom keyword (null/absence literal). See
  Section 2a.
  
- Renamed from an earlier attempt that literally used the identifier
  `NULL` -- **rejected**, because `NULL` is a macro from `<stdio.h>`/
  `<stdlib.h>` (typically `((void*)0)`), and the preprocessor would have
  mangled the enum declaration before compilation. `NONE`/`NULL_KEYWORD`
  avoid the collision entirely.

### Resolved: `INVALID_KEYWORD` removed

Cut from `KEYWORD_TYPE`. Reasoning: "not a keyword" already has a home --
`PURPOSELY_UNDEFINED_KEYWORD` on a WORD-classified node already means
exactly that (checked against the keyword table, no match). A lexeme
that isn't a keyword is just not a keyword; there's no separate
"invalid keyword" case distinct from "this WORD didn't match anything,"
so the extra enum value had no distinguishing use and was removed.


### 6b. `COMMENT`: New `LargeTOKEN` added with comment detection support

Axiom currently supports C-style comments.

```c
/* This is a comment */
```

This works both for single line as well as multi-line comments.

```c
// This type of comment is not supported yet.
```

The single line comment type of `//` is not yet supported because of implementation constraints, which is why the earlier design decision of keeping two separate large tokens of `SINGLE_LINE_COMMENT` and `MULTI_LINE_COMMENT` have been collapsed to just `COMMENT` with `/*  */`, opening and closing comment markers as the lexer will treat anything in between these markers as a valid comment.

---

## 7. Deliberately deferred / out of scope for v0.1

- `byte` type (raw byte manipulation)
- Unsigned integer types
- String literal lexing (designed, not implemented -- see Section 4)
- Compiler diagnostic hints (designed, not implemented -- see Section 3)
- Keyword-length-cap exceptions (currently unneeded -- `true`, `false`,
  `bool`, `NONE` all fit `<=5` as-is; see Section 1/2 notes)
- `INVALID_KEYWORD`'s actual purpose (see Section 6, open question)
- `NONE`'s exact type-system semantics (any type vs pointer-only -- see
  Section 2a)
- `keyword`/`keyword_type` are populated at lex time but not yet
  consumed by anything downstream, since no parser exists yet

---

*Keep this addendum in sync with the main spec as decisions get finalized
and implemented. Once a section here is actually built, move/merge it into
the primary spec document rather than letting notes and implementation
drift apart.*
