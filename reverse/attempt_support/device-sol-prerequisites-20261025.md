# Device consolidation prerequisites, 2026-10-25

Seat: yasinschroeder-codexb. Scope: GameNetwork, GameEngineDevice and Libraries.

## Laser Xfer include-order blocker cleared

The current Device planner and --plan retain the approved W3DLaserDraw TU and
mixed/protected donor boundaries. The unchanged normal dry-run reproduced the
Luna handoff's BfmeXfer.h:37 C2061 for Snapshot. The composer hoists includes
above this donor's operand forwards. The donor now includes the existing
BfmeDrawXferPrefix.h, already published for Supply in the same directory. That
header keeps exactly those same operand declarations with the canonical Xfer
include. The prefix and shared headers are unchanged; bodies and ABI are
unchanged. No new header, pin, name, baseline or protected register is added.

`./build.sh W3DLaserDrawXfer.cpp` passes 2/2 rows (86 retail bytes), and the
frozen-file check passes. The normal merge dry-run now accepts four donors and
five rows instead of three donors/three rows; xfer and loadPostProcess join the
previously compatible subset. Local receipts: build/laser-sol-before-dry.txt
and build/laser-sol-after-dry.txt. This is a separately verified prerequisite,
not an applied merge or recovered bytes.

The accepted RefCountPtrTextureRva000C9A51.cpp still has its active Microsoft
header report, which must be refreshed through its owning tool before a merge
can safely delete that path. The earlier Linux/Wine scan prerequisite/handoff
remains relevant. RefCountPtrTextureDestroyRange.cpp and the out-of-scope Common
vector destructor report no baseline match; do not claim them exact or split
mixed files. Mechanical work can rerun the current plan/trial after resolving
the report prerequisite. No merge was manually applied.

No pending source-path change exists in origin/master..HEAD or the staged
prerequisite; there are no changed path consumers to repair. All four GameInfo
prerequisites were published through f4d7013e88 with normal push verification
(45 rows across six affected sources/dependents, nine exact EH rows). The five
GameInfo file scopes and five body RVAs were released after that confirmed
push. GameInfo's all-five-donor merge trial preserves 18 rows/1067 retail bytes,
with four intact fragments ready for a mechanical merge.

Retain file:Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DLaserDrawXfer.cpp,
0x000C92A0 and 0x000C92E8 until this prerequisite is confirmed published. Then
release the file scope and settle the RVAs (release --landed, explicit release
for unchanged ledger rows if needed).

## Font template declaration blocker cleared

The normal Font trial reproduced the private SimpleDynVecClass primary-template
collision against the seed's included Zero Hour simplevec.h (C2953/C2913).
simpledynvec_uint_add.cpp now includes that existing header and defines the
already-rowed unsigned Add as an explicit specialization. The target's +4/+8/+C
field accesses, four-byte element and existing BfmePod4 Grow callee are unchanged.
The small BfmePod4 specialization/friend remains the existing declaration, not a
new pin or alias. No shared/reference header or protected register changed.

`./build.sh simpledynvec_uint_add.cpp` preserves its one 51-byte row and
`find_declared_unmatched.py` passes. The normal Font dry-run now accepts all
three eligible files, six rows/227 retail bytes, with no rejected donors.
Receipts: build/font-sol-before-dry.txt and build/font-sol-after-dry.txt.
The Rva00090034SimpleVecDtors.cpp Microsoft-header queue entry still needs its
owning refresh before that donor path can be deleted. This prerequisite is
ready for the mechanical seat after that refresh; no merge was applied here.

No pending source moves or path consumers were added by the Laser/Font batch.
Retain file:Code/Libraries/Source/WWVegas/WWLib/simpledynvec_uint_add.cpp,
file:Code/GameEngineDevice/Source/W3DDevice/GameClient/GUI/W3DGameFont.cpp and
0x0009014A until publication is confirmed; claims.py claimed the approved
destination together with this donor/RVA. Release those scopes after landing.

TreeDraw's unchanged trial still rejects ModuleNameKey because the seed lacks
the virtual declaration. Retail table 0x00BCCCF8 places that method at slot 4;
the seed constructor deliberately suppresses compiler vtables and explicitly
stores its existing address global. A complete compatible DrawModule virtual
prefix and constructor/vtable repair is still needed; a slot-0 virtual or a
partial emitted table would not establish the retail ABI. No source attempt
or new hatch was retained for that unchanged blocker.

