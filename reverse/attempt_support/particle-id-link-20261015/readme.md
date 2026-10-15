# Remove incidental particle ID getter emitters

At BFME 2 source revision 4b7e7091c4dd659f6f123ec7f25cb75a1a178344,
four recovered particle-system consumers emitted an unused seven-byte
`ParticleSystem::getSystemID` COMDAT reading +0xA8. The census selected a
different copy with no proven retail address. Replace the inline getter with
direct access to each existing target view's ID field. LaserUpdateInitLaser
now spells its previous +0xA8 cast as the same field layout. BoneFXUpdateUpdate
keeps the ID in a local before passing it to vector::push_back: passing the
field by reference changes the native value-copy behavior and fails the gate.

Target evidence is independent of the getter's source name. Retail directly
reads +0xA8 at RVAs 004BE391 (ActiveBody), 004BA151 (TransitionDamageFX),
00487BEF (BoneFXUpdate), and 0036370E/00363765 (LaserUpdate). All five loads
are `8b80a8000000`. target-reads.json identifies their complete owner rows.
The existing source supplies the field/type names; neither the first census
copy nor this repair establishes a retail address for the standalone getter.
No pin, shared header, function row, baseline or compiler flag changes.

## Acceptance and scope

The unchanged census index measures 28269d8e8d at 2026-10-15 09:31 UTC;
SHA256 6128e4df8c49e7783f07dcf447831cfd3c9850b9bf46249d968878411907b551.
Before and after objects for all four peers were substituted into that same
index. Four getter conflicts become zero. Ordinary local link_check changes
from 0/4 to 3/4 clean units, predicting **0 -> 7,947 existing authored bytes**:
ActiveBody 5,556; TransitionDamageFXParse 1,645; LaserUpdateInitLaser 746.
This excludes padding; the discovery ranking's 8,360 is a different count.
BoneFXUpdateUpdate's 811 bytes remain held by the unchanged STLport node
allocator allocate/deallocate COMDAT conflicts. No allocator repair is claimed.

- Bounded strict-current preparation before and after: 52/52 matched rows,
  four reusable compiler receipts. An independent ./build.sh also passes
  52/52, with 20 string literals plus six empty refs, 20 compiler float
  literals, and four named imports verified; zero skipped/baselined literals.
- EH verification: ten rows EXACT, no baseline/missing/nonexact results.
- Object proof: all 224 retained external COMDATs have identical raw bodies,
  extents and byte/relocation digests. Exactly one seven-byte getter is removed
  from each object. Strong, undefined and weak symbol lists are unchanged.
  Both source/object hashes and before/after link findings are recorded.
- Frozen-file, class, converged-data (eight addresses, no second names or
  unjudged rows), shadow data (zero findings) and whitespace checks pass.
- A read-only place_bodies rescan of all four sources finds zero bodies/pins.
  No unsupported incidental recovery is added.

This is a legacy local link preview, not self-strict placed linkage or a
closed-strict gain. The census's two untouched getter copies remain recorded
in object-proof.json; their current objects are not locally available, so no
fresh provider or closure validation is claimed. The changed consumers no
longer define or reference that getter. A maintainer's full link measurement
remains outstanding. No full link cycle, census build/measure/history, nightly,
boot or scheduler operation was run. New authored C++ bytes: zero.

## Existing shadow identity finding

The normal commit hook reports the BoneFX main row's vector<ParticleSystemID>
`push_back` binding at 002E01C6 as wrong/unknown against the current identity
universe. identity-debt.json scans that same row with both the saved-before
and current-after objects in the same universe: the finding, relocation offset
131, symbol, target and classification are identical. This is pre-existing
binding debt, separate from the getter conflict removed here. The repair does
not certify the vector helper or claim BoneFX closed-strict linkage. No
identity baseline entry was added and no gate was weakened.

## Donor review and freshness

Reviewed BFME 1 repair d2e21369067f2f2c762c1c7ec2792c75f1ecf53d,
including its verification notes and seven source edits. Its principle of
removing surplus competing COMDAT emitters applies. Its constructor wrapper,
alias scaffold, pin and addresses are inapplicable and were not imported.
The previously established local ScriptEngine direct-field repair supplies
an additional supported pattern; target bytes establish each application here.

Official BFME 1 master was fetched at cef1b705; verified checkout/gitlink
stays a7c38d3b2597121f178ab5190b3062478823257d. The live foreign
file:reference/open-bfme-1 claim (codex-6bc6-20261008) prevents this seat
advancing it. The earlier full comparison also recorded 2,982 stale units
and an incomplete old-input baseline. No donor input was substituted and
no freshness-success stamp was written. The pointer owner's comparative
full-byte verification and affected donor refresh remain outstanding.

Discovery used repair_queue.py link, link_rank.py help/top/near and the
published-index fetch (the identical local index was retained). All four
files were claimed before editing. Scratch original sources/objects and
proof.py remain in ignored build/particle-id-link-20261015. Committed evidence
contains the relevant results without claiming a census publication.
