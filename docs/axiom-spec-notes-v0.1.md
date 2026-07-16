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

## 1. Keywords (control flow / declarations)

```
if, let, for, while, do, loop, fn, ret, brk, cont, const, true, false
```

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
- `true` / `false` exceed the 5-character keyword cap is N/A (`true` = 4,
  `false` = 5 -- actually both fit). No exception needed after all;
  earlier discussion flagged `false` as a possible cap exception, but at
  5 characters it fits the `<=5` rule exactly. *(Left here as a note in
  case the cap is ever tightened below 5.)*

## 2. Type keywords

```
int, float, dloat, bool, char, str, sint, lint
```

- `dloat` = double, `sint` = short int, `lint` = long int. Naming
  convention: prefix letter + shortened base word (`d`+`loat`, `s`/`l`+`int`).
  Future type names should probably follow the same scheme for consistency.
- `byte` -- **deferred**, not in v0.1. Axiom isn't tackling advanced/raw
  byte-manipulation topics yet. Cheap to add later (purely additive);
  costly to remove once code depends on it -- hence deferring rather than
  guessing now.
- No signed/unsigned distinction yet. `sint` and `lint` are **signed for
  now**. Unsigned variants are an open future item, not yet scoped.

## 3. `str` type -- design decisions

- `str` is a **composite type**, built from `char`, not a true primitive.
  This is a deliberate choice consistent with Axiom's philosophy (Section 1:
  manual memory management, expose systems concepts rather than hide them).
- Declaration requires an explicit capacity, e.g.:
  ```
  str[10] name = "Hello!";
  ```
- **Null-termination** (C-style, scan for `\0`) is the chosen approach for
  determining actual string length vs declared capacity -- decided over a
  length-prefixed alternative, mainly because it's the more direct fit to
  integrate into the lexer at the current stage.
- Unused capacity (e.g. 3 wasted bytes in `str[10]` holding `"Hello!"`) is
  **allowed to compile** -- the programmer owns that tradeoff, consistent
  with "no magic." However:
  - The compiler should emit a **non-fatal diagnostic hint** pointing out
    under-utilized `str` capacity, similar in spirit to Rust's compiler
    hints. Compilation should not be blocked by this.
  - This diagnostic-hints feature is **future work** -- needs a working
    parser and some notion of a symbol table before it's buildable. Noted
    here so the idea isn't lost.

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
- Comments will likely need similar special-zone scanning logic later.
- **Status: designed, not implemented.** Next concrete lexer task when
  string support is picked up.

## 5. Boolean type

- Axiom will have a **real `bool` type**, conceptually mirroring C's
  `stdbool.h` (`bool`/`true`/`false`) -- not raw C-style integer truthiness
  (0/1). `true` and `false` are values of a genuine boolean type.

## 6. Deliberately deferred / out of scope for v0.1

- `byte` type (raw byte manipulation)
- Unsigned integer types
- String literal lexing (designed, not implemented -- see Section 4)
- Compiler diagnostic hints (designed, not implemented -- see Section 3)
- Keyword-length-cap exceptions beyond `false` (currently unneeded, see
  Section 1 note)

---

*Keep this addendum in sync with the main spec as decisions get finalized
and implemented. Once a section here is actually built, move/merge it into
the primary spec document rather than letting notes and implementation
drift apart.*
