# GameNetwork consolidation handoff, 2026-10-25, codexb2

Scope: `Code/GameEngine/Source/GameNetwork/`. The current consolidation planner
and report check passed; the TU queue used the current in-memory routing because
the committed TU map is stale. `check_csv.py` passed after the upstream rebase.

## Verified changes

- `udp.cpp` absorbed two accepted donors; 13 matched rows remain. Fresh
  `./build.sh udp.cpp` and frozen-file scan passed.
- `IPEnumeration.cpp` absorbed three accepted donors; 7 matched rows remain.
  Fresh build and frozen-file scan passed; the three EH pins verified.
- The accepted split moved `NetCommandNode::detach` (RVA `0x0058B8AE`) from
  `NetCommandList.cpp` to `NetCommandRef.cpp`; both sides passed build and
  frozen-file checks, 8 rows total. Doxygen inputs retain both `htree.cpp` and
  `NetCommandRef.cpp` after the upstream rebase conflict resolution.

Across these accepted operations, three rows/sources were preserved, three
source files were removed and one was added: net two fewer source files. Fresh
checks covered 28 rows across changed TUs/sides. Commits currently in the
outgoing range are `d07fb8740c`, `56fb6ae40e`, and `f5b186f030`.

The combined active-path audit of `origin/master..HEAD` found no active
hard-coded consumers for absorbed paths. Remaining donor-path mentions are
provenance comments, historical census/attempt/name evidence and the explicit
Doxygen source entry. No tool, hook, workflow, include or build-input repair is
needed. No protected register was edited and the TU map was not regenerated or
staged. The staged handoff adds no source path change.

## Rejected or unresolved donors for Sol

Do not retry unchanged:

- `NetCommandWrapperList.cpp`: seed compile fails at
  `reference\shims\sweep\Common\MessageStream.h(92)` with
  `C2653: 'BfmePoolGlue' : is not a class or namespace name`.
- `NetCommandRef.cpp`: `NetCommandRefCtor.cpp` fails with C2511, constructor
  `NetCommandRef::NetCommandRef(NetCommandMsg *)` not found in `NetCommandRef`;
  `NetCommandRefContents.cpp` fails with C2039, `rva0058B8BA` is not a member
  of `NetCommandRef`, and C2065, `m_msg` undeclared.
- `GameSpy/LadderDefs.cpp`: seed compile fails in VS `cstdlib(20)` with C2039,
  `atoi` is not a member of the global namespace. Mixed donors are outside
  this seat's prefix, so no split was attempted.
- `NetCommandList.cpp`: ctor/deleter donors are refused because their
  path-keyed identities are protected; `NetCommandListAddMessage.cpp` fails
  with C2504, `NetCommandMsg` base class undefined.
- `GameSpy/GSConfig.cpp`: `Rva0054E84CBody.cpp` fails with C2065,
  `m_sentinel` undeclared. Mixed donors are outside the seat's split scope;
  protected donors remain untouched.
- `DisconnectManager.cpp`: the tool dry run accepted
  `Common/Rva004D376ACtor.cpp`, but the trial build had byte mismatches in the
  ctor and deleting dtor at RVA `0x004D376A`. The unverified trial was restored;
  no retry was made.
- `NetPacket.cpp`: its dry run remained blocked for over 16 minutes, with the
  Python process waiting on a pipe and a defunct `cl.exe` child. It was
  terminated without applying a merge. The temporary generated file was
  removed. This is a tool-run failure, not an accepted candidate result.

The planner's source report and `--check build/consolidation` passed before
these operations. Queue entries marked HELD were skipped. No link, smoke,
nightly or other maintainer-only lane was run.

The last `progress.py origin/master` reports the origin census at 2026-10-25
18:23 and `LINKED 95.38%`; this mechanical consolidation adds no recovered
bytes. The full audited outgoing range is `f7884d755d..851d0e9620`. It contains the
three verified source changes above and this handoff. `/opt/runner/publish`
held the four-commit batch for its 5-commit/45-minute threshold. Outstanding
accepted file claims are the four UDP donor files, the three IPEnumeration
donor files, and `NetCommandList.cpp` plus `NetCommandRef.cpp`, owned by
`yasinschroeder-codexb2`; their associated RVA claims remain held until landing.
The abandoned DisconnectManager file and RVA claims were released.
