# WeaponSetUpgrade split provider blocker (codexb2, 2026-10-26)

The inherited split trial for `Code/GameEngine/Source/GameLogic/Object/Upgrade/WeaponSetUpgrade.cpp`
carved `?buildFieldParse@WeaponSetUpgradeModuleData@@SAXAAVMultiIniFieldParse@@@Z`
(0x004B56F6, 34 bytes) from
`Code/GameEngine/Source/GameLogic/Object/Update/ModuleDataBuildFieldParseChained.cpp`.
The allocated TU check passed. The scoped build verified 63/63 functions and
data rows; both declaration scans passed. The generated split is preserved at
`build/weaponset-upgrade-split-blocked.patch` for inspection.

The staged source trial is not publishable: `python3 tools/data_check.py --staged`
reported `Code/GameEngine/Source/GameLogic/Object/Upgrade/WeaponSetUpgrade.cpp`
`duplicate-def` for `?BfmeWeaponSetUpgradeFields@@3QBUFieldParse@@B` at
0x00858020. The same initialized definition remains in the residual
`ModuleDataBuildFieldParseChained.cpp`, so this is a real duplicate provider.
Do not retry unchanged; Sol must reconcile the shared FieldParse table ownership
before another split trial. The code-identity staged scan reported 0 new
findings. `tu_map.py --check-fresh` reports stale inputs including staged
`reverse/functions.csv`; no regenerated map was made.

No identity or provider/consumer improvement is claimed. The trial was restored
after preserving this evidence; its source/RVA claims were released.
