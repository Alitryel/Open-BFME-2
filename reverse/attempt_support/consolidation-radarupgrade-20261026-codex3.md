# Mechanical consolidation blocker: RadarUpgrade

Date: 2026-10-26
Destination: `Code/GameEngine/Source/GameLogic/Object/Upgrade/RadarUpgrade.cpp`

The approved plan has seven rows, three donors and one mixed donor. The dry run
accepted no donors:

- `RadarUpgradePoolKey.cpp`: `C2039`, `getModuleNameKey` is not a member of
  `RadarUpgrade`; the composed member definition also reports `C2270`.
- `RadarUpgradeUpgradeImplementation.cpp`: `C2143` missing `;` before `*` and
  `C2501` missing type for `Rva004B46F9::Object`.

Result: `blocked: no verified merge of two or more donors`. No files or claims
were changed. Sol owns the declaration prerequisites.
