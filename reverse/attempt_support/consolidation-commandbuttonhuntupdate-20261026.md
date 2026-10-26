# CommandButtonHuntUpdate TU consolidation (2026-10-26)

Shard 0/5 allocation and `--check-tu` passed for
`Code/GameEngine/Source/GameLogic/Object/Update/CommandButtonHuntUpdate.cpp`.
The scoped planner snapshot and `--check` passed. The plan had nine approved
rows; three sources were protected, and one common getter source was mixed.
The dry run accepted only `CommandButtonHuntUpdateScanClosestTarget.cpp` and
rejected the destructor donor (C2600: destructor not declared in the view) and
Xfer donor (C2061: `Snapshot` declaration missing). The accepted source was
merged unchanged; no mixed or refused source was touched.

The merge moved the scan method and its EH/funclet rows (seven matched rows)
into the approved TU. Fresh `./build.sh` passed 7/7 rows, including verification
of all five funclet pins after compiler-label renumbering;
`find_declared_unmatched.py` passed. Staged checks: ownership shadow clean;
code identity 7 rows, zero new findings; converged data 10 addresses, zero
second names; `allowed_symbols.py` 27 references (21 owner, 3 fold, 2 alias,
1 EH), zero wrong bindings; EH exact 1/1; `link_check.py --staged
--new-variants --staged-peers --shadow` exited 0 with one current object and
no new COMDAT variant. The scoped Microsoft-header scan found no local
definitions. `tu_skeleton.py` refreshed report consumers while applying; no
header queue rows changed.

Path audit covered the complete pending change (`origin/master..HEAD` plus the
staged rename). No active tool, hook, workflow, include, or build input uses the
absorbed path. Remaining mentions are source comments and reverse evidence.
Code/data identity findings and bindings remain unchanged; no protected
register or TU map was edited by hand. Since the approved TU did not previously
exist, this replaces one donor path with one TU path: net source-file reduction
is zero, with seven matched rows preserved.

Sol prerequisites: the destructor donor needs its declaration/view repaired;
the Xfer donor needs `Snapshot` declarations; protected source keys still
require their owning repair lane.
