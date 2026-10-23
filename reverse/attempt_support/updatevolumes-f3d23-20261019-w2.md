# updateVolumes partial recovery

Final validation passed: check_csv, pin_consistency, git diff --check, inherited-comment preservation and retained-payload equality. A fresh compile of the actual bank reproduces the retained source's complete extent, alignment counts and eight differing call-displacement bytes (`banked.align.raw.log` and `banked.strict.raw.log`). explain_mismatch independently reports unresolved REL32 and the first difference at +0x151. `final.receipt.json` records the final validation clock. No background process remains.

Result: closer bank with required null behavior restored. No production source, function row, pin, verifier or submodule pointer changed. All changes remain uncommitted. Symbol: `?updateVolumes@W3DVolumetricShadow@@IAEXM@Z`. Native RVA: `0x000F3D23`. Extent: 736 bytes. The retained source is `reverse/attempts/0x000f3d23.cpp`; `repair_queue.py dest` names `Code/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DVolumetricShadowRenderDynamicMeshVolume.cpp` by neighbour heuristic. Integration into that existing owner remains unattempted because the callee identities below are unresolved.

## Measurements

All alignment figures come directly from fresh `align_diff.py` runs with `BFME_OBJSTORE=off`. Each edited source had its object and dependency receipt removed before measurement. The memory category includes absolute DIR32 sites; all 22 remaining memory entries are relocation noise. Branch and relocation categories do not decide improvement. Both original and retained bodies emit the complete native extent. The positional byte count comes from `build.compile_function` with the actual symbol map, no temporary pins; shifted DIR32 sites make this count unsuitable for choosing structural trials. The final body is aligned, so its 8 differing bytes identify two precise call displacements. The bank score is computed as (736 - 8) / 736, rather than preserving the old farm's instruction fitness.

| Source | Emitted bytes | Instructions | Structural regions | Memory differences | Register differences | Patched differing bytes |
|---|---:|---:|---:|---:|---:|---:|
| before | 736 | 203 | 5 | 25 | 0 | 267 |
| h1 | 744 | 205 | 4 | 25 | 0 | 362 |
| h2 | 744 | 205 | 4 | 26 | 1 | 364 |
| h3 | 716 | 200 | 6 | 24 | 3 | 382 |
| h4 | 742 | 204 | 3 | 25 | 0 | 385 |
| h5 | 740 | 203 | 5 | 23 | 2 | 338 |
| h6 | 737 | 202 | 10 | 38 | 10 | 486 |
| h7 | 742 | 204 | 3 | 25 | 0 | 385 |
| h8 | 742 | 204 | 1 | 24 | 0 | 375 |
| h9 | 751 | 210 | 12 | 72 | 22 | 521 |
| h10 | 730 | 203 | 2 | 23 | 0 | 367 |
| h11 | 735 | 201 | 1 | 31 | 7 | 77 |
| h12 | 738 | 202 | 2 | 22 | 2 | 331 |
| h13 | 756 | 200 | 3 | 35 | 4 | 320 |
| h14 | 736 | 202 | 0 | 22 | 0 | 8 |
| h15 | 736 | 202 | 0 | 22 | 0 | 8 |
| h16 | 736 | 202 | 0 | 23 | 1 | 10 |
| h17 | 736 | 202 | 2 | 24 | 1 | 21 |
| h18 | 736 | 202 | 0 | 22 | 0 | 8 |
| h19 | 736 | 202 | 0 | 22 | 0 | 8 |
| retained-final | 736 | 202 | 0 | 22 | 0 | 8 |

Raw outputs are `build/updatevolumes-w2-20261019/<source>.align.raw.log` and `<source>.strict.raw.log`. The original bank is preserved as `before.cpp`. `retained-final.cpp` is the final source before the bank header is prepended. `hypotheses.md` records each hypothesis, evidence and refuting observation before the experiment. No attempt used a synthetic symbol map.

## Supported changes

Retail at VA 004F3DA0 tests the selected mesh and skips directly to the loop increment when it is null. The farm bank's `mesh ? 1 : 1` expression dropped this branch and could dereference null. The retained body restores the donor's null guard. This is a semantic correction independently of its measured alignment gain.

Restore the donor's outer light loop and the lightIndex*160+meshIndex array relationship. With this loop present, native register allocation and index lifetime agree without any volatile access in the body. Use direct mesh-array indexing and natural nested for loops. An explicitly inlined, memberwise SphereClass assignment retains one source pointer across all four copies, removing the extra pointer reload between Center and Radius. The unused inherited __vref template remains in the preamble but is never instantiated. Every inherited bank comment is preserved. Every applicable EA comment from the GeneralsMD updateVolumes body is restored at the corresponding operation.

