# Weapon call providers: four consumer units

Base: 437b04e20b3c5e8a3a9458b92c2bf5353e5bc9fd. Paired runner index:
a2839ea429, 2026-10-15 13:35; underlying census 5986a99448, 04:52.
Its metadata and SHA256 are in object-proof.json. Committed link_status.csv
belongs to a different measurement (4b7e7091c4); it supplied discovery only.
No missing or mismatched data-back artifact was ranked.

BezierProjectileBehaviorFire.cpp had two unresolved declaration-only views.
Bind its native call at row+0x64 to the already recovered
WeaponTemplate::adjustTargetPositionOnVictim provider, 0x002CAB3A. The
TargetCoord spelling reproduces that provider's 12-byte hidden-result ABI;
the existing scatter caller independently uses the same spelling. Retail
calls this address with the source, victim, flag and output, and the provider
returns with RET 16. Identity/provenance remain those of the existing rows;
this repair imports no donor implementation or new target layout claim.

The second call, row+0xEE, targets 0x0049CB57. Its existing owner is
TerrainRoadType::getRoadWidth: D9 41 14 C3, fld [ecx+0x14]; ret, no
relocations. Use that provider through an explicitly documented call view.
This asserts shared code and scalar-call ABI, not a terrain identity for a
weapon. Sweep the other three current WeaponTemplate::rva0049CB57 consumers:
PorcupineFormationBodyModuleSlots, PorcupineFormationBodyModuleRva004C21A9,
and AIStatesBfmeOnExit. Replace two now-empty private WeaponTemplate class
definitions with forward declarations. No pin, alias, datum, compiler flag,
ledger row, extent, header or baseline is added or changed.

Acceptance:

- Ordinary ./build.sh passes all 31 changed-consumer rows. Bounded
  link_check --prepare-current passes all 141 rows in six explicit units
  (four consumers and both providers), with current strict reusable receipts,
  six literals/two empty strings, 167 float literals and no skipped references.
  The final forward-declaration cleanup separately passes its four rows.
- Object comparisons preserve every external code definition and every full
  section's bytes, including all matched row extents. Six REL32 names change:
  two in Bezier, one in the slots unit, two in the damage unit (one is its
  existing duplicate unowned helper), one in AI. Every rowed changed call is
  independently decoded from retail to its stated provider. Proofs and hashes
  are committed; saved objects and comparison scripts remain under ignored
  build/bezier-aim-link-20261015/.
- Paired legacy previews remove five unresolved findings across four units.
  Bezier findings fall 2 -> 0 and predicted LINKED goes 0 -> 892 bytes.
  Sibling findings fall 6 -> 5, 9 -> 8, 5 -> 4; they still predict zero LINKED
  bytes. New authored matched bytes are zero. This is strict object currency
  plus a legacy preview, not self-strict placement, closed-strict closure,
  an actual link, or a new census measurement.
- Frozen definitions, class gate, EH (no EH-bearing consumer rows), new COMDAT
  variant admission, CSV and whitespace checks pass. Enforced data check has
  one existing baselined finding and zero outside baseline; converged-data
  check has no second names or unjudged rows. Placement resweep: zero bodies
  and zero pins in all four affected units.

Limits and handoff:

The permitted current-ledger preview refuses 800 missing provider objects;
it does not start a whole-tree compile. Both providers remain independently
unlinked: target-position source has the already recorded link_debt false
positive on RNG bound 0xBC614E (12345678), and W3DRoadBuffer retains nine
unresolved names, seven COMDAT findings and the existing numeric-address
finding. No workaround or verifier edit was attempted. Porcupine units retain
distance-test/ActiveBody names and duplicate definitions; the damage unit
also retains three COMDAT findings. AI retains three unrelated unresolved
helpers and Coord3D::scale's competing body. Complete transcripts are included.
These are separate dependency/provider tasks; no gains in them are claimed.

Donor linking review: de59a7e9f8 (converged Apt COMDAT spelling), d003077f0b
(call an existing matched provider), and 2c86b2326 (native provider rebinding).
The provider-reuse principle applies; donor addresses/layouts are not proof.
The clean verified BFME1 checkout/gitlink remains
a7c38d3b2597121f178ab5190b3062478823257d. Official master was fetched at
95eeb3bef370a7cd730b0ad5f228c317c8756e72. The reference scope is foreign
claimed and the earlier old-input full baseline is still unfinished (record
53899: 2982 stale TUs, interrupted after 21 minutes with 2806 remaining).
Retain verified inputs; do not repeat that unchanged multi-hour baseline,
advance the pointer, or mark freshness successful without its comparison.
Freshness remains due and is recorded blocked. No maintainer-only runner,
census build, index publication, full link cycle or boot check was started.

Discovery also checked repair_queue link, link_rank top/near/address lanes,
and name_globals --dry-run (zero rewrites). Several ranked files already
LINKS in their current sources and receive no credit. AptCharacterByteCounts
is blocked on the existing AptLinker::Load bank; the two Apt call-adapter
units still need the unrowed 0x006EE6C0 provider. Those unchanged
reconstructions were not retried.
