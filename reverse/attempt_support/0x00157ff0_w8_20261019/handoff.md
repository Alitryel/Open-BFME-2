# Result: closer bank through destination compiler settings

Symbol: `?Store_Thai_GDI_Glyph@FontCharsClass@@AAEPBVFontCharsClassCharDataStruct@@G@Z`. Retail RVA 0x00157FF0, extent 1323 bytes through RET 4 at 0x00158518, with padding at 0x0015851B. The destination query selects `Code/Libraries/Source/WWVegas/WW3D2/render2dsentence.cpp`; no Code source or ledger match was added.

The copied bank lacked `/arch:SSE`, although the destination region uses `/O2 /arch:SSE /G7`. Adding it replaces the x1 branch with retail's CMOVG and removes two structural regions. The ordinary ABC local read emits identical code to the farm's volatile read under otherwise identical settings. The final candidate retains every existing bank comment, preserves the old compiler directive below the effective first directive, and restores the applicable original ZH parent comments. Raw object comparison proves the statements are unchanged except the ordinary local read and that final equals the SSE control.

| Candidate | Emitted bytes | Structural regions | Memory | Register |
| --- | ---: | ---: | ---: | ---: |
| before | 1332 | 23 | 99 | 27 |
| ordinary | 1332 | 23 | 99 | 27 |
| cached | 1349 | 23 | 123 | 36 |
| before_sse | 1332 | 21 | 99 | 26 |
| natural_sse | 1323 | 24 | 121 | 33 |
| unpadded_sse | 1322 | 21 | 109 | 31 |
| final | 1332 | 21 | 99 | 26 |

The requested positional byte measurement changes from 1002 to 966. This is diagnostic only; acceptance uses the structural, memory and register classes above. Relocation and branch differences do not count as defects. The score is the relocation-aware mnemonic-aligned target-instruction agreement: 234/380 before and 236/380 after. It is a new explicitly defined metric, not the historical farm score. Raw align_diff's memory count includes absolute-address relocation noise; the same count is used on both sides.

## Remaining blocker

Both the bank and final emit 1332 bytes against retail's 1323. Their stack reservation is already B8, but local homes differ, starting with the saved this pointer at +0x90 versus retail +0x80. The outer tiled loop still uses different strength reduction and guard placement. Its maxX expression recomputes `64/Scale` after ExtTextOutW, whereas retail caches the quotient. Restoring the cached quotient removes that extra division but worsens memory and register alignment; restoring plain SIZE as well worsens all three classes. Removing only SIZE padding reduces the positional byte count but worsens both memory and register differences and is rejected. No observed dropped raster operation or volatile self-store justifies replacing the bank with these worse trials. No prior guard, minima, helper or broad flag sweep was repeated. First exact-byte difference remains +0x2C; the exact gate is not passed.

## Identity and provenance

Retail has its own prologue after the preceding RET and a complete RET 4 epilogue. Its ABI is thiscall with a 16-bit glyph in one stack slot. WB 0x009F1BD0 independently names Store_Thai_GDI_Glyph in render2dsentence.cpp and has the same glyph-index GDI imports, cache path, scaling, bearing and nested sampling semantics. Retail proves Scale +0x40, font +0x48, map +0x450, buffer vector +0x10, pixel offset +0x28, height +0x2C and extra height +0x30. Its new calls target 0x0002FDA0, map operator[] calls target 0x00157DD0, and buffer rotation targets 0x00156490. The bank declarations agree. ZH Store_GDI_Char is a parent semantic donor, not independent evidence for this Thai name or target layout. The old Store_GDI_Char pin is retained unchanged.

## Reproduction and retained evidence

Inputs: checkout af72028f8f334a7becdfa74206ce7acfe6391b75, BFME 1 pointer a18d9ed50607e9175de4d6568798d7d73119de09, default MSVC 7.1, `/O2 /arch:SSE /G7 /DNDEBUG /MD /EHsc`. Every build sets BFME_OBJSTORE=off. Trials use distinct paths; direct bank measurements delete the specific object and its dependency sidecar first. Raw before/after alignment and the mismatch report are beside this handoff. Every trial source, raw bytes and alignment log, compiler command, semantic and comment assertions, full retail listing and WB record, and the recorded pre-experiment hypotheses remain under `build/worker_157ff0/`. The raw positional byte logs use the gate's positional relocation patching, so instruction analysis uses align_diff and the raw object, never shifted patched addresses.

Clock start 2026-10-19T06:01:09+00:00, handoff preparation 2026-10-19T06:09:37.562831+00:00, measured elapsed 8.48 minutes at preparation. Model gpt-6.1-sol. All changes are uncommitted.

## Final checks

The bank was recorded through re_log.py as partial, then freshly recompiled at its actual reverse/attempts path after deleting its object and dependency sidecar. It reproduces final.cpp's raw body and alignment exactly. Every old bank comment is retained. check_csv and pin_consistency --check pass; their raw outputs are beside this handoff. explain_mismatch confirms a non-exact body. add_match, build.sh and find_declared_unmatched were not run because no matching Code source was produced. No Code source, pin or functions.csv row changed. All commands completed; no background worker was started.
