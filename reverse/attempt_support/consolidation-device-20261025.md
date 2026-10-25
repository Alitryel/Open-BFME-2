# Device consolidation handoff, 2026-10-25

## Win32BIGFileSystem

Destination: `Code/GameEngineDevice/Source/Win32Device/Common/Win32BIGFileSystem.cpp`.
The normal merge accepted five donors and `./build.sh` matched all 11 carried
ledger rows (the tool subject counts seven approved routed rows).
`find_declared_unmatched.py` and `check_csv.py` passed. The attempted merge was
restored, including both source-column ledgers; no source or debt was changed.

The batch path audit found an active `reverse/ms_header_queue.tsv` entry for
absorbed `Code/GameEngine/Source/Common/Win32BIGFileSystem_init.cpp`, with
`sprintf:abi` debt. `repair_queue.py ms-headers` skips nonexistent paths, so
leaving that entry at the deleted donor would hide existing work.
The owning `ms_header_audit.py scan` failed before scanning: its kitchen-sink
compiler returns false with empty output even for an empty preprocessing TU.
Using the build tool's genuine compiler WINEPATH exposes the underlying next
error, `D2021: invalid numeric argument /work3/.../tmp.cpp`: the audit supplies
Unix absolute source paths to cl, and its INCLUDE paths are also Unix paths.
It needs a separately verified Linux/Wine portability repair before a fresh
queue can be generated and this merge safely published. No check was bypassed
and no queue record was deleted or hand-reclassified.

The sixth clean donor, `Rva00603CA3Finish.cpp`, also needs a declaration
reconciliation (`Rva00603C0F::rva00603CA3` missing in the composite). Mixed and
protected donors remain untouched. Claims for this attempted TU were released.

Reproduce: `python3 tools/ms_header_audit.py scan
Code/GameEngine/Source/Common/Win32BIGFileSystem_init.cpp`; then use the normal
planner, plan, dry run and merge after the prerequisite repair.

## W3DLaserDraw and W3DGameFont

The same prerequisite blocks these candidates without repeating the failing
audit. Laser's normal three-donor merge byte-matched 3/3 rows (167 bytes)
before restoration, but its absorbed `RefCountPtrTextureRva000C9A51.cpp` has
an active `free:abi` header-queue entry. Laser claims were released.
Font's dry run accepts the existing TU and `Rva00090034SimpleVecDtors.cpp`
(five rows), but the latter has an active `operator delete [ ]:same` queue
entry. No actual Font merge or claims were made. Neither report entry was
deleted, reclassified, nor silently left pointing at a vanished source.

Laser also retains an unmerged xfer donor that fails in `BfmeXfer.h:37`
(missing `Snapshot`) and a texture-range donor with no baseline match.
Font retains a private `SimpleDynVecClass` template conflict.

## Shadow identity finding

The normal W3DBridgeBuffer commit hook reports one new shadow finding for
`?Normalize@Vector3@@QAEXXZ` (definition: divergent). The private method's
source text was already identical in the pre-merge TU; its source definition
was not changed by consolidation. No baseline or identity gate was altered.

## Completed scoped pass

Seven retail TUs were consolidated through normal `tu_skeleton.py --merge`
admission: W3DShrubBuffer, W3DBridgeBuffer, W3DGhostObject,
W3DVegetationBufferBase, W3DSupplyDraw, TileData and W3DTreeDraw.
The pass removes fourteen source files net and preserves 21 distinct matched
rows (2,514 retail bytes). Each resulting TU passed `./build.sh`,
`find_declared_unmatched.py`, CSV integrity and normal commit hooks.
These are consolidation results, with no recovered-byte or linked-byte claim.

TileData's RGB555 donor initially failed because composition moved its
`extern "C"` definition ahead of the template helper. Direct conditional
expressions changed the retail stack layout and emitted `cmov`; both were
reverted. A separate C-linkage declaration lets the unchanged definition
inherit linkage and retain helper-before-use order. That prerequisite matched
1/1 (281 bytes) in its own commit, then the normal merge matched 3/3.

## Remaining scoped queue

The final scoped queue was read with `tu_skeleton.py --queue --under
Code/GameEngineDevice/Source/ --limit 20`; it lists eight remaining TUs.
No mixed file was split and no protected register was changed.

- Shrub retains thirteen possible file removals. Private class views omit
  methods/fields required by other donors; `Rva000E73FCCopy.cpp` has no baseline
  match. Existing destination hatches were carried unchanged.
