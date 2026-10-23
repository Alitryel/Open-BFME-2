# Registry data-owner link repair

Base db73342532d1faaba71e15478b929567ac402a8c. Both consumer files were
claimed before editing. The unchanged runner index measures 147cfae2cb at
2026-10-14 07:27; its SHA256 is recorded in both object proofs. Committed
link_status.csv measures the newer de7bb30890 and was used for discovery,
not as paired acceptance evidence. No census or maintainer-only runner ran.

AIUnitBuilderNameMembership and ObjectRva0028DCC4 read the pointer at native
VA 0x00DFEEF8 under two TheSkirmishAIManager spellings. Declare and use its
existing sole matched owner, g_00DFEEF8 (Rva002A8F24 pointer), defined in
Rva005EEA20Find.cpp. data_rows.csv and data_ledger.csv independently identify
that owner. No new global, pin, alias, type, layout, row or baseline is added.
The original receiver/method identities remain unresolved as documented in
the existing source and ledger. This repair makes no new naming claim.

Acceptance:

- Before and after strict preparation passes both consumers' ordinary byte
  gates: native 0x004DFB7E, 111 bytes, and 0x0028DCC4, 284 bytes. String,
  float and import references have no skipped or baselined items. The
  unchanged provider's 166-byte body and four-byte data row pass build.sh.
- Parsed whole-object comparison preserves every nondebug section's bytes,
  flags, extent and relocations after normalizing just the changed data name.
  Each object changes exactly one DIR32 target name. Exclusive definitions
  and weak externals are unchanged. Current strict compiler receipts pass.
  Original sources, objects, receipts and comparison script remain under
  ignored build/name-membership-link; proof summaries are committed here.
- CSV, class, declared-function, whitespace and EH checks pass. EH has zero
  applicable rows and no missing objects. Placement resweep has zero bodies
  and pins. Enforced converged-data check has eight protected addresses and
  zero second names. Shadow data retains Object's independent FireLogic
  wrong-name finding at RVA 0x009FEC68; it is not caused by this repair.

Paired previews against the same index remove two unresolved references:
name membership 1 -> 0, Object registration 4 -> 3. Name membership LINKS
0 -> 110 bytes (the progress counter excludes one 0xCC byte from its 111-byte
extent); Object remains 0 -> 0 across 284 bytes. New authored C++ coverage
is zero. These are legacy local-preview results, with strict current consumer
receipts; no self-strict or closed-strict LINK gain, census gain, complete
link-cycle result or runtime result is claimed.

Object's remaining unresolved references are FireLogicSystem's TheFireLogic,
g_Va00DFE7A8, and LuaDrawableState::rva00333E5B. They require independent
ownership/callee evidence and are outside this registry repair. A source
search found these two consumers as the remaining extern declarations using
TheSkirmishAIManager; the supported cause has been swept.

Donor review used retained verified BFME 1 a7c38d3b2597121f178ab5190b3062478823257d:
fea964f8 removes allocation stand-ins in favor of canonical owners;
d003077f replaces a second function provider with the real owner's declaration;
de59a7e9 reconciles COMDAT spelling. The ownership principle applies here;
no donor body, layout or address is imported. Target data ownership and
byte/relocation checks establish the actual BFME 2 repair.

Official BFME 1 master was fetched at 0340ce41a1fe9f3a712fa978c6f5b2a67d7fd978.
The clean checkout/gitlink remains at the last verified a7c38d3b pointer:
its pending update still requires the previously blocked old/new full-gate
comparison with 2,982 stale TUs. The unchanged blocker was not retried and
no successful freshness stamp was written.
