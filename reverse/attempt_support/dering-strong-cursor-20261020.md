# Strong deringing: flat weight indices fix the store cursors

Target `_DeringBlockStrong_C`, retail `0x001C1AD0..0x001C22BE`, 2030 bytes. Inputs were the approved clean-room specs `reverse/vp6_cleanroom/specs/001c1ad0.md` and `001c22c0.md`, retail disassembly, the existing bank and its evidence folders. No external decoder source was consulted. Base commit `afcc6810c2`, flags `/O2 /G6 /DNDEBUG /MD` (MSVC 13.10.3077). This is an improved bank, not a match.

## Result

The new bank emits the same 2046 bytes as before and is measurably closer by every measure taken:

| Measure | Old bank | New bank |
| --- | ---: | ---: |
| `align_diff` structural regions | 32 | 31 |
| retail and our instructions inside those regions | 63 / 68 | 61 / 66 |
| memory operand differences | 141 | 139 |
| register operand differences | 73 | 73 |
| branch-target differences (not defects) | 51 | 44 |
| ordered byte alignment, retail first, sharpen DIR32 bound to `0x00DB7A28` | 1633/2030 | 1654/2030 |
| exactly equal aligned instructions | 390 | 398 |

The frame is still `0x174` against retail's `0x178`.

## Finding

Retail's weight-store cursors sit one element above the array base in both weight loops (`lea eax,[esp+0xfa]` with stores at `-2,0,+2,+4`; `lea eax,[esp+0x6a]` with stores at `-2,0,+2`). The old bank advanced a weight row pointer (`vweight[c]`, `vweight += 8`), which cl 7.1 biases two elements up (`-4..+2`). A micro study (one loop per function, same flags) shows that the bias follows the address form, not the loop counter: `vweight[c]` with an advancing pointer gives +2 elements, while `vertical[r * 8 + c]` or `vertical[base + c]` with the same advancing source row pointer gives +1, exactly retail's. The same holds for the horizontal loop (`horizontal[r * 9 + c]`). With flat indices both weight loops reproduce retail's cursor bias, store order and source-pointer shape; only the register colouring remains (retail uses esi for the source cursor and ecx for the store cursor, the bank edx and edi).

The output loop reads the up weights through their own base pointer (`upWeights = vertical`) instead of `downWeights[... - 8]`. That pointer variable changes the IV family cl builds: the bank's down-weight cursor was `vertical + 9` elements, the new one is `vertical + 1`, and this was the best of the sixteen spellings measured. Retail's is exactly `vertical + 8` (down weights at `[eax]`, up at `[eax-0x10]`), which none of the spellings produced.

## Remaining mismatch

- Output-loop cursors stay one element above retail's: source row `+1` (retail `+0`), below `+3` (`+2`), above `+5` (`+4`), destination `+4` (`+3`). Because the output source cursor starts at `source + 1`, cl keeps the horizontal phase's `source + 1` alive in ebp, so the horizontal row counter is spilled to the stack instead of living in ebp as in retail. Retail also spills one more invariant (`below - above`, frame `0x54`); this is consistent with its 4 extra frame bytes and with both arrays sitting 4 bytes higher than ours.
- A micro study of the output loop gives the source cursor at +1 for every form tried: flat, commuted, `pitch * r`, row-local pointer, advancing pointer, index variable, advancing index, `(r + 1) * pitch - pitch`, counting down, reading through `source - pitch`, and a pointer biased by -1. A pointer biased by +1 moved it to +2, and one biased by +2 gave +1 again. None gives retail's 0.
- The prologue loads the sharpen entry before the scale entry (retail scale first) and the vertical loop's colouring differs; both are allocation consequences.

## Ruled out in this run (whole-function trials, all under `build/w4_1c1ad0/`)

- Product order inside the blend: all 24 orders compile to identical code (cl canonicalises the sum).
- Declaration order of the per-pixel locals (centre, right pixel, weights): no change.
- Prologue statement order (five variants of the quality, sharpen, cap, above and below order, including a conditional cap): none improves every class at once.
- Table and parameter types (`const` or sized sharpen table, non-const or unsigned scale table, unsigned Q index): byte-identical.
- Inline weight reads instead of locals: 29 regions, but those regions cover 204 retail instructions (against 61), mnemonic alignment falls from 555 to 412, and bytes fall to 1454. This is a merge of regions, not an improvement.
- Flat source indexing in the horizontal loop, or a row-local `hrow`: the row counter moves into ebp as in retail, but the row cursor loses retail's +1 bias and register differences rise to between 80 and 98 (against 73).
- Down weights through `vertical[r * 8 + 8 + k]`, `(r + 1) * 8`, a row-local pointer, or advancing weight cursors: all worse.
- Reading above and below through `source` (`source[r * pitch +- pitch + k]`) reproduces retail's 0x178 frame and the array positions exactly, but changes the whole output loop (63 regions).

## Behaviour

`dering-strong-cursor-20261020-harness.c.txt` links the old bank, the new bank and an independent spec model, all built with the repository's MSVC 7.1, into one native test. It ran 5120 cases (all 64 Q indices, positive and negative pitches, flat, checkerboard, ramp and random inputs, perturbed scale tables, disjoint, in-place and three partially overlapping destinations) and compared the whole 32 KB buffer: 0 failures. A one-index mutation of the candidate failed 1371 cases, so the harness detects such errors. To rerun it, compile the two bodies with `/O2 /G6 /DNDEBUG /MD` and `/DDeringBlockStrong_C=Bank_Strong` or `/DDeringBlockStrong_C=Cand_Strong`, then link both objects with the harness. Unicorn is not installed in this seat, so the retail emulator oracle was not rerun; the old bank passed it in 2560 cases, and the new bank equals the old one on every case above.

## Lead for the weak sibling

The same flat weight indexing applied unchanged to the weak bank `reverse/attempts/0x001c22c0.cpp` measured 18 to 14 regions, 33 to 32 memory and 17 to 14 register differences at the same 1526 bytes. Nothing was recorded for it in this run.
