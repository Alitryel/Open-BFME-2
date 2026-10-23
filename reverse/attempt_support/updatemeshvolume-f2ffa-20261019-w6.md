# updateMeshVolume: blocked, current bank preserved

Symbol: `?updateMeshVolume@W3DVolumetricShadow@@IAEXHHPBVMatrix3D@@ABVAABoxClass@@M@Z`. Retail RVA `0x000F2FFA`, size 3369 bytes. Checkout `e919629eecd5645df5d5d9d2ce2035419631e1d4`; donor checkout `a18d9ed50607e9175de4d6568798d7d73119de09`. Model: `gpt-6.1-sol`.

## Result and measurements

The existing `reverse/attempts/0x000f2ffa.cpp` is unchanged. Fresh before and retained compiles both emit 3369 bytes and 846 instructions. They have 35 differing resolved bytes including the unresolved AABox copy call, or 31 bytes excluding that call's four relocation bytes. No trial qualifies as closer. No Code source, ledger row, pin, header, gate or submodule pointer changed.

The table uses unmodified `align_diff.py` categories. Memory counts include absolute DIR32 relocation operands; relocation and branch counts do not decide closeness. Differing code bytes exclude the explicitly reported unresolved call, not any other defect. Positional counts for structurally different trials are diagnostic only.

| Candidate | Emitted bytes | Structural regions | Memory differences | Register differences | Differing code bytes |
|---|---:|---:|---:|---:|---:|
| before | 3369 | 0 | 45 | 2 | 31 |
| h1_outer | 3369 | 0 | 85 | 3 | 72 |
| h1_inner | 3369 | 0 | 82 | 6 | 72 |
| h2_operand_double | 3369 | 4 | 47 | 2 | 49 |
| h2_product_double | 3369 | 4 | 45 | 2 | 41 |
| h2_partial_double | 3371 | 5 | 45 | 3 | 2923 |
| h2_products_double | 3377 | 6 | 48 | 10 | 2643 |
| h3_early | 3382 | 24 | 214 | 20 | 3156 |
| h3_late | 3381 | 11 | 101 | 14 | 2674 |
| retained | 3369 | 0 | 45 | 2 | 31 |

## Hypotheses and refutations

All target verdicts and the current bank were read before experiments, including both cited handoffs and the preserved `updatemeshvolume_f2ffa_20261019/donor_form_t1x.cpp.txt`. The earlier `build/s3r9/volume-lifetime-best.cpp` and previous raw scratch directories are absent. The crack-d and crack-e target notes report no new experiment. Prior declaration permutations, empty destructors, use swaps and scalar arithmetic permutations remain ruled out.

H1 tested the prior handoff's proposed vector-sharing lever. Retail shares toLight and lightRay storage, and their values have disjoint lifetimes. The trial explicitly reuses toLight for the later ray, restores the donor subtraction temporary, and controls whether lightPosObject is scoped to reconstruction. Refutation was wrong homes, new structure, or increased memory/register differences. Both variants emit the full extent but increase code differences from 31 to 72. Explicit source-variable reuse does not force shared storage after SSA splitting. The outer form has 85 memory and 3 register differences; the inner form has 82 and 6.

H2 tested expression types rather than another permutation of the float expression. Retail keeps the row-1 dot in x87 until the double argument store to fabs. Promoting operands, products or partial sums could change reassociation while retaining extended arithmetic. Refutation was a retained product commute, new structure, new spills, or any worsened alignment category. All four forms retain the wrong first product pair. Operand/product promotions introduce four structural regions; partial/product temporaries add spills and exceed the native extent. No promoted form is retained or asserted to preserve strict source rounding independently of retail.

H3 tested naming the actual indexed light-history Vector3 subobject rather than copying an input parameter. The native function spills the common lightIndex*0xA0+meshIndex index at EBP-8. A real cached subobject reference could change whether the compiler stores an index or address and thus its allocation priority. Both reference placements introduce a live pointer and structural regressions. Refutation was any such added allocation or worse alignment. No further experiment is justified by these results without new compiler-dataflow or source evidence.

