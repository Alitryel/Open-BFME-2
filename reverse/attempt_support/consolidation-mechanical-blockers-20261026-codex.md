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

No rejected candidate was applied or claimed. These prerequisites require the
Sol lane; do not repeat unchanged dry runs. No identity debt retirement or
recovered bytes are claimed.
