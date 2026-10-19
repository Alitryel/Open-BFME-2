# EmotionTrackerUpdate update handoff

Result: closer partial for `?update@EmotionTrackerUpdate@@UAE?AW4UpdateSleepTime@@XZ`, RVA `0x004B1633`, retail extent 2200 bytes. The bank is `reverse/attempts/0x004b1633.cpp`. No production source, matched row or pin changed. `repair_queue.py dest` reports `EmotionTrackerUpdateDtor.cpp` by its neighbour heuristic, while its proposed TU and the native/WB source strings identify `Code/GameEngine/Source/GameLogic/Object/Update/EmotionTrackerUpdate.cpp`. A future exact landing should reconcile that proposed TU rather than add update to the destructor unit merely because it is nearby.

Input checkout: `04a6b1d12b2a4b7bc81e7ed58ccb3c2cfebdc2d7`. BFME 1 pointer inspected without updating: `a18d9ed50607e9175de4d6568798d7d73119de09`. Compiler: default MSVC 7.1, inherited `/O1 /arch:SSE /G7 /MD /EHsc`, STLport marker and `_STLP_USE_STATIC_LIB`. `BFME_OBJSTORE=off` was set for every compilation and measurement. Start: 2026-10-19T07:27:49+00:00. Verdict time: 2026-10-19T07:49:20.288766+00:00. Measured elapsed at verdict: 21.52 minutes. model=gpt-6.1-sol.

## Evidence and corrected semantics

All six target verdicts and the complete original bank were read before experiments. None of those verdicts cites a separate retained evidence path. Their WB lead was read in full as decompiled control-flow evidence and checked against native and annotated assembly. This body was reconstructed from the target; no donor function was ported. The BFME 1 and Zero Hour emotion-update source absence was not treated as a reason to repeat their old dependency audits.

Native entry `0x008B1633` starts an EH prologue immediately after the previous function's RET at `0x008B1632`. It returns at `0x008B1ECA`, immediately before the owned xfer entry at `0x008B1ECB`. This is a complete function start, not a fragment or an overlap. WB `0x01230DD0` names `EmotionTrackerUpdate::update`, names its official source file and carries assertions 343 through 604. The native object/data loads, named filter constructor and family call graph independently corroborate the match. See raw `build/emotion_4b1633/retail.txt`, `retail-callees.txt`, `wb-retail.txt` and `wb-decomp.c`.

The update is a no-argument thiscall returning the int-sized UpdateSleepTime enum. Its receiver is root+0x10: data/object are at receiver-0xC/-8; flags, expiry, target IDs, vector and active nugget are at receiver+0x14/+0x20/+0x50/+0x80/+0x8C. Selection and PulseEmotion receive root, not the secondary receiver. Native selection returns a pointer in EAX and RETs without arguments; activation takes Object* plus duration and RETs 8; deactivation RETs without arguments; the private direction helper takes a 32-bit word and float and RETs 8. Native entry/return sites and the target caller's argument setup were checked; the helper's semantic name remains unknown. The owned CanBeActivatedFor declaration and GameLogic/PartitionManager canonical headers are used.

The previous bank was semantically wrong: it double-decremented the countdown, read data/object through the wrong adjustment, shifted several fields through an extra implicit vptr, walked nuggets as objects, treated the nugget entry pointer as a kind, passed the wrong shroud receiver/arguments, omitted target and container-change paths, reversed the probability comparison and expired only on strict greater-than while clearing one shared flag. The replacement restores the system ObjectID scan with nested nugget eligibility scans, the three target roles, correct root calls, forced activation duration, container normalization and per-slot frame >= expiry cleanup. The two retail strings, including case and the random-call line 0x25E, were checked directly. This is a static target-flow audit; no runtime equivalence or exact-byte claim is made.

All 13 inherited comment-only lines and all 28 original inline-comment lines remain verbatim. Stale field annotations are retained inside a clearly labelled evidence comment. The first inherited cl line is unchanged; no later cl line was introduced.

## Measurements

All probes are n=1. Counts are from the unmodified `tools/align_diff.py`; relocation and branch lines are excluded from the improvement decision. The original bank emits more than three quarters of retail, so ordinary region comparison applies. The packaged candidate improves every defect class relative to the original bank. The score 0.86233 is the fraction of retail instructions outside structural regions and aligned memory/register defects: `1 - (15 + 54 + 22) / 661`. It is a queue estimate, not exact-byte coverage.

