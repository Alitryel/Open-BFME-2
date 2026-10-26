# GameMemory mechanical trial, 2026-10-26

The allocated shard 1/5 TU `Code/GameEngine/Source/Common/System/GameMemory.cpp`
passed `--check-tu`. Its fresh plan listed 28 approved rows from five donors.
The merge dry run accepted the seed plus these three unchanged donors (three
moved rows):

- `Rva00030730Init.cpp`, RVA `0x00030730`;
- `stlport_byte_allocator.cpp`, RVA `0x000307F0`;
- `GameMemoryFree.cpp`, RVA `0x00030830`.

The dry run rejected `Code/GameEngine/Source/Common/Rva000308E0AddHeap.cpp`
with `C2011: 'MemoryPool::HeapTable': 'struct' type redefinition`; left that
donor untouched. The applied trial passed `./build.sh
Code/GameEngine/Source/Common/System/GameMemory.cpp` (5/5 rows, six data rows)
and `find_declared_unmatched.py`.

The complete path audit found the active source inventory at
`docs/doxygen/pages/subsystems/memory.md` still lists the soon-to-be-removed
`GameMemoryFree.cpp` and `stlport_byte_allocator.cpp` paths. This needs a manual
registry edit outside the mechanical seat. The trial was reverted without
changing inherited work; no merge is published. Sol should update that source
inventory, rerun the planner and dry run, claim the destination/donors/RVAs,
then repeat the full composition and provider checks before applying.

Other old-path mentions found by the audit are source provenance comments and
historical evidence; classify them during Sol's path audit. The provider audit
for this trial was not run because the active registry blocker already prevents
publishing it.
