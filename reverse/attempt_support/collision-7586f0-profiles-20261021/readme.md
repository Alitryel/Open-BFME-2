# Collision axis-list sort, 0x007586F0

GPT-6; lane R; budget 30m; active investigation about 7 minutes.
Inputs: BFME2 208a4ed8d5bf33d20051685b46436d2abe828822; committed BFME1 reference 3f00bbbe9b0c477c2182782b7401aa4fa8b1aa80. The reference checkout was updated to that committed revision; fetched upstream was newer and was not substituted into these measurements. No claim of full-reference update verification.

The previous bank was copied to scratch. Identity/layout evidence remains native 0x007586F0..0x007588BC and byte-identical WB 0x01802EC0: four 12-byte head/tail/count records, float endpoint key +0x10, caller UpdateSort. Original sort method name unknown. No new name or pin.

## Results

All three authenticated compiler profiles (RTM, SP1, DDK 4035) produce exactly the same result for each of the two prior shapes. The best complete body remains 460 bytes, 33 differing byte positions, fitness 0.99047. It derives B with lea ebx,[edi+0xc] after clearing output counts; retail computes lea ebx,[esp+eax+0x38] directly after A. Loop alignment padding changes as a consequence.

Important extent correction: the independent-index form emits **470** bytes, not 460. Scorer truncates its comparison to the requested row extent. Every trial here separately records the complete COFF function span using object_functions. Thus the index form's apparent equal-length score was not whole-body proof.

Forty serial measurements (including controls and repeated equivalent helper controls) cover three compiler profiles, two-dimensional and named pair views, input pointer lifetimes spanning the pass condition, count checks through A/B, OR/XOR/index/address calculations, source-index types, aggregate pointer views, pointer/reference helper boundaries, and integration into the actual current owner. No improvement. Pair/index forms grow or change the register assignment; aggregate/helper boundaries canonicalize to the best bank. Narrow source index also worsens.

Independent explanations: full native control flow and layout already established by previous handoff; new lifetime, pair-layout and helper-context tests above are measured. No external callee is present in this leaf body, so missing provider visibility cannot explain it. Current owner integration equals the bank. The prior extensive control-flow/flags trials were reviewed rather than repeated; this run closes their expressly untested compiler-build hypothesis. Diagnostic aggregate casts are not proposed production code.

No production source, ledger row, pin or bank changed. Existing better bank is preserved. Remaining work needs an evidence-backed representation that combines the direct B address computation with retail register allocation; no artificial extra uses, volatile fences or assembly introduced.
