# W3DCamTransform 0x102F83, r60 (2026-10-21, claude-opus-5-5, ~150 min over two contexts)

Bank unchanged: `reverse/attempts/0x00102f83.cpp`, fit 0.91179 (len 4262 vs 4299, rdtot 191).
Read r53-r59 and `w3dcamtransform-102f83-20261021.md` first. Scratch was `build/b4-102f83/`
(`sc2.py` scorer, `xy2.py` reload probe, `v20/base.cpp` = bank, `v32/s0.cpp` = single-if base 0.88893).

## Target facts re-confirmed (retail.s)

- Everything up to +0x508 is byte-identical to the bank (mode-2 early Look_At block,
  matrix build, both mulVector3, `*=factor`, Z store). The first divergence is the translate
  at +0x50d: retail stores sX, sY, tX, tY immediately (`movss xmm0,[edi]; addss xmm0,[ebp+0x58];
  movss [ebp+0x58],xmm0`, operands pos+value), ours keeps tX/tY in xmm0/xmm1, sinks the stores
  and reloads them after `findObjectByID` (+0x55d/+0x562).
- No integer/8-byte access to the s/t slots anywhere in retail: only movss/arith, the four
  `lea` pairs for Look_At (+0x1bb, +0xb73, +0x106a) and transitionLiveMode (+0xae2), and one
  x87 `fld [ebp+0x70]` / `fstp [ebp+0x60]` (+0x981/+0x988, tZ = sZ - height).
- Candidate sets: retail {xmm7=1.0, sZ, tZ}, X/Y memory; ours {1.0, sZ, tX, tY}, tZ memory.

## WB 0x7E3040 facts (for the next shape)

- mulVector3 is out-of-line sub_7E7310 (ret 4, locals x@-8 y@-4 z@-0xc, frame 0x10).
- realZoom tested once; pitchAdjust=1.0 inside; `sourcePos.Z=(capped*.75+.25)*Z`;
  `(s.X-t.X)/fxPitch+t.X` with fdiv.
- Live block: m_cameraSource via inline operator=, Distance on Z-zeroed copies, then
  `delta = v->source - hold` (asserts), hold += delta, v->source(+0x4c) = v->target(+0x58),
  `+0x4c += delta.X/Y`, copy back, clear +0xa8 unless +0xa9.

## Disproven this round (never repeat)

- v33: tracked-symbol cap via short-lived early locals: inert.
- v34: implicit compiler copy ctor / operator= for Vector3: 0.62-0.78, candidacy still mixed.
- v35: transitionLiveMode definition before/after/removed x Look_At through a noinline stub
  that still escapes (calls extern la_hook) x {two-if bank, single-if}: byte-identical to the
  bases (0.91179 / 0.88893). Look_At visibility via a forwarding stub changes nothing.
- v36: local `bool`/`const bool`/`int`/`Bool realZoom = v->realZoom` caching the test: c2 threads
  the retest away and the CFG behaves as single-if, all four X/Y become candidates, 0.78-0.82.
- WB Distance live copies (again): below bank.

## Still untested

- A real construct that removes only X/Y candidacy: the only known trigger is an 8-byte
  (V2f) block access to the X/Y pair (MMR, but emits int moves retail lacks). Look for a
  source access that c2 treats as overlapping X/Y and later folds to float moves (e.g. a
  Vector2/Coord2D member copy that is optimised to movss, or a union view).
- Rebuild the c2 tracer (build/agU, build/agW are gone) and dump the candidate weights for
  tX/tY at the translate on bank vs a single-if base.
- BFME 1 0x006E0580 retail read (x87 there, low value).
