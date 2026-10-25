# FlammableUpdate frame-view prerequisite, 2026-10-25

The scoped GameLogic planner and current in-memory TU plan approve the seed and
the eligible fragments listed below. The preceding diagnostic repair exposed a
seed C2143/C2059: composition hoists the TheGameLogic macro above the real global's
extern declaration. The seed file scope was claimed before editing.

Remove that macro and cast the existing GameLogic pointer to the existing
FlammableGameLogic view at the frame read. The +0x40 field, global declaration,
compiler flags and expressions otherwise remain unchanged. This introduces no
second global symbol and makes no new layout or donor-identity assertion.

Official ./build.sh passes the seed's three rows (117 retail bytes), including
strings, floats and imports. Declared-unmatched passes before and after, with the
same four existing marked definitions. The ordinary supported merge dry run now
accepts six rows (215 retail bytes) from:

- GameLogic/Object/Update/FlammableUpdate.cpp
- Libraries/Source/WWVegas/WWLib/StlSweepW5Rva0048C84C.cpp
- Libraries/Source/WWVegas/WWLib/StlSweepW6Rva0048C872.cpp
- GameLogic/Object/Update/Rva0048C8C6Ctor.cpp

Leave this now-compatible merge for Luna; no source was moved or removed here.
The remaining failures are distinct: Xfer/AudioManager redefinitions; duplicate
doAflameDamage body; missing rva0048C7BF receiver vocabulary; missing OS_A and
rva0048C8F9 in the accumulate fragment; duplicate STL random_access_iterator_tag
in CameraMarkerVecErase. Mixed and protected donors remain refused. Exact local
trial: build/codex-flammable-cast/dry-run.txt. Do not repeat the failed donors
until their declaration/body prerequisites change.

The pending batch since 5bf1ba9fe4 plus this staged edit has no source path moves;
active tools, hooks, workflows, includes, build inputs and registries need no
repointing. Upstream-only path changes in the divergent tip comparison are not
outgoing moves (confirmed with the merge-base diff and outgoing commit list).
No merge, file reduction, debt retirement, new hatch or recovered C++ bytes.
Keep the seed file claim until publication, then release it.