- Bridge retains seven possible removals, requiring private-view reconciliation
  or a byte-codegen repair. Its shadow identity finding is recorded above.
- Ghost retains two possible removals: `StlSweepW5Rva00063BB2.cpp` changes bytes,
  and `S3StrideCopyLoops_Rva00064605.cpp` conflicts with a private vector view.
- BIG, Laser and Font retain the header-queue prerequisite above. These failed
  consumer audits were restored instead of publishing dangling queue sources.
  BIG's clean `Rva00603CA3Finish.cpp` donor also remains rejected: the composite
  emits `error C2039: 'rva00603CA3' : is not a member of 'Rva00603C0F'` at line
  360, followed by `error C3861: 'rva00603CA3'` at line 364. Reconcile its
  declaration in a verified prerequisite change before retrying this donor.
- Supply retains its xfer donor, which fails on `BfmeXfer.h:37`'s missing
  `Snapshot` declaration. Its body was left unchanged and its claim released.
- Shadow's `W3DBufferManager.cpp` dry run reports `accepted: []`, `rejected: {}`,
  and `blocked: no verified merge of two or more donors`. No source was
  changed; the 0x00115FF1 attempt records this exact acceptance boundary.

## Compatibility audit

Each commit calling the runner publisher audited every pending absorbed path
from outgoing commits plus the staged merge, including active tools, hooks,
workflows, includes, build/configuration inputs and registries. No containing
directory was removed, and recursive Code source discovery remains valid.
Normal ledger repointing accompanied each merge; TU-map changes only updated
source columns, never regenerated routing. Remaining old-path references are
census/name history, attempt evidence, naming-decision reasons and source
provenance. Original EA path strings remain intact.

## Reference freshness handoff

The missing freshness receipt triggered an official BFME 1 upstream check.
The clean pinned checkout is `0bf534ea7ccde110c456edb9cd2dd5dae823c953`;
fetched upstream was `3f10b03557f74f6c71bf0180663ae0d70f6a810d`.
The initial shallow checkout could not fast-forward; fetching deeper history
resolved ancestry. No reference pointer was advanced or freshness success
recorded. Completing the pointer update and refreshing affected donor results
belongs to a reference-update pass outside this dedicated consolidation scope.

An initial old-input full build collided with source removal while merges were
in flight (`Rva00603FD2Ctor.cpp` disappeared). It was polled to completion and
then rerun with the game sources held steady. The stable run at `0845a25e9d`
completed with `FULL GATE: OK` and verified all 98,244 function rows and 2,209
data rows. String, float, import, DIR32, pin, module, source-claim and no-op
patch checks also passed. Its complete receipt is retained locally as
`build/bfme1-freshness-stable-old.log`. This verifies the retained inputs and
does not establish the newer pointer's compatibility.

## Follow-up pass, 2026-10-25 (codexb3)

Destination scope: `Code/GameEngineDevice/Source/`. Reviewed the scoped planner,
original-path alternatives, current approved plans and dry merges. Every applied
move used the normal claimed `tu_skeleton.py --merge`; no mixed-file split,
naming vote, routing-map regeneration or maintainer runner was used.

Verified results for this pass (distinct rows at the final destinations):

| Retail TU | Donor .cpp files removed | Matched rows preserved | Retail bytes |
|---|---:|---:|---:|
| W3DSupplyDraw.cpp | 1 | 3 | 137 |
| W3DShrubBuffer.cpp | 1 | 5 | 431 |
| W3DBridgeBuffer.cpp | 5 | 10 | 1225 |
| TileData.cpp | 1 | 5 | 519 |
| Total | 8 | 23 | 2312 |

One scope-local header was added, so the net tracked file reduction is seven.
This is consolidation progress, with no newly recovered C++ bytes or claimed
link-census/ownership improvement.

Prerequisites were separate byte-verified commits. Supply's local
`BfmeDrawXferPrefix.h` places operand forwards ahead of the existing Xfer header
when includes are hoisted; the seed and donor use the same verified flags/view.
Shrub's dirty-byte member spelling was aligned without changing its offset.
Bridge reconciled the existing mesh reference prefix and mesh pointers at
0x38/0x7C/0xB8, visibility at 0x104, stride 0x114, and the MeshClass member at
0xC4. Its cull donor shed unused includes while retaining EA provenance. The
init donor's Vector3 component spelling was aligned, and the destination now
exposes its verified template-name/state/enabled suffix at 0x108/0x10C/0x110.
No escape hatch or protected register was added or expanded.

