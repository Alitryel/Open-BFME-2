# Stealth Object-wrapper emission repair

Base BFME2 revision: 2a2e46fcd800d6870ab53a80885918742c33d263.
Fixed local index: a2839ea429, 2026-10-15 13:35 UTC, derived from census
5986a99448, 2026-10-15 04:52 UTC. index-meta.json records its SHA256.
The census, index, status and history are unchanged.

StealthUpdateLogic.cpp emitted unused standalone copies of Object::getStealth
(5 bytes, 0a6d8ae0eddb) and Object::getWeaponInWeaponSlot
(11 bytes, 95f47f5cf2fa). Both differ from their first census copies and
lose selection. Apply the established imported-forceinline spelling to these
two local wrapper definitions. The existing inline forwarding and weapon-set
address calculation are preserved; no import reference or undefined name is
introduced. Headers, compiler flags, layouts, data identities, pins, ledger
rows and extents remain unchanged.

The original target identities and layouts remain grounded in the existing
whole retail StealthUpdate bodies, constructor/xfer, parse table and ledger
provenance. For example rva00373F59 at 0x00373F59 is the complete 856-byte
stealth-rule chain with five weapon queries. getStealth callers include
rva00373D28 at 0x00373D28 and disguiseAsObject at 0x00373DF0. This repair
establishes no new standalone wrapper address and does not assert that the
census winners are the correct BFME2 layouts. ZH semantics remain donor facts;
complete retail verification establishes the preserved target operations.

## Acceptance and improvement

- Bounded link_check.py --prepare-current before and after: 20/20 whole
  retail rows exact, with strict reusable current-input compiler receipts.
  Independent ./build.sh: 20/20; seven string and 15 float literals, zero
  skipped or baselined references, zero named imports.
- EH verification: 5/5 EXACT before and after, no baseline or missing object.
- Paired proof refreshes each object independently into a copy of the same
  fixed index. Findings drop 9 -> 7, removing exactly the two wrapper COMDAT
  conflicts. Every other finding and remaining provider selection is unchanged.
- Exactly those two outlines disappear. All 95 retained COMDAT bodies,
  extents and relocation digests are equal. Every retained nondebug section
  preserves bytes, flags, extent, definitions and symbolic relocations
  (SafeSEH indices normalized by symbol). External/weak bindings and data
  facts are equal. No retained nondebug relocation targets a removed helper.
- Class, declared-definition, new-variant, CSV and whitespace checks pass.
  Converged data enforcement checks eight addresses: no second names or
  unjudged rows. Optional data --enforce returns 1 both before and after for
  the same two unbaselined compiler static-guard wrong-name findings at
  0x00A01F00 and 0x00A01F08. The outputs compare exactly; this independent
  data-owner debt is preserved, not waived or repaired.
- Placement resweep: zero bodies, zero pins.

The unit owns 5,722 existing nonpadding authored bytes but still does not
link. LEGACY local LINKED remains 0 -> 0 bytes; new authored C++ bytes are zero.
Strict compiler currency and scoped byte verification are established.
Closed-strict closure, placed self-strict gains and actual-link gains are
unmeasured. No census build/measure/history, full link cycle, nightly, boot,
scheduler or shadow publisher was run.

Five unresolved names remain: Rva002390CB assignment, BFMEThingFactory::newDrawable,
CreateAHeroManager::rva002197A6, Rva0028F326Owner::rva0028F326 and
Rva00439E0C::rva00439E0C. Selected-provider findings for
StealthUpdate::getStealthLevel and isDisguised also remain. These need separate
provider/home-unit evidence and repairs; none was retried here.

Cohort review: the fixed index's eight getStealth copies and five
getWeaponInWeaponSlot copies have only this unit as a losing consumer.
Other copies, winning-provider verdicts and consumer references remain
unchanged; object-proof.json records them. No same-cause losing peer remains
in that measurement, so no shared header or unrelated file was edited.

proof.py reproduces the paired comparison from the repository root using
ignored source/object/strict-receipt snapshots in
build/stealth-object-inline-link-20261015/before and the unchanged recorded
index. input-hashes.json records input identities. Stored JSON is paired local
evidence, not a closed-strict receipt. To reproduce after scratch cleanup,
compile the parent and repaired sources with the same verified dependencies,
save the parent's objects/receipts under that path and run proof.py.

## Donor review and freshness

Reviewed BFME1 repair 66b19a8e95a4add525ef808fcea088e306798e2b, its patch
and verification message: imported forceinline removes unused allocation
copies without new imports. The emission mechanism applies; its Apt names,
addresses, layouts and linked-byte gains do not transfer. No donor code was
imported and no unchanged broad donor scan was repeated.

Verified clean BFME1 checkout/gitlink remains
a7c38d3b2597121f178ab5190b3062478823257d. Official master fetched during
this session is 464e5b60. Another worker's live file:reference/open-bfme-1
claim (codex-6bc6-20261008) blocks the due comparative update. Preserve
verified inputs and write no freshness-success stamp. Comparative full byte
verification and affected donor refresh remain required before advancing it.
No decoder source was read.

Discovery: repair_queue.py link, link_rank.py help/top/near/file and the
current local object preview; published-index fetch confirmed the same index.
The file claim preceded changes. No per-row data-back artifact or manufactured
ranking was used.
