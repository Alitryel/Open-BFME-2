# 0x001C1AD0 DeringBlockStrong_C: weight order and IV anchors (2026-10-20, R3)

Clean room: only `reverse/vp6_cleanroom/specs/001c1ad0.md`, the 001c22c0 spec,
retail disassembly and repo code. No decoder source consulted. Flags
`/O2 /G6 /DNDEBUG /MD` (permute `--flags`: 0 of 1 closed).

Bank: `reverse/attempts/0x001c1ad0.cpp` (2046 B against 2030, 1689/2030 ordered
bytes, was 1649 in the previous bank). Previous evidence:
`dering-strong-cursor-20261020.md`, `dering-strong-followup-20261019/`.

## Established (target evidence)

- **Subtraction order.** c2 reassociates `128 - a - b - c - d` in the order the
  weight locals are declared. Declaring `left, up, down, right` per pixel gives
  retail's `128 - right - down - up - left` sequence (+37 ordered bytes, fit
  0.77616 to 0.78770).
- **The rest is the strength-reduction anchor.** Per address family, retail's
  output loop keeps cursors at source+0, below+2, above+4, dest+3, vertical+8,
  horizontal+1. Ours: source+1, below+3, above+5, dest+4, vertical+9,
  horizontal+1, so each pixel's addressing is retail's shifted one pixel late.
  Retail's per-pixel product order also differs (pixel 0: center, down, left,
  up, right; pixel 1: center, up, down, right, left); this follows the anchor.

## Per-pixel source pointer (lead, not closed)

`const unsigned char *p = source + r * pitch + k;` with two or more source
reads through `p` gives retail's source+0 anchor, but then below+1, above+3,
dest+4 (one pixel *early*), and the body shrinks to 2013 B:

| form | size | fit | ordered |
|---|---|---|---|
| LUDR arrays (`d_LUDRcp`) | 2046 | 0.78770 | 1686 |
| LUDR + row pointer `p = source + r*pitch`, `p[k]` (bank) | 2046 | 0.78848 | 1689 |
| per-pixel p only (pi3) | 2013 | 0.737 | - |
| per-pixel p, pb, pa (pi5) | 2013 | 0.77895 | 1646 |
| pi5 x 144 decl orders, best ordered `pabLDURcq` | | 0.78171 | 1652 |
| pi5 x 144, best fit `pabDULRcq` | | 0.79292 | 1607 |

A single p substitution compiles identically to the array form; 32 mixes of
array/pointer for center/right/left/below/above (with LUDR) all score 25 of 42
on the byte-load operand sequence, none better than LUDR.

## Ruled out this session (do not repeat)

- All 720 local decl orders: no effect on the source anchor.
- Advancing pointers (`s++` per pixel, with or without `sb++`, `sa++`, comma
  form, pre-biased `s = ... - 1`): 1091-1282 ordered, far worse.
- Row-local pointers indexed by k (`s[k]`, `sb[k]`, `sa[k]`): 1675, same as arrays.
- Store-loop forms, pixel counts, offset variables, integer per-pixel index
  (`i`, `j`, `m`), weight pointers (`hw`, `uw`, `dw`), `p` biased +1, `p[pitch]`,
  above/below expressed through source (ab1-6).

## Next angles (untried)

- Mixed forms per pixel (p for some pixels only) to land between LUDR (+1 late)
  and pi5 (-1 early).
- Different below/above base expressions together with per-pixel p, then rerun
  the 24 weight orders.
- Sibling 0x001C22C0 (weak, bank 0.973788): try the LUDR decl-order lever there.