All four destination `./build.sh` runs, `find_declared_unmatched.py`, CSV and
normal commit hooks passed. The hooks checked source ownership, code identity
(shadow, no new finding), converged data, pin admission, literal/float/import
references and EH where present. Bridge's final ten-row build includes its init
EH row; TileData's five-row build includes its destructor EH row. Only ledger
source columns moved; the committed TU map's routing was not regenerated.
CSV verification: 98,247 function rows, 15,733 symbols, 2,210 data rows.

Upstream commit `80ff5cf1e52d4cd952c16a86aa68a747bcbd4107` arrived during a publisher
rebase. Its changed consolidation instructions were read. Its EH-parent routing
fix made the Bridge init and TileData destructor whole-file candidates. The new
split lane was not used. A planner currency probe encountered an in-flight
compiler-trial source; the report was regenerated with the trial finished and
`name_lane.py consolidate --check build/consolidation` then passed. Local receipt:
`build/device-planner-after-init-merge.log`.

### Final compatibility audit and publication handoff

The audit covers all outgoing absorbed paths plus staged moves through
`c9411de1053cac4a570b996691a40d3acfcc3d62`, based on
`20d076561b9a2a0e705a187684f73b9aee12c4e9`. The fetched `origin/master..HEAD`
diff and staged diff were reviewed together; inverse incoming GameLogic changes
were distinguished from this seat's moves. Receipts:
`build/device-pending-paths-7.txt`, `build/device-path-consumers-7.txt`, and
`build/device-directory-consumers.txt`. The combined search covered old paths,
basenames, directory-derived discovery, active tools, hooks, workflows, includes,
build inputs, registries and documentation. No active consumer needed a repair.
Intentional old mentions remain in census history, attempt history/support,
source provenance, stale generated not-yet-merged comments and an unrelated
destructor declaration comment. No containing directory was removed. EA paths
remain unchanged. Normal source-ledger repointing accompanied every move.

At handoff writing the thirteen implementation commits remain local. Each commit
called `/opt/runner/publish` in the same command. Most calls deferred on the
shared slot. One publisher ran and rebased successfully, with its push gates
passing, but all three push attempts failed (remote pack rename/unpack, then a
remote error, then a concurrent master update). The final handoff commit retries
publication normally; the runner owns any remaining unpublished batch.

Unchanged rejected donors' claims and the partially acquired Vegetation scope
were released. Keep the following accepted file claims until publication is
confirmed, then release them and run `python3 tools/claims.py release --landed`:

- `Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DSupplyDraw.cpp`
- `Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DSupplyDrawXfer.cpp`
- `Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/BfmeDrawXferPrefix.h`
- `Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DShrubBuffer.cpp`
- `Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DShrubBufferRva000E70D9.cpp`
- `Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DBridgeBuffer.cpp`
- `Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DBridgeBufferRva000DD878.cpp`
- `Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DBridgeBufferDestructor.cpp`
- `Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DBridgeClearBridge.cpp`
- `Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DBridgeBuffer_cullBridge_W3DBridge_QAE_NPAVCameraClass_Z.cpp`
- `Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DBridgeInit.cpp`
- `Code/GameEngineDevice/Source/W3DDevice/GameClient/TileData.cpp`
- `Code/GameEngineDevice/Source/W3DDevice/GameClient/TileDataDtor.cpp`
- `reverse/attempt_support/consolidation-device-20261025.md`

The corresponding 23 RVA claims are the matched rows in the four destinations,
including Bridge's 0x00762E6C and TileData's 0x007649BA EH rows.
Use the live claims/pending landing records for settlement rather than assuming a
local commit is a published receipt.

### Remaining scoped candidates

- Vegetation: completed the formerly held reset/render-pass merge after the
  claim cleared. Seven rows passed the destination build, declaration check,
  CSV check and commit hooks; commit `6201ba59fe` is awaiting publication.
- Shrub: the current queue marks the remaining donor set HELD. Explicit claims
  for 0x000E7140 and 0x000E7A40 were refused under `jarvis-p2-shrub-1025`; neither
  file was edited. Other private-view prerequisites remain with that worker.
- Bridge: remaining clean donors need Vector3/MeshClass and terrain declarations
  or add/load member declarations reconciled. Final dry/apply receipts retain
  the exact compiler refusals for GetModelVertices, Load, AddBridge and
  LoadBridges; these unchanged donor claims and RVAs were released. The
  GetModelVerticesFixed donor remains protected-register keyed; mixed ctor,
  destructor and renderer files were not split.
