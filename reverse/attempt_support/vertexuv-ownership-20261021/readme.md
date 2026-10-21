# VertexUV ownership: consolidation and scoped COMDAT repair

Original investigation inputs: BFME2 f4afb09f6c23fa56054e34df2d34023c7c69b0ed; committed and checked-out BFME1 a80da2e3be84ebdb3b6bc280faca3f99a44788af. Model GPT-6, lane R, budget 30m; about 16 minutes through the review packet. This is a linking/data repair, zero new matched coverage and no measured link-cycle credit.

## Finding

`PointGroupClassRva0017D770.cpp` uses a private `_VertexUV`, but the other consumers use the global `?VertexUV@@3V?$VectorClass@VVector2@@@@A` defined by pointgr.cpp. Both resolve to retail RVA 0x009F94C0 during masked byte verification. These are distinct link-time data objects; the previous iterator-COMDAT repair did not repair that identity.

Plain external binding emits 1575B rather than native1583B. Static references/pointers, inlined buffer-parameter helpers, const views and whole-owner external binding do not recover the native body. Two initial const-view trials rejected assignment from a const element address; corrected const_cast versions preserve the underlying mutable object's semantics but still fail matching. The requested restrict keyword is unsupported by this compiler. Oa/Ow/Og- are diagnostics only and are not proposed settings.

## Prepared result

The proposed-source.patch preserves the reviewed source proposal. The user explicitly approved the seven-file consolidation; implementation and ordinary verification follow below. It consolidates seven source files into pointgr.cpp, keeps VertexUV internal to that one owner and puts every actual UV reader/writer in the owner. PointGroupClassRva0017A890.cpp merely declares VertexUV and has no UV data relocation, so it is excluded (its separate VertexLoc problem remains outside this repair).

The common class declaration is the committed BFME1 pointgr.h extended only with the already-target-proven BFME2 helper declarations. The combined unit uses the existing banked_segline Draw_Triangles signature and string configuration from the verified submit helper, plus the existing Matrix4 link view from Render. No shared header was changed. Moving the sizing helper out of the class preserves the original global initializer ordering and compiler label bindings.

The private combined object reproduces **56/56 selected complete named functions**, with full COFF symbol spans recorded in cohort-results.json and no unresolved call relocations. This includes all 42 named old pointgr rows (the two existing funclets are admitted by the ordinary58-row gate below), both rendering methods, the 3377B submit method and its EH handler, shutdown, both existing ICF names for the sizing helper, four compression instantiations and the1583B UV helper. The original initializer/dtor notes keep their existing compiler labels; no new alias or pin is proposed. Both26B global initializers become exact once their original declaration order is restored.

This is private-object evidence only: no production build, full associative EH admission, regenerated data ledger or final whole-image placement has been claimed. The existing two sizing rows at one RVA must remain justified byte/relocation twins under the normal existing ICF checks.

## Concrete pending work

1. Obtain explicit approval for the seven-file consolidation. The automatic execution review rejected applying it because broad replacement of a production TU exceeded what it considered the authorized single-data investigation. No production command ran and no Code file changed.
2. Apply the reviewed source moves; use normal add_match --replace-existing for the14 rows in rehome-manifest.json, with their existing ICF relationship preserved. Remove the six drained split sources only after every row is verified in the owner. No no-verify flags.
3. Re-derive data_ledger.csv through its own tool, inspect the UV entry for one internal definition and no remaining competing external binding. Do not hand-edit that generated ledger or expand a baseline.
4. Run the ordinary scoped build, data identity check, frozen-file check and link prediction on providers/consumers together. Resolve any normal gate refusal before publishing; do not claim the draft alone as progress.

Independent explanations covered: reference/helper ABI and constness; global linkage and array-pointer alias views; optimizer settings; complete owner/class context; static data definition and initialization order; the submit dependency's actual Draw_Triangles signature. The broader source consolidation was explicitly approved on 2026-10-21 after the initial automatic execution review refusal.

Explicit user approval authorized the consolidation. The first implementation was reverted after the strict receipt refusal below. The resumed implementation and current verification are recorded in the final section.


## Approved implementation and stop, 2026-10-21

The user explicitly approved the seven-file consolidation. All fourteen moves passed ordinary add_match --replace-existing verification, preserving both pre-existing ICF sizing names. The final ordinary source build passed **58/58 ledger rows**, including the two existing generated funclets, with string/float/import checks passing. normal-admission.json and normal-build-58.txt preserve this admission evidence. The six old files had no remaining function rows before removal. find_declared_unmatched and check_csv passed; git diff --check was clean after trimming only copied-header whitespace.

The data-ledger tool generated one internal `_VertexUV` owner at RVA009F94C0, size16, defs1, refs18. Only that generated row was transplanted; full regeneration lacked23403 unrelated local objects and must never replace the committed complete ledger. generated-vertexuv-row.json preserves the exact tool-produced row.