## Debug exception declaration blockers cleared

The Libraries planner and current approved debug/debug_except.cpp plan identify
ten clean candidates. Its normal baseline trial accepted seven, rejecting
LogFPURegisters and LogRegisters because the seed's DebugExceptionhandler and
exception-pointer/context views did not declare their interfaces. One Common
record-initializer donor was separately rejected for bytes.

The three exception-reporting donors now use the local
WWVegas/WWDebug/BfmeDebugExceptionView.h. It combines their existing declarations:
typed exception/context pointers; FloatSave at +0x1C followed by the previously
verified SegGs..SegSs register fields at +0x8C..+0xC8; the FPU donor's superset
of the Debug virtual overloads with width/fill unchanged at +0x9F50/+0x9F54;
and all three existing handler member declarations, retaining their access.
The explicit local include directory is retained by normal merge composition
and resolves from the approved debug/ destination as well as the donors.
No shared reference header, canonical class contract, pin, name or register was
changed. No Common source was edited.

`./build.sh` preserves GetExceptionType 1044 bytes, LogFPURegisters 635 bytes
and LogRegisters 678 bytes: 3/3 bodies, 104 string references and two named
imports verified. Frozen-file checks and diff checks pass. The normal trial
now accepts nine files/nine rows/2815 retail bytes. Only the unchanged Common
Rva0088D8E0RecordInitialize.cpp byte rejection remains. Receipts:
build/debug-except-sol-before-dry.txt and build/debug-except-sol-after-dry.txt.
The compatible subset is ready for a mechanical merge with normal claims and
the complete path audit. Mixed/protected candidates remain untouched.

Retain file scopes for DebugExceptionGetType.cpp,
DebugExceptionhandler_LogFPURegisters.cpp, DebugExceptionhandler_LogRegisters.cpp
and BfmeDebugExceptionView.h under Code/Libraries/Source/WWVegas/WWDebug/,
plus RVAs 0x0003C7A0, 0x0003CD30 and 0x0003DA20, until publication is confirmed.
This declaration-only prerequisite adds the local header but moves no existing
source path; the full outgoing Laser/Font/debug batch still has no absorbed
fragment or renamed consumer to repoint.

## PingThread SDK declarations and include order cleared

The refreshed Network planner and approved PingThread plan retain the mixed and
protected boundaries. The normal baseline trial accepted three files/ten rows,
rejecting the two clean Pinger donors on duplicate placement-array operators.
The earlier handoff also identified the seed's private void-pointer return for
GetProcAddress, conflicting with the existing Windows header's FARPROC return.

PingThread.cpp now includes its existing sweep windows.h before STLport and
uses that header's declarations instead of its eight local SDK typedefs and
function declarations. This also establishes the SDK shim's existing
placement-array guard before STLport and GameMemory meet; the shim is unchanged.
The ICMP helper's function-pointer casts and every body remain unchanged.
`./build.sh PingThread.cpp` passes all five rows/502 retail bytes, four literals
and three named imports; declared-unmatched and diff checks pass.

The normal after trial accepts five files/13 rows/958 retail bytes, including
areThreadsRunning and both getRequest donor rows. Only
Rva0055011A00550041.cpp remains rejected, for explicit string specializations
after instantiation. Receipts: build/ping-sol-before-dry.txt and
build/ping-sol-after-dry.txt. No merge was applied.

The optional ms_header_audit scan and check could not preprocess even their
empty kitchen-sink prefix in this Linux environment (exit 1; scan receipt in
build/ping-sol-ms-header.txt). No report refresh or register retirement is
claimed. The PingThread Microsoft-header queue row needs the owning environment
and writer refreshed before deletion or debt retirement. That queue is held
by another worker and was not edited. Retain the PingThread.cpp file scope and
0x0054F99E until this prerequisite is published, then release them.

The complete outgoing prerequisite batch still moves no existing source path.
The new debug view's explicit include path was verified from the standalone
donors and the approved merge destination; no active path consumer needs a move.

## HTree blocker reassessed against current composition

The refreshed Libraries planner and snapshot check pass. The approved HTree
plan still offers the seed, Storage, destructor and Capture_Bone as clean files,
with eleven mixed and four protected candidates retained. A fresh normal trial
now accepts none: Storage needs the missing HTreeClass::rva00160FC0 declaration,
while the destructor and Capture_Bone report `bytes`. This supersedes the old
Capture_Bone C2065/BfmePod36 diagnosis in the earlier HTree handoff; it does not
prove which composed row differs or justify a speculative declaration edit.

