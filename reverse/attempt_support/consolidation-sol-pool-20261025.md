# Sol pool handoff, 2026-10-25

Seat codexb; GameNetwork, GameEngineDevice and Libraries. This pass made six
verified prerequisite commits, leaving compatible donors for the Luna seats.
No merge or split was applied. No existing source file was removed, no new
retail C++ byte was recovered and no code-identity key was retired. One private
GameInfo header was added. The owning Microsoft-header refresh removed three
queue rows covering seven private definitions.

Published commits:

- b33d9b8d64: Thread constructor declarations; seed plus constructor, four rows
  accepted by the normal merge dry run.
- 2dbcecac5e: SDK FreeConsole declaration; five destructor-unit rows exact.
- f772432ef4: standard placement operations; three factory/EH rows exact and
  seed plus destructor plus factory accepted, ten rows.
- b491a1bf77: mesh-model query declarations; seed plus assignment accepted,
  four rows. The geometry-unique donor still needs its buffer fields and
  placement-array/header environment reconciled.
- 1efc3f6a40: standard allocation declarations in the mesh assignment unit;
  three rows exact, four private definitions removed through the owner audit.

The publisher confirmed the first five commits landed. Commit 6e633a67b6 shares
the GameSlot view and is still held for batching at this handoff. Its two source
files verify 20/20 rows; the commit hook checked 47/47 dependent rows. The normal
GameSlot split trial now accepts the seed and nine carved rows (19 rows total),
preserving the one residual row. Leave that split to Luna. The same two existing
shadow code-identity findings remain; no new finding or identity retirement is
claimed. Details, EH/provider evidence and commands are in the four companion
consolidation-sol-{thread,debug,meshmdl,gameslot}-20261025.md handoffs.

The six prerequisite commits preserve 36 distinct existing ledger rows across
eight source files. Individual build.sh, declared-unmatched, data, EH and hook
checks passed as documented in those handoffs. The published push hook checked
42/42 rows across six sources. A DebugIOCon intermediate dry run exposed a
cache-dependent compile sentinel after accepting its composed body; the
recorded false reject was not worked around or patched here.

Additional read-only scoped investigations:

- Ghost: the current normal dry run still rejects the in-pool STL copy donor
  on __false_type/allocator redefinition and the Common stride-copy donor on
  vector redefinition. Replacing the private template system requires a real
  STL/header and provider reconciliation, not another unchanged merge.
- FirewallHelper: the completed normal dry run approves 37 rows across 14
  donor files but accepts none: the seed itself loses bytes under every merged
  flag set. Three mixed and five protected donors remain. The isolated packet
  pump shares the seed's packed message layout, but adding friendship alone
  would not address this measured flag/header composition boundary. No source
  was edited. Resolve that shared prerequisite before retrying individual
  donors; receipt build/sol-firewall-before.txt and a re_log.py blocked entry.
- DX8 polygon renderer: current routing approves the seed and both in-pool
  constructors, but the normal dry run rejects both constructors with MSVC 7.1
  C1001 at composed line 21. The legacy-header seed and constructor views with
  BFME 2 split-table fields need compiler-safe reconciliation. No source was
  edited; this blocker is recorded through re_log.py. Receipt:
  build/sol-dx8polygon-before.txt. The exact ICE cause was not isolated; the
  differing views alone do not establish its cause.
- PropDraw retains its Coord3D header/constructor ABI and addProp signature
  conflict; Font retains its broader FontLibrary/vtable and private-vector
  conflict. No speculative body or include change was left behind.
- TARGA and Profile normal trials already accept their available clean donors;
  leave those mechanical moves to the consolidation seats. PingThread and BIG
  were held by other seats and were not edited.

The active scoped planner/queue receipts are under build/consolidation/network,
build/consolidation/device and build/consolidation/libraries, and
build/sol-{network-queue-2,device-current-queue,wwvegas-current-queue}.txt.
Regenerate planner inputs after source/ledger changes; these receipts do not
approve any move.

The outgoing path audit covers the merge base of origin/master and HEAD plus
this staged handoff/log. There are no pending source moves or deletions, only
the new quoted GameInfoSlotView.h include beside both source files. Active
tools, hooks, workflows, includes, build inputs, registries and fold proofs need
no path repair; historical EA paths are retained. Incoming origin-only moves
are not this seat's unpublished work. No protected baseline or TU map changed.

Final progress.py origin/master: BYTE-MATCHED 100%, LINKING 98.01%, LINKED
95.38%, all deltas zero; census 2026-10-25 18:23 at ef9c691284. check_csv passes.
Keep the GameInfo.cpp, GameSlotCtor.cpp, GameInfoSlotView.h, GameSlot handoff,
this handoff and 0x003FF50C/0x003FFB4C claims until the runner confirms publication,
then release the scopes and settle the RVAs. No blocked body claim is held.