**Stop:** tools/link_check.py --prepare-current pointgr.cpp compiled a strict receipt and ran the ordinary58/58 gate, then exited1: `link_check: prepared receipt went stale during normal gates`. No downstream data_check, eh_verify or link preview ran because the shell stopped on that exit. This is not evidence of a byte mismatch or measured credit.

A concurrent evidence write created reverse/attempt_support/vertexuv-ownership-20261021/normal-admission.json while that preparation was running. Because the approved source needs /I., tools/build.py inventories the checkout's non-.cpp filenames (build and .git excluded); adding this JSON can invalidate the strict receipt. This is the supported explanation, not a proven verifier bug: no false-reject claim, gate changes, receipt edit or bypass was attempted. At the next authorized retry, finish all evidence writes before preparing the strict receipt and keep its search inventory unchanged through verification. Then run the still-pending data identity, complete EH and provider/consumer linking checks, followed by the ordinary commit/push hooks.

Per the user's stop-on-gate-refusal instruction, the exact approved implementation is banked in approved-source-and-ledger.patch and the production source/ledgers are restored. The patch contains the fully checked source and row moves; do not treat its banked bytes as progress. Zero new matched bytes and zero measured link-cycle credit. About29min total target investigation/implementation, GPT-6, laneR, budget30m; publication/claim cleanup follows separately.


## Resumed implementation: verified source and remaining closure

Resumed from BFME2 b632df8a627d328eb486b926a225672098b33064 after explicit user approval and a fresh origin-backed claim on all thirteen unique RVAs and seven files. No other worker's claim overlapped. Model GPT-6, lane R, budget30m, about20min of resumed target work before publication. All evidence filenames were created before preparing strict compiler receipts; the previous inventory refusal did not recur.

The seven production units are consolidated into pointgr.cpp; fourteen existing rows are rehomed with normal add_match --replace-existing, preserving the two already-justified ICF sizing names. The six drained units are removed. The generated data-ledger UV row is tool-derived and names one internal16B `_VertexUV` at0x009F94C0 with one definition and18references. Only this generated row is transplanted: unrelated missing local objects make the full locally regenerated data ledger incomplete. There is no shared-header, pin or baseline edit and no new matched coverage.

Additional bounded linking work uses existing views and settings: Vector3's Length link view and BFME_POINT_MATRIX4_TRANSFORM_INLINE remove two competing copies without changing any retail body. Preloading RefCount, RenderObj, WWString and Shader under their original settings before selecting size optimization for the existing DX8 wrapper preserves the standalone52B Set_Material,61B Set_Shader and158B Convert_Color bodies. The preload matters because nested WWString/RenderObj headers reset optimization. The existing Shader copy constructor must remain under the original settings. No new anchor, ABI adapter or fabricated address is added.

Final ordinary results, preserved in resume-verification.txt and resume-eh.json:

- All58ledger rows pass the normal byte/ref gates, including the two existing renumbered funclets. The private56named-body trial also checked every complete COFF extent and relocation.
- link_check --prepare-current succeeds with a strict reusable receipt and reruns the ordinary58/58gate; no census/index/status is rewritten.
- data_check --enforce: one source, zero findings, zero outside baseline.
- Complete EH verification: all3applicable graphs EXACT, zero baseline exceptions.
- find_declared_unmatched, check_csv and whitespace checks pass.

The scoped link preview drops the six now-retired owners only in memory, refreshes this source and otherwise keeps the published index at d08db10acb,2026-10-21 18:42UTC. resume-link-preview.json records the result; no index, census or history file is written. Five of seven initial blockers are removed. The unit owns10192authored bytes but remains unlinked in this preview (0 ->0); **no measured link-cycle credit is claimed**.

Remaining independent prerequisites:

1. Matrix4(bool) still emits a102B O2 copy where retail owns121B. A private size-optimized math-header trial fixes the121B copy but changes both rendered transform loops (+2B each: Render727vs725 and RenderVolumeParticle1025vs1023). The broad math optimization is therefore rejected. A class-wide dllimport forward declaration is rejected by VC7.1 C2487 because existing member imports collide; the unemitted helper-anchor trial leaves the O2 copies unchanged. A future repair needs a targeted existing-class link view or independently reconciled constructor/codegen; do not repeat whole-header O1 or class-import guesses unchanged.
2. The selected SimpleVecClass<unsigned long>::Resize comes from the frozen index's decalmsh.cpp and is not retail's; mesh.cpp also offers a wrong copy. This unit's own complete129B copy still reproduces retail0x00143E90 and preserves the existing fold-proof pin. Fix the other providers with their consumers under their own claims, then refresh the preview. Their files were not modified in this seven-file repair.

Reference freshness: official BFME1 master was fetched and compared (1425f921b5a5f1b5f80ba4857c4a70e6f2497f12); the committed and checked-out verified inputs remain a80da2e3be84ebdb3b6bc280faca3f99a44788af. No donor-pointer update or full-reference verification was attempted in this scoped resumed repair, and no successful-freshness stamp was written. Do not mistake the comparison for a verified reference upgrade.
