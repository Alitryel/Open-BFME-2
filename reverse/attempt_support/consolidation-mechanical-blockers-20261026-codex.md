# Consolidation mechanical trial handoff — 2026-10-26

Shard 2/5. `StringPool.cpp` was the only accepted merge: two unchanged donors,
two matched rows, all preserved; net source-file count reduced by one. The
commit is `d0d7d4482b`, awaiting the shared publisher with the inherited
`version.cpp` merge. Build, unmatched-definition, EH, identity, data,
converged-data, TU ownership, CSV, case-collision and pre-commit gates passed.
The publisher hook still needs to report selected-provider and consumer-binding
results for the outgoing range.

Read-only rejected trials (no claims or source edits):

- `W3DWaterTracks.cpp`: zero accepted donors. Current diagnostics match the
  existing detailed blocker in `consolidation-device-20261025.md`: missing
  `WaterTracksObj` members, `RealRange` redefinition, and a compiler-generated
  constructor conflict. Three mixed donors stayed untouched.
- `AssistedTargetingUpdate.cpp`: zero accepted donors. Pool-key donor fails
  C2039 (`rva000486E31` is not a member of `AssistedTargetingUpdate`); ctor
  donor fails C2065 (`m_vtable` undeclared); feedback-laser donor fails C2011
  (`Coord3D` redefinition at `Coord3D.h:7`). Three mixed donors stayed
  untouched.
- `OCLSpecialPower.cpp`: zero accepted donors. Pool-key donor fails C2039
  (`rva0004C3147` is not a member of `OCLSpecialPower`); find donor fails
  C1083 (cannot open `Coord3D.h`); module-data ctor fails C2908 (the
  `_STL::vector<_Tp>::~vector(void)` specialization was already instantiated);
  at-location donor fails C1083 (cannot open `Lib/Coord3D.h`); module-data dtor
  fails byte verification. Six mixed donors stayed untouched.

- Follow-up split trial for `OCLSpecialPower.cpp`: `VslotSmallBodiesF.cpp`
  carved row `0x004C31EC` and the merge verifier accepted it unchanged; both
  sides built and `find_declared_unmatched.py` passed. The staged composition
  failed `git diff --cached --check` on newly added whitespace-only lines at
  OCLSpecialPower.cpp:266, :353 and :369, introduced where the tool rewrote
  existing closing-brace whitespace. Per the mechanical lane, the trial was
  restored without editing the TU body; file and RVA claims were released.
- `AptString.cpp`: dry-run accepted unchanged donors
  `Rva006D7090Factory.cpp`, `AptStringCharCodeAt.cpp`, and
  `AptStringObjectMemberLookup.cpp`; applying was skipped because claims for
  the destination and all moved rows are held by `halilkkaya-tu-b`.

No rejected candidate was applied or claimed. These prerequisites require the
Sol lane; do not repeat unchanged dry runs. No identity debt retirement or
recovered bytes are claimed.

## WeaponSetUpgrade accepted composition, 2026-10-26

Shard allocation and the scoped planner currency check passed for
`Code/GameEngine/Source/GameLogic/Object/Upgrade/WeaponSetUpgrade.cpp`.
The split trial carved `0x004B56F6` from
`ModuleDataBuildFieldParseChained.cpp`; it moved the sole initialized
`BfmeWeaponSetUpgradeFields` definition and preserved 62 residual rows. The
merge accepted that split and the unchanged
`WeaponSetUpgradePoolKey.cpp` donor (`0x004B56B1`). The separate constructor
donor remained rejected, C2511: its constructor signature is not declared in
`WeaponSetUpgrade`.

The split-side build passed for both files, then the merged TU build passed
3/3 matched functions and its byte-verified data row. Both declaration scans,
`check_csv.py`, and `git diff --cached --check` passed. The staged code identity
gate found zero new findings. `data_check.py --staged` reported two shadow
`wrong-name` findings for the static pool-key locals at `0x00A03E7C` and
`0x00A03E80`; the existing pool-key identity debt remains with Sol, and no
identity key was retired. The report for the prior split-provider defect
documents the duplicate table fix and its object-level provider comparison.

The source path audit found no active references to the absorbed pool-key
filename in tools, hooks, workflows, build inputs, or registries; source
provenance comments and historical ledger evidence retain the old spelling.
The current source batch still needs the pre-push link-batch report for
selected providers, lost bytes, input freshness, and affected consumer
bindings. No C++ bytes were recovered and the new destination plus absorbed
donor leaves the source-file count unchanged for this TU.

## Additional allocated trials, 2026-10-26 (Shard 2/5)

- `GarrisonContain.cpp`: allocator approved; scoped planner currency check and
  `--plan` completed. Dry run accepted zero unchanged donors. Compile blockers
  include `Coord3D` redefinitions (`Coord3D.h:7`), private/protected member
  access (`ObjectModule::m_object`, `GarrisonContain::validateRallyPoint`,
  `Team::m_id`), missing generated members (`GarrisonContain::rva0047801C`,
  `rva004787B0`), and duplicate `Xfer`, `ObjectID`, `AsciiString`, `GameLogic`
  or `_STL` declarations. All five mixed donors were left untouched.
- `TerrainRoads.cpp`: allocator approved; scoped planner currency check and
  `--plan` completed. Dry run accepted zero unchanged donors. Two donors fail
  on the existing `SubsystemInterface` parse errors in
  `reference/shims/subsystem_bfme2/subsystem_interface.h:36`; another needs
  undeclared `TerrainRoadType::m_08`/`m_0C` and further members; one donor has a
  byte mismatch; another refers to absent `TerrainRoadCollection` declarations.
  No source, ledger, or claims were changed.

## Squad compact merge completed, 2026-10-26 (Shard 2/5)

`Squad.cpp` passed allocation and scoped planner checks. The approved unchanged
`Gen0018BC70BfmeCompact.cpp` donor merged into Squad; the tool preserved four
matched bodies and repointed the 70-byte body in `functions.csv` and `tu_map.csv`.
The other two donors remain rejected: both hit duplicate `_STL::allocator`
template/specialization errors in `reference/shims/bfmealloc/stl/_alloc.h`.
The mixed `SquadGetAllObjectsAndRemoveDead.cpp` carve was inspected and refused
because a namespace/extern-C block defines content; it remains untouched.

Verification: `./build.sh Squad.cpp` passed 4/4 rows, its declaration scan and
`check_csv.py` passed, staged code identity reported zero new findings, staged
data identity reported zero findings, and the TU ownership check passed. No
identity, data or header-queue keys referenced the absorbed path. The path audit
found only tool-repointed owner entries (`functions.csv`, `tu_map.csv`), the
stale census row in `reverse/link_status.csv` (retained as historical measurement),
and historical attempt-support notes; tools, hooks, workflows, includes, build
inputs and active registries have no hard-coded consumer for the donor path.
The pre-push audit still must compare selected providers and affected consumers
for this outgoing source change. This merge reduces Code source files by one;
matched coverage is unchanged and no identity debt is claimed retired.
