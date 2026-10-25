# GameNetwork PingThread consolidation follow-up, 2026-10-25

The refreshed plan and `tools/tu_skeleton.py --merge` accepted PingThread's
seed plus four donors: `PingThread_Pinger_areThreadsRunning.cpp`,
`PingThread_Pinger_getRequest.cpp`, `StlportDequePod16Dtor.cpp`, and
`StlportNarrowRecord0054FEF1DequeAux.cpp`. Commit `667c27ef7f` moves 13
approved rows into `PingThread.cpp`; its build verifies 13/13, the declared
check is clean, and EH verifies three rows exactly. The Microsoft-header report
was refreshed by the merge tool. No new matched bytes are claimed.

One unchanged donor was rejected by the merge trial:
`Code/Libraries/Source/WWVegas/WWLib/Rva0055011A00550041.cpp` fails with MSVC
C2908 because the explicit `_STL::basic_string<_CharT,_Traits,_Alloc>`
destructor specialization has already been instantiated. Its required STL
prerequisite is outside this seat's mechanical lane; leave the donor unchanged
for Sol. Three other donors remain refused because their source paths are keyed
in protected path registers. No register was edited by hand.

The complete path-change audit covered the staged PingThread merge and the
outgoing `origin/master..HEAD` range. Active ledger and Microsoft-header rows
were repointed by the owning merge tool. No active tool, hook, workflow,
include, or build input consumes the absorbed paths; remaining matches are
historical link records, attempt evidence, and source comments. The publish
runner is batching commit `667c27ef7f`; its TU/file/RVA claims remain held until
publication is confirmed.

## Remaining mixed split checks

The scoped queue and current plans were rechecked after the merge. The in-scope
mixed donors inspected for FirewallHelper, DisconnectManager,
GameResultsThread, PingThread and IPEnumeration were whole donors, so split
refused with `no row would remain in the file: it is a whole donor, use
--merge`. `NATUpdateBfme.cpp` had eight carved candidates but split refused
because a namespace/`extern "C"` block defines something. BuddyThread's
`BuddyThreadCallbacks.cpp` and `BuddyThread_Unresolved.cpp` hit the same block
refusal; the callbacks file also has data-identity key `g_rva00627AA0`, and the
unresolved file has row `0x0055197E` with no definition spelling its name.

`GameSlotCtor.cpp` was the only trial with rows remaining on both sides: two
rows carved, one retained, and all nine carved byte rows matched alone under
TU flags. The merge compile rejected it with C3861 (`reset` not found) and
C2039 (`reset` is not a member of `GameSlot`). Resolving that view is outside
the mechanical seat. No split was applied, and all remaining work is either a
whole-donor merge prerequisite, a protected register, or a declaration/data
repair for Sol.
