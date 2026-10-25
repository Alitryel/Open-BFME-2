# AptValueGCAllocator consolidation blocked (2026-10-25)

Destination: `Code/Libraries/Source/Apt/AptValueGCAllocator.cpp`.

The TU passed the allocator check. I refreshed and checked the scoped consolidation report, read the TU plan, and ran one merge dry run. Of five approved rows, no donor was accepted. `AptValueGC_PoolManager_CleanPool.cpp` fails composition with C2039 (`CleanPool` is not a member of `AptValueGC_PoolManager`) and C3861 (`GetFirstAptValue` identifier not found). `Rva006D29E0Cluster.cpp` is a protected path-keyed entry. This needs declaration/register work outside this lane; no merge or claims were made.
