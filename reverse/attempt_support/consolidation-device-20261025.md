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
