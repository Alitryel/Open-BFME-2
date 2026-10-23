# Link-repair queue reassessment, 2026-10-23

Inputs: BFME 2 `83f341924d`, BFME 1
`96c88c73a5cd1a58fc2f8db691beea50acd996db`, published census
`b711de3634` (2026-10-23 14:28, retail-truth-4). The published index and
objects were fetched successfully. No source, header, ledger, pin, or baseline
was changed in this reassessment. No new linked-byte gain is claimed.

The rankings describe the published census, not necessarily current sources.
Run scoped current-source previews before attempting their proposed repairs.
The following current previews already link without a change: ArmySummaryCopy,
LivingWorldRegionConstructor, AIStatCollector, Rva0018BEC7Ctor (the Fog
namespace constructor), the POD28 allocate-copy helper, the narrow string
substr helper, and StlSweepR3Rva002A3FAF. These are inherited results, not
repairs authored by this seat. AIStatCollector's old missing-provider handoff
does not describe its present scoped legacy result (362 B link).

## Current prerequisites

`python3 tools/link_check.py` on these paths gives:

| Unit | Current linked / matched B | Remaining blockers |
| --- | ---: | --- |
| Common/Thing/ModuleFactory.cpp | 0 / 2,421 | GrantScienceUpgradeModuleData::buildFieldParse undefined; ModuleData destructor unproven and differs from kept copy; UpgradeModuleData destructor is not retail's, including the selected definition |
| GameLogic/Object/Update/FireSpreadUpdate.cpp | 0 / 205 | BitFlags<13> DISABLEDMASK_NONE and UpdateModule::crc undefined |
| GameLogic/Object/Update/DeletionUpdate.cpp | 0 / 130 | Same two undefined names |
| W3DDevice/GameClient/RTS2DSceneCtor.cpp | 0 / 163 | RTS2DScene virtual destructor undefined |

The first three paths are relative to `Code/GameEngine/Source/`; the last is
relative to `Code/GameEngineDevice/Source/`.

ModuleFactory's old insertion/allocator blockers have gone; its remaining
destructor and parse-provider requirements are separate work. See
`modulefactory-provider-link-20261020/readme.md` for earlier repair evidence.
Changing only the common ModuleData destructor also cannot isolate a gain in
the reviewed sibling cohort: their other unresolved/selected blockers remain.

The Update units use the ZH-derived 13-bit declaration. Target evidence for the
disabled-state family uses 11 bits (the bound in retail 0x001C81C0 and script
handling at 0x001D01D0); an 11-bit global/getter provider already exists. This
does not prove which donor enum members should be removed, or establish a
target UpdateModule::crc provider. Replacing the global type alone is not a
verified repair. The Snapshot contract has four slots, so adding a CRC slot
without reconciling the class would introduce another unsupported view.
Read `update-virtual-link-20261021/readme.md` and attempt-log entry for
FireSpreadUpdate 0x0048B769: removing its unverified destructor/CRC was already
tried and preserved bytes but left the constructor's vtable unresolved. That
unchanged experiment was not repeated.

RTS2DScene needs its native virtual-destructor provider; inventing an empty
definition or a scalar-deleting alias is not justified by the constructor.
No compiler trial was started for these unchanged prerequisites.

## Fallbacks checked

- `link_rank.py --top 30`, near rankings through eight blockers, and
  `class_views.py --blockers`: reviewed current providers and existing banks;
  high-byte remaining classes require actual class/vtable reconciliation.
- BFME 1 link-repair commits at the verified donor pointer were compared with
  applicable BFME 2 units. Previously inherited repairs were not re-credited.
- `repair_queue.py link`: cross-checked its leads against current previews;
  a suggested command marked "pass test" is not itself a measurement.
- `name_globals.py --dry-run`: zero files changed, zero edits kept.
- `rehome_rows.py --limit 12`: scanned 104 candidates, four byte-exact moves.
  AptOnlineLogin, View, and the POD12 tree/map pairs already link on both sides
  (10,885 B, 819 B, and 1,143 B respectively). LivingWorldAutoResolveBattle
  retains independent blockers. No rehome was applied because none isolates
  a linked-byte gain.
- Reviewed narrow map/pair, Vector3, SysTime, DamageFX, shader and module
  blocker banks before considering repeat trials; their unresolved identity,
  ABI or compiler prerequisites remain. See existing tracked handoffs rather
  than restarting their disproven source variants.

These are scoped **legacy** previews only. No self-strict or closed-strict
gain is claimed. No census, full link cycle, nightly or boot runner was run.
The data-back artifact fallback was unavailable without a matching cycle
bundle; that missing artifact was not treated as proof of an empty queue.
No claims were acquired and no production edits need resuming. Reassess these
cohorts after the named providers or class contracts change.
