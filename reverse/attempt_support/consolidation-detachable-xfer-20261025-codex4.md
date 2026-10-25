# DetachableRiderUpdate Xfer prerequisite, 2026-10-25

Allocated family A shard 1/2 destination:
Code/GameEngine/Source/GameLogic/Object/Update/DetachableRiderUpdate.cpp.
Reviewed current scoped Update planner original paths, alternatives, mixed
routing and protected/template prerequisites; currency check passed before edit.
Current tu_skeleton --plan and ordinary merge dry-run receipts are in
build/codex4-detachable-{plan,before,after}.txt. No map or owner changes.

Before: ordinary --merge TU --dry-run accepted no donors. Xfer's BfmeXfer.h
was hoisted above its required Snapshot/operand declarations. Moved the exact
existing declarations and include together into private
DetachableRiderXferPrefix.h. Class definitions, bodies and compiler flags are
unchanged; shared BfmeXfer.h is unchanged.

After: same ordinary dry-run accepts seed and DetachableRiderUpdateXfer.cpp,
five rows, 772 retail bytes. Demonstrated unblock for Luna, not a confirmed
landing. WeaponTemplateSetConstruct remains rejected (duplicate _Construct
template definition); killRider remains rejected (DisabledType declaration
order and conflicting private DetachableRiderUpdate/UpdateModule views).
Three protected and five mixed sources remain. No merge applied.

Checks:
- ./build.sh both: 5/5 exact, string/float/import checks pass.
  find_declared_unmatched.py passes. EH: zero requiring EH, zero missing objects.
- allowed_symbols scoped sources: 21 references, 20 owner and one certified
  fold, zero wrong bindings; complete reference report unchanged.
- Fresh baseline/final _object_defs: identical code digests, extents, COMDAT
  flags and undefined names. data_check.object_facts: identical data bindings
  and defined data, zero unread rows. Ignored codex4-detachable-* receipts.
- Ordinary dry-run composed object 1d224feab5ea4308.obj: same complete union of
  original external code definitions/COMDAT flags; same data facts, no unread
  rows. Its five rows give the same 21 correct references. No selected provider
  or consumer binding changes.
- data_check.py --converged both: two sources, ten addresses, zero second names,
  zero unjudged rows. link_check.py --new-variants both exits 0. Neither source
  owns a code identity, data or header/MS-header queue finding.

Publication compatibility audit: base 2538d83cfd through pending Upgrade/Rain/
OCL commits and this staged wrapper has no source moves/absorptions. Reviewed
origin/master..HEAD and isolated outgoing paths with the triple-dot diff
because origin advanced independently. Active tools, hooks, workflows, includes,
build inputs and registries need no repointing. The existing Xfer source is the
sole new-header consumer. Historical EA paths and protected debt keys remain.
File reduction, identity debt retired and recovered C++ bytes are separately
zero for this prerequisite.

Additional OCL trial was abandoned before edits when claims were refused:
yasinschroeder-codex2 owns OCLUpdate destination, countdown and Rva0049B2A2Xfer,
plus its other donor RVAs. Its follow-up should stack on our pending GameLogic
adoption 5a04e55474, which retires the header-adoption blocker. Released both
new speculative header claims (OCLUpdateTimerView.h and OCLXferPrefix.h).
No changes or pending body attempts remain from that refused scope.

Keep claims until publication: DetachableRiderUpdate.cpp,
DetachableRiderUpdateXfer.cpp, DetachableRiderXferPrefix.h and 0x004AE7AD.
Earlier pending claims are listed in their handoffs. File:Common/
OCLUpdate_getRemainingFrames.cpp and 0x0049B303 remain held until its commit
lands; release promptly after publication so the other worker can proceed.
