# StatusBitsUpgrade consolidation claim held (2026-10-25)

Allocated destination: `Code/GameEngine/Source/GameLogic/Object/Upgrade/StatusBitsUpgrade.cpp` (shard 0/5, reported unheld at allocation). The scoped planner snapshot was regenerated and passed `name_lane.py consolidate --check build/consolidation`. Dry run accepted unchanged `StatusBitsUpgradeUpgradeImplementation.cpp` (2 rows); it rejected the constructor donor for `bytes`, and refused the pool-key donor because it is in a protected path-keyed register.

Applying the accepted merge refused with the exact error `blocked: held by another worker: file:Code/GameEngine/Source/GameLogic/Object/Upgrade/StatusBitsUpgrade.cpp`. The merge tool released any claims it had acquired; no source or ledger changes were applied. Reassess allocation after the competing claim expires; do not retry while held.
