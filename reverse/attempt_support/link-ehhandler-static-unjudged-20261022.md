# Retail truth could not judge any COMDAT copy with a C++ EH handler

Check: `tools/link_census.py` `RetailTruth._judge` (verdicts behind keep_rule,
judge_selected and link_check).

MSVC 7.1 emits a function's EH handler as `__ehhandler$<function>`, a STATIC
symbol in its own COMDAT section; the function body loads it with
`mov eax, offset handler`. `_judge` gives statics no address ("a static's name
is per TU"), so every copy of an EH-carrying function stayed `unknown`, however
exact its bytes, although the ledger rows these handlers by that very name.

Evidence: `??1?$basic_string@GV?$char_traits@G@_STL@@V?$allocator@G@2@@_STL@@QAE@XZ`,
row 0x0000B3C0 (stlport_narrow_string_base_dtor.cpp), first in link order:
every relocation resolves except `__ehhandler$...` (row 0x0075B7CB), so the
owner's own copy is `unknown` and 26 units touching the name are held as
`selected` (45,109 B). Over the whole index, 3,498 COMDAT copies are `unknown`
only because of their handler.

Fix: a static named `__ehhandler$<name>` is checked against its ledger row;
landing on it proves the site. A miss leaves the copy `unknown`, never
`wrong`: the ledger can name a handler after an ICF twin whose home is not
this copy's (`__ehhandler$??$_Construct@U?$pair@$$CBHV?$vector@I...` row
0x0076A03A is the handler of parent 0x001E7243, while the function's row is
0x0021C671 with handler 0x0076E633).
