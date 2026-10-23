# List node release: +510 B linked

At parent 0cbe358230, using the published b73720bed9 census (legacy preview):

| Unit | Before | After |
| --- | ---: | ---: |
| ShellMenuScheme_Rva002008c8.cpp | 0 | 289 |
| ControlBarResizerO1_Unresolved.cpp | 0 | 130 |
| EvacuateDamageEvacuationSum.cpp | 0 | 91 |
| Total | 0 | 510 |

The existing typed erase pins come from each native caller's REL32 and select
the 32-byte list erase at 0x438539. This target unlinks the node and calls
GameMemory free at 0x30830. These units instead emitted a node-allocator release
inside erase; Resizer also emitted the wrong list-base destructor. Specializing
only each relevant node allocator's release retains the reference STLport
erase and destructor algorithms, with target-supported allocation ownership.
The existing Rva00030830FreeAllocation spelling resolves the rowed free provider;
no symbol pin, alias, alternate entry or ledger extent was added.

Each erase emission is exactly 32 bytes, matching the entire native body and
relocations (`explain_mismatch.py --rva 0x438539 --size 32`), not just its callers.
All 9 existing rows across the three units pass ./build.sh. Explicit strict
preparation passed for all three units (8/8 and 1/1 rows), producing self-strict
reusable receipts. The paired link_check result is legacy-index 0/3 -> 3/3,
0 -> 510 B. No closed-strict closure or census update is claimed.

Local diagnostics: build/shell-erase-before.txt,
build/list-erase-sweep-before.txt, build/evac-erase-before.txt,
build/list-node-release-final.txt, build/list-node-release-strict.txt,
build/evac-erase-strict.txt, and build/{ShellMenuScheme,ResizerWindow,
EvacuationRecord}-erase-full-proof.txt.

The related GameWindow erase has a different native target (0x29DFC5), a
pool-recycle body rowed under an Object-pointer owner. It is not part of this
free-node sweep. Its claimed cohort was released without changes; its current
preview also exposes independent parser unresolveds and duplicate dispatch.
