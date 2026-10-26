# UpdateModule current-verifier follow-up, 2026-10-26

Seat codex family A shard 0/2; fresh allocation check authorizes this destination.
Read the earlier consolidation-updatemodule-20261026.md handoff. No source edit
is needed: ordinary current `tu_skeleton.py --merge
Code/GameEngine/Source/GameLogic/Object/Update/UpdateModule.cpp --dry-run`
accepts seed and UpdateModuleXfer.cpp, two existing rows / 116 bytes. The old
Snapshot include-order failure does not reproduce after the separately verified
per-candidate diagnostic cache fix fc3e3896ff. This establishes current acceptance,
not a claim that every past Snapshot failure had that cause.

Scoped name_lane planner/check and current --plan pass. Planner reports same-name
Zero Hour/stale-map hints with no alternative destination; these are not target
ABI proof. The merge uses current routing rebuilt in memory. No map is committed.

Acceptance: ./build.sh both sources passes 2/2; find_declared_unmatched reports
all bodies matched; link_check --prepare-current accepts both strict receipts.
allowed_symbols --source both: two owner references, zero wrong bindings.
The accepted scratch object build/tu_skeleton/164596ee34ee9f60.obj preserves the
union's three external code definitions, aliases, COMDAT policies, unresolved
references, and all data facts (no external data definitions). No changed provider
or consumer binding exists. Proof uses upstream COFF/data readers; no hand compile.
Receipts: build/codex-updatemodule-{before-build,before-trial,prepare,allowed}.txt,
*-composition-proof.json and planner build/consolidation/codex-updatemodule.

No merge is applied; leave the compatible donor to Luna. Its two existing alias
hatches must travel through the merge tool. Mixed UpdateModuleSetWakeFrame.cpp
still has the earlier split hatch-growth blocker; no unchanged split is retried.
No source paths/debt keys move, no files removed, no recovered bytes or census gain.
Unchanged source/unused-header claims were released; only this handoff claim
awaits publication. This is a verified current dry-run result, not a Luna landing.
