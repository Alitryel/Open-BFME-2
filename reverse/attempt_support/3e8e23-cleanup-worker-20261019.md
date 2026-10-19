# ScriptConditions cleanup handoff

Result: blocked. The bank reverse/attempts/0x003e8e23.cpp remains byte-for-byte unchanged (SHA256 030855967c8f2021a5207e98ffe1564ae16c5000d39e3405623107c465cda552); no reconstruction was placed in Code and no row, pin, header or compiler setting was changed. Symbol `?rva003E8E23@ScriptConditions@@IAE_NPAVParameter@@000@Z`, native interval 0x003E8E23 through 0x003E8FED, extent 459 bytes. `repair_queue.py dest` still reports Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditions_evaluateTeamStateIs.cpp as a neighbour heuristic and ScriptConditions.cpp as the proposed original home, with no usable approved TU.

## Measurements

The table is generated from build/worker-3e8e23-cleanup/metrics.json. Positional counts mask COFF relocation slots and include missing or excess bytes; alignment classes decide closeness. Four raw memory differences in every report are absolute-global relocation placeholders, leaving two real memory differences.

| Trial | Emitted bytes | Structural regions | Raw memory differences | Register differences | Masked positional differing bytes |
|---|---:|---:|---:|---:|---:|
| baseline | 462 | 2 | 6 | 1 | 20 |
| h1-true-boundary | 462 | 2 | 6 | 1 | 20 |
| h1-dtor-start | 462 | 5 | 6 | 1 | 32 |
| h1-dtor-end | 462 | 2 | 6 | 1 | 20 |

No trial improves the bank. The true-boundary and destructor-end variants emit the identical raw body SHA256 as baseline. The destructor-start variant adds instruction-order differences at both exit cleanups. Every direct call resolves. The sole existing cleanup defect starts at +0x1B6 (native RVA 0x003E8FD9): test ecx,ecx instead of xor eax,eax plus cmp ecx,eax, eax instead of edx for the virtual-call register, immediate zero instead of push eax, and an extra jump with a separate null-arm xor. The bank is three bytes longer than the proven retail extent and must not be admitted as matched.

## Hypothesis and refutation

Before compilation, build/worker-3e8e23-cleanup/hypotheses.md recorded H1, its retail and prior-barrier evidence, and the alignment observation that would refute it. A compiler barrier before the true return or at the inline temporary destructor boundary might have preserved zero sharing without adding machine operations. All three placements refuted that prediction. No previously rejected flag, full-layout, exception-contract or return-expression sweep was repeated.

The nine prior target verdicts, cited reverse/attempt_support/3e8e23-worker-20261019.md and its raw evidence were read. The older build/big/veterancy-visible directory is absent. The read-only donor follow-up found GeneralsMD's deleteInstance uses pool lookup and pool->freeBlock; retail uses global deletion after scalar destruction with flag zero. That wrapper cannot be transplanted on the present evidence. No new supported experiment remains.

## Identity and provenance

Fresh native decoding in build/worker-3e8e23-cleanup/retail.txt confirms the next body at 0x003E8FEE, RET 16 and the condition-146 dispatcher setting ecx and pushing four Parameter pointers before calling this body. PLAYER_HAS_OBJECT_OF_VETERANCY is the established template relationship; it does not establish an original method spelling, so the address-derived member name is retained. Retail uses Object template +4, experience tracker +0x264, rank +0x24, Parameter int +8 and the six signed comparisons. Current provider resolution is recorded in metrics.json and baseline-explain.txt. Global deletion on both exits, including the null arm, is retained.

The BFME 1 game/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditionsRva00326F40.cpp donor corroborates the walk and comparisons, not BFME 2 layouts or compiler shape. BFME 2 base 2094cb79ccf260dbcbd01f6694de3a181d1d20b9; donor checkout a18d9ed50607e9175de4d6568798d7d73119de09.

## Raw outputs and checks

Every trial and log is in build/worker-3e8e23-cleanup/. Raw probe output: probes.txt, baseline-align.txt, h1-true-boundary-align.txt, h1-dtor-start-align.txt, h1-dtor-end-align.txt, baseline-explain.txt and metrics.txt. align_diff completed successfully as a diagnostic for every trial, but byte identity fails. check-csv-before.txt passed. Post-record CSV, pin and whitespace results are in check-csv-after.txt, pin-consistency-after.txt and diff-check.txt. No changed Code source exists, so find_declared_unmatched and build.sh are not applicable; no exact result is claimed. Every experiment checked build/STOP_WORKER first, and BFME_OBJSTORE was off throughout. No background task was started. All scratch artifacts and new object-cache paths are enumerated in artifacts.txt.

The record clock and measured duration are in build/worker-3e8e23-cleanup/timing.json. model=gpt-6.1-sol. All changes are uncommitted; no git write or network operation ran.
