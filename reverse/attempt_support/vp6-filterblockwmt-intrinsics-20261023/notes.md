# FilterBlock_wmt: scalar dispatch and SSE2 widening

Target: complete sole body of `Code/Libraries/Source/VP6/FilterBlockWmt.cpp`,
`_FilterBlock_wmt`, RVA `0x001D7DF0`, 465 bytes through RET `0x001D7FC0`.
Inputs: clean-room spec `reverse/vp6_cleanroom/specs/001d7df0.md`, retail,
existing BFME2 source, and pinned compiler intrinsic declarations only.
No external decoder source or BFME1 decoder donor was read.

## Selection and prior evidence

Reviewed every assembly-containing VP6 TU by instruction-family counts,
the 300-entry clean-room queue against the actual narrow-range ledger, and
live claims. 294 specs already have matched VP6 home rows; six have matched
homes elsewhere. This is not an exhaustion claim. Remaining purely scalar
assembly regions in the home inventory are processor probing/timing;
the more scalar-heavy image kernels still mix integer setup with SIMD.
ClampLevels_mmx already has multiple failed full-intrinsic trials and a
historical partial C-setup/assembly-loop bank, so it was not repeated.

Selected this 465-byte primarily scalar dispatch function because only its
bicubic widening loop requires four SSE2 operations. Both whole-file and RVA
claims were acquired under `sol-team-vp6-20261023`; no conflicting VP6 claim
was present. The target was unchanged at fetched origin/master. Prior RVA
records were a 444-byte six-variant reconstruction with unresolved branch
and scheduling differences, then the current 465-byte mixed C/assembly
landing. No prior candidate bank remained for this RVA.

## Trials and concrete new result

All builds were normal scoped `./build.sh` commands in the unchanged isolated
OrbStack seat, one at a time, BUILD_POOL=1, shared object store off. No raw
compiler invocation, shared header, runtime, wrapper, submodule, pin, ledger
row or verifier edit was made. Input BFME2 HEAD was
`47b5b044f75950245c347cee93effe2640926b89`; committed and checked-out BFME1
remained `138757e9b74645fbcbb7724a7af2764e34931e11`.

1. Standard `emmintrin.h`, original `/O2 /G6 /MD`, pointer cursors and
   eight-row countdown: 435 bytes. Real MOVDQU/zero-unpack/MOVDQU sequence,
   but the compiler added AND ESP,-16 and a 0x10C frame, changing dispatch
   buffer addressing to ESP-relative. An unnamed intrinsic expression alone
   did not prevent alignment; no named vector local was needed to cause it.
2. Same arithmetic and flags, TU-local actual compiler intrinsic declarations
   with an unaligned 16-byte `__declspec(intrin_type)` union: 511 bytes.
   No stack realignment, but ordinary FPO greatly expands argument addressing
   and epilogues. This tests real value-type alignment rather than inserting
   padding, dummy data, wrappers, aliases or register-selecting assembly.
3. Trial 2 plus admitted `/Oy-`: 449 bytes. Exactly restores PUSH EBP;
   MOV EBP,ESP; SUB ESP,0x100 and the native EBP-0x100 block position.
   The arithmetic remains genuine SSE2 and emits no helper calls or MMX.
   Only scoped flag trials were run, not a full-tree flag/header gate.

The local type experiment is a diagnostic, not a proposal to replace
compiler headers globally. Its four intrinsic function names/prototypes and
`intrin_type` are based on the compiler header; the storage union is 16
bytes with natural eight-byte alignment instead of `align(16)`. No decoder
ABI is changed. All vector loads/stores remain explicitly unaligned.
`candidate.cpp.txt` retains this third experiment. Its original introductory
assembly comment describes the production original, not the candidate.

## Remaining byte differences and reassessment

Retail has these explicit setup operations after the filter calls:

    LEA EAX,[EBP-100h]; PUSH EDI
    MOV [EBP+0Ch],8; MOV [EBP+8],EAX
    MOV EDI,[EBP+10h]; MOV ESI,[EBP+8]
    MOV ECX,8; MOV EAX,16
    PXOR XMM0,XMM0

Its loop uses XMM3 for pixels, advances ESI by the saved stride at EBP+0Ch,
advances EDI by EAX, decrements ECX, and preserves EDI. Those stack homes
exist because the original assembly block names C locals; the stride is
actually constant eight, not an unknown external field.

Trial 3 instead keeps the source in EAX, destination in ECX and count in
EDX, advances both pointers by immediates, and uses XMM1 pixels/XMM0 zero.
It also aligns the intrinsic loop to 16 bytes. Scalar dispatch preloads
pixelsPerLine earlier and has several argument/register scheduling deltas;
the call graph and zero/negative-difference branches are retained.
Thus matching frame construction did not close the whole function, and this
is not only a single SIMD register-number disagreement.

Real pointer lifetimes, callee visibility and control flow were reassessed:
all six real filter callees remain external and retain their original ABI;
there is no missing call to restore inside the widening loop. Width eight,
output row pitch sixteen and eight rows are fixed by retail/spec. Adding
volatile, fake address escapes, external barriers or dummy work just to keep
constant-stride stack stores would manufacture constraints, so none was tried.
An independent authentic source context would be needed to explain these
homes without assembly. The type-alignment result is reusable evidence,
but no proof of impossibility for every genuine C++ formulation is claimed.

Candidate and retail whole-body disassemblies are included. The object
readback utility normalizes relocation slots to zero; these slots are not
resolved retail addresses. No executable/runtime semantic test was run.
No coverage or hatch gain is claimed. Restore and byte-verify the original
465-byte production TU, then commit this evidence only.
