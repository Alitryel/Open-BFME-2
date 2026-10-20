# Two natural Pathfinder compiler EH handlers

This batch records 20 previously unclaimed retail bytes already emitted by
the real recovered Pathfinder bodies. It adds no source scaffold, pin, alias,
assembly or synthetic parent. Both handlers are ordinary compiler symbols in
`Code/GameEngine/Source/GameLogic/Pathfinder/pathfinder.cpp`.

| Parent | Native parent | Handler | FuncInfo |
| --- | --- | --- | --- |
| FindAttackPath | 002FAD13 | 00778FB5, 10 B | 009212A4 |
| rva002F4115 | 002F4115 | 00778EED, 10 B | 009211D4 |

Each whole parent is independently byte-exact. Its real DIR32 relocation at
offset +1 names its own `__ehhandler$` symbol; the corresponding native
immediate establishes the handler address. The complete associative EH graph
passes `eh_verify.verify_row` as EXACT, including its actual FuncInfo placement,
unwind states and cleanup relocations. Ownership therefore comes from the
native parent frame and proven graph, never from address adjacency.

Each complete 10-byte handler moves that proven FuncInfo VA into EAX and jumps
to the existing CxxFrameHandler at RVA 00629182. Normal byte verification
resolves both relocations and reproduces the whole handler. A narrow current
ledger scan confirms neither range already had a matched owner; other handlers
that are shared with existing entries were explicitly excluded.

The two new names are the actual emitted compiler symbols, with no
`object-symbol=` indirection. Existing source identity and layout uncertainty
is unchanged. The homogeneous batch passes `add_match_batch`: 111/111 function
rows in the owner, plus its two data rows and literal/import checks.

Read-only discovery, exact parent/handler comparisons, full EH proof and the
banking manifest are in `build/owned-ehhandlers-oct20/`; the repeatable drivers
are `build/discover-owned-ehhandlers-oct20.py` and
`build/prepare-owned-ehhandlers-oct20.py`. The discovery reads existing compiled
objects and asserts that they do not change. Normal hooks remain enabled.