- WaterTracks: the current dry run found no verified two-donor merge; SaveTracks
  has no baseline match in that trial. Flush/bounds donors are protected-register
  keyed, and other rows are mixed. No source or claims changed.
- TreeDraw: ModuleNameKey donor fails because the seed lacks getModuleNameKey;
  adding a virtual requires checking the existing constructor's vtable stores.
- PropDraw: React donor fails on Coord3D redefinition against the seed's header
  environment. It needs the owning canonical-header/declaration acceptance path.
- BIG/Laser/Font: the header-audit/path-keyed prerequisites documented above are
  unchanged. Ghost's byte/vector-view blockers and Shadow's lack of a verified
  two-donor merge are unchanged and were not repeatedly rebuilt.

### Fresh scoped queue recheck

The planner snapshot and scoped queue were regenerated on 2026-10-25 and passed
`name_lane.py consolidate --check`. The queue still has no clean unheld donor
set. `Win32BIGFileSystem.cpp` routes outside this pilot prefix and Shrub is
HELD, so neither was taken. Current merge trials found no accepted in-scope
batch: WaterTracks has no accepted donors and `Rva000FF50DSaveTracks.cpp` has
no baseline match; BufferManager accepts no donors; Bridge accepts none, with
`W3DBridgeGetModelVertices.cpp` failing at `m_start` (missing `;`),
`W3DBridgeLoad.cpp` failing at the missing `W3DBridge::MeshClass` declaration,
`W3DBridgeBufferAddBridge.cpp` failing because `W3DBridgeBuffer::addBridge` is
undeclared, and `W3DBridgeBufferLoadBridges.cpp` failing because
`W3DBridgeBuffer::loadBridges` is undeclared. Ghost accepts none; its rejected
donors still hit `_STL::__false_type` redefinition and duplicate `_STL::vector`
template definitions. Prop's rejected React donor still hits a `Coord3D`
redefinition, and TreeDraw's rejected module-name donor calls missing
`W3DTreeDraw::getModuleNameKey`.

The updated Laser trial accepts three donors under this prefix plus two WW3D2
donors under `Code/Libraries/`; it rejects the vector destructor donor for no
baseline match and refuses protected-register donors. GameFont accepts its
existing seed plus two `Code/Libraries/` donors. These cross-area batches were
left unapplied. In-scope split trials for the Prop destructor, both Tree module
data donors, BufferManager re-acquire, and both Font donors were whole donors
with no residual. BufferManager Slots carved only `0x00115ECB` and `0x001163E7`
(2/2 matched); six other rows had duplicate definitions, and the merge verifier
still accepted no donor. All dry runs were read-only; no claims or source edits
were made for these candidates.

Final scoped queue receipt: `build/device-queue-after-init.txt`. The session ends
with verified consolidation tasks complete, not an assertion that the scope has
no remaining work. The BFME 1 reference update/freshness handoff above remains
open; no success receipt or pointer update was invented.

`python3 tools/progress.py origin/master` passed: BYTE-MATCHED 7,978,500 bytes
(100.00%), LINKING 7,343,016 (97.74%), LINKED 7,598,950 (95.24%). All three deltas
are zero. Linking figures remain the census dated 2026-10-25 09:42 at
d2636bb381; no new census was run. Local receipt: `build/device-session-progress.txt`.

## Follow-up pilot pass, 2026-10-25

The scoped planner was regenerated and `name_lane.py consolidate --check
build/consolidation` passed. `tu_skeleton.py --queue --under
Code/GameEngineDevice/Source --limit 20` rebuilt its TU routing in memory; no
regenerated map was committed.

Two accepted, unchanged donor merges were verified:

- `W3DSnowManager.cpp` was merged into `W3DSnow.cpp` (14 rows in the tool's
  merge receipt; the destination build verified 15/15 matched rows). Four
  path-keyed function rows and one TU-map entry were repointed. `build.sh`,
  `find_declared_unmatched.py`, and `check_csv.py` passed. The source count fell
  by one. The path audit found no active consumer requiring a manual change;
  source discovery remains recursive and the original EA path provenance stays
  in the ledgers.
- `W3DWaypointBufferDestructor.cpp` was merged into `W3DWaypointBuffer.cpp`
  (8 rows). `build.sh` verified 8/8; declaration and CSV checks passed. Eight
  function rows and one TU-map entry were repointed. The donor became the
  canonical TU file path, so this move did not change the source-file count.
  `W3DWaypointBufferDrawWaypoints.cpp` remains untouched: the dry run rejected
  it with C2143 syntax errors in the combined TU.

