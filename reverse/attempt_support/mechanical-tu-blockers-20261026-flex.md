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
