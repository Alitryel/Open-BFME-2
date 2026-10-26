# SpawnPointProductionExitUpdate prerequisite survey, 2026-10-26

Seat codex, allocated family A shard 0/2. Reviewed the allocated destination
`Code/GameEngine/Source/GameLogic/Object/Update/ProductionExitUpdate/SpawnPointProductionExitUpdate.cpp`,
the 2026-10-25 blocked handoff, current source bodies and a fresh scoped planner.
The planner's original-path catalogue and same-name donor leads are placement
hints, not target layout proof or merge approval. Current upstream `--plan`
approves ten rows across seven source files, including two mixed donors, with
no refused placements. The older handoff's thirteen-row count is not current.

This is not an isolated allocator/include repair. The seed retains the Zero
Hour SpawnPoint/Update/Exit class hierarchy. Target evidence in the existing
matched bone initializer instead accesses the BFME 2 fields at module +0x24
and +0x28, and the exit body receives its interface at module +0x20. The previous
trial also encounters allocator<char> specialization C2950. A coherent receiver,
header and provider reconciliation must preserve those target accesses and
constructor/vtable bindings together. This survey does not establish the full
layout or identify an external donor as BFME 2 source.

Commands/evidence:

```
python3 tools/name_lane.py consolidate --under Code/GameEngine/Source/GameLogic/Object/Update/ProductionExitUpdate/
python3 tools/tu_skeleton.py --plan Code/GameEngine/Source/GameLogic/Object/Update/ProductionExitUpdate/SpawnPointProductionExitUpdate.cpp
python3 tools/find_declared_unmatched.py Code/GameEngine/Source/GameLogic/Object/Update/ProductionExitUpdate/SpawnPointProductionExitUpdate.cpp
```

Local reports: `build/codex-spawnpoint-planner-20261026.txt` and
`build/codex-spawnpoint-plan-20261026.txt`. The frozen-file checker accepts the
seed's existing one matched body and four pre-existing unclaimed-body markers;
no marker was added. No unchanged dry-run was repeated, no source was edited,
and no merge or debt retirement occurred. Recorded a blocked prerequisite
survey for reserveDoorForExit (0x004A3F3B, 70 bytes) through `re_log.py`.
Released all four claimed files (seed, bone initializer, bone revalidation and
exit donor). This target remains available for a larger ABI prerequisite;
there is no newly demonstrated unblock or recovered byte claim here.
