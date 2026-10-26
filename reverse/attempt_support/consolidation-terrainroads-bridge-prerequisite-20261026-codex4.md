# TerrainRoads newBridge prerequisite trial, 2026-10-26

Allocated GameClient destination `Terrain/TerrainRoads.cpp`: current runner
`--check-tu` exited 0; the scoped Terrain planner and normal routing were read.
The plan has 27 approved rows across six clean files. Same-spelling planner
alternatives point to TerrainRoads.cpp, but remain hints with stale-map,
macro/internal-linkage, include and unledgered-definition qualifications.
No map, row owner or protected register was edited.

The baseline normal dry run accepted nothing: the subsystem shim is lifted
before Bool, the TerrainRoadType constructor loses its opaque member names,
the destructor fails bytes, and newBridge loses collection/type declarations.
Investigated only the seed and TerrainRoadCollectionNewBridge.cpp after claiming
both files plus a proposed private header and this handoff. No outside donor was
changed or claimed. Source-scope claims cover this prerequisite trial.

Trial: combine the seed's TerrainRoadType declarations with the bridge donor's
extra getters/setters and use the donor's four-byte OpaqueRefElement4 sound
records at +0x64/+0xD4. The seed already assigned these records through casts;
remove those casts after making the members typed. Retain the seed's field
tables and ID counter definitions and add the existing newBridge declaration.
Tried the collection declaration first in the private header, then visibly in
both source files so the composer could inspect its members.

Both variants preserve the standalone coverage. Official `./build.sh` on both
files passes 32/32 rows, 18 literals and two imports, including the parent-bound
EH funclets. The scoped frozen checks pass (the seed's existing note remains:
31 matched rows and one unclaimed definition). `allowed_symbols.py --source`
reports 145 references: 121 owner, 18 EH, six aliases, zero wrong bindings.
The initial shared-header variant's standalone code definitions and undefined
references compare identical with the original COFF snapshots. These are
existing matched bytes, not a recovery or composition proof.

The normal merge still refuses its final accepted-set re-verification. With
collection declarations visible, it reports:

```
accepted: []
rejected: TerrainRoadCollection.cpp: C2600 constructor must be declared first
          Rva002DAC58Dtor.cpp: C2600 destructor must be declared first
          TerrainRoadType.cpp: C2065 m_08 / m_0C undeclared
blocked: the accepted donors did not re-verify
         .TerrainRoads.578da2c006b724e3.tu_skeleton.cpp(196):
         error C2600: TerrainRoadCollection::TerrainRoadCollection:
         cannot define a compiler-generated special member function
```

No final composition/provider comparison is available, so this does not clear
the prerequisite. The unexpected constructor diagnostic after its donor was
rejected warrants a scoped composer investigation; it is not yet a proven
false reject. Do not repeat the unchanged trial or infer merge safety from the
standalone build. Recorded the blocked verdict at 0x002DB64E with re_log.py.
Restored both source files from the pre-trial snapshots and removed only the
new trial header. No source edit, merge, file reduction, debt retirement or
recovered C++ bytes remains. Release all four file claims after recording this
blocked handoff; no RVA claim was acquired.

Local receipts and preparation copies: `build/codex4-terrainroads/`, including
`trial-TerrainRoads.cpp`, `trial-TerrainRoadCollectionNewBridge.cpp`,
`trial-TerrainRoadView.h`; normal reports
`build/codex4-terrainroads-trial-{before,after,final,visible-collection}.txt`.
The publish audit includes both previously committed prerequisites plus this
log/handoff: no source path moves, deletes or renames, no path consumers to
repoint, and all original EA strings and debt owners remain intact.
