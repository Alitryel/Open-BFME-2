# Sol consolidation prerequisites: SDK reports and WaterTracks

Seat: codexb (GameNetwork, GameEngineDevice, Libraries), 2026-10-25.

## Scoped Microsoft-header report refresh

The previous published declaration repairs are byte-exact under the current
compiler: `./build.sh` on GameNetwork/GameSpy/Thread/PingThread.cpp,
GameNetwork/Rva00594C12Write.cpp and GameNetwork/IPEnumerationRuntime.cpp
passes all seven rows, four string literals and eight imports. Frozen-file
checks pass. Paths above are relative to Code/GameEngine/Source/.

Current `ms_header_audit` successfully constructs its real VC 7.1 / Platform SDK
index under Wine; the old Linux failure is no longer reproduced. Scanned these
three existing files, asserted each result was present and had no analysis error,
then called its `refresh_queue` writer. PingThread and UDP Write now have no
local Microsoft declarations; their stale report entries are removed.
IPEnumerationRuntime retains WSACleanup (unknown to this configuration) and
operator delete (same); its obsolete WSADATA ABI conflict is gone. No unrelated
report lines were changed. This refresh does not retire code-identity keys.

Acceptance: three report refresh / queue tests pass. The broader audit test
module has 44 passes and two pre-existing failures on this Linux checkout:
`test_extra_root_arguments` (Windows absolute path handling) and
`test_included_project_headers_are_inspected` (gets classification). No tool or
check was changed. Source consumers and ledger paths remain unchanged; outgoing
path audit against origin/master and the staged report finds no moved sources.

Luna can retry the normal PingThread and UDP merge lanes with current reports;
remaining private class / string-specialization prerequisites from the earlier
handoffs remain. IPEnumeration still needs resulting-TU classification before
its final report can be removed.

## WaterTracks composer false rejection (not a source regression)

Normal W3DWaterTracks.cpp trial accepts nothing. Composing the unchanged seed
alone with each of union-first, union-longest, first and longest fails C2144 and
C1004 at rotateInit. `chunks` treats `waveInfo waveTypeInfo[6] = { ... }` as a
function body and emits its semicolon as a separate declaration. The composer
hoists that semicolon before the initializer, leaving the table unterminated.
The tracked seed has its semicolon. No WaterTracks source was changed. Scratch
receipts: build/sol-water-{first,union-first,union-longest,longest}.cpp.

Recorded `false-reject tu_skeleton` against 0x000FE359 in re_attempts.log.
Tool and test files are held by the Common Sol seat for conditional-block and
pragma preservation; do not compete for them. A chunker regression should keep
braced initializers and their semicolons in one declaration, without treating
functions as declarations. WaterTracks file/constructor/init claims released.

No files consolidated or identity keys retired by this report refresh.

## BIG lookup-result donor repaired

`Code/Libraries/Source/WWVegas/WWLib/Rva00603CA3Finish.cpp` no longer declares
unused STL map aliases, a comparator, or receiver data fields. Its caller only
needs the existing lookup member, so it now uses the minimal public class view
also used by Rva00603C5F.cpp. No receiver layout was inferred or changed.

Acceptance: `./build.sh` passes its sole 95-byte row at 0x00603CA3; the frozen-file
check passes. The normal Win32BIGFileSystem.cpp merge dry run improves from five
accepted donors / 11 matched rows to six donors / 12 rows, with no rejected clean
donors. Scratch reports: build/sol-big-before.txt and build/sol-big-after.txt.
Luna can apply that six-donor merge through tu_skeleton. Mixed/protected donors
remain outside that acceptance scope. This prerequisite commit removes no files
and retires no identity debt. No source paths move in the outgoing batch, so the
consumer audit requires no path updates.
