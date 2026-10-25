# OCLUpdate consolidation tool error (2026-10-25)

Allocated destination: `Code/GameEngine/Source/GameLogic/Object/Update/OCLUpdate.cpp` (shard 0/5, unheld). The planner snapshot was regenerated under `Code/GameEngine/Source/GameLogic/Object/Update/`, and `name_lane.py consolidate --check build/consolidation` passed. The plan had 9 approved rows, 5 candidate donors, 2 mixed files and no protected refusals.

Dry-run accepted the unchanged TU plus `Code/GameEngine/Source/Common/OCLUpdate_getRemainingFrames.cpp` (4 rows) and rejected other donors. The accepted donor has a `GameLogic` header-queue entry; the merge tool's path-keyed repoint preserved that entry under the destination TU.

Applying the accepted merge failed with:

```
FileNotFoundError: [Errno 2] No such file or directory: '/work2/Open-BFME-2/Code/GameEngine/Source/Common/OCLUpdate_getRemainingFrames.cpp'
```

At failure, `tu_skeleton.py` had staged deletion of the donor, generated destination changes, and repoints in `reverse/functions.csv`, `reverse/header_queue.tsv`, and `reverse/tu_map.csv`; the exception occurred while rereading the now-missing donor. I restored only these trial paths and released the destination, donor and `0x0049B303` claims. No consolidation source or ledger change remains. This is an unverified tool failure; investigate its write/read ordering before retrying this TU.
