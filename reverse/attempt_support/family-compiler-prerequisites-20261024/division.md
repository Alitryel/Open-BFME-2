# Unsigned CRT division recovery: backend prerequisite

BFME2 2c7d0eefe57f6d5c34c828abbbb3341f722e3ac1; verified donor pointer32774ab03393709a7f14331ba8d98d281a55ffd9.
Target: __aulldiv at0x006295C0, complete104B from native ulldiv.obj; genuine two64-bit stack arguments, EDX:EAX result, RET16. Existing prebuilt member retained.

Native algorithm divides into two paths. For high divisor0 it performs high-word32/32 division, followed by64/32 division of(remainder:low), then combines quotient words. Otherwise it right-shifts numerator and divisor until divisor fits32 bits, divides normalized64/32, multiplies quotient estimate by original divisor words and decrements on carry or overshoot. The full-word translation was checked against Python exact n//d for110,042 deterministic edge/random cases, with no artificial input narrowing. Zero divisor remains the native/C++ exceptional case.

Trials, all isolated outputs using build.compiler_command:
- Official clang23-x86, /O1 /G6 /GS- /MD, actual public __aulldiv name on stdcall function:121B, two self-calls to __aulldiv at relocation offsets49/104. This is recursively invalid as a runtime implementation, so it is not a banked partial.
- Genuine already-proven quotient-range invariants via __builtin_assume(rem<dl) and(normalized numerator high<divisor low): identical121B and recursive calls. These invariants do not restrict external inputs.
- Independent MSVC7.1 backend, same full algorithm:127B and two __aulldiv calls at40/81; ordinary stdcall spelling additionally decorates @16. Clang's literal function-name binding solves naming but not the arithmetic lowering.
- Microsoft's genuine _udiv64(unsigned __int64,unsigned,unsigned*) intrinsic would represent the exact required hardware operation on x86. Official Clang23 reports it unrecognized and emits unresolved __udiv64 rather than DIV. Adding a declaration or pragma cannot implement it.

Primary references inspected: Microsoft _udiv64 documentation https://learn.microsoft.com/en-us/cpp/intrinsics/udiv64?view=msvc-170 (introduced VS2019); LLVM BuiltinsX86.td and intrin.h contain no udiv builtin. No compiler toolchain substitution, inline assembly, byte insertion, recursion pin, fake high half or input assumption was proposed.

The signed170B __alldiv includes the same core and inherits the64/32 lowering blocker.149B __aulldvrm additionally returns quotient in EDX:EAX and remainder in EBX:ECX, beyond the ordinary scalar-return ABI, so it needs a separately supported genuine return protocol before any source claim.

Next prerequisite: a supported pinned backend intrinsic/legalization for x86 double-word unsigned division, or an independent frontend expression that actually selects DIV over EDX:EAX. A software32-bit bit-loop may be semantically correct but cannot reproduce the native instruction sequence; do not treat another recursive helper call or a narrowed32-bit dividend as progress.

Scratch proofs: aulldiv_v1.cpp, v1.txt; aulldiv_assume.cpp, assume.txt; aulldiv_msvc.cpp, msvc.txt; udiv64_intrinsic.cpp, intrinsic.txt; math_validation.txt. No production/ledger/gate changes.
