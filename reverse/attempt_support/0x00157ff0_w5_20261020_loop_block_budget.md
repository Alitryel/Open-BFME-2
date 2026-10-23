# 0x00157FF0 Store_Thai_GDI_Glyph: the outer tile loop is skipped by a per-loop block budget

Symbol `?Store_Thai_GDI_Glyph@FontCharsClass@@AAEPBVFontCharsClassCharDataStruct@@G@Z`, retail RVA 0x00157FF0, 1323 bytes (0x157FF0..0x15851B, `ret 4`), flags `/O2 /arch:SSE /G7 /EHsc`. Verdict: blocked. The bank `reverse/attempts/0x00157ff0.cpp` is unchanged and stays the best candidate. Model: claude-opus-5-5.

## Result

The bank measures 1332 B against 1323 B with 21 structural regions, 99 memory and 26 register differences (`tools/align_diff.py`, freshly compiled). A WB 0x9F1BD0-faithful rewrite of the tile loops (`0x00157ff0_w5_20261020_wb_faithful.cpp.txt` beside this file: `sx`/`sy` before ExtTextOutW, named `xstart`/`ystart` after it, `maxX = xstart + tileX`, no `64/Scale` recompute) measures 1373 B with 19 regions, 123 memory and 30 register differences. That trades two regions for 24 memory and 4 register differences, so it is not closer and was not banked. Without the SIZE padding the rewrite gives 1347 B, 21 regions, 123 memory, 30 register.

## What retail does that every reconstruction misses

Retail's outer `ty` loop (0x223..0x48F) receives no loop optimisation at all. It multiplies `ty*tileX` and `ty*tileHeight` per iteration, counts `ty` up in `edi`/`[esp+0xac]`, and also recomputes the `ty`-invariant `-tileWidth` (`neg edx` at +0x24C) on every iteration, so not even loop-invariant code motion was applied to it. The nested `tx` loop is fully strength-reduced (count-down at `[esp+0x14]`, induction variables for `sx`, `xstart` and the ExtTextOutW x argument). Every reconstruction so far strength-reduces the `ty` loop (three count-downs instead of two) and hoists `-tileWidth` out of it; the remaining regions, the frame and most slot differences follow from that.

## New finding: the trigger is an exact block count, the same for bank and rewrite

Diagnostic trials (dummy statements, never for landing) inserted conditionals at the top of the `ty` body and read whether the `ty` loop stays reduced (count-down `sub dword ptr [esp+x],1` instructions: 3 reduced, 2 skipped). Each result is one compile (n=1).

| Inserted at the top of the `ty` body | Extra blocks | `ty` loop |
| --- | ---: | --- |
| 35 `if (g[i]) h[i] = 0;` | 70 | reduced |
| 36 `if (g[i]) h[i] = 0;` | 72 | skipped |
| 23 `if (g[i]) ++h[i]; else --h[i];` | 69 | reduced |
| 24 of the same if/else | 72 | skipped |
| 34 if-then plus 1 if/else | 71 | reduced |

Blocks are counted as two per if-then (then and join) and three per if/else. The threshold is K = 36 if-then conditionals for both the bank and the WB-faithful rewrite (bisected), consistent with the bracket the 0x00156A60 study found for its sibling body (30 keep the reduction, 36 skip it). So the loop is skipped once it holds about 72 more basic blocks than our source gives it, independent of how the tile loops are spelled. With K = 40 the `ty` loop takes retail's shape, including the per-iteration `-tileWidth`.

Conditionals that the optimiser removes early do not count, which narrows where the missing blocks could come from: 40 dead clamps (`int d = ty*k; if (d > tilesX) d = tilesX;`, never read) and 40 tests of a local flag initialised to 0 (`if (mode == k) ...`) both compile byte-identically to the bank, so dead-code removal and constant propagation run before the loop pass counts blocks. These did not move the threshold or change the `ty` loop either: 48 straight-line global copies, 48 member-derived stores, 48 value ternaries (compiled branch-free), 20 if/else statements (60 blocks), one volatile read, an 8-case switch, 60 conditionals outside the loops (also combined with K = 30 inside), one or six full copies of the function compiled earlier in the same unit, and one or three extra strength-reducible loops before the tile loops. Flags `/Z7`, `/Zi`, `/Zd`, `/GR`, `/Gs`, `/Gy`, `/J`, `/EHs` and `/Zc:forScope` on or off compile byte-identically to the bank; `/EHa`, `/Ge` and `/Oy-` are worse.

## Why this is still a wall

Retail's final `ty` loop has 30 blocks and 14 conditional branches against our 28 and 14, and its `tx` loop 25 blocks against our 23. WB's debug body shows no call, assertion or flag test inside any of the six loops (only ExtTextOutW), so its source carries nothing that could add some 72 blocks and vanish later. The Rich header pins cl 13.10.3077 without LTCG, and retail's FuncInfo (0xD0BA24) has maxState 1, whose only unwind action calls the out-of-line selection destructor 0x001543E0. None of the spellings, flags, compiler builds, EH settings or unit contexts tested here and in earlier verdicts supplies the missing blocks. The Zero Hour parent `Store_GDI_Char` keeps a nine-conditional `#ifdef TEST_PLACEMENT` block in its column loop. A similar debug block in BFME 2 that survives into the optimiser's loop pass but not into the final code would explain the result, but no spelling found so far does that (the 0x00156A60 study found that front-end-folded `if (0)` and `while (0)` blocks do not count).

## Next lever to try

Find a construct whose conditional blocks exist when cl 7.1 runs loop optimisation but are removed afterwards. Measure any idea with the bulk recipe above: insert it in the `ty` body and see whether K drops below 36. A candidate that lowers K is a lead even before it closes the body. Do not repeat the flag, EH, unit-context, extra-loop and ternary probes listed here, nor the visible-helper, guard, minima and stride trials of earlier verdicts.
