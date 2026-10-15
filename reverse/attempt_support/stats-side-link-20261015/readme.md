# StatsCollector side-field link repair

At source revision 98025021887fe1a4c752ba8babb162c3c9c664b4, the
StatsCollector unit's only current-object link blocker is its four-byte
Player::getSide COMDAT (8d4158c3). The census keeps a different copy;
there is no proven standalone retail address for this getter. Remove the
surplus method and read the existing target view's public m_side field.
Keep the controlling-player evaluation in a local before comparing the
string: nesting it in the comparison changes MSVC 7.1 argument scheduling.

Target evidence: the complete collectUnitCountStats row 00437B4D..00437BB5
calls Object::getControllingPlayer at 00437B79, then emits lea ecx,[eax+58]
at 00437B83 before StringBase<char>::compare. target-read.json records the
whole row. Existing source and ZH/BFME1 semantics supply the Player/side
names; the direct field offset and complete machine behavior are independently
established by target bytes. No standalone getter identity is asserted.

## Acceptance

The supplied runner index measures commit 28269d8e8d, 2026-10-15 09:31 UTC;
SHA256 6128e4df8c49e7783f07dcf447831cfd3c9850b9bf46249d968878411907b551.
Both original and repaired objects were substituted into that identical index
in memory. One COMDAT conflict becomes zero findings. Ordinary link_check.py
changes 0/1 to 1/1 clean, predicting 0 -> 2,172 existing authored linked bytes.
This excludes padding. The committed census status is unchanged.

- Bounded link_check.py --prepare-current before and after: 16/16 rows,
  strict reusable compiler receipts. Independent ./build.sh also passes
  16/16, 44 literals plus two empty refs and 18 named imports; none skipped
  or baselined. No compiler float literals.
- EH verify: five rows EXACT, zero nonexact/baselined/missing.
- Object comparison: exactly the four-byte getter is removed. All 85 retained
  external COMDAT bodies, extents and byte/relocation digests are identical;
  strong, undefined and weak symbol lists are identical. object-proof.json
  records hashes, paired findings and the untouched census copies.
- Frozen-definition, class, whitespace and shadow data checks pass;
  converged-data enforcement reports eight addresses, zero second names and
  zero unjudged rows. place_bodies.py finds zero additional bodies or pins.

These are strict compiler-currency and byte checks plus a legacy local link
preview. No self-strict placement, closed-strict linkage, committed census gain
or full link-cycle result is claimed. The removed getter is neither defined
nor referenced by this consumer, so this fix adds no provider dependency.
Other units' side getters remain outside this file claim; most are currently
claimed by another seat. No pin, header, baseline or flag change was made.
New authored C++ bytes: zero. Maintainer full-link measurement is outstanding.

## Donor review and freshness

Reuse the earlier dedicated linking scan and its reviewed BFME1 repair
d2e21369067f2f2c762c1c7ec2792c75f1ecf53d: removing surplus competing
inline emitters applies, while that donor's constructor identity, wrapper,
addresses and alias scaffold do not. This field access is target-proven.
Official BFME1 master was fetched and is now e27a65cb; the verified gitlink
and clean checkout remain a7c38d3b2597121f178ab5190b3062478823257d.
The live foreign file:reference/open-bfme-1 claim still prevents this seat
advancing donor inputs. Comparative full-byte verification and affected donor
refresh belong to that pointer update. No freshness stamp was written.

Discovery: repair_queue.py link, link_rank.py help/top/near, and current-object
checks; no per-row data-back artifact was used. StatsCollector was claimed
before editing. Original sources/objects and proof.py remain in ignored
build/stats-side-link-20261015. No maintainer-only runner was invoked.
