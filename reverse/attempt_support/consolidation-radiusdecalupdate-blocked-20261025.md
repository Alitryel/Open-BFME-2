# RadiusDecalUpdate mechanical consolidation blocked (2026-10-25)

Allocated destination: `Code/GameEngine/Source/GameLogic/Object/Update/RadiusDecalUpdate.cpp` (shard 0/5, unheld). The planner was regenerated under `Code/GameEngine/Source/GameLogic/Object/Update/`; `name_lane.py consolidate --check build/consolidation` passed. The plan has 9 approved rows, 4 candidate donors, 1 mixed donor and 1 protected-path refusal. The dry run accepted no donors and reported `blocked: no verified merge of two or more donors`; no source or ledger changes were applied.

Exact dry-run rejections (tool output is truncated after its diagnostic limit):

- `RadiusDecalUpdateCtorThunk.cpp`: `RadiusDecalUpdate.<hash>.tu_skeleton.cpp(22) : error C2061: syntax error : identifier 'RadiusDecal' | ... (30) : error C2504: 'UpdateModule' : base ...`.
- `RadiusDecalUpdateUpdate.cpp`: `RadiusDecalUpdate.<hash>.tu_skeleton.cpp(15) : error C2061: syntax error : identifier 'RadiusDecal' | ... (21) : error C2143: syntax error : missing ...`.
- `RadiusDecalUpdateXfer.cpp`: `BfmeXfer.h(37) : error C2061: syntax error : identifier 'Snapshot' | BfmeXfer.h(48) : error C2061: syntax error : identifier ...`.

The refused pool-key donor, `RadiusDecalUpdatePoolKey.cpp`, is keyed in a protected path-keyed register and requires a Verifier-Change commit to move. Sol must address the missing type/base declarations before a new unchanged-donor trial; do not repeat this dry run without changed prerequisites.
