# W3DView::pickDrawable: receiver-access investigation

Initial checkpoint: blocked, original bank unchanged. **Resolved in the subsequent lifetime investigation**: see the recovery section below. The earlier experiments and their refutations remain valid historical evidence. Target `?pickDrawable@W3DView@@UAEPAVDrawable@@PBUICoord2D@@_NH@Z`, RVA `0x0008B1E5`, actual whole extent 651 bytes (end0x8B470). No Code, ledger, pins or verifier changes. This records a failed planned approach; no exact match or improved bank is claimed.

## Starting evidence and reproduction

Read all standing RVA evidence and the tracked w4 and w4-followup handoffs before testing. Those identify the W3DView vtable slot9, rowed screen-pick caller431012, named ZH skeleton and WB9938D0. These identity/boundary facts were carried from their target evidence, not inferred from similarity. The donor does not prove BFME2's additional searches/fallback. Current bank restores the GameLogic-null guard and already matches both historically troublesome ECX joins.

`inputs.json` captures this investigation's revisions and hashes. Updated only the clean BFME1 checkout to BFME2's already committed pin cf0a80c22858, without changing the gitlink. The default compiler is MSVC13.10.3077 with the existing O1/G7/SSE/EHs flags. BFME_OBJSTORE=off for all probes. No source from a protected decoder lane was read.

Fresh normal explain reproduction: target651B; current bank652B; raw instruction alignment has zero structural changes and one true operand difference, retail+0x1B6 MOV ECX,EAX versus candidate MOV ECX,[EBP-0x10]. Relocations and branch displacement consequences are excluded from that comparison. The first positional patched difference at+0x24 is an earlier jump displacement caused by the extra byte, not a new register-save defect. A shifted source's DIR32 resolution can also make the patched positional listing noisy; raw instruction alignment excludes each actual COFF relocation operand. Do not diagnose those shifted immediate values as class layouts.

`before-explain.log` is the unmodified normal-tool output (PowerShell UTF16). Explain's exit0 is diagnostic success, not a byte-gate pass. The raw extent and full resolved byte equality were checked separately in the scratch drivers. There is no exact win.

## Refuted handoff hypothesis

The handed-over change declares an ordinary draw local, makes its other accesses textual volatile accesses, and reads the call receiver normally. It emits649B with one structural region and three true nonbranch operand differences: the compiler coalesces into ECX instead of preserving the native EAX value plus MOV ECX,EAX. `access-probe.cpp.txt` is the exact failing source; `access-probe-explain.log` its normal explain output. This refutes the original proposal. Do not re-serve it as a likely solution.

Result array schema is `[trial, emitted_bytes, structural_regions, nonrelocation_nonbranch_operand_differences, exact]`; the targeted table uses named object fields. These compact custom alignment counts are diagnostics, not replacements for the repository gate.

## Additional bounded tests

- `targeted-results.json`: 32 combinations of access qualification for initialization, hit stores, post-call reads and terrain stores; the receiver uses the cached field value. Qualifiers either retain649B or disturb more of the body. A plain forceinline DrawableInfo field accessor also leaves652B/one difference with the stack receiver and649B with the cached receiver.
- `typed-results.json`: pointer/void-pointer/integer helper results, const receiver qualification, actual noinline zero-return body visibility, and assignment-conditional forms. These were diagnostic only: new decorated prototypes were resolved in a temporary in-memory map to the existing helper address; no pins or rows were created, and such a model alone would not authorize landing. No exact match. No-inline stub visibility preserves the mismatch; allowing inlining removes the call and branches, regressing the retail structure.
- `shape-results.json`: textual-volatile/const source field loads, positive guards/explicit else, and value-returning selection helpers. Same652/649 outcomes or regressions.
- `reuse-results.json`: reuse the existing pointer across the query call, use a condition declaration, and use an ordinary ternary fallback. Same mismatch or larger structural regressions.
- `query-results.json`: inline query wrapper boundaries, tiny value/reference query records and supported alias/inlining flags. No exact result. Some reference/pointer wrapper variants did not compile because they dropped volatile qualifiers; those failed experiments are not evidence about code generation. No successful trial uses an invalid qualifier conversion.
- `profile-results.json`: repository-authenticated4035 and6030/SP1 profiles, both stack and cached receivers. Both reproduce652B/one difference or649B. Compiler profile is not an established solution.
- Actual map lifetime: replacing the bank's 12B PickHitMap constructor/destructor wrapper by the actual existing `RenderObjHitMap` STLport type preserves652B with volatile draw and669B without it. The actual multimap default constructor then needs an unresolved25B provider; no pin was created. Thus this test does not prove a landable map rewrite or solve the receiver issue.

The WB helper CB88F0 was independently inspected: it is13B unoptimized thiscall, returns zero, no calls. This supports the existing folded null-helper interpretation, but not the bank's borrowed network-class name as an original Drawable identity. A future exact recovery should reconcile that view and canonical class declarations before admission.

## Resume and publication

The best existing bank remains unchanged at reverse/attempts/0x0008b1e5.cpp. There is no newly discovered missing-function prerequisite, so no speculative blocked-on is recorded. Further work needs a new source/alias/register-lifetime explanation; repeating these qualifier, cache, wrapper or profile families unchanged has no support.

All generated trial sources and generation drivers remain in ignored build/pickdrawable-handoff-20261019 and build/pick_*_trials.py in the isolated checkout bf2-bank-sway-20261015. The included results plus representative source are sufficient to reject the current handoff without preserving every failed variant. Do not modify the game source or call add_match for these nonmatching probes. Normal check_csv and commit hooks verify this evidence-only change; no full build, census or runtime comparison is claimed.

Measured session was approximately9minutes to the result timestamp (2026-10-19T20:25:11Z), excluding final evidence publication. model=GPT-6-Codex.

## Recovery: shared result lifetime

The next independent hypothesis concerned result lifetime and use counts rather than the receiver expression. Keep an ordinary nonvolatile `Drawable *draw`, keep the native search/call/terrain behavior, and route the successful picked result and terrain early-out result paths to one `pickedDone: return draw;` after a scope containing terrain locals. This is an ordinary control-flow refactor: it adds no dummy operations and avoids entering the scope of uninitialized locals. The invalid-shroud branch still returns null, and the hit map still receives exactly one destructor call on every path after its construction. The trailing unconditional goto was removed as unnecessary.

This emitted exactly651B, all relocations resolved, zero differing bytes. Normal `explain_mismatch.py` independently reports exact. The source then adopted the canonical `ICoord2D.h` and `GameLogicObjectLookupView.h` without changing emitted bytes. It is installed at `Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DViewPickDrawable.cpp`. `add_match.py` verified the whole body, recorded landed and removed the old bank. A scoped `eh_verify.py` reports the parent EH data EXACT (1/1). `find_declared_unmatched.py` reports all defined functions already matched; the class gate passes. No new symbol pin, assembly, volatile access or shared-header edit was required.

The result supports a source lifetime/use-count explanation for the EAX-to-ECX move. The compiler's internal register-allocation cause was not reverse engineered, so that explanation remains an inference. The concrete verified recipe is the common result exit and ordinary pointer.

A scoped ordinary link preview cannot assess this newly introduced source because it is absent from the current census index807ae26368. The new-variants COMDAT check is run separately before commit; it is narrower than proving the unit links. No census or link-cycle run was started.
