# Sideways pathfinder converter reconciliation

At BFME 2 6fe36b553f10117070acae4699db1357f870502d, PathfinderSidewaysAttack.cpp
emitted an exclusive 115-byte Rva002E7875WorldToCell copy with digest
1b167be26562, proven wrong by retail. The existing canonical owner in
pathfinder.cpp and footprint-query sibling emit retail's 162-byte copy,
digest 3f8b7a442248. Apply their established floor/FISTP conversion and
inline COMDAT selection to the sideways copy. The helper must remain
visible: a declaration-only trial changed FindAttackPathSideways's stack
escape analysis and failed its byte gate, so it was reverted.

This is an existing RVA identity and existing target layout. No new name,
pin, row, header, flag, alias, baseline or data-global claim is introduced.
The x87 assembly is the already-proven compiler machinery from the owner
and footprint sibling. Original realToIntFloor remains unchanged for the
unrowed neighboring function; its cast behavior is preserved.

## Verification

The measured index is ac77c85054, 2026-10-15 14:25. context.json records
its SHA256. proof.py pairs the same strictly current sideways object and
unchanged strictly current footprint-query/world-line objects against that
frozen index, refreshing only these three objects in memory. It never
rewrites the census, index, link_status or measurement history.

The sideways unit loses exactly three findings: the converter's duplicate,
losing COMDAT and selected-wrong findings (22 -> 19). Footprint query loses
two findings and world-line loses one; both become clean in this local
legacy prediction: 1,443 existing matched bytes (1,380 + 63).
proof.json records their matched-byte totals. These
are self-strict witnesses and legacy predictions, with no closed-strict
closure, full census, executable placement or runtime gain claimed.
Authored C++ byte growth is zero.

- Strict preparation and normal byte gates pass eight matched rows across
  the three units, including the sideways unit's four rows. Its float gate
  verifies 13 literals; the peers verify eight floats, one string and one
  named import. No reference baselines or skipped literals are used.
- The repaired helper is proven retail by every byte and relocation.
  Of 64 pre-existing external COMDATs, 62 are unchanged. The unrowed
  rva002F83F5 retains every byte and its extent: two constant relocations
  now name __real@3dcccccd rather than a TU-local constant, with exactly
  the same four-byte content cdcccc3d. The proof normalizes only this
  explicitly verified equivalence and compares every other nondebug
  section, flag, byte, definition and symbolic relocation.
- MSVC emits a new unused 34-byte TU-local outline of worldToCellFloor,
  as it does for the canonical inline-assembly machinery. No nondebug
  relocation references it. It is not a recovered row or progress.
  Undefined symbols and weak externals are unchanged; only the repaired
  converter changes from exclusive to mergeable definition.
- Proven data-reference bindings are unchanged. The formerly unjudged
  local constant name disappears. Data enforcement has zero findings;
  converged-data checks eight addresses with no second name or unjudged
  row. EH verifies one exact row and no missing/nonexact objects.
- Frozen definitions, class gate and prescribed ranked new-variants
  admission pass. Identity shadow findings remain 10 -> 10, with no new
  findings. Placement resweep finds zero additional bodies and pins.
  CSV, whitespace and normal commit/push hooks are required too.

The proof's original object, strict receipt and source remain under ignored
build/sideways-worldtocell-link-20261015/before. Evidence creation changes
the footprint source's /I. include inventory, so the final strict preparation
is run after all evidence filenames exist. No input inventory is weakened.

## Donor review and remaining blockers

Reviewed BFME 1 repairs c1315665a1 (suppress surplus constructor copy) and
262d3e9507d68409d7cf86e730f4c75eefa58ccd (remove stale donor body beside
retail owner). Their provider-ownership principle applies, but removing this
particular definition loses compiler escape analysis; a matching inline
copy is the supported repair. No donor layouts or source are imported.

The clean verified BFME 1 gitlink remains
a7c38d3b2597121f178ab5190b3062478823257d. Official master was fetched at
95eeb3bef370a7cd730b0ad5f228c317c8756e72. Its overdue pointer/layout update
is held by another worker's file:reference/open-bfme-1 claim; no pointer
advance or successful freshness stamp is asserted.

Sideways retains 19 unrelated findings: three unresolved symbols, five
other exclusive duplicates, six losing COMDATs and five selected-wrong
dependencies, enumerated in proof.json/link.txt. Broad private Pathfinder
views and constructors remain separate repairs. The canonical pathfinder.cpp
file is claimed by another worker and was not edited. No maintainer-only
link cycle, census build/measurement, nightly or boot runner was invoked.

Model: gpt-6.1-sol.
