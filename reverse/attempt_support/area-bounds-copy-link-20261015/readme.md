# AreaPolygon copy-constructor emission repair

AreaPolygonUpdateBounds.cpp now marks its existing MathCoord2D copy constructor
imported forceinline. The bounds-refresh caller already inlines the copy;
the change suppresses an unused 19-byte standalone COMDAT that differs from
the first indexed copy in PathfinderSidewaysAttack.cpp. The constructor's
field copies, caller, compiler flags, headers, ledger and pins are unchanged.
No import reference or alias is introduced. Neither constructor copy has an
established retail address; this repair does not assert a standalone identity.

Target evidence remains the existing 478-byte 0030B3D1..0030B5AF bounds body,
its documented WorldBuilder twin, and independently verified target layout
and calls. No donor layout, name or semantics are newly promoted to target facts.

## Paired measurement

Base checkout: c7e53a24e5 (full hash in proof.json).
Frozen index: ac77c85054, 2026-10-15 14:25; SHA-256
a56a77c2b6ade796640ae98e6b02aaa5f1b51cac34e0b31c2f115caf5cda9da3.
The published-index fetch retained this same local generation and downloaded
its compiled objects. No census, index, status or history was rewritten.

The original consumer has a version-2 reusable receipt bound to the saved
original source and object. Compiler command, dependency hashes, include-search
inventory, search roots and retry directories match the after receipt.
The repaired consumer and unchanged selected-copy provider both have current
strict reusable receipts. Separate copies of the same frozen index substitute
the two current cohort objects for each preview; only the consumer changes
between before and after.

| Unit | Before findings | After findings | Local legacy clean bytes |
| --- | ---: | ---: | ---: |
| AreaPolygonUpdateBounds.cpp | 1 | 0 | 0 -> 478 |
| PathfinderSidewaysAttack.cpp | 19 | 19 | 0 -> 0 |

This is a legacy local-preview gain of 478 existing matched bytes. There are
zero new authored C++ bytes. Strict receipts establish current compiler
evidence; self-strict placement and closed-strict closure gains are unmeasured.
No full executable-link or census gain is claimed.

The provider retains three unresolved names, five duplicate findings, six
COMDAT findings and five wrong-selected findings. All are identical in both
paired previews. Its broader pathfinder reconciliation is separate work;
the ordinary two-unit link check exits 1 for those retained findings while
reporting the consumer LINKS. The indexed constructor family contains only
these two units, so no further conflicting consumer remains in that family.

## Acceptance

- Bounded strict preparation passes the original consumer, then the current
  consumer/provider cohort: 5/5 matched rows and 20 compiler float literals,
  zero baselined or skipped references. Independent consumer build: 1/1 exact,
  seven float literals verified.
- Full COFF proof: exactly the unused constructor is removed. All 18 retained
  COMDAT bytes, extents and relocation digests are unchanged. Every retained
  nondebug section, flags, bytes, local/external relocation binding and linker
  directive compares equal. No retained relocation targets the removed body.
  Strong-definition, undefined and weak-name sets are identical.
- EH cohort: 1 EXACT, zero nonexact, baseline or missing-object cases.
- Enforced consumer data check: zero findings. Converged-data enforcement:
  two sources, eight addresses, zero second names or unjudged rows.
- Frozen-definition, canonical-class, no-new-variant, ledger and whitespace
  checks pass. Placement resweep: zero bodies, zero pins.

proof.py replays against original source/object snapshots in ignored
build/area-bounds-copy-link-20261015 and the frozen census index. proof.json
records hashes, the constructor family and complete paired findings. File and
consumer RVA claims were acquired before editing; the unchanged provider was
file-claimed for its bounded preparation. No maintainer-only runner was used.

## Donor review and freshness

Reused the existing dedicated-linking review at clean verified BFME 1 pointer
a7c38d3b2597121f178ab5190b3062478823257d and re-read repair
66b19a8e95a4add525ef808fcea088e306798e2b's verification evidence. Its
imported-forceinline emission technique applies; its Apt identities, layouts,
addresses and link gains do not. No donor source was imported.

Official master was fetched to 7afa50f4c at session start. The overdue pointer
update remains under another worker's live file:reference/open-bfme-1 claim;
comparative full verification is outstanding. The verified pointer and old
success stamp were preserved without claiming freshness.
