# Camera transform 0x00102F83: k-scan bank (2026-10-20, claude-opus-5-5)

Symbol `?rva00102F83@W3DCamTransform@@QAEXPAUCameraTransformInput@@@Z`, 4299 B,
RET4, frame `lea ebp,[esp-0x74]; sub esp,0x88`. WB twin 0x7E3040
(`tools/wb_show.py wb:0x7E3040`). Home `Code/GameEngineDevice/Source/W3DDevice/
GameClient/W3DCamTransform.cpp` (holds 0x102B83 transitionLiveMode only).
cl line is unchanged from the 2026-10-19 bank (`/O1 /G7 /arch:SSE /MD`, see that
handoff).

Scored with `permute.Scorer` fitness (0.5 mnemonic + 0.3 instruction + 0.2 byte).

| Body | fit | len | hunks |
|---|---:|---:|---:|
| previous stash (gpt-6.1-sol) | 0.8872 | | |
| + constraint `x` local (cameraMax then cameraMin on one local) | 0.8826* | | |
| + Matrix3D(axis,angle) ctor with separate `cosf`/`sinf` locals | 0.8907 | | |
| + 24 unused int locals | 0.9019 | | |
| + 56 unused int locals (banked) | 0.9045 | 4282 | 82 |

\* measured on the intermediate b2 body, which also had other changes.

## What the levers fixed

- Constraint block at +0x1EF: one float local for the X clamp.
- Pitch-matrix build: the WWMath-shaped ctor, with `c`/`s` declared before the
  rows, matches retail's cos/sin order and its spills.
- Shake / final rotate block (+0xF67..+0x1003) and +0x5C2..+0x5E8: these follow
  operand rank, so the 56 padding locals fix them. In the k-scan from 0 to 63,
  k=56 was best and k=24 next.

## Residue (k56 regions, retail offsets)

- 2AD: zoom Z multiply operand order.
- 39A/3C0/3CF: angle-matrix slot assignment. Retail Row1 = [0x4c],[0x40],[0x38]
  and Row2 = [0x48],[0x34],[0x64]. Ours swaps Row1[0]<->Row1[2] and
  Row2[0]<->Row2[2]. No k in 1..63 fixes Row2; only k=27 mod 32 fixes Row1.
  This points to a structural numbering difference, not a count.
- 4DD..561: pos-add commutative order. Retail keeps targetPos in memory with no
  reload after findObjectByID.
- 61A..7CA: second-matrix branch.
- 80F..AA4: retail computes `(s - t)*inv + t` with memory operands in both pitch
  branches. Retail also keeps targetPos.Z (xmm0) and sourcePos.Z (xmm1) live
  across the join into the positionHold block at +0x9AD. Ours reloads both and
  tail-merges the Y store.
- B8D..C8A and D7E..DE0: slaved/lookup tail.

## Disproven (each scored against the 0.8907/0.9045 bases)

- Control flow: WB liveCamera branch order without `targetHeight` (w1/w2) and
  with `sourcePos *= factor` (w2); sourcePos-first with `targetHeight` (w3).
  Removing the farm levers in the pitch branches (ternary Y, `_ReadWriteBarrier`)
  also regresses: 0.869-0.880.
- Lifetime: constraint locals; the k-scan of 0..63 padding locals (per-site
  windows: Row2 is never fixed).
- Types/layout: Matrix3D built with operator[] axis access (c2/c6), and four
  mulVector3 shapes (member vs operator[], Set vs direct writes, inline vs
  forceinline).
- Order: all 36 mulVector3 term permutations (inert: add chains are
  canonicalized by rank).
- Callee visibility: inline WWMath `Set(axis,angle)` -> `Set(axis,s,c)` chain
  (c1/c3, also under the k-scan).
- Flags: `tools/permute.py --flags 0x00102F83` closed nothing.

## Next angle

Make targetPos behave as memory the way retail does. Two ideas: route the
interpolation through an inline helper that takes `Vector3&`/`const Vector3&`
(a WWMath Lerp-style call), or create the Row2 matrix symbols in a different
order (build the matrix through a temporary Matrix3D that is copied, not
constructed in place).
