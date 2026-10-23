# W3DCamTransform 0x102F83, r59 (2026-10-21, claude-opus-5-5, ~110 min)

The bank is unchanged: `reverse/attempts/0x00102f83.cpp`, fit 0.91179, length 4262 against retail's 4299.
Read r53–r58 first. Every family below scored at or below the bank. Scratch files were under
`build/cam/{g16,h1..h5}` and are not kept.

## Retail reading (target evidence, retail.s +0x7f4..+0x960)

- Retail tests `realZoom` once (`je +0x8bd`). That arm holds the letterbox block, the
  `fxPitch` store and `1.0/fxPitch` (`divss` on the just-computed register value). The X/Y lerp
  uses memory operands (`subss/addss xmm,[ebp+0x58/0x5c]`) and the arm ends with
  `movss xmm0,[ebp+0x60]` (tZ) before `jmp +0x9ad`.
- The else arm is `comiss 1.0,fxPitch; jae live-test; cmp live; jne live-block`, followed by the
  division adjust, which is also a reciprocal multiply. The compiler turns two `/p` into
  `1/p` itself (our `adjustPitch` division helper does the same), so the source spelling is
  free. The WB twin 0x7E3040 also has a single `realZoom` test and the division form.
- The two-if bank retests `[ebx+0x8c]` at +0x868 and keeps tX/tY in xmm0/xmm1 there. Retail
  keeps sX/sY/tX/tY memory-resident and sZ, tZ and the constant 1.0 (xmm7) in registers.

## Disproven this round (scores are fit; bank 0.91179)

- g16: rerun of the g13 2^10 factorial on the r58 base. Best is the base itself.
- h1: `float&` / `const float&` forceinline and inline helpers for the realZoom lerp,
  `adjustPitch`, the translate and the distance (96 variants). All inert, except `lerpD` in
  `adjustPitch` at 0.84174.
- h2: single-`if` `realZoom` (adjust form inverse/division/helper × else form ×
  `1.0f*` spelling). Best is 0.88893 (inverse in the arm, helper in the else arm). With a single `if`, all
  four X/Y become register candidates (they are reloaded after `findObjectByID`). The `1.0f*`
  spelling is inert.
- h3: WB-faithful live block (Distance on Z=0 copies, Vector3 ctor copies, dx/dy) × live-block
  statement order (bank or WB) × `targetHeight` or per-arm, on both the two-if and single-if bases (24
  variants). Best is the bank; `tdwh` gives 0.90659.
- h4: `operator[]` X/Y access in four regions. Inert or worse (0.90153/0.90922).
- h5: the two r55 "still untested" items, at the main translate and the live-block translate
  (four sites, every subset, 60 variants):
  - XY-pair struct view (`((XY2*)&sourcePos)->x+=`): byte-identical to the bank at every
    subset. MSVC sees through the cast.
  - Visible `__declspec(noinline)` helper `addXY(Vector3&,const Coord3D&)`: 0.86–0.902
    (best with the live target site only). It does not make X/Y memory-resident.
  - `float *f=&d->X; f[0]+=…` forceinline helper: 0.899 at best.
  - Struct-view forceinline helper: 0.82–0.899.

## Still untested

- The BFME 1 analogue is 0x006E0580 in Open-BFME-1, a gen dump with no matched source; its
  retail could show whether VC7.1 there also keeps X/Y in memory. That would be a read-only comparison.
- Permute on a single-if base. Its control flow is the faithful one, but it starts at 0.889, so it
  needs the X/Y candidacy fixed first.
