# LadderDefs CRT/string prefix prerequisite, 2026-10-25

The GameNetwork Luna handoff reported C2039 in cstdlib: atoi missing from the
global namespace after composition hoisted the import declaration below string
headers. The baseline normal merge dry-run reproduced the seed failure under
every merged flag set.

The unchanged CRT rename/include/redeclaration and string-header guards now
live in local BfmeLadderStringPrefix.h. Its include preserves their order during
composition. No function body, template specialization, symbol, source owner,
compiler flag or hatch count changes.

Acceptance:

- ./build.sh GameSpy/LadderDefs.cpp: 50/50 existing rows exact, including all
  38 funclet rows through parent-EH label resolution, and two named imports.
- find_declared_unmatched passes the source and new header; diff --check passes.
- Normal merge dry-run now accepts LadderDefs.cpp, StlSweepW5Rva0054D7E2.cpp,
  Rva0054D8D8Dtor.cpp and FamilyDeletingDtors_muse-10-54D958.cpp: 59 byte rows.
  This clears the seed composition failure and enables three whole donors.
  Leave the approved merge to Luna with normal current routing and claims.
- LadderListFindLadder.cpp remains rejected: C2819/C2227 after class union,
  because its pointer-based list view conflicts with the real list members.
  Mixed donors stlport_list_asciistring_insert.cpp and Rva0054D974Dtor.cpp remain
  behind for their normal split lane. The Common donor is outside this seat.

Receipts: build/sol-ladder-before.txt, sol-ladder-build.txt,
sol-ladder-after.txt and refreshed build/consolidation/network snapshot.
No files removed, recovered bytes or identity debt retirement is claimed. One
private header is added; no protected register is edited. The existing
Microsoft-header queue entry for LadderDefs is retained, since the same CRT
import override is still present.

Publication audit covers outgoing GameSlot and wrapper prerequisites plus
this staged edit. No source moves, renamed paths or source deletions exist in
that batch. The new quoted include resolves beside LadderDefs and its retail
TU. Active tools/hooks/workflows, includes, build inputs and registries require
no repointing. Existing EA paths and provenance are retained.

## Follow-up: findLadder sentinel access

LadderListFindLadder.cpp now reads each sentinel through a pointer reference to
the existing member's first word. The old minimal pointer view and STLport's
complete list view have that same storage (vendor/stlport/stl/_list.h,
_List_base::_M_node); the native head offsets remain local +0, special +4,
standard +8. Each loop still reloads its sentinel at the original use sites.
This avoids applying operator-> directly to a complete list after class union.
No allocation, ABI name, private layout, source ownership or field order changes.

The standalone body remains 151/151 bytes exact. Declared-unmatched and
diff --check pass. The normal merge dry-run now accepts all five whole files,
60 rows, with no rejected donor. Receipt: build/sol-ladder-find-build.txt and
sol-ladder-find-after.txt. Leave the merge and mixed-file splits to Luna; no
merge is applied here and no source file is removed. The source-only follow-up
adds no path move or consumer to the publication audit above. The prefix commit
gate also reports 13 shadow code-identity findings against the register; those
are retained, and this prerequisite makes no identity retirement claim.
