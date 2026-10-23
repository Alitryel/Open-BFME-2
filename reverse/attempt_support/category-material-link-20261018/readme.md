Paired current-provider legacy link_check: 0 -> 2,007 matched bytes.
DX8GenerateTextureCategoriesBFME2.cpp newly links 878 B and
DX8TextureCategoryAddMesh.cpp newly links 1,129 B. dx8renderer.cpp remains
blocked independently. Census c2c5ac8c27; self-strict reusable receipts only;
no closed-strict claim and no authored C++ coverage gain.

The initial two-provider measurement is before-providers.txt. The wider
before-addmesh.txt also establishes Add_Mesh's active material-getter blocker
before editing that unit. Removing duplicate donor Generate_Texture_Categories
and split-table Peek_Material definitions from dx8renderer binds their rowed
BFME2 providers. The existing accessor anchor retains rowed GapFiller material
array getter 5796A8 after its last donor caller disappears.

Native split-table Peek_Material 145560..1455A6 and the complete Add_Mesh
145620..145A68 inline descriptor material at +A8. The separately rowed
descriptor getter 2C8ECF uses +A4; a named inline method on these private
views emitted a competing +A8 out-of-line body. Direct field access preserves
the proven native inlining while eliminating that copy and redundant model
accessors. Ordinary forceinline alone still emitted the competing copy.
All existing target layout and donor provenance remain as documented in the
source and ledger. No shared headers, pins, aliases or baselines changed.

Acceptance: 92/92 code rows exact across three units with strict reusable
receipts, 7/7 EH records EXACT; frozen-definition check passes; data enforce
has one existing baselined finding, no new findings; converged-data check
has zero second names and zero unjudged rows.
