# SpawnPointProductionExitUpdate mechanical trial blocker

`python3 tools/tu_skeleton.py --merge Code/GameEngine/Source/GameLogic/Object/Update/ProductionExitUpdate/SpawnPointProductionExitUpdate.cpp --dry-run` accepted no donors and reported: `blocked: no verified merge of two or more donors; the seed itself fails under every merged flag set: compile: reference\\shims\\bfmealloc\\stl\\_alloc.h(446) : error C2950: '_STL::allocator<char>' : cannot explicitly instantiate an explicit specialization`.

The unchanged donor failures were:

- `SpawnPointProductionExitUpdate.cpp`: `compile: reference\\shims\\bfmealloc\\stl\\_alloc.h(446) : error C2950: '_STL::allocator<char>' : cannot explicitly instantiate an explicit specialization`.
- `SpawnPointInitializeBonePositions.cpp`: `compile: .../.SpawnPointProductionExitUpdate.e6a6d32f76280350.tu_skeleton.cpp(185) : error C2511: 'SpawnPointProductionExitUpdate::SpawnPointProductionExitUpdate(Thing *,const ModuleData *)' : overloaded member function not found in 'SpawnPointP` (tool-truncated diagnostic).
- `SpawnPointExitObjectViaDoor.cpp`: `compile: .../.SpawnPointProductionExitUpdate.d4934d4c752d985e.tu_skeleton.cpp(193) : error C2039: 'exitObjectViaDoor' : is not a member of 'SpawnPointProductionExitUpdate' | ...` (tool-truncated diagnostic).
- `SpawnPointRevalidateOccupiers.cpp`: `compile: .../.SpawnPointProductionExitUpdate.6d0f8b45f5d05aba.tu_skeleton.cpp(154) : error C2039: 'revalidateOccupiers' : is not a member of 'SpawnPointProductionExitUpdate' | ...` (tool-truncated diagnostic).

The plan also refused `Code/GameEngine/Source/GameLogic/Object/Update/SpawnPointProductionExitUpdatePoolKey.cpp` with the exact reason `keyed in a protected path-keyed register (needs a Verifier-Change commit)`. No source or ledger changes were applied for this TU. Sol's header/flag and protected-register prerequisites must be resolved before another trial.
