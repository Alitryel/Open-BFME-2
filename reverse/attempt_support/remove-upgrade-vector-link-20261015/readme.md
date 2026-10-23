# Upgrade-removal vector provider repair

BFME2 base: `9ab203bd1df614deb1375a43b5ba90df7da57c04`.
Consumer: `Code/GameEngine/Source/GameLogic/Object/Upgrade/RemoveUpgradeUpgradeImplementation.cpp`.
Its existing 528-byte row is at RVA `0x004B8095`.

A TU-local explicit specialization declaration leaves ScienceType vector
push_back to its existing shared provider at `0x002E01C6`, rather than emitting
another copy and its unused overflow/allocation dependencies. This preserves the
consumer's established UpgradeID-to-ScienceType ICF spelling. It introduces no
new identity, alias, pin, type layout, compiler flag or shared header change.
Retail bytes and relocations independently establish the caller's invariance;
the existing identity/layout evidence in the source remains unchanged.

## Paired measurement

Both phases refresh the saved-before/current consumer and the same strict-current
ThingTemplate.cpp and Player.cpp provider witnesses into separate in-memory
copies of the frozen runner index. Its receipt commit is `825b86983f`, dated
2026-10-15 12:37; the underlying census commit is `5986a99448`, 04:52.
Index SHA256: `672f6ffe10798a1e82a1516e32c7d579bd787503faae7ee6beabb6e4cca2b93c`.
Discovery link_status.csv was measured at `4b7e7091c4`; that stale discovery
artifact is not the before measurement. No index or census status was changed.

Consumer findings fall **5 to 0**, with no unresolved, duplicate, address or
wrong-selected finding in either phase. The removed findings concern deallocate,
max, allocation-proxy deallocate, vector clear and vector insert-overflow.
All **26 retained COMDATs** have identical bytes, extents and relocation digests.
The only removed nondebug sections are 19 redundant COMDATs and their one unused
overflow EH handler/table pair. SafeSEH loses only that handler's entry. Other
normalized nondebug sections and linker directives are identical. No retained
section refers into the removed subtree except the unchanged push_back call.

The selected winner identity, digest and retail verdict for each of the 19
removed names are identical before/after. Both provider units' full finding
sets are unchanged. proof.json records exact names, object/source hashes and
provider receipts; proof.py asserts these properties and no new variants.

Default local link_check predicts **LINKED 0 to 528 existing retail bytes**.
New authored C++ bytes: **0**. These are legacy local preview results. Strict
compilation receipts do not establish self-strict or closed-strict link gains.
The bounded current-ledger preview refuses 799 missing provider objects; it does
not rebuild them. ThingTemplate.cpp and Player.cpp also retain independent
findings enumerated in proof.json. Broader closure therefore remains outstanding.
No full census, link cycle, nightly, boot or scheduler runner was invoked.

## Acceptance

- Normal whole-consumer byte gate passes 1/1. Bounded strict preparation for
  consumer plus both provider units passes **41/41** with reusable current
  receipts and no unverified string, float or import discrepancies.
- EH verification: **1 EXACT**, no baseline exceptions or missing objects.
- Data enforcement on all three units: zero findings. Converged-data check:
  eight addresses, zero second names or unjudged rows.
- Consumer class gate and declared-definition check pass. Placement rescan:
  zero bodies and zero pins. Whitespace and ledger checks pass.
- Default local consumer link check exits 0; the current-ledger preview exits 1
  for the missing objects documented above. New-variant checks pass. Normal
  commit hooks must also pass before publication.

## Reference review and triage

Reviewed BFME1 repairs `53d32d6b4b377317a3397971629ca3ad20b870e9`
(Apt constructor emission suppression) and
`66b19a8e95a4add525ef808fcea088e306798e2b` (allocation-copy suppression).
The existing-provider/emission principle applies; no donor source or layout was
imported. The clean verified donor checkout/gitlink remains
`a7c38d3b2597121f178ab5190b3062478823257d`. Official master fetched as
`d891c34e379868ebb0aa92a47aa7b798f9d2d1ac`. Its freshness stamp is overdue;
another worker's reference-scope claim and the incomplete old-input comparison
with thousands of stale units prevent a verified pointer update. The stamp was
not advanced and the last verified inputs were retained.

Discovery used repair_queue.py link and link_rank.py rank/near/per-file checks.
Many census findings were already repaired in current objects. A Drawable getter
trial was restored because its strict current baseline already had zero
findings; the blocked triage is logged and its file claim released. Existing
deferred hard dependencies were not retried. The consumer file claim is released
after this repair is committed.

Run proof.py from the repository root with the frozen index, current provider
objects, and the saved baseline in `build/remove-upgrade-link-20261015/`.
Saved object binaries stay in ignored scratch; the tracked script and JSON are
attempt evidence, not production gate tooling.
