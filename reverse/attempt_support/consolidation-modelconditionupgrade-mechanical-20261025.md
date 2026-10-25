# ModelConditionUpgrade mechanical merge handoff

For `Code/GameEngine/Source/GameLogic/Object/Upgrade/ModelConditionUpgrade.cpp`, the planner snapshot passed its currency check and the allocated TU dry run accepted the destination plus `ModelConditionUpgradeConstructor.cpp` and `Rva004B63BDUpgradeImplementation.cpp` unchanged. Three rows were preserved and the two donor files were absorbed.

The plan left these donors refused, with the exact tool reason:

- `Code/GameEngine/Source/Common/System/ModelConditionUpgradePoolKey.cpp`: `keyed in a protected path-keyed register (needs a Verifier-Change commit)`
- `Code/GameEngine/Source/GameLogic/Object/Update/ModelConditionUpgradeModuleDataCtor.cpp`: `keyed in a protected path-keyed register (needs a Verifier-Change commit)`

They were not modified or merged. They need Sol's protected-register workflow before a later mechanical trial. No moved source appeared in `reverse/code_identity_baseline.tsv`, `reverse/data_check_baseline.txt`, `reverse/header_queue.tsv`, or `reverse/ms_header_queue.tsv`.

The commit hook's post-merge shadow identity scan also reports `definition: divergent | ?set@WeaponTemplateSetHead@@QAEXH@Z` (3 rows scanned, 1 new finding). This TU-local finding remains outstanding for Sol's identity lane; the merge did not retire it or change the identity baseline.
