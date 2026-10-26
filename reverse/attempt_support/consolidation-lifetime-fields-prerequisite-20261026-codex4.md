# LifetimeUpdate frame-field prerequisite, 2026-10-26, codex4

Allocated destination: Code/GameEngine/Source/GameLogic/Object/Update/LifetimeUpdate.cpp.
Stacks on 5a78a88cac's shared module-data declaration prerequisite.

## Repair and demonstrated unblock

Expose the two already evidenced frame words at +0x20 and +0x24 in the update
view, replacing exactly eight bytes of padding. The calcSleepDelay and Xfer
donors already access those offsets. Preserve the view's extent and +0x28 byte.
Composition then exposed the calcSleepDelay donor's source-line sensitivity:
its padded __LINE__ moved away from retail's diagnostic argument 118. Pass the
observed value explicitly and remove the padding. Retain retail's complete EA
source-path string and unchanged random/frame logic.

Before: the normal dry-run accepted seed plus module-data constructor, five
rows / 274 existing retail bytes. After: it also accepts calcSleepDelay, six
rows / 329 bytes. This demonstrates one further compatible donor (55 existing
bytes), not a Luna landing or newly recovered bytes. Leave the merge to Luna.
Remaining rejected donors need pool getter declarations, Xfer base declarations,
and constructor/base ABI plus canonical GameLogic adoption. Mixed rows remain.

## Verification and binding evidence

- ./build.sh on update and calcSleepDelay: 5/5 rows exact, including the 55-byte
  calcSleepDelay body; literal, float and import checks pass. Both sources pass
  find_declared_unmatched. Before/after complete standalone code fingerprints,
  sizes, exclusivity, unresolved names and data facts compare equal in
  build/codex4-lifetime-fields-{before,final}.json.
- allowed_symbols: thirteen owner references, zero wrong bindings. Converged
  data check reports no second names or unjudged rows. No debt keys retired.
- Final normal --merge --dry-run receipt:
  build/codex4-lifetime-fields-final-trial.txt. Inspect its actual composed
  object build/tu_skeleton/12399f8d70f7c89f.obj: all ten code definitions retain
  fingerprints/sizes except the previously inspected absent-from-retail
  module-data anchor (9 to 28 bytes, constructor stores inlined). All ten
  COMDAT selections equal the standalone union. The eleven unresolved names
  equal the donor union after internal resolution; per-row data references
  retain the vtable alias, GameLogic and original diagnostic string. Anchor
  disassembly/referrer evidence is recorded in the preceding prerequisite.
- Existing constructor _vtbl_00C4ED70 wrong-name debt remains unchanged; this
  repair does not establish a new vtable name or retire identity debt.

## Batch audit and handoff

Reviewed the scoped Update planner's Lifetime packet before editing; the
normal trial rebuilds stale routing in memory. No merge, split, source move,
ledger repoint or TU-map regeneration is committed. Audit pending
origin/master..HEAD plus these changes: the preceding private header has only
its two verified consumers; this change adds no path consumers. Active tools,
hooks, workflows, includes, build inputs and registries need no repointing.
Historical EA paths and protected registers remain intact.

Net file reduction zero; recovered C++ bytes zero; identity debt retired zero.
Keep pending-batch file claims until publication, then release manually and
settle landed RVAs. Leave the compatible three-source merge to Luna.

Additional read-only allocated probe: AssistedTargetingUpdate's normal trial
accepts no donor pair. Pool-key lacks rva000486E31, constructor lacks m_vtable
and m_secondary0C, and feedback-laser composition redefines Coord3D. No edits
or claims were taken. Receipt: build/codex4-assisted-current-trial.txt.
