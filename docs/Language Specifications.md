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
# Experimental stuff

# Forgetful Mode (Experimental)

Axiom provides an optional **Forgetful Mode**, intended for developers who wish to retain manual memory management while receiving additional runtime assistance in detecting memory-related issues.

Forgetful Mode is **disabled by default** and can be enabled during project initialization or through the project's configuration file.

## Purpose

The goal of Forgetful Mode is **not** to replace manual memory management, but to assist developers by tracking heap allocations and reporting potential memory management mistakes.

This mode is especially useful during development and debugging of large projects where manually tracking every allocation becomes increasingly difficult.

## Current Features

When Forgetful Mode is enabled, the runtime maintains an internal allocation tracker.

Each heap allocation records metadata including (but not limited to):

- Allocation identifier
- Allocation size
- Source file
- Line number
- Function name
- Allocation status (allocated/freed)

Upon program termination, the runtime automatically generates an allocation report.

Example:

```text
=========================================
Forgetful Mode Report
=========================================

Total Allocations : 127
Freed             : 126
Leaked            : 1

Leak Detected

Allocation ID : 42
File          : src/main.ax
Function      : main
Line          : 87
Size          : 64 bytes

No matching free() call was found.
```

## Philosophy

Forgetful Mode is designed as a **developer assistance tool**, not as a replacement for manual memory management.

Programs written with Forgetful Mode disabled continue to use explicit allocation and de-allocation exactly as written by the programmer.

## Future Expansion

Future versions of Forgetful Mode may provide additional diagnostics, including:

- Memory leak detection
- Double-free detection
- Use-after-free detection
- Dangling pointer diagnostics
- Optional automatic cleanup of unreleased allocations during program shutdown

The implementation details of Forgetful Mode are intentionally unspecified and may evolve between compiler versions without affecting the language itself.

---