Fresh rejected prerequisites, with no edits to those donors:

- BibBuffer: destructor donor fails byte verification; allocator donor has
  C2440 converting `BfmeDynamicNativeVB *` to `DX8VertexBufferClass *`; the
  constructor hits MSVC C1001.
- FlatHeightMap: the two in-prefix partial/frame donors fail C1001 and byte
  verification. Its accepted external Common donors are outside this pilot.
- TreeBuffer: the dry run accepted one in-prefix destructor together with
  three Common donors outside this pilot. An accidental tool application
  briefly staged that cross-prefix merge; it was fully restored before commit,
  its 68 claims were released, and no TreeBuffer change remains. The reset
  donor also fails on missing `Rva000E6AC0::rva000E65B1` and `m_dirty`.
- Smudge: constructor needs `m_probeColor` (C2065), release has a pointer
  conversion error (C2440), reacquire fails byte verification, and copyRect
  hits C1001.
- DisplayStringManager: accepted donors are outside this pilot; remaining
  declarations fail on `rva00090381` and `m_14`.
- ProjectileStreamDraw: the seed fails at `BfmeXfer.h(37)` with C2061 for
  `Snapshot`; the in-scope mixed split trial could carve no row because the
  definition did not spell its name.
- Snow mixed split: carving `0x00093CC3` would leave matched row `0x00083BD4`
  behind, so the split was refused.

Previously recorded blockers for Shrub (HELD), Bridge, WaterTracks, Laser,
GameFont, Ghost, TreeDraw, PropDraw, and BufferManager remain unchanged in the
sections above. No identity debt retirement is claimed. Fresh planner/queue
reports and these exact dry-run results are the evidence for the Sol follow-up.

The staged path audit for `origin/master..HEAD` plus both staged moves found no
active consumer requiring repair. The planner reports 1,025 source files after
the pass, down from 1,026 at its start: Snow removed one source file and the
waypoint donor was renamed to its canonical TU path without changing the
count. Remaining mentions of the absorbed Snow
source are `reverse/name_basis.csv` provenance, the historical
`reverse/link_status.csv` receipt, and the retained source-origin comment in
`W3DSnow.cpp`. The waypoint donor name remains in historical `reverse` attempt
evidence and the related Common destructor comment. These were preserved as
evidence/comments; active recursive source discovery and the build inputs use
the consolidated files. The `Win32LocalFileSystem` dry run accepted only the
Common family outside this pilot; its in-prefix wide file-list donor was
rejected with C2511. Debris accepted no donors: its in-prefix React donor
fails byte verification, and Xfer hits duplicate `StringBase` template
definitions; the other candidate rows are mixed or protected-register keyed.
The final planner snapshot and queue show no other accepted in-prefix donors
beyond work recorded above.

Publication handoff: commit `150906143e` is locally verified and waiting in the
runner's shared publish batch. The path audit covered both moves
(`W3DSnowManager.cpp` to `W3DSnow.cpp`, and `W3DWaypointBufferDestructor.cpp`
to `W3DWaypointBuffer.cpp`) and the outgoing ledger changes; the follow-up
documentation commit adds no path changes. Keep these claims until landing:
RVA `0x00762F44`; file claims for `W3DSnow.cpp`, `W3DSnowManager.cpp`,
`W3DSnowManagerRender.cpp`, `W3DSnowManagerRenderSubBox.cpp`,
`W3DSnowBlendPhase.cpp`, `Rva0009322DLightning.cpp`,
`W3DSnowManager_reset.cpp`, `W3DSnowStateTransition.cpp`,
`W3DWaypointBuffer.cpp`, `W3DWaypointBufferDestructor.cpp`,
`W3DWaypointBufferDrawWaypoints.cpp`, and this handoff file. No claim was
released for either verified merge because publication has not yet occurred.

TreeBuffer follow-up in this seat: the current dry run and apply accepted the
seed plus four in-scope donors, absorbing `Rva000EADA7Copy.cpp`,
`Rva000EB08CCheck.cpp`, `Rva000EB3D1.cpp`, and `Rva000EDA94Dtor.cpp` into
`W3DTreeBuffer.cpp` (15 rows; 12 function rows repointed in this commit).
The final TU build
reported 17/17 matched rows, `find_declared_unmatched.py` passed, and
`check_csv.py` passed. The planner's pre-merge source count was 1,025, so this
merge removes four source files; it recovers no bytes.

