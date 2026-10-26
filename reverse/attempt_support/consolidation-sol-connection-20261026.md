# Connection prerequisite boundary, 2026-10-26, codexb

Family B shard 0/2 runner queue authorizes Connection.cpp. The scoped
GameNetwork planner, its currency check and current in-memory --plan were
reviewed. The current plan has 11 ordinary approved rows, eight clean source
files, one mixed source and no refused files; protected-register transfer
support has superseded the previous handoff's five path-key refusals.
Connection is not a registered canonical class; class_views lists 22 views.

Before any edit, find_declared_unmatched passes for the seed, Init and doSend.
Fresh ./build.sh on all eight clean sources verifies 19/19 ledger rows,
three compiler literals and four named imports. The ordinary
`python3 tools/tu_skeleton.py --merge Code/GameEngine/Source/GameNetwork/Connection.cpp --dry-run`
now stops before declaration composition:
`the TU file loses 2 row(s) under the carried flag override`.
ConnectionRva0058BD4F.cpp carries `-O2 -arch:SSE`; the verifier correctly refuses
to lose the seed's region-default matches. Receipt:
build/sol-connection-before-trial-20261026.txt; standalone build receipt:
build/sol-connection-before-build-20261026.txt.

A declaration-only repair cannot demonstrate the proposed unblock until this
compiler-profile prerequisite is solved. Do not weaken the override guard,
remove the registered override without its owning tool's evidence, or equate
standalone matches with a successful composed binding proof. The planner also
retains Init's UnicodeString member versus the seed's trivial block, differing
Connection/NetCommand* views, doSend's GameLogic canonical-header prerequisite,
and the mixed clearCommandsExceptFrom residual boundary from the prior handoff.
No source, row, register, flag or ownership change was attempted. No merge,
file reduction, debt retirement or recovered byte gain. Blocked verdict recorded
at 0x0058BD4F; all eight source claims released. Continue with another allocated
prerequisite rather than rebuilding this unchanged boundary.
