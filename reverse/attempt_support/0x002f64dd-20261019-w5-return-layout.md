# Return-layout follow-up for FindCollisionFreeQuickPath

Blocked. Preserve `reverse/attempts/0x002f64dd.cpp` byte for byte, including every contributor comment. Neither experiment improves it, and no further evidence-backed experiment is justified by the current inputs. No reconstruction was placed in `Code/`; no row or pin was added.

Symbol: `?FindCollisionFreeQuickPath@Pathfinder@@UAEPAVPath@@PAVObject@@PBUCoord3D@@PAVPathNode@@@Z`. Retail RVA `0x002F64DD`, extent 1286 bytes. Owner: `Code/GameEngine/Source/GameLogic/Pathfinder/pathfinder.cpp`. Base revision: `5c620a3c8ae8511f146ea9c53bdb88d89ae24c34`. Existing bank and owner input hashes are recorded in `build/quickpath-resume-20261019-w5/inputs.json`. Compiler: default MSVC 13.10.3077, owner `/O1 /arch:SSE /G7 /EHsc`, complete owner definitions with the bank's virtual-slot and padding patch in an isolated copy. Model: `gpt-6.1-sol`.

All five prior verdicts and their cited bank and support evidence were read before the first experiment. The preceding handoff is `reverse/attempt_support/0x002f64dd-20261019-w5.md`. New hypotheses and refuting observations were written before their experiments in `build/quickpath-resume-20261019-w5/hypotheses.md`; every experiment checked `build/STOP_WORKER` first.

| Candidate | Emitted bytes | Structural regions | Memory differences | Register differences | Positional masked differing bytes |
|---|---:|---:|---:|---:|---:|
| Existing bank reproduced in current owner | 1298 | 3 | 7 | 0 | 843 |
| H22: scan selects an index, success follows scan | 1303 | 4 | 27 | 0 | 863 |
| H23: scan jumps directly to success outside both loops | 1298 | 3 | 7 | 0 | 843 |

The seven baseline memory differences are DIR32 relocation operands. H22 adds a comparison and changes stack-slot reuse; it leaves the epilogue late and is worse. H23 removes that added decision, but reproduces the baseline's complete emitted symbol bytes exactly. Its external success label and allocation scope therefore do not control the remaining layout. Its matching hash is recorded in the raw metric files. Neither trial qualifies for a replacement bank, regardless of byte-sequence score. Diagnostic source patches are `build/quickpath-resume-20261019-w5/h22.patch` and `build/quickpath-resume-20261019-w5/h23.patch`; complete trial sources and raw output remain in that folder.

The exact remaining mismatch is unchanged: retail joins goal-null, goal-rejected and parent-null at +0x11A and places the shared epilogue at +0x214; the candidate uses +0x4FF and +0x501. Cleanup needs an extra branch and early branches widen, giving 1298 bytes against retail's 1286. The 1286-byte boundary abuts the next prologue and must not be enlarged. Frame 0xB0 and all aligned non-relocation register and memory operands still agree.

Identity evidence remains independent of the byte metric: the WB record at VA 0xD624A0 names this function and the Pathfinder source path; the native vtable at VA 0xC053F8 slot 10 contains VA 0x006F64DD. A fresh raw probe verifies all 45 aligned direct callees and the slot against current ledger/pin candidates (`build/quickpath-resume-20261019-w5/identity.log`). Retail uses ECX and three stack arguments, returning with RET 12. Object position +0x38 and AI +0x258, PathNode next +0, position +0xC and layer +0x18, cell info +0 and packed word +0xC agree with current declarations. These are target observations; no donor implementation or new identity inference was imported.

Raw diagnostics: `baseline-align.log`, `h22-align.log`, `h23-align.log` and each corresponding `*-explain.log` under `build/quickpath-resume-20261019-w5/`. Each explain and align process exited 0; explain reports an expected target byte mismatch, not gate success. The untouched owner's `build.sh` passes 87 function rows and one data row (`owner-build.log`). `find_declared_unmatched.py` passes (`owner-declared.log`); `pin_consistency.py --check` passes (`pin-consistency.log`). Final CSV and integrity receipts are in the same folder. `BFME_OBJSTORE=off` was set for every build and measurement. No background task was started.

Clock: start 2026-10-19T03:03:03+00:00; verdict clock 2026-10-19T03:07:44.702261+00:00; elapsed 4.695 minutes. No commits or network operations were performed.

Final integrity checks: `check_csv.py` passes (`check-csv.log`). The first optional git integrity probes failed because Git refused `NUL` as an exclude file in the submodule; raw failures remain in `diff-check.log` and `status-final.log`. Plain read-only retries pass (`diff-check-plain.log` and `status-final-plain.log`). The status output lists only the attempt-log addition and this new handoff. The original bank and owner hashes remain unchanged (`final-receipt.json`).
