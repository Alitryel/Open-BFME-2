# CommandSetUpgrade prerequisite survey, 2026-10-26

Allocated codex family A shard 0/2 destination:
Code/GameEngine/Source/GameLogic/Object/Upgrade/CommandSetUpgrade.cpp.
Fresh `tu_skeleton.py --plan` approves seven rows, four donors and two mixed
files. Scoped Upgrade planner packets (build/consolidation) preserve the
same-name donor and original-path hints; their stale-map warning does not
approve a move. The upstream plan rebuilds routing in memory. No merge applied.

The constructor/removal source emits primary and UpgradeMux vtables from its
partial BehaviorModule/UpgradeMux hierarchy. The pool-key file instead has a
separate one-method class. Unlike declaration-only consumers, adding that
virtual method to the constructor's class can change emitted vtable data.
The 0x004B3AFF body and the 0x004B3B42 body remain neutral, adjusted-interface
receivers; the former accesses the owner at this-8 and module data at this-0xC
and calls the whole-module hook at this-0x10. A coherent target interface and
provider reconciliation is required before sharing those declarations.
No target vtable ordering or donor layout is inferred from the common TU name.
This is a structural survey, not a reproduced byte failure or a new gate reject.

Read current constructor/removal and interface sources, prior attempt entries,
the fresh plan and scoped planner packet. Did not change source, compiler flags,
ledgers, hatches or registers, and did not run a speculative merge. Recorded
blocked survey for ctor 0x004B3AB2/49 through re_log.py; released all four file
claims. Receipts: build/codex-commandset-plan-20261026.txt and
build/codex-upgrade-planner-20261026.txt.

Other allocated queue triage: MaxHealthUpgrade's current plan has seven rows,
four donors and two mixed files; its module-data constructor has target fields
at +0x118/+0x11C while the legacy module declaration describes +0x70/+0x74.
The planner also reports compiler settings and duplicate receiver types.
No repair was attempted or claim acquired there. HeightDieUpdate has seven
approved rows/five donors/two mixed files, but the actual source/destination
claims belong to yasinschroeder-codexb2. No source was changed; released the
sole unused new-header claim. Fresh scoped Update planner completed with no
missing inputs; did not run another worker's trial. Reports:
build/codex-{maxhealth,heightdie}-plan-20261026.txt and
build/codex-heightdie-planner-20261026.txt.

No source paths move in this survey or the pending declaration prerequisites;
their combined consumer audit remains applicable. No recovered bytes, file
reduction, debt retirement or newly compatible TU is claimed by this survey.
