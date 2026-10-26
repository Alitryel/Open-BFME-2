# Allocated prerequisite survey, 2026-10-26 (codexb)

Family B, shard 0/2. The runner queue authorizes DisconnectManager and
debug_io_ods; neither was HELD. Current parent-directory naming planners were
read, and their currency check passed before the respective investigation.
No source, row ownership, flag override, hatch or debt register was changed.

## DisconnectManager

`tu_skeleton.py --plan Code/GameEngine/Source/GameNetwork/DisconnectManager.cpp`
approves 39 ordinary rows in nine files plus one mixed donor. The ordinary
`--merge ... --dry-run` accepts none. Its seed's registered empty flag override
carries the default compiler optimization rather than the region's
`-O1 -arch:SSE -G7`; 31 main-donor rows and two constructor rows would be lost.
The remaining donors report no baseline match under that carried setting.
Receipt: build/sol-disconnect-before-trial-20261026.txt.

The unchanged seed passes `./build.sh`: 4/4 rows, one import; the four scoped
GameNetwork files also pass find_declared_unmatched. The supported read-only
scan
`flag_defaults.py generate sol-disconnect-default-20261026 --mode default
--sources build/sol-disconnect-sources-20261026.txt` confirms three seed rows
survive the region flags but processDisconnectKeepAlive (0x004D3CA8, 48 bytes)
does not. The normal object has `add esp,8` immediately after Rva004D39DEGet;
the region object compares first and uses two `pop ecx` instructions, making
47 bytes and shifting the resetPlayerTimeout call. This is an actual byte
requirement, not a stale override-count inference. No override was dropped or
per-function optimization hatch introduced. Declaration reconciliation is
still behind this boundary. Cross-family Common donors were left untouched.
The seed file and all four RVA claims were released after recording blocked.

## ODS debug output

`tu_skeleton.py --plan Code/Libraries/Source/debug/debug_io_ods.cpp` approves
four ordinary rows in two clean files plus one mixed factory. Its ordinary
dry-run rejects the clean constructor donor: the `_pch.h`/internal_io.h seed
view already has an inline constructor, conflicting with the separate donor
body. Receipt: build/sol-ods-before-trial-20261026.txt. All three scoped sources
pass find_declared_unmatched (existing emission-only markers retained).

Retail constructor 0x0003F380 stores base table VA 0x00BC0990 and derived table
VA 0x00BC09AC. Both have seven slots. The local constructor and factory views
declare only six. The derived native slots are recorded in
build/sol-ods-vtable-20261026.txt; the extra slot before Write is the rowed
0x0073B660 false helper, as in the prior debug_io_net handoff. Its native method
name and interface signature remain unresolved. Upstream Zero Hour's six-slot
interface is donor evidence and does not establish BFME 2's extra signature.
No speculative declaration or table binding was added, and no source claim
was retained. Removing duplicate constructors alone cannot establish a safe
composition with this interface mismatch.

Both blocked verdicts are in reverse/re_attempts.log. These read-only trials
provide no file reduction, debt retirement, recovered bytes or linked-byte
gain. No maintainer-only runner was invoked.

## Win32LocalFileSystem owner handoff

The allocated Win32Device destination's current in-memory plan approves 22
ordinary rows in four donors and four mixed files. Its parent-directory naming
planner was refreshed and checked. The Device wide-list donor passes the
frozen-file check. The older mechanical C2511 refusal is explained by current
declarations: Common/Rva006047F3Family.cpp's LocalFileSystem base has `_v7`,
while Win32LocalFileSystemGetFileListWide.cpp implements the const five-argument
UnicodeString overload at native slot 7 (0x006050B9, 619 bytes). Common's
FilenameList typedef is an AsciiString set; Device's same typedef names a
UnicodeString set. The raw-buffer wide overload at slot 15 is a separate API.

This requires the Common owner's interface/typedef reconciliation, preserving
both native overloads, the slot-7 table binding, comparator owner 0x00037B40
and existing comparator/set provider receipts. No Common source was claimed
or edited and no speculative declaration was added to Device to mask the
selected-view mismatch. The unchanged failed composition was not repeated.
Record blocked and release the two Device file claims. Receipt:
build/sol-localfs-plan-20261026.txt. This is an owner handoff, not an unblock.

## Win32DIKeyboard owner handoff

The allocated destination's current plan approves eight ordinary rows in two
files, with no mixed or refused donors. Its parent planner and currency check
pass, as do both frozen-file checks. One ordinary dry-run rejects the sole
worker: GameLogic/AI/DirectInputKeyboardOpen.cpp expects DI8Obj/DIDevObj pointers
with explicit `m_table` views, whereas the Device seed's same fields use
IDirectInput8/IDirectInputDevice8 virtual interfaces. The selected class gives
C2039 at the worker's `m_table` dereference. Receipt:
build/sol-keyboard-trial-20261026.txt.

The pointer offsets agree (0xE20/0xE24); that does not make the source interfaces
interchangeable. Reconcile the worker with the existing interface, or agree
on a shared complete interface with its GameLogic owner, preserving the
create-device/format/cooperative-level/property/acquire slots and current
data owners. No GameLogic source was claimed or edited. The Device destination
claim was released after the blocked verdict. No row, provider or debt gain
is claimed by this investigation.
