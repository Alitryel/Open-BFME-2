# RebuildHoleExposeDie mechanical consolidation blocked (2026-10-25)

Allocated destination: `Code/GameEngine/Source/GameLogic/Object/Die/RebuildHoleExposeDie.cpp` (shard 0/5, unheld). The planner was regenerated under `Code/GameEngine/Source/GameLogic/Object/Die/`; its snapshot check passed. The plan has 11 approved rows, 4 mixed files, no refused files, and 4 candidate donors. The dry run accepted none and reported `blocked: no verified merge of two or more donors`; no source or ledger changes were applied.

Exact dry-run rejections (tool output is truncated after its diagnostic limit):

- `RebuildHoleExposeDieXfer.cpp`: `BfmeXfer.h(37) : error C2061: syntax error : identifier 'Snapshot' | BfmeXfer.h(51) : error C2061: syntax error : id...`.
- `RebuildHoleExposeDieOnDie.cpp`: `RebuildHoleExposeDie.<hash>.tu_skeleton.cpp(348) : error C2511: 'RebuildHoleExposeDie::RebuildHoleExposeDie(Thing *,const ModuleData *)' : overloaded member function not found in 'RebuildHoleExposeDie' | ...`.
- `RebuildHoleExposeDieModuleDataDtor.cpp`: dry-run rejection `bytes`.

The mixed donors were not changed. Sol must reconcile the Xfer and constructor declarations and resolve the destructor byte mismatch before another mechanical trial; do not repeat this dry run without changed prerequisites.
