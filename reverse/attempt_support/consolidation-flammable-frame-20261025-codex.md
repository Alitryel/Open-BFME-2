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

## SpecialAbilityUpdate merge addendum (2026-10-25)

After rebasing onto current origin/master, the same clean trial was regenerated
and `tu_skeleton.py` again accepted the seed plus three unchanged donors. The
merge repointed 25 rows and the `reverse/ms_header_queue.tsv` path key. Build
passed 26/26 matched rows, all five existing funclet pins, four string literals
and 13 compiler float references; declared-unmatched, staged TU ownership,
code-identity (26 rows, 0 new findings), CSV and whitespace checks passed.
`data_check.py --staged` reports three shadow findings outside the baseline in
the merged source (`wrong-name` at 0x00A033A0, 0x00A033A8 and 0x009FEFA4).
They were not retired or treated as cleanup; Sol should reconcile their data
identity against the original providers. The `SpecialAbilityUpdate.cpp` source
has an existing ms-header queue row; the merge tool repointed it. No current
header-queue item was removed.

Rejected clean donors remain for Sol: `SpecialAbilityUpdateModuleData.cpp`
reports C2039 (`m_customAnimAndDuration` is not a member of
`SpecialAbilityUpdateModuleData`); `SpecialAbilityUpdateSlot8.cpp` reports
C2039 (`rva0044EDA6` is not a member of `SpecialAbilityUpdate`);
`Rva0044EECACheck.cpp` reports C2039 (`m_val20` is not a member of
`Overridable`); `Rva0044EF5EFinish.cpp` reports C2504 (`BehaviorModule` base
class undefined); `SpecialAbilityUpdateXfer.cpp` reports C2061 (`Snapshot`
identifier missing at `BfmeXfer.h(37)`); `SpecialAbilityUpdateRva0044FEB6.cpp`
and `Rva00451EACMethod.cpp` report C2061 (`CommandSourceType` identifier
missing); `SpecialAbilityUpdateIsWithinStartAbilityRange.cpp` and
`SpecialAbilityUpdateInitiateIntent.cpp` report C2143 (missing `;` before `*`)
and C2501 for `Object::AIUpdate`; and
`SpecialAbilityUpdateTriggerAbilityEffect.cpp` reports C2143 before `*` and
C2501 for `Object::Player`. Mixed and protected donors remain untouched.

The final tooling compatibility audit used current `origin/master..HEAD` plus
staged moves. Across this batch, active tools, hooks, workflows, source/header
includes, build inputs and registries have no manual path consumers for the
absorbed donors. `reverse/link_status.csv`, attempt logs/evidence and the
TU's source provenance comments keep historical original paths by design.

## Additional scoped trials and TransitionDamageFX merge (2026-10-25)

QueueProductionExitUpdate had no accepted donors. The dtor donor fails C3855:
`BitFlags` template parameter `NUMBITS` is incompatible with its declaration;
its Xfer donor reports C2011 `Xfer` redefinition at `BfmeXfer.h(19)`; the
ExitObjectViaDoor, SetRallyPoint, notifyProductionBurstFinished and
Rva004A0670Copy donors report C2011 `Coord3D` redefinition in the included
Coord3D.h. PoolKey, ctor and QueryRallyOverride are protected path-keyed
refusals. No donor was changed or retried.

TunnelContain has no safe merge: its seed fails under every merged flag set at
`reference/shims/bfmealloc/stl/_alloc.h(446)` with C2950 (`allocator<char>`
cannot explicitly instantiate an explicit specialization). Other donor errors
include C2061 `Snapshot` in `BfmeXfer.h(37)`, missing `removeFromContain`,
`rva0047DF44` and `rva0047DF81` members, plus a failed cast from
`ContainModuleInterface *` to `TunnelContain *`. No donor was changed or retried.

Earlier scoped dry runs also remain blocked: GiantBirdAIUpdate ctor and
FollowPathAppend report C2226 on `AICommandType`; its locomotor, collision and
waypoint donors report missing class members, and Xfer reports missing
`Snapshot`. AITNGuard's seed fails with C2143 in GameLogicObjectLookupView.h(37)
and C2061 at line 113; no donor was accepted. These files were left untouched.

TransitionDamageFX merge applied by the tool after rebasing and regenerating the
trial: the target plus `TransitionDamageFXModuleDataCtor.cpp` were accepted,
20 rows were repointed, and the constructor fragment was removed. Build passed
28/28 rows and six funclet pin verifications; `find_declared_unmatched.py`
reported all definitions already matched. Staged ownership, CSV, whitespace and
case checks passed; identity remains shadow and reports three new `divergent`
bindings from the merged TU to `AsciiString` dtor 0x00036410 for its three
record types. `data_check.py --staged` had zero findings. Sol should review those
identity bindings; none were retired here.

TransitionDamageFX donor blockers remain: Xfer fails C2061 `Snapshot` in
`BfmeXfer.h(37)`; the Rva004B9DA9 and ctor donors reference missing
`bfmeUseFDE`/record members; CopyRange reports `_STL::random_access_iterator_tag`
redefinition; EraseRange and ModuleData destructor report missing type/member
syntax; NeighborIDSubobjectNameDataAppend reports `_strcmpi` linkage
redefinition and STL allocator conflicts; mapLoadPostProcess reports a second
`_STL::allocator` definition. Mixed and protected donors remain untouched.

The tooling compatibility audit for the pending range `origin/master..HEAD`
plus this staged move included the absorbed paths from OneRingPenaltyUpdate,
FlammableUpdate and SpecialAbilityUpdate, and the TransitionDamageFX ModuleData
constructor. Searches across active tools, hooks, workflows, source/header
includes, build inputs, registries and docs found no manual path consumer to
repair. The merge tool repointed `functions.csv`, `tu_map.csv`,
`ms_header_queue.tsv` and doxygen inputs. Historical EA-path references were
preserved. Outstanding shadow identity findings include the three Transition
bindings and the three SpecialAbility data findings already listed above; this
batch retires no identity/data/header debt.
