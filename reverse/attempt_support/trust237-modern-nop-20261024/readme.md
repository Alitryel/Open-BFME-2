# Patched signature check: modern NOP intrinsic controls

Target `?Rva00237D3DCheck@@YAHXZ`, RVA0x00237D3D, complete226B.
The exact assembly owner remains `Code/masm_dumps/VersionSignatureCheckPatched.asm`.
This is failed recovery evidence, not C++ exact progress. Prior patched-target,
rounds14--18 and callee-expression handoffs were read before work. Their old
MSVC7.1 intrinsic/source-shape matrices were not repeated.

## New compiler prerequisite tested

Modern Microsoft documents `__nop` as a genuine intrinsic:
https://learn.microsoft.com/en-us/cpp/intrinsics/nop?view=msvc-170 .
The hypothesis was that an already installed modern x86 compiler could provide
the independently proven sixteen-byte post-link patch in real C++ without asm,
emit, source patching or a changed target. This does not infer original source.
The source preserves all API setup/calls and the target's unconditional success.
It does not invent a consumer to keep the native dead status register alive.

* Pinned Clang23:36 controls (O1/O2/Od, frame on/off, intrinsic on/off,
  three equivalent result-declaration positions),14 distinct bodies,274--460B.
  It does not recognize this declared `__nop` as a builtin; every object has
  sixteen external ___nop call relocations and zero decoded NOP instructions.
  The emitted warning recommends intrin.h for non-builtin intrinsics; no header
  asm implementation was substituted and no unresolved call is called exact.
* Installed MSVC14.50.35717 and14.51.36231:12 controls (O1/O2/Od, frame on/off),
  four distinct bodies of200/218/240/300B. All twelve genuinely recognize __nop
  and emit sixteen decoded single-byte NOPs, with no ___nop calls. This supplies
  a real NOP producer, but none supplies the whole226-byte target. Optimized
  bodies interleave independent return materialization/register pops among the
  NOPs, combine GUID stores, change scheduling/register allocation and remove
  the unused WinVerifyTrust status. Od retains a contiguous NOP16 but is300B.

Both modern compilers are local diagnostic inputs only. No new accepted compiler
profile, production flag, verifier rule, baseline, pin or ledger row was added.
The driver replaces compiler_command's executable privately, preserves x86 ABI,
uses GS- to compare the old target, and prepends that compiler's actual directory
to PATH. It uses no headers. compiler-hashes.json identifies cl/c1xx/c2 inputs.
The Clang profile/package hashes are those already enforced by compiler_profiles.

The existing diagnostic cache refused reuse because include inventories were
unproven; several oversized bodies also correctly failed extent evaluation.
No cache receipt or copied DIR32 operand is used as landing proof. The independent
raw-object audit reads every complete function, its actual relocation list,
source/raw-function-body hashes, instruction lengths and NOP offsets. All48 bodies have
extents unequal to226, independently ruling out a whole-body exact match.
Audit results include the actual226B target hash. These are finite negative
controls, not proof that all possible C++/compiler approaches are impossible.

## Verification and handoff

Normal whole-file verification of the exact assembly owner plus VersionDestructor
and VersionInitGlobals passed40/40 functions across3 files, one data row,
21 literals plus2 empty-string references and7 named imports. Production files
were untouched; no nonmatching candidate was installed. A diagnostic candidate
and both reproducible generators are preserved as .txt evidence.

To reproduce, copy the three .py.txt drivers to ignored build/ without .txt and
run them from the repository root with the worker Python environment. The audit
expects both generators' original build/trust237-*-nop results directories.
The modern driver needs the two installed toolchain paths it explicitly names;
do not replace a missing profile silently. Full objects/results stay ignored.

The remaining prerequisite is a supported genuine C++ lowering of the complete
native dead-status/call/return sequence plus contiguous internal NOP16. New
modern NOP recognition alone is insufficient. Retain the exact ASM owner and
older stronger VC71 partial banks. Do not repeat these bounded matrices unchanged
or add asm padding, volatile artificial consumers, fake register ABI or byte
patches to claim authored C++. C++ exact delta remains0.
