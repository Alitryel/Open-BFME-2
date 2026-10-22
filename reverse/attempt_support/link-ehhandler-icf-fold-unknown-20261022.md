# link_census: an ICF-folded own EH handler left retail copies unknown (2026-10-22)

**Symptom.** STLport `basic_string<char>(const char *, const allocator &)`
(retail 0x00009100, owner `stlport_narrow_string_cstr_ctor.cpp`, row matched)
judged `unknown`. So all 17 other units' wrong copies counted against them, and
retail-truth-3's "another copy is proven retail" exemption never applied.

**Cause (target evidence).** The owner copy's only unresolved relocation was its
own handler, `__ehhandler$??0?$basic_string@D...@PBDABV?$allocator@D@1@@Z`. Retail
0x9100's EH prologue pushes 0x00B5B6D8, i.e. RVA 0x0075B6D8. That address is rowed
as the default ctor's handler (`__ehhandler$...@QAE@XZ`): /OPT:ICF folded the two
identical 10-byte thunks (`mov eax, FuncInfo; jmp __CxxFrameHandler`). The
judge proved a function static only through a ledger address of its own name.

**Why not a pin.** `pin_admission.py --add` refuses it with "one address, one identity".
Fold proof also fails with "only 2 non-relocation bytes", because the thunk is
two opcodes around a DIR32 and an external REL32.

**Fix.** `RetailTruth._judge` handles a copy's reference to its own
`__ehhandler$<name>` when no row bears that name. Retail's slot proves the
reference when it lands on any rowed `__ehhandler$` thunk. That equals what a row
under the folded name would prove, since the byte gate copies the thunk's FuncInfo
DIR32 from retail. A handler row of the name that lands elsewhere stays `unknown`.
So does another function's unrowed handler. Regression test:
`test_own_eh_handler_folded_into_a_rowed_twin_is_proven`.

**Measured.** With the owner re-judged, `link_check` links 8 of the 18 units:
the owner plus 7 consumers, 0 -> 4,149 B. The other 10 have independent blockers.
`build/scratch/eh_gap.py` found 60 names (82 wrong copies) whose unknown copies
miss only `__ehhandler$` addresses. The unfolded ones need ordinary handler rows.
