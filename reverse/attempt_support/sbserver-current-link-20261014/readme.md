# SBServer map provider verification

Verified checkout d8b5fc23cc. This records the existing source repair in
12c5f93b59a5465bbb0e9d61add9045572cadab8; this session changes no C++ and
claims no newly repaired or authored bytes. The bounded preparation creates
strict reusable compiler receipts for the map providers and checks their
shared release provider together.

## Providers and target proof

The owned files are StlportMapSBServerSubscript.cpp,
stlport_map_int_sbserver.cpp and TreeHintRefReleaseBFME2.cpp at their ledger
paths. Both map objects emit SBServer's 29-byte copy constructor at RVA
0x005E3B2D and 19-byte destructor at RVA 0x005E3B83 as select-any COMDATs
(selection 2). Each whole body and every relocation is retail-correct.
Their byte-and-relocation digests agree across the two objects. The
24-byte release provider at RVA 0x0007DEEF is also retail-correct.
objects.json records these verdicts, exact bodies, relocations, source and
object hashes, and each object's strict currency. Target proof supports
the four-byte handle operations, not a broader recovered server layout.

The inherited change makes the owner's previously exclusive copy and
destructor definitions inline/noinline. It retains the visible bodies
needed by the subscript consumer's alias analysis while permitting the
identical copies to coalesce. No source reconstruction was retried here.
The BFME 1 linking review included upstream 262d3e950 (removing a competing
particle-loader copy); it supports inspecting provider conflicts but is
not proof of these BFME 2 bodies and supplies no imported source.

## Acceptance and limits

- `link_check.py --prepare-current` on the three explicit owned files:
  23/23 matched bodies exact, source claims and string/float/import gates
  pass; three self-strict reusable receipts accepted.
- Joint ordinary `link_check.py` on those same three current objects:
  3/3 LINKS, LINKED 24 -> 1290 bytes against index cb660e4d97,
  measured 2026-10-13 04:02. The map units contribute 713 and 553 bytes;
  the release provider contributes 24. This verifies the inherited repair.
- The `--census-only` probe retains the subscript unit's two duplicate
  blockers. Its output is 2/3 LINKS, 577 bytes: the tool also overlays
  selected current providers in memory, so this is not a fresh global
  measurement or a source-change before/after experiment.
- Enforced converged-data check: three sources, eight addresses, zero
  second names and zero unjudged rows. `find_declared_unmatched.py`
  and `check_csv.py` pass.

These are self-strict provider witnesses and a legacy local preview.
Closed-strict closure and full-link gains remain unmeasured. The index
commit differs from committed link_status.csv's 67e1365aa9 measurement;
neither was edited or combined into a ranking. No census or maintainer-only
verification runner was started.

Other queue probes confirmed that part_ldr and the strafe update already
link in current local previews. ShroudManagerImpl008FBA40 retains its
unowned raster callees; FireWeaponUpdate retains its unowned secondary
interface vtable. Those unchanged blockers were not reconstructed again.
The dedicated repair queue and link_rank's U/D/L/S/A views were inspected.

The verified BFME 1 checkout/gitlink remains
cee35b7d8ca077d7255f1c39cb69e9fd9627aa85. Official upstream was fetched to
30c4ca7346c098cc8755f7fd685a11f2d01f67fb. The overdue comparative full-byte
update remains outstanding; the pointer and old freshness stamp were
preserved. No successful freshness check is claimed.

Transcripts: prepare.txt, link-before.txt, link-after.txt, data.txt.
