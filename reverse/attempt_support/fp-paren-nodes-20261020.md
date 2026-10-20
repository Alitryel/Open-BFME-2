# Floating-point parentheses are IL nodes in c2 3077 (three matches, 2026-10-20)

**Target facts:** the retail bytes of 0x004C6A20, 0x0028F326 and 0x00175E50; each body now compiles byte-exact.

**Compiler facts:** traced in c2.dll 13.10.3077, never executed outside the lab tracer.

**Structural inference:** the spellings below are the shapes that reproduce retail. The original headers and macros are not recovered.

## Mechanism

A parenthesized floating-point expression produces a paren node in the backend IL.
- On x87 it becomes machine op 617 on the stack value and emits no bytes.
- Constant folding and reassociation do not see through it until later.

These nodes are part of the post-register-allocation list schedule:
- The schedule is per basic block: `SchSchedGraph` 0xB5338, with one `SchSelectInstrs` (0xB4F08) call per cycle.
- Each cycle issues up to three instructions and at most one load.
- `SchComputeStaticPriority` (0xB550A) sets the static priority from the node's height (+0x34, shifted) and its successor count (+0x22).
- Flag bonuses come from the `_SchmdHWT` table: about +0x8000 for memory reads, plus a critical-path bit.

Node layout used by the tracer:
- +0x10: next node in the ready list
- +0x1c: the tuple
- +0x28: static priority
- +0x2c: dynamic priority
- +0x30: ready cycle

Tools (scratch): `build/xs/trace/sched_picks.py` prints the per-cycle picks and the ready list, and `sched_dump.py` prints the graph nodes.

## Cases

### 0x004C6A20 WoundArrowUpdate::update (347 B)
- **Residue:** retail issues the data reload and the target x load before the `fstp` of sqrt's result.
- **Fix:** `float length = ((float)sqrt(e));`. The two paren nodes after the call keep the `fstp` from being ready until cycle 18, so the three loads issue first, one per cycle.
- **What a plain `sqrt(e)` does:** the `fstp` pairs with the first load in cycle 16.
- **Same shape elsewhere:** `<math.h>`'s float `sqrt` → `sqrtf` chain (`return (sqrtf(_X));`, `return ((float)sqrt((double)_X));`) also makes these two nodes. Its float parameter, however, moves the argument's sum from x87 to SSE.
- **What did not work:**
  - `(double)(e)` on the argument adds a node before the call and moves the `fstp` earlier.
  - Single parentheses, an unparenthesized cast and inline helpers without parentheses are all inert.

### 0x0028F326 vision test (294 B)
- **Residue:** after `call Sin`, retail issues the first dot `fmul` before the visionAngle `movss` load. Without the fix the load ranks 0xAC00 against the `fmul`'s 0x9C00.
- **Fix:** `return (x*r.x)+(y*r.y)+(z*r.z);` in the dot helper (WB 0x41FB90). The parenthesized terms lengthen the dot chain, and the `fmul` wins.
- **Inert:** outer parentheses only, parentheses on a single term, or on two terms.

### 0x00175E50 AABoxRenderObjClass::Render (243 B; was 246 B)
- **Residue:** the row grouping in the handoff `00175e50-aabox-render-unit-fold-20261020.md`, `(y*0+z*0)+x | (y+x*0)+z*0 | (z+x*0)+y*0`.
- **Fix:** a translate whose second and third products are parenthesized:
  `m[i][3] += m[i][0]*t[0] + (m[i][1]*t[1]) + (m[i][2]*t[2]);`
  - The diagonal 1.0 products of rows 1 and 2 reach reassociation as paren nodes and are folded only afterwards, which is exactly the handoff's diagnostic.
  - Row 0's diagonal (unparenthesized) folds early.
- **Remaining y/z swap:** fixed by the translation filled X, Y, Z (`Get_?_Translation`). The canonical keys of the `y*0` and `z*0` nodes follow the pieces' symbol numbers.
- **Identity:** in the home unit, built as `Matrix3D temp; temp.Make_Identity();`. The link-view `Matrix3D(bool)` there emits 355-386 B.
- **Ruled out:** all 24 parenthesizations of the three-term sum were scanned; only `A + (B) + (C)` gives the grouping.

### 0x0055DDD1 LightningEmissionModule::getPosition (1295 B; second transform's colouring)
- **Before:** the bank, two inline copies of Zero Hour's `Inverse_Transform_Vector`.
- **The single deciding site:** the second copy's inner Z ADD. It sorted MUL(dz,A22) ahead of MUL(A02,dx), with key low halves 0xD5E0 against 0x26B8.
- **MUL key formula:** low = (k1 + 2·k2 + 0x30) & 0xFFFF over the sorted operand keys. It is verified on every row of both copies.
  - A temporary has key 0x10000 + 32·X.
  - A memory leaf through hash var H has key 0x10008 + 0x4000·(H mod 4).
  - The A02 address hash var (H787) is created in the first copy and reused in the second.
- **Fix:** `out->Z = ((A[0][2] * v->X) + A[1][2] * v->Y + A[2][2] * v->Z);` in the second copy only.
  - The parenthesized product reaches the sort as a hash-var temporary keyed above the plain products, so it leads.
  - The xmm0/1/2 colouring of dx/dy/dz then follows as a knock-on effect.
- **Prediction check:** an alternative, three extra paren pairs around the first copy's inner sum (shifting A02 to H790, mod 4 = 2), was predicted from the formula before compiling and is also exact. Two or three pairs fail, as predicted.
