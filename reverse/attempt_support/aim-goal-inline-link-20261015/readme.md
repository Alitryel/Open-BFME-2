# Aim-state goal accessor emission repair

BFME2 base e312e07cbb62a3a166b3abdfa7ba28e3227913e9.
Fixed measurement index a2839ea429, 2026-10-15 13:35 UTC, derived from
census 5986a99448, 2026-10-15 04:52. Its SHA256 is in index-meta.json;
the paired check leaves the index and committed census/status unchanged.

AIAttackAimAtTargetStateOnExit.cpp emitted an unused four-byte
StateMachine::getGoalPosition copy (80c9c5883cb8), conflicting with the
first census copy. Marking the existing accessor imported forceinline
suppresses that standalone copy and preserves every retained instruction.
The existing +0x24 member calculation and caller identities remain grounded
in their previously verified retail bodies and ledger provenance. Neither
this outline nor the first census copy has a proven retail address: this
repair makes no new standalone identity or canonical layout claim.

## Acceptance and improvement

- Before and after bounded link_check.py --prepare-current: 3/3 matched rows
  with strict reusable current-input receipts. Independent ./build.sh: 3/3;
  one float reference, zero string/import references, no skipped references.
- Exactly one COMDAT disappears, with no new COMDATs. All 17 retained COMDATs
  and all retained nondebug sections preserve bytes, flags, extent, external
  definitions, symbolic relocations and weak/external bindings. No retained
  section relocates to the removed copy. Data-reference facts are equal.
- Paired same-index legacy preview: two findings become one, removing exactly
  the competing getter. Remaining provider selection verdicts are unchanged;
  no new variants. Existing nonpadding bytes: 565 (ledger extents total 567).
  Legacy predicted LINKED stays 0 -> 0. No authored C++ growth, closed-strict
  closure/gain, census measurement or full-link gain is claimed.
- EH check: no EH rows on either side, zero failures. Data shadow: zero
  findings. Enforced converged-data check: eight addresses, zero second names
  or unjudged rows. Class, declared-definition, ledger and whitespace checks
  pass. Placement resweep: zero bodies and zero pins.

The unresolved updateInternal bool-argument method at native 0x003508C5
still prevents this unit from linking. Its existing 1104-byte bank and
recorded compiler-shape blocker are unchanged and were not retried.
MobMemberSlavedUpdate.cpp and AIUpdate.cpp hold the other two census getter
copies (digest 5d8d322110a2); they are distinct dependency scopes with a
different body. Their definitions and selection verdicts are unchanged.
No headers, flags, pins, ledger rows, layouts, data names or hatches change.

proof.py reproduces the comparison from the repository root against ignored
source/object/receipt snapshots in build/aim-goal-inline-link-20261015/before
and the recorded fixed index. The JSON evidence is a local object comparison,
not a closed-strict receipt.

## Donor review and boundaries

Reused the dedicated linking review and inspected BFME1 repair
c1315665a1b22beb7e6d9279548fe5b1c26ed1f9 (unused DamageInfo constructor copies).
Its imported-inline emission mechanism applies; no donor layouts, source
bodies or measured gains are inherited. Verified BFME1 checkout/gitlink
remains a7c38d3b2597121f178ab5190b3062478823257d. Official master was fetched
as e082760734795655f086939df77b393f4b728375. Another seat's live reference
file claim blocks pointer work; preserve the verified inputs and write no
freshness-success stamp. No decoder sources, census build/measure/history,
full link cycle, nightly, boot runner or shadow publisher were used.
