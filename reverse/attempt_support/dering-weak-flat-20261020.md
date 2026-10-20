# Weak deringing: flat weight indices and output statement order

Target `_DeringBlockWeak_C`, retail `0x001C22C0..0x001C28B6`, 1526 bytes. Inputs were the approved clean-room specs `reverse/vp6_cleanroom/specs/001c22c0.md` and `001c1ad0.md`, retail disassembly, the existing bank, its evidence folders and the strong sibling's handoff `dering-strong-cursor-20261020.md`. No external decoder source was consulted. Base commit `4d26addf6e`, flags `/O2 /G6 /DNDEBUG /MD` (MSVC 13.10.3077). This is an improved bank, not a match.

## Result

| Measure | Old bank | New bank |
| --- | ---: | ---: |
| emitted size | 1526 | 1526 |
| `align_diff` structural regions | 18 | 6 |
| memory operand differences (one is the sharpen DIR32) | 33 | 24 |
| register operand differences | 17 | 9 |
| branch-target differences (not defects) | 12 | 0 |
| fixed-offset differing bytes, sharpen DIR32 masked | 243 | 64 |
| ordered byte alignment, retail first, DIR32 filled | 1441/1526 | 1478/1526 |
| first differing byte | +0x63 | +0x2E3 |

Everything before the output loop (prologue, both weight loops, frame `0x160`) is now byte-identical to retail.

## What changed, in the order it was measured

1. Flat weight stores (`vertical[r * 8 + c]`, `horizontal[r * 9 + c]`) instead of advancing weight row pointers, the strong sibling's lead: 18 to 14 regions, 243 to 113 fixed bytes. Both weight loops become exact, including retail's +1 element cursor bias.
2. The column variable shared by the vertical and output loops is `unsigned int`: the output loop's column test becomes retail's `jb` (14 to 13 regions, 112 bytes). Separate or for-scoped counters instead emit 1542 bytes.
3. The four weight locals are read in the order left, up, down, right: 13 to 6 regions, 112 to 70 bytes. All 24 orders were measured; the next best (up, left, down, right) gives 10 regions.
4. Two pixel values read into locals before the weights (the bank uses the centre and right pixels): memory differences 28 to 24, 70 to 64 bytes. All 325 ordered subsets of the five pixels placed before the weights were measured; any two or three locals give 64, one, four or five give 70, so it is the count that matters, not which pixels.

## Remaining mismatch (all inside the output loop)

- Output-loop prologue colouring: retail keeps `below` in esi and `source` in edi, ours in ebx and esi.
- Spill homes of three row cursors: retail's above cursor shares `above`'s own slot `[esp+0x28]`, the horizontal-weight cursor takes `below`'s slot `[esp+0x30]` and the `source + 1` cursor `[esp+0x40]`; ours use `0x30`, `0x40` and `0x28`. The row-end cursor update order differs as a consequence.
- Six address operands are commuted: retail writes the cursor as base and the loop-invariant difference as index (`[ecx+ebx]`), ours the reverse (`[ebx+ecx]`). One load pair at +0x48F/+0x49E is swapped for the same reason.

## Ruled out in this run (whole-function trials under `build/w4_1c22c0/`)

- Subtraction order inside `128 - ...` (24 orders plus three grouped or reordered forms) and product order of the blend (all 120): byte-identical, cl canonicalises them.
- Address spellings (`*(p + r * pitch + c)`, `(p + r * pitch)[c]`, `p[c + r * pitch]`, `p[pitch * r + c]` and two more): identical. A per-row `int` offset local emits 1542 bytes.
- Advancing `above`, `source`, `below` or `destination` by `pitch` per row, all 15 combinations: 1440 to 1519 bytes.
- Declaring `below` before `above`, or both before the quality or after the cap: worse (9 to 13 regions).
- Shared or unsigned output row counter, function-scope row pointers, C89 hoisted declarations, `const` locals, `unsigned char` pixel locals, ternary clip: identical.
- Up, down or right weights through their own base pointers: 1521 to 1542 bytes. `(r + 1) * 8` and `r * 9 + (c + 1)`: identical. Short weight locals: 1585 bytes.
- Non-const `source` or unsigned `pitch` (diagnostic only): identical.
- Each neighbour's weight grouped with its pixel local, all 24 neighbour orders, weight or pixel first, centre first or last: best 64 bytes, the same plateau.

## Behaviour

`dering-weak-flat-20261020-harness.c.txt` is the strong sibling's native harness adapted to the weak filter: the old bank, the new bank and an independent spec model (weight `quality + 32 - 2 * difference`, cap 24, each output stored immediately) are built with the repository's MSVC 7.1 and compared over the whole 32 KB buffer. It ran 5120 cases (all 64 Q indices, positive and negative pitches, flat, checkerboard, ramp and random inputs, perturbed scale tables, disjoint, in-place and three partially overlapping destinations): 0 failures. A mutation that makes the right weight read the left pair failed 2434 cases. Compile the two bodies with `/O2 /G6 /DNDEBUG /MD /DDeringBlockWeak_C=Bank_Weak` and `/DDeringBlockWeak_C=Cand_Weak` and link them with the harness. Unicorn is not installed in this seat, so the retail emulator oracle was not rerun.

## Next lead

The remaining differences look like one allocation cause: retail's above cursor is coalesced with `above` itself, ours is a new temporary, which reorders the spill homes and the base and index operands. A gap measurement (throwaway uses of `above` in a scratch copy, see `docs/matching.md`) would size it before more spelling trials.
