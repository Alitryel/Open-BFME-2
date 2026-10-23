Current-provider legacy link_check: RenderObjCopy.cpp 0 -> 578 B and
RenderObjCtor.cpp 0 -> 262 B, a combined +840 B. The independently current
FloatUpdateUpdate.cpp matrix-copy provider remains linked at 1,035 B.
Census c2c5ac8c27. Self-strict reusable receipts only; no closed-strict or
new authored C++ coverage claimed.

Both files previously reset optimization before including refcount.h, despite
the existing comment requiring size optimization. Keep that header and the
ordinary matrix3d.h under the existing size setting. Their emitted RefCount
deleting destructor and Matrix3D constructors now agree with the kept/native
helpers, while the native RenderObj constructors and all other rows remain
exact. The original target layout, constructor semantics, donor provenance and
ABI evidence are unchanged. This also removes two redundant optimization
pragmas per file. No pins, aliases, shared headers or baselines changed.

An imported Matrix3D copy trial changed array-construction/EH shape and failed
one copy-constructor row; discarded. The ordinary header under the established
size setting preserves inlining and matches all 11 rows. The successful cause
was checked against SceneOwnership, MeshGeometryCopy and static_sort_list;
they have independent LineSeg/RefMultiList or vtable conflicts, so no zero-gain
edits were retained there.

Acceptance: 11/11 code rows exact, 2/2 EH tables EXACT, strict reusable receipts,
frozen-definition checks pass; data enforcement zero findings and converged
data zero second names/unjudged rows. Link closure and census not run or changed.

Post-publication rebase: origin/master advanced to facceef2cd, including
9338f64595 and 01d5ecf927. Those upstream changes already remove the shader
conflict and let MeshClassRender link. Their earlier measured +131/+1,427 B
are historical results, not additional gains against the new master.
Resolve the two dx8renderer comment conflicts by retaining upstream comments;
all functional changes merge without adjustment. Recheck the same nine current
providers with the six touched files first restored temporarily to origin/master
(try/finally restored the committed files), then with the combined repair.
Legacy linked totals 2,810 -> 5,657 B, net +2,847 B against current master:
material generator +878 B, category AddMesh +1,129 B, RenderObj helpers +840 B.
MeshClassRender, split shader and sort-flags provider already link in both;
dx8renderer still has independent blockers. Six owned sources pass 113/113
self-strict byte rows after rebase, with exact EH records and data acceptance.
No closed-strict gain claimed. Rebased evidence is prefixed rebased-.
