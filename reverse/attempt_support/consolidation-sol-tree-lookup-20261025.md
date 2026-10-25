# Tree lookup consolidation prerequisite, 2026-10-25

Seat codexb, device pool. Current in-memory routing approves W3DTreeBuffer.cpp
and W3DTreeBufferRecordLookup.cpp. The Luna device handoff and the normal
before receipt build/sol-tree-removal-final-after.txt report C2039 for
rva000ECF2A and C2065 for count.

The seed now declares the existing lookup and startMorph methods. The donor
uses the seed's m_count/m_records member spellings, retaining its original
0x5c0 array offset, 0xe8 stride and +0x44540 count. Its existing TreeLookupRecord
view is applied to the canonical record array at the use site; key +0x58,
guard +0xc8 and unsigned state +0xd4 retain their original evidence and types.
The native indexed startMorph call and its parameter order are unchanged.
No class layout, header contract, compiler flag, pin or other hatch was added.

Acceptance: ./build.sh on both sources passes 18/18 rows, all string/float/import
checks and scoped source claims (build/sol-tree-lookup-build.txt). Declared
unmatched and class-gate checks pass. Data identity scans two sources with zero
findings; code identity scans 18 rows with no new problems or notes. EH verifies
two EXACT parents with no missing objects. The Microsoft-header scan finds no
local definitions. Neither source carries a data/identity baseline key or
header/ms-header queue entry; no key was retired.

The final normal --merge --dry-run accepts the seed, removal donor and lookup
donor with 18 matched rows (build/sol-tree-lookup-after.txt), and emits the
composed C++. This is normal lane acceptance, not a diagnostic-only trial.
Leave that compatible subset for Luna; movement, other private declarations,
string-header conflicts, six mixed files and one protected donor remain.

Publication audit: the outgoing merge-base range including inherited c1898b7266
and a957cd3f2a plus this staged prerequisite contains no source-path changes.
Active tools/hooks/workflows/includes/build inputs/registries need no path
repair; historical EA paths remain. Source files removed 0, recovered C++
bytes 0, identity keys retired 0. Keep the seed, lookup and this handoff file
claims and 0x000ECF2A until publication is confirmed, then release them.
