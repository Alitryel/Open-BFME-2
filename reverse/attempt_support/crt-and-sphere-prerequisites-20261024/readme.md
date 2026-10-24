# CRT multiply and sphere-square-root prerequisites, 2026-10-24

Inputs: BFME2 worker5c7cb7f78b, verified reference32774ab03393709a7f14331ba8d98d281a55ffd9; RTM, SP1, DDK4035 and pinnedclang23-x86 compiler profiles, unchanged retail image and verifier. No production source, ledger, pin or baseline was changed. All experimental objects were isolated under ignored build/, using compiler_command directly; build/match was not injected.

## CRT multiply: complete52B at00629580

The existing library owner and stronger prior bank
`reverse/attempt_support/long-multiply-clang23-20261023/` remain authoritative. Native requires two64-bit stack inputs, EDX:EAX modulo64-bit result, RET16, a no-save zero-high-word fast path, slow-only EBX save and three unsigned MUL instructions.

New independent RTM/SP1/DDK controls for the ordinary and low-first forms are73B and recursively call the very __allmul runtime being reconstructed; full64-bit cross terms give112B/four recursive calls. Their ordinary stdcall name also gains @16, unlike the native public helper. These are invalid implementations for replacement, never banked partial recoveries. The diagnostic source documents that refusal. Clang preserves the genuine public name and ABI, but ordinary/low-first forms are45/55B and full64-bit cross terms collapse to31B with the native fast path removed.

The new control set tests the concrete merged-restore hypothesis beyond the prior bare shrink-wrap control: enable-shrink-wrap=true plus enable-shrink-wrap-region-split=true, independently disabling tail merge and branch folding, on both prior clean and stack-word forms with/without a likely-fast-path annotation. All16 controls remain45B/53B. They keep entry callee-save pushes and IMUL cross terms. No input restrictions, false preserved-register output, fake high-half use or new calling convention were added.

The pinned compiler's post-shrink-wrap MIR is preserved. It reports empty save/restore points and entry loads from fixed-stack argument objects. Current LLVM [ShrinkWrap.cpp](https://raw.githubusercontent.com/llvm/llvm-project/main/llvm/lib/CodeGen/ShrinkWrap.cpp) classifies frame-index operands as frame-related; this is consistent with the observed refusal to sink the save past incoming-argument loads. This explanatory source is current upstream, not asserted to be an audited copy of the exact pinned compiler revision. The MIR and28 native compiles are direct evidence. [X86FrameLowering.cpp](https://raw.githubusercontent.com/llvm/llvm-project/main/llvm/lib/Target/X86/X86FrameLowering.cpp) does not establish a blanket Windows ban on shrink wrapping; avoid that inaccurate explanation.

Remaining prerequisite: legitimate instruction selection for three native unsigned MULs and save placement that can remain after pre-branch stack-argument reads. Restore-region splitting, ordinary lifetime rearrangement and the independent MSVC profiles do not provide it. No new compiler, instruction emitter or verifier relaxation was introduced.

## Sphere family: complete112B at0006F400 and277B at0019BE00

The existing donor-based SphereClassReCenter.cpp and SphereClassAddSphere.cpp remain byte-exact, with their small x87 FSQRT helper retained. Native computes the displacement and dot product with single-precision SSE, spills the input to an already-dead incoming parameter slot, executes FLD/FSQRT/FSTP to a local float slot, then resumes SSE arithmetic. Target offsets and operations are direct disassembly facts; SphereClass/Vector3 names and semantic relationships remain their prior donor provenance.

Tested54 full-TU controls: ordinary return/local sqrt(double), sqrtf, genuine local volatile input/output single-precision rounding forms, precise /Op, and independent SP1/DDK/Clang profiles. RTM/SP1/DDK plain sqrt folds preceding arithmetic into x87: ReCenter72B and AddSphere300B. Input/output float stores recover the SSE arithmetic boundary but use different slots/frame/register scheduling: ReCenter115B and AddSphere273B. Volatile objects here model native float rounding and local spills only; they access no global/caller-owned data. They do not match and were not installed. Precise /Op emits an extra __CIsqrt call (unresolved in these diagnostics), not native inline FSQRT. Clang candidates are120/142B and272/298B. No new partial score is claimed from length proximity.

The patch preserves the resumable diagnostic helper change; sphere-controls.tsv gives every tested size and refusal. The remaining prerequisite is expressing the native SSE-to-x87-to-SSE boundary with the same slot reuse and operation scheduling under the genuine ABI, without manual stack-slot access, assembly, input-domain narrowing or hidden extra calls. Existing source is unchanged and no C++ coverage gain is claimed.
