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

- Vegetation: dry merge accepted reset/render-pass donors, seven rows. Normal
  application refused the render-pass file claim held by another worker; no
  source changed and all nine partial claims acquired here were released.
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

Final scoped queue receipt: `build/device-queue-after-init.txt`. The session ends
with verified consolidation tasks complete, not an assertion that the scope has
no remaining work. The BFME 1 reference update/freshness handoff above remains
open; no success receipt or pointer update was invented.

`python3 tools/progress.py origin/master` passed: BYTE-MATCHED 7,978,500 bytes
(100.00%), LINKING 7,343,016 (97.74%), LINKED 7,598,950 (95.24%). All three deltas
are zero. Linking figures remain the census dated 2026-10-25 09:42 at
d2636bb381; no new census was run. Local receipt: `build/device-session-progress.txt`.
