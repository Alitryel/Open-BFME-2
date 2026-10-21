# _DeringBlockStrong_C (0x1C1AD0, 2030 B): row-offset IV form

Session 3 (2026-10-21, claude-opus-5-5). Continues
`dering-strong-anchors-20261021.md` and `dering-strong-bias-20261020.md`.
Banked body: `reverse/attempts/0x001c1ad0.cpp` (2030 B, exact size,
1993 equal bytes, 19 differing instructions, insn ratio 0.982).

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

## Next angles

- The pixel 2/3 product order is a c2 reassociation rank question, so it needs
  changes to the expression DAG, not spelling: weight sharing (pixel k's right
  weight is pixel k+1's left weight; try one shared weight array/local per
  boundary), `128 - ...` computed into a local, the clamp shape, and `temp` type
  (unsigned char / short).
- Scratch generators: `build/s1c/g13.py` .. `g16.py` (untracked).
