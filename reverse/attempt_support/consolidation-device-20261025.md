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
