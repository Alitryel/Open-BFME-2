# Clean-room MMX average first intrinsic control, 2026-10-24

Target: AverageBlock_MMX at0x1D76E0,84B, in the two-row AverageBlockMmx.cpp
owner beside the unchanged88B MMX_idct1. Only approved specs001d76e0 and
001d45f0, retail and existing repository code were read. No external decoder
source or derivative was accessed.

One complete-file genuine-MMX control implements the specified8x8 byte
average into64 words using unpack-byte, add-word and arithmetic-shift intrinsics.
Packed memory views express potentially unaligned source/output memory.
No EMMS, stronger register-preservation contract, input restriction, artificial
volatile or instruction emitter was introduced. This is diagnostic source,
not a recovered or runtime-verified body.

The ordinary pinned VC7.1 profile emits92B versus native84B, first difference
at+3: AND ESP,-8 alignment instead of native PUSH ESI/PUSH EDI, a different
integer register web with a shared source-base delta, and MM2 zero versus
nativeMM7. Low/high vector allocation and instruction interleaving also differ.
There are no unresolved calls. The whole production source was restored exactly.

This first control does not exhaust the source/lifetime or compiler hypotheses.
The prior CopyBlockMMX bank documents scalar-backed vector lifetime as a way
to avoid alignment in a different function; that is a possible next independent
AverageBlock experiment, not a result already proven here. No partial score or
matched-row change is claimed. Private diagnostics: build/vp6-average/result.json.
