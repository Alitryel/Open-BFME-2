# W3DCamTransform 0x102F83, r53 (2026-10-20, claude-opus-5-5, ~90 min)

Bank replaced by a HACK-FREE body (scratch build/nbr/r53/102f83/best_nohack.cpp):
the previous bank's 0.9045 relied on 56 unused int locals, _ReadWriteBarrier,
an equal-arm ternary and volatile casts; stripped of those it scores 0.8601.
This body: fit 0.8782, len 4266, align 46 structural / 115 memory / 61 register
(previous hacked bank 51/100/68). Carried unchanged: WWMath::Sqrt = BFME1
wwmath.h __asm; transitionLiveMode's landed `this ? 0.0f : 0.0f`.

WB 0x7E3040-backed levers that moved it:
- C: distance = Vector3 delta=v->source; delta-=v->target; v->distance=delta.Length()
  (WB operator-= asserts 191/192, Length, fsqrt): final region 35 -> 2.
- G: real matrix3d.h Rotate_X/Y/Z bodies (tmp1/tmp2, sinf/cosf): 39 -> 31.
- M: live branch float height=tan(fxPitch)*distance; targetPos.Z=sourcePos.Z-height
  (WB local_150).
Disproven/regressing: Vector3::Distance on XY copies; WB-order hold delta; WB
division fxPitch; Set(axis,s,c); two-arg mulVector3; real Make_Identity; real
Row-wise operator= (zoom 0, distance 9, but matrix 159-179); empty 0x7E8450 call;
dropping constraint x; fxPitch spelling; named 90.0f; decl order; full matrix3d.h
include (0.70-0.83). Removing targetHeight with WB parenthesised targetPos.Z +=
(pos.z+targetZAdjustment) gives retail's tail-merged join, pitch 104 -> 94, but
live block 67 (keep for later).

Remaining wall: retail keeps sourcePos/targetPos X/Y in MEMORY (stores each result
immediately, subss xmm0,[ebp+0x58], X fully before Y), only Z enregistered across
the +0x9AD join; ours keeps X/Y in xmm0-3 interleaved and sinks stores. Same in
the +0x50D translate and live blocks. A 0..95 dead-local scan (diagnostic) never
moves these regions (period 32, k=0 best): structural, not symbol count. Angle
matrix stack slots swap (0x38/0x4C, 0x48/0x64): colouring. Next: what makes cl
treat those X/Y fields as possibly aliased with v (not scalar-replaced) — c2
tracer tools build/agU/symcreate.py, build/agW/tools/sim.py; recipes.md section
"c2 3077 levers traced on 2026-10-20".
Scratch: best.align / bank.align, edits.py greedy.py run.py sc.py, gr1/gr2.log,
ks.log, retail.asm, CGM.asm, wb.txt.
