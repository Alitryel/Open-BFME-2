# Sol prerequisite batch handoff, 2026-10-26, codex

Dedicated family A repair seat, shard 0/2. Inherited edits were preserved,
rebased and verified before new work. This batch applies no merges or splits.

| Destination | Verified prerequisite | Ordinary dry-run after repair | Authored commit |
| --- | --- | --- | --- |
| RadarUpdate | Shared receiver for seed, pool-key and Xfer; inherited repair recovered this session | Three sources, five rows, 312 retail bytes | 59c08a189b |
| AnimatedParticleSysBoneClientUpdate | Shared clientUpdate and pool-key receiver | Two sources, three rows, 135 retail bytes | 8b28b80b65 |
| UnitCrateCollide | Shared execute and pool-key receiver | Two sources, four rows, 462 retail bytes | 7823ccb24b |

The two new prerequisite repairs accept seven existing rows / 597 retail bytes;
the inherited Radar recovery is separate. Combined acceptance is twelve rows /
909 retail bytes. These are demonstrated compatible compositions for Luna,
not confirmed downstream landings, newly recovered code or a link census gain.
Each target still has an incompatible opaque constructor. Mixed helper files
stay behind. Each individual prerequisite handoff records the exact build,
frozen-file, ordinary dry-run, object identity and link-preview commands.

All seven edited C++ consumers retain their existing matched bytes. Scoped
header gates passed 32 rows for Radar, 30 for the particle receiver and 31 for
UnitCrate. UnitCrate's two EH graphs are EXACT. Saved verified baseline objects
and rebuilt objects keep their external code/data definitions, non-debug
sections, relocations, COMDAT policies, undefined symbols and aliases; reference
identity and data facts are unchanged. There are no changed provider/consumer
bindings. Shadow pool-key data-name findings remain; no register entry was
silently removed. Converged-data enforcement passes. No maintainer link cycle,
smoke, nightly or ownership recorder was run.

Other investigated or skipped prerequisites:

- SpawnPointProductionExitUpdate: inherited survey recovered in 64e2dea613;
  target receiver/interface offsets differ from the legacy class and its seed
  also has the allocator<char> C2950 include failure. No source edit.
- CommandSetUpgrade: structural survey and blocked evidence in 83507aa666;
  constructor/removal emit primary and UpgradeMux vtables while interface rows
  use adjusted this pointers. Extending the bare pool declaration alone would
  not reconcile these provider facts. Its four scope claims were released.
- MaxHealthUpgrade: legacy ModuleData offsets +0x70/+0x74 conflict with the
  target +0x118/+0x11C, alongside flag/type prerequisites. No speculative edit.
- HeightDieUpdate: source and destination were held by yasinschroeder-codexb2
  when investigated. The unused header claim was released; no source edit.
- Fresh allocated-queue reassessment after the final repair: Squad and Dynamic
  Shroud already have the previous compact/transfer prerequisites. Their real
  STL and update-interface blockers remain. QueueProductionExit still combines
  legacy and canonical Coord3D/Xfer/BitFlags declarations; prior GameLogic
  adoption is retained. These unchanged blockers were not rebuilt.
- Newly listed FireWeaponWhenDamagedBehavior has constructor-emitted vtables
  and different update/dtor declarations; its unrelated Xfer source explicitly
  describes another retail cluster. No declaration-only fix was attempted.
  StatusBitsUpgrade's existing handoff records a constructor byte mismatch;
  RankInfo's string/vector lifetime declarations differ between constructor
  and destructor providers. These require dedicated structural work. GameMemory
  was not selected. No claim was taken for these read-only reviews.

Combined compatibility audit covers the complete local range
6f56e094b78d58d834629a0cbaeeea3c71d659d2..7823ccb24b plus this receipt.
No source path is moved, renamed or deleted. The three new headers have seven
expected direct C++ consumers, confirmed together across Code, tools, hooks and
workflows. Active build inputs and registries need no path repoint; original
EA evidence is preserved. Function/data ownership, code/data debt, header queues,
hatches and TU-map registers are unchanged. Upstream changes visible in a raw
origin/master..HEAD comparison were distinguished from this local range using
the common ancestor. No source-file reduction, debt retirement or recovered
C++ bytes is claimed; three scoped headers were added.

Required final measurement: `python3 tools/progress.py origin/master` passes.
BYTE-MATCHED is 7,978,500 bytes / 100.00%; LINKING is 7,267,914 / 96.74%;
LINKED is 7,518,133 / 97.51%, all delta zero. The latter two remain the
2026-10-25 21:36 census at f995f30157, not a new measurement. The authored-C++
delta is zero. Local receipt: build/codex-sol-session-progress-20261026.txt.

At this audit the five authored commits are still pending publication.
Each commit invoked /opt/runner/publish in the same command; the final repair
was deferred because the shared push slot was occupied. Do not poll or invoke
publish alone. The runner will publish a retained final batch. Keep the
following eleven file claims until publication is confirmed, then release them
and run `python3 tools/claims.py release --landed`:

- Code/GameEngine/Source/GameLogic/Object/Update/RadarUpdate.cpp
- Code/GameEngine/Source/GameLogic/Object/Update/RadarUpdatePoolKey.cpp
- Code/GameEngine/Source/GameLogic/Object/Update/RadarUpdateXfer.cpp
- Code/GameEngine/Source/GameLogic/Object/Update/RadarUpdateView.h
- Code/GameEngine/Source/GameClient/Drawable/Update/AnimatedParticleSysBoneClientUpdate.cpp
- Code/GameEngine/Source/GameClient/Drawable/Update/AnimatedParticleSysBoneClientUpdateView.h
- Code/GameEngine/Source/GameLogic/Object/Update/AnimatedParticleSysBoneClientUpdatePoolKey.cpp
- Code/GameEngine/Source/GameLogic/Object/Collide/CrateCollide/UnitCrateCollide.cpp
- Code/GameEngine/Source/GameLogic/Object/Collide/CrateCollide/UnitCrateCollideExecute.cpp
- Code/GameEngine/Source/GameLogic/Object/Collide/CrateCollide/UnitCrateCollideView.h
- Code/GameEngine/Source/GameLogic/Object/Collide/UnitCrateCollidePoolKey.cpp

The mistakenly requested nonexistent Common/System/UnitCrateCollidePoolKey.cpp
claim was released. Blocked or unused scopes are not retained.
