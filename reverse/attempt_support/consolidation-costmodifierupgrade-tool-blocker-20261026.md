# CostModifierUpgrade dry-run tool blocker (2026-10-26)

Shard 0/5 `--check-tu` passed for
`Code/GameEngine/Source/GameLogic/Object/Upgrade/CostModifierUpgrade.cpp`, and
the scoped planner snapshot/currency check passed. The plan had 12 approved
rows, four candidate donor files, five mixed files, and one protected donor.
The `tu_skeleton.py --merge ... --dry-run` process never returned an accepted
or rejected list. After 4m43s, PID 5184 was blocked in `subprocess.communicate()`
reading the compiler pipe (`anon_pipe_read`) and its child `cl.exe` PID 6338
was defunct. The process was interrupted; no claims were acquired and no source
or ledger files were applied. This is a tool-run failure, not evidence about
donor compatibility. Do not repeat the unchanged trial until the pipe/child
failure is understood.
