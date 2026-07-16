---
tags:
  - lang-spec
---
---

So, it's time to decide what the new language should look like.

For now, this is what I have decided.

# My Language Specification

Chosen Language Name: `Axiom`.

`Axiom-Lang` Specification `v0.1`

> This specification describes the language as it currently exists.
   It is expected to evolve alongside the compiler.
  When implementation and specification disagree,
  the specification should be updated to reflect the
  intended behaviour.


---
## 0. Goals

The language is designed to:

- Teach compiler construction.
- Teach systems programming.
- Keep syntax explicit.
- Avoid unnecessary magic.
- Prefer deterministic behaviour.

---
## 1. Philosophy

- Compiled language.
- Manual memory management. 
- Explicit braces for blocks. 

> The language is intended to expose systems programming concepts rather than hide them, hence the reason for leaving memory management to the user.

---
## 2. Lexical Rules

- Identifiers begin with letters.
- Identifiers may contain digits.
- Identifiers cannot begin with digits.
- Keywords <= 5 characters. (May lift this restriction for certain special keywords if needed)
- Keywords are pure ASCII only, cannot contain `PUNCTUATION`.
- `IDENTIFIER` size <= 15 characters. 

> The `IDENTIFIER` size limit simplifies the first implementation of the compiler. The limit may be relaxed in future revisions.


More lexical rules regarding keywords and types defined in [[axiom-spec-notes-v0.1]].

---
## 3. Syntax Rules

- Blocks use braces.
- Statements terminate with ';'

---