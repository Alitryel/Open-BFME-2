# BridgeScaffoldBehavior consolidation handoff

Destination: `Code/GameEngine/Source/GameLogic/Object/Behavior/BridgeScaffoldBehavior.cpp`.

The allocated TU merge accepted four unchanged donors and retained all seven approved rows. It rejected `BridgeScaffoldBehaviorPoolKey.cpp` because `ScaffoldTargetMotion` is defined twice (C2011 in the generated TU). The plan's mixed `Common/Rva0024A797Grandchildren.cpp` split was refused because a copied helper or datum would grow an escape-hatch count. Both remain for a Sol repair; neither was modified.

Verification on the applied composition: `./build.sh Code/GameEngine/Source/GameLogic/Object/Behavior/BridgeScaffoldBehavior.cpp` passed (7/7 matched rows; string, float and import reference checks passed); `find_declared_unmatched.py` found no unmatched definitions; staged data check found no findings; staged TU ownership passed. `name_lane.py consolidate --check build/consolidation` passed after regenerating its report. `header_adopt_lane.py order` showed no type with a new private view attributable to this merge. Hatch totals were carried by the merge tool. `tu_map.py --check-fresh` still reports the snapshot stale because `reverse/functions.csv` changed; this consolidation lane does not commit a regenerated map.

`code_identity_gate.py --staged` found four new shadow findings for alternate names already carried with the merged donor content (`_vtbl_00C40B70`, `_vtbl_00C40B88`, `_vtbl_00C40B98`, `_vtbl_00C40C54`, all targeting `Rva00458402`). Preserve these for Sol's identity lane; no identity debt is claimed retired.

The path consumer search found only source comments, append-only naming provenance, historical attempt evidence and the prior census snapshot for donor paths. No active tool, hook, workflow, include or build configuration referenced these donor files. Current source/ledger ownership is the merged TU. A new post-composition census is not available in this lane; rely on the outgoing batch's pre-push selected-provider audit and carry any inconclusive result to the next census. The historical path mentions remain intentionally unchanged.
