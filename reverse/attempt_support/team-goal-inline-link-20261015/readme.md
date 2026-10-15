# AIPlayer team-build goal accessor emission repair

Base BFME2 tree: a587597496b57ca26bbefc9dccae766606048392.
Measurement index: a2839ea429, 2026-10-15 13:35 UTC, derived from census
5986a99448, 2026-10-15 04:52. SHA256 and paired findings are recorded in
index-meta.json and object-proof.json. The index and census were not changed.

AIPlayerTeamBuild.cpp emits a competing seven-byte
AIUpdateInterface::getGoalPosition outline (7502c9406d0c). The existing view
loads the state machine at +0x30 and adds +0x24. Its already matched caller,
AIPlayer::onUnitProduced at 0x004F4962, establishes the retained inline
calculation; its original BFME1/BFME2 provenance remains in the ledger.
There is no proved native standalone address for this getter, so neither
its outline identity nor the census winner's layout is asserted here.

Mark only getGoalPosition imported forceinline. This preserves its inline
use while suppressing the unused competing definition and the now-unused
four-byte getStateMachine and locomotorGoalPosition outlines. No incoming
nondebug relocation from retained sections names any of these three bodies.
No imported reference, undefined name, weak binding, flag, header, private
layout, data name, pin, ledger row or hatch count changes.

## Verification and improvement

- Bounded link_check.py --prepare-current before and after: 35/35 rows,
  strict reusable current-input receipts. Independent ./build.sh: 35/35;
  37 strings plus three empty references, seven floats, zero named imports;
  no skipped or baselined reference checks.
- EH: 13/13 EXACT. Class and declared-definition gates pass. Shadow data:
  zero findings. Enforced converged data: eight addresses, zero second names
  or unjudged rows. CSV and whitespace checks pass.
- Paired proof: exactly three outline COMDATs disappear; all 181 retained
  COMDATs and every retained nondebug section byte, flag, extent, definition,
  symbolic relocation and external/weak binding remain identical. No new
  variants. Data facts are equal. Selection verdicts for remaining copies
  of all three affected names are unchanged.
- Same-index legacy preview: 19 -> 18 findings, removing exactly the goal
  getter conflict; eight unresolved, eight other COMDAT, and two selected
  findings remain. The unit contains 9,097 existing nonpadding bytes, but
  predicted LINKED remains 0 -> 0. No new authored C++ bytes, closed-strict
  closure/gain, census measurement or actual-link gain is claimed.
- Placement resweep: zero bodies, zero pins.
- The commit hook's code-identity shadow check reports eight existing
  binding/definition findings (queueSupplyTruck, TeamPrototype-list lifetime
  and helpers, Object body getter, Team/TeamPrototype name getters). The
  paired proof preserves all these retained bindings and definitions; this
  repair does not assert they are resolved. No protected baseline changes.

The unchanged blockers are listed in link-after.txt: TeamInQueue ctor and
predicates, queueSupplyTruck, ScriptEngine helpers, TeamPrototype reset,
BuildListInfo string getter, friend_getNextTemplate and TeamPrototype-list
allocation/lifetime copies. They need independent evidence and repairs.
The other two census goal getters have different bodies and dependency
scopes (MobMemberSlavedUpdate and AIUpdate); this repair does not change them.

proof.py reproduces the paired comparison from the repository root using
ignored source/object/receipt snapshots in
build/team-goal-inline-link-20261015/before/ and the recorded unchanged index.
The stored JSON is local evidence, not a closed-strict or census receipt.

## Donor review and limits

Verified BFME1 checkout/gitlink remains a7c38d3b2597121f178ab5190b3062478823257d.
Official master was fetched at e082760734795655f086939df77b393f4b728375.
Its live foreign file claim prevents pointer work here; preserve the verified
inputs and write no freshness-success stamp. Reviewed donor repair
c1315665a1b22beb7e6d9279548fe5b1c26ed1f9 (unused DamageInfo ctor copies),
plus the existing BFME2 locomotor-getter repairs. Only their imported-inline
emission mechanism is applicable; donor layouts and gains are not inherited.
No decoder source was read and no census build/measure/history, full link
cycle, nightly, boot runner or shadow publisher was started.
