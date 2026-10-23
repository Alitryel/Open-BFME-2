# distSqToSegment 0x4EACF5 (+ caller distanceSq 0x4EADBA), r54 (2026-10-20, claude-opus-5-5)

No improvement: helper 197/197 nd 4 (swapped apx/apy entry pair), caller exact
but for the call. ~1,230 variants (scratch build/nbr/r54/4eacf5 g1..g10 + h.py/
run.py/show.py on variant_search.Scorer):
- Single-use scalars: the subtraction issue order is always the reverse of the
  multiply order, and the first-issued sub becomes the final addss destination;
  retail has both in the same order (apx sub and apx mul first, apy product as
  destination). No dot spelling / parentheses / declaration order breaks that
  coupling (g7/g8: strictly nd 4 or 6).
- So retail likely keeps apx/apy as a real variable (ZH Geometry.cpp's struct
  lineToPt). Any carrier that keeps them (struct, Coord3D, float[2], WWMath
  Vector2 copy) fixes the entry order but leaves a 3-value register swap (nd 12):
  dx/dy in xmm2/xmm3 and the length-squared y-difference (inline sqr param) in
  xmm4, retail xmm3/xmm4 and xmm2 (that y-difference coloured before dx/dy).
- Unmoved by dx/dy representation/position, symbol count (not mod 4), length-
  squared definition (8 forms), tail forms, dot operand order.
- Matched 3D sibling 0x6BD680 (GeometryPointLineDistSquared.cpp, x87) computes
  length squared as lineStart - lineEnd; the 2D retail helper uses lineEnd -
  lineStart and recomputes instead of reusing dx/dy.
Next: c2 register-colouring trace (_Color_4/_Globregs_4 disassemblies in
build/compiler-causal-lab-20261015/) on the struct-lineToPt variant: why the
sqr-parameter y-difference colours after dx/dy only when lineToPt is real.

## Round 2: c2 colouring trace (scratch ctr.py/sod.py, tr/, g11)
g11 (54): length-squared before/after the dot, named ly(/lx), sqr by reference,
inline Coord2D lengthSqr(): nothing beats nd 4 (scalar) / 12 (struct).
Trace (hooks GrgNewGlobreg/Color/Spillcosts/OrderGlobregs/RegAssign):
- Globreg creation follows symbol-number order: pointer params, then dx/dy
  (idx 4/5), then late-numbered dot, closest pieces and inline sqr params in
  source order (bank y-difference likely idx 11, sym 0xa6 — inferred).
- The struct form adds lineToPt.x/.y as candidates (idx 6/7, flag 0x804),
  shifting dot and later by two — consistent with g6 (pure renumbering inert).
- OrderGlobregs (0x8482F) only builds a per-class bitvector (XMM class 6) from
  the 1024-bucket globreg hash: a set, not a priority. The decision is inside
  @Color@4 (Spillcosts weights or helpers 0x82978/0x83c65/0x83d3c/0x85eb0); no
  spill occurs.
Resume: hook the end of Color's loop (or Spillcosts per globreg), dump colour and
cost per globreg for tr/bank.cpp vs tr/p1.cpp, compare dx/dy (4/5) against the
y-difference (bank 11 / struct 13).