The exact source changes for all eight trials are preserved in `updatemeshvolume-f2ffa-20261019-w6.patch`. The unchanged bank retains every prior comment. Hypotheses were written before trials in `build/f2ffa_w6/hypotheses.md`, and every trial checked `build/STOP_WORKER`. It was absent at the last check.

## Exact remaining mismatch

The combined history index spills at EBP-18 rather than EBP-8. The raw previous-light delta and transformed lightPosObject occupy EBP-10/-C/-8 rather than EBP-1C/-18/-14. The three normalization reloads at native 0xF3357, 0xF335F and 0xF3367 read toPrevLight's copied fields at EBP+3C/+40/+44 rather than the raw delta slots. Scalarized ray temporaries spill at EBP-14 and EBP-1C instead of EBP-C and EBP-10. Row 1 evaluates its first Z product before Y rather than Y before Z at 0xF3121..0xF312F. Corner0's addition is already correct in this bank.

The AABox copy constructor call at 0xF3473 remains unresolved. This TU emits `??0AABoxClass@@QAE@ABV0@@Z` as exactly retail 0x9AC04's 43 bytes with zero relocations, independently rechecked in `identity.raw.log`. No pin was added because it would not improve the structural/memory/register comparison or complete the body. Future landing still needs the normal fold-proof admission. All other call relocations resolve through the actual current symbol map.

## Identity and boundary evidence

Target disassembly starts with a complete entry at 0xF2FFA, decodes all 3369 bytes and ends with RET 0x14 at 0xF3D20, immediately before the next function at 0xF3D23. The Ghidra inventory independently records RVA 0xF2FFA with extent 3369. The native updater at 0xF3D23 calls this entry at 0xF3E73. ECX=this and the five four-byte stack arguments agree with the bank declaration.

The C++ method name and semantic outline come from the BFME 1 and ZH donors; no target debug name is claimed. Target matrix conversion, light histories, rotation comparisons, frustum tests, silhouette update, allocation, both volume constructors and bounding-volume stores support that identity independently of byte similarity. WB twin 0x806A80 and updater 0x805CA0 remain prior evidence, not a newly rerun WB analysis. Layout offsets are retained target facts; the explicit lifetime-sharing proposals are reconstruction hypotheses. Opaque dependencies remain address-named.

## Checks and reproduction

Set `BFME_OBJSTORE=off`. Run `python build/f2ffa_w6/probe.py LABEL SOURCE`; it removes the source object before `align_diff.py` and records raw alignment, complete resolved instruction differences, disassembly and a receipt. Before/retained were compiled independently at different paths. The object-store environment also applies to every explain and check subprocess.

Raw logs live in `build/f2ffa_w6/`. `before.align.raw.log` and `retained.align.raw.log` reproduce 0/45/2 structural/memory/register counts. Their strict logs reproduce 35 total differing bytes, 31 excluding the unresolved call. Every trial has corresponding `.align.raw.log`, `.strict.raw.log`, `.disassembly.raw.log` and `.receipt.json`; h1/h2/h3.raw.log preserve complete probe command outputs. `identity.raw.log` contains native boundaries, caller calls, copy-body equality, revisions and identical SHA-256 hashes for the bank and before copy.

`explain.raw.log` independently confirms the exact emitted size and mismatch; its process exits zero but the byte check fails and reports the unresolved REL32. `check_csv.raw.log` and `pin_consistency.raw.log` pass. `destination.raw.log` names `Code/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DVolumetricShadowRenderDynamicMeshVolume.cpp` by neighbour heuristic, while tu_map proposes the main W3DVolumetricShadow.cpp; no destination edit was attempted. `git_diff_check.raw.log` passes. No production source changed, so neither a production build nor find_declared_unmatched result is claimed. No background task was started and no git-writing or network command was run.

Clock interval before verdict: 2026-10-19T08:43:57+00:00 to 2026-10-19T08:51:47.195824+00:00, 7.84 minutes. `record.receipt.json` records the verdict command and clock.

`build/f2ffa_w6/files.txt` inventories the retained scratch files and generated object-cache paths. `final.receipt.json` records 8.57 elapsed minutes, no stop request and zero background tasks started. `final_checks.receipt.json` records passing final whitespace and status command exits; their raw outputs are `final_diff_check.raw.log` and `final_status.raw.log`.
