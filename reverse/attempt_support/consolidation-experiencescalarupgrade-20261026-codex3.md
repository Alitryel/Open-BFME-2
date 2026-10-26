# Mechanical consolidation handoff: ExperienceScalarUpgrade

Date: 2026-10-26
Destination: `Code/GameEngine/Source/GameLogic/Object/Upgrade/ExperienceScalarUpgrade.cpp`

The approved merge trial accepted `ExperienceScalarUpgradePoolKey.cpp` and
`ExperienceScalarUpgradeModuleDataCtor.cpp` unchanged. Its three moved rows
passed `./build.sh` byte verification, and `find_declared_unmatched.py` found
no unrowed definitions. The merge tool carried the protected data keys and
transferred the hatch accounting.

The dry run rejected these donors; keep their bodies in place until Sol resolves
the class prerequisites:

- `ExperienceScalarUpgradeConstructor.cpp`: `C2039`,
  `getModuleNameKey` is not a member of `ExperienceScalarUpgrade` in the
  composed TU.
- `ExperienceScalarUpgradeUpgradeImplementation.cpp`: the same `C2039` for
  `getModuleNameKey` in the composed TU.
- Planner evidence also marks `FireWeaponWhenDeadBehaviorDerived.cpp` and
  `ModuleDataBuildFieldParseChained.cpp` mixed; their other rows stay with their
  assigned TUs.

Outstanding checks for Sol: `code_identity_gate --staged` reports one shadow
`alternatename (unreferenced)` finding for
`/alternatename:_vtbl_00BF2558=??_7WeaponSetUpgradeModuleData@@6B@`; the staged
data check reports two shadow `wrong-name` findings at `0x00A03EAC` and
`0x00A03EB0`. These were carried through the merge and were not retired here.
The final batch provider audit at base `7d964ea623f1951551f0a35e6709a549071b13e2`
found no selected-provider change or changed-unit unresolved blocker. The four
destination objects were current and passed strict byte receipts. The identity
and data findings remain for Sol; this merge did not retire them.
