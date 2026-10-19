# 0x00272FB6 Drawable ship/boat physics xform (1682 B): 2 of 418 instructions differ

Banked body: `reverse/attempts/0x00272fb6.cpp` (score 0.99). The symbol is pinned
by `reverse/symbols.csv` as a callee of `Drawable::calcPhysicsXform` (0x27BA95).
Toolchain: `/O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc`. The intended home is
`Code/GameEngine/Source/GameClient/DrawablePhysicsXformShip.cpp`, a new unit.

## Target facts and inferences
- Retail facts: size 1682 B, RET 8, `this` = Drawable, args are (const Locomotor*,
  PhysicsXformInfo&); the locomotion state lives at Drawable+0x13C.
- WorldBuilder twin (build tool `tools/wb_show.py`): `accel = vel;
  accel.normalize(); accel.scale(v)`, a dead `prevVel = pos1 - pos2`, a 3D accel
  zero, and dot products in the form `vel.x*dir->x + vel.y*dir->y`. Retail adds
  about 5 source lines and does not use WB's `(-S*(1-D))*field` grouping, which
  CSEs S*(1-D) and gives a 1657 B body.
- What took the body from 24 diffs to 2: defining `Coord3D::length` and
  `Coord3D::normalize` in the TU, as plain `inline` (they stay out of line at
  /O1). This lets VC7.1 forward vel.x/vel.y in xmm3/xmm4 and hoist the m_pitch
  load, i.e. the in-TU mod/ref effect. Coord3DInline.h set/sub/scale are used,
  without COORD3D_INLINE_ASSIGN.

## Remaining mismatch
At +0x22D (0x2731E3), in the first pitch-spring damping product:
retail `movss xmm5,[eax+8]; mulss xmm5,[ebp-0x14]`,
ours `movss xmm5,[ebp-0x14]; mulss xmm5,[eax+8]`.
VC7.1 decides which operand of a commutative mulss is loaded and which is used
from memory by a tie-break that couples across sites. Changing one spring
line's IL flips accel-roll damping and the dot products instead, never this
first site. Source operand order inside the product is canonicalized and has
no effect.

## Disproven (do not repeat)
- Damping: `-D*rate`, `rate*-D`, `-rate*D`, `D*-rate`, `-(D*rate)`, `((-D)*rate)`.
- Stiffness: `-S*(p*(1-D))`, `-(S*(..))`, `(-(..)*S)`, `-(..*S)`, `((..)*-S)`,
  and the WB grouping. Neither term order nor spring/damper locals helps; the
  locals give 18-19 diffs.
  The full 5x4x3 grid is in build/x272/search4.py.
- Assignment forms `+=`, `x = x + ...` and `x = ... + x`, on this line and
  toggled on every later `+=` site.
- Preceding code: accel.zero(), 2D vs 3D accel zero, prevVel present or absent,
  copy-init vel, accel.set(&vel), direct-v scale, `!` null tests, a ratio local,
  casting both ratio operands, scaling accel first, declaring accel after vel.
- `(1-D)` factor locals (at the line or at the top), the `1 - D` int literal,
  inline Locomotor getters, and `__declspec(noinline)` vs plain inline on
  length/normalize. These are identical.

## Leads not yet tried
- The real retail source detail at or before the first spring line, i.e. the
  ~5 extra lines retail has over WB. A different declaration point for the
  stack constant at [ebp-0x14] (PITCH_DAMPING spilled to a local) may change
  the tie-break.
- Before landing: in-TU length/normalize need markers or an absorbing decision
  (see AIWall.cpp:563/569 for the same pattern).

## Round 2 (2026-10-19, claude-opus-5-5): local-count recipe and declaration order
- docs/recipes.md:144 (local count decides commutative operand order): k inert
  `int unusedN = 0;` locals at the top of the body, k=0..80, never flips +0x22D;
  best stays the 2-diff body (k=4 and k=12 break structure, 10 regions).
- The same scan with the locals after the PITCH_DAMPING declaration, before the
  first spring line, before the object block and before ROLL_BOB_AMPLITUDE
  (k=1..30 each): no improvement, 12 to 18 memory lines.
- All 120 declaration orders of PITCH_STIFFNESS, ROLL_STIFFNESS, PITCH_DAMPING,
  ROLL_DAMPING and UNIFORM_AXIAL_DAMPING: the banked order is the only
  2-diff one; every other order gives 6 diffs or more.
