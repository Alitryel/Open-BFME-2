# VertexUV ownership: approved consolidation banked after receipt refusal

Inputs: BFME2 f4afb09f6c23fa56054e34df2d34023c7c69b0ed; committed and checked-out BFME1 a80da2e3be84ebdb3b6bc280faca3f99a44788af. Model GPT-6, lane R, budget 30m; about 16 minutes through the review packet. This is a linking/data repair, zero new matched coverage and no measured link-cycle credit.

## Finding

`PointGroupClassRva0017D770.cpp` uses a private `_VertexUV`, but the other consumers use the global `?VertexUV@@3V?$VectorClass@VVector2@@@@A` defined by pointgr.cpp. Both resolve to retail RVA 0x009F94C0 during masked byte verification. These are distinct link-time data objects; the previous iterator-COMDAT repair did not repair that identity.

Plain external binding emits 1575B rather than native1583B. Static references/pointers, inlined buffer-parameter helpers, const views and whole-owner external binding do not recover the native body. Two initial const-view trials rejected assignment from a const element address; corrected const_cast versions preserve the underlying mutable object's semantics but still fail matching. The requested restrict keyword is unsupported by this compiler. Oa/Ow/Og- are diagnostics only and are not proposed settings.

## Prepared result

The proposed-source.patch preserves the reviewed source proposal. The user explicitly approved the seven-file consolidation; implementation and ordinary verification follow below. It consolidates seven source files into pointgr.cpp, keeps VertexUV internal to that one owner and puts every actual UV reader/writer in the owner. PointGroupClassRva0017A890.cpp merely declares VertexUV and has no UV data relocation, so it is excluded (its separate VertexLoc problem remains outside this repair).

The common class declaration is the committed BFME1 pointgr.h extended only with the already-target-proven BFME2 helper declarations. The combined unit uses the existing banked_segline Draw_Triangles signature and string configuration from the verified submit helper, plus the existing Matrix4 link view from Render. No shared header was changed. Moving the sizing helper out of the class preserves the original global initializer ordering and compiler label bindings.

The private combined object reproduces **56/56 selected complete named functions**, with full COFF symbol spans recorded in cohort-results.json and no unresolved call relocations. This includes all 44 old pointgr rows, both rendering methods, the 3377B submit method and its EH handler, shutdown, both existing ICF names for the sizing helper, four compression instantiations and the1583B UV helper. The original initializer/dtor notes keep their existing compiler labels; no new alias or pin is proposed. Both26B global initializers become exact once their original declaration order is restored.

This is private-object evidence only: no production build, full associative EH admission, regenerated data ledger or final whole-image placement has been claimed. The existing two sizing rows at one RVA must remain justified byte/relocation twins under the normal existing ICF checks.

## Concrete pending work

1. Obtain explicit approval for the seven-file consolidation. The automatic execution review rejected applying it because broad replacement of a production TU exceeded what it considered the authorized single-data investigation. No production command ran and no Code file changed.
2. Apply the reviewed source moves; use normal add_match --replace-existing for the14 rows in rehome-manifest.json, with their existing ICF relationship preserved. Remove the six drained split sources only after every row is verified in the owner. No no-verify flags.
3. Re-derive data_ledger.csv through its own tool, inspect the UV entry for one internal definition and no remaining competing external binding. Do not hand-edit that generated ledger or expand a baseline.
4. Run the ordinary scoped build, data identity check, frozen-file check and link prediction on providers/consumers together. Resolve any normal gate refusal before publishing; do not claim the draft alone as progress.

Independent explanations covered: reference/helper ABI and constness; global linkage and array-pointer alias views; optimizer settings; complete owner/class context; static data definition and initialization order; the submit dependency's actual Draw_Triangles signature. The broader source consolidation was explicitly approved on 2026-10-21 after the initial automatic execution review refusal.

Explicit user approval remains valid for this consolidation. Production changes were reverted after the strict receipt refusal below; all body and file claims are released at session end.


## Approved implementation and stop, 2026-10-21

The user explicitly approved the seven-file consolidation. All fourteen moves passed ordinary add_match --replace-existing verification, preserving both pre-existing ICF sizing names. The final ordinary source build passed **58/58 ledger rows**, including the two existing generated funclets, with string/float/import checks passing. normal-admission.json and normal-build-58.txt preserve this admission evidence. The six old files had no remaining function rows before removal. find_declared_unmatched and check_csv passed; git diff --check was clean after trimming only copied-header whitespace.

The data-ledger tool generated one internal `_VertexUV` owner at RVA009F94C0, size16, defs1, refs18. Only that generated row was transplanted; full regeneration lacked23403 unrelated local objects and must never replace the committed complete ledger. generated-vertexuv-row.json preserves the exact tool-produced row.

**Stop:** tools/link_check.py --prepare-current pointgr.cpp compiled a strict receipt and ran the ordinary58/58 gate, then exited1: `link_check: prepared receipt went stale during normal gates`. No downstream data_check, eh_verify or link preview ran because the shell stopped on that exit. This is not evidence of a byte mismatch or measured credit.

A concurrent evidence write created reverse/attempt_support/vertexuv-ownership-20261021/normal-admission.json while that preparation was running. Because the approved source needs /I., tools/build.py inventories the checkout's non-.cpp filenames (build and .git excluded); adding this JSON can invalidate the strict receipt. This is the supported explanation, not a proven verifier bug: no false-reject claim, gate changes, receipt edit or bypass was attempted. At the next authorized retry, finish all evidence writes before preparing the strict receipt and keep its search inventory unchanged through verification. Then run the still-pending data identity, complete EH and provider/consumer linking checks, followed by the ordinary commit/push hooks.

Per the user's stop-on-gate-refusal instruction, the exact approved implementation is banked in approved-source-and-ledger.patch and the production source/ledgers are restored. The patch contains the fully checked source and row moves; do not treat its banked bytes as progress. Zero new matched bytes and zero measured link-cycle credit. About29min total target investigation/implementation, GPT-6, laneR, budget30m; publication/claim cleanup follows separately.
