# Drift report: the 16 live candidates are all spent (2026-10-20)

`reverse/zh_sweep/drift_report.csv` was regenerated 2026-10-20 10:31 and holds
37,539 rows. Rows land continuously, so the report ages: most of its candidates
are already matched. Filtering it against the current ledger by **candidate RVA**
(not by function name, which misleads â€” several names share one address after
ICF) leaves only 16 candidates at 24â€“220 B with `aligned_pct >= 85`, `votes >= 3`.
Each one is spent. Re-check with `drift_live.py` in this directory (it prints
the live list) before treating any drift row as work.

| candidate | verdict |
|---|---|
| 0x006E039E `?isTickAnimation@@YA_NPAX@Z` (Apt.cpp) | Real body **0x006E03A0, 75 B, already matched** as `?rva006E03A0@BfmeAptValue006DCD20@@QBEHXZ` (`AptValueTypePredicatesBFME2.cpp`). Wrong TU attribution: the free helper in Apt.cpp takes its pointer on the stack, the retail body is a member (`mov esi,ecx`). The two AptCIH.h predicates are distinguishable by their assert lines: **0xd3 = the type-18 check** (10 inlined copies, `get()==0x12`), **0xd8 = the type-19 check** (7 inlined copies, `get()==0x13`). `apt_tick_search.py` in this directory finds both forms. |
| 0x007588BA `??_GVideoPlayerBase@@UAEPAXI@Z` (+5 `VectorClass` twins) | Real body **0x7588C0, 30 B** (the candidate is 6 bytes into the preceding body plus `int3` padding) and **already matched** by the ICF twin `??_GRva009A45A0CollisionData@@QAEPAXI@Z` (30 B). `VideoPlayerDestructorThunk.cpp`'s own copy is 36 B only because it inlines `~VideoPlayerBase`; a `__declspec(noinline)` there would reproduce the 30-byte twin â€” a fold-pin candidate, never a second row at that address. |
| 0x006C0D6F `?bfmeEmitRva0018E750VectorDtor@@â€¦` (+2 twins) | Real body **0x6C0D70, 39 B**, a **thiscall member** (`mov eax,[ecx+0x28]`, element stride `0xc`, element dtor `0xa9e440`, `operator delete` `0x2fd80`). All three candidate names are free `__cdecl` helpers with element stride `0x24` â€” a shape coincidence, wrong identity. Writing it means naming the owning class (unknown; address-derived only) and the vector member at +0x28. |
| 0x006F009D `?GetCharacterInst@AptCIH@@â€¦` / `?CharacterInst@AptCIH@@â€¦` (51 B) | Mid-instruction: 0x6F009D is inside the big dispatcher that starts at 0x6F0090 (`call 0x6e0200`, `push 0xa5`, jump table at 0xaf11a4). No function boundary there. |
| 0x001B28D8 / 0x001B28DC `??_Gâ€¦` (34 B / 30 B) | The generic scalar-deleting-destructor fold region. Other workers hold live claims on several 0x001Bâ€¦ addresses (`claims.py list`), and each name there is an ICF twin of one body. Do not row a second name at an address that already has one. |
| 0x007B682E `_$E285` (WorldHeightMap.cpp) | An EH funclet. It lands with its parent body and its `$L` graph, never standalone. |

Method note for the next drift pass: match on `candidate_rva` coverage by matched
rows, then check the **boundary** (int3 padding before a body is common; a
candidate that starts on `cc` is one to twelve bytes early), then check the
**calling convention** (a free-function candidate whose retail twin loads the
argument from `ecx` is a member â€” different identity even at 96% shape).
