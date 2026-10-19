# PointGroup UV helper assignment

## Result

Blocked. Preserve `reverse/attempts/0x0017d770.cpp` byte for byte with all contributor comments. The fresh before and after measurements both emit 1583 bytes, with 11 structural regions, 5 memory differences, 5 register differences, and 510 positional differing bytes. The latter count is diagnostic only. The lowest positional count among rejected trials is 218, but its alignment worsens in every defect class. No candidate qualifies for a closer bank. No source, function-ledger, pin, header, or verifier change is proposed.

Symbol: `?rva00916CD0@PointGroupClass@@QAEXPAEHH@Z`. Retail boundary: `0x0017D770`, 1583 bytes. `repair_queue.py dest 0x0017D770` names `Code/Libraries/Source/WWVegas/WW3D2/PointGroupClassDiffuseFill.cpp` by neighbour heuristic and explicitly reports no approved TU. The unmodified bank remains the source of the best attempt; no reconstruction was put in Code.

## Inputs and evidence

The BFME2 checkout is `8a0843b9cf6fd749f00fca6cc938eb07e288a81c`; the BFME1 checkout is `a18d9ed50607e9175de4d6568798d7d73119de09`. The original bank cites donor revision `6583b3c1ff`. All nine existing verdicts and `reverse/attempt_support/0x0017d770/readme.md` were read, along with the current donor `reference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2/PointGroupClassUVFill.cpp` and its `targets/game/reverse/identity_evidence/00916cd0-pointgroup-uv.md`. The previous handoff's `build/worker-17d770/` is absent here; its unavailable raw artifacts were not treated as independently reproduced evidence.

Target evidence was re-derived from the complete body and caller. Ghidra lists the start and extent; retail ends in `ret 12` at `0x0017DD9C`, followed by INT3 at `0x0017DD9F` and the next function at `0x0017DDA0`. The body contains no calls. The array updater calls this entry at `0x0017F3DE` with ECX=this and three stack arguments. Retail directly reads the grid byte at this+0x20, mode at this+0x2C, default-frame byte at this+0x49 and the optional four-float address. The nonnull frame-pointer path does not read frame bytes; it repeats the first triangle or quad table entry. The null path masks the default frame, optionally transforms the selected entry in place, then copies it. This independently agrees with the bank and BFME1 helper. Keep the address-derived name; no semantic method name or rectangle type is newly asserted. The broader member names/layout remain donor evidence where not witnessed by those target accesses.

The corrected raw complete disassembly, caller and boundary output is `build/uv17d770/identity-retail.log`. The initial diagnostic also read preceding data at an unaligned instruction boundary; it is retained as `identity-initial.log` and is not boundary evidence. Canonical-header dependency hashes are in `build/match/build_uv17d770_before.deps.json`; the actual compiler command is retained in `build/uv17d770/compiler-command.log`. All measurements set BFME_OBJSTORE=off, use unique trial paths and remove their object and dependency receipt before measuring. Every trial checks build/STOP_WORKER immediately before compiling. No network, git-writing command, claim, background monitor, or restricted runner was used.

## New hypotheses and refutations

H1 was recorded before testing in `build/uv17d770/hypotheses.md`. Retail's second quad X product folds the UV memory operand, while the bank loads it. Based on the documented assignment-destination precedence, compound X/Y multiply-then-add updates and reference-bound updates were tried without changing arithmetic order. X alone emits identical bytes. Y and XY cut positional differences but worsen structural, memory and register alignment; reference-bound updates also worsen alignment and size. This hypothesis did not produce a closer body.

H2 was also recorded before testing. Canonical Vector2 assignment uses reference-returning indexed access. Direct field copies and inline float-pair/reference-returning helpers tested whether exposing the same field read/write order differently would restore the nonnull branch's missing ECX-to-EDX UV-pointer copy. The two helper forms emit exactly the unchanged body in both scopes. Direct fields alter allocation and unrolling substantially and worsen all alignment classes. No scope, barrier, flag, equal-arm or counter search from the earlier handoff was repeated. There is no justified follow-up from these results in this assignment.

| Trial | Emitted bytes | Structural regions | Memory differences | Register differences | Positional differing bytes |
|---|---:|---:|---:|---:|---:|
| after | 1583 | 11 | 5 | 5 | 510 |
| before | 1583 | 11 | 5 | 5 | 510 |
| h1-ref | 1591 | 19 | 18 | 17 | 758 |
| h1-x | 1583 | 11 | 5 | 5 | 510 |
| h1-xy | 1583 | 12 | 15 | 13 | 218 |
| h1-y | 1583 | 12 | 15 | 13 | 218 |
| h2-fields-all | 1534 | 37 | 296 | 69 | 1503 |
| h2-fields-nonnull | 1559 | 27 | 146 | 41 | 1497 |
| h2-pair-all | 1583 | 11 | 5 | 5 | 510 |
| h2-pair-nonnull | 1583 | 11 | 5 | 5 | 510 |
| h2-reference-all | 1583 | 11 | 5 | 5 | 510 |
| h2-reference-nonnull | 1583 | 11 | 5 | 5 | 510 |

The remaining mismatch starts at +0x1E: retail initially loads VertexUV into ECX and copies it to EDX at +0x31; the bank loads EDX directly. The argument/log2 loads and induction setup differ. The default branch loads VertexUV after its table computation instead of before its mode split, and its triangle index/table allocation differs. The second quad X multiply has a different SSE operand form. Frame-mask allocation is already EDI in both current bank and retail; older notes describing EDX versus EDI are stale for this bank. Alignment's memory count includes unpatched DIR32 operand differences, so these are not five independently established layout defects.

## Verification and resumption

Raw trial outputs are `build/uv17d770/h1-run.log` and `h2-run.log`. Each trial retains its source, raw align_diff and explain_mismatch logs, extracted disassembly, measurement log and JSON under that task directory. Before and after logs use the prefixes `before` and `after`. The align tools exit zero when reporting mismatches; all ten trials compiled but none passed exact byte comparison. No add_match or build.sh gate was run because no exact Code body exists. No find_declared_unmatched check is applicable because no Code source changed.

`check_csv.py`: exit 0, raw log `build/uv17d770/check-csv.log`. `pin_consistency.py --check`: exit 0, raw log `build/uv17d770/pin-consistency.log`. `build/uv17d770/final-check.log` verifies bank preservation, emitted-byte equality for unchanged trials, and append-only verdict recording. The unchanged bank is the best resumption source. Further work needs new compiler/dataflow evidence for the UV-pointer split and default-path load scheduling, rather than a smaller positional byte count.

Measured elapsed time: 5.507 minutes, from 2026-10-19T05:17:02+00:00 to 2026-10-19T05:22:32.418225+00:00; clock receipt `build/uv17d770/timing.json`. Model: gpt-6.1-sol. Changes remain uncommitted.
