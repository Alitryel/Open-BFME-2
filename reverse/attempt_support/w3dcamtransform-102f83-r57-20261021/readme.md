# W3DCamTransform 0x102F83, r57 (2026-10-21, claude-opus-5-5)

Bank improved (hack-free): reverse/attempts/0x00102f83.cpp fit 0.88522 -> 0.90858,
len 4260. Read r53, r54 and r55/r56 first (sibling dirs); nothing below repeats them.

## The lever: ZH two-if realZoom
ZH W3DView.cpp splits realZoom into two tests: the first `if (realZoom)` computes the
letterbox/zoom pitch (`pitchAdjust`, `sourcePos.Z *= ...`, `fxPitch = ...`), and a second
`if (realZoom) { inversePitch ...X/Y adjust } else if (fxPitch<=1 || live) ... else
adjustPitch(...)` does the adjustment. With it, sourcePos X/Y stop being globreg
candidates in the translate region (retail's memory-operand form there; metric ar/ld
from 8/14 to 10/14, retail 22/12). Read as block weights: the extra test changes c2's
frequency weights, so X/Y lose candidacy. The cost: the second test retests
[ebx+0x8c] (isLetterBoxed is a call), which retail does not, and the realZoom and else
adjust arms tail-merge. targetPos X/Y stay candidates (xmm0/xmm1).

Hold (h2): `Vector3 delta(source-sourcePos per axis); sourcePos=v->source;` before
`targetPos += delta` (retail stores sourcePos X/Y early), worth +0.0036 on top.

## Factorials (scratch build/b4-102f83/gen_v2..v4.py, all on base or base2)
- v2 A{single-if, two-if division, two-if inverse} x M{shim, real nested WWMath
  mulVector3} x H{h0, WB hold with operator- and +=, h2}: best a2m0h2 = 0.90858.
  Real matrix3d.h mulVector3 is always worse (0.86-0.88). The full WB hold is worse
  except with the division realZoom.
- v3 R{5 realZoom forms} x E{helper, inline division, inline inverse} x H x T{Set,
  field-wise zeroing}: every single-if form stays at 8/14 and <= 0.8857; T is inert.
- v4 on base2: L{base, WB live-block order: sourcePos XYZ += pos first} x N{targetHeight,
  per-arm `targetPos.Z += (...)`} x R{4} x E{3} x H{2} (96): base2 stays best; WB order
  0.90338, no targetHeight <= 0.888, inline else arms 0.899.

## Diagnostics (not adoptable, recorded for the mechanism)
- `_ReadWriteBarrier` at the translate and before the hold: 0.89913 (hack).
- `g_vp=&sourcePos` at entry plus `*g_fp=0` at the translate: ar/ld 16/12, so c2's
  points-to kills escaped locals at indirect stores through non-parameter pointers.
  `*g_fp=0` alone, kp() calls, empty `__asm{}`, `__asm nop`, volatile branch tests:
  inert.
- BFME1 d_006e0580 (the BFME1 build of this function) is x87, so no codegen lead.
- /O1 /G7 /arch:SSE reconfirmed against matched siblings.

## WB 0x7E3040 facts (wb.txt in scratch)
Single realZoom test in WB with division form `t+((s-t)/fxPitch)`; live block adds
sourcePos XYZ first, then targetPos XY, then `targetPos.Z += (pos.z+targetZAdjustment)`;
non-live arm `sourcePos.Z += groundLevel; targetPos.Z += (groundLevel+targetZAdjustment)`.
Its source shapes are all byte-worse here (v3, v4), so WB's single test is a debug-build
reading of what retail compiled as one test; the two-if gain must come from a
retail-faithful shape that changes weights the same way.

## Open
1. targetPos X/Y candidacy (retail memory-resident).
2. A single-test form that keeps the two-if weight effect without the retest.
3. Secondary: distance Length operand order (retail X,Z,Y).
