# Particle update accumulator controls

Result: blocked. Keep `reverse/attempts/0x001fab59.cpp` unchanged. Symbol `?update@Rva001FAB59@@QAE_NH@Z`, retail RVA `0x001FAB59`, extent 1704 bytes. Input revision `c95aea81d9db3c7524cd76c55dc2ad35d77c23f0`. No production source, pins, ledger rows, baselines or compiler profiles changed. The destination tool identifies `Code/GameEngine/Source/GameClient/System/FXParticleSystem/CPUParticleUpdate.cpp` by neighbour heuristic, not independent source-file evidence (`build/particle-update-w8/destination.log`). The older bank comment names another intended home; no landing was attempted.

## Measurements

| Candidate | Emitted bytes | Positional differing bytes | Structural regions | Memory | Register |
|---|---:|---:|---:|---:|---:|
| baseline | 1709 | 1207 | 5 | 11 | 5 |
| h1 | 1704 | 436 | 5 | 26 | 9 |
| h1z | 1713 | 1177 | 8 | 19 | 7 |
| h2 | 1708 | 1158 | 6 | 19 | 8 |
| h2a | 1708 | 1158 | 6 | 19 | 8 |
| h2b | 1704 | 436 | 5 | 26 | 9 |
| h3 | 1709 | 1216 | 6 | 24 | 7 |

Measurements come from `tools/align_diff.py` and `tools/explain_mismatch.py` with the same symbol, RVA, size and `CL=/I.` for every source. The include environment supplies the root include directory required by the prior verdict. All original bank comments are retained in the trial sources. Raw alignment reports are `build/particle-update-w8/<candidate>-align.log`; full side-by-side disassemblies are `<candidate>-explain.log`; exact measured bytes and metadata are `<candidate>.bin` and `<candidate>.json`. Positional differing bytes compare the relocation-filled first 1704 bytes and do not establish closeness after a length change. The alignment tool additionally reports ten absolute-memory relocation comparisons in every memory count; these are common noise, not defects. Relocation and branch categories are excluded from the ranking. No trial improves the required alignment classes. The existing bank remains authoritative.

## Hypotheses and controls

The hypotheses, supporting evidence and refutation criteria were written before each experiment in `build/particle-update-w8/hypotheses.md`. Separate scalar product assignments test the documented assignment-destination rule; a Z-only control isolates the first-evaluated product. Sequential accumulation tests retail's observed Z+Y+X graph. The two-factor controls isolate product assignment order from the sum graph. A final result-local control keeps products in the same statements as accumulation, as described by the matching guide. Every changed source is under `build/particle-update-w8/`; `make_trials.py` reproduces all six. The experiment runner checks `build/STOP_WORKER` before each compile.

Separate products can recover the desired MOVAPS/MULSS orientation locally and the retail length, but increase other operand and scheduling differences. Reversing product assignment order is inert in both sum-graph controls: H1/H2b and H2/H2a emit identical full bodies. Z-only and product-in-accumulation controls are worse. These results rule out the tested scalar-accumulator family. They do not prove that all clean C++ representations are exhausted. No further independent evidence-backed experiment was identified in this pass.

The original mismatch remains at row-zero Z in all four columns and column-W row-one X: retail copies the cached column scalar with MOVAPS then folds the matrix element into MULSS; the bank loads the matrix element with MOVSS then uses register MULSS. This costs five emitted bytes. A third-column load schedule also differs. Baseline alignment separates these into five structural regions and the reported operand classes.

## Identity and ABI evidence

`reverse/ghidra_functions.csv` identifies start `0x1FAB59` and size 1704, followed immediately by `0x1FB201`. Direct retail disassembly in `build/particle-update-w8/retail.log` and bytes in `boundary.log` establish the prologue, ECX receiver, one stack argument and final RET 4 at VA `0x005FB1FE`. The attachment, profiling, transform, emission and tail call relationships correspond to the bank's Zero Hour ParticleSystem::update guide; this is structural evidence, not proof of the original BFME 2 class spelling. Keep the address-derived receiver name.

Direct calls resolve to the existing Drawable transform and bone-position owners, string predicate, transform setter, GameLogic object lookup, Object shroud query, Thing drawable getter, ParticleSystem destroy/emission owners, module update and final predicate. Native call-site stack arguments, ECX setup, indirect GameClient slots +0x40/+0x7C, member accesses and Object transform +8 agree with the bank declarations. Every compiled candidate has zero unresolved calls. Canonical Coord3D and GameLogic headers are already included. No donor code was newly imported. All seven target verdicts found in the log were read, along with the bank and the related `reverse/attempt_support/crack-e-finish.md` disposition. The visibility verdict's cited `build/big/particle-update-visible` is absent in this checkout; no claim of reviewing those unavailable raw trials is made.

## Verification and retention

Each baseline/trial explain and alignment command exited zero as a diagnostic invocation, but every body fails byte equality. No add_match call or production build was appropriate. `build/particle-update-w8/checks.json` records validator exit codes and raw log paths. `integrity.log` records the unchanged bank hash and byte comparisons. Trial sources, binaries and raw outputs are retained as requested; `manifest.txt` lists task artifacts. No background process was started. Elapsed at verdict recording: 5.80 minutes from the tool clock at 2026-10-19 02:17:59 UTC. model=gpt-6.1-sol.
