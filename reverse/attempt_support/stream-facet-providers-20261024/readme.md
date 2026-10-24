# Existing stream and numeric facet providers

BFME2 input 44360745f0; published census b711de3634 (2026-10-23 14:28),
retail-truth-4. Model gpt-6.1-sol. The narrow_istream and narrow_num_put
units retain independent blockers, but current linking library consumers
already emit these same named helpers. Rehome twenty-nine existing rows across
eight receiving units, preserving code, identity, ABI, flags, pins and aliases.
The stream constructor's existing compiler handler and cleanup move with the
parent; existing parent FuncInfo evidence, not adjacency, establishes ownership.
No authored C++ coverage is added.

Preflight: complete receiving bodies and relocations exact for all twenty-nine,
zero unresolved relocations and no wrong identity binding in the moved rows.
Original named rows, vendor source and receiving callers retain their identity
and provenance basis. Facet width/layout assumptions are not newly inferred
from matching bytes; donor layouts/addresses are not imported.

BFME1 reviewed at verified f5140c1c: NumPutLongLongNarrow.cpp,
stlport_classic_locale_impl.cpp and vendor _istream.h/_num_put.h/_locale.h.
Its classic locale already declares independent formatter providers; its
expanded long-long formatter and input-constructor semantics are reference
leads, not evidence for BFME2 ABI or body boundaries. BFME2's current TUs
already have supported provider bindings and exact emitted helpers. Prior full
reference-update comparison: link_library_providers_20261023/readme.md.

Excluded: num_put deleting destructor 0x000072C0/30B in classic_locale
byte-matches, but its num_put destructor binding at native 0x000072E0 is
wrong/unknown. Recorded blocked and claim released; original row unchanged.
Existing narrow/wide identity prerequisites and banks are not retried.

Also excluded: facet constructor 0x00006F50/30B. Although the receiving
body is exact, moving its ownership sorts classic_locale ahead of locale_global
(first row 0x00006F70). Its divergent basic_string<char> destructor then wins,
and code_identity_gate reports a new divergent definition. Retaining the
original owner restores the retail-proven locale_global destructor selection;
no code or verifier workaround. Recorded blocked and released its claim.

Moved rows (RVA, extent, receiving unit):

- 0x0000FE40, 50 B, Code/Libraries/Source/WWVegas/WWLib/stlport_classic_locale.cpp
- 0x00010220, 50 B, Code/Libraries/Source/WWVegas/WWLib/stlport_classic_locale.cpp
- 0x00016590, 144 B, Code/Libraries/Source/WWVegas/WWLib/stlport_narrow_fstream.cpp
- 0x00019650, 24 B, Code/Libraries/Source/WWVegas/WWLib/stlport_narrow_money_get_string.cpp
- 0x00007C70, 21 B, Code/Libraries/Source/WWVegas/WWLib/stlport_narrow_ostream.cpp
- 0x00007E90, 32 B, Code/Libraries/Source/WWVegas/WWLib/stlport_narrow_ostream.cpp
- 0x00009860, 49 B, Code/Libraries/Source/WWVegas/WWLib/stlport_narrow_ostream.cpp
- 0x0000D2D0, 74 B, Code/Libraries/Source/WWVegas/WWLib/stlport_classic_locale.cpp
- 0x0000D410, 74 B, Code/Libraries/Source/WWVegas/WWLib/stlport_classic_locale.cpp
- 0x000132E0, 13 B, Code/Libraries/Source/WWVegas/WWLib/stlport_narrow_ostream.cpp
- 0x000132F0, 14 B, Code/Libraries/Source/WWVegas/WWLib/stlport_narrow_ostream.cpp
- 0x00013760, 21 B, Code/Libraries/Source/WWVegas/WWLib/stlport_create_filebuf.cpp
- 0x000173E0, 17 B, Code/Libraries/Source/WWVegas/WWLib/stlport_wide_istream.cpp
- 0x00017B90, 8 B, Code/Libraries/Source/WWVegas/WWLib/stlport_narrow_ostream.cpp
- 0x00017BA0, 15 B, Code/Libraries/Source/WWVegas/WWLib/stlport_narrow_ostream.cpp
- 0x00017D30, 21 B, Code/Libraries/Source/WWVegas/WWLib/stlport_narrow_istreambuf_iterator.cpp
- 0x0001BBE0, 15 B, Code/Libraries/Source/WWVegas/WWLib/stlport_narrow_ostream.cpp
- 0x0001BE10, 13 B, Code/Libraries/Source/WWVegas/WWLib/stlport_narrow_ostream.cpp
- 0x0001C6C0, 10 B, Code/Libraries/Source/WWVegas/WWLib/stlport_narrow_ostream.cpp
- 0x0001C6D0, 14 B, Code/Libraries/Source/WWVegas/WWLib/stlport_narrow_ostream.cpp
- 0x0001D0F0, 9 B, Code/Libraries/Source/WWVegas/WWLib/stlport_narrow_ostream.cpp
- 0x0001D9D0, 18 B, Code/Libraries/Source/WWVegas/WWLib/stlport_narrow_filebuf.cpp
- 0x00620120, 18 B, Code/Libraries/Source/WWVegas/WWLib/stlport_narrow_ostream.cpp
- 0x006CFE10, 13 B, Code/Libraries/Source/WWVegas/WWLib/stlport_wide_istream.cpp
- 0x0000CF10, 79 B, Code/Libraries/Source/WWVegas/WWLib/stlport_classic_locale.cpp
- 0x0000D130, 79 B, Code/Libraries/Source/WWVegas/WWLib/stlport_classic_locale.cpp
- 0x00007220, 30 B, Code/Libraries/Source/WWVegas/WWLib/stlport_classic_locale.cpp
- 0x0075C1E0, 28 B, Code/Libraries/Source/WWVegas/WWLib/stlport_narrow_fstream.cpp
- 0x0075C1FC, 10 B, Code/Libraries/Source/WWVegas/WWLib/stlport_narrow_fstream.cpp

Acceptance: paired scoped **legacy** link_check rises from 11,960 to 12,792
bytes: **+832 B linked**, eight of ten units clean before and after.
The 29 moved extents total 963 B: the progress metric excludes the existing
three gen-alias bodies (102 B), gen-funclet (28 B), and one 0xCC byte.
This does not claim new authored C++ bytes, self-strict/closed-strict progress,
or a full-image link result. The blocked source collectors retain their
scan_not, __find_if, and string range-initializer prerequisites.

Full scoped byte gate: 220/220 rows, imports and strings pass. EH 17/17
exact; code identity zero findings both before and after. Frozen-definition,
CSV and whitespace checks pass. No source, header, alias, pin or baseline
changes. Current-object receipts were already valid, so no refresh compile
was needed.
