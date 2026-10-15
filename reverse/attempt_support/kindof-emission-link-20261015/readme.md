# KindOf inline emission link repair

Nine private ThingTemplate views emitted unused isKindOf COMDATs that the
runner index judges wrong against retail. Mark those inline definitions, and
seven forwarding Thing/Object/Drawable definitions, imported forceinline.
The existing C++ bodies stay intact. The three getTemplate COMDATs emitted
only for these forwarding bodies also disappear. None of the removed sections
has an incoming nondebug relocation. No new import or definition is emitted.
No class layout, identity, ABI, compiler flags, shared header, global, pin or
ledger row changes.

Donor technique: BFME1 commit 66b19a8e95a4add525ef808fcea088e306798e2b,
reviewed directly. It supplies the imported-forceinline emission technique;
it does not establish any BFME2 identity, offset or behavior. The target basis
is the existing source/ledger provenance and full retail byte checks. Each
unit retains its own target-specific inline body and layouts. No donor type
or offset is substituted. In particular, Team's constant-word implementation
is not promoted to a general ThingTemplate provider.

## Paired measurement

Base commit: 32045635709a1518d146ccdf42d8a7b3a4ba6ac8.
Unchanged runner index: a2839ea429, 2026-10-15 13:35; census metadata
5986a99448, 2026-10-15 04:52. context.json records the index SHA256.
The older committed link_status queue was used only for task selection.
No census, index, link status, baseline or history is rewritten.

Strict bounded preparation passed for original and repaired objects. Original
sources, objects and dependency receipts remain in the ignored directory
build/kindof-emission-link-20261015/before. The read-only proof.py there
refreshes the original and repaired cohorts independently into copies of the
same runner index. proof.json records all paired findings and hashes. All nine
repaired receipts are strictly current, without fresh-object or legacy-receipt
fallback. All 736 retained COMDAT bytes and relocation digests are identical;
the multiset of every retained nondebug section, flags, raw data, directives,
external bindings and normalized relocations is identical. EH .sxdata symbol
indices are compared by referent. Exactly 19 unused helper sections disappear,
with no incoming nondebug relocation. Data facts are identical before/after.

| Consumer | Local findings before | After |
| --- | ---: | ---: |
| AIUpdateInterfacePrivateGuardObject | 4 | 0 |
| AIGroupTightenToPosition | 4 | 1 |
| TransportContainRiders | 6 | 2 |
| SpecialPowerModuleDtor | 8 | 5 |
| AIUpdateInterfacePrivateGuardPosition | 4 | 0 |
| TeamGetControllingPlayer | 10 | 8 |
| AutoHealBehaviorPlayerScan | 4 | 0 |
| PalantirCommandInterfacePortrait | 4 | 1 |
| GameLogicInit | 92 | 90 |

The 29 removed findings are precisely the removed helpers' COMDAT, duplicate
and wrong-selected findings. All other findings are unchanged. Three consumers
now pass the local legacy link preview: guard object 115 bytes, guard position
249 bytes and AutoHeal player scan 370 bytes, totaling 734 existing nonpadding
bytes. This is a preview against the recorded index, not a full link or new
census measurement. Strict-current consumer objects are verified, but neither
self-strict placement gain nor closed-strict provider closure is measured.
New authored C++ bytes: zero.

## Acceptance and remaining blockers

- ./build.sh: 122/122 function rows, two data rows, 75 literals, ten empty
  references, seven float literals and nine named imports verified. No
  baselined, skipped or unverified references. Twenty-one renumbered funclet
  labels were re-proven from their parents' EH data; two complete STLport
  constructor folds verified against retail owners and resolved callees.
- EH before/after: all 36 rows EXACT, zero missing or baselined rows.
- Frozen definitions, class, CSV, whitespace and new-variant checks pass.
- Converged-data admission passes: eight addresses, zero second names or
  unjudged rows. Strict data enforcement exits 1 for 15 existing wrong-name
  findings (five Palantir statics, ten GameLogicInit globals/statics). The
  paired object data facts prove the exact finding set unchanged; this check
  is not claimed to pass. Details are in proof.json and acceptance.txt.
- Ordinary local link_check exits 1 because six consumers retain independent
  blockers. AIGroup lacks iterator insert; Transport lacks consume and has a
  model-condition COMDAT; SpecialPower retains five competing vtables; Team
  retains three unresolved and five other COMDAT findings; Palantir has the
  Rva00528B37Equal duplicate; GameLogicInit retains 90 findings, including
  missing subsystem providers, conflicting accessors and STL/layout helpers.
  Complete names are in proof.json and link-after.txt.
- place_bodies resweep: zero bodies, zero pins.

The indexed ThingTemplate::isKindOf family has sixteen emitters. Nine local
private definitions are repaired here. The other seven are inventoried in
peer-inventory.json: MapUtil, Player, Thing, ParkingPlace, Selection and
ScoreKeeper involve shared definitions or separate class/provider work;
W3DModelDraw also has another worker's live file claim. Their index entries
are leads, not current provider verification. No peer is silently treated as
fixed. No new class contract is inferred from a suppressed helper copy.

The verified BFME1 gitlink/checkout remains
a7c38d3b2597121f178ab5190b3062478823257d. Official master was fetched and is
464e5b60 at this pass. Another worker holds file:reference/open-bfme-1; this
seat preserved the verified inputs and did not write a freshness-success
stamp. The pending reference update needs its own comparative full gate.
No full link cycle, census rebuild, nightly or boot operation was run.
