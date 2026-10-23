# BridgeBehavior module-data link repair

Retail BridgeBehaviorModuleData table C40A10 has all 31 entries of the existing
`Code/GameEngine/Include/Common/BfmeModuleData.h` interface, with its deleting
destructor 45824C in slot zero. Destructor 45804A and the folded base destructor
49B47C restore Snapshot table BBB554. These are target table/relocation facts;
the list cleanup semantics and member layout retain the existing BFME1 recovery.

Replace the empty private UpdateModuleData base with the established ModuleData
interface and Snapshot teardown. Mark the intermediate base novtable: retail
does not install its table. Preserve the existing folded UpdateModuleData
destructor row and all member offsets. No new pin or alias is needed.

Same-index scoped `tools/link_check.py` before/after, published index 456ce161c5
(2026-10-23 06:28): **0 -> 140 B newly linked**. The previous competing
UpdateModuleData destructor, deleting destructor and vtable disappear. This is
a legacy scoped prediction; no self-strict, placed or closed-strict gain is
claimed. The index lacks a current dependency closure.

Acceptance: `./build.sh` passes all 6 rows; `tools/eh_verify.py` reports EXACT
1/1; `tools/find_declared_unmatched.py` passes. `link_check.py --prepare-current`
was attempted but refuses an include inventory with unknown macro/parent search
roots, so no strict reusable receipt is claimed. Normal byte verification and
the paired link preview complete successfully.

Related sweep: SlowDeathBehaviorModuleDataCtor and CallHelpOnDamageModuleDataDtor
already use the shared interface on this checkout. CreateCrateDieModuleDataDtor
already links 89 B and needs no change. Their stale census entries are not new
improvements. GettingBuiltBehavior was repaired upstream previously.
