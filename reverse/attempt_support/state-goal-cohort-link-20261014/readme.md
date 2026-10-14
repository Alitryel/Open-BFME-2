# StateMachine local goal helper cohort

Source base: 0c802334de4d28732975585526813478ee41e50b.
Measurement index: 147cfae2cb, 2026-10-14 07:27; its SHA256 is in
object-proof.json. Committed link_status.csv (67e1365aa9) served discovery
only. No index, census, status, history or baseline was edited.

Fourteen private StateMachine views emit getGoalPosition as 8d4124c3
(lea eax,[ecx+24h]; ret), without relocations. The generic name's indexed
first copy in MobMemberSlavedUpdate.cpp has 8d4128c3 (+0x28), digest
5d8d322110a2; AIUpdate.cpp agrees. Their cached bodies still reproduce
that indexed helper, but their receipts are not currently strict reusable;
no provider currency or closed-strict claim follows from those caches.
The generic helper has no retail address. The +0x24 copies were losing
COMDATs; removing them leaves the indexed generic keeper unchanged.

Extend the existing locomotorGoalPosition helper spelling from
AIUpdateInterfaceLocomotorDistanceToGoal.cpp to these fourteen views.
Their member declarations and layouts remain unchanged. Calls through
AIUpdateInterface::getGoalPosition retain that wrapper's name. This is an
implementation helper distinction, not a recovered retail name or new layout
claim. Existing ledger evidence supplies each parent's target identity;
this repair carries those identities without adding donor identity claims.

Acceptance:

- Scoped link_check --prepare-current before and after: 267/267 matched
  rows across fourteen files, with strict reusable receipts. Independent
  ./build.sh: 267/267 exact; 139 string literals, ten empty-string references
  and 104 float literals verified; no skipped/baselined references.
- Compare all nondebug object sections (including directives), sizes,
  flags and relocation offsets/types/referents; compare all external
  definitions and undefined symbols. Only the one StateMachine helper name
  is normalized. Every comparison agrees; all 1,111 COMDAT digests/sizes
  agree. The renamed helper retains its entire four bytes and no relocations.
  Object/receipt hashes are recorded. Original sources, objects and receipts,
  plus the one-off comparison script, remain under
  build/state-goal-cohort-link-20261014/.
- Same-index legacy local preview: 324 -> 310 findings, exactly one old
  helper COMDAT conflict removed per source, no added findings. All fourteen
  units retain unrelated blockers: 0/14 clean and LINKED 0 -> 0 bytes.
  link-delta.json records each consumer's before/after counts.
- New-variants admission, frozen definitions, class gate, CSV and whitespace
  checks pass. EH: 31/31 EXACT, zero baseline/missing failures. Enforced
  converged data: fourteen sources, eight addresses, zero second names or
  unjudged rows. Shadow data has seven existing findings (three outside its
  baseline); all 267 rows' data bindings and definitions match the saved
  original objects exactly, with no unread rows. No data debt was changed.
- Placement resweep: zero bodies and zero pins.

Self-strict object verification is established for the touched units.
Closed-strict current-ledger preview was attempted and refused because 389
provider objects are missing (closed-after.txt). No closed-strict gain,
fresh census gain or link.exe placement is claimed. No maintainer runner
was started. New authored C++ bytes: zero.

Reference review: verified BFME 1 gitlink
23b143233b5a8664a3bdf8572df6d905c310a5a1. Donor repair
de59a7e9f891b3ed2d4221d151ca881f4b75a583 separates conflicting inline
helper emissions while preserving matched parents; that principle applies.
Its Apt code/layout does not transfer and no donor code was imported.
Target offset differences come from the BFME 2 objects and indexed bodies.
Fetched official BFME 1 master a7c38d3b2597121f178ab5190b3062478823257d:
only an Apt source and attempt log differ. At final claim check,
yasinschroeder-codex6 holds file:reference/open-bfme-1. The clean verified
pointer is preserved; comparative full-gate verification/pointer update
remain with that owner, and no freshness success stamp was written.

Lane discovery: repair_queue.py link; link_rank.py top/near/U/L/A/S.
name_globals dry-runs for ConstIntGettersAddr.cpp and
FireWeaponUpdateBehaviorDtor.cpp yielded zero rewrites. Their unresolved
providers and already-recorded harder repairs were not retried. The earlier
message-box repair was already landed. File claims cover this cohort.
