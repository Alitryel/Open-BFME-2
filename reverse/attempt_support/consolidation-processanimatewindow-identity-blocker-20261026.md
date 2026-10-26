# ProcessAnimateWindow mechanical merge blocker (2026-10-26)

Allocated TU: `Code/GameEngine/Source/GameClient/GUI/ProcessAnimateWindow.cpp`
(`shard 0/5`). The scoped consolidation planner and its currency check passed.
The current dry run accepted the seed plus
`ProcessAnimateWindowDestructors.cpp` (12-row composed trial) and rejected
`SlideLeftUpdate.cpp` and `SlideTopUpdate.cpp` with the existing duplicate
`ICoord2D` and missing `finished` member errors. Five other sources remain
refused because they are keyed in a protected path register.

The apply tool staged the accepted merge and repointed three matched rows
(`0x005C4FEF`, `0x005C5990`, `0x005C6317`) to the TU. Fresh `./build.sh
Code/GameEngine/Source/GameClient/GUI/ProcessAnimateWindow.cpp` passed 12/12
matched rows; `find_declared_unmatched.py` passed. Staged identity verification
reported one new shadow finding: `definition: duplicate | ??0ProcessAnimateWindowSpiral@@QAE@XZ`.
Because the changed composition's selected COMDAT/provider was not verified,
the merge trial was restored and its TU, donor, and moved-row claims released.

Other scoped evidence before restoring the trial: `data_check.py --converged`
reported 10 addresses and zero second names; `allowed_symbols.py --source`
reported seven references (five owner, one EH, one alias) and zero wrong
bindings; `link_check.py --staged --new-variants --staged-peers --shadow`
exited 0 (`Compile: 0 of 1 TU(s)`, one current cached object). The path audit
found no active tooling, hook, workflow, include, or build input referring to
the absorbed donor; its remaining mentions were the TU's row comments, ledger
provenance, and historical census/map evidence. No debt register or TU map
regeneration was performed.

Sol follow-up: resolve or prove the duplicate spiral-constructor definition
and selected COMDAT before retrying this composition. Other rejected donor
declaration issues remain unchanged and should not be retried without their
prerequisites.
