# Keyboard key definitions/repeat prerequisite — 2026-10-26 codex

Allocated family A shard 0/2 destination:
`Code/GameEngine/Source/GameClient/Input/Keyboard.cpp`.
This follows de88735255's receiver prerequisite; no merge, split, source move,
name vote or register retirement is applied.

## Demonstrated unblock

The Input-prefix planner's original paths, alternatives and prerequisites were
reviewed and regenerated after the trial; its input/output check passes. Current
routing is rebuilt in memory by the ordinary composition tool, not committed.
Before this change, the initializer redefined key enums and the repeat checker
redefined allocator/key states. Both had private Keyboard receivers.

Move the initializer's existing complete KeyDefType to KeyboardView.h, add its
existing nonvirtual method declaration and KEY_STATE_AUTOREPEAT, and make both
donors use the seed's shared receiver. Keep the repeat checker's BfmeE8 vector
call identity and record accesses through explicit casts. No vector identity,
virtual slot, receiver layout, compiler option or new name is inferred.

`tu_skeleton.py --merge <Keyboard.cpp> --dry-run` now accepts four sources:
seed, resync, initKeyNames and checkKeyRepeat, **15 existing rows**. This adds
the **8,023-byte initializer and 111-byte repeat checker** to the previous
13-row composition. This is a prerequisite unblock for Luna; no downstream
merge or census result is claimed.

Remaining: KeyboardInitUpdate.cpp redefines KEY_STATE_DOWN and lacks virtual
method declarations; KeyboardRva00232AE8.cpp and
rva00232B7BRva00232B7BFarm.cpp conflict with STLport allocator declarations.
GapBodiesGE04.cpp and GapBodiesSeat1A.cpp remain mixed and untouched. Further
vector/ABI reconciliation requires its own evidence and checks.

## Acceptance and bindings

- `./build.sh <seed> <resync> <repeat> <initializer>`: **15/15**, one data row,
  two imports. `find_declared_unmatched.py` passes all four; class_gate.py passes
  both newly adapted consumers and the shared header.
- `link_check.py --prepare-current --paths-from
  build/codex-keyboard-keydefs-sources.txt`: **15/15**, strict reusable receipts.
  No census/index update or maintainer runner.
- Supported object APIs (`allowed_symbols.Obj`, `_object_defs` and census COMDAT
  policies) compare preserved before objects with strict current objects. All
  non-debug/non-directive section bytes, flags, normalized relocations, COMDAT
  policies, external code definitions and undefined references are identical.
  Definition counts are 14/1/1/1 and section counts 18/1/1/2 for seed/resync/
  repeat/initializer. Local relocation targets are normalized by section,
  offset and type. The batch's directive-alias union is identical. Therefore
  no provider candidate, selected body or consumer binding changes.
- `allowed_symbols.scan` preserves all **28 code/data reference facts**. Eleven
  initializer facts change compiler local-label spellings only; normalization
  ignores that spelling for section-local labels. The independent section and
  relocation comparison retains each target section, offset and type.
  `data_check.object_facts` preserves all definition/reference facts.
- Converged data, EH (one EXACT graph), new COMDAT variants, and diff-whitespace
  checks pass. Existing code/data identity keys and header queues are preserved;
  the initializer retains its OurLanguage data ownership and MS-header entry.
  A fresh scoped ms_header_audit.py show is retained.

Scratch: build/codex-keyboard-keydefs-{before-files,before-objects}/,
*-sources.txt, *-dryrun.txt, *-planner.txt, *-object-proof.json,
*-reference-delta.json, *-data-delta.json, *-ms-headers.txt, *-path-audit.txt.
Proof scripts use supported inspection APIs; no manual match-cache compilation.

## Complete batch audit and measurements

Audited both pending commits 36240d337d and de88735255 plus this staged change.
The origin/master..HEAD diff also contains incoming remote changes; outgoing
history and merge-base comparison isolate the two local commits. Neither those
commits nor this repair moves/deletes/renames existing source paths. Searches
cover active tools, hooks, workflows, source includes, build inputs, registries,
queues and docs. The new Keyboard header has its four intended consumers;
RepairDockUpdateView has two. No active path consumer needs repointing; all
original EA paths, row ownership and protected debt keys remain. Read the
pre-push batch audit for freshness uncertainty at eventual publication.

File reduction **0**, registered debt retired **0**, recovered C++ bytes **0**.
No linked-byte/ownership gain is measured. Keep pending file claims until
publication is confirmed, then release file scopes and settle --landed.