| Trial | Emitted bytes | Structural regions | Memory differences | Register differences | Raw alignment log |
| --- | ---: | ---: | ---: | ---: | --- |
| before | 1701 | 85 | 116 | 69 | [before.align.log](../../../build/emotion_4b1633/before.align.log) |
| h1 | 2153 | 42 | 165 | 66 | [h1.align.log](../../../build/emotion_4b1633/h1.align.log) |
| h2 | 2164 | 29 | 89 | 67 | [h2-valid.align.log](../../../build/emotion_4b1633/h2-valid.align.log) |
| h3a | 2164 | 29 | 89 | 67 | [h3a.align.log](../../../build/emotion_4b1633/h3a.align.log) |
| h3b | 2172 | 24 | 57 | 26 | [h3b.align.log](../../../build/emotion_4b1633/h3b.align.log) |
| h4 | 2172 | 24 | 57 | 26 | [h4.align.log](../../../build/emotion_4b1633/h4.align.log) |
| h5 | 2194 | 22 | 101 | 21 | [h5.align.log](../../../build/emotion_4b1633/h5.align.log) |
| h6 | 2166 | 22 | 94 | 32 | [h6.align.log](../../../build/emotion_4b1633/h6.align.log) |
| h7a | 2184 | 21 | 57 | 25 | [h7a.align.log](../../../build/emotion_4b1633/h7a.align.log) |
| h7b | 2174 | 22 | 57 | 24 | [h7b.align.log](../../../build/emotion_4b1633/h7b.align.log) |
| h7c | 2172 | 24 | 57 | 26 | [h7c.align.log](../../../build/emotion_4b1633/h7c.align.log) |
| h8a | 2186 | 19 | 57 | 23 | [h8a.align.log](../../../build/emotion_4b1633/h8a.align.log) |
| h8b | 2174 | 19 | 94 | 31 | [h8b.align.log](../../../build/emotion_4b1633/h8b.align.log) |
| h9a | 2189 | 19 | 56 | 24 | [h9a.align.log](../../../build/emotion_4b1633/h9a.align.log) |
| h9b | 2187 | 16 | 54 | 23 | [h9b.align.log](../../../build/emotion_4b1633/h9b.align.log) |
| h10 | 2193 | 16 | 54 | 22 | [h10.align.log](../../../build/emotion_4b1633/h10.align.log) |
| h11 | 2187 | 16 | 56 | 26 | [h11.align.log](../../../build/emotion_4b1633/h11.align.log) |
| handoff | 2193 | 16 | 54 | 22 | [handoff-packaged.align.log](../../../build/emotion_4b1633/handoff-packaged.align.log) |

Positional gate-patched differing bytes, including missing tail bytes: 2053 before and 1249 after. Positional differences excluding object relocation slots: 1893 before and 1094 after. The positional counts are diagnostic only; unresolved calls and shifted relocation slots prevent interpreting them as exact-match evidence. Raw outputs: `build/emotion_4b1633/before.object.log`, `handoff.object.log`, `before.explain.log`, `handoff.explain.log`. Machine-readable measurements and hashes are in `build/emotion_4b1633/measurements.json`.

## Experiments and remaining work

The hypotheses, retail locations and falsifiers were written before each trial in `build/emotion_4b1633/hypotheses.md`. Component-wise position copying removes MOVSD's ESI/EDI reservation. WB's explicit no-closest flag branches restore the entry register allocation. An inline bool accessor restores the two native SHR/TEST sequences; a bitfield spelling does not. Inline getters restore player-index preloads. The actual STLport vector restores the address-of-end loop and SSE radius schedule. Equality operand swaps do not control call order. Sequenced rank calls introduce spills or worse allocation, including when combined with the status accessor. The direct activation receiver variant and the first-radius local both regress a defect class and were rejected. An explicit range bool is retained because its complete measurements dominate the earlier bank; its materialized branch remains a mismatch.

The remaining structural differences are the range-bool materialization and initialization schedule, first shroud-call position scheduling, rank-comparison lifetimes, selected-nugget/target-ID caching and the merged activation lookup calls. Stack homes also differ. Two direct call symbols remain unresolved: `?rva004B13D8@Rva004B13D8@@QAEPAVEmotionNugget@@XZ` (retail 0x004B13D8) and `?rva004DCC84@Rva004DCC84@@QAEXPAVObject@@H@Z` (retail 0x004DCC84). Their ABIs were checked; no pin or provider claim was added. Full linking and vtable-provider reconciliation remain unverified. The closer result is established by all-class alignment gains, not a smaller positional byte count or a shorter body.

## Checks and changed paths

Candidate compilation and align_diff: PASS, raw `build/emotion_4b1633/handoff-packaged.align.log`. The bank itself was freshly compiled and reproduces the same counts in `build/emotion_4b1633/banked.align.log`. Every trial source and raw output is retained under `build/emotion_4b1633/`. Exact comparison: FAIL as expected for this partial; raw `build/emotion_4b1633/handoff.explain.log` reports the two unresolved calls and nonzero differences. Comment preservation: PASS in `build/emotion_4b1633/comment-preservation-final.log`. Summary dominance assertion: PASS in `build/emotion_4b1633/measurements-final.log`. `check_csv.py`: PASS in `build/emotion_4b1633/check-csv.log`. `pin_consistency.py --check`: PASS in `build/emotion_4b1633/pin-consistency.log`. No build.sh exact gate, unmatched-definition admission or add_match was run because no production match is claimed.

Reviewable changes are this handoff, `reverse/attempts/0x004b1633.cpp` and the re_log.py append to `reverse/re_attempts.log`. Scratch files and derived object/dependency caches are enumerated in `build/emotion_4b1633/manifest.txt`. All changes remain uncommitted. No subagent, network action, claim, forbidden runner or persistent background task was started.

The first whitespace check failed on CRLF endings in the newly generated bank payload. Only the bank, measured handoff source and this new document were normalized to LF, with identical content lines asserted in `build/emotion_4b1633/normalize.log`. `git diff --check` then passed (raw `build/emotion_4b1633/diff-check-after.log`; the remaining output is an unrelated inaccessible global Git ignore-file warning). A fresh bank compile after normalization reproduces the measurements in `build/emotion_4b1633/banked-lf.align.log`. Final raw byte/relocation equality and inherited-comment checks are in `build/emotion_4b1633/closeout-final.log`; the final clock reading is in `build/emotion_4b1633/final-receipt.json`.
