# GameNetwork consolidation, 2026-10-25

Seat: yasinschroeder-codexb2. Destination scope:
`Code/GameEngine/Source/GameNetwork/`. This is consolidation; no newly recovered
C++ bytes or new linked/ownership census result is claimed.

## Verified batch

| TU | absorbed fragments | rows | retail bytes preserved | net files removed |
| --- | ---: | ---: | ---: | ---: |
| FrameDataManager.cpp | 3 | 3 | 169 | 2 |
| GameInfo.cpp | 4 | 6 | 223 | 3 |
| NAT.cpp | 2 | 4 | 291 | 1 |

The commits are `4dd09834e4`, `400c939521`, `790a789c2f` before any publisher
rebase. Each applied merge used `tools/tu_skeleton.py --merge`, normal claims,
current in-memory routing, `./build.sh TU`, declared-unmatched, ledger, EH and
normal commit checks. Every moved row was approved in the current routing;
`reverse/tu_map.csv` was not regenerated (only existing source fields repointed).
All 13 rows and 683 retail bytes remain matched.

GameInfo's normal hook reports two **shadow** code-identity findings: divergent
STL map/tree `end()` COMDAT definitions. It passed the enforced gates; this is
not an identity-debt retirement. Other two merges reported zero new identity
findings. Existing inline anchors in GameInfo were retained from its donors.

## Path-consumer audit

Reviewed the complete pending moves from base `91fe970939` through the three
merge commits against active tools, hooks, workflows, source/header includes,
build inputs, registries and documentation. Recursive source discovery needs no
new explicit entry. Updated the current FrameDataManager path in
`docs/bfme2-network-timing-path.md`. Remaining old-path mentions are fragment
provenance comments, class names, historical link census, attempt evidence and
landed attempt receipts. They are retained as history, not compiler receipts
for the new paths. Generated planner snapshots must be regenerated after edits;
never scan while a merge trial has a temporary source under Code/.

## Remaining scoped queue and prerequisites

* FirewallHelper: dry-run accepted no combination; 10 mixed files and two
  protected-register donors remain. Tool reported no detailed rejection for
  the remaining combinations. No donor was edited or manually split.
* DisconnectManager: dry-run compiled an apparent four-file subset, but it
  included Rva004D376ACtor.cpp's 0x004D376A constructor and 0x004D381B destructor
  which current routing marks **proposed**, not approved. Only its deleting
  destructor 0x004D3C8B is approved. Do not apply that merge: current donor
  selection admits collateral same-TU rows below approved confidence. The
  processDisconnectPlayer/Command candidates also changed bytes. No merge
  applied; routing/selection prerequisite needs a tooling seat.
* GameResultsThread: no accepted combination. `_Deque_iterator_base` duplicate
  template definitions (C2953) block four donors; three Common narrow-string
  donors have no baseline match. Other files mix TU owners. Canonical STL view
  prerequisites span sources outside this destination scope.
* GameInfo: remaining isolated donors fail on incompatible GameInfo/GameSlot
  member views (C2039/C2065) or duplicate SlotState enumerators (C2365).
  Representative verdicts recorded with re_log.py; rejected donor scopes and
  RVAs released. Mixed and protected-register files remain intact.
* NAT: remaining donors fail on missing or inconsistent PortNegotiationSchema
  and NAT member declarations. These donors are in Common/, outside the seat's
  prerequisite-edit scope. Representative verdicts recorded with re_log.py;
  rejected donor scopes and RVAs released. Mixed/protected files remain intact.
* PingThread: dry-run verifies a five-row subset with the seed, pod20 init-map
  and Rva00550083Ctor fragments. Other candidates fail on GetProcAddress's
  FARPROC return type or duplicate placement new[] bodies. Refresh the Microsoft
  header report when the seed changes; do not edit the protected-register files.
* IPEnumeration: GetMachineName alone is accepted (no net removal). Runtime's
  private WSAStartup signature conflicts and its class destructor is absent
  from the selected view. Needs a verified in-scope declaration prerequisite.
* Connection: seed + constructor verified 3/3 rows (123 bytes), declared check,
  ledger and EH, but reverted pending a reliable Microsoft-header report refresh.
  The optional audit scan failed under default Linux Wine setup. Verified patch
  is local scratch `build/connection-verified-merge.patch`; re-run the current
  planner and merge tool rather than applying the patch. Claims were released.

## Microsoft header audit environment

