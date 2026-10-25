# AITNGuard mechanical consolidation blocked (2026-10-25)

Allocated destination: `Code/GameEngine/Source/GameLogic/AI/AITNGuard.cpp` (shard 0/5, unheld).

The current consolidation plan lists 33 approved rows, 6 candidate donors, 5 mixed files, and 4 protected-path refusals. The report was regenerated for `Code/GameEngine/Source/GameLogic/AI/` and `name_lane.py consolidate --check build/consolidation` passed. `tu_skeleton.py --merge Code/GameEngine/Source/GameLogic/AI/AITNGuard.cpp --dry-run` accepted no donors and reported `blocked: no verified merge of two or more donors`; no source or ledger changes were applied.

Exact dry-run diagnostics:

- Seed `AITNGuard.cpp`: `GameLogicObjectLookupView.h(37) : error C2143: syntax error : missing ',' before '&' | GameLogicObjectLookupView.h(113) : error C2061: syntax error : identifier` (seed fails under every merged flag set).
- `AITNGuardXfer.cpp`: `BfmeXfer.h(37) : error C2061: syntax error : identifier 'Snapshot' | BfmeXfer.h(48) : error C2061: syntax error : identifier 'AsciiString'`.
- `AITNGuardHasAttackedMeCondition.cpp`: `AITNGuard.<hash>.tu_skeleton.cpp(304) : error C2039: 'getBodyModule' : is not a member of 'Object' | ... (320) : error C2039: 'getRelationship' : is not a member of 'Object' | Co` (tool output truncated).
- `AITNGuardReturnStateOnEnter.cpp`: `AITNGuard.<hash>.tu_skeleton.cpp(447) : error C2039: 'getPosition' : is not a member of 'Object' | ... error C2227: left of '->x' must point to class/struct/union | Code\` (tool output truncated).
- `Rva00545D7ECtor.cpp`: dry-run rejection `bytes`.

No donor was accepted. The four refused files (`AITNGuardAttackAggressorStateCtor.cpp`, `AITNGuardInnerStateCtor.cpp`, `AITNGuardMachineCtor.cpp`, `AITNGuardStates.cpp`) are keyed in a protected path-keyed register and need a Verifier-Change commit to move. This is for Sol's declaration/view and byte investigation; no retries without changed prerequisites.
