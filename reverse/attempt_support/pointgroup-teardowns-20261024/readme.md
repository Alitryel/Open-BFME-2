# PointGroup teardown vtable ownership, 2026-10-24

Inputs: BFME2 b8259655173099477cad3079217fd7ef5e50cd71, plus the separate VertexLoc attempt handoff commit. Committed BFME1 donor and freshly fetched official master: 32774ab03393709a7f14331ba8d98d281a55ffd9. model=gpt-6, lane=R, budget=30m.

Six already matched 59-byte teardowns at 007B7280, 007B72C0, 007B7300, 007B7340, 007B7380 and 007B7400 originally stored addresses of four distinct zero-filled 28-byte Rva*Vtable arrays. No other Code source references these anchors. The measured closure graph in ../simplevec-ulong-provider-20261022 shows the false Vector4 and float table datums alongside the real 24-byte compiler vtables, with data-content/data-back failures. The six target functions install the four VectorClass<T> vtables and clear the allocation; their existing neutral wrapper identities are retained.

Reference review: the committed donor vector.h supplies the real VectorClass destructor and ABI; the explicit qualified destructor calls Clear with the class qualifier. Related BFME1 PointGroup files do not contain an anchor repair to transfer, and no donor occurrence of the four Rva*Vtable names or corresponding PointGroup teardown handoff was found. The destructor implementation is inherited; BFME2 types, storage addresses and all six complete bodies are checked independently against target bytes. No reference pointer was changed and no new pin was added.

Repair: replace the six manual layout-view cleanups with real qualified destructor calls; remove the layout overlay and all four false table definitions. Import the actual Vector3/Vector4/VectorClass definitions through the committed donor headers. Use /G7, as the matched pointgr.cpp sibling does. Declare existing Vector3 equality and ID-by-reference specializations instead of emitting competing copies.

Both control and final normal build pass 6/6, 354 existing matched bytes, no new coverage. The plain imported-header trial also passes 6/6 but creates four COMDAT conflicts. The final /G7 and decl-only variant resolves them; normal link_check with the current consumer passes 2/2 and retains census prediction 353+10192=10545 own linked bytes, not an earned-credit measurement. The original prediction was already 353 for this TU; do not call that a +353 gain. The external-template-class experiment suppresses required inlining and fails all six bodies, so it was discarded.

find_declared_unmatched passes; data_check --enforce reports zero findings; check_csv passes (98202 function rows). The initial explicit-provider preparation is preserved in prepare.txt; the final normal gate and current-object preview follow the source adjustment. The original frozen-index before/after preview files are preserved verbatim. body-verification.json records all six final production bodies and the four canonical vtable extents from the compiled object. No protected verifier, baseline, header or ledger file was edited. No nonmatching production body remains.

The full immutable shifted-base link cycle is separately authorized and will bind the source commit; results must be recorded before claiming earned byte credit. The unresolved VertexLoc ownership problem is separately banked in ../vertexloc-ownership-20261024 and is not claimed fixed here.

Source repair elapsed: 7.9 minutes for this homogeneous six-body batch (verification-run time is separate).

## Native section placement

Before trusting the full cycle, the old receipt revealed that all six manual wrappers were unplaced: compiled .text versus retail .text$yd. The first new snapshot run (the unpublished pre-placement commit 6dbcedbbfb810370d82741fd19e0eecda6306d6f) was stopped deliberately for this repair, with actual process exit 241. Its remaining native jobs completed; no compiler was active before the next scoped build. It produced no completed receipt or credit claim.

The six real wrappers now use the native .text$yd code segment, after all header definitions; helper implementations keep their existing compilation context. Both code_seg directives restore the surrounding segment normally. Final normal build: 6/6 exact. The unmodified link_cycle analyze/plan_order routines on the production object find six independent external COMDAT units, all six orderable at their own original addresses, with no refusal (placement-plan.json). This is a necessary placement prediction, not an actual link result. Real shifted-base verification still follows.

The additional source repair took approximately three minutes; immutable export/cache restoration/full-run time is separate from the body work budget.
