# Link repair triage, 2026-10-23

Inputs: BFME 2 `27dd681fd25e39dcb7a019cae17765c4e55d2f84`, BFME 1
`96c88c73a5cd1a58fc2f8db691beea50acd996db`, published census
`456ce161c5` (2026-10-23 06:28, retail-truth-4). No production source changes
retained; no new linked-byte gain claimed. All claims released.

## Registry allocator experiment

The older registry deferral identifies `_STL::free` versus C `free` as a string
COMDAT difference. Changing `/EHsc` to `/EHs`, removing the macro that redirects
STL string cleanup to `_STL::free`, and explicitly declaring the manual Win32
imports and `sprintf` `__declspec(nothrow)` preserves all 18 registry bodies.
The normal scoped gate passed source claims, 18/18 functions, seven funclet
pins, four literals and fourteen named imports. The accompanying diagnostic
patch preserves the exact trial; it is not a proposed production change.

However, a before/after preview including the current provider
`Code/Libraries/Source/WWVegas/WWLib/stlport_narrow_string.cpp` shows that the
original `Code/Libraries/Source/WWVegas/WWDownload/registry.cpp` already LINKS
1,907 authored bytes. The trial also links 1,907. It repairs no current blocker
and was reverted. Do not repeat the free-spelling change based only on the old
census. This is a legacy preview, not a closed-strict measurement.

Command: `python3 tools/link_check.py Code/Libraries/Source/WWVegas/WWDownload/registry.cpp Code/Libraries/Source/WWVegas/WWLib/stlport_narrow_string.cpp`.

## Current-provider checks and remaining contracts

* The current `PingThread_PingThreadClass_Thread_Function.cpp` plus
  `PingThread.cpp` already link 410 + 234 bytes. The old unresolved placeholder
  is repaired upstream; no local gain.
* `DebugDestructorThunk.cpp` plus `DebugConstructor.cpp` still link only the
  constructor's 418 bytes. The destructor emits a one-slot Debug table, the
  constructor emits 35 slots, and retail's table at RVA `0x007BE810` has 184
  bytes / 46 slots. Copying the first provider's truncated table is not an
  established class repair. The destructor writes its own vptr, so a speculative
  `novtable` change is inappropriate. Reconcile the whole retail class contract.
* `Rva003FD4DADtor.cpp` plus `LivingWorldLogicDelayedEventXfer.cpp` still link
  zero of 703 authored bytes. The destructor's Snapshot view has four slots,
  while retail and the other provider require seven. The latter also references
  undefined `Rva002BB49CEvent::{crc,getType,loadPostProcess,slot4,slot5,xfer}`.
  This needs genuine class/method ownership, not an invented table.
* The previously documented SysTime, string hash/insert, owned-deque, and module
  hierarchy blockers have no new supporting hypothesis in this pass. Existing
  banks and attempt logs remain the starting points.

## Coverage and measurement limits

Checked `link_rank.py --top 30 --near 2` and `--top 150`,
`class_views.py --blockers`, `repair_queue.py link --limit 15`,
`name_globals.py --dry-run` (zero edits), and `rehome_rows.py --limit 20`
(the one exact Eva rehome is already repaired upstream). The high-ranked class
families require shared ABI reconciliation. Many small ranked blockers already
link when their current provider is included; these are not new repairs.

The BFME 1 donor review included its IME, compareNoCase, AIState, Drawable and
Apt string linking repairs through fetched official revision `f5140c1c`.
The verified submodule pointer was preserved. Donor repairs are leads, not BFME 2
ABI or byte proof; no donor-pointer advance was claimed here.

`link_check.py --refresh --current-ledger` cannot establish current closure:
110 objects are absent from the published index, including AbsImportForwarder,
CommonRoundedProductStride, Mutex, MilesAudioManager and Texture. No census was
rebuilt, and no closed-strict gain is asserted. This cache failure does not prove
the repair lane is exhausted. Resume from a refreshed published index, or select
a concrete class contract with independent evidence rather than repeating these
stale rankings.

Scratch receipts in this checkout are `build/link-seat-registry-original-check.txt`,
`build/link-seat-registry-trial1.txt`, `build/link-seat-ping-before.txt`,
`build/link-seat-debug-before.txt`, `build/link-seat-event-before.txt` and
`build/link-seat-current-ledger.txt`. These scratch paths are not prerequisites
for using the tracked findings or diagnostic patch.
