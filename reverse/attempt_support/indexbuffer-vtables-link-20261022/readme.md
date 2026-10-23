The first indexed DX8IndexBufferClass and SortingIndexBufferClass tables came
from FamilyDeletingDtorsO2.cpp, whose private views declared only their virtual
destructors. The full index-buffer unit inherits RefCountClass::Delete_This in
slot zero and puts the deleting destructor in slot one. The first provider now
has that same inheritance and an inline-only count-initializing constructor.
No shared header, pin, compiler flag or ledger address changes.

Target evidence: constructors at RVA 00138980 and 00138B20 install VA 00BD2EF4
and 00BD2EFC. Retail's two-word tables are [0046CE57,00539200] and
[0046CE57,00539220]. The second entries are this provider's rowed deleting
destructors. The inherited slot is also present in the committed BFME1
37c3022de1ab944c7ffe536440d637dc8199091c refcount header. Target slots establish
the ordering; donor inheritance supplies the existing class relationship.
The constructor's count-at-four initialization follows the existing target
RefCountClass view used by DX8RendererAddMesh, not a new layout inference.

Paired local legacy previews use the same published census/index 08160bc2c9
(2026-10-22 17:08): FamilyDeletingDtorsO2 stays LINKS 251 -> 251 authored bytes;
dx8indexbuffer goes from two table COMDAT blockers and 0 bytes to LINKS 2391.
Net improvement is 2391 existing authored retail bytes. A census-wide lookup
finds no other table loser for this provider's remaining three table names.
These previews are not closed-strict placement or runtime evidence.

Acceptance: ./build.sh and link_check.py --prepare-current pass all 43 rows
across the provider and consumer, including the five parent-bound unwind rows.
The strict reusable receipts establish current byte-verified inputs; closure
was not run. Frozen-file check, class gate, CSV integrity and diff whitespace
checks pass. Enforced data checking finds only two existing baseline entries;
converged-data checking finds no second names. No census, full link cycle,
nightly, boot runner or index/status update was performed.

Other triage in this batch: the skin renderer's 1618B unit needs the kept
DynamicVectorClass<Vector3> view in FXShaderRendererSkin.cpp reconciled with
retail's six slots (004F28A7/004F1C16/004F0CF9/004F1C0D/004F1CA6/004F1CA1).
Several slot owners have other template names, so declaration-only suppression
would conceal the prerequisite. No source was changed; claims were released.
AssetManagerImplRefresh's 3252B unit has conflicting pointer-tree constructor
copies; declaration-only and inline-only bodies disturb the matched parent.
The original was restored and verifies 2/2. Both blockers are recorded through
re_log.py. The farm-initializer rows were held by another worker and untouched.