TreeBuffer donor blockers left for Sol, unchanged after the trial:

- `Rva000EA24DReset.cpp`: C2039, `rva000E65B1` is not a member of
  `Rva000E6AC0`; also C2065, `m_dirty` undeclared.
- `W3DTreeBufferRva000EA48D.cpp`: C2600, the `W3DTreeBuffer` constructor
  cannot be defined as a compiler-generated special member not declared first.
- `W3DTreeBufferRva000EA327.cpp`: C2039, `rva000EA327` is not a member of
  `W3DTreeBuffer`; also C2065, `count` undeclared.
- `rva000EAFA4Rva000EAFA4Farm.cpp`: C2039, `rva000EAFA4` is not a member of
  `W3DTreeBuffer`; also C2065, `count` undeclared.
- `W3DTreeBufferRva000EB0E6.cpp`: C2039, `rva000EB0E6` is not a member of
  `W3DTreeBuffer`; also C2065, `m_numTrees` undeclared.
- `W3DTreeBufferRva000EB2EF.cpp`: C2039, `rva000EB2EF` is not a member of
  `W3DTreeBuffer`; also C2065, `m_numTrees` undeclared.
- `W3DTreeBufferUpdateTexture.cpp`, `W3DTreeBufferAddTreeType.cpp`,
  `W3DTreeBuffer_startMorph.cpp`, `W3DTreeBufferRva000ECDF5.cpp`, and
  `W3DTreeBufferXfer.cpp`: C2953, `StringBase` template class already defined.
- `Rva000EBFD1UpdateVertexBuffer.cpp`: C2039, `Release_Ref` is not a member
  of `Rva000EDA94Ref`.
- `Rva000EC9C6.cpp` and `W3DTreeBufferRecordLookup.cpp`: C2039,
  `rva000EB2EF` is not a member of `W3DTreeBuffer`.
- `W3DTreeBufferAddTree.cpp`: C2039, `rva000EB2EF` is not a member of
  `W3DTreeBuffer`; its other diagnostic is C2600 for the undeclared
  compiler-generated constructor.
- `W3DTreeBufferUpdateTopplingTree.cpp` remains refused because it is keyed in
  a protected path-keyed register. No identity or data debt was retired.

The path audit for the pending range plus these staged moves searched the old
and destination basenames in active tools, hooks, workflows, includes, build
inputs and registries. It found no active consumer requiring a manual change;
remaining old source mentions are the generated TU's source-origin comments and
historical `reverse` evidence. The moved sources had no code-identity or data
baseline keys; the merge tool retained queue accounting and moved every
accepted ledger source. The current TU passed its byte/declaration checks; no
source provider or consumer binding was changed by the composition.

ShrubBuffer follow-up in this seat: the tool accepted the seed and five in-scope
 donors, absorbing `W3DShrubBufferRva000E7140.cpp`, `W3DShrubBufferRva000E75F5.cpp`,
`W3DShrubBufferRva000E7A40.cpp`, `W3DShrubBufferRva000E912A.cpp`, and the Common
`Rva000E73FCCopy.cpp` into `W3DShrubBuffer.cpp` (11 rows; 6 function rows
repointed). The final TU build reported 11/11 matched rows, `find_declared_unmatched.py`
passed, and `check_csv.py` passed. Five donor source files are removed; no bytes
are recovered.

Rejected ShrubBuffer donors remain for Sol, with the exact dry-run errors:

- `W3DShrubBufferRva000E72B3.cpp`: C2039, `rva000E7140` is not a member of
  `W3DShrubBuffer`; C2065, `m_count` undeclared.
- `W3DShrubBufferUnitMoved.cpp` and `W3DShrubBufferUpdateTexture.cpp`: C2039,
  `rva000E7A40` is not a member; the generated constructor then reports C2600.
- `W3DShrubBuffer_loadShrubsInVertexAndIndexBuffers.cpp`: C2950,
  `_STL::allocator<char>` cannot explicitly instantiate an explicit
  specialization; the same missing-member error is also reported.
- `W3DShrubBufferRemoveShrubsForConstruction.cpp`: C2084, placement array new
  already has a body.
- `W3DShrubBufferRva000E8365.cpp` remains refused because it is keyed in a
  protected path-keyed register.
- The other rejected candidates in the dry-run output remain untouched; no
  declaration, signature, layout, linkage, or body repair was attempted.

