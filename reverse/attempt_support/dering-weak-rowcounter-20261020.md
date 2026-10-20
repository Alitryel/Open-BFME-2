# Weak deringing: shared row counter and five pixel locals

Target `_DeringBlockWeak_C`, retail `0x001C22C0..0x001C28B6`, 1526 bytes. Inputs were the approved clean-room specs `reverse/vp6_cleanroom/specs/001c22c0.md` and `001c1ad0.md`, retail disassembly, the committed bank and its evidence (`dering-weak-flat-20261020.md` and the older folders). No external decoder source was consulted. Base commit `0023bd546f`, flags `/O2 /G6 /DNDEBUG /MD` (MSVC 13.10.3077). This is an improved bank, not a match.

## Result

| Measure | Committed bank | New bank |
| --- | ---: | ---: |
| emitted size | 1526 | 1526 |
| `align_diff` structural regions | 6 | 6 |
| memory operand differences (one is the sharpen DIR32) | 24 | 16 |
| register operand differences | 9 | 9 |
| fixed-offset differing bytes, sharpen DIR32 masked | 64 | 56 |
| ordered byte alignment, retail first, DIR32 filled | 1478/1526 | 1486/1526 |
| first differing byte | +0x2E3 | +0x2E3 |

The output loop's inner body is now byte-identical to retail as well. What remains is the output-loop prologue and the row-end cursor updates.

## Source changes

- All three row loops share one function-scope `int r` (`for (r = 0; r < N; r++)`) instead of a `for (int r ...)` per loop.
- Each output reads all five pixels (centre, right, left, below, above) into locals before its four weights (left, up, down, right).

The shared counter fixes the six commuted base/index address operands (retail writes the cursor as base): with the committed bank's two pixel locals it measures 6/20/9, without pixel locals 6/28/10. Four or five pixel locals then also fix the pixel-3 product order (6/16/9). Five pixel locals with per-loop counters measure 6/28/9.

## Gap measurement (scratch copies only, never banked)

- Throwaway stores `g_sink = (int)x;` cannot size the gap here. A store to a global changes the whole function (1542 to 1594 bytes) at every position, top, before the output loop, in the row loop or in the pixel loop.
- Throwaway uses as conditional returns (`if (x == (const unsigned char *)k) return;`) for `above`, `below`, `source` and `destination`, 1, 2, 4 and 8 of them at the top or just before the output loop, never change the output-loop spill homes or the prologue registers. Live compare blocks (`if (cap == k) cap = k;`), up to 15 at the top or between the weight loops, do not change them either. So the homes are not a use-weight gap.
- The same probes do flip the six commuted address operands to retail's order, for 7 to 12 inserted blocks (not 1 to 6, not 16), whether placed at the top or just before the output loop. The inner loop is then byte-identical to retail. The base/index order therefore follows an IL count ahead of the output loop, not a weight. Dead initialised locals instead move the pixel-3 product order, and so does the number of pixel locals, which is why the committed bank needed two or three of them and this one needs four or five.
- The shared row counter is the natural spelling that moves that count.

## Remaining mismatch

- Output-loop prologue colouring: retail keeps `below` in esi and `source` in edi; ours uses ebx and esi.
- Row-cursor spill homes: retail puts the above cursor in `above`'s own slot `[esp+0x28]`, the horizontal-weight cursor at `[esp+0x30]` and the `source + 1` cursor at `[esp+0x40]`; ours use `0x30`, `0x40` and `0x28`. The row-end update order and the IV initialisation order follow from this.

These homes were identical in every one of about 950 trials this run and last run, with only structurally broken bodies differing.

## Ruled out in this run (trials under `build/w4_1c22c0/`)

- Inert (identical code): casts in either weight loop (removing up to six `(int)hc`, adding `(int)c`, dropping `(short)`), weight expression forms (`quality + 32 - 2 * difference` and two more), initialised `weight`, two-dimensional arrays, phase scopes, inline helpers for the weight clamp or the output clip, else-block clamp and clip forms, direct table reads in the loops, `while` or `do`/`while` outer loops (same as the shared `for`), function-scope `value`, `pixel` or weight locals, function-scope row pointers, `const` pointers, counter declaration order and an unsigned shared `r`.
- Worse: a ternary cap, nested clamps, other clip forms, an absolute-difference helper (1542 bytes), per-pixel index locals or pointer locals, inner `do`/`while` loops (unrolling lost), neighbour reads through other base pointers, one shared row pointer for both weight loops, function-scope `difference` and `weight`, and the horizontal loop on the shared column.
- 120 combinations of weight order, pixel-local set and order, interleaving, loop form and `const` pointers: best 6/16/9; none moves the spill homes.

## Behaviour

The native harness `dering-weak-flat-20261020-harness.c.txt` (committed last run) compared the committed bank, this bank and the independent spec model in 5120 cases: 0 failures. Unicorn is not installed in this seat, so the retail emulator oracle was not rerun.
