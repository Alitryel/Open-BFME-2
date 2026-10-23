# Three natural EH handlers from recovered C++ owners

This homogeneous batch banks **30 new C++ bytes** emitted by three real,
already recovered methods. It adds no source scaffold, assembly, pin or alias.

| Parent RVA | Existing C++ method | Handler RVA | FuncInfo RVA |
| --- | --- | --- | --- |
| 00336EB0 | LuaScriptEngine object-status event parser | 0077C2B6 | 00925924 |
| 0046525F | OpenContain::exitObjectViaDoor | 0078AC87 | 00939830 |
| 00158E90 | Render2DSentenceClass Thai sentence builder | 007671A8 | 0090BAB0 |

Each complete 10-byte handler loads its parent's FuncInfo and jumps to the
existing CxxFrameHandler at RVA 00629182. Addresses are established by the
actual DIR32 relocation in each byte-exact parent and its matching native
immediate. The whole associative EH graph independently passes EXACT, proving
the FuncInfo placement, unwind states and cleanup calls. Parent ownership is
never inferred from adjacency. Existing parent naming/layout uncertainty is
retained; the new names are the actual compiler-emitted handler symbols.

The initial read-only scan covered 80 recently changed C++ units. Only three
objects initially had strict current receipts, so matches from older objects
were treated as provisional. Four explicitly claimed owner units then passed
`link_check --prepare-current`: all 13 existing function rows, one data row,
literals and imports verified. No census, index or link status was changed.
Every selected parent and handler was rechecked against those current objects,
with unchanged object stamps and include-search inventory.

Two additional template-handler candidates were excluded: their compiler
symbol names already have other ledger owners. The ordinary batch admission
refused the first conflict atomically before writing any row. Neither matching
bytes nor an exact graph overrides the existing name/address constraint. Their
claims were released, and no substitute name or alias was introduced.

The remaining three ranges and names are genuinely unowned. Normal atomic
`add_match_batch` verification passes in each real source. The normal commit
and push hooks are retained. Scripts, refreshed receipts, native graph proofs,
the excluded-name records and the banking manifest are under the ignored
`build/recent-natural-handlers-oct20/`; drivers are
`build/recent-natural-handlers-oct20.py` and
`build/prepare-recent-handlers-oct20.py`.
