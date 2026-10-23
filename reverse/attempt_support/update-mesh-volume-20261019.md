# updateMeshVolume partial recovery

The bank is closer and remains nonmatching. No production source, ledger row, pin, gate or submodule pointer changed. The retained source is `reverse/attempts/0x000f2ffa.cpp`; its eventual home from `repair_queue.py dest` is `Code/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DVolumetricShadowRenderDynamicMeshVolume.cpp` (a neighbour heuristic, with the main W3DVolumetricShadow.cpp still proposed in tu_map).

Symbol: `?updateMeshVolume@W3DVolumetricShadow@@IAEXHHPBVMatrix3D@@ABVAABoxClass@@M@Z`. Native boundary: RVA `0x000F2FFA` through the `RET 0x14` ending immediately before `0x000F3D23`. Ghidra independently records the start and extent. Checkout: `394012baa68b43c4b3098e57286b4a3375d91837`. Donor checkout: `a18d9ed50607e9175de4d6568798d7d73119de09`. Model: `gpt-6.1-sol`.

## Measured result

Both bodies emit the complete native extent and instruction count. The alignment counts below are the unmodified output of `tools/align_diff.py`; its memory category includes absolute DIR32 relocation operands. Relocation and branch differences are excluded from the improvement decision. Resolved-byte differences are independently computed with `build.compile_function` using the real symbol map and no synthetic pins.

| Candidate | Emitted bytes | Instructions | Structural regions | Memory differences | Register differences | Resolved differing bytes | Unresolved calls |
|---|---:|---:|---:|---:|---:|---:|---:|
| Original farm bank | 3369 | 846 | 0 | 83 | 3 | 70 | 0 |
| Retained bank | 3369 | 846 | 0 | 47 | 2 | 33 | 0 |

The bank score is computed as resolved byte agreement, `(extent - differing_bytes) / extent`; it is not the old farm's instruction score. Measurements are reproduced from distinct source paths with `BFME_OBJSTORE=off`; the object and dependency receipt are removed before each alignment measurement. The final retained source is independently recompiled after adding the handoff comments. Raw logs remain in `build/worker_f2ffa/`.

## Supported change

Native stores the unnormalized previous-light delta into the same three stack words later used for the object-space light position. Replace the implicit subtraction return temporary with `Vector3::Subtract(objectCenter, history, &lightPosObject)`, copy that value to `toPrevLight`, and retain the donor's member Normalize. The earlier value is dead before the matrix transform overwrites lightPosObject. Together with restoring plain `box.Center + box.Extent`, this preserves the native instruction structure and moves the sphere and extrusion-scalar homes into place. The old equal-arm Corner0 workaround is removed. The farm's initialized Corner4 self-assignment is removed with identical emitted bytes. Every existing bank comment is preserved.

The row-1 source now writes the native grouping `(Y product + Z product) + X product`; the compiler still commutes its first two products. No volatile accesses, redundant operations, assembly, optimization pragmas or pins were introduced.

## Remaining mismatch

The index spill is at EBP-18 instead of EBP-8. The shared lightPosObject/raw-delta vector starts at EBP-10 instead of EBP-1C. Scalarized lightRay spills use EBP-14 and EBP-1C instead of EBP-C and EBP-10. Normalization reads the equivalent toPrevLight copy at EBP+3C/+40/+44 rather than the raw source slot. Row 1's first x87 product pair is Z,Y instead of Y,Z. Corner0's final ADDSS exchanges its two equivalent operands. The complete resolved instruction differences are in `retained.strict.raw.log`.

`explain_mismatch.py` confirms the extent and first differing byte, but its heuristic labels the displacement byte E8 as a call-shape mismatch. Full instruction decoding shows that byte belongs to `mov [ebp-18], ecx`; it is the index-home difference.

## Experiments and refutations

Every hypothesis, evidence and refuting observation was written before its trial in `build/worker_f2ffa/hypotheses.md`; every new trial checked `build/STOP_WORKER` first.

| Trial | Observation | Disposition |
|---|---|---|
| H1, explicit shared assignment using operator- | Retains a third vector copy and adds structural regions. | Rejected. |
| H2, direct output-parameter Subtract | Reduces memory differences but changes Corner0 structure and registers. | Rejected alone. |
| H3, raw-source normalization spelled in caller | Named scalar changes the frame and regresses many homes. | Rejected. |
| H4, H2 with plain donor Corner0 | Improves memory and registers with no structural differences. | Retained basis. |
| H5, raw-source normalization in inline helper | Optimizer removes copies and changes structure. | Rejected. |
| H6, right-associated native dot | Ties H4; still emits Z,Y,X. | No improvement. |
| H7, left-associated native dot | Ties H4 with source association following native. | Retained. |
| H8, remove redundant farm self-assignment | Entire emitted function equals H7. | Retained cleanup. |

## Identity and provenance

The name and semantic outline come from BFME 1's `game/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DVolumetricShadow.cpp` and the corresponding ZH definition. Target facts are the native entry/exit, five stack arguments with ECX=this, target layouts, matrix conversion, light-position history, visibility tests, silhouette update, allocation and constructVolume/constructVolumeVB calls. The actual target calls resolve to existing providers without aliases or temporary symbol-map assignments. These relationships support the donor method identity; native does not supply its C++ name. The opaque constructor remains address-named. The unrelated donor class layouts in the bank preamble are inherited evidence, not newly proved target layouts.

All prior target verdicts and the complete bank were read before the first experiment. The target mentions in `crack-d-round-notes.md` and `crack-e-finish.md` add no unexplored compiler lead. The cited old scratch candidate `build/s3r9/volume-lifetime-best.cpp` is absent in this checkout. Declaration permutations, empty destructors and use swaps remain exhausted; this pass tested explicit use-definition sharing instead.

## Reproduction and checks

Run with `BFME_OBJSTORE=off`. `python tools/align_diff.py build/worker_f2ffa/baseline.cpp <symbol> 0x000F2FFA 3369` reproduces the original comparison; replace the source with `build/worker_f2ffa/retained.cpp` for the new comparison. Remove that source's object before rerunning. `python build/worker_f2ffa/probe.py strict <source>` resolves all relocations and prints the full instruction differences without compiling or editing the ledger. `final.explain.raw.log` contains the independent explain_mismatch output.

Raw alignment checks: `baseline.align.raw.log`, `retained.align.raw.log` and each `h*.align.raw.log`. Raw strict checks: `baseline.strict.raw.log` and `retained.strict.raw.log`. The complete final candidate is `retained.cpp`; every earlier trial source is preserved alongside its raw logs. `destination.raw.log` records the source destination; `native.calls.raw.log` and `baseline.disassembly.raw.log` record the native ABI and callee sequence. `re_log.raw.log`, `check_csv.raw.log` and `pin_consistency.raw.log` record the banking operation and final ledger checks. No production source was changed, so no production build or find_declared_unmatched result is claimed. The exact byte check remains a failure by the measured differences above.

Final validation passed: `check_csv.py` and `pin_consistency.py --check`. A fresh compile of the actual bank reproduces the retained source's alignment counts and resolved differences; raw outputs are `0x000f2ffa.align.raw.log` and `banked.strict.raw.log`. `git_diff_check.raw.log` records the whitespace check. `files.txt` inventories all task artifacts and its object-cache outputs. No background task was started. Elapsed time at verdict recording is measured in `record.receipt.json`; the final clock receipt is `final.receipt.json`.
