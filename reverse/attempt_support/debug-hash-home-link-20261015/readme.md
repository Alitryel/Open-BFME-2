# Allocator hash lookup ownership repair

Source base: dc7e44f01d30554ef35b47f2612a99f35bf6aa5b. Actual local index:
19a2565407, 2026-10-15 09:33; original census 5986a99448, 2026-10-15 04:52.
Index SHA256 a80ba518f5ac1ce70a2a30c3903ad5425a12bf8a0e1b4c91d1a05808ba9957a3.
The committed link status is discovery evidence, not this measurement's artifact.
No index, census status/history, baseline, pin, shared header or flags changed.

Rva006C1850Rva006C1920.cpp owned the 70-byte lookup at 0x006C1850,
while Rva006C3AB0DebugSetter.cpp already emitted an identical copy before its
caller. The setter needs the body visible so MSVC preserves retail's reload
ordering for the address-taken output slot. The strong original definition
and the setter's inline definition competed, blocking both units. Rehome the
existing row through add_match --replace-existing and remove the redundant
out-of-line definition, retaining its declaration and other hash operations.

Identity and layout evidence remain the native 0x006C1850..0x006C1896
RET 8 body, its (key >> 3) % bucketCount index, key at +0, value at +4,
next at +8, and retail callers 0x006C259D, 0x006C268C, 0x006C3B6D and
0x006C4969. The names remain address-derived; this repair adds no semantic
class-name or full-layout claim. No donor source is copied.

Acceptance:

- Before and after bounded strict preparation verifies all six rows in the
 two explicitly claimed units, with strict reusable dependency receipts;
 ordinary whole-byte checks pass. add_match independently verifies both
 setter rows. There are no strings or imports to baseline or skip.
- The setter's nondebug object sections are identical, including bytes,
 extents, relocations, bindings and directives. Complete object hashes
 differ after recompilation. The original unit loses exactly the 70-byte
 lookup section and retains six unchanged nondebug sections. The asserting
 scratch proof normalizes COFF symbol references, including relocations.
- Paired local checks refresh the same index in memory with both saved before
 objects, then both strict-current after objects. Both duplicate findings
 disappear. The setter becomes clean; the hash unit retains exactly the two
 unresolved names below. The standalone CLI agrees: 0/2 -> 1/2 clean and
 0 -> 584 existing linked retail bytes. The setter previously owned 514
 bytes and now owns 584; the hash unit moves from 527 to 457. Total matched
 and authored C++ bytes do not grow.
- This is self-strict currency for the explicit cohort and a legacy local
 link prediction against unchanged external providers. No closed-strict
 gain, link.exe placement or new census result is claimed.
- EH verification: one EH-bearing row, EXACT, no missing objects. Frozen
 definitions, canonical classes, new COMDAT variants, converged data (eight
 addresses), shadow data, CSV and whitespace checks pass. The affected
 placement sweep returns zero bodies and zero pins.

Remaining dependencies in the hash unit:
?rva00033150@Rva00033150@@QAEXH@Z and
?rva000338F0@Rva000338F0@@QAEXH@Z. Its independent link repairs remain open.
Rva006C1F60Finish.cpp was inspected as another allocator consumer; its three
GeneralAllocator unresolved providers are independent and no improvement is
attributed to that unit. Current probes of Rva00500BF5TreeInsert.cpp,
Rva005E62F1Constructor.cpp, GapBodiesSeat1B.cpp and AutoPickUpUpdateUpdate.cpp
already link before changes; those are not new gains.

Reference linking review: clean verified gitlink/checkout
a7c38d3b2597121f178ab5190b3062478823257d. Reviewed upstream repairs
de59a7e9 (equivalent COMDAT expressions), 92a8d854 (canonical data owner),
and 4966496c (surplus AsciiString emission). Ownership and emission lessons
apply; BFME 1 layouts and bodies are not imported. Official master fetched
to 75ff0c1485a68eafb10344670711edbee8679b62. Updating remains blocked by
another worker's reference/open-bfme-1 file claim and the outstanding large
old/new full-gate comparison described in
../unicode-comparator-link-20261014/readme.md. Preserve verified inputs;
no successful freshness stamp or gitlink update is claimed.

The Rva0042CB81 guard-constructor trial was restored and recorded separately
in ../fp-guard-link-20261015/readme.md. No unchanged blocked conversion was
retried. Work selection used repair_queue link and link_rank help/top/near
plus D/S/A/L queries. No data-back ranking was used for this duplicate-symbol repair.

No full link cycle, census build/measure/history, nightly, boot runner or
shadow publisher was started. Scratch sources, before objects/receipts and
asserting proof.py remain in build/debug-hash-home-link-20261015.
