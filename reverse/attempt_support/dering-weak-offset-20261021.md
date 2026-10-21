# _DeringBlockWeak_C (0x1C22C0, 1526 B): offset IV + weight helper

Session 2026-10-21 (claude-opus-5-5), after the strong twin
`_DeringBlockStrong_C` (0x1C1AD0) landed exact in
`Code/Libraries/Source/VP6/DeringBlockStrongC.cpp`. Banked body:
`reverse/attempts/0x001c22c0.cpp`, 1526 B (retail size), 7 differing bytes,
7 instructions off (bank was 56 bytes).

## What moved

| Step | Differing bytes | Instruction-span score |
|---|---|---|
| previous bank (row counter) | 56 | - |
| row-offset IV (`int off = 0; ... off += pitch;`, reads `X[off + c]`) | 36 | 19 |
| eight hand-unrolled output pixels | 34 | 12 |
| rolled output + `ClampWeight` helper in the vertical loop | 7 | 7 |

The helper must be the early-return form (`if (w < -64) return sharpen; if (w < 0)
return 0; if (w > cap) return cap; return w;`). A ternary chain and a variant
that also computes `quality + 2 * (16 - difference)` inside are byte-identical;
a helper that assigns a local and returns it is inert (same as no helper).
The same helper in the horizontal loop, abs-difference helpers in either loop and
a pixel-clamp helper all change the size.

## Remaining residue is a symbol-count effect

The 7 instructions (SIB base/index order of output stores, one stack-load order)
do not respond to spelling. They follow c2's count of **distinct variables** in
the function:

- Appending N dead `int dummyI = I;` locals at the end of the function body
  gives score 0 (exact retail bytes) for N = 81..144 and N = 305..336 on the
  banked body; the boundaries sit on multiples of 32 symbols. Dummies placed
  before the output loop shift the windows (period 64).
- One variable assigned many times adds nothing; each user local counts once even
  inside unrolled loops; a temp passed to an inline parameter adds nothing.
- Dummies are not acceptable source. The working hypothesis is that retail's
  source declares many more locals (an On2-style hand-unrolled C body with
  per-copy locals, or more inline helpers with locals).

End-dummy ruler (score per N, step 4, `build/s1w/w27.py`), without the helper:

- eight hand-unrolled output pixels with centre/right/left/below/above locals in
  pixels 0..2: 12 (N 0-48), 20, 16, 8 (N 212-304), 10;
- weight loops hand-unrolled: vertical x1 + horizontal x3: 16 then 8 from N 140;
  vertical x4: never below 16.

No shape without the helper reaches 0; with the helper the 0 window starts at
+81 symbols.

## Disproven (do not repeat)

- Weight base pointers (`up`/`down`/`left`/`right` row pointers): only one form
  keeps the size and it is inert.
- Helper keyword `inline` vs `__forceinline`: identical.
- Which pixels are locals (only the count of locals matters), declaration
  and cast spellings, cap forms, the strong twin's TU, random per-copy searches.
- Hand-unrolled vertical loop x2/x8 and horizontal x9: size changes; vertical
  x4: 27/28 B off.

## Next angles

1. Find a natural source with about 81+ more distinct symbols: per-pixel locals
   in hand-unrolled output and weight loops together with the vertical helper
   (each copy's `difference`, `weight`, pixel and product locals), or more
   helpers with their own locals (inline helper locals count; parameters fed
   temps do not). Use the end-dummy ruler on each candidate shape to see how far
   it is from a 0 window.
2. Check whether c2 counts the `ClampWeight` helper's symbols once per inline
   expansion: if so, more expansions (hand-unrolled vertical loop with the
   helper, which changed the size without it) may reach the window.
3. Scratch generators (untracked): `build/s1w/w20.py` (helper forms),
   `w25.py`/`w27.py` (end-dummy ruler), `w13.py`/`w17.py` (hand-unrolled shapes),
   `w23.py` (parallel scoring).
