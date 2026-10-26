# GameMemory guarded-helper prerequisite, 2026-10-26, codex

Allocated family A shard 0/2 destination:
`Code/GameEngine/Source/Common/System/GameMemory.cpp`. No merge or split applied.

The existing seed's HeapTable view and Rva000308E0AddHeap.cpp's smaller view
collided in the ordinary composition trial (C2011, MemoryPool::HeapTable).
Both consumers now include GameMemoryGuardView.h, carrying the seed's existing
partial view: clear flag at +0x404, adding-heaps flag at +0x40D, size 0x410.
The full memory_pool.cpp view independently has those fields at these offsets.
The single extern g_heaps binding and its separate memory_pool.cpp definition
are unchanged. The AddHeap function-pointer definition and every body and flag
remain unchanged. No new data name or layout recovery is claimed.

The ordinary `tools/tu_skeleton.py --merge TU --dry-run` now accepts all five
direct donors / six existing rows / 279 retail bytes, with no direct rejection.
Before the repair it accepted four donors / five rows and rejected the 16-byte
AddHeap helper. This is a demonstrated prerequisite unblock, not a later Luna
landing, file reduction, recovered bytes, debt retirement or census gain.

Checks and local receipts:

- `./build.sh GameMemory.cpp Rva000308E0AddHeap.cpp`: 3/3 exact before and after,
  one data row exact. `find_declared_unmatched.py` and scoped `class_gate.py`
  pass. Converged data check: two sources, ten addresses, no second names or
  unjudged rows. `link_check.py --prepare-current` on the same pair passes
  strict reusable receipts without changing census/index/status.
- All three external code definitions, six non-debug sections, data bytes,
  normalized relocations, COMDAT policies, undefined symbols and alternates
  are identical in the two edited objects. Data bindings/definitions are equal.
  The code-reference identity scan has zero facts in both versions; this is not
  a claim to have checked callers through a zero-fact scan.
- `./build.sh Rva00030730Init.cpp stlport_byte_allocator.cpp GameMemoryFree.cpp`:
  the other three donors pass 3/3, six data rows, thirteen literals and two
  named imports. These sources were verified, not edited or moved. In particular,
  the Libraries donor remains with its assigned owner.
- The normal trial's composed object, build/tu_skeleton/3fd89a3796ef44f1.obj,
  retains all six code definitions, their COMDAT choices and all alternates.
  Its twenty external data/string definitions retain bytes, flags and COMDAT
  policies. Per-source data bindings are unchanged; the union of data
  definitions is equal. The resolver's external AddHeap-pointer reference
  resolves internally to the same original definition when composed. After
  accounting for that verified resolution, the undefined-symbol union is exact;
  no other provider or binding changes. An initial scratch comparison subtracted
  only code definitions, so it reported this data reference as missing; the
  expanded comparison verifies both code and data definitions explicitly.
- Scoped Common/System name planner regenerated after the edit and
  `name_lane.py consolidate --check build/consolidation` passes. The report's
  original-path alternatives and blockers were reviewed; hints did not approve
  any move. The normal trial rebuilt current TU routing in memory. No committed
  TU map or protected register was edited.
- Receipts: build/codex-gamememory-{before,after}-build.txt,
  build/codex-gamememory-{before,after}-trial.txt,
  build/codex-gamememory-other-build.txt,
  build/codex-gamememory-object-proof.json,
  build/codex-gamememory-reference-delta.json,
  build/codex-gamememory-data-delta.json,
  build/codex-gamememory-composition-proof.json and
  build/codex-gamememory-prepare.txt. Scoped comparisons use the normal object,
  identity and data-check readers; no manual compile touched match caches.

Remaining merge prerequisites: four mixed files remain mixed; the vendored
ZLib source remains refused. The earlier mechanical handoff's active inventory
blocker is still real: docs/doxygen/pages/subsystems/memory.md names
GameMemoryFree.cpp and stlport_byte_allocator.cpp. The merge tool repoints
sources.cfg, not that prose table. Update the table coherently with a future
merge, retain historical provenance, and coordinate any Libraries donor scope
with its assigned owner. Existing memory_pool.cpp identity/data debt and
MemoryPoolInit.cpp data/header/hatch ownership remain with those untouched files.

Publication audit: there are no unpublished local moves before this repair;
the raw origin/master..HEAD diff includes newer upstream-only commits. This
repair adds one header and edits two consumers without moving a source. Active
Code/tools/hooks/workflow/build-input searches find exactly those two includes,
both verified together. Ledgers, registries and historical EA strings need no
repointing for this prerequisite. File reduction and identity debt retired are
zero; recovered C++ bytes are zero. Keep the five source/header/handoff/register
claims until publication is confirmed.

Other allocated probes this pass: UpdateModule's current ordinary trial already
accepts seed plus Xfer donor / two rows, superseding its old include-order
refusal; no repair was needed and its unused claims were released. Known
Keyboard, GiantBird, RankInfo, HeaderTemplate and dock/upgrade structural
boundaries were read rather than repeating unchanged blocked trials.
