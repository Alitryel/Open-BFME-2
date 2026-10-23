# 0x102F83 W3DCamTransform::rva00102F83, round r64/r65 (2026-10-21)

The bank is unchanged: `reverse/attempts/0x00102f83.cpp`, **0.91326**.
- Its source is `build/b4-102f83/r63/best1.cpp`.
- Fingerprint (ar, ld, sum order) = (11, 13, ZYX), len 4254, rdtot 188.
- Retail: (22, 12, XZY), len 4299.
- Read the r63 handoff first.

## Residue, sharpened: the candidacy swap
**Retail:**
- s.X/s.Y/t.X/t.Y are memory everywhere.
- Only s.Z (xmm1) and t.Z (xmm0) are register candidates, live into the 0x9ad hold join.
- xmm7 holds the 1.0 constant. It is hoisted before `if(realZoom)` and spilled to [ebp+0x7c] across isLetterBoxed.

**Ours:**
- t.X is in xmm0, t.Y in xmm1, s.Z in xmm5.
- t.Z is memory [ebp+0x60].

`r64/det4.py` prints the xmm reload offsets after calls in 0x540-0xa00:
- retail `- 64 64,7c - 64 - 70`
- bank `5c,58 64 64,7c - 64 - 70,5c,58`

## Length (-45 B) comes from the realZoom shape
**Retail uses a single realZoom test:**
1. `fxPitch` is computed in xmm0 and stored to [ebx+0xa0].
2. Then `movss xmm2,1.0; divss xmm2,xmm0`, a lerp with memory operands.
3. `0x8b3 movss xmm0,[ebp+0x60]; jmp 0x9ad`.

**The retail else path:**
- `0x8bd comiss xmm7,[ebx+0xa0]; jae 0x90c; cmp live; jne 0x915`.
- 0x8cf is the lerp with `divss xmm7,[ebx+0xa0]`.
- 0x90c goes to the height arm (0x992) when not live.
- The live arm ends `jmp 0x8b3`.

**The bank's two-if form (the W11 lever, +0.020 mean):**
- It retests [ebx+0x8c] at 0x86c and reloads 1.0 into xmm7.
- It tail-merges (`0x8e2 jmp 0x897`).
- So the two-if form scores higher but cannot be the source shape. The source is single-if with fxPitch forwarded in a register.

## Disproven this round
- **Single-if factorial 2^11** (`build/b4-102f83/r64/bf/gen.py` on `r64/si/s0.cpp`, `res.txt`). Best is the base, 0.88893. None reached the retail det4 pattern. Mean effects:

  | Factor | Mean effect |
  |---|---|
  | K1 | 0 |
  | K2 | -0.0008 |
  | K3 | +0.005 |
  | K4 | -0.003 |
  | K5 | -0.006 |
  | K6 | -0.027 |
  | K7 | -0.050 |
  | K8 | -0.0008 |
  | K9 | -0.024 |
  | K10 | +0.005 |
  | K11 | +0.009 |

- **`lp/`, `ab/` families.**
  - ab a000100 reaches 0.91421 at retail length 4299.
  - It is **semantically wrong**: never bank it.
- **Commutative operand swaps on the bank** (`r65/gz.py`): all 0.91326.
  - The 0x2ad operand order (retail zoom*offset.Z) follows FactCanonSort keys, as recipes.md "c2 3077 levers" says, not source spelling.
- **offset*zoom spellings** (`r65/gz2.py`):
  - f4 is inert;
  - operator*, Set, temp and `*=` forms give 0.76-0.82.
- **Identical escapes.** Retail has the same four Look_At lea sites, so escapes do not explain the residue (r63).

## Shape references
- ZH `W3DView::buildCameraTransform`: `reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DView.cpp:259`.
- BFME1 attempt `reference/open-bfme-1/targets/game/reverse/attempts/0x006e0580.cpp:148-300`.
  - It uses `Coord3D &pos`, a `positionY` local, block scope, a t.Z chain and an else-if chain.

## Next: let the c2 allocator say why
Plan (not started):
1. Adapt the 0x5881DB tracer (`reverse/attempt_support/0x005881db-c2trace-20261021/`, winedbg over c2.dll at base 0x10700000):
   - copy `*.txt` to `build/c2tr-102f83/` without the suffix;
   - set ROOT in wdbg.py (and the `sys.path` lines) to `/work4/Open-BFME-2`;
   - change the `updateMeleeAttack` name filter to `rva00102F83`.
2. On the bank, use `rec7.py` at round 1 to dump the records (w3 priority, w9 refs, w10/w11 blocks, +0x40 cost) for the sourcePos/targetPos pieces.
3. Force t.X/t.Y (and s.X/s.Y) to spill (`slotmove2.py name@round`, `force.py` cost edits) and score with `sc2.py`.
4. If forcing them approaches retail (and t.Z takes a register), the deciding w9/cost tells which reference counts the source must change. Search source factors that move exactly those counts.

The two-if/single-if contradiction above means the forced run should start from the single-if s0 body as well as from the bank.
