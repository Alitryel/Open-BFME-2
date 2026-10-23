# Target and prior evidence

Read all seven verdicts for RVA 0x002AEEA7 and the complete bank they cite. None cites a separate attempt-support file; a content and filename search of reverse/attempt_support found none for this target. The farm warning requires a fresh semantic review. The bank has a compiler barrier and a volatile read of its local team pointer, but does not contain equal-arm expressions or volatile self-stores.

Retail inspection in retail.log confirms the 400-byte boundary between the preceding ret 8 and the next function's prologue, the thiscall ret 4 ABI, all calls listed in the bank comments, contain +0x250, AI +0x258, command base +0x20, Player index +0x54, list +0x32C, prototype head +0x334, 24-byte member-iterator output, and the 8-byte team PMF. The name remains address-derived. The script caller supplies constant 1; that does not prove a real method name or enum argument type.

## H1 (before the first compiler experiment)

Hypothesis: the bank's volatile team-pointer read and compiler barrier are compensating for an inaccurate iterator representation or loop model. Replacing these with the typed, inline DLINK_ITERATOR<Team> used by exact Player siblings, and expressing the object loop as the donor's done()/cur() pattern, may recover retail's spill and reload behavior naturally.

Evidence: retail has an object-current reload and null test at +0x9B followed by a memory compare at +0x145; a raw, unguarded PMF call at +0x14F; and the adjacent exact ungarrisonAllUnits uses a typed team iterator and ordinary object iterator accessors. Prior attempts report raw-PMF and loop spelling trials, but not reconciliation with the subsequently exact sibling's typed iterator in combination with the current farm bank.

Refutation: the natural typed-iterator trial either removes a required retail null test, adds a PMF guard, or fails to reduce structural regions and memory/register differences against a freshly compiled original bank. Do not add behavior-changing operations or treat positional byte count as success.

H1 result: refuted. typed_natural emits 410 bytes, typed_barrier 411, and raw_no_volatile 409. All have 17 structural regions versus the original bank's 16. No replacement is justified.

## H2 (before the next compiler experiments)

Hypothesis: restoring the source-level STLport list iterator, and separately restoring the Object iterator's typed virtual-inheritance PMF storage instead of its byte-array placeholder, can change alias and spill analysis without inventing operations. These representations are independently supported by the exact sibling sources and the rowed iterator providers. The raw sentinel node and padded iterator in the bank bypass both representations.

Evidence: WorldBuilder C19C00 has the same donor garrisonAllUnits loop skeleton and distinct done()/cur() reads, and the exact Team::iterate_TeamMemberList provider copies the PMF to output +8, not a packed +4. Its actual type is 8-byte-aligned and 24 bytes wide. Current Object is only singly inherited and its iterator hides those typed fields behind unsigned char[20].

Refutation: these typed representations preserve the same alignment defects, introduce extra guards, or increase either structural regions or memory/register counts. A positional-byte gain alone is insufficient.

H2 result: the typed Object layout alone is instruction-identical to the bank. The STLport list changes this to EBX and eliminates the zero register, which is meaningful progress toward retail. It has 13 structural regions, 18 memory and 18 register differences versus 16/19/13 before. This is a class tradeoff and cannot replace the bank. Combining the typed Object layout with the list has the same output.

## H3 (before the next compiler experiments)

Hypothesis: now that the real list has removed the zero register, removing the bank's volatile team read or using the typed team iterator can let Team win EDI and spill the list node, as retail does. H1 ruled this out only with the raw list, where EBX remained occupied by zero. Test these supported representations against the new allocation, with the sibling's inlined list comparison as a separate control.

Refutation: Team remains spilled or the typed advance adds a guard or loop rotation, without an admissible improvement in all difference classes.

H3 result: list_typed_natural is 401 bytes with 12 structural, 18 memory and 17 register differences (170 positional bytes); list_raw_no_volatile is 409 bytes with 12/17/18 (351 positional bytes); the inline-comparison control is identical to the latter. Team still spills and the list remains in a register. These are class tradeoffs, not bank improvements.

## H4 (before the next compiler experiments)

Hypothesis: the iterator's natural done()/cur() pair and lifetime boundaries, rather than just its storage, cause the redundant top null test and register priorities. The bank's loop condition reads cur() directly; the donor and WorldBuilder use done(). With the now-tested real STLport list, compare the bank's raw team walk using the donor done() condition and separate the lifetime of the team PMF from the explicit outer nonempty guard. This tests supported source scopes, without adding volatile operations or artificial equal-arm expressions.

