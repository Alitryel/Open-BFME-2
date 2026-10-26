# AnimatedParticleSysBoneClientUpdate prerequisite, 2026-10-26

Seat codex, allocated family A shard 0/2. Destination:
`Code/GameEngine/Source/GameClient/Drawable/Update/AnimatedParticleSysBoneClientUpdate.cpp`.
The allocated queue and fresh upstream `--plan` place four retail rows across
three donors, including the mixed `ConstIntGetters4.cpp`. The scoped planner
under GameClient/Drawable/Update supplies a same-spelling Zero Hour definition
and WorldBuilder file pairing for clientUpdate, both hints rather than target
layout or merge proof. Its seed packet is complete and has no static blocker;
the other donors lie outside that planner prefix. Current routing, rebuilt in
memory by tu_skeleton, independently approves the attempted composition.

Shared the receiver declaration between clientUpdate and the pool-key consumer.
The existing matched clientUpdate establishes drawable +8 and life +0xC; the
new header preserves those accesses and declares both existing methods. Neither
consumer emits a vtable. This partial interface does not claim retail slot
ordering or reconcile the opaque constructor. No body, compiler setting,
canonical class contract, pin, ledger owner or protected register was changed.

Before/after ordinary merge trials:

- Before: no two-source composition; pool-key donor fails C2039 because the seed
  lacks getModuleNameKey. Constructor donor separately fails C2511.
- After: seed and pool-key source accepted, three matched rows including the
  pool-key EH handler, 135 bytes. Constructor remains C2511; the mixed constant
  getter stays behind. The proposed merge carries one data-check key and two
  data-ledger rows; these were not deleted or retired here.

Verification:

```
./build.sh Code/GameEngine/Source/GameClient/Drawable/Update/AnimatedParticleSysBoneClientUpdate.cpp Code/GameEngine/Source/GameLogic/Object/Update/AnimatedParticleSysBoneClientUpdatePoolKey.cpp
python3 tools/find_declared_unmatched.py Code/GameEngine/Source/GameClient/Drawable/Update/AnimatedParticleSysBoneClientUpdate.cpp Code/GameEngine/Source/GameLogic/Object/Update/AnimatedParticleSysBoneClientUpdatePoolKey.cpp
python3 tools/tu_skeleton.py --merge Code/GameEngine/Source/GameClient/Drawable/Update/AnimatedParticleSysBoneClientUpdate.cpp --dry-run
python3 tools/link_check.py Code/GameEngine/Source/GameClient/Drawable/Update/AnimatedParticleSysBoneClientUpdate.cpp Code/GameEngine/Source/GameLogic/Object/Update/AnimatedParticleSysBoneClientUpdatePoolKey.cpp
```

Byte checks pass 3/3; frozen-file checks pass both consumers. Compared saved
verified baseline objects with the rebuilt objects through upstream Obj,
_object_defs, _comdat_selections, alternate_names, allowed_symbols.scan and
data_check.object_facts. Both external code definitions, all ten non-debug
sections including relocation targets and COMDAT policies, external data,
undefined symbols, aliases, five reference-identity tuples and data-reference
facts are identical. No provider/consumer binding changed. Link preview reports
two LINKS and 135 -> 135 predicted linked bytes; this is not a census result.

Local receipts: build/codex-particlebone-{plan,before,after,link}-20261026.txt,
build/codex-particlebone-object-proof.json, -reference-delta.json and
-data-delta.json; planner build/consolidation/codex-particlebone. One initial
planner run collided with a dry-run temporary source; the fresh planner was
rerun after that trial completed and succeeded with no missing inputs.

Compatibility audit: this prerequisite and the earlier RadarUpdate repair
move or delete no source path. The new header has exactly these two consumers;
active tools/hooks/workflows/build inputs and registries have no old path to
repoint. Original EA/donor evidence is preserved. No source-file reduction,
identity debt retirement or recovered C++ bytes is claimed. The compatible
merge is left for Luna; no downstream landing is confirmed by this receipt.