The path audit for the pending range and these moves searched active tools,
hooks, workflows, includes, build inputs and registries. It found no active
consumer requiring a manual change. The Common copy donor carried the shrub
constructor row, so it was kept out of the preceding TreeBuffer commit and is
included here with its matching TU ledger move. No identity or data debt was
retired.

Additional unchanged consolidation trials in this seat (no source or ledger
changes from these trials):

- `W3DBridgeBuffer.cpp`: dry run accepted no donors. The allocate-buffer donor
  fails C2039 (`allocateBridgeBuffers` is not a member); the bridge destructor
  and model-vertex donors fail C2146/C2501 at `m_bridges` and `m_start`; the
  buffer constructor fails C2600 (compiler-generated constructor not declared);
  bridge load fails C2143/C2501 at `W3DBridge::MeshClass`; load-buffers fails
  C2065 (`m_initialized`); add/load bridge donors fail C2039/C2065 for missing
  members. Two in-prefix mixed split trials were also refused: the constructor
  split loses matched row `0x0017098D`, and draw-bridges loses `0x0039B780`.
  `W3DBridgeGetModelVerticesFixed.cpp` remains protected-register keyed.
- `W3DSnow.cpp`: no donors accepted. The lightning donor fails C2065
  (`WeatherSetting`); the subbox and render donors fail C2065 (`W3DSnowManager`);
  reset, blend-phase, and state-transition donors fail C2039 for missing class
  members. Four paths remain protected-register keyed.
- `Water/W3DWaterTracks.cpp`: no donors accepted. The Common move/find donors
  and device init donor fail C2143 (missing `;` before `*`); the render-system
  constructor fails C2600; the object render donor has C2011 (`RealRange`
  redefinition); save-tracks fails C2039 (`m_initTimeOffset` missing).
  Three paths remain protected-register keyed.
- `FlatHeightMap.cpp`: the dry run accepted the TU and two donors, but apply
  stopped before changing files because other workers held
  `Rva000E1D51Forward.cpp` and `FlatHeightMapOnFrameUpdate.cpp`. The partial
  update donor fails C1001; the on-frame donor fails byte verification. No
  claim for this candidate remains under this seat.
- `W3DBibBuffer.cpp`: no donors accepted. The destructor donor fails byte
  verification, allocation fails C2440 converting `BfmeDynamicNativeVB *` to
  `DX8VertexBufferClass *`, and the constructor fails C1001.
- `W3DSmudge.cpp`: no donors accepted. Constructor fails C2065 (`m_probeColor`);
  release-resource fails C2440 converting `DX8IndexBufferClass *` to
  `IndexBufferRef *`; reacquire fails byte verification; `copyRect` fails C1001.
- `W3DDisplayStringManager.cpp`: constructor donor fails C2039 for missing
  `rva00090381`; Common destructor donor fails C2065 (`m_14`) and C3861.
- `W3DWaypointBuffer.cpp`: draw donor fails C2143 (missing comma before `&`).
- `W3DVegetationBufferBase.cpp`: Common binder destructor fails C2677 (`&&`
  has no applicable global operator for `RefCountPtr<T>`); its other mixed
  donors are outside this pilot's assigned prefix.
- `W3DSupplyDraw.cpp`: destructor donor fails byte verification; the pool-key
  donor remains protected-register keyed; the remaining donor rows are mixed.

The planner and `--check build/consolidation` passed after the TreeBuffer and
ShrubBuffer merges. Planner source count is 1,020; the two merges in this seat
removed nine donor files total and preserved their accepted matched rows. The
Shrub TU hook reported the shadow code-identity finding
`definition: divergent | ??0Coord3D@@QAE@ABU0@@Z`; it remains outstanding for Sol
and was not retired. The TreeBuffer and ShrubBuffer commits are locally verified
and still await publication; keep their merge claims until landing, then run
`python3 tools/claims.py release --landed`.

### Follow-up pilot queue and split review

The scoped planner snapshot and `--check build/consolidation` passed. The
current TreeBuffer, ShrubBuffer and Snow dry runs accepted no donors; leave the
following unchanged for Sol's prerequisite lane:

- TreeBuffer reset donor: C2039, `rva000E65B1` is not a member of
  `Rva000E6AC0`; C2065, `m_dirty` undeclared. Other rows fail on missing
  `W3DTreeBuffer` members (`rva000EA327`, `rva000EA48D`, `rva000EB0E6`) and
  fields such as `count`/`m_numTrees`.
