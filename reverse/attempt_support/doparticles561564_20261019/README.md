# doParticles 0x561564 (LightningDrawModule, 1744 B): 3-angle pass 2026-10-19

Result: partial, nd 10 -> 8, size-exact, banked in reverse/attempts/0x00561564.cpp.
Base: the 2026-10-19 .9834 bank. Flags unchanged (bank cl line). Model claude-opus-5-5.

## Lever that closed one site
New pointer-copy locals: `ShareBufferClass<Vector3> *tT0=g_00E065C8;` before `locs`,
`offset` copied from a `pointsB[j]` local in both loop heads, and `o/f/l` pointers
at the refresh AddP and the cached add. Together they close the cached-loop z add (561a9a).

## Mechanism (target-independent compiler fact, measured)
The commutative SSE operand picks rotate with the count of surviving user locals
mod 8. A chain of N pointer copies anywhere in the body gives identical code for N
and N+8. Unused locals and identifier names have no effect. Most earlier "levers"
(staging locals, helper parameter order, pointer arguments) only rotated this cycle.
Score every structural trial at all 8 shifts: `knobs.py.txt` here is the harness
(chain knobs g/Q/P/R/C/T/J/K/L/M plus a count; BASE= picks the source; 10 parallel compiles).

Cross picks across the 8 shifts, bank family (axisC stored x,y,z):
| shift | wrong |
|---|---|
| 0 | X4 Y4 |
| 1 | X2 X3 X4 Y2 Y4 |
| 2 | X1 X2 X3 Y2 Y4 |
| 3 | X1 X2 X3 Y2 |
| 4 | X1 X3 Y2 Y3 |
| 5 | X3 X4 Y2 CzP1 Y4 |
| 6 | X4 CzP1 Y4 |
| 7 | X4 CzP1 Y4 |
X1=B.y P1, X2=B.y P2, X3=B.z P1, X4=B.z P2; Y1..Y3=C.x P2, C.y P1, C.y P2; CzP1=C.z P1; Y4=C.z P2.
X1 (C.z*A.x) and X4 (C.y*A.x) are always opposite. Retail needs the rank C.y > A.x > C.z,
which this family never produces.

## Ruled out
- Types: real WWMath Vector3 and canonical Coord3D members compile the same as the TU-local Vec.
- Operand order: source operand order in the adds is canonicalized.
- Plain helpers: ZH Coord3D::crossProduct and Vector3::Cross_Product bodies give nd 15.
- Natural combinations: about 600 (axisA/axisC init, cross helper, add spellings, noise declaration orders); the floor is the bank.
- `axisC=Vector3(0,0,1)` and `axisC.Set(0,0,1)`: they create the &axisC.z register at the store,
  so B.x P2 is wrong at every shift.
- WB-literal body (pos local, combined first-particle if, zeroed noise, literal noise
  rows, explicit adds, plain crossProduct): nd 42.

## WB facts (0x1429DF0)
- axisA: computed as set(dx,dy,dz), then Coord3D::normalize is called.
- axisC: three member stores (0, 0, 1), with no temp.
- Cross products: Coord3D::crossProduct(&C,&A,&B) and (&A,&B,&C) are out-of-line cdecl calls.
  Retail inlines them (an out-of-line copy exists at 0x360C), so cross-TU inlining is possible but unproven.

## Next hypothesis
Find a form that creates the C.z address at the cross (as plain stores do) but numbers it
after the A.x/A.y loads, and score it at all 8 shifts.
