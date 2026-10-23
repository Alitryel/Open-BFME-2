Selection-message getter emission repair, 2026-10-15

At BFME2 6cfdafa3a7, SelectionXlatTranslateGameMessage.cpp emits an unused
seven-byte Object::getContainedBy COMDAT that differs from the first copy
selected by the frozen census. Apply dllimport to its existing inline view,
keeping its inline implementation and suppressing the external copy. No
function identity, layout, compiler setting, ledger, pin or data name changes.
The embedded parent remains present-unmatched; its bytes do not change and
this change makes no claim to recover it. Only the existing 86-byte helper is
rowed. The source's original donor and target provenance remains intact.

This continues the supported cause from tunnel-guard-getter-link-20261015.
The frozen index's ten nonconst getter definers were reviewed: four modern
views are already repaired; this selection consumer has a separate seven-byte
variant; five old engine views agree with the first copy and are outside this
conflicting-consumer repair. No other definers are counted as repaired.

BFME1 c1315665a1b22beb7e6d9279548fe5b1c26ed1f9 was reviewed. Its suppression
of unused DamageInfo constructor copies supplies the mechanism, not target
layout evidence. Direct target object comparison supports this application.
Official BFME1 master was fetched as 86d49b09744d9dfb7896d0d1b6e621d3536f30d2.
The verified gitlink/clean checkout remains a7c38d3b2597121f178ab5190b3062478823257d.
Another worker holds file:reference/open-bfme-1; the previously recorded
old/new full-verification prerequisite with stale baseline inputs is unresolved.
No donor inputs, pointer or successful freshness stamp are changed.

context.json pins the measurement hash and commits. The runner index measures
19a2565407 at 2026-10-15 09:33, derived from census 5986a99448 at 04:52.
The committed link-status queue measures 28269d8e8d and is not substituted for
the index. Fetch-index preserved this newer local index and obtained available
published objects. No census, status, history or index is rewritten.

proof.py refreshes only this owned consumer into independent in-memory copies
of that same index. Findings fall 38 -> 37: exactly the getter conflict is
removed; all other findings are identical. Legacy LINKED stays 0 -> 0. The
affected helper contains 86 existing nonpadding bytes; authored growth is zero.
Strict before/after prepare-current verifies 1/1 and establishes current
receipts for the consumer. External provider closure remains legacy; no
closed-strict or link.exe-placement improvement is claimed.

All 648 retained COMDATs have identical bytes and sizes. The stronger normalized
comparison proves all retained nondebug sections, flags, definitions, symbolic
relocations, EH data and directives identical. The removed getter has no
incoming nondebug relocation. Data bindings and zero data findings are identical.
No new COMDAT variants are admitted. The selected comparison provider remains
unchanged; the repair removes this consumer's conflicting emission only.
identity-proof.py also compares both objects through the identity gate: its
seven existing shadow findings remain seven, with zero new findings and no
baseline edits.

The ordinary byte gate also passes 1/1. EH has zero rowed graphs and zero
missing objects; retained unrowed EH sections are covered by the object proof.
Class, declared-definition, variant, enforced data and ledger checks pass.
Converged-data checking finds zero second names at eight addresses.
The ordinary local link check still exits 1 for the other 37 findings: four
unresolved dependencies, twenty-nine conflicting COMDATs and four selected-provider
findings (see local-link.txt/object-proof.json for the exact partition).
Full placement and provider reconciliation remain follow-up work.
The required placement resweep reports zero additional bodies and zero pins.

Run proof.py from the repo root. Original source, object and dependency receipt
remain under ignored build/selection-getter-link-20261015/before; binary
snapshots are not committed. object-proof.json records object hashes and the
complete paired diagnostics. checks.json records acceptance commands and exits.
