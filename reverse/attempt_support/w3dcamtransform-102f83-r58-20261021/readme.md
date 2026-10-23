# W3DCamTransform 0x102F83, r58 (2026-10-21, claude-opus-5-5, ~120 min)

Bank improved, hack-free: reverse/attempts/0x00102f83.cpp fit 0.90858 -> 0.91179
(sc2 difflib rdtot 191). Read r53-r57 first; nothing below repeats them.

## What moved the score
1. Shaker global accessed directly twice, as retail does (WB 0x7E3040 reloads
   `[0x2246004]` before each call: rva00065E3C then Update_Camera_Shaker). The old
   `CameraShakeSystemClass *system=...` local was wrong. Dropping it alone gives
   0.88755: one fewer c1 symbol renumbers the temporaries and breaks the
   matrix/translate region +0x66a..+0x7e5.
2. Adding back exactly one natural symbol restores that numbering:
   `Matrix3D *transform=v->transform;` in the slaved-listener block (ZH W3DView.cpp:450
   uses a `transform` local there). Result 0.91179. A dead extra local at function start
   or keeping the `system` local gives identical bytes in that region, so the count matters,
   not the position. The transform local is the natural, ZH-backed choice.

After +0xb40 only +0xc02..+0xc8a differs (shaker Rotate_X/Y/Z register colouring).
Before that, the residue is still the X/Y candidacy in the pitch/translate regions.

## Disproven this session (each <= bank)
- v14: early dead zero stores of the sourcePos/targetPos X/Y/Z fields.
- v15: routing every X/Y read through forceinline/inline members (late struct-piece
  numbering, recipes c2): X/Y stay register candidates; `*=factor` and xyAdj inert.
- v16: late-numbered X/Y with 8..256 meter locals: candidacy unchanged.
- v17: shaker spellings (local, direct, `->` through a cast, reference): only direct x2 wins.

## Open wall
Retail never makes sX/sY/tX/tY globregs (xmm7=1.0 pitchAdjust spilled to +0x7c around
isLetterBoxed, xmm1=sZ, xmm0=tZ, X/Y read from memory, tX twice in the realZoom arm).
Ours: xmm7=1.0 with the same spill, but tX/tY in xmm0/xmm1, sZ in xmm5, tZ uncached.

## Next ideas (untested)
- Rerun the r55 g13 factorial and the r57 families on the new base: the symbol
  numbering changed, so earlier inert edits may act now.
- Look for more natural single symbols (ZH locals `position`, `pos`, `angle`) and test
  pairs with the transform local (numbering period looks like 1 symbol here, 32 meters
  in r56).
- Rotate_X/Y/Z colouring at +0xc02: cut it into a probe with the shakerAngles reads.
