# _DeringBlockStrong_C (0x1C1AD0, 2030 B): row-offset IV form

Session 3 (2026-10-21, claude-opus-5-5). Continues
`dering-strong-anchors-20261021.md` and `dering-strong-bias-20261020.md`.
LANDED exact (2026-10-21) in `Code/Libraries/Source/VP6/DeringBlockStrongC.cpp`:
the last residue (store 2's SIB order) fell to writing the row store as eight
explicit `c = k; destination[off + c] = (unsigned char)temp[c];` statements
(see "Session 3c" below).

## Finding: a basic offset induction variable

The output loop's cursor families, their invariants and the size all match retail
once the row offset is a basic induction variable instead of `r * pitch`:

```cpp
int off = 0;
for (r = 0; r < 8; r++) {
    int temp[8];
    /* pixel k: */ int centerPixel = source[off + k]; int rightPixel = source[off + k + 1];
                   int left = ..., up = ..., down = ..., right = ...;   // weights after the loads
                   value = (... * centerPixel + down * below[off + k] + left * source[off + k - 1]
                            + up * above[off + k] + right * rightPixel + 64) >> 7; clamp into temp[k]
    for (c = 0; c < 8; c++)
        destination[off + c] = (unsigned char)temp[c];
    off += pitch;
}
```

Every earlier form (`r * pitch`, row pointers, per-pixel pointers, carried locals,
index temps, bias/mask spellings) missed at least one family anchor. This one gives
retail's S/B/A/D cursor map exactly: S 0:ecx; B 2:edi; A 2:ebx+edi; D 0:ebx+ecx,
4:ebx+ebp.

Loading `centerPixel, rightPixel` before the four weight locals (instead of after)
fixes pixel 0's schedule (rightPixel load before the `[esp+0x20] + ecx` above
address); 1985 -> 1993 equal bytes.

## Remaining residue (19 instructions)

1. Pixels 2 and 3: retail sums `... + right * rightPixel + left * leftPixel`
   (`lea edx, [edx + ebp + 0x40]`, edx = left product); ours puts the left
   product first and the right product last (`lea edx, [ebx + ebp + 0x40]`).
   Pixels 0, 1 and 4..7 already match. leftPixel there is the CSE'd stack value
   (pixel 2: [esp+0x1c], pixel 3: [esp+0x18]) in both builds.
2. Store 2: retail `mov byte ptr [ebx + edi], dl`, ours `[edi + ebx]`
   (ebx = [esp+0x60] delta, edi = B2 cursor). Stores 0 and 4 match.

## Disproven in the offset form (do not repeat)

- All 120 uniform term orders of the value sum: byte-identical (c2 sorts terms).
- Per-pixel spellings for pixels 2 and 3 (`build/s1c/g15.py`, 193 variants):
  L/C/R as `X[off + k]`, `X[k + off]`, `(X + off)[k]`, `*(X + off + k)`,
  `*(X + k + off)`, `X[off + k * 1]`; leftPixel as a local before/after centre
  and right; centre/right order. All identical to the bank.
- Pixel-local load order and placement (`g14.py`, 427 variants): only
  {centre, right} before the weights helps; adding leftPixel/belowPixel/
  abovePixel locals before the weights costs 16 bytes (2046 B).
- Store spellings `destination[c + off]`, `(destination + off)[c]`,
  `*(destination + off + c)`: identical.
- Carried locals (`g16.py`, modes L, C, LC; pre/mid/post; row or function scope):
  all much worse (C 2026-2028 B, LC 2064 B, L 1978 B).
- Accumulated sums (`g17.py`): `sum = c * centre; sum += ...` in all 24 orders,
  with or without `+ 64` in the seed, with or without a `center` weight local: the
  order is canonicalized again; 1970-1980 equal bytes, pixel 2/3 residue unchanged.
- 2D weight arrays (`g18.py`): `short horizontal[8][9]` byte-identical to 1D;
  `short vertical[9][8]` (direct or via row pointers) loses the vertical+8 anchor
  (2022 B).
- Earlier, in this form: `for` vs comma loop identical; weight row pointers
  advanced per row 2033 B; per-pixel source pointers for below and above 2046 B.

## Session 3b: pixel locals vs inline reads (1 instruction left)

c2 numbers values in creation order, and both the product order in the sum and
the base/index order of an address follow that numbering. Whether a pixel is a
local or read inline therefore moves orders that no spelling can (spelling is
canonicalized). Factorial over all 8 pixels x {none, centre, right, centre+right}
x {loads before / after weights} (`build/s1c/g19.py`..`g22.py`, 896+ variants):

- pixels 1..6 fully inline (`source[off + k]` etc. in the sum, no pixel locals)
  fix the pixel 2/3 product order (residue 1 above);
- pixels 0 and 7 keep `int centerPixel = source[off + k]; int rightPixel =
  source[off + k + 1];` before the weight locals: pixel 0 for its schedule,
  pixel 7 for the operand order in the hrow loop.

Remaining: store 2 `mov byte ptr [edi + ebx], dl`, retail `[ebx + edi]`
(retail2.s index 581; ebx = [esp+0x60] dest-below delta, edi = below cursor B2).
Stores 0 (`[ebx + ecx]`) and 4 (`[ebx + ebp]`) match.

Disproven for store 2 (all leave index 581 alone or add residue):
- all per-pixel inline/local combinations above, plus 1500 random extra
  leftPixel/belowPixel/abovePixel locals per pixel (`g26.py`): 581 never moves;
- `temp` declared in/out of the row loop, before/after `off`; `off` type and
  position; the `(unsigned char)` cast; `int c` (turns `jb` into `jl`);
- store loop forms: `destination[c + off]`, separate loop counter (int,
  unsigned, function scope), `while`, `c <= 7`, `++c`: identical; unrolled
  stores, destination row pointer, advancing destination, do-while, `!=`: much
  worse;
- 12 declaration-order toggles of the function-scope locals: only above/below
  and quality/sharpen swaps change anything, and only in the prologue;
- `below`/`above` spelled `source[off + pitch + k]` / `source[off - pitch + k]`:
  much worse.

## Session 3c: the row store (exact)

Probing the store loop showed the store 2 SIB order depends on how the row
stores enter the IR, not on the pixel code: storing only c = 1..7 already gave
retail's `[ebx + edi]`. Explicit stores `destination[off + k] = ...` (constant
index) give 2022 B, but eight `c = k; destination[off + c] =
(unsigned char)temp[c];` statements give retail's bytes exactly. Compiler flags
(24 sets), parameter/temp types (54 combinations), identifier names (72) and the
weight-loop `difference`/`weight` forms (225) were tested first and changed
nothing at store 2. The weak twin `_DeringBlockWeak_C` (0x1C22C0) may share
both the offset IV and this store shape.

## Next angles (superseded: the body landed)

- The pixel 2/3 product order is a c2 reassociation rank question, so it needs
  changes to the expression DAG, not spelling: weight sharing (pixel k's right
  weight is pixel k+1's left weight; try one shared weight array/local per
  boundary), `128 - ...` computed into a local, the clamp shape, and `temp` type
  (unsigned char / short).
- Scratch generators: `build/s1c/g13.py` .. `g16.py` (untracked).
