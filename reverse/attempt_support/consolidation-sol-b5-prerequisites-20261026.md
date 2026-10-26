# Sol B5 prerequisite session, 2026-10-26 follow-up

Model gpt-6.1-sol, medium; family B, deterministic shard 1/2. No merges,
source moves, identity retirements or recovered bytes in this session.

## Verified prerequisites, left for Luna

| Destination TU | Repair | Dry-run improvement | Commit |
| --- | --- | --- | --- |
| WW3D2/dx8webbrowser.cpp | Is_Browser_Open view includes seed's existing static declarations | 6 -> 9 compatible rows; 153 existing bytes | 0ad490306b |
| debug/debug_except.cpp | shared Debug view includes clipboard donor's existing virtual tail | 12 -> 13 compatible rows; 767 existing bytes | 934b02a29d |

These are demonstrated unblocks, not confirmed downstream Luna landings.
Full evidence, accepted files, remaining prerequisites and scoped bindings
are in consolidation-sol-b5-browser-20261026.md and
consolidation-sol-b5-except-20261026.md in this directory. Standalone builds
both 10/10 exact; external code definitions, COMDAT selections, undefined
sets, data facts and relocation bindings are unchanged (23 browser; 27
exception). Frozen/class/data/converged/allowed-symbol/EH checks passed.
Header commit hook reached 36/36 exact in two dependent sources, including
its conservative Eva include-graph dependent. Eva's cached actual dependency
list has no changed header; no Eva source or include was changed. MS-header
check passed; existing exception-struct conflicts remain in the audit queue.

Both commits are queued by /opt/runner/publish (threshold five commits or
45 minutes). Final handoff commit retries publication; runner publishes
leftovers after the session. Do not invoke publish separately. Keep the
claims below until these commits are confirmed on origin/master, then
release file scopes and run claims.py release --landed.

## Attempted and skipped tasks

Allocated runner queue was refreshed at end: build/sol-b5-final-queue.log.
All new targets passed --check-tu; no paired-seat targets were taken.

* Browser wrapper 0x001776A0: missing invoke trial reached competing
  BfmeObjECFPtr/Rva00958E30 versus Rva00958D30 BSTR types (C2664).
  Reverted trial, recorded updated evidence with re_log.py, released its
  unchanged cluster claim. Existing identity debt remains. Initialize is
  another worker's claim; Common mixed donors are cross-family.
* linegrp: --plan and ordinary --merge --dry-run accept no donors. Render
  requires registered -O2 -arch:SSE -G7 versus carried -G7; SetArrays requires
  -O2 -G7; destructor composed bytes fail. No flags, lifetime model or body
  changed. build/sol-b5-linegrp-{plan,before-trial}.log.
* udp: scoped planner, --plan and ordinary dry run accept no donors. Seed's
  canonical UDP header lacks old rva00594976/rva00594A06/rva00594B2E names
  and m_socket/m_err private view. NonBlocking and Broadcast rows overlap
  already-owned SetBlocking/AllowBroadcasts addresses. Identity/overlap
  reconciliation is prerequisite, not permission to append duplicate names.
  build/sol-b5-udp-{plan,before-trial}.log. No edit/claim acquired.
* debug_except: ExceptionFilter still needs Signature::Size/class view;
  Common RecordInitialize byte mismatch and mixed donors remain outside
  this repair. No repeated speculative attempt.
* Prior unchanged surface/htree/Prop/Apt/vertex prerequisites and blockers
  retain the inherited session handoff. All five inherited commits were
  confirmed landed; all fourteen inherited scope claims were released.
* MessageStream 0x00A00950 remains maintainer decision #116; untouched.

## Audit, progress and next session

Audited pending 0ad490306b..934b02a29d plus this index: no path moves,
deletions or changed build inputs. Incoming origin/master-only changes
visible in the two-dot diff are not this batch's moves. No active tooling,
hook, workflow, include, build input or registry needs repointing. Existing
ledgers/debt keys retain their sources; no protected register was edited.
No regenerated TU map, hatch growth or maintainer-only runner.

python3 tools/progress.py origin/master: BYTE-MATCHED 7,978,500 (100%);
LINKING 7,351,388 (97.85%); LINKED 7,596,747 (98.53%). All deltas zero.
File reduction = 0; identity debt retired = 0; recovered C++ bytes = 0.
The measured improvement is compatibility of four existing rows/920 bytes.

BFME1 official upstream was fetched and checked clean against pinned
ff391a5e versus upstream cbc06db8. Full reference-update verification remains
unfinished; preserve verified pin and do not fabricate a freshness receipt.

Outstanding own file scopes (publication bookkeeping only):

    file:Code/Libraries/Source/WWVegas/WWDebug/BfmeDebugExceptionView.h
    file:Code/Libraries/Source/WWVegas/WW3D2/dx8webbrowser.cpp
    file:Code/Libraries/Source/debug/debug_except.cpp
    file:reverse/attempt_support/consolidation-sol-b5-browser-20261026.md
    file:Code/Libraries/Source/WWVegas/WW3D2/DX8WebBrowserCreateBrowser.cpp
    file:reverse/attempt_support/consolidation-sol-b5-except-20261026.md
    file:Code/Libraries/Source/WWVegas/WW3D2/DX8WebBrowser_Is_Browser_Open.cpp
    file:reverse/attempt_support/consolidation-sol-b5-prerequisites-20261026.md
    file:Code/Libraries/Source/WWVegas/WWDebug/DebugCopyDialogReport.cpp

## Recovery verification, 08:34 UTC

The interrupted restart failed on model capacity before editing. Recovered
the three clean unpublished commits (7102f77dd4, 0dd7739680, this handoff).
Fresh pull/rebase and check_csv passed. Rechecked all four changed/direct
consumer sources with ./build.sh: 19/19 rows exact, 109 literals, 10 empty
strings and 12 imports; no compile required with current dependency receipts.
Both saved before/after object-proof scripts pass again: all external code
definitions, selected COMDATs, undefined sets, data facts and 23 browser /
27 exception relocation bindings remain equal. Frozen-file checks pass.
All nine publication scope claims renewed. Complete origin/master..HEAD
path audit still has no moves, deletions, changed build inputs or affected
path consumers. Publication retried with this amended handoff. Official
BFME1 now reports c0384c97 versus clean verified ff391a5e; preserve the
verified reference and unresolved full-update check without a success receipt.
