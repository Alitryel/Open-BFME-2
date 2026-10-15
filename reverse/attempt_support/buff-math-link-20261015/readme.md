WW3D inline helper emission repair, 2026-10-15

Base 6e0058e861641df6ec33d405a51bb62d1e0373d3. All three edited files were
claimed before editing and passed the frozen-definition check. The affected
consumers are listed in sources.json. No shared header, compiler flag, pin,
alias, layout, ledger extent or baseline changes.

Two consumers emit an unused Vector4(float,float,float,float) copy that differs
from retail's owner in matrix3d.cpp. W3DBuffBufferFill and MaterialCollector
also emit unused MeshModelClass::Get_Shader copies. The former copy is itself
retail-exact, but exposes the consumer to a wrong selected provider elsewhere;
the latter copy differs from retail. Mark these four existing definitions
imported forceinline without changing their bodies. Their callers already
inline the operations. No imported reference replaces a removed definition.
Existing source/ledger evidence remains the identity and layout basis; this
change establishes no new target identity from the donor or from placement.

Paired measurements use the same frozen runner index: 825b86983f, 2026-10-15
12:37, derived from census 5986a99448 at 04:52. index-meta.json records its
SHA256. Both sides replace only these three objects in memory. Findings:

| Consumer | COMDAT before/after | Selected before/after | Other findings |
| --- | --- | --- | --- |
| W3DBuffBufferFill | 2 / 1 | 1 / 0 | one unresolved, unchanged |
| W3DWaterDrawOceanWater | 5 / 4 | 4 / 4 | one duplicate, unchanged |
| MaterialCollectorCollectMaterials | 7 / 6 | 7 / 6 | six duplicates, unchanged |

The improvement is three fewer COMDAT findings and two fewer wrong-selected
findings. Legacy predicted LINKED bytes remain 0 -> 0. These are self-strict
current object receipts and a legacy local preview, not closed-strict closure,
a new census or executable placement. No linked-byte gain is claimed.

Object proof: exactly the four named helper sections disappear; all 177
retained COMDATs and every retained nondebug section have identical complete
bytes, extents, flags, external definitions and normalized symbolic relocations.
The comparison covers EH data and directives, including .sxdata symbol-index
normalization and local-symbol targets. No incoming nondebug relocation targets
a removed section. No new variant appears. The after receipts are strict-current;
the ordinary gate reuses them. object-proof.json records both sides' complete
local findings and object SHA256s; index SHA256 is unchanged after comparison.

Acceptance: before/after bounded prepare-current, independent ./build.sh on
the whole cohort: 9/9 rows, one data row, eight float literals, zero skipped
string references and zero named imports. EH 4/4 EXACT, no baseline/missing
objects. Enforced data check has zero findings; converged-data check covers
eight addresses with zero second names/unjudged rows. Declaration, class, CSV
and whitespace checks pass. Ordinary hooks must pass before publication.

Sibling sweep enumerated the index's Vector4 and Get_Shader definers, then
checked current objects. dx8renderer.cpp is claimed by another worker;
matrix3d.cpp and MeshModelGetShaderO1.cpp are the retail owners. sphereobj.cpp
uses the shared math header and reports 57 unclaimed definitions; it needs a
separate broader reconciliation. Other shader and constructor configurations
are not inferred to have the same emission behavior. No shared shim was edited.

Placement resweep reports one 22-byte RefCountPtr<TextureClass> copy at
0x001494F0 and no pins. The same mangled name is already pinned to the distinct
21-byte folded body at 0x000424BB, owned as AssetReference's copy constructor.
Placement does not reconcile these identities and call relationships. Recorded
this lead blocked in re_attempts.log; no duplicate row or pin was added.

Remaining W3DBuffBuffer blockers: unresolved DX8Wrapper::render_state and
Matrix4 assignment with two real incoming nondebug relocations. Unlike the
removed copies, that assignment cannot simply be suppressed. Ocean water still
needs HAnimComboData destructor/Matrix3D/DX8Wrapper/Light/Flush reconciliation;
MaterialCollector retains duplicate providers and refcount/material helpers.
These require separate provider, ABI and EH evidence. No failed code remains.

Donor review: verified clean checkout/gitlink remains
a7c38d3b2597121f178ab5190b3062478823257d. Reused the dedicated donor sweep
documented in ww3d-helper-link-20261015, and inspected the actual diff and
verification notes of c1315665a1b22beb7e6d9279548fe5b1c26ed1f9: its imported
forceinline DamageInfo repair applies as an emission strategy; its types,
layouts and bodies are unrelated. No donor code or dependency was imported.
Official master fetched as e082760734795655f086939df77b393f4b728375. The
pointer update remains blocked by the foreign reference/open-bfme-1 file claim
and outstanding comparative full verification. Verified inputs and the old
freshness stamp are preserved; no freshness success is claimed.

Discovery: repair_queue.py link, link_rank.py help/top/near/L and bounded
current-object checks. Several ranked getter/constructor conflicts are already
resolved in current sources and were not retried. No per-row data-back ranking
was manufactured; no maintainer-only link cycle, census build/measure/history,
nightly, boot or shadow-publisher runner was started.

Reproduction: at the base, prepare-current the three explicit sources, save
their unchanged-basename objects and sources under
build/buff-math-link-20261015/before, and capture link-before.json with all
three replacements in memory. Apply this commit and prepare-current again.
The comparison script is ignored scratch at build/buff-math-link-20261015/proof.py;
its retained-section normalization follows the committed proof in
../ww3d-helper-link-20261015/proof.py. It refuses a different index SHA256,
checks current receipts and compares the complete paired findings. Logs and
the resulting proof are committed here; sources/objects remain scratch.