H1 restores the missing null guard. H4 removes the sphere reload. H8 identifies initialization placement. H14 proves the missing outer loop controls index allocation. H15, H18 and H19 remove the explicit offset, its volatile accesses, the redundant guard and the pointer cast without changing emitted bytes. The other trials are rejected as detailed in `hypotheses.md`. In particular, H10 trades structure for memory alignment and H11 lowers positional differing bytes while adding memory/register differences, so neither is a closer bank. H20's first formatting assertion caught added braces; it was corrected before compiling. `finalize-first.raw.log` preserves that refusal, and `finalize-corrected.raw.log` records the corrected token/comment assertions. The failed missing-file measurements remain in `retained.align.raw.log` and `retained.strict.raw.log`.

## Remaining blockers

The direct call at body offset 0x150 (displacement 0x151..0x154) targets native RVA 0x000F2FFA. The corresponding `updateMeshVolume` name remains unrowed and unresolved. Its complete native boundary ends at this function's entry with RET 0x14, proving five stack arguments. This body has ECX=this and one float argument with RET 4. No pin is added merely to turn the partial into an exact claim.

The call at offset 0x202 (displacement 0x203..0x206) targets RVA 0x0009AC04, whose real owner is `??0Region3D@@QAE@ABU0@@Z`. The bank's `??4AABoxClass@@QAEAAV0@ABV0@@Z` resolves to its own row at 0x001492E0. Those two complete 43-byte bodies are identical, as `identity.raw.log` verifies, but they are distinct native addresses. The existing assignment identity therefore cannot be fold-pinned to the Region3D owner under the admission rules. No alternate constructor, renamed copy routine, cast bridge or synthetic symbol-map entry is substituted to erase this conflict. Recover the target's actual copy/type relationship before integrating the body. The prior verdict already reported this exact identity wall; the new result resolves compiler shape, not that identity.

## Identity and provenance

Target facts: Ghidra independently records the exact start/extent; the preceding worker's RET 0x14 ends at 0x000F3D23, and this body's RET 4 ends at 0x000F4003. The matched Update caller at 0x000F4017 calls here at 0x000F42B1 and supplies one float. Native mesh selection, mesh-record stride, deformed-vertex update, geometry bounds, visibility state machine and render-task insertion agree instruction for instruction with the retained source apart from the two call bindings. `native.raw.log` and `identity.raw.log` preserve raw disassembly, direct callees and virtual offsets.

The method name and semantic outline come from BFME 1 and ZH `GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DVolumetricShadow.cpp`. Donor names are supported by the target caller and callee relationships; native bytes do not independently provide C++ type names. Preamble class views remain inherited structural inferences. All ten checkout verdicts were read, including the Region3D fold refusal missing from the assignment's nine-row list. Related worker handoffs `reverse/attempt_support/update-mesh-volume-20261019.md` and `reverse/attempt_support/updatemeshvolume_f2ffa_20261019/README.md` were also read. Checkout: `c10ac5f3ab8bd54d2a72f735b492bbe6ad903e07`. Donor: `a18d9ed50607e9175de4d6568798d7d73119de09`. Compiler settings remain the inherited first `// cl:` line: `/O1 /G7 /arch:SSE /MD /DNDEBUG /Oy-`.

## Checks and artifacts

`before.align.raw.log` and `retained-final.align.raw.log` are the required comparative measurements. `before.strict.raw.log` and `retained-final.strict.raw.log` preserve actual-map byte comparisons. `final-explain.raw.log` is the independent explain_mismatch report. `banked` alignment and strict logs independently recompile the actual bank after writing it. `check-csv.raw.log`, `pin-consistency.raw.log`, `comment-preservation.raw.log` and `git-diff-check.raw.log` record final validation. A production build and find_declared_unmatched are not claimed because no production source was changed and the body is not exact. `record.raw.log` preserves the re_log banking operation. `destination.raw.log` and `prior-verdicts.raw.log` preserve selection and prior evidence.

Elapsed at verdict recording: 13.75 clock-measured minutes, model=gpt-6.1-sol. `record.receipt.json` records UTC timestamps and the computed duration. Every trial source and raw log remains under `build/updatevolumes-w2-20261019/` at the coordinator's explicit request. No background task was started. Exact byte verification remains a failure by the 8 measured call-displacement bytes.
