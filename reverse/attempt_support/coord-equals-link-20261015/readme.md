# Coord3D equality and FiringTracker provider repair

BFME2 base: `f3940ec24ccf4e8e24d10d70770c9abfd7935684`.

`coord3d.cpp` emitted an exclusive Coord3D::equals definition alongside the
inline COMDAT already emitted by `FiringTrackerXfer.cpp`. Their complete 57-byte
bodies and relocation digests are identical and pass the retail gate. Remove
the unused exclusive definition and move its existing ledger row to the inline
emitter. The two pre-existing folded equality rows stay in coord3d.cpp; no name,
pin, extent or alias is added.

The Xfer unit also conflicted with the older Zero Hour FiringTracker::update
definition in `FiringTracker.cpp`. Remove that superseded 114-byte definition
and its present-unmatched marker. The already matched BFME2 implementation at
0x004DED3B remains the provider, including its movement-triggered cooldown.
Its 151-byte body and all retained callers and vtable relocations are unchanged.

## Paired measurement

The frozen local index measures commit `ac77c85054`, 2026-10-15 14:25, SHA256
`a56a77c2b6ade796640ae98e6b02aaa5f1b51cac34e0b31c2f115caf5cda9da3`.
Before and after objects for all three units are refreshed independently into
copies of that same index. Strict reusable compilation receipts establish
object currency. The index and committed census files are unchanged.

All 86 retained coord COMDATs, 582 retained Xfer COMDATs and 655 retained old
tracker COMDATs have identical bytes, sizes and relocation digests. Every other
normalized nondebug section and linker directive is identical. The only symbol
changes are removal of the exclusive equals definition, changing the obsolete
update definition to an external reference, and dropping its reloadAllAmmo
reference. Data facts are identical with zero findings.

| Unit | Local findings before | After | Legacy predicted linked bytes |
| --- | ---: | ---: | ---: |
| coord3d.cpp | 1 | 0 | 0 -> 2265 |
| FiringTrackerXfer.cpp | 3 | 0 | 0 -> 1543 |
| FiringTracker.cpp | 13 | 10 | 0 -> 0 |

Total local legacy prediction: **0 -> 3808 existing bytes**. New authored unique
C++ bytes: **0**. No self-strict or closed-strict placement gain is claimed.
No full census, link cycle, nightly or boot runner was started.

`link_check.py` must receive all three changed units together so the obsolete
provider is refreshed in memory. A check of only coord and Xfer still sees the
old census definition of update and reports the old duplicate; that is not the
combined result. The final three-unit command exits 1 because the old tracker
still has independent blockers, while both repaired consumers report LINKS.

## Acceptance and reproduction

- Before/after explicit `link_check.py --prepare-current` gates all 80 ledger
  rows (77 across coord/Xfer, 3 in old tracker), with strict reusable receipts.
  An explicit build of coord/Xfer also passes 77/77 rows, including three string
  literals and ten compiler floats. No named-import discrepancies.
- EH: EXACT 2, no exceptions, baseline allowances or missing objects.
- Enforced data: zero findings; convergence: eight addresses, no second names
  or unjudged rows. New-variant check passes all three units.
- Class gate, declared-definition check, CSV check and whitespace check pass.
  Placement rescans return zero bodies and zero pins in all affected units.

`proof.json` includes the paired findings, strict currency, object hashes,
whole-body equality twin and data facts. `proof.py` runs from the repo root
using ignored snapshots in `build/coord-equals-link-20261015/{0,1,2}` and the
frozen index. It asserts that only the two identified conflicts disappear.
`acceptance.txt`, `eh.json` and `link-after.txt` preserve command evidence.
All three files and both affected RVAs were claimed before editing.

## Donor review and remaining blockers

BFME1 repair `d5043e1658bdf46d39281a2e975e9e0145221555` moves eleven Coord3D
rows away from exclusive definitions to retail-identical inline emitters; this
directly supplies the repair pattern. Repair
`d003077f0b7ce97622adb7a53f1fe76653433c5c` supplies the related provider-reuse
method. No donor code, target identity or layout was imported.

Official BFME1 master was fetched at `95eeb3bef370a7cd730b0ad5f228c317c8756e72`.
The clean verified checkout/gitlink stays at
`a7c38d3b2597121f178ab5190b3062478823257d`. The overdue reference update is
foreign-claimed; its old-input full baseline was previously interrupted with
2806 of 2982 stale TUs left after 21 minutes. No unchanged multi-hour retry,
pointer advance or freshness success stamp was made.

The old tracker still has eight unresolved AudioEventRTS, disabled-mask,
Object model-condition and module CRC names, plus nonretail/selected STLport
`_S_maskbit<3>` findings. These require independent repairs. Broader placement
measurement and the reference update remain outstanding.
