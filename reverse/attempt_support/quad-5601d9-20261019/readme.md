# QuadDrawModule::doParticles handoff

Result: a closer, semantically complete bank for `?doParticles@QuadDrawModule@FXParticleSystem@@UAEHAAVRenderInfoClass@@PAXPAH@Z`, RVA `0x005601D9`, retail extent 2114 bytes. It is not exact and is not entered in the function ledger. Model: `gpt-6.1-sol`.

Inputs are checkout `b84952de3bdcf52147d697f19c6d7364efb147ae` and pinned BFME 1 donor `a18d9ed50607e9175de4d6568798d7d73119de09`. The original bank is available at that checkout revision and as `build/quad-5601d9-20261019/before.cpp`. All eight prior verdicts were read. Their cited `build/s7-r7` and `build/mp3/r10/wins/ms_best_0x005601d9.cpp` artifacts are absent here; the recorded existence checks are in `prior-paths.txt` in the same scratch directory.

## Measurements

| Measurement | Before | Replacement |
| --- | ---: | ---: |
| Emitted bytes | 2097 | 2112 |
| Structural regions | 10 | 5 |
| Memory differences | 76 | 63 |
| Register differences | 7 | 2 |
| Masked positional differing bytes, diagnostic only | 633 | 355 |

The selection uses the three alignment classes, all of which improve. Positional bytes are supplementary. Both alignments use the unchanged `tools/align_diff.py`, an explicit 2114-byte extent, fresh source paths and `BFME_OBJSTORE=off`. Its memory count includes unpatched absolute relocation operands; the comparison uses the same tool on both versions. Raw outputs and the full operand listings are `before-align.log`, `before-object.log`, `bank-candidate-align.log` and `bank-candidate-object.log` under `build/quad-5601d9-20261019/`. The final bank itself is checked again in `bank-align.log` and `bank-object.log` there.

## Identity and semantics

Target facts: the native body ends with `RET 12` at RVA `0x00560A18`, immediately before the next entry at `0x00560A1B`. ECX is the receiver and there are three stack arguments. WB `0x01422720` names `FXParticleSystem::QuadDrawModule::doParticles`; its particle getters, rotation-axis dispatch, texture lookup and renderer calls agree with retail. Particle axis, position and next offsets are `0x10`, `0x1C` and `0x64`; system texture and storage offsets are `0x10` and `0xA4`. The four D3DX targets were resolved through their native import thunks, not guessed from source names. Full raw evidence is `retail-audit.log` and `wb-retail.log` in the scratch directory.

Donor facts: pristine ZH `matrix4.h`, `vector4.h` and their dependencies supply vector copying, indexing, addition and matrix multiplication. The first active compiler line names the actual WWMath, WWLib and WWDebug directories. A thin 64-byte Matrix4 wrapper preserves the existing global declaration and external diagnostic-constructor shape. The bank retains address-derived helper names where target identity is unproved. `TextureAsset::Get` is independently established by WB and the existing exact row at RVA `0x00132D89`, including its static hidden-return ABI; the obsolete free helper declaration is removed.

The replacement removes all volatile reads and equal-arm expressions, retains every matrix product, and restores the four-component translation with zero W found in WB. All seven original comment lines survive verbatim and in order, including the old compiler line after the active one. No pins or shared headers changed.

## Remaining mismatch

The frame already matches `0x104`. Matrix dot products still differ in association and load/fold choices, first visible at native `+0x4C7`. The translation/view loop has three structural regions at `+0x5D6`, `+0x5E5` and `+0x600`; texture receiver preparation contributes the other two at `+0x773` and `+0x777` (`add` plus `mov` versus `lea`). The renderer callee `?rva00177F82@Rva00177860@@QAEXAAVRenderInfoClass@@@Z` remains unresolved at native call target RVA `0x00177F82`. Do not mistake the two-byte extent gap for an immediate-only repair.

H1 restored W through complete copies or scalar additions; H2 added donor copy/assignment interfaces; H3 restored overloaded indexing; H4 isolated donor method spelling and scalar-return temporaries; H5 used full pristine donor headers; H6 tried the donor operator and native matrix type; H7 isolated direct-field versus indexed translation; H8 staged the exact native product orders with scalar accumulators. H5 and H7 direct fields yielded the accepted improvement. H8 regressed to 6 structural, 67 memory and 9 register differences. All other trials and their raw results remain in the scratch directory; `hypotheses.md` records each hypothesis, evidence and refutation before its experiment. No arbitrary permutation sweep was run.

## Verification

The exact comparison remains a mismatch; `bank-explain.log` records the actual remaining unresolved name and extent. `check-csv-after.log` and `pin-consistency-after.log` record the final integrity checks. No nonmatching source was put in Code, and no function row was added, so there is no source-row build or declaration gate to pass yet. The eventual home reported by `repair_queue.py dest` is `Code/GameEngine/Source/GameClient/FXParticleSystem.cpp` (a neighbour heuristic, not an established translation unit). No git write commands or background tasks were started.

The initial `git diff --check` reported CRLF characters in the replacement source as trailing whitespace. Only that bank was normalized to LF, and the full bank measurement and integrity checks were repeated. The initial raw results retain the `-before-lf.log` suffix; `diff-check.log` is the final check. `receipt.json` records the clock-measured duration and result codes; `manifest.json` lists retained scratch artifacts and generated objects.
