# FloatUpdate mechanical merge blockers (2026-10-26)

Allocator shard 4/5 served `Code/GameEngine/Source/GameLogic/Object/Update/FloatUpdate.cpp`; `--check-tu` exits 0. The scoped `name_lane.py consolidate` snapshot is current (141 groups, no compile-trial groups). The TU plan has 7 approved rows and four mixed donor files. The unchanged merge dry-run accepted no donors and refused no rows, so no merge was applied.

Two unchanged donors fail compilation and need a separate source repair before a future consolidation trial:

- `Code/GameEngine/Source/GameLogic/Object/Update/FloatUpdatePoolKey.cpp`: `FloatUpdate.cpp(30) : error C2039: 'rva00048D761' : is not a member of 'FloatUpdate'`.
- `Code/GameEngine/Source/GameLogic/Object/Update/FloatUpdateModuleDataCtor.cpp`: `FloatUpdate.cpp(49) : error C2065: 'm_vtable' : undeclared identifier`.

The errors reproduced identically after rebasing onto current `origin/master` (`8aa94fb8e4` plus the pending verified BFME 1 pointer commit). No source or ledger repair was attempted in the mechanical lane. Sol owns declaration/layout repair; retry only after that prerequisite changes.
