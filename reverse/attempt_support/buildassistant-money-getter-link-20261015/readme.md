# BuildAssistant money getter emission repair

BuildAssistant.cpp now marks its existing private Player::getMoney definition
imported and forceinline, matching StatsCollector.cpp. This preserves the
existing inline address-of-member operation at +0x90 while removing its unused
seven-byte standalone COMDAT (8d8190000000c3). There is no new import reference,
pin, alias, flag, class layout or ledger row. The two callers are the complete
475-byte canMakeUnit at 0x00391B08 and 575-byte update at 0x003922BF. Their existing
target-derived layouts and ZH semantic identities are unchanged.

The paired proof refreshes before and after objects independently into copies
of the unchanged runner index measuring 28269d8e8d, 2026-10-15 09:31 UTC.
measurement.json records base checkout and index hash; proof.json records source,
object and strict receipt hashes and all findings. All 194 retained COMDATs
retain complete bytes, extents and relocation digests. All other nondebug
sections and symbolic relocation destinations, external bindings, weak externals
and linker directives are identical. Local labels compare by target contents,
flags, size and offset; SafeSEH indices compare by symbol name. No retained
relocation references the removed getter. Saved original source/object/receipt
and the executable comparison remain in ignored
build/buildassistant-money-getter-link-20261015.

The same-index legacy local preview removes exactly one COMDAT finding (six
findings become five), with zero added findings. BuildAssistant still does not
link. Existing unresolved float g_00E027C4, ObjectSellInfo scalar destructor
COMDAT/selected conflicts, and selected definitions of Player::onStructureCreated
and Player::onStructureConstructionComplete remain unchanged. New authored C++
bytes and newly linked bytes are both zero. Strict reusable receipts establish
self-strict byte verification before and after; closed-strict closure and a
placed self-strict gain are not measured. No census, index, link_status or
measurement history was changed.

The same-cause census cohort contains only this unit and StatsCollector.cpp;
StatsCollector already uses the imported-forceinline definition. No other
consumer is changed. The external bindings and all caller relocations remain
identical, so no provider alteration is required for this emission-only repair.

Donor review: BFME 1 repair 66b19a8e95a4add525ef808fcea088e306798e2b
was inspected with its patch and verification message. It applies imported
forceinline to suppress unused Apt allocator copies without changing callers
or adding imports. The emitter technique is applicable; its Apt identities,
ABI and layout are inapplicable. The local StatsCollector sibling is the
same-accessor precedent. Existing target evidence, rather than donor layout,
supplies this Player money member and the two call relationships.

BFME 1 master was fetched as d891c34e379868ebb0aa92a47aa7b798f9d2d1ac.
The clean checkout and committed gitlink remain the previously retained
a7c38d3b2597121f178ab5190b3062478823257d. A live foreign claim on
file:reference/open-bfme-1 (codex-6bc6-20261008) blocks the pointer update;
comparative full verification remains outstanding and no successful freshness
stamp was written.

Acceptance:

- Bounded prepare-current before and after: current strict reusable receipts,
  34/34 complete matched rows, two strings and 23 float literals verified,
  zero named import references.
- ./build.sh: 34/34 exact; five renamed funclets verified through parent EH data.
- EH verifier: 7/7 EXACT, no baseline debt or missing objects.
- Paired complete COFF proof: only the unused getter disappears; all retained
  sections and relocations unchanged; local findings six to five.
- Ordinary link_check: expected exit 1, five remaining findings; new-variants passes.
- Frozen-file and class gates pass. Enforced data check: zero findings;
  converged check: eight addresses, zero second names or unjudged rows.
- place_bodies: zero bodies and zero pins. check_csv and diff whitespace pass.

An initial read-only queue check prepared ParticleSystemDebugDisplayBody.cpp:
it already LINKS 1007 existing nonpadding bytes and was left untouched; both
claims were released. Several other getter queue entries were also already
repaired in tracked sources. No still-deferred reconstruction was retried.
No maintainer-only verification runner was started.
