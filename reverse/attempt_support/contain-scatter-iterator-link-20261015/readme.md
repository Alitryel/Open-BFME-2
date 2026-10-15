# Containment and scatter iterator ownership, 2026-10-15

At BFME2 base `8736b680cc`, keep typed list-iterator inequality local in
GarrisonContainUpdate.cpp and AIGroupScatter.cpp. Both use the existing
InGameUI.cpp / PlayerTemplate.cpp repair: compare STLport's same node pointers
without emitting an incompatible external base-iterator comparison. Game
bodies, ABI, layouts, compiler settings, globals and ledger rows are unchanged.

## Controlled result

The genuine baseline and repaired objects have strict reusable compiler
receipts and pass ordinary byte gates. Each phase refreshes a separate
in-memory copy of the same runner index: update commit `19a2565407`, census
commit `5986a99448`. context.json records the index SHA-256 and full source
base. No census, index or status was rewritten.

Local legacy preview findings change **6 -> 5 in each consumer**, across
865 existing authored bytes as counted by link_check.py (0xCC excluded).
The removed finding in both is `_List_iterator_base::operator!=`, whose
external body is not retail's. LINKED stays **0 -> 0 bytes**. New authored
matched bytes are zero. This establishes no self-strict placement,
closed-strict gain or full executable linkage.

object-proof.json proves all 24 retained Garrison COMDATs and all 42 retained
scatter COMDATs retain identical bytes and relocation digests. In each object,
one unreferenced 18-byte external comparison is replaced by one unreferenced
12-byte static comparison. No nondebug relocation refers to those helpers;
all other normalized sections, relocations, external bindings and directives
are unchanged. No provider or caller retargeting occurs. The shared external
provider is left alone; the two consumers stop supplying rejected copies.

identity-proof.json independently checks saved genuine baseline objects and
repaired objects: all 12 existing identity-shadow findings are identical.
These include existing class-view divergence, duplicate definitions and the
unowned removeInvalidObjectsFromGarrisonPoints binding. This repair does not
resolve those findings or infer new game identities or layouts.

## Acceptance

- Strict preparation before and after: 4/4 ledger rows byte-match. The
  parent-proven scatter funclet is rediscovered after label renumbering.
- Explicit ./build.sh on both changed consumers: 4/4 matched; string, float
  and import-reference checks pass.
- EH verification: 2/2 EXACT; zero baseline, missing or inexact rows.
- Local link check: five remaining findings in each unit (expected exit 1).
  Paired link-proof.py proves exactly one finding removed from each.
- New-COMDAT-variant check, data enforce (zero findings), converged-data check
  (eight addresses, zero second names/unjudged rows), class gate, declared
  definitions and whitespace check pass.
- place_bodies.py: zero additional bodies or pins.
- Session-start check_csv: OK, 91,217 function rows.

Proof scripts run from the repository root using saved genuine binary objects
and source snapshots in build/contain-scatter-iterator-link-20261015. Only the
JSON proofs and text verification evidence are committed.

## Remaining blockers and reference review

Garrison still needs the opaque containment-list allocator/proxy deallocation,
clear and destructor providers reconciled, plus the selected
removeInvalidObjectsFromGarrisonPoints definition. Scatter still needs
SimpleObjectIterator::insert, duplicate getMinMaxAndCenter ownership, and
aiMoveToPosition / isKindOf / getAIUpdateInterface COMDAT reconciliation.
These require separate supported repairs; no unchanged blocked body was retried.
The audio Rva000A7E9E lead was inspected but not edited: the existing funclet
label false-reject verdict remains unresolved.

Started with repair_queue.py link and link_rank.py, then fetched the published
object store (22,455 objects; newer runner index retained). Reviewed BFME1
linking repairs `63e68aaa567` and `de59a7e9f89` and the prior recorded scan:
supported provider/helper ownership is applicable; no donor addresses, ABI,
layouts or implementations are imported. The directly applicable local-helper
recipe already exists in BFME2. Official BFME1 master fetched to
`1c4d808dd`; the clean verified checkout remains at the committed
`a7c38d3b2597121f178ab5190b3062478823257d`. Another worker owns
file:reference/open-bfme-1. Its overdue freshness update remains blocked on
the recorded dependency inputs / stalled old-input MSVC baseline; no pointer
advance, unchanged full retry or freshness success marker was made.

Maintainer-only full link cycles, nightlies and boot operations were not run.
