# Closer attack-aim bank

Result: a semantically corrected, measurably closer partial for `?updateInternal@AIAttackAimAtTargetState@@AAE?AW4StateReturnType@@_N@Z`, retail RVA `0x003508C5`, extent 1104 bytes. No source was placed in `Code/`, and no ledger row or pin was added. Work is uncommitted. Input checkout: `b65794c66d4aa9aa20756625c1405954c1f8a889`; reference checkout: `a18d9ed50607e9175de4d6568798d7d73119de09`. Model: `gpt-6.1-sol`.

All eight target verdicts and the additional caller/link verdicts were read. The cited `build/big/aim-visible` evidence is absent in this checkout. Both `aim-goal-accessor-link-20261015/readme.md` and its preceding `aim-goal-inline-link-20261015/readme.md` were reviewed. Previously unsuccessful callee-visibility and owner-integration experiments were not repeated. Every hypothesis and its refuting observation was written before its probes in `build/aim-3508c5-worker/hypotheses.md`.

## Measurements

The raw `align_diff.py` counts are authoritative for comparison. Each trial used a new path, and the actual object path was deleted before each alignment and explanation measurement. Every compilation used `BFME_OBJSTORE=off` and the bank's `/O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /I.` settings.

| Candidate | Emitted bytes | Structural regions | Memory differences | Register differences | Positional differing bytes within retail extent |
| --- | ---: | ---: | ---: | ---: | ---: |
| Original farm bank (`before.cpp`) | 1114 | 27 | 39 | 9 | 783 |
| Final corrected bank (`final.cpp`) | 1109 | 5 | 9 | 1 | 207 |
| Alternative with source ID read at its original site (`goal-pointer.cpp`) | 1104 | 4 | 32 | 41 | 75 |

The final candidate improves all three defect classes over the original bank, without trading one class against another. Relocation and branch counts are excluded from that decision. The four-region alternative is preserved only as scratch evidence because its register count regresses against the original bank. The final score is `0.8125`, the positional matching fraction `(1104 - 207) / 1104`; it uses a different measure from the farm's score and does not determine the alignment ranking. The final body also extends five bytes past the retail extent, which prevents admission.

Raw evidence and receipts: `build/aim-3508c5-worker/before-align.txt`, `before-explain.txt`, `before-metrics.json`, `final-align.txt`, `final-explain.txt`, `final-metrics.json`, and `receipts.jsonl`. All trial sources and raw logs remain in that task folder. `probe.py` reproduces measurements without manually populating shared compile caches. `comments-check.txt` records the preservation of every existing bank comment line, including duplicate metadata lines.

## Identity, ABI, and semantics

Target evidence is in `build/aim-3508c5-worker/wb-retail.txt`. The Ghidra inventory starts a 1104-byte function at `0x3508C5`. Native ECX is the receiver, `[ebp+8]` is tested as a byte, EAX returns `0`, `-1`, or `-2`, and native `ret 4` at `0x350D12` ends the whole body at exclusive `0x350D15`. The matched aim-state update caller and the WorldBuilder twin `0xE1F350`, named `AIAttackAimAtTargetState::updateInternal` in `AIStates.cpp`, corroborate the method identity. Retail independently establishes the state, object, template, weapon, and virtual-call offsets; WorldBuilder's debug-layout offsets were not copied.

The farm bank ran `setTurretTargetPosition` unconditionally after either turret branch. Retail's object setter at `0x3509AE` jumps at `0x3509B3` over the position setter at `0x3509BD`; WorldBuilder and the ZH donor agree. The exclusive `else` is restored. The unsupported volatile self-store, volatile aim-offset member, and unused barrier declaration are removed. The guarded victim-position copy and real double-returning CRT `fabs` declaration are preserved.

The successful new shape uses a const reference to the template's turn-limit member and a scalar snapshot inside the slow-turn branch, plus a scalar aim-offset snapshot. Together these prevent unwanted template promotion and remove repeated aim-offset reads. In that changed lifetime context, caching the goal-position pointer produces retail's explicit `+0x24` address materialization. An ordinary source-ID value snapshot before the final victim-AI checks selects retail's source/weapon register roles. The ID is read across only inline member accesses before the same targeter call, so this introduces no intervening call or changed operation ordering. The remaining eager ID load is explicitly counted as a mismatch.

The semantic donor is `GeneralsMD/Code/GameEngine/Source/GameLogic/AI/AIStates.cpp`, `AIAttackAimAtTargetState::update`, at the reference revision above. Applicable EA comments about dead targets, immobile turrets, angular tolerance, range-object semantics, and targeter ordering were copied into their corresponding places. Donor-only disabled-held naming, removed preattack conditions, obsolete commented-out crush code, and the old debug expression were not asserted as BFME 2 behavior. No donor ABI or layout was accepted without target evidence.

`repair_queue.py dest` offers `AIAttackFireDuringApproachStateUpdateInternal.cpp` only as a neighbor heuristic, with no approved TU. That is a different class. The existing aim-state owner/caller files are `AIAttackAimAtTargetStateOnExit.cpp` and `AIAttackAimAtTargetStateOnExit_Update.cpp`; reconcile the bank there before any future exact landing, rather than treating the heuristic as ownership proof.

## Remaining mismatch and ruled-out hypotheses

The five remaining structural regions are an early `pop ecx` around the aim-delta `fabs` comparison (retail offsets `+0x2FB`/`+0x302`), cleanup interleaved differently with the half-turn-rate multiply (`+0x3E6`/`+0x3ED`), and the eager source-ID load near `+0x3FD`. The one register operand difference is `push esi` versus retail's `push [esi+0x74]`. The nine memory differences printed for the final candidate are unpatched absolute global/constant operands; the raw tool counts are retained rather than silently reclassified. All direct calls resolve. The extent and full-byte mismatch remain failures.

Ruled out by saved probes: float casts and inline float wrappers around CRT fabs add stores; reversing comparison operands adds instructions; source-position caching promotes an unwanted live range; a source-ID member reference, orientation cache, explicit source receiver, alternate victim-AI guard, named preventing boolean, and fallback-pointer scope do not close the register gap. Direct boolean assignment changes stack homes without improving alignment. Diagnostic-only source sinks show a one-reference priority gap, but no sink or synthetic operation is retained. No inline assembly, emitted bytes, naked function, optimization pragma, new alias, or new pin was introduced.

The candidate is a reusable partial, not an exact recovery. CSV/pin checks and final comment/semantic assertions have raw outputs under the task folder. The coordinator can rerun them locally; no verification runner, network operation, git mutation, or background service was started.
