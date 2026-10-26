# DemoTrapUpdate module-data prerequisite, 2026-10-26, codex4

Allocated family A shard 1/2 target:
`Code/GameEngine/Source/GameLogic/Object/Update/DemoTrapUpdate.cpp`.
The scoped Update naming planner and currency check passed before editing
(build/codex4-update-planner-stable.txt). Its packet has donor-path hints,
not a retail image filename for this TU. Private classes, flags, quoted
includes, mixed rows, constructor hatches and pool-key identity remain explicit
prerequisites. The current-map normal plan approves ten rows, seven donors
and three mixed files; that routing, rather than the hints, approves placement.
No row or source path is moved by this change.

The normal before dry-run accepted no pair. In particular the seed's private
DemoTrapUpdateModuleData omitted its constructor, producing C2600 when the
55-byte constructor donor joined it. Their accessed fields describe the same
prefix but use different types/names. The constructor's existing declaration
now lives in DemoTrapUpdateModuleDataView.h and both consumers include it.
Fields become public for the existing update accesses. The update uses the
constructor's existing scan-rate/friendly-mode fields and views its +0x0C
zero block as the same existing BitFlags<69> argument. This preserves all field
offsets, the zero-block helper constructor and its call, vtable binding, flags,
receiver convention and stores. No new donor identity or complete layout is
claimed. The counted /alternatename remains in the constructor donor.

Verification (build/codex4-demotrap-* and build/codex4-prereqs-*):

- Before and after ./build.sh on the seed and constructor: 4/4 rows exact,
  433 bytes, including the two generated EH funclet rows. Frozen-file checks
  pass. The combined after build with LifetimeUpdate verifies 5/5 rows and
  all literal checks. EH verifier: one applicable row EXACT, zero missing
  objects or baseline exceptions; renumbered $L labels verified against EH data.
- Standalone before/after snapshots are identical: all external code-definition
  fingerprints, extents and exclusivity; undefined symbols; and per-row data
  facts. Scoped allowed_symbols for the three prerequisite sources has
  18 references (16 owner, one EH, one alias), zero wrong code bindings.
  Converged data: three sources, ten addresses, zero second names/unjudged rows.
- Normal upstream --merge TU --dry-run now accepts the seed and module-data
  constructor: four rows / 433 bytes. The actual composed object is
  build/tu_skeleton/02e8a3a12f56e508.obj. Upstream COFF helpers confirm all four
  definitions retain the standalone union's fingerprints, sizes, exclusivity
  and actual COMDAT selection maps. Its 17 undefined symbols equal the donor
  union after internal resolution. Per-row data facts remain the same:
  vtable at 0x0084ED70, ThePartitionManager at 0x009FE748 and __except_list.
  This is a demonstrated dry-run unblock, not a confirmed Luna landing.
- Ordinary data checking preserves the pre-existing constructor vtable
  wrong-name finding at 0x0084ED70; it is not repaired by sharing declarations.
  The pool-key donor separately still has wrong-name findings for guard/key
  at 0x00A03A48/0x00A03A44. No data or identity key is retired, and no hatch
  count or baseline is edited. The seed and constructor have no code/data
  identity register keys to transfer; the constructor's hatch stays put.

Remaining composition blockers: pool-key method declaration, primary receiver
constructor/ABI, onObjectCreated and accessed module-data fields, status-enum
names in Rva00495A2B, and Snapshot include ordering for Xfer. Three mixed donors
remain. Leave the newly compatible seed/constructor pair for Luna. The dry-run
printed a future hatch-transfer trailer; it does not apply to this repair,
which performs no merge or register transfer.

Publication compatibility audit across origin/master..HEAD plus pending edits:
no source moves/deletions/renames. The new private header has exactly the two
intended consumers, verified together. Active tools, hooks, workflows, includes,
build inputs and registries need no repointing. Historical EA literals remain.
The pending LargeGroupAudio header and LifetimeUpdate adoption add no source
moves either. Receipt: build/codex4-prereqs-path-audit.txt. Keep destination,
constructor, new header, evidence and two RVA claims until confirmed landing.

Other scoped triage: UnpauseSpecialPowerUpgrade's existing receiver/base ABI
blocker is unchanged; no broad trial repeated. DockUpdate approach-position
already uses the constructor-bearing Coord3D companion required by its ABI;
a plain-header substitution is not an established fix. Those read-only reviews
make no cleanup claim. No cross-family or maintainer-only runner used.

Measurements: zero files removed, zero recovered C++ bytes, zero identity/data
debt retired. The separate LifetimeUpdate commit retires one header-queue row.
