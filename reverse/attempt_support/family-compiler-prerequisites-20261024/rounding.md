# x87 rounding family, 2026-10-24

No exact C++ body and no production change. Scope: fast_float2long_round at
0x0015F520 (13B) and Gen_008F7CD0::bfmeCellExtent8F74E0 at0x007398A0 (41B).
The original ledger source names and all existing code remain unchanged.

## Best independent lead

Pinned Clang23 with genuine __builtin_lrintf and -fno-math-errno,
-mno-sse,-mno-sse2,-mfpmath=387 emits a13-byte scalar conversion:

    50 d9442408 db1c24 8b0424 59 c3

Native is identical except first byte51 (PUSH ECX instead of PUSH EAX).
Both use dword FISTP, and the emitted builtin's conversion instruction obeys
actual x87 rounding control; no truncating-cast equivalence or bounded-input
precondition is asserted. There are no relocations. Candidate leaf_0_0.cpp
and object are the strongest semantic guide, not a matching body.

Official LLVM X86FrameLowering::emitSPUpdate lines314-324 explicitly chooses
EAX for slot-size prologue stack allocation, independently explaining this
residue rather than suggesting expression ordering will close it:
https://raw.githubusercontent.com/llvm/llvm-project/main/llvm/lib/Target/X86/X86FrameLowering.cpp
This is current upstream corroboration, not proof of an exhaustive compiler
option impossibility. No compiler modification, opcode edit, fake live-in,
new parameter, explicit frame manipulation, or testing-only register-reserve
option was used to change that choice.

## Independent controls

- O1 and ordinary O2 give the same13B and genuine FISTP dword.
- strict floating-point/frounding-math controls call external lrintf instead.
- no_caller_saved_registers requests stronger preservation than native and
  emits15B, using ADD ESP4 instead of native POP ECX.
- preserve_most similarly emits15B; preserve_all is ignored/not a solution
  under this target and preserves the wrong13B shape; alternate ordinary
  calling conventions do not close the first byte and some alter RET cleanup.
- MSVC RTM/SP1/DDK4035 /QIfist tests use qword FISTP and16B bodies for long,
  int,unsigned casts; short adds narrowing. This changes overflow behavior and
  is not a valid full-domain replacement for native dword FISTP.
- Whole41B ceil wrapper with genuine builtin conversion emits39/40B under
  frame/size controls, with different stack allocation/store homes and direct
  _ceil REL32 instead of native imported IAT call. It is not exact.

Microsoft documents /QIfist's current-FPU-rounding behavior and warns against
using it for required truncation; that does not resolve its qword lowering:
https://learn.microsoft.com/en-us/cpp/build/reference/qifist-suppress-ftol?view=msvc-170

## Reproduce

Use existing Python314, PYTHONHOME=C:/Python314 and
PYTHONPATH=<repo>/build/python-deps. The trial.py,abi_trial.py,qifist_trial.py
and ceil_trial.py files use compiler_command and unique scratch outputs only.
They never call build.compile_source and never touch build/match. Logs with
full bytes/relocations/disassembly are adjacent. The helper's actual owning
Radar source is large and its inline asm also feeds neighboring rowed bodies;
changing the full TU compiler without revalidating those would be unsound.

No add_match, ledger, Code, symbol, baseline, gate, source-header or reference
edit was made. Both investigation claims are released when this handoff ends.

Native PUSH ECX allocates the result slot; FISTP overwrites that slot and
POP ECX loads the result. It does not preserve incoming ECX. Such stronger
preservation trials are diagnostics, not evidence for a changed native ABI.
