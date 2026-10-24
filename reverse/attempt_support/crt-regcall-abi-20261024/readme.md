# CRT shift helper: independent regcall ABI control

Inputs: BFME2 43103255a8, published BFME1 gitlink and clean checkout
0bf534ea7ccde110c456edb9cd2dd5dae823c953, pinned unmodified clang23-x86,
/O1 /G6 /GS- /MD. The cached controls use complete header-free translation
units, private objects only; no Code, ledger, pin, baseline or gate edit.
Native __allshl at RVA 0x00629780 and __aullshr at 0x006297A0 each own a
complete 31-byte body. Their value input is EDX:EAX, count CL, return EDX:EAX.

New hypothesis: genuine __regcall on three reordered scalar arguments
(lo, count, hi) assigns them EAX, CL, EDX, potentially avoiding the register
web of the prior regparm(3) trial. The input half is correct, but its 64-bit
return contract is ECX:EAX. The minimal independent control returning
((U64)hi << 32) | lo emits `mov ecx,edx; ret` (3 bytes). The matching
regparm(3) control in (lo, hi, count) order emits just `ret` (1 byte).
This isolates the ABI difference from control flow and register allocation.

The complete left-shift regcall control emits 52 bytes and ends by assigning
high to ECX; right-shift emits 45 bytes and likewise returns high in ECX.
They are invalid replacements regardless of size. No literal symbol binding,
ABI adapter, fake return field, fixed register, assembly or input restriction
was added. Natural compiler name: ___regcall3__probe. All four diagnostics
report candidate_exact=false and landing_verified=false.

The old regparm(3) route remains the genuine input AND return protocol;
its earlier 68 source/backend controls and the native redundant CL mask
blocker are preserved in ../family-compiler-prerequisites-20261024/shifts.md.
Those exhausted controls were not repeated, apart from the minimal new
one-byte echo control needed to isolate the return-contract comparison.
No claim of impossibility across every compiler is made.

Primary corroboration: Clang documents regcall as a distinct calling
convention. Current upstream X86CallingConv.td uses EAX, ECX, EDX, EDI, ESI
for the 32-bit regcall integer class, including return allocation. This is
context rather than an audit of the pinned compiler source; the emitted
objects are direct evidence. Regcall v4 removes EAX from the Windows
argument class and does not address this contract, so it was not tuned.
https://clang.llvm.org/docs/AttributeReference.html#regcall
https://github.com/llvm/llvm-project/blob/main/llvm/lib/Target/X86/X86CallingConv.td

The independent division prerequisite was reviewed rather than repeated:
../family-compiler-prerequisites-20261024/division.md. Current upstream
BuiltinsX86.td still has no scalar integer DIV builtin. The pinned compiler's
previous _udiv64 test already establishes the actual unsupported route;
vector division does not represent native scalar DIV and is not a new lead.
The remaining library owner is retained. This bank adds zero C++ exact bytes.

## Independent modulo-32 intrinsic route

Microsoft documents __ll_lshift and __ull_rshift on x86 as reducing the count
modulo 32. That is a narrower operation than ordinary U64 shift and therefore
a new candidate for avoiding the prior expression's extra bit-32 selection.
Two complete controls kept the correct regparm(3) native ABI, explicit count
>=64 zero path and >=32 word path, and used the documented intrinsic only in
the <32 path. Both emitted 36-byte bodies containing unresolved external
calls (___ll_lshift / ___ull_rshift); pinned Clang did not recognize the
intrinsic pragmas. Their short emitted sizes are not proximity or progress.
No header implementation containing assembly was imported. The native
explicit large-count mask remains a separate unmet requirement even if a
compiler later supports these intrinsics.
https://learn.microsoft.com/en-us/cpp/intrinsics/ll-lshift?view=msvc-170
https://learn.microsoft.com/en-us/cpp/intrinsics/ull-rshift?view=msvc-170
