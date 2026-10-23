# AIRingHeroTactic::update inline extraction

Result: blocked. Symbol `?update@AIRingHeroTactic@@UAEXXZ`, RVA `0x005ACBFF`, extent 229 bytes. Existing bank `reverse/attempts/0x005acbff.cpp` remains unchanged (SHA-256 `66963ad7a0be5e82d1bb4affe97aa4db46c0d6c772bc1c3080a3947d4170cda3`). No reconstruction was written to Code, no pins were added, and no function row was changed.

Input revision: `fb5b8848171738ca8cdd8e92e959c6824291efed`. The eleven prior verdicts, their bank, and both files in `reverse/attempt_support/ring-hero-update-context-20261019/` were read before compilation. No donor source was used. Trial flags were `/MD /GX /DNDEBUG /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE`; an unchanged copy with the bank's `/Os` flags and the bank itself were also measured.

## Hypothesis and refutation

The hypothesis, evidence and refuting observation were written before compilation in `build/ring-hero-inline-20261019/hypothesis.md`. Whole-operation inline extraction could have retained a different optimizer lifetime shape across the running guard and shared return. Four natural extractions were tested: the entire update body, the running body after the guard, the escort search, and the follow-escort branch. All emitted exactly the same raw body and relocations as the bank. The body SHA-256 is `73c6286193e4deba708b13528d85506e7bd5a596e808aa84ccab89488a35b383`. This refutes those extraction forms; no further source experiment is justified by this result.

The bank and all four trials have 229 bytes, 75 instructions and zero unresolved calls. Both before and after, the standard relocation pass reports 13 differing positional bytes. This count includes shifted global-operand artefacts and is not the acceptance metric. `align_diff.py` reports four structural regions, three memory differences and three register differences in every case. All three memory lines are DIR32 global operands, not layout defects. Relocation and branch lines were ignored when assessing improvement. No trial is closer, so the 0.985 bank was preserved.

Retail saves EDI at `0x005ACC08` before the running branch and EBX at `0x005ACC15` after it, then restores EBX before EDI. The candidate saves both after the branch and restores them in the opposite order. Retail places `mov ecx,esi` between the two `end(false,false)` argument pushes; the candidate places it after both. These remain the exact compiler-shape blockers.

## Identity and boundaries

`build/ring-hero-inline-20261019/native-and-prior.log` contains the raw retail body, all six direct callee bodies, vtable words and relevant ledger evidence. The preceding run body tail-jumps at `0x005ACBFA`, update starts at `0x005ACBFF`, returns at `0x005ACCE3`, and the next destructor begins at `0x005ACCE4`. Vtable RVA `0x008723E8` slot 7 points to VA `0x009ACBFF`. The named constructor string and existing WorldBuilder-backed tactic siblings support the class and update slot. Retail receives this in ECX and uses the established stack argument widths; direct calls agree with the bank's declarations. The command at `0x0026C347` retains its address-derived name.

The established class home is `Code/GameEngine/Source/Common/Rva005AC7E1Tactic.cpp`. The current `repair_queue.py dest` result is a neighbouring AIFarmKillSquad file, explicitly marked a heuristic with no TU map. It does not override the class evidence and is preserved in `build/ring-hero-inline-20261019/destination.log`.

## Raw evidence and checks

All trials, scripts, raw bytes, metrics and unmodified tool outputs are in `build/ring-hero-inline-20261019/`. Each `*.explain.log` records the known byte-match failure (the diagnostic exits 0), and each `*.align.log` records a successful alignment diagnostic. The original bank's final diagnostics are `0x005acbff.explain.log` and `0x005acbff.align.log`. The initial direct bank alignment failed while touching the shared object store outside the writable root (`bank-original.align.log`); the retry with supported `BFME_OBJSTORE=off` passed. This environment setting changes caching only.

`find_declared_unmatched.py` passed for the untouched class home (`home-declared.log`). `check_csv.py` passed (`check-csv.log`), and `pin_consistency.py --check` passed (`pin-consistency.log`). No exact candidate exists, so add_match and build.sh were not run. Every experiment checked `build/STOP_WORKER` first; it was absent. No background process was started and no git write operation was run.

Measured interval: `2026-10-19T02:02:27+00:00` through `2026-10-19T02:08:15.601711+00:00`, 5.81 minutes. model=gpt-6.1-sol.
