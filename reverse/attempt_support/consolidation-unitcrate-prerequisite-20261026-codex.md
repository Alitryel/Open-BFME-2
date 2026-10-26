# UnitCrateCollide prerequisite, 2026-10-26

Seat codex, allocated family A shard 0/2. Destination:
`Code/GameEngine/Source/GameLogic/Object/Collide/CrateCollide/UnitCrateCollide.cpp`.
The allocated queue and fresh upstream plan approve six rows across three
donors and two mixed files. The scoped planner under Collide/CrateCollide
finds same-spelling Zero Hour source definitions and original-path evidence;
these are placement hints, not target layout or merge approval. Its packets
also retain the execute EH row's unresolved placement and existing data debt.
The merge tool rebuilds current routing in memory and handles emitted EH rows.

Shared the existing execute receiver declaration with the pool-key consumer.
The execute body accesses ModuleData at +4; this offset and the existing
CrateCollide declarations are unchanged. Neither consumer emits a vtable.
The new header declares both already matched methods without claiming the
complete virtual interface. No body, compiler setting, pin, canonical class
contract, ledger owner or protected register changed.

The ordinary baseline merge trial accepts only the pool-key donor (two rows).
Execute fails C2039 because that seed lacks executeCrateBehavior. The opaque
constructor independently fails C2511. It writes explicit primary and secondary
pointer members; reconciling that representation is a separate prerequisite.
The mixed ConstIntGetters4.cpp and Rva004BC4FCDerived.cpp remain untouched.

After the repair, the ordinary dry-run accepts pool-key and execute together:
two sources, four matched rows including both EH handlers, 462 retail bytes.
The constructor remains C2511. The proposed merge carries one data-check key
and two data-ledger rows; this repair neither transfers nor retires them.
The compatible composition is left for Luna.

Verification commands:

```
./build.sh Code/GameEngine/Source/GameLogic/Object/Collide/CrateCollide/UnitCrateCollideExecute.cpp Code/GameEngine/Source/GameLogic/Object/Collide/UnitCrateCollidePoolKey.cpp
python3 tools/find_declared_unmatched.py Code/GameEngine/Source/GameLogic/Object/Collide/CrateCollide/UnitCrateCollideExecute.cpp Code/GameEngine/Source/GameLogic/Object/Collide/UnitCrateCollidePoolKey.cpp
python3 tools/tu_skeleton.py --merge Code/GameEngine/Source/GameLogic/Object/Collide/CrateCollide/UnitCrateCollide.cpp --dry-run
python3 tools/link_check.py Code/GameEngine/Source/GameLogic/Object/Collide/CrateCollide/UnitCrateCollideExecute.cpp Code/GameEngine/Source/GameLogic/Object/Collide/UnitCrateCollidePoolKey.cpp
```

Byte checks pass 4/4 and both frozen-file checks pass. Saved verified baseline
objects were compared with rebuilt objects using upstream Obj, _object_defs,
_comdat_selections, alternate_names, allowed_symbols.scan and
data_check.object_facts. All five external code definitions and 19 non-debug
sections, including contents, flags, relocation targets and COMDAT policies,
are identical. External data, undefined symbols, aliases, all 17 reference
identity tuples and data-reference/definition facts are unchanged. No existing
provider/consumer binding changed.

The link preview reports two LINKS, 459 -> 459 predicted linked bytes. That
tool's linked-byte accounting differs from row extents; it is diagnostic, not
a new census measurement or an increase in authored or linked coverage.

Local receipts: build/codex-unitcrate-{plan,before,after,link}-20261026.txt,
build/codex-unitcrate-object-proof.json, -reference-delta.json, -data-delta.json
and planner build/consolidation/codex-unitcrate (fresh after the edit, no missing
inputs). No source-file reduction, identity debt retirement or recovered C++
bytes is claimed. A later actual merge still needs its own composition audit;
this receipt proves the prerequisite and existing consumer bindings.

Combined compatibility audit: base
6f56e094b78d58d834629a0cbaeeea3c71d659d2 through 83507aa666 plus this repair.
The three receiver prerequisites move or delete no source path. The seven
expected source includes are the only consumers of the three new headers.
Active tools, hooks, workflows, build inputs and registries have no old path to
repoint; original EA evidence remains intact. Code/data identity registers,
header queues, hatch baseline, TU map and function/data ownership ledgers are
unchanged by the complete local batch. Incoming upstream merges seen by a
raw origin/master..HEAD diff are excluded using the actual local merge base;
the publisher rebases before pushing. No downstream Luna landing is claimed.
