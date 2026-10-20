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

## Session r54 (2026-10-20, claude-opus-5-5): all disproven, bank unchanged (0.8782)
Families (scratch, bank as base, none beat 0.87820/46 regions):
- f1 (128): ZH-style mulVector3 (copy x,y,z then assign; ~0.78), sourcePos*=factor,
  if-form object lookup, translate order, live-block order, targetPos field init,
  targetPos.X=targetPos.X+... : inert or worse.
- f2: WB literal condition `live && (!live || !object || flag)` folds (inert);
  no targetHeight +/- parens; WB sourcePos-first live-block order.
- f3: pointer locals sp/tp, inline translate helper, `const Coord3D *pos` local: 0.80-0.87,
  block-1 store order unchanged.
- f4: 1-12 dead Vector3 locals with field stores (piece budget): block 1 unchanged.
- f5 (134): FP paren nodes at factor, zoom products, fov, live Z, mulVector3 rows,
  *=factor and +=pos spelled as (a*b)/(a+b), matrix ctor term: best = bank.
- Declaring sourcePos/targetPos after the mode==4 block (WB position), split decls,
  reversed order: +0.00005 at best.
- Vector3::operator[] for block-1 fields / *=factor loop: folds identical (loop 0.78).
- permute.py --flags: closed 0 of 1.
Probes p1/p2 (function cut after block 1 / after the join) keep ours' sunk-store
pattern, so later code does not cause it. lea sites of sourcePos (0x68) / targetPos
(0x58) are identical in both (4 pairs), `edi = &v->pos` identical: the block-1
difference is scheduler/dependence, not address-taken status. Operand order tell:
retail adds `pos.y + Y'` for both sourcePos.Y and targetPos.Y, ours `Y' + pos.y`
(FactCanonSort key of the [ebx+0x50] memory leaf vs temp) — not moved by parens.
Note: permute.py needs the zero-padded spelling `0x00102f83`.
Later in r54:
- f6 (14): empty liveHook(&sourcePos,v) before `if(!v->special) transitionLiveMode`
  (WB sub_7e8450 position), forms noinline/inline/extern: inert.
- f7 diagnostic: early exposeVec(&sourcePos/&targetPos) flips the Y operand order to
  retail's (`[ebx+0x50]+Y'`) but block-1 stores stay sunk; fit 0.863-0.874.
- Root cause located: ours keeps sourcePos/targetPos X/Y as globreg candidates in
  xmm0-3, reloaded after findObjectByID (+0x566) and consumed by the fxPitch arms; the
  two inversePitch arms become identical and tail-merge (`jmp +0x8bb`). Retail never
  enregisters them (memory reads in every arm); the block-1 sunk stores are a
  consequence. Open question: what disqualifies the candidates in retail (dead-local
  scan already done in earlier sessions).
- permute.py 30 min: build/permute/0x00102f83/best.cpp 0.87867 but 50 regions
  (Z*=(capped*0.75f+0.25f) form, targetPos+=delta after sourcePos=v->source): not adopted.
