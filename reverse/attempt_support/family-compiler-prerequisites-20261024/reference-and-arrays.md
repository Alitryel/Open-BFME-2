# Reference and CRT prerequisite refresh, 2026-10-24

BFME2 revision: 2c7d0eefe57f6d5c34c828abbbb3341f722e3ac1. Donor: 32774ab03393709a7f14331ba8d98d281a55ffd9.
No production source, ledger, symbol, baseline or verifier was changed.

BFME1 scan checked 38,788 donors: 5,525 placements all claimed, 5,516 independent-boundary controls, 617 near comparisons; ranked/near each serve zero. Named lift lane completed via Windows extended paths: 146 lifted bodies / 105,306 B, 103 servable / 79,182 B. These are source leads, not BFME2 C++ progress.

Forced normal ZH discovery rebuild under the long checkout emitted 311 objects and failed 676 of 987 TUs. About 593 errors specifically report stl/_prolog.h Invalid argument, a Windows path-length prerequisite; this does not refute upstream's 918 usable short-path objects. Other failures include known SDK and obsolete-source errors. No stale failed object was retained. Fresh match checked 7,550 functions: 498 exact-unique claimed, 453 exact-multi, 1,226 near; zero packets. Logs remain in this folder. A bounded small-emission search of the earlier 318-object cache found zero free patterns among 4,578 eligible 8-23B symbols / 1,081 distinct body/mask patterns. That old-cache result is explicitly bounded, not a current full-reference exhaustion claim.

## ArrayUnwind independent compiler controls

Read the existing array-unwind-clang23-20261023 bank first. Its Clang23 result already proves native free-thiscall callback ABI, but the94B parent remains blocked on legacy __SEH_prolog/epilog lowering. I did not repeat its source or optimization variants.

New isolated controls tested pinned vc71-sp1 and vc71-ddk-4035. Both reject the free-thiscall callback typedef with C4234. Diagnostic-only suppression compiles the identical12B body ff742404ff54240c59c20800 under ?ArrayCallbackControl@@YGXPAXP6AX0@Z@Z. P6A and the stack push demonstrate cdecl callback ABI, so these compiler versions do not supply a native-SEH plus genuine-callback combination either. No suppressed diagnostic source is eligible for production or a body claim. Source/object hashes are in array_abi/results.json; unique compiler_command outputs only, shared build/match untouched. The0x6290B2 claim was released.

Microsoft's primary diagnostic documentation explains that C4234 marks an unimplemented keyword, and thiscall documentation distinguishes ECX this from stack parameters:
https://learn.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-4-c4234?view=msvc-170
https://learn.microsoft.com/en-us/cpp/cpp/thiscall?view=msvc-170

Independent backend context: LLVM main X86WinEHState.cpp, emitExceptionRegistrationRecord/linkExceptionRegistration/unlinkExceptionRegistration, explicitly constructs the registration and stores its link at FS:0. This corroborates the banked inline-registration shape but is not claimed as source provenance for the pinned compiler binary, nor proof that every backend option has been exhausted:
https://github.com/llvm/llvm-project/blob/main/llvm/lib/Target/X86/X86WinEHState.cpp

Native four94/96/98/102B iterator-family bodies all rely on the legacy frame helper protocol. A member-function-pointer substitution changes public callback ABI/type; hand-generated frames, synthesized helper-prologue calls or raw assembly would bypass the prerequisite rather than solve clean-C++ lowering. No such workaround was tried. Unsigned division6295C0 was already owned by another family seat, so no competing trial or claim was made.
