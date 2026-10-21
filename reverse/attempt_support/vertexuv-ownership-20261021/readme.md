# VertexUV ownership: prepared consolidation, awaiting approval

Inputs: BFME2 f4afb09f6c23fa56054e34df2d34023c7c69b0ed; committed and checked-out BFME1 a80da2e3be84ebdb3b6bc280faca3f99a44788af. Model GPT-6, lane R, budget 30m; about 16 minutes through the review packet. This is a linking/data repair, zero new matched coverage and no measured link-cycle credit.

## Finding

`PointGroupClassRva0017D770.cpp` uses a private `_VertexUV`, but the other consumers use the global `?VertexUV@@3V?$VectorClass@VVector2@@@@A` defined by pointgr.cpp. Both resolve to retail RVA 0x009F94C0 during masked byte verification. These are distinct link-time data objects; the previous iterator-COMDAT repair did not repair that identity.

Plain external binding emits 1575B rather than native1583B. Static references/pointers, inlined buffer-parameter helpers, const views and whole-owner external binding do not recover the native body. Two initial const-view trials rejected assignment from a const element address; corrected const_cast versions preserve the underlying mutable object's semantics but still fail matching. The requested restrict keyword is unsupported by this compiler. Oa/Ow/Og- are diagnostics only and are not proposed settings.

## Prepared result

The proposed-source.patch contains a **draft only**, never applied to Code. It consolidates seven source files into pointgr.cpp, keeps VertexUV internal to that one owner and puts every actual UV reader/writer in the owner. PointGroupClassRva0017A890.cpp merely declares VertexUV and has no UV data relocation, so it is excluded (its separate VertexLoc problem remains outside this repair).

The common class declaration is the committed BFME1 pointgr.h extended only with the already-target-proven BFME2 helper declarations. The combined unit uses the existing banked_segline Draw_Triangles signature and string configuration from the verified submit helper, plus the existing Matrix4 link view from Render. No shared header was changed. Moving the sizing helper out of the class preserves the original global initializer ordering and compiler label bindings.

The private combined object reproduces **56/56 selected complete named functions**, with full COFF symbol spans recorded in cohort-results.json and no unresolved call relocations. This includes all 44 old pointgr rows, both rendering methods, the 3377B submit method and its EH handler, shutdown, both existing ICF names for the sizing helper, four compression instantiations and the1583B UV helper. The original initializer/dtor notes keep their existing compiler labels; no new alias or pin is proposed. Both26B global initializers become exact once their original declaration order is restored.

This is private-object evidence only: no production build, full associative EH admission, regenerated data ledger or final whole-image placement has been claimed. The existing two sizing rows at one RVA must remain justified byte/relocation twins under the normal existing ICF checks.

## Concrete pending work

1. Obtain explicit approval for the seven-file consolidation. The automatic execution review rejected applying it because broad replacement of a production TU exceeded what it considered the authorized single-data investigation. No production command ran and no Code file changed.
2. Apply the reviewed source moves; use normal add_match --replace-existing for the14 rows in rehome-manifest.json, with their existing ICF relationship preserved. Remove the six drained split sources only after every row is verified in the owner. No no-verify flags.
3. Re-derive data_ledger.csv through its own tool, inspect the UV entry for one internal definition and no remaining competing external binding. Do not hand-edit that generated ledger or expand a baseline.
4. Run the ordinary scoped build, data identity check, frozen-file check and link prediction on providers/consumers together. Resolve any normal gate refusal before publishing; do not claim the draft alone as progress.

Independent explanations covered: reference/helper ABI and constness; global linkage and array-pointer alias views; optimizer settings; complete owner/class context; static data definition and initialization order; the submit dependency's actual Draw_Triangles signature. The remaining prerequisite is approval/admission of the prepared broader source consolidation, not another blind spelling sweep.

All claims acquired for this investigation are released when this packet is saved. The source repair is not applied. Production remains exactly as before the investigation.
