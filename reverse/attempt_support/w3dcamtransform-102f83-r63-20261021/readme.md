# 0x102F83 W3DCamTransform::rva00102F83, round r63 (2026-10-21)

The bank `reverse/attempts/0x00102f83.cpp` rose from 0.91227 (r61) to **0.91326**.
- Fingerprint: (ar, ld, fsqrt order) = (11, 13, ZYX), rdtot 188.
- Retail: (22, 12, XZY), rdtot 0.
- Score with `build/b4-102f83/sc2.py` (fitness, len, fingerprint, rdtot).
- `r63/det.py` prints RELOAD or mem for t.X/t.Y after the `findObjectByID` push.
- Read the r62, r61 and r55 handoffs first.

Compiler: MSVC 7.1 `/O1 /G7 /arch:SSE /DNDEBUG /MD`, no EH, no /GL. The `// cl:` line is in the bank.

## Residue (unchanged in kind)
Retail keeps sourcePos.X/Y (ebp+0x68/6c) and targetPos.X/Y (ebp+0x58/5c) memory-resident everywhere.
- Every translate statement is load, add, store, in source order.
- Retail's xmm candidates are only s.Z and t.Z (t.Z loaded at the 0x8b3 join).

Ours makes t.X/t.Y xmm candidates:
- the t.Y load is hoisted in the translate;
- they are reloaded after `findObjectByID` (+0x561), at the joins 0x87f/0x890 and 0x94c/0x951, and in the hold `t += delta`.

Frame slot reference counts (retail / ours):

| slot | 0x58 | 0x5c | 0x60 | 0x68 | 0x6c |
|---|---|---|---|---|---|
| retail | 23 | 19 | 11 | 28 | 24 |
| ours | 19 | 15 | 13 | 26 | 22 |

## Best body levers (factorial 2^10 on the single-if s0, `r63/gen.py`, `f.res`)
- Two-if realZoom (W11, +0.020 mean): the clamp and fxPitch first, then `if(realZoom)`. This is the dominant lever.
- Division-form realZoom lerp (W3).
- `addXY(Vector3&,const Coord3D&)` translate helper (W6, +0.007 mean).
- Inline else lerp (W8).
- `Vector3 delta=v->source-sourcePos;` (W9).
- WB live/join order W1: -0.008 mean. Double-live W2: inert.

## New evidence this round
- **The translate is direct field access in retail.**
  - Retail reads `v->pos.x` as `[edi]` (edi = &v->pos, CSE'd from the shake add) and `v->pos.y` as `[ebx+0x50]`.
  - The `addXY` reference helper gives `[edi+4]`, so the helper is a compensating lever, not source.
  - Direct adds (`r63/dx/d1`, W6=0 in f.res: best x0000000001 0.91179) restore `[ebx+0x50]` and the retail frame (t at 0x58).
  - They still hoist the t.Y load and keep t.Y in xmm1.
  - **Next sessions should prefer direct adds** and find the other cause.
- **Escape ablation (`cp/`, `es/`).** t.X/t.Y become memory (det mem) only when all three Look_At address escapes (mode2, main, nearAdjust) are gone. Any one remaining escape gives RELOAD.
  - Retail has the same four lea escape sites (0x1bb, 0xae2 transitionLiveMode, 0xb73, 0x106a), so escapes alone do not explain the residue.
  - A visible non-leaking Look_At body in the TU: e1 0.7968, e1n 0.83905 (mem, but the frame is reshuffled and t.X is const-propagated).
  - A leaking Look_At body (e3/e3n): RELOAD, worse.
  - Dropping the transitionLiveMode body (e2): inert.
- **Alias probe (`build/b4-102f83/pr3/`).** MSVC 7.1 hoists `v->pos` loads above stores to s/t even after an earlier `sink(&sourcePos)` (a global escape). The retail ordering is therefore not an aliasing effect.
- **A Vector3 destructor is a red herring.**
  - A trivial `~Vector3(){}` makes MSVC 7.1 emit `operator-` out of line (W9 temp, 37 calls against retail's 36).
  - That fifth escape flips det to mem: dt_best1 0.87072, (15,11).
  - The 2^10 factorial with the dtor (`fd.res`) peaks at 0.91227, where the dtor is inert.
- **The real WWMath `vector3.h`** (reference/open-bfme-1) in place of the shim is byte-identical (rv/a=b, c=d).
  - `sourcePos=v->pos` (Coord3D operator=) is required.
  - `Set(pos.x,..)` gives 0.81564; fieldwise assignment gives 0.86455.

## Disproven this round (by family)
- **Control flow:**
  - single-if WB plan: at most 0.88893;
  - mode2 as if/else (S1): inert;
  - nested nearAdjust (S3): inert;
  - if-form object (W10): -0.0045;
  - WB join (W1).
- **Variable lifetime and scope:**
  - mode2 block-scoped own locals (m2): 0.85124, separate slots, while retail shares them;
  - nearPitch local (S5): -0.0067;
  - `Matrix3D *transform` local (S2): +0.0018 mean, not best;
  - sink weights (sk.res): best 0.91177.
- **Types and layout:** real vector3.h (inert); Vector3 dtor (de-inlines operator-); WB live-arm `Vector3 p1/p2` + `Vector3::Distance` (wd/a-e, 0.85752-0.88873).
- **Expression forms:**
  - mode2 `Set(s.X,s.Y,0)` (S6): -0.022;
  - `(sourcePos-targetPos).Length()` (S7): -0.029;
  - adjustPitch helper on the else arm (S8);
  - `targetPos+=delta` (S4/W7).
- **Callee visibility and inlining:**
  - inline reference helpers at each t.X/t.Y site (hp/, 2^8): all RELOAD, base best;
  - Look_At body visible, leaking or not;
  - transitionLiveMode body hidden.
- **Compiler settings:**
  - /Os /Ob1 /Gy /Gs /GF /G6: inert;
  - /Op /O2 /Oy- /Ot /Oi /Oa /Ow /Og-: worse;
  - /QIfist does not compile.

## Next ideas (untested)
1. Start from direct translate adds (x0000000001 family) and re-run the hold, join and Look_At factors on that base. The current best is tuned around the addXY compensation.
2. Ask why t.X/t.Y lose candidacy in retail while s.Z/t.Z keep it.
   - Cut a probe with the real control flow: translate, then findObjectByID, then live/hold arms, then Look_At(&s,&t) twice. Keep targetPos non-constant (no `Set(0,0,0)` fold).
   - Vary the reference weights of t.X vs t.Z per region.
3. The XZY distance sum order (ours ZYX) is a numbering clue for the delta temp. Try the delta built as `v->source; delta-=v->target` vs a `Vector3::Distance` call on v->source/v->target with the direct-add base.
