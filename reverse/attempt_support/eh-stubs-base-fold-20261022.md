# Narrow string base cleanup admission, 2026-10-22

BFME 2 starting tree e33d802535; BFME 1 verified pointer 42bba2ddbd5c.
Follow-up to eh-stubs-20261022.md. No destructor identity is swapped.

The unresolved narrow `_String_base<char, allocator<char> >` destructor already
compiles in registry.cpp to the complete 14-byte free-first-member destructor
at RVA 142D70, including the resolved free call at +8. Constructor EH maps
independently select that body for base-only lifetime states. The official
fold_proof_problems check returned no problems, then pin_admission --add
admitted the folded template name using that ledger source. Every existing
owner at 142D70 was checked by that proof; there is no other address for the
newly pinned name. No donor identity is inferred from bytes alone.

registry.cpp passed 18/18 rows, literals and imports. Pin consistency passes.
Exact parent EH graphs bind labels $L550/$L610 in narrow_string_range_ctors
and $L6146 in narrow_string_substr to 75C350/75C390/75C918 respectively.
add_match_batch verified all three complete 8-byte actions, resolving their
REL32 jumps through the admitted base destructor. These are emitted by existing
C++, with no new source or compiler-label forcing. New unique EH coverage:24B.

Paired ordinary link_check on the same 17-unit cohort before/after the pin:
2/17 clean, 3419 linked bytes in both runs: +0 legacy linked bytes.
These are legacy previews, not self-strict or closed-strict link evidence.
The pin alone does not fix remaining constructor or selected-copy blockers.
No full link cycle or census was run.

Five assigned stubs remain blocked: 768841/76884B/768868 require the still
unrowed and currently claimed parent18C84E;75C850 requires coordinated lock
provider identity;7A70A0 still has the previously recorded scalar-versus-array
delete shape. Their dependencies have not changed, so no identical trials
were repeated. The previous handoff retains their evidence.
