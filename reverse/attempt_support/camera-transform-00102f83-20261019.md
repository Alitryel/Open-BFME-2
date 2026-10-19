# Camera transform at RVA 0x00102F83

Result: closer bank, not byte exact. Symbol `?rva00102F83@W3DCamTransform@@QAEXPAUCameraTransformInput@@@Z`, retail extent 4299 bytes, intended home `Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DCamTransform.cpp`. No production source, header, pin or function-ledger change. Model gpt-6.1-sol.

BFME 2 input commit: `6f2cb58a14cdbc926ff80cb09be62daad12e64b3`. Reference pointer and checkout: `a18d9ed50607e9175de4d6568798d7d73119de09`. Prior provenance names older donor revisions; this change is supported by target bytes rather than a new donor identity claim. The GeneralsMD W3DView::buildCameraTransform and WWMath matrix declarations were reviewed. Applicable donor algorithm comments were restored, and every existing bank comment line is retained.

## Measurements

All sources were compiled with BFME_OBJSTORE=off and a fresh object. The first bank cl line remains `/I. /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /ICode/Libraries/Include/Lib`; default compiler MSVC 7.1. Raw align_diff reports are the selection criterion. Positional differing bytes compare verifier-patched streams, including missing tail bytes; that count alone is not evidence of improvement. Those patched data relocation values are not semantic evidence once instruction offsets diverge.

| Trial | Emitted bytes | Structural regions | Memory differences | Register differences | Positional differing bytes |
|---|---:|---:|---:|---:|---:|
| before | 4278 | 76 | 110 | 99 | 2794 |
| h1b_join | 4270 | 74 | 108 | 91 | 2736 |
| h2_constraint | 4289 | 77 | 148 | 106 | 3432 |
| h3_donor_mul | 4278 | 75 | 109 | 100 | 2826 |
| h3b_join_mul | 4276 | 81 | 116 | 102 | 2981 |
| h4_shared_rotate | 4270 | 74 | 108 | 91 | 2736 |
| h5_donor_set | 4317 | 79 | 123 | 106 | 2953 |
| candidate | 4270 | 74 | 108 | 91 | 2736 |

The final candidate repeats H1b's measurements exactly. Relocation and branch lines are excluded from the improvement decision. The candidate has no unresolved callees. Its measured full patched-byte sequence fitness is 0.887151359552; the unchanged bank reproduces 0.866969802961. This differs from the historical score convention, so historical fitness numbers were not used for acceptance.

## Evidence and change

Ghidra inventory declares the start and extent. The preceding matched transitionLiveMode ends at this start. Native VA 0x00502F83..0x0050404E is a complete RET4 body with a biased EBP frame and sub esp,0x88. WorldBuilder VA 0x007E3040..0x007E7303 is the debug twin and also ends with RET4. The receiver is supported by the matched transitionLiveMode call at native +0xAEC; original function and descriptor names remain unproved. Keep the address-derived function name.

Native +0x7B5..+0x7BA computes targetZAdjustment + pos.z in the live branch; +0x7CF..+0x7D9 computes targetZAdjustment + groundLevel in the other branch. Both paths join before adding targetPos.Z at +0x7E5. WB +0x155C..+0x1565 and +0x219F..+0x21A8 independently support this grouping. The bank now computes a branch-selected targetHeight and adds it after the join. The live branch's second rotations and all source and target translations remain present. The candidate now emits the corresponding shared addition at its +0x7E6, with different XMM registers.

The raw identity probe compares all 36 call destinations and virtual slots in order, and checks the RET4 and 0x88 frame. It passes. This confirms those relationships, not the original entry-point spelling or every argument's semantic type.

## Ruled out and remaining

Direct ordered X upper-constraint selection regressed all alignment classes. Restoring donor two-argument mulVector3 lowered regions and memory alone but increased registers, and combining it with H1b regressed all classes. Sharing Rotate_X/Y/Z row temporaries emitted the same body as H1b. Restoring Matrix3D constructor/Set overload layering regressed all classes. These are not accepted. Initial h1_join.cpp is invalid because a CRLF-specific edit omitted the final target-height addition; all of its measurements are excluded. Its source and raw logs remain for audit. The first H3 source-generation assertion failed before a body was emitted; the corrected trial is the one measured above.

Remaining: X constraint upper-bound branch/register choice at native +0x1EF; zoom/offset Z multiplication operand choice at +0x2AD; first matrix spill-slot permutations at +0x39A..+0x3CF; pitch and second-rotation scheduling at +0x3F4..+0x7C3; realZoom reload/ternary and height-subtraction shape; position-hold SSE allocation; shake and final Rotate_Y register scheduling at +0xF75..+0xFD2. The bank still embeds a private canonical Coord3D view with lengthSqr, which must be reconciled through its contract/header before production admission. The existing live-mode global spelling also predates the current home-unit data-name repair; no new data binding is admitted here.

## Raw records

Task folder: `build/worker-00102f83-20261019/`. Each measured trial retains its `.cpp`, `.align.raw.log`, `.explain.raw.log`, `.probe.raw.log`, `.metrics.json` and `.patched.bin`. `before.cpp` preserves the original bank byte for byte. `candidate.cpp` is the accepted body. `hypotheses.md` records hypotheses and refutation conditions before trials. `native.raw.log`, `wb.raw.log` and their binaries retain target disassembly; `identity.raw.log` retains the call and ABI assertions; `candidate-comments.raw.log` records comment preservation. `dest.raw.log` records the source-home query. `record.raw.log` records re_log.py's result. Nothing was compiled directly through build.compile_source. No git write command, network operation, background task or production-source edit was performed.

Started 2026-10-19 07:38:11 UTC; banking at 2026-10-19 07:47:23 UTC; elapsed 9.21 minutes from UTC timestamps. Additional post-bank checks are retained in the same task folder.

Post-bank checks: fresh compilation through align_diff on the actual bank passed and reproduced the candidate measurements (`bank.align.raw.log`). `tools/check_csv.py` passed (`check-csv.raw.log`). `tools/pin_consistency.py --check` passed (`pin-consistency.raw.log`). `candidate.explain.raw.log` reports the expected size mismatch, so there is no exact-byte claim and no add_match or production build. Final bank suffix and original-comment preservation assertions passed (`final-review.raw.log`). All logs are under the task folder. No background process was started. Finished 2026-10-19 07:48:08 UTC; elapsed 9.96 minutes.
