# W3DTreeDraw mechanical consolidation blocked (2026-10-25)

Allocated destination: `Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DTreeDraw.cpp` (shard 0/5, unheld). The planner was regenerated under `Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/`; snapshot check passed. The plan has 9 approved rows, 3 donors, 2 mixed files and 2 protected-path refusals. Dry run accepted no donors and reported `blocked: no verified merge of two or more donors`; no source or ledger changes were applied.

Exact dry-run rejections (the compile diagnostic is truncated by the tool):

- `W3DTreeDrawModuleNameKey.cpp`: `W3DTreeDraw.<hash>.tu_skeleton.cpp(90) : error C2039: 'getModuleNameKey' : is not a member of 'W3DTreeDraw' | ... (91) :`.
- `W3DTreeDrawModuleDataCtor.cpp`: dry-run rejection `bytes`.

The module-data ctorG7 and field-parse donors are refused because they are keyed in protected path-keyed registers. Sol must resolve the class declaration and ctor byte mismatch before retrying; do not repeat the unchanged dry run.
