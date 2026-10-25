# DataChunk reader consolidation prerequisite

Scope: `Code/GameEngine/Source/Common/System/DataChunk.cpp`, following the
DataChunk blockers in `consolidation-common-20261025b.md`.

The existing seed lacked declarations for the already-rowed scalar reader and
chunk-label methods. The union composition strategies instead deferred the
class past `DataChunkInputEofMethod`, producing C2653. Declaring those
nonvirtual APIs in the seed lets the first-class composition strategy retain
its existing layout and member-pointer initializer.

Verification on 2026-10-25:

- `./build.sh Code/GameEngine/Source/Common/System/DataChunk.cpp`: 17/17 exact.
- `find_declared_unmatched.py` passed for the seed and all three inspected
  reader/name-lookup donors; it passed again for the edited seed.
- `tu_skeleton.py --merge Code/GameEngine/Source/Common/System/DataChunk.cpp
  --dry-run` now accepts `DataChunkInputReadScalars.cpp` and
  `DataChunkInputGetChunkLabel.cpp` together with the seed. Their four bodies
  total 151 retail bytes. The report is in the local ignored
  `build/datachunk-prerequisite-dryrun.txt`.
- `check_csv.py` and `git diff --check` passed.

No rows moved, files removed, new C++ bytes recovered, or identity debt retired.
The compatible donors are left for the mechanical consolidation seat. Rebuild
the planner snapshot before applying a merge; normal current routing and claims
still apply.

Remaining independent blockers in the dry run: `Mapping` field spellings in
`DataChunkTableOfContentsGetName.cpp`; missing output API/private-view agreement
for the ASCII, Unicode, name-key and dictionary writers. Mixed and protected
donors remain untouched. This declaration change does not resolve those
blockers.
