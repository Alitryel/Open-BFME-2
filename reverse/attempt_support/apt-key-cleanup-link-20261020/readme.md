Apt key destructor link trial, 2026-10-20

Index e7a7769fe5 (2026-10-20 18:36); donor review 4483e88da1c2 as in
special-ability-frame-global-link-20261020. Read earlier 006D07E0 deferral: do
not pin the wrong-owner 006CD530 teardown. Current pin instead names an ICF
fold at 000A9DF3, with Bfme5ThirtyFour fold proof. Current index finds these
private destructor copies wrong for that address. No new pin attempted.

Import-forceinline key destruction exists in PlaybackBufferResize,
Rva00893030RefDispatch and Rva006D0790Init. Tried the same attribute change,
without changing any destructor body, in seven units (listed in measurement).
Also applied it to BfmeRefVGO in AptLoad, which had its own destructor conflict.
All seven retain EH cleanup references to __imp_??1Rva006D07E0Key; AptLoad
also retains __imp_??1BfmeRefVGO. Link preview remains 0 -> 0 bytes. No changes
kept. Needs coherent non-imported cleanup ownership or actual canonical body
that matches folded 000A9DF3, including relocation callees. Existing visible
body copies differ by private view; suppressing emission alone is insufficient.

Strict before: 83/83 row bytes, 101 strings, one float, import checks pass.
Trial byte gate reports Bfme5ThirtyFour funclets rva007A81B8/7A8458/7A8488
missing under their old object labels; AptLoad's $L1763 has two indistinguishable
candidate bodies in its parent's group, so the gate correctly refuses to pick.
No gate workaround attempted. This is an altered EH graph/ownership attempt,
not a demonstrated false reject. Restored all original source text, retained
only this concise handoff and exact preview diagnostics. t=7 model=gpt-6.1-sol.
