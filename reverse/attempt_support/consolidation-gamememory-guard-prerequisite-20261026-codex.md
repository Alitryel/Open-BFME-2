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

## Session close and publication handoff

The inherited TunnelTracker repair/recovery and this session's StatusBitsUpgrade
repair plus FireSpread blocked evidence landed in the five-commit batch ending
66ad9c43ca. StatusBitsUpgrade's landed repair is 66ad9c43ca; its ordinary trial
accepts four rows / 185 bytes, with constructor and mixed-source prerequisites
remaining. TunnelTracker recovery is separate from this session's new repairs.
The preceding obstacle-register entry records that push's inconclusive audit;
no new link cycle or audit was substituted for the missing receipt/index.
All eleven claims for that published batch were released and
`claims.py release --landed` reported zero remaining landed RVA claims.

GameMemory's authored prerequisite commit is bfe1afe5ec, pending publication at
this close. Its full header pre-commit check passed 30/30 rows over three
dependent sources (including Eva), five float references, ten literals plus
five empty-string references. The explicit changed pair passes 3/3, one data
row and converged-data enforcement; EH reports no graphs in the pair. The
shadow identity check reports zero new findings and the data check zero
findings. The publisher deferred the single commit to its normal final batch;
it was not invoked alone or polled for a slot. This receipt adds no new source
consumer or move, so the preceding complete path audit remains current.

`python3 tools/progress.py origin/master` passed at close:
BYTE-MATCHED 7,978,500 / 100.00%; LINKING 7,370,962 / 98.11%; LINKED
7,614,012 / 98.75%, each delta zero. The last two remain the census of
2026-10-26 08:28 at 47e030bafc, not this session's measurement. Authored C++
delta, source-file reduction and identity debt retired are all zero. Local
receipt: build/codex-sol-prerequisite-progress-20261026.txt.

The final runner publication must retain these five file claims until landing,
then release them and run `claims.py release --landed`:

- Code/GameEngine/Source/Common/System/GameMemory.cpp
- Code/GameEngine/Source/Common/Rva000308E0AddHeap.cpp
- Code/GameEngine/Source/Common/System/GameMemoryGuardView.h
- reverse/attempt_support/consolidation-gamememory-guard-prerequisite-20261026-codex.md
- docs/linking_obstacles.md

There is no unfinished source trial or preparation edit. The remaining work is
the ordinary Luna merge and the explicit structural/registry prerequisites above.

## Next-session recovery

The runner preserved and rebased the unpublished commits to 8809f34ccf
(prerequisite) and f847270698 (receipt). The next session found a clean tree,
read the current instructions and prior receipts, pulled master, and passed
`python3 tools/check_csv.py` (98,273 function rows). The outgoing range has
no source moves: the new guarded-view header has exactly the two consumers
already verified together above. The complete pending path audit therefore
remains the recorded header/consumer audit; no historical path is repointed.
This recovery receipt retries publication with the inherited batch. Preserve
the five listed claims until the publisher confirms landing.
