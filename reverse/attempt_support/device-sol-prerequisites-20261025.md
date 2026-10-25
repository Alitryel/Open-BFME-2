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
