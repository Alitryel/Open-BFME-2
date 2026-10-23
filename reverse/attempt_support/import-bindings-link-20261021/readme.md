Import binding repair, 2026-10-21

The three current-object units failed against the published 2b4d1fb42a index before this change and all three pass afterwards: legacy LINKED 0 -> 147 B. Self-strict preparation verifies all five current rows (148 B) before and after. The index counts the stream row as 52 B; the current ledger extent is 53 B. No closed-strict closure or authored coverage gain is claimed.

Target evidence from the PE import directory and complete row disassembly:
- S1IndirectSlotCalls.cpp: refresh at RVA 4CEF33/17 calls IAT BBA918, winmm!timeGetTime; constructor at 50E52/16 calls BBAAC4, mss32!_AIL_lock_mutex@0. Replace donor slot globals with correctly typed dllimport declarations.
- Rva0083ED40StreamStateReport.cpp: RVA 1BDD0/53 loads BBA67C (msvcr71!_iob), adds 40h, and calls BBA660 (msvcr71!fputs) with ios failure. The CRT FILE is 32 B, so the existing offset names stderr. Include stdio.h and select /MD; default static CRT declarations produced direct calls and were rejected by the byte gate.
- renderobjectrecycler.cpp: the declared stricmp import is absent from retail; its case-insensitive CRT import is _strcmpi (BBA518 and BBA6F4). The verified BFME1 donor 68c5ce2789e974f36b6c742d57437d157bc159e9 already uses /Dstricmp=_strcmpi for this unit; inherit that binding. The other two donor files retain opaque slots and receive target-specific repairs here. No donor layout or semantic identity is promoted from masked bytes alone.

Checks: ./build.sh on all three sources passes 5/5, one string and four named imports; link_check.py --prepare-current supplies strict reusable receipts for those same five rows. link_check.py on the same three current objects reports 0/3 and 0 B before, 3/3 and 147 B after. find_declared_unmatched.py, check_csv.py and diff --check pass. The recycler has five existing present-unmatched definitions; none was added or newly claimed. Its unreadable, unreferenced Peek_Obj diagnostic remains nonblocking under retail-truth-2.

Raw local command output: build/seat-import-before-prepare.txt, seat-import-before.txt, seat-import-build3.txt, seat-import-final-prepare.txt, seat-import-final-after.txt. The census, index and link_status were not rewritten. No full link cycle was run.