Evidence: WorldBuilder's distinct done()/cur() reads and its local team iterator scoped inside the list loop; retail hoists the PMF initialization under the nonempty-list guard. Exact sibling sources similarly scope the typed team iterator inside the list loop. H1 and H3 used the typed team iterator; neither retained the raw PMF while changing these scopes with the real list.

Refutation: the required reload still needs a barrier, zero caching returns, or the scope changes retain the list in EDI/EBX and Team on the stack. Stop pursuing this family once those outcomes are measured.

H4 result: done()/cur() spelling does not change the barrier trial; moving the PMF into its donor scope restores EBX-zero and 17 structural regions. Removing the barrier gives 14 structural, 15 memory, 18 register differences. These scopes and accessors do not solve the allocation.

## H5 (diagnostic only, before the next compiler experiments)

Hypothesis: the remaining allocation wall is a small priority gap between the team value and the STLport list iterator, as described by docs/matching.md's controlled register-allocation recipe. Add one through three diagnostic volatile-sink stores of Team at the top of its loop in list_typed_natural. These trials change behavior and must never be banked or put in Code. They measure how many extra references are required to make Team occupy a callee-saved register, and whether the rest of retail's allocation then follows.

Refutation: none of these probes puts Team in a callee-saved register, or Team wins one but the this/list/zero roles still differ. That would rule out a small natural source-weight adjustment as a sufficient fix for the remaining allocation.

H5 result: one diagnostic Team store produces the target's this=EBX, Team=EDI, building=ESI and spilled-list roles together, and its top-tested team loop. Two stores retain those roles; three promote Team to ESI and move the building. This establishes a one-use priority gap. The extra stores are behavior changes and remain diagnostic artifacts only.

## H6 (before the next compiler experiments)

Hypothesis: the donor's visible TeamPrototype::iterate_TeamInstanceList() return-by-value helper changes the reference/lifetime graph enough to close the measured one-use Team priority gap. The bank constructs the team iterator directly or splits its PMF from the current value; the real donor helper returns the combined iterator. Compare the helper return with the direct constructor, then test the source's equivalent null-team guard as a positive conditional scope. All emitted runtime operations must retain retail semantics.

Evidence: WorldBuilder calls its inline helper at B3C610 and assigns the 12-byte Team iterator at C19CDF; GameCommon.h MAKE_DLINK_HEAD defines exactly a return of DLINK_ITERATOR<Team>(head, &Team::dlink_next_TeamInstanceList). This helper was not represented in H1-H4. One extra Team reference suffices diagnostically.

Refutation: the helper inlines to the existing wrong allocation and guard polarity fails to change it. Do not turn the diagnostic sink into a bank lever.

H6 result: the donor helper removes the team/list structural discrepancies and leaves only three structural regions, with 16 memory and 24 register differences (401 bytes, 101 positional bytes). It naturally keeps Team in EBX, this in EDI and the building in ESI. Positive null guards emit identical code. The register count is higher than the bank, so this is still a prohibited tradeoff.

## H7 (before the next compiler experiments)

Hypothesis: the remaining swapped this/Team registers come from the bank's explicit outer nonempty guard plus the for-condition, which gives this an extra conditional reference compared with the donor's single for-loop. Remove that redundant outer guard while retaining the helper, then independently restore the compiler barrier to distinguish retail's object-condition reload from register priority. Test the actual typed Object-iterator layout only with this strongest helper model.

Evidence: the original donor has a single list for-loop and no separate nonempty guard. H6 recovers the target's team/list structure, and the diagnostic priority gap was one use. Retail's object null test reloads current at the top rather than retaining the bottom condition's value.

Refutation: removing the redundant guard does not recover this=EBX/Team=EDI or the barrier introduces zero caching again. This exhausts the known donor-scope differences without inventing operations.

H7 result: removing the outer guard and restoring the typed Object layout emit the same 401-byte helper result. Reintroducing the barrier restores EBX-zero and 17 structural regions. No semantics-preserving trial lowers every mismatch class relative to the bank. The donor helper candidate and all raw measurements are preserved; no new justified experiment remains from these findings.
