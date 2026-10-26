# TunnelTracker rejected donors, 2026-10-26

The refreshed shard 1/5 allocation and current planner approved
`Code/GameEngine/Source/Common/RTS/TunnelTracker.cpp`. The current merge dry run
accepted only its seed and `TunnelTrackerGetCurNemesis.cpp` plus
`TunnelTrackerUpdateNemesis.cpp` (six rows); the applied and verified merge
removed those two fragments. The other donors were left unchanged. Their
compiler diagnostics point to prerequisites for a future Sol pass:

- `TunnelTrackerContain.cpp`: `_alloc.h(446) C2950` (explicitly instantiating
  explicit specialization); `TunnelTracker.cpp` trial C2039: `getContainMax`
  is not a member of `TunnelTracker`.
- `TunnelTrackerCtorBfme.cpp`: `_alloc.h(446) C2950`; trial C2600: constructor
  cannot be defined because it is not an explicitly declared member.
- `Thing/TunnelTracker_isValidContainerFor.cpp`: `_alloc.h(446) C2950`; trial
  C2039: `isValidContainerFor` is not a member of `TunnelTracker`.
- `Thing/TunnelTracker.cpp`: `_alloc.h(446) C2950`; trial C2039:
  `removeFromContain` is not a member of `TunnelTracker`.
- `TunnelTrackerDtor.cpp`: `_alloc.h(446) C2950`; trial C2600: destructor
  cannot be defined because it is not an explicitly declared member.
- `Rva004F56FCAdd.cpp`: `_alloc.h(446) C2950`; trial C2664: `list::push_back`
  cannot convert the argument to its element type.
- `Rva004F571BReplaceContainedOwner.cpp`: `_alloc.h(446) C2950`; trial C2039:
  `tunnelContainer` is not a member of `Object`.
- `TunnelTrackerXfer.cpp`: `_alloc.h(446) C2950`; `BfmeXfer.h(37) C2061`:
  syntax error, identifier `Snapshot`.
- `TunnelTrackerLoadPostProcess.cpp`: `_alloc.h(446) C2950`; trial C2039:
  `loadPostProcess` is not a member of `TunnelTracker`.
- `TunnelTrackerDeleter.cpp`: trial C2511:
  `TunnelTracker::TunnelTracker(EmitVtableTag *)` has no matching overload in
  `TunnelTracker`.

Do not retry these unchanged trials. Manual declaration, layout, shared-header
and include repairs are outside the mechanical consolidation seat. The applied
subset passed `./build.sh Code/GameEngine/Source/Common/RTS/TunnelTracker.cpp`,
`find_declared_unmatched.py`, staged code-identity/data checks, and staged
COMDAT/provider checks. Old path mentions remain only in provenance comments
and historical evidence (`reverse/link_status.csv` and prior attempt notes); no
active path consumer needed repair.

After rebasing onto `origin/master` at `4d2094622a`, the refreshed pre-push
`link_batch_audit.py` was inconclusive: its provider index is at `763dc8759f`
and it reports that the current `TunnelTracker.cpp` object lacks a current
receipt. Do not treat this as link clearance; carry the unit into the next
census. `docs/linking_obstacles.md` is currently claimed by
`yasinschroeder-codex`, so this seat left that shared register untouched and
hands off the audit evidence for its owner to record.