The official standalone build of htree.cpp, HTreeClassDestructor.cpp and
HTreeClassCaptureBone.cpp passes all 13 rows and seven float references. Thus
this is a consolidation prerequisite, not lost matched coverage. No HTree
source was changed and no merge applied. Fresh normal-trial receipt:
build/htree-sol-capture-before-dry.txt; approved plan: build/htree-sol-plan.txt.
The next attempt needs row-level composed-byte evidence before choosing a
source or tooling repair. Both rejected body verdicts were recorded with
re_log.py; the read-only reassessment's file and RVA scopes are released.

## Batch audit and verified totals

Immediately before the handoff commit, the complete outgoing range
origin/master..2e2940e95c and this staged evidence were audited against fetched
origin 27b23d675b8e46e096fc697af711003cf06c29f3. The direct two-endpoint diff
also includes incoming changes from other seats; the outgoing merge-base diff
and commit list isolate this batch. It modifies six existing source files and
adds one local header, without a source deletion, rename, ledger repoint or
active consumer path change. Tools, hooks, workflows, build inputs, registries
and historical EA paths require no repointing. Protected registers and the TU
map are unchanged by this batch. Normal acceptance gates remain required.

The session's eight prerequisites cover 29 existing matched rows/4063 retail
bytes in standalone verification. The five resulting compatible normal trials
preserve 51 rows/5320 retail bytes in total. No merge was applied, no source file
was removed and no new matched bytes, census movement or debt retirement is
claimed. GameInfo is already published; Laser, Font, debug and PingThread
prerequisites are a28e194a65, 12bb2947c0, 4d259ff112 and 2e2940e95c before any
publisher rebase. Retain their exact file/RVA scopes listed above until the
publisher confirms landing, then release them. The next mechanical pass should
use current routing and fresh reports, respecting all remaining SDK report,
Common-donor, mixed and protected boundaries.

## UDP Write SDK prototype blocker cleared

The fresh Network planner passes its snapshot check. The approved lower-case
udp.cpp plan and normal baseline trial reject all four remaining clean donors:
three use private UDP alias members absent from the shared header, and
Rva00594C12Write.cpp conflicts with the seed's sendto prototype (C2733).

The Write donor now includes the existing sweep winsock.h instead of its four
local import declarations and signed SOCKET typedef. Its existing class name,
16-byte address view and function body remain, with an explicit sockaddr cast
for the typed header prototype. SOCKET remains four bytes; socket and error
fields remain at +0 and +0x1C. No shared/header contract, pin or name changed.
Official standalone verification preserves the full 109-byte row and all four
named imports; declared-unmatched and diff checks pass. The normal after trial
accepts udp.cpp plus Write: 13 rows/882 retail bytes. Receipts:
build/udp-sol-write-{before,after}-dry.txt. The three private UDP alias donors
retain their declaration prerequisite; no merge was applied.

Write's Microsoft-header queue row still describes the removed declarations.
That register is held by another worker; the owning environment and writer must
refresh it before deleting the donor or retiring debt. No queue row was edited
and no debt retirement is claimed. Keep file scope
Code/GameEngine/Source/GameNetwork/Rva00594C12Write.cpp and RVA 0x00594C12 until
confirmed publication, then release them with the earlier prerequisite scopes.

The complete pending path audit was repeated for the additional Write edit:
origin/master..6015a8b4c3 plus this staged prerequisite, against fetched origin
27b23d675b8e46e096fc697af711003cf06c29f3, distinguishing incoming changes by
the outgoing merge-base diff. There are still no deleted or renamed sources,
ledger repoints or changed path consumers. Active tool/hook/workflow, build,
source/header, registry and doxygen searches find only the intended local debug
includes, existing Write routing/SDK row and seed's historical marker paths.
No active consumer repair or historical EA path rewrite is needed.

Updated session total: nine verified prerequisites, 30 affected existing rows
and 4172 standalone retail bytes. The six compatible normal trial subsets
contain 64 rows/6202 retail bytes in total. Actual merges/files removed/new
matched bytes remain zero. The previous five pending commits were held by the
shared publisher cooldown, not rejected by verification; this prerequisite
retries publication in the same command as its commit. Runner-held claims and
the exact audited range are documented here for settlement after landing.
