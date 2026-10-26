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

## Flex seat 4/5 follow-up

- `RiderChangeContain.cpp`: unchanged merge accepted no donors. The ctor
  requires a `TransportContain` default constructor; pool key is already
  defined; Xfer has an `Xfer` redefinition/`Version1` issue; several module
  data and behavior donors hit duplicate `AsciiString` declarations; the
  parse donor triggers an MSVC internal compiler error; `RemoveFirst` needs
  inaccessible `Module::m_moduleData`; `Rva047E59EKill.cpp` lacks
  `Rva047E59EDamage8`. No edits or claims were made.
- `UnpauseSpecialPowerUpgrade.cpp`: the merge trial accepted its pool key,
  module-data ctor and upgrade-name-ref donors and byte-verified all four
  rows. The two remaining donors need `getModuleNameKey` declarations. Staged
  identity audit found a new unreferenced `/alternatename` for
  `_vtbl_00BF2558`; `repair_queue.py retire data` refused two wrong-name local
  static keys at `0x00A03E68` and `0x00A03E64`. The trial was restored and
  claims released for Sol's identity review.
- `AIUnitUpgrader.cpp`: the accepted destructor donor byte-verified six rows,
  but staged identity audit found the destructor's binding at `0x00506B28`
  collides with the existing `Rva00506B28DwordImmSetter::apply` owner. The
  trial was restored and claims released.
- `HealContain.cpp`: merged the accepted module-data parse donor; pool-key and
  Xfer donors still need member declarations.
- `ProjectileStreamUpdate.cpp`: merged the accepted `Rva0033EF86.cpp`; ctor,
  pool-key, Xfer and `getAllPoints` donors remain blocked by missing declarations
  or duplicate declarations.
- `DynamicShroudClearingRangeUpdate.cpp`: merged accepted animate-grid-decals
  and Xfer donors. Ctor, pool key, update and module-data ctor still require
  declaration or special-member work.

Publication handoff: the publisher stopped once with `Cannot rebase onto multiple
branches`. A subsequent explicit `git pull --rebase origin master` fetched
`5db17fb47684656adf2563faf60b3c9e4872f069` and rebased the complete 14-commit
pending batch cleanly. No merge conflict or source change resulted; publication
is still pending.

## Flex seat follow-up — Luna session 2026-10-26

Two tool-accepted unchanged merges landed in the verified staging set:

- `MoneyCrateCollidePoolKey.cpp` merged into `CrateCollide/MoneyCrateCollide.cpp`;
  four matched rows were byte-verified. The ctor remains rejected: C2511,
  `MoneyCrateCollide(Thing *, const ModuleData *)` is absent from the target
  class view. The merge tool transferred its data-check and data-ledger keys;
  converged data check passes, while shadow data check still reports two
  wrong-name local-static keys at `0x00A04058` and `0x00A04054`.
- `SupplyCenterProductionExitUpdateExitDoor.cpp` merged into
  `ProductionExitUpdate/SupplyCenterProductionExitUpdate.cpp`; three matched
  rows were byte-verified. The pool key remains rejected because
  `getModuleNameKey` is absent from the class view (C2039); the behavior ctor
  lacks the `UpdateModule` base declaration (C2504).

Both destination builds and `find_declared_unmatched.py` pass. The staged
TU-ownership check, `repair_queue.py verify-removed`, and converged data check
pass. Staged code-identity shadow audit reports two new divergent-definition
findings (`??0Vector3@@QAE@ABV0@@Z` and `??AMatrix3D@@QBEABVVector4@@H@Z`);
no identity key was retired.

Further allocated unchanged trials accepted no donors and remain for a source
prerequisite pass: `StealthUpgrade.cpp` (ctor overload absent; pool key and
upgrade methods absent), `DockUpdate.cpp` (member declarations/fields absent,
duplicate `ObjectID`/`GameLogic` definitions, and special-member destructor
cannot be declared), `FireWeaponCollide.cpp` (`CollideModule` base and several
member declarations absent), `HealContain.cpp` (`getModuleNameKey` and `xfer`
absent), and `TunnelContain.cpp` (ctor/member declarations and destructor
special member absent). For `RiderChangeContain.cpp`, no donor merged; its
`ModuleNameGetters.cpp` carve matches alone but donor composition fails with
C2953 `StringBase` template redefinition. The `DockUpdate.cpp` dry run was
allowed to finish; no second compiler trial was started.

## Luna shard continuation — W3DPropDraw and Keyboard

- `W3DPropDraw.cpp`: accepted the unchanged `W3DPropDrawModuleDataDtor.cpp`
  donor and byte-verified five rows including the three EH rows. Its staged TU,
  data and ownership checks pass. Shadow identity reports one new divergent
  `??1ModuleData@@UAE@XZ` definition. The pool-key row lacks its class member
  declaration (C2039), the module-data ctor initializes absent member
  `m_distanceFog` (C2614), and the react donor duplicates `Coord3D` (C2011).
- `Keyboard.cpp`: dry-run accepted its three donors plus the TU seed and
  byte-verified 15 rows; `KeyboardInitUpdate.cpp` loses a member declaration
  and duplicates `KEY_STATE_DOWN`, while `KeyboardRva00232AE8.cpp` and
  `rva00232B7BRva00232B7BFarm.cpp` conflict on `_STL::allocator`. Applying the
  accepted donors was refused before writing because `hatch_counters.py`
  requires the prior W3D merge's modified files to be committed first. Retry
  after that commit; no Keyboard source or ledger change was applied.
- `MaxHealthUpgrade.cpp`: accepted no donors. Its module and implementation
  donors both require an undeclared `getModuleNameKey` member (C2039).
