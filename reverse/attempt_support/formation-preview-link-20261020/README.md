Formation-preview Matrix3D emission repair, 2026-10-20

Legacy link preview gains 2,453 existing nonpadding matched bytes in
InGameUIUpdateFormationPreview.cpp; authored C++ byte growth is zero.
The complete 2,462-byte native body at 0x002A4E1F is unchanged and byte-exact.

The unit's visible axis/angle Matrix3D constructor and Transform_Vector are
needed for native inlining. Marking those two forceinline definitions dllimport
preserves their inline operations while suppressing their external COMDAT
copies, which retail proves wrong. Ten external copies disappear (the two
blockers plus their otherwise unused helper dependencies); no COMDAT is added
or changed. All retained nondebug sections, flags, bytes, definitions and
relocation referents compare equal. No import reference is introduced.

Before/after measurements replace this unit's object in the same published
retail-truth-2 index, 5366c4f808 (2026-10-20 12:21), in memory. The attached
paired JSON records object hashes, exact findings and strict byte currency.
Self-strict byte receipts pass; closed-strict gains were not measured.
No census, full link cycle, nightly or boot runner was invoked.

Acceptance: ./build.sh and link_check.py --prepare-current pass the sole
row; link_check.py changes from two nonretail helper conflicts to LINKS;
find_declared_unmatched.py and git diff --check pass. No pins, ledger,
shared headers or verifier code change.

Sweep: the other units flagged for these same helpers (Locomotor, coltest,
mesh, LineGroupClassRender) have independent unresolved/duplicate/helper
blockers, so suppression alone would not link them. BFME1 donor 92f6bbe8
was reviewed against previously checked 0dc8a26a: its recent repairs rename
callees/base types, release StringClass through Free_String, or remove a
Pathfinder constructor copy. None supplies this Matrix3D repair. This repair
uses BFME2's existing matched helper semantics and the established local
import-inline emission pattern. Current donor input freshness was already
verified by upstream commit e3779b76e8.
