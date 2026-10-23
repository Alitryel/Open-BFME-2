# WaterTracksObj::render handoff

Blocked. The existing farm bank is unchanged. No tested source is closer under the assigned structural, memory and register comparison, and no reconstruction was placed in Code/.

Body: `?render@WaterTracksObj@@QAEHPAVDX8VertexBufferClass@@HAAVRenderInfoClass@@@Z`, RVA `0x000FEADB`, 2413 bytes, ending at `0x000FF448`. The approved destination is `Code/GameEngineDevice/Source/W3DDevice/GameClient/Water/W3DWaterTracks.cpp`. Checkout: `394012baa68b43c4b3098e57286b4a3375d91837`; BFME 1 checkout: `a18d9ed50607e9175de4d6568798d7d73119de09`. Semantic donor provenance remains BFME 1 `9cbfb551fe20`, as documented in the bank. Model: `gpt-6.1-sol`.

All six prior verdicts and the current semantic donor were read before compilation. The cited `build/big/water-render-visible/proof.json` is absent, so its closure claim was not treated as fresh evidence. The raw native body ends in `ret 0xc` and immediately abuts another function. Its flush caller supplies the vertex buffer, batch start and RenderInfo reference; the existing flush source and render pin independently support the real name.

Fresh retail evidence: append/discard Lock calls use COM slot +0x2c and Unlock uses +0x30, with buffer member +0x1c and FVF size +0xc. The call at body +0x68d resolves to RVA 0x0007FA2B and its EAX result is tested before signed integer conversion from [eax+0x60]. Point bounds resolves to 0x000FE9E3; the camera call uses virtual slot +0x208; shroud resolves to 0x007397F0; draw helpers resolve to 0x0011D530 and 0x001206D0. The current target helper source has an integer-returning owner at 0x0007FA2B. Declaring that existing owner and casting its returned integer to the accessed record pointer removes the unresolved symbol without changing the alignment tuple. The bank arithmetic and constant-true equal-arm Lock preserve the operation selected by retail; no dropped operation or volatile self-store was found.

Remaining mismatch: append-lock member-address/load scheduling at body +0x6b..+0x8e, early moving-wave perpendicular subtraction at +0x251..+0x2c3, and mid-moving-wave direction product/scheduling at +0x30f..+0x368. Operand differences elsewhere include relocation-address noise classified as memory by align_diff. The displayed counts below are the tool’s unmodified categories.

| Trial | Emitted bytes | Structural regions | Memory | Register | Masked raw positional byte differences |
|---|---:|---:|---:|---:|---:|
| baseline | 2415 | 11 | 23 | 7 | 1740 |
| buffer_first | 2396 | 12 | 25 | 8 | 1790 |
| buffer_ref | 2249 | 44 | 112 | 75 | 2069 |
| moving_perp | 2415 | 11 | 23 | 7 | 1740 |
| owner | 2415 | 11 | 23 | 7 | 1740 |
| perp_copy | 2416 | 31 | 91 | 54 | 1713 |
| perp_width | 2269 | 22 | 26 | 16 | 1994 |
| perp_yx | 2366 | 32 | 96 | 52 | 1999 |
| pointer_ref | 2414 | 19 | 42 | 43 | 1716 |
| reach_copy | 2393 | 31 | 107 | 70 | 1638 |
| reach_ref | 2357 | 33 | 87 | 51 | 1953 |
| reach_yx | 2255 | 35 | 103 | 67 | 1746 |

The masked raw positional count excludes object relocation fields and includes any length difference; it is supplementary and does not decide closeness. The preserved before/after bank has the baseline count in both cases. explain_mismatch’s patched positional byte difference is 1762 for baseline and owner; a size mismatch causes its fixed-size relocation copying to obscure the displaced instruction stream, so use the raw align logs for reconstruction. The normalized positional instruction comparison is 47 on both baseline and owner, rather than the older farm verdict’s 46; this is one fresh baseline compilation, not a reproduction of that historical run.

Ruled out: pointer-reference binding with and without duplicate-call removal; moving the existing buffer load before FVF calculations; a named perpendicular Vector2 intermediate; separate Y-then-X component assignments; a cached final-width scalar; copied perpendicular/direction operands; and a const-reference reach scalar. The named perpendicular intermediate is byte-inert. All other shape variants regress. The tempting smaller positional byte count in reach_copy comes with worse structural, memory and register counts and was rejected.

Hypotheses and refutation criteria were recorded before trials in `build/water-render-w7-20261019/hypotheses.md`. Every trial source, raw align/explain output, retail/object disassembly, metric and command receipt is under that task directory. The useful owner reconciliation is retained in `owner.cpp`; the original bank is retained in `baseline.cpp`. `summary.log` contains fresh boundary bytes, call destinations, the unchanged-bank SHA256 assertion and measured tuples. No pin was added. No git write command, network operation, verification runner or background task was started.

Clock receipt: started `2026-10-19T03:57:41+00:00`, handoff prepared `2026-10-19T04:04:38.836194+00:00`, elapsed `6.96` minutes. `BFME_OBJSTORE=off` was set for every compilation and measurement. Each probe checks `build/STOP_WORKER` before compiling; no stop marker was present during the trials.