- ShrubBuffer donors fail on absent class members (`rva000E72B3`,
  `rva000E7734`, `updateTexture`, `addTreeType`, `drawShrubs`, `startMorph`,
  `rva000E8F9D`, `addShrub`, `DoXfer`); the shrub type constructor also hits
  C2011, `Coord2D` class type redefinition in `coord2d.h(13)`.
- Snow donors fail with C2065, `WeatherSetting` undeclared, or missing
  `W3DSnowManager` members (`reset`, `rva00093B5B`, `target_00094652`).

In-prefix split trials were read-only and rejected: TreeBufferUpdate and the
Snow render file would lose matched residual rows; the tree type constructor
and destructor carves into TreeBuffer failed `bytes`; the same carves into
ShrubBuffer failed C2011 (`Coord2D` redefinition); WaterTracksTestUpdate would
grow a hatch count through copied `drawEditorLine`/`unbindEditorTrack` helpers
and `pauseWaves`; BridgeCtor and BridgeBufferDrawBridges would lose matched
residual rows; W3DTerrainLogic is blocked because its `extern "C"` block defines
something; SmudgeManagerTestHardwareSupport would lose a matched residual row;
and W3DDrawModuleDeletingDtors has no definition spelling the ProjectileStream
row `0x000D144F`. No split was applied. Cross-prefix mixed donors remain outside
this seat's scope. No identity debt or byte/link improvement is claimed.

### Current-session result

- `FlatHeightMap.cpp` accepted the seed plus `Rva000E10C0.cpp` and
  `Rva000E1D51Forward.cpp`; the tool repointed 2 function rows and 2 TU-map
  rows. `./build.sh Code/GameEngineDevice/Source/W3DDevice/GameClient/FlatHeightMap.cpp`
  passed 38/38 matched rows, 13 string literals, 7 float literals and 29 EH
  funclet-label checks. `find_declared_unmatched.py` passed. No data rows,
  header-queue entries, identity keys or hatch counts belonged to those donors;
  the tool refreshed the TU map/function sources and did not stage other
  registers. The active path-consumer search found no tool, hook, workflow,
  include or build-input consumer; source-origin comments and old link-status
  /attempt evidence are historical. No new link census or COMDAT selection was
  run, so census bindings remain unmeasured for this move.
- `FlatHeightMapDoPartialUpdate.cpp` remains rejected with MSVC C1001 at
  composed TU line 540; `FlatHeightMapOnFrameUpdate.cpp` remains rejected by
  byte verification. `Rva000E1072.cpp` remains refused because it is keyed in
  a protected path-keyed register. All were left untouched.
- `W3DDisplayStringManager.cpp` accepted no donors: the constructor donor
  reports C2039 (`rva00090381` is not a member of
  `W3DDisplayStringManager`); the Common destructor donor reports C2065
  (`m_14` undeclared) and C3861 (`rva0009038` not found).
- `W3DWaypointBuffer.cpp` accepted no donors: DrawWaypoints reports C2143 at
  composed TU lines 38 and 56 (missing comma before `&`).
- After Sol's BibBuffer allocation prerequisite, `W3DBibBuffer.cpp` dry-run
  accepts its seed and allocation donor. Applying through the merge tool
  staged a TU whose complete contents were the single token `compile`; the
  required build then failed C1004 (unexpected EOF). Only this trial's staged
  source/ledger changes were restored and all acquired claims released. This
  is handed to Sol as a tool/application false-reject investigation; no code
  or tool workaround was made.

The pending FlatHeightMap path range was audited across active tools, hooks,
workflows, includes, build inputs, source registries and path-keyed ledgers.
The only references outside the new TU are source-origin comments, current
historical link-status rows, and attempt evidence. The moved owners are code
rows only; provider/data ownership and header/hatch debt did not change. No
identity retirement or source-byte recovery is claimed.

The staged code-identity gate reports five new shadow findings in the composed
TU (`RefCountPtr<FXShader::RenderingMethod>` copy constructor, `Vector3` copy
constructor, `Matrix3D::operator[]`, `VertexMaterialClass::Add_Ref`, and
`W3DTreeBuffer::setIsTerrain`). They remain outside the baseline and require
Sol's separate identity lane; no identity key was retired. `data_check.py
--staged` reports zero findings for the staged source.

`link_check.py --staged --new-variants --shadow` completed against the fetched
2026-10-25 census index with 0 recompiles (1 current staged TU) and reported no
new selected-COMDAT variant. The live census itself is unchanged.