Default `ms_header_audit.run_cl_e` on this Linux seat returned false with empty
output until WINEPATH was set using build.compiler_environment. Then MSVC
reported D2021 for the absolute Unix temporary-source path. A local untracked
wrapper in `build/msheader-env/wine` uses the same `/usr/bin/wine` and compiler,
converts INCLUDE entries and the temporary input filename to Windows Z: paths,
and normalizes only preprocessor line-directive paths back to Unix so the
owning audit recognizes header locations. The windows.h probe succeeds with
3,384 recognized header directives. No tracked gate/tool was modified. The
refresh driver is `build/refresh-network-ms-header.py`; output is scoped to
ignored build/ reports, not the entire tracked queue. Preserve unrelated queue
rows if integrating scoped results through the owning writer.

## UDP destructor prerequisite

UDPDrainDestructor.cpp now uses the same headers and compiler environment as
udp.cpp. Its 69-byte body and all three named imports verify unchanged. The
only retained TU-local SDK declaration is shutdown (absent from the sweep
Winsock shim); the owning SDK audit classifies it same. The refreshed scoped
queue has one definition instead of four. Its aggregate class is conflicting
because static transitive-include analysis reports 863 closure findings,
including inactive Unix socket headers; this is not a proven retail ABI
regression or debt retirement. The actual Windows build passes. The owning
writer generated the row under build/ and only that row replaced its former
entry in the tracked queue; unrelated entries are unchanged. The new dry-run
accepts udp.cpp plus this destructor (11 rows); all other UDP donors still
fail on private member declarations or sendto C-linkage signatures.

## Applied UDP merge and expanded batch audit

After the separate destructor prerequisite, the normal merge tool absorbed it
into udp.cpp. All 11 rows (738 retail bytes) pass the byte gate, 24 named import
references, declared-unmatched and EH (zero missing objects). One source file
was removed and one 69-byte row repointed. This brings the batch to four TUs,
seven net files removed, 14 repointed rows (752 bytes), with 24 affected TU rows
(1,421 bytes) verified. Existing UDP seed rows are not recovered bytes.

The stale committed map still shows UDPDrain as proposed, but the current
in-memory routing approved udp.cpp for every moved row. Only the source column
was repointed; no map regeneration was committed. The refreshed SDK report now
names udp.cpp with the same classification. Audited all four pending moves plus
the SDK-report consumer: no active tool/hook/workflow/include/build input loads
the deleted destructor path. Retained historical census and fragment provenance.
The SDK index passes its owning `index --validate` check (223,085 names from
954 headers). UDP's nonblocking and broadcast placeholder rows share addresses
with existing real seed rows: they are existing alias cleanup, not missing-body
regressions. Rejected scopes were released; accepted-row claims remain until
publication, including any shared RVA also represented by a rejected alias.

## Connection blocker cleared

With the SDK audit invocation repaired locally, reran the current planner,
plan and dry-run, then applied seed + ConnectionCtor through the normal merge
tool. All three approved rows (123 bytes) match; named imports,
declared-unmatched and EH pass with zero missing objects. Refreshed both prior
queue entries into one owner-generated Connection.cpp row: two local SDK
names are classified same, with the pre-existing collision advisory retained.
The earlier reverted attempt above is history; its report-refresh prerequisite
is now cleared. Net one source file removed, one 90-byte row repointed.

The combined five-TU batch audit adds ConnectionCtor to the four earlier
moves. Only the generated SDK queue required a current-path update; other
mentions are provenance, historical census, or unrelated LivingWorld names.
UDP's merge hook also reports two shadow identity findings for its retained
htonl/htons import aliases (unreferenced directives). All 11 rows and 24 named
imports pass; no new alias or baseline exemption was added.

## Applied PingThread subset

The refreshed planner, current routing and merge trial approve the seed plus
stlport_deque_pod20_initmap and Rva00550083Ctor. The normal merge tool absorbs
the two fragments, repoints four rows (268 bytes), and preserves all five TU
rows (502 bytes). ./build.sh verifies 5/5, four string literals and three named
imports; declared-unmatched and EH pass with zero missing objects. The SDK
owner regenerates the seed report with its unchanged eight-name classification;
its new STL includes add three static closure findings, retained as reported.
GetProcAddress and placement-new rejected donors remain unchanged, with verdicts
recorded and their scopes/RVAs released.

The six-TU batch now removes ten net source files and repoints 19 matched rows
(1,110 bytes), preserving 32 affected TU rows (2,046 bytes). These are existing
matched bytes, not new recovery. Current in-memory routing approves all moved
rows, including 0x0054FD6F whose committed source column was already stale; only
source-column repoints emitted by the merge tool are committed. The complete outgoing range from 91fe970939 through
f14b826293 plus this staged merge was audited against freshly fetched upstream
4e835ab16a. No active tools, hooks, workflows, includes or root build scripts
reference the deleted paths; current ledger/report paths are repaired. Remaining
mentions are fragment provenance, historical census and attempt evidence. The
Microsoft queue consumer still selects the new PingThread.cpp row. Accepted
file/RVA claims stay held until a confirmed push; publication cooldowns have
held the preceding commits locally so far.
