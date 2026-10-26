# RepairDockUpdate consolidation provider prerequisite

The shard-3 allocator listed `Code/GameEngine/Source/GameLogic/Object/Update/DockUpdate/RepairDockUpdate.cpp`; `--check-tu` passed. The scoped `name_lane.py consolidate --under Code/GameEngine/Source/GameLogic/Object/Update/DockUpdate/` report had `missing_inputs=[]`, and its snapshot check passed. `tu_skeleton.py --plan` showed nine approved rows, six donor files and two mixed files.

The merge dry run accepted these unchanged donors:

- `RepairDockUpdateModuleDataParse.cpp`
- `RepairDockUpdatePoolKey.cpp`
- `RepairDockUpdateModuleDataCtor.cpp`

That trial moved four matched rows (including the pool-key EH handler). It rejected `RepairDockUpdateBehaviorCtor.cpp` with C2511 because the constructor declaration is absent from the destination class view, `RepairDockUpdateXfer.cpp` because `BfmeXfer.h` cannot resolve `Snapshot`, and `RepairDockUpdateAction.cpp` because `RepairDockUpdateModuleData::buildFieldParse` is absent from the destination view. These need a Sol prerequisite pass; this lane did not edit declarations or bodies.

Mixed-file trials were reviewed. The `ConstIntGetters4.cpp` carve for RVA `0x004A11CE` matched 1/1 rows beside the TU, but applying it was refused because another worker held the donor file claim. The `Rva0058A0F4Derived.cpp` carve for RVA `0x004A11D4` was blocked because moving its copied helper/data would grow a hatch count. Neither split changed files.

The applied merge trial passed `./build.sh` (4/4 matched rows, source claims and data rows verified), `find_declared_unmatched.py` (all definitions matched), `eh_verify.py` (exact), `check_csv.py`, `tu_ownership.py --staged`, `hatch_counters.py --staged`, and case-collision checks. `class_gate.py` reported no finding for the destination. Header and MS-header queue probes showed no `RepairDockUpdate` item. The path-consumer search found no active references to the three absorbed source paths outside their provenance comments in the generated TU; ledgers and protected path registers were repointed by `tu_skeleton.py`.

Identity and binding status remains a prerequisite. The identity register is in `shadow` mode; its staged scan reported an unreferenced `_vtbl_00C4ED70` alternatename, which was already present in the constructor donor and moved with the hatch counter. The staged data scan reported three wrong-name findings at `0x00A03BA0`, `0x00A03B9C` and `0x0084ED70`; no retirement was attempted. `link_check.py --staged --new-variants --staged-peers` reported no new selected-COMDAT conflict. However, `link_check.py --refresh --current-ledger <TU>` refused because 60 current-ledger object receipts were missing, including `FramGrab.obj`; it therefore could not establish provider/consumer bindings for the new composition. The publish command returned immediately due the shared account cooldown, so the pre-push `link_batch_audit.py` did not run.

The trial merge commit `f60b25e606` was withdrawn before publication, and its source/ledger changes were restored. The commit hook had passed; no merge is retained. Its file and RVA claims were released. Retry only after the missing object receipts are available and the provider/consumer comparison can be completed; address the listed compile prerequisites in Sol's lane first.
