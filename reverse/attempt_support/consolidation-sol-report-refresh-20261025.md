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

## Font SDK prerequisite cleared

`Code/Libraries/Source/WWVegas/WWLib/Rva00090034SimpleVecDtors.cpp` now includes
`<new>` instead of privately declaring array delete. Its four existing rows
remain byte-exact, including both scalar deleting destructors; frozen-file
checking passes. The current SDK scan reports no local declarations and no
analysis error. `ms_header_audit.refresh_queue` removes precisely this source's
obsolete operator-delete report row. No identity key is retired.

This clears the dangling Microsoft-header report prerequisite recorded by the
Device mechanical seat for this donor. The normal Font trial accepts the seed
and both eligible donors, preserving six rows with no rejection. Receipt:
build/sol-font-after-sdk.txt. This subset is ready for the mechanical seat.
BIG's separate sprintf report on the Common init donor and Laser's game-free
ABI report remain; the BIG declaration repair above does not clear that report.

## BuddyThread composer false rejection

The fresh Network planner succeeds after the compiler trial has ended. A normal
BuddyThread trial accepts nothing. Composing the unchanged seed alone under
all four strategies drops the semicolon after `static enum CallbackType`,
yielding C2628/C2561 at callbackWrapper. The tracked declaration ends in `};`.
This is another declaration-chunking reproducer for the existing tooling owner,
not a source regression. No source was changed. Scratch receipts are
build/sol-buddy-{first,union-first,union-longest,longest}.cpp. The false rejection
is recorded at 0x00551FB3; its body and automatic file claim were released.

The fresh Libraries plan/trial still accepts the previously repaired nine-file
debug-exception subset; its one byte rejection is the unchanged Common record
initializer outside this seat. That ready subset remains for the mechanical
seat. No source paths move anywhere in this prerequisite batch; the combined
outgoing and staged path audit needs no consumer updates. Inherited naming
vote/agreement edits remain unstaged and untouched.

## Laser SDK prerequisite cleared

`Code/Libraries/Source/WWVegas/WW3D2/RefCountPtrTextureRva000C9A51.cpp` now uses
`<stdlib.h>` with `/D_CRTIMP=`. Retail calls the existing game `_free` wrapper
at 0x00030830, not the CRT import; that wrapper is already owned by
Common/System/GameMemoryFree.cpp. The configuration preserves this direct
call while taking the prototype from the real header. No alias, pin or new
allocator name is introduced.

`./build.sh` preserves the complete 30-byte cleanup at 0x000C9A51 and its zero
import count. Frozen-file checking passes. A fresh SDK scan reports no local
declarations or analysis error; the owning refresh_queue writer removes only
this source's old free:abi report row. This supersedes the outstanding Laser
report blocker above. BIG's sprintf report still remains.

The normal Laser dry run accepts four files / five rows: buildFieldParse,
xfer/loadPostProcess, this cleanup and the module-data constructor. The two
range/vector donors have no baseline match and remain untouched. Receipt:
build/sol-laser-after-sdk.txt. The ready subset is left for Luna. No source
paths move in this commit or its pending predecessors, so the combined audit
again requires no path-consumer changes. File reduction and identity retirement
remain zero for these prerequisite repairs.

## Laser range include prerequisite cleared

`RefCountPtrTextureDestroyRange.cpp` now resolves the existing BFME streak
`ref_ptr.h` through its include directory, rather than a source-relative path
that fails after placement beside W3DLaserDraw.cpp. It also uses the existing
`__PLACEMENT_VEC_NEW_INLINE` integration setting beside the include: always.h
owns array placement new/delete, while the module-data donor includes `<new>`.
Keeping this setting in the source preserves it when the composer chooses
another donor's compiler flags. No shared header or template layout changed.

Acceptance: the complete 25-byte row at 0x000C99F9 is byte-exact under
`./build.sh`, the frozen-file check passes, and the normal Laser dry run now
accepts five files / six rows, retaining all four files / five rows accepted
before this repair. Receipt: build/sol-laser-after-range-source-new.txt. Leave
this expanded subset for the mechanical seat.

The remaining Common Rva000C9A12VectorDtor.cpp rejection is independently
reproduced as C1083: its source-relative `ref_ptr.h` path cannot resolve from the
Laser destination directory. That source is outside this pool; no edit or claim
was taken. Scratch reproducer: build/sol-laser-vector-diagnose.py. The normal
trial reports only this clean donor rejected, as `no baseline match`.

Batch consumer audit: the outgoing merge-base range b439739e42..274ecc6c41 plus
this staged prerequisite contains no source moves or deletions, so tools,
hooks, workflows, includes, build inputs and registries need no path repoints.
The double-dot comparison against fetched origin/master (e9a1ead7b2) also shows
an incoming-only handoff; it is not a deletion in this batch. Existing EA path
strings remain intact. No files were removed and no identity debt was retired.
