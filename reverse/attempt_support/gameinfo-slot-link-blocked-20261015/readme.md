# GameInfo slot duplicate: restored trial

At source base 876974c82a, runner index 19a2565407 (2026-10-15 09:33),
getConstSlot at 0x003FF2BE has three identical 24-byte strong definitions:
GameSlotApparent.cpp (ledger owner), GameInfoPlayerCounts.cpp and
GameInfo_Rva003FF374.cpp. The owner has only this duplicate blocker.

Strict preparation verifies all 37 cohort rows before the attempt. Marking
only the two secondary definitions inline __declspec(noinline) changes
getNumOpenOrOccupiedSlots, isSandbox and isStartPositionTaken: the compiler
loses EDX preservation and spills each loop index to a callee-saved register.
This fails the ordinary byte gate (three of 37), so no source change remains.
The complete attempt was restored and strict preparation passes 37/37 again.
The existing body comments already require same-TU register analysis; simple
extern declarations would also break it. Home-unit consolidation or another
evidence-backed approach is needed; no alias/hatch workaround was attempted.

Recorded through re_log.py as blocked and all three file claims released.
Rejected sources and source/object/receipt snapshots are retained only under
build/link-seat-20261015/. No improvement or closed-strict result is claimed.
