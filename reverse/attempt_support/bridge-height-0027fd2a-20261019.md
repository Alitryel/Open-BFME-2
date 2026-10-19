# Bridge::getBridgeHeight at 0x0027FD2A

Result: blocked. Preserve reverse/attempts/0x0027fd2a.cpp unchanged. No source or ledger row was added. Model: gpt-6.1-sol. Starting checkout: 8c8b04d8d4dbc349a8c745865493e349a2471da0; local BFME 1 reference: a18d9ed50607e9175de4d6568798d7d73119de09. Start time: 2026-10-19 09:06:03 UTC; the recorded verdict supplies the clock-measured duration.

Target: ?getBridgeHeight@Bridge@@QAEMPBUCoord3D@@PAU2@@Z, retail RVA 0x0027FD2A, 713 bytes. tools/repair_queue.py dest names Code/GameEngine/Source/GameLogic/Map/BridgePickBridge.cpp as a neighbour heuristic, with the approved TU map proposing TerrainLogic.cpp. No matching body was available to move into either unit.

All six earlier target verdicts, the bank's full comment history, and their cited docs/recipes.md were read before the first experiment. No separate target evidence path is cited in those six verdicts. The Zero Hour donor is inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameLogic/Map/TerrainLogic.cpp inside the BFME 1 submodule. Its planar method was read; its applicable getHeight comment is carried into the clean trials. BFME 1's current public method is a five-byte incremental-link thunk and supplies no missing curved algorithm.

## Identity and boundary evidence

Raw BFME 2 inspection is build/bridge-0027fd2a/retail.log. The native entry immediately follows the 300-byte pickBridge body ending in ret 12. The target ends with ret 8 at RVA 0x0027FFF0, and the next native function begins at 0x0027FFF3. The Ghidra inventory independently lists 0x27FD2A with size 713. The rowed 0x002803F9 caller passes position and NULL after isPointOnBridge, then consumes st0 as a height. The receiver accesses agree with other Bridge methods: endpoint positions at +0x0C/+0x18, corners at +0x28/+0x34/+0x40/+0x4C, and the polygon pointer at +0xC8. The curved branch calls rowed Coord3D::normalize at 0x35B6 twice. The plane arm calls rowed Set at 0x7BFC2 and Compute_Intersection at 0x69168. Literal inspection confirms -0, -1, 1 and 1000. Method identity is supported by these target relationships and the donor's planar method; the curved distance blend is derived from BFME 2 retail, not claimed as donor source.

## Measurements

All measurements use BFME_OBJSTORE=off and isolated source paths. probe.py deletes each source's cached object and dependency receipt before align_diff.py. Every emitted body is larger than three quarters of the retail size. These counts are generated from the raw tool results, not the farm score. Positional differences include effects of instruction shifts and are diagnostic only; relocation and branch lines do not decide improvement.

| Trial | Emitted bytes | Structural regions | Memory differences | Register differences | Positional differing bytes |
|---|---:|---:|---:|---:|---:|
| before | 726 | 16 | 30 | 27 | 629 |
| clean | 687 | 11 | 37 | 32 | 639 |
| cross | 730 | 18 | 37 | 34 | 632 |
| rotate | 690 | 14 | 43 | 35 | 634 |
| rotate_inline | 690 | 11 | 38 | 35 | 634 |
| height_staged | 687 | 13 | 37 | 31 | 640 |

The retained body is unchanged, so its positional difference count before and after remains the before row's value. Every alternative increases memory or register differences, including those that reduce structural regions; none qualifies as closer under the assignment's rule. The clean 687-byte body is the smallest straightforward candidate, but is not a replacement bank. No proved externally visible semantic defect was found in the farm body: its volatile self-stores touch stack-local normals and preserve their values. Their extra accesses remain a concern, not proof of a wrong returned result.

## Hypotheses tested

1. A full inline cross product with the vertical axis might explain retail's scratch register copies and late zero. Refuted for this donor helper: its z expression retains products by zero absent in retail, and its alignment is worse.
2. In-place perpendicular rotation might require the old component copies seen in retail. Refuted as a matching repair by direct and inline-member forms; both increase memory/register differences.
3. Staged first/second height interpolation might explain retail's tail register order. Refuted as a matching repair; it increases the structural count against the clean expression and still loses to the bank in memory/register counts.

Each hypothesis, its supporting instruction observations, and its refutation test were written before the associated trials in build/bridge-0027fd2a/hypotheses.md. No additional evidence-backed experiment emerged. Remaining mismatch: the curved branch's split 2+1 movsd copy, late xorps, temporary movaps copies, reuse of the along.y slot for toDY, and the interpolation tail's XMM allocation. No missing callee, type-size discrepancy or boundary problem was found. Do not repeat the earlier flag/compiler/statement-order sweeps without new evidence.

## Raw outputs and reproducibility

All trial sources, helper scripts and raw output remain in build/bridge-0027fd2a/. For each named trial, NAME.align.log is the complete align_diff.py output and NAME.explain.log is the complete explain_mismatch.py output. NAME.metrics.json contains the extracted counts. probes.log and rotation-probes.log record the process results; all six alignment compilations succeeded and all six explain runs reported a mismatch. clean.object.log is unpatched object disassembly. retail.log includes the native caller and normalize body. dest.log records the destination query. prior-verdicts.log records the six earlier verdicts. check-csv-before.log and check-csv-after.log record ledger hygiene; pin-consistency.log records the unchanged pin-map check; record.log records the re_log.py append. No exact byte gate or unmatched-definition check was needed because no Code source or matched row was changed. No background task was started.
