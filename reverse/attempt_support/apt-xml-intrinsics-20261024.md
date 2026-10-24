# Apt XML predicate debugger-trap intrinsic repairs

Existing predicate identities and bitfield layout remain the ledger's, backed by the
corresponding checked-cast assertion callers. Each complete native body is110B.
Only conditional inline INT3 statements change to the genuine MSVC7.1 __debugbreak
intrinsic, also used by the shipped CRT crtdbg.h:391. No flags, layouts, ABI, callback,
literal, input domain or symbol pins change. No memory fences are needed.

Each commit converts one body, after private full-extent byte comparison and the normal
whole-file gate over all four440B predicates and16 literal references. The published
index measures432 linked bytes for this file; each preview remains LINKS432->432.
These are inline-assembly repairs in an already-counted C++ file: zero coverage gain.

Verified conversions, banked one per commit:
- `isXmlNode` at `0x006DBDE0`: complete110B; both traps use the intrinsic.
