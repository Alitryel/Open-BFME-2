Tree-hint vector cleanup link repair, 2026-10-20

Bind W3DWater's out-of-line vector storage cleanup to its existing rowed
STLport folds, and the RegionDetailsArmiesPage constructor to the existing
vector destructor. In that destructor, declare the rowed _Destroy and retain
the shim allocator's null-guarded free inline without emitting an allocator
copy. The current shim already ignores the count; no element-layout change or
new function identity is asserted. Existing fold pins remain unchanged.

Paired legacy-index preview e7a7769fe5 (2026-10-20 18:36): W3DWater 0 -> 1,303,
vector destructor 0 -> 63, page constructor 0 -> 185 nonpadding matched bytes;
+1,551 B total across three units. Original current objects were saved before
editing; both phases replace all three objects in the same unchanged index
using their census basenames. All five blocking fields are empty afterwards.
Retained COMDAT byte/relocation digests are identical, no new COMDATs. Details
and object/index hashes are in proof.json; proof.py reproduces the comparison
from local build/seat-water snapshots.

Before/after strict preparation and normal byte gates pass 33/33 rows, with
string/float/import checks. EH, new variants, class gate, undeclared definitions,
converged data and whitespace checks pass. These are self-strict objects and
legacy preview results; closed-strict closure and executable gain are unmeasured.
Authored C++ bytes +0; no census/status/index rewritten.

The initial destructor trial declared allocator deallocate externally, which
prevented native inline storage cleanup (1/4 peer rows failed). Restoring its
existing visible null-guarded free with import-forceinline passes. No import
pointer remains referenced, as checked by the paired unresolved inventories.
Other TreeHint users retain unrelated blockers and were not edited.

BFME1 donor review reused unchanged 4483e88da1c2: a411b334c, 3313189ad and
c54305633 supply ownership/provider leads, as recorded in the existing
shared-node-allocator evidence. The body here follows the BFME2 shim and
retail; no donor address/layout transplant. t=20min model=gpt-6.1-sol.
