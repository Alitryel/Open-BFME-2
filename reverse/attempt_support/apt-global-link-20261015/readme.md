Apt wrapper canonical-global repair

Base: 44dfb332a4 (full SHA in context.json). Frozen census: ac77c85054,
2026-10-15 14:25 UTC, SHA256 in context.json. No new census or matching
per-row data-back artifact was available or used for ranking.

The two profile callback methods in AptInvokeWrappers.cpp read retail data
0x009FE4CC at four DIR32 sites through the private TheRva00222A8BTarget name.
The data ledger identifies the existing owner as g_bfmeAptWindowManager,
with BfmeAptWindowManager pointer type, defined in Rva005832D0MapName.cpp.
BannerUIUpdate.cpp already consumes that owner through Rva00222A8BTarget casts.
Declare the existing global with its ledger type, and cast to the unchanged
local view at the four uses. No new global definition, pin, alias, layout,
compiler flag, target name or allowance is introduced. The pointer address
and four access sites are target facts; the class spelling is carried from
the established owner/data ledger, whose status remains provisional. This
repair makes no additional semantic class-identity claim.

Verified improvement

The before/after data check changes one baselined wrong-name binding to zero
findings across all three units. Exact paired data facts preserve address
0x009FE4CC and every other binding/definition. The data baseline is untouched.
Both affected retail bodies (0x00522A91, 107 bytes; 0x00521841, 110 bytes) and
the modified file were claimed before editing.

Before and after bounded strict preparation gates all 16 rows in the wrapper,
canonical provider and Banner consumer. All three have self-strict reusable
receipts. proof.py compares saved before objects in build/apt-global-link-20261015
with current objects, and independently refreshes both cohorts into the same
frozen census index. The shared index/status is unchanged. Every normalized
nondebug section, byte, extent, EH table, linker directive and symbol binding
is identical after replacing the old undefined data name by the canonical
undefined name. Exactly four DIR32 relocations retarget; no other reference
changes. Both untouched provider/consumer objects are entirely identical except
COFF timestamps. proof.json records object/receipt hashes and exact findings.

Legacy local findings are unchanged by this data repair: wrapper and provider
LINKS; Banner still has five unresolved names and a separate Rva00216332Call
duplicate. The ordinary local link_check CLI exits 1 on those independent
Banner findings. Its +941 relative to the frozen census comes from upstream's
d9f026ec39 callback ownership repair, not this global repair. Incremental
legacy-linked bytes and authored C++ bytes are both zero. Self-strict object
currency is established; no closed-strict, census-placement, executable or
runtime gain is claimed. The verified improvement is one fewer wrong-name
data binding and reuse of the existing linked datum.

Acceptance: 16/16 full byte rows, 12 literals plus two empty-string references,
one compiler float, zero named imports. EH EXACT 10; zero missing/nonexact or
baseline entries. Enforced data zero findings. Converged check: eight addresses,
zero second names or unjudged rows. Declared-definition, class, no-new-variants,
CSV and whitespace checks pass; placement resweep finds zero bodies/pins.
acceptance.txt contains command output and expected exit statuses.

This is a target-supported canonical-global repair following the existing
linking lane; no donor source/ABI is imported. The previously reviewed donor
provider-reuse repairs and unchanged freshness blocker are documented in
../apt-invoke-owner-link-20261015/readme.md. Verified BFME1 gitlink remains
a7c38d3b2597121f178ab5190b3062478823257d. Its overdue controlled old/new full
verification remains separate and no freshness stamp is written.
No full census, link cycle, nightly, boot or scheduler runner was invoked.
Remaining Banner findings require independent provider repairs.
Model: gpt-6.1-sol.
