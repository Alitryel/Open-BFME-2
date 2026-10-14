# Horde kind-mask helper linkage repair

Base checkout: 71163a5824. Runner measurement index: 147cfae2cb,
2026-10-14 07:27, SHA256 in object-proof.json. The committed link_status.csv
queue measures de7bb30890 and is discovery evidence only. Neither measurement
artifact, status nor history was changed; no per-row data-back ranking was used.

Two local inline helpers in HordeContainIface11CSlots.cpp read kind words at
ThingTemplate +0x114. The first linked Object::isKindOf and
ThingTemplate::isKindOf copies read +0x108. Their complete 36B and 31B bodies
are recorded in object-proof.json; their only byte difference is that offset,
and none has relocations. Both generic helper names have no retail address.
Distinct local class views cannot share one out-of-line implementation.

Rename both helpers to hordeKindMask and their seven inline uses. This is an
implementation name for the existing local view, without asserting a retail
method name or a new canonical class layout. Native accesses in the existing
matched callers, and the complete byte gate, support keeping their +0x114
operation. No data, ABI, flags, headers, pins or ledger rows change.

Acceptance and limits:

- Before/after bounded link_check.py --prepare-current: strict reusable
  receipts, all 139 checked function rows byte-exact. The final ./build.sh
  independently passes 139/139, five literals plus two empty-string references,
  30 float constants and zero named imports, with no skipped/baselined refs.
- All 578 retained external COMDATs have identical bytes, lengths, digests and
  normalized relocation targets. Both renamed helper bodies also stay wholly
  identical. All 614 nondebug COFF sections match after helper-name
  normalization, including local code/data and relocations. Strong definitions,
  undefined names and weak bindings stay identical. Before/after object/source
  hashes and the complete retained digest list are in object-proof.json.
- The unchanged first-provider witness ObjectSetTriggerAreaFlagsForChangeInPosition.cpp
  passes its one-row byte gate and strict receipt preparation. Paired in-memory
  previews refresh only that witness and the consumer against the same index.
  Consumer findings decrease 60 -> 58 solely by losing the two conflicting
  helper copies; provider findings stay 2 -> 2. Remaining consumer findings:
  11 unresolved, one duplicate, 40 COMDAT losers and six wrong-selected names.
  Both units still fail local link closure; legacy LINKED bytes remain zero.
- EH verification: 10/10 EXACT, no baseline or missing objects. Frozen
  definitions, class gate, new-variant admission (shadow), CSV and whitespace
  checks pass. Enforced converged-data checks cover eight addresses with zero
  second names or unjudged rows. All row-level data facts compare equal; the
  same two shadow wrong-name findings at A03674/A03684 remain unchanged.
- Placement resweep reports zero bodies and zero pins. All related Object
  loser consumers in the index were reviewed: FoundationAIUpdateSlots.cpp has
  the same +0x114 view, but another worker holds its file claim; it is untouched.
  The remaining indexed Object copies agree with the first +0x108 body.

This is self-strict byte verification and a bounded paired legacy improvement
of two findings, with zero new authored bytes or linked bytes. Closed-strict
closure, actual placement and fresh census gains remain unmeasured. No
maintainer-only verification runner was started. Scratch before/after objects,
receipts, sources, full snapshots and comparison script remain under
build/link-seat-20261014c for reproduction.

Reference review: clean verified BFME 1 gitlink
 a7c38d3b2597121f178ab5190b3062478823257d. Retained prior linking review
 d2e21369067f2f2c762c1c7ec2792c75f1ecf53d and inspected reconciliation
 b955ec4852b51ec7190f1a4542a9f2864abda988. Conflicting private helper ownership
is applicable as a cause; donor layouts, aliases and pins are inapplicable.
No donor code is imported. Target byte/layout evidence is independent of that
ownership lead; the existing Horde radius repair supplies the verified local
helper-rename pattern.

Official BFME 1 fetch still finds 58ab850fd1f734e310048b2e19c1ecb7ba112a3f
 ahead of the verified pointer. Freshness remains due: the recorded old-input
comparison requires thousands of stale TUs and previously stalled the compiler.
The unchanged multi-hour prerequisite was not retried within this bounded
link seat; the checkout, committed pointer and success timestamp are preserved.

The first re_log entry misspelled the representative owner as QAE. The next
entry corrects it to the ledger's UAE virtual spelling at 46A2EC, size149.
Both describe this same linkage-only repair; no retail row was added.
