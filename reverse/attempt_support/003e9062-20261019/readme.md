# Blocked: skirmish special power readiness

`?evaluateSkirmishSpecialPowerIsReady@ScriptConditions@@IAE_NPAVParameter@@0@Z`, RVA `0x003E9062`, 404 bytes. Result: blocked; the existing `reverse/attempts/0x003e9062.cpp` bank is retained byte for byte. No source, pin, compiler setting or function-ledger change is proposed. BFME 2 input: `0a64aa2c20ddcdffbb141e63677e11cdc62e991f`; BFME 1 input: `a18d9ed50607e9175de4d6568798d7d73119de09`; compiler: MSVC 13.10.3077. Model: gpt-6.1-sol. Measured investigation duration at verdict: 10.44 minutes, from 2026-10-19 02:12:00 UTC to 2026-10-19 02:22:26 UTC.

## Remaining mismatch

The bank emits a bottom-loaded assignment-condition loop. Native instead loads Object into EDI at +0xD2, tests it, skips the next iteration's reload, then performs a separate null test at +0xDE. The native bottom at +0x14A is `cmp [ebp-0x34],0` and branches to the Object reload at +0xDB. The bank omits those checks/reload and uses a load to ECX, test and copy to EDI at the bottom. The reference done()+cur()+null-check shape restores neither all those operations nor the native allocation: EDI becomes the list iterator and pPower uses EBX. A valid next attempt needs evidence that explains both constraints together.

## Measurements

Counts below are generated from the raw `align_diff.py` output and patched-byte comparisons in `build/worker-003e9062/measurements.json`. Positional byte counts are diagnostic only and did not determine bank quality. All successful probes compile with no unresolved calls. Six memory lines in every row are absolute global relocations that align_diff classifies as memory; those are not defects. Relocation and branch lines are excluded from the table.

| Trial | Emitted bytes | Structural regions | Memory lines | Register lines | Positional differing bytes |
|---|---:|---:|---:|---:|---:|
| baseline | 391 | 4 | 6 | 0 | 186 |
| guard_do | 402 | 11 | 16 | 5 | 238 |
| guard_do_nested | 402 | 11 | 16 | 5 | 238 |
| typed_iterator | 402 | 11 | 16 | 5 | 238 |
| visible_advance | 402 | 11 | 16 | 5 | 238 |
| member_mask_assign | 391 | 4 | 6 | 0 | 186 |
| member_mask_done | 402 | 11 | 16 | 5 | 238 |
| native_compare_done | 402 | 11 | 16 | 5 | 238 |

The bank remains the best candidate under the required structural-first comparison. Exactness fails for every trial. No score or partial verdict is issued.

## New hypotheses tested

1. An explicit initial guard plus do/while could preserve the native rotated loop while changing use weights. Both goto-advance and nested-condition forms produced the same unsuccessful allocation. `guard_do.cpp` and `guard_do_nested.cpp` preserve them.
2. The real virtual-inheritance member-pointer type could change alias/lifetime analysis compared with Object* plus byte padding. The typed iterator passes a 24-byte size assertion and preserves the provider's inherited-vbptr layout, but the caller is unchanged. `typed_iterator.cpp` preserves it. The initial single-inheritance forward-declaration trial fails C2292; its reproduced raw output is `typed_forward_failure.explain.log`.
3. Visible Object iterator advance could change the caller's allocation, even when not inlined. `visible_advance.cpp` keeps the direct call, and its emitted 32-byte advance independently matches retail exactly with no unresolved names (`advance-provider.log`); the caller remains unchanged. Placing the definition before completing Object reproducibly causes compiler error C1001 (`visible_early_failure.explain.log`).
4. A genuine one-word DisabledMask member could change codegen relative to the bank's reinterpret_cast through byte padding and its seven-word generic BitFlags view. A BitFlags<11> specialization at Object+0x1C8 reproduces both original outcomes unchanged. `member_mask_assign.cpp` and `member_mask_done.cpp` preserve these supported layout trials.
5. The current owner's TU-local free list-iterator comparison could differ from the original inherited STLport member comparison. Removing the local overload leaves the done-loop output unchanged (`native_compare_done.cpp`). This refutes the dependency difference as a cause; no second assignment-form trial was needed.

Each hypothesis, its evidence and its refuting observation was written before its probe in `build/worker-003e9062/hypotheses.md`. STOP_WORKER was checked before every probe. The prior four verdicts cite no separate evidence path; their raw rows are preserved in `prior-verdicts.log`. No prior flag or barrier sweep was repeated.

## Identity, ABI and placement

Native boundary is `[0x003E9062,0x003E91F6)`: the preceding RET 4 ends at entry, this body returns with RET 8, and the next prologue begins at the limit. Ghidra independently records 404 bytes. Condition 85's jump-table entry at VA 0x007EC5C0+(85-5)*4 is VA 0x007EB94B; its call at 0x007EB967 goes directly to this body. The matched template initializer labels condition 85 SKIRMISH_SPECIAL_POWER_READY. Together with the Zero Hour named evaluator and matching behavior, this supports the bank's real name rather than just its bytes. Target loads independently establish Parameter cache +0x20, GameLogic frame +0x40, Object disabled mask +0x1C8, isReady slot 4 and getReadyFrame slot 0x10. Direct calls agree with current ledger/pins for string copy, power lookup, player-mask iteration, team-member iteration, status bit 2, DisabledMask any, module lookup, canUseSpecialPower and iterator advance. Donor source supplies algorithm/name leads; target calls and accesses supply ABI and offset evidence.

`repair_queue.py dest 0x003E9062` currently recommends `Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditions_EvaluateSkirmishCanFireSpecialPowerOnTeam.cpp` by its nearest-neighbour heuristic; it has no approved whole ScriptConditions TU. The bank's historical append unit is `Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditions_evaluateTeamStateIs.cpp`. All trials use a declarations-only prelude from that unit and its effective regional flags: /O1 /arch:SSE /G7 with its remaining include/define/EH flags. `inputs.json` stores the exact flags and input hashes. No reconstruction was placed in Code.

## Raw evidence and reproduction

All trial sources, complete explain and align outputs, patched compiled bytes, stats, initial hypotheses, failed compiler reproductions, input hashes, retail disassembly and probe scripts remain under `build/worker-003e9062/`. For each successful trial NAME, read NAME.explain.log and NAME.align.log; rerun `python build/worker-003e9062/probe.py NAME` only when justified. `identity-dispatch.log` records the native case-85 call; `retail-disasm.txt` records the complete target and neighbouring instructions. `record-blocked.log` holds the re_log.py receipt. `check_csv.log`, `pin_consistency.log` and `final-checks.json` hold final checks, exit codes and unchanged-bank/owner hash assertions. No background tasks were started. All changes remain uncommitted.
