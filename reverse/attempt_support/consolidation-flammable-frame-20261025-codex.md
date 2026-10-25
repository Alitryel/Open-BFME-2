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

## Applied consolidation update (2026-10-25)

The scoped merge is now applied. `tu_skeleton.py --merge` accepted the seed and
three unchanged donors, moving six matched rows into FlammableUpdate.cpp and
removing these fragments:

- GameLogic/Object/Update/Rva0048C8C6Ctor.cpp
- Libraries/Source/WWVegas/WWLib/StlSweepW5Rva0048C84C.cpp
- Libraries/Source/WWVegas/WWLib/StlSweepW6Rva0048C872.cpp

Verification: `./build.sh FlammableUpdate.cpp` passed all 6/6 matched rows;
`find_declared_unmatched.py` passed with 5 already-unclaimed definitions;
`tu_ownership.py --staged --shadow`, `code_identity_gate.py --staged` (6 rows,
0 new findings), `data_check.py --staged` (0 findings), `check_csv.py`, and
`git diff --cached --check` passed. The planner snapshot was regenerated and
`--check build/consolidation` passed (5,447 source files). No identity or data
keys were retired. Existing FlammableUpdatePoolKey data debt and the OneRing
Coord3D header queue item remain for Sol; the protected Flammable donors remain
unmoved.

Rejected donor evidence for Sol: `FlammableUpdateXfer.cpp` fails with C2011
`Xfer` redefinition at `BfmeXfer.h(19)` and C2011 `AudioManager` redefinition
in the composed TU; `FlammableUpdate_doAflameDamage.cpp` fails C2084 (duplicate
`FlammableUpdate::doAflameDamage` body); `FlammableUpdateRva0048C7BF.cpp` fails
C2039 (`rva0048C7BF` is not a member of `FlammableUpdate`); `Rva0048CACCAccumulate.cpp`
fails C2065 (`OS_A` undeclared) and C2039 (`rva0048C8F9` is not a member);
`CameraMarkerVecErase.cpp` fails C2011 (`_STL::random_access_iterator_tag`
redefinition); `FlammableUpdateModuleDataDtor.cpp` is rejected on bytes; and
`FlammableUpdateModuleDataCtor.cpp` fails C2614 (`m_damageType` is not a member
of `FlammableUpdateModuleData`). Protected-register and mixed donors were left
untouched. The separate AssaultTransport dry run accepted no donors; its
unmodified rejections include C2039 `Rva0048F365Helper` missing from the class,
C2011 `Xfer` redefinition at `BfmeXfer.h(19)`, and C2065 `m_object08`
undeclared.

Tooling compatibility audit covered the complete outgoing path range
`origin/master..HEAD` plus staged moves: BfmeConv987.cpp to
OneRingPenaltyUpdate.cpp (inherited, previously audited) and the three absorbed
Flammable fragments above. Searches of tools, hooks, workflows, source/header
includes, build inputs, registries and docs found no active path consumer needing
a manual repoint. `reverse/link_status.csv`, `reverse/re_attempts.log`, source
provenance comments and attempt evidence retain historical old-path references;
these were preserved. `reverse/header_queue.tsv` still has the existing OneRing
Coord3D item, and `reverse/ms_header_queue.tsv` has no entries for these paths.
