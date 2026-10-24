# VP6 MMX void ABI: preserve_most control

No recovered body or metric gain. Production code, ledgers, pins and compiler
profiles are unchanged. The complete existing MmxIDct.asm owner passes the
normal whole-file gate: all five bodies, 7,686 bytes, with no skipped references.

The approved clean-room specs describe five void cdecl functions. Retail saves
EDX, ECX and EBX, then overwrites EAX with the input pointer and restores only
those three saved registers. All five complete native extents and entry/tail
bytes are hashed in input-proof.json. MMX_idct3 is unreferenced, so no caller
provides evidence for overriding its documented void return contract.

The existing October 23 Clang18/19 intrinsic-body bank already rules out ordinary
cdecl, no_caller_saved_registers, preserve_all on x86, and the listed MMX
allocation/size controls for the 1,034-byte body. It remains the stronger
whole-function bank and is not overwritten here. This investigation tests the
previously unrecorded preserve_most attribute using the existing hash-pinned
clang23-x86 profile. The probe is ordinary C++ arithmetic and memory access
with the same two-pointer, void cdecl interface as the smallest native kernel;
it is a compiler-contract control, not a proposed decoder implementation.

Results with -Werror=ignored-attributes:

* preserve_most is accepted for i686-pc-windows-msvc, and preserves modified EAX
  as well as ECX/EDX. Its entry is push edx; push ecx; push eax; it restores all
  three on return. Extra EAX preservation is the byte mismatch, and shifts the
  argument offsets. The control does not need EBX; adding actual MMX work does
  not remove the obligation to preserve any modified EAX.
* no_caller_saved_registers is accepted and produces identical control bytes.
  This reproduces the earlier void-EAX result with the current pinned compiler.
* preserve_all is rejected as unsupported for this target. The warning is an
  error, so a silently ignored convention cannot appear to satisfy the ABI.

Neither successful void convention expresses the native combination of
ECX/EDX preservation with EAX scratch. The native body writes EAX, so retaining
its exact entry excludes merely avoiding EAX usage in a different allocation.
An invented return value, explicit register constraints, assembler wrappers,
naked bodies and instruction emitters are not acceptable solutions. This is a
concrete compiler/ABI prerequisite before a new full intrinsic-body experiment
using these attributes can be viable. It does not prove that every other
compiler or genuine source lifetime shape is exhausted.

Reproduction: copy reproduce.py.txt to build/vp6-abi-probe/run.py and invoke
D:/b2/w03.ps1 python build/vp6-abi-probe/run.py from the worker root. It uses
build.compiler_command only, invokes the compiler with private output paths,
and never calls build.compile_source or writes build/match. The JSON records
exact commands, compiler/package hashes, source hashes, return diagnostics and
complete probe disassemblies. No external VP6 decoder source was consulted;
only approved spec ABI headers, retail and existing in-repository evidence.
