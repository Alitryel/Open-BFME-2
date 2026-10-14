# Animation pivot getter ownership repair, 2026-10-14

BFME 2 base: `30defe0407908c6f8a0603afe13d7055640e78e5`.
The supplied index measures `cb660e4d97`, 2026-10-13 04:02. The committed
link-status queue measures `67e1365aa9`, 2026-10-13 16:47; it served discovery
only. No per-row data-back artifact, census counter or index was modified.
File claims cover both checked sources, with an RVA claim for `0x00196740`.

## Change and target evidence

`HAnimComboClassGetMotion.cpp` owns the complete 27-byte retail
`HAnimComboClass::Get_Pivot_Weight_Map` at `0x00196740`.
`HAnimComboBFME1.cpp` emitted an additional inline definition. Its complete
body equals the owned provider, including extent, with zero relocations.
The exclusive provider and inline copy still collide under the local link rules.

Remove the competing inline definition and its present-unmatched marker.
In `Normalize_Weights`, call `HAnimComboData[anim_idx]->Get_Pivot_Map()` directly
so the same reference-counted data accessor remains inlined. Simply removing
the definition changed the matched normalization body; that first trial failed
its ordinary byte gate and is not the final implementation.

The accepted object has 121 retained COMDATs, all with unchanged normalized
byte/relocation digests and extents. Its only removed COMDAT is the getter;
none was added. The whole 1,173-byte normalization body is unchanged.
The dedicated provider object is byte-for-byte unchanged. No matched body,
row, pin, alias, compiler flag or header changes. Existing names and semantics
remain inherited from the prior donor recoveries; no new identity or layout
claim is made. `object-proof.json` records the object comparison.

## Donor review and freshness

Reviewed BFME 1 repair `d2e21369067f2f2c762c1c7ec2792c75f1ecf53d`:
remove TU-local constructor definitions and retain the established retail
provider. That ownership principle applies; its alias pins and constructor
implementation do not. The already ported animation getter source supplies
the actual semantic guide. The current donor's `hanim.h` and `refcount.h`
are unchanged relative to the fetched upstream revision.

The official fetch now succeeds and found master at
`4deeb580e`; retain the clean verified checkout at
`cee35b7d8ca077d7255f1c39cb69e9fd9627aa85`. A comparative full audit and pointer
publication remain outstanding: upstream differs in 1,219 files, including
the animation implementation and dependency inputs outside this bounded repair.
No update was claimed verified and the overdue success stamp is unchanged.

## Acceptance and limits

- Ordinary final gate: **23/23** animation rows exact; 15 float references
  verified. The parent EH graph binds its renumbered cleanup label normally.
- Bounded strict preparation before and after: **25/25** rows across the
  changed consumer/emitter and existing provider, with two reusable strict
  receipts. These are self-strict witnesses, not closed-strict closure.
- Same-index legacy local preview: emitter duplicates **19 -> 18** and
  selected-provider findings **34 -> 33**; its 23 COMDAT findings remain.
  The getter provider retains 2 duplicate, 2 COMDAT and 3 selected findings.
  Total findings **83 -> 81**, zero added; both preview commands return 1
  because independent blockers remain. **LINKED remains 0 -> 0**.
- Converged-data audit: two sources, eight addresses, zero second names,
  zero unjudged rows. Declared-definition, CSV and whitespace checks pass.
- Placement resweep: zero bodies and zero pins.

Authored C++ byte growth is zero. One escape-hatch annotation is removed.
The supplied index still includes older competing `hanim.cpp` definitions
removed by the previous repair, so it does not establish current getter
closure. Remaining work includes animation duplicate ownership and shared
RefCountClass/WeightInfoStruct COMDATs. No full census, link cycle, nightly
or boot runner was started. Broader linking gains require current closure
evidence and the maintainer's permitted verification runners.
