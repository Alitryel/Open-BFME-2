# Consolidation handoff: SpawnPointProductionExitUpdate.cpp

Shard 0/5 allocation and TU check passed. Scoped planner/check passed. The 10-row destination has 7 clean donor files and 2 mixed donors. Merge dry run accepted none; rejected clean donors unchanged for these exact compile blockers:

- `SpawnPointProductionExitUpdateDtor.cpp`: `Coord3DCtorView.h(21): error C2011: 'Coord3D' : 'struct' type redefinition`.
- `SpawnPointProductionExitUpdatePoolKey.cpp`: `error C2084: function 'NameKeyType SpawnPointProductionExitUpdate::getModuleNameKey(void) const' already has a body`.
- `SpawnPointProductionExitUpdateCtor.cpp`: `Coord3DCtorView.h(21): error C2011: 'Coord3D' : 'struct' type redefinition`.
- `SpawnPointInitializeBonePositions.cpp`: `error C2365: 'MAX_SPAWN_POINTS' : redefinition; previous definition was a 'enumerator'`.
- `SpawnPointExitObjectViaDoor.cpp`: `Coord3D.h(7): error C2011: 'Coord3D' : 'struct' type redefinition`.
- `SpawnPointRevalidateOccupiers.cpp`: `error C2065: 'INVALID_OBJECT_ID' : undeclared identifier`.

Mixed `ModuleNameGetters.cpp` has candidate 0x004A3B8F; split dry run reached the merge verifier but rejected it with `error C2011: 'SpawnPointProductionExitUpdate' : 'class' type redefinition`. Mixed `VslotSmallBodiesY.cpp` has candidate 0x004A3B95; split dry run refuses because `hatch_counters rule 3`: a copied helper or datum carries a hatch. No source, ledger, or claim edits were made for this TU. Declaration/class reconciliation and hatch work belong to Sol.
