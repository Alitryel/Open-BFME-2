Grid mapper helper ownership repair, 2026-10-20

Legacy paired preview: mapper.cpp links 0 -> 5,784 existing nonpadding
matched bytes (70 rows); authored C++ byte growth is zero. The new 1,166-byte
GridWSEnvMapperCalculate body is unchanged and exact. Its visible inline
calculate_uv_offset helper emitted a COMDAT alongside mapper.cpp's strong
retail owner at 0x001825E0, blocking both. Reusing the existing
bfme_grid_mapper_link header and its imported-forceinline declaration
suppresses the redundant external body without changing its inline expansion.
That header differs from bfmemapper only in this helper's declaration.

Acceptance: ./build.sh and link_check.py --prepare-current pass (71/71 rows
across consumer and owner, string/float/import checks included). Paired preview
uses index 5366c4f808, 2026-10-20 12:21, and verifies both strict byte receipts.
All retained nondebug sections, bytes, flags, definitions and relocation
referents are identical; only the duplicate helper disappears. No import
reference or new COMDAT is introduced. find_declared_unmatched.py and
git diff --check pass. Closed-strict gains were not measured. No shared
header, ledger, pin or verifier edit and no full link cycle/census.

GridWSEnv itself remains blocked on four pre-existing nonretail math helpers:
Vector4(float x4), vector constructor iterator, Matrix4(Vector4 x4), and
Transpose. The existing row-link Matrix4 view lacks this consumer's required
16-float constructor/Init, so further reconciliation needs that combined
header contract and is independent of the duplicate ownership repaired here.
Its unreferenced Get_Transform copy is diagnostic only (retail-truth-2); no
suppression was attempted. A first declaration-only attribute trial failed
C2375 before using the already-established matching scoped header.

Provenance: BFME1 92f6bbe8 recent link repairs reviewed this session as
described in formation-preview-link-20261020/README.md; this repair reuses
BFME2's existing GridTextureMapperCalculate link view and exact helper owner.
