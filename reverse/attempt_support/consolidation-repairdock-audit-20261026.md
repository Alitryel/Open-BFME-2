# RepairDockUpdate consolidation audit — 2026-10-26

Allocated destination: `Code/GameEngine/Source/GameLogic/Object/Update/DockUpdate/RepairDockUpdate.cpp` (shard 3/5). The current planner snapshot had no missing inputs and passed `name_lane.py consolidate --check`; approved TU routing was confirmed by `tu_skeleton.py --plan`.

## Applied composition

- `tu_skeleton.py --merge` accepted and absorbed four unchanged donors: `RepairDockUpdateModuleDataParse.cpp`, `RepairDockUpdatePoolKey.cpp`, `RepairDockUpdateXfer.cpp`, and `RepairDockUpdateModuleDataCtor.cpp`.
- `tu_skeleton.py --split` carved approved row `0x004A11CE` from `ConstIntGetters4.cpp`; its residual retains the other rows. The split moved no hatches.
- Net source-file change: **3 fewer files** (four donor files removed, one destination TU added; the mixed getter file remains). One TU was merged. Six function rows moved, including the EH handler; the `g_00C51C10` data row and its ledger ownership moved with the parse body. The tool preserved the existing hatch total and transferred the protected data register keys.
- `RepairDockUpdateBehaviorCtor.cpp` and `RepairDockUpdateAction.cpp` remain untouched. The ctor donor failed with `C2511: RepairDockUpdate::RepairDockUpdate(Thing *,const ModuleData *)` not found; the action donor failed with `C2039: buildFieldParse is not a member of RepairDockUpdateModuleData`. `Rva0058A0F4Derived.cpp`'s destructor carve is refused because a copied helper or datum would grow an escape-hatch count.

## Verification

- `./build.sh RepairDockUpdate.cpp ConstIntGetters4.cpp`: source claims OK; data row byte-verified; 273/273 matched functions byte-verified; string, float and import references verified.
- `find_declared_unmatched.py` on both files: all definitions already matched.
- `tu_ownership.py --staged`: exit 0.
- `link_check.py --staged --new-variants --staged-peers`: exit 0; both staged units used current object receipts and no selected-COMDAT conflict was reported.
- `code_identity_gate.py --staged` (shadow): one finding remains, an unreferenced `/alternatename` for `_vtbl_00C4ED70`; it is carried from the merged donor and is not claimed as identity cleanup.
- `data_check.py --staged` (shadow): three `wrong-name` findings at `0x00A03BA0`, `0x00A03B9C`, and `0x0084ED70`. These remain register debt after the merge and need Sol's identity/data review; no key was retired here. The merge tool's follow-up is `repair_queue.py retire data <destination>` after its post-commit owner verdict.
- `check_csv.py`: OK. The regenerated scoped planner snapshot passes `--check`. No RepairDockUpdate entry was found in either header queue.
- Tooling/path audit found no active reference to the four deleted donor filenames in `tools/`, `.githooks/`, `.github/`, build entrypoints, include trees, or the Doxygen source list beyond the generated destination entry. Historical `link_status.csv` receipts and references for the two intentionally retained donors remain stale/current-owner evidence and are not treated as proof of this composition.
- The pre-push `link_batch_audit.py` for this commit must still be reviewed for selected-provider and consumer-binding changes; no census or maintainer-only link cycle was run.

No code-identity or data debt is claimed retired. No retail function bytes were newly recovered; this is a source-file consolidation.
