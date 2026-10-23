# Find/swap helper ownership repair

At source base 3179344836, both Rva005FA8F5Find.cpp and Rva005FA98CSwap.cpp
own the same exact 39-byte key search. The caller must see its definition
for MSVC register-use analysis (ECX survives both calls). Rehome the existing
row to Rva005FA98CSwap.cpp through add_match --replace-existing and delete
the redundant standalone definition. No algorithm, layout, flags, headers,
pins, aliases or gate rules change. Names remain address-derived.

Target evidence: the 0x005FA8F5..0x005FA91C body searches stride-eight entries
at +0x34 using signed count +0x4C, returning the matching or one-past-end entry.
The swap calls it at 0x005FA9AE and 0x005FA9B8. The surviving source already
carried this body and caller relationship; this repair asserts no donor name.

Measurement uses runner index 825b86983f (2026-10-15 12:37; original census
5986a99448). proof.json records the index hash, complete paired findings,
strict object/receipt hashes and assertions. Both current objects before
repair have only the helper duplicate. Refreshing the surviving object and
retiring the removed owner with link_check.forget, exactly as --update-index
retires vanished ledger owners, clears every finding. The prescribed local
link_check CLI, run against an isolated copy of that index, reports LINKS:
0 -> 123 existing retail bytes. Shared index and census/status are unchanged.

Acceptance: bounded --prepare-current and ./build.sh pass both retail rows
before and after. Normalized non-debug COFF sections, bytes, flags, extents,
relocations, data, directives, strong/undefined/weak bindings and COMDAT
verdicts in the home are unchanged. Every removed external COMDAT survives
identically in the home. The proof script is retained in scratch at
build/find-swap-home-link-20261015/proof.py, with before snapshots and isolated
preview-index.pkl. EH has zero applicable rows; declarations, canonical
classes, CSV, shadow data and enforced converged data pass. Placement resweep
finds zero bodies/pins. No extra matched or authored C++ bytes are claimed.
This is strict self currency and a legacy local prediction; closed-strict
closure, a fresh census, link.exe placement and data-back gains are unmeasured.

BFME1 donor review: clean verified gitlink a7c38d3b2597121f178ab5190b3062478823257d
retained. Reviewed de59a7e9f891b3ed2d4221d151ca881f4b75a583 and
4966496c5ae401ec877a044e1ae6dd04f9d9f65c, including their byte/link acceptance.
Their convergence and emission principles apply; target source and ABI are
independently established above, with no donor import. Official master fetched
to 3a5eb7a27d25a9192ca16872ae5446a5cde592f1. Freshness update remains held by
another worker's live file:reference/open-bfme-1 claim and the outstanding
old/new full-byte comparison. No freshness success stamp was written.

No census build/measure/history, full link cycle, nightly, boot or shadow
publisher runner was invoked.
