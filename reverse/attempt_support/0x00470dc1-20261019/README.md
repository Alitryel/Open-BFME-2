# Closer bank for 0x00470DC1

Result: a closer fragment bank, with every old comment preserved. The function is not exact. The authoritative comparison table is [measurements.tsv](measurements.tsv); `baseline` is the old bank and `bank_reconstructed` reproduces the replacement. Its structural, memory and register counts all improve. The patched positional byte count is recorded separately and did not determine selection. Relocation and branch differences were not treated as defects. The score is an estimate for queue ranking.

Symbol: `?rva00470DC1@HordeContain@@UAEXXZ`. Retail RVA: `0x00470DC1`. Retail extent: 1699 bytes. Home source: `Code/GameEngine/Source/GameLogic/Object/Contain/HordeContainIface11CSlots.cpp`. Base commit: `0d8d778ff93a2a6a95bceba097f36d17be78eb6b`. No commits, pins or functions.csv rows were added. The sole ledger-related change is the verdict appended by re_log.py.

The home source is unchanged. [best.patch](best.patch) preserves the complete candidate as a small patch against that source. The bank remains a fragment: apply its original commented view patch, change the new slot record's count to unsigned, then append its local constructor view and body. A fresh reconstruction from the saved bank reproduced the selected trial's code, emitted bytes, relocations and measurements. Do not enter the candidate as matched until its exact-byte comparison passes.

## Evidence and remaining work

Retail's primary vtable at VA 0x00C45050 selects this body in slot 35; the next slot calls RVA 0x00474842. The full body ends with RET immediately before the next prologue at RVA 0x00471464. ECX carries primary this, with the separate +0x11C interface used for its virtual calls. The address-derived virtual no-argument member name remains appropriate. Original method identity and high-level record names remain unproved. The complete retail disassembly and provider inventory are in `build/worker_470dc1/retail.txt`; the ordered direct-call comparison is in `build/worker_470dc1/callsite_proof.log`. No new donor method or layout identity is claimed.

The candidate corrects the intermediate release-band copy to use the member's current position, as retail's ESI dataflow requires. It uses member-wise constructor views for local triples, zeros the facing vector before its subtractions and scalarizes the perpendicular difference and scaled side. The existing Coord3DCtorView.h and the sibling HordeDelta2D view support this constructor distinction. [hypotheses.md](hypotheses.md) records each hypothesis, refutation criterion and rejected trial.

The remaining mismatch is compiler shape: retail shares its ID, attacker spill and length spill at [ebp-0x18], while the candidate keeps ID/length at [ebp-0xC] and attacker at [ebp-0x30]. Several other frame slots consequently differ. Retail reuses ESI for GameLogic through both attack-pair lookups and then reloads attacker; an explicit cache instead spills GameLogic and keeps attacker in ESI. Scaling preload/store schedules, FST versus FSTP/FLD/FXCH for length, and the shared held-copy tail also differ. Named-ID lifetime changes, caching, direct component initialization, scale/add spelling, fresh scalar copies, guard inversion, shared-copy control flow, returned-position construction and assignment-in-comparison were tested. No further supported repair was identified.

The four prior verdicts and the complete bank comments were read before experiments. Their explicit scratch evidence `build/wb_470dc1_full.txt` is absent in this checkout. The cached parent-audit row under `reverse/attempt_support/crack-g-parents-20261014/parent-audit.tsv` was also checked.

## Checks and raw logs

| Check | Result | Raw output under build/worker_470dc1/ |
|---|---|---|
| Old-bank align_diff and byte comparison | Baseline measured | baseline.align.log; baseline.count.log; baseline.explain.log |
| Replacement align_diff and byte comparison | Closer; exact comparison fails | bank_reconstructed.align.log; bank_reconstructed.count.log; bank_reconstructed.explain.log |
| Ordered direct-call targets | Pass | callsite_proof.log |
| find_declared_unmatched on unchanged home | Pass | frozen.before.log |
| build.sh on unchanged home | Pass | home.build.local.log |
| check_csv | Pass | check_csv.log |
| pin_consistency --check | Pass | pin_consistency.log |
| Source and comment preservation | Pass | handoff.final.log |

The first home build could not touch the shared object store outside the sandbox (`home.build.log`). Retrying with the documented `BFME_OBJSTORE=off` option passed. The first preservation assertion compared whole scratch files including added comments and failed (`handoff.log`); the final check compares code plus emitted bytes and relocations and passes. The failed h6held diagnostic is retained in `h6held.explain.log`; its final relocation exceeded the supplied extent, so that trial was rejected without changing the extent. Other trials and their raw outputs remain under `build/worker_470dc1/`. No background job remains active.

Start clock: 2026-10-19 02:23:14 UTC. Handoff elapsed at generation: 18.98 minutes. model=gpt-6.1-sol. Every changed path, including scratch sources and object-cache outputs, is listed in `build/worker_470dc1/changed_paths.txt`.
