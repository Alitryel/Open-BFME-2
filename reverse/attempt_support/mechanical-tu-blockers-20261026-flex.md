# Flex-shard unchanged consolidation blockers — 2026-10-26

## BridgeBehavior

The allocated `BridgeBehavior.cpp` plan approved 41 rows from 21 donors, with
ten mixed files and one explicitly refused row. The unchanged merge trial
accepted no donors. The refused row at `0x004565BD` and two other bodies in
`BridgeBehaviorAreaEffects.cpp` expand `__FILE__` into verified bytes. Donor
compile failures were:

- `BridgeBehaviorPoolKey.cpp`, `BridgeBehaviorCreateScaffolding.cpp`,
  `BridgeBehaviorCtor.cpp`, `BridgeBehaviorDtor.cpp`,
  `BridgeBehaviorHandleObjectsOnBridgeOnDie.cpp`,
  `BridgeBehaviorListValueCopy.cpp`, `BridgeBehaviorOnBodyDamageStateChange.cpp`,
  `BridgeBehaviorParseTimeAndLocation.cpp`, and `BridgeBehaviorResolveFX.cpp`:
  lose matched rows under the carried `-G7 -arch:SSE` override.
- `BridgeBehaviorGetInterfaceFromObject.cpp`, `BridgeBehaviorIsScaffoldInMotion.cpp`,
  `BridgeBehaviorListOperations.cpp`, `BridgeBehaviorOnHealing.cpp`,
  `BridgeBehaviorParseOCL.cpp`, `BridgeBehaviorRemoveScaffolding.cpp`,
  `BridgeBehaviorRva00456725.cpp`, `BridgeBehaviorRva0045674D.cpp`,
  `BridgeBehaviorRva00456774.cpp`, `BridgeBehaviorSetScaffoldData.cpp`, and
  `Rva004581FDOnDie.cpp`: no baseline match.

Mixed split trials did not provide an applied merge. `DestroyInstances.cpp`
(`0x0045710A`) and `BridgeBehaviorListCleanup.cpp` (`0x00457441`) have no
definition spelling the target; module-data ctor and Xfer splits would grow a
hatch; module-data dtor and parse-FX splits are blocked by namespace/extern-C
definitions; field-parse split `0x00458268` fails on missing
`PhysicsBehaviorModuleData::m_fieldParse`; module-name getter and Vslot splits
fail with a duplicate `BridgeBehavior` declaration and undefined
`ChecklistUIItemMovieClip`, respectively. The `DispByteFieldGetters.cpp`
`0x004571F4` split trial compiles unchanged, but was not applied because the
remaining donor is 176 rows and no merge is unblocked. The observed compiler
errors and routing report are retained in the session output.

## MetaEvent

The allocated `MetaEvent.cpp` plan approved 11 rows from six donors and one
mixed source. The unchanged merge trial accepted no donor:

- `MetaMap.cpp`: `SubsystemInterface` redefinition plus missing `m_head`.
- `MetaMapFindGameMessageMetaType.cpp` and `parseDebugCommandMap.cpp`:
  `ICoord2D` redefinition in the donor reference headers.
- `MetaMapRecDtor.cpp`: `StringBase` template redefinition.
- `MetaMapParseMetaMap.cpp`: `parseMetaMap` and
  `findGameMessageMetaType` are not members of `MetaMap`.

The mixed `GameClientDrawableTOC.cpp` row at `0x001DB432` is inside a
namespace/extern-C block the split tool cannot carve. No trial changed source,
ledgers, claims, or routing.

## Additional allocated trials

- `HealContain.cpp`: its unchanged merge dry run accepted
  `HealContainModuleDataParse.cpp`, but the required accepted split donor
  `ConstIntGetters4.cpp` was held by another worker, so no part was applied.
  The `FlatMultiVptrDestructors.cpp` split for `0x00466B45` was blocked because
  a copied helper or datum would grow a hatch. My destination/donor/RVA claims
  were released; the other worker's claims were untouched.
- `MoneyCrateCollide.cpp`: unchanged merge accepted no donors. Its ctor donor
  fails with C2504 (`CrateCollide` base undefined); its pool-key donor fails
  with C2039 (`getModuleNameKey` not a member of `MoneyCrateCollide`).
- `W3DSnow.cpp`: unchanged merge accepted no donors. The constructor trial
  fails on undeclared `WeatherSetting`/`OVERRIDE`; getters, reset, blend-phase
  and state-transition trials fail on missing `W3DSnowManager` members/fields;
  render-sub-box and render trials lack `W3DSnowManager`; the game-client
  finish donor lacks its `SnowManager` base. The mixed render-as-quads split
  for `0x00093CC3` was rejected because the residual loses matched row
  `0x00083BD4`.
- `SupplyCenterProductionExitUpdate.cpp`: merge accepted no donors. The pool
  key has no declared `getModuleNameKey`; the ctor has undefined `UpdateModule`;
  the accepted-donor verification also fails on explicit instantiation of
  `_STL::allocator<char>`. Its mixed source has no rows approved for this TU.
- `StealthUpgrade.cpp`: its three-row constructor donor stopped compiling
  after the accepted split added a class view, and the pool-key and
  implementation donors still fail on undeclared members. The verified split
  of `0x004B532D` from `ModuleNameGetters3.cpp` was retained. It creates the
  previously absent `StealthUpgrade.cpp`, increasing the source-file count by
  one.

The PreorderCreate merge audit records two new shadow `wrong-name` findings
for its transferred local-static data keys (`0x00A03F90` and `0x00A03F94`).
The converged data check remains clean; neither key was claimed retired.
