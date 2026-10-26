# PingThread consolidation prerequisite, 2026-10-26

Seat: codexb5 (Sol medium), allocated family B shard 1/2. Inspected base:
`c85d92855d`; allocation: `/opt/runner/consolidation_queue.py --limit 20`.
Destination: `Code/GameEngine/Source/GameNetwork/GameSpy/Thread/PingThread.cpp`.
This is a declaration prerequisite, with no merge, row repoint or new recovery.

## Target facts and repair

The initial normal `tu_skeleton.py --merge TU --dry-run` accepted the seed
and WWLib/Rva005503B1Factory.cpp (16 rows). The startThreads donor failed
with C2370 for NumWorkerThreads; it also carried a minimal ThreadClass view
while the seed included Zero Hour's different thread.h view.

The seed and startThreads now declare the same BFME 2 ThreadClass prefix and
interface already used by WWLib/ThreadClassLifecycle.cpp: name +4, ID +44,
handle +48, priority +4C, size 0x50, and destructor/Execute/Thread_Function
virtual slots. The seed suppresses the foreign thread.h through its existing
guard, including its indirect inclusion through mutex.h. The startThreads
worker view replaces padding with that base and declares its virtual override.
The seed's worker array uses the same ThreadClass pointer type, and its mutex
and holder fields match the existing startThreads donor (+A8 and +B0).
The seed's PingThreadClass gains the +50 mutex pointer already used by the
matched Thread_Function donor. NumWorkerThreads uses the donor's exact int
spelling. No function body, compiler flags, pin, alias or shared header changes.

These layouts are existing BFME 2 reconstruction evidence, independently
constrained by the matched worker constructor at 0x0054F93F and thread base
constructor/lifecycle. Zero Hour is not asserted to prove the BFME 2 layout.
No canonical-class register entry exists for these two class names.

## Verification

Commands below use TU = PingThread.cpp and donors in the same Thread directory.
Receipts remain local under build/sol-b5-ping-*.

The final ordinary merge dry-run accepts seed, startThreads and
WWLib/Rva005503B1Factory.cpp: **three files / 20 rows**, versus two / 16
before. This demonstrates the startThreads unblock; Luna has not yet landed
the merge. Receipts: build/sol-b5-ping-before.txt and
build/sol-b5-ping-after.txt. The Thread_Function rejection now reports only
GameMemory::free, removing the earlier missing m_runMutex prerequisite.

- Before and after `./build.sh TU PingThread_Pinger_startThreads.cpp
  PingThread_PingThreadClass_Thread_Function.cpp`: 22/22 rows, four literals,
  eight imports; no mismatches. `find_declared_unmatched.py` passes all three.
- `class_gate.py TU PingThread_Pinger_startThreads.cpp`: passes.
- `eh_verify.py` on all three: EXACT 5, no baseline exceptions or missing objects.
  The two startThreads cleanup labels renumber from $L385/$L384 to $L394/$L393;
  build.py identifies each by its exact parent's EH placement and bytes.
- `code_identity_gate.check` on the three sources: no problems or notes before
  or after (shadow mode), including its scoped selected-COMDAT definition check.
  Raw allowed_symbols omits the two renumbered local-label rows after the edit.
  Resolving those labels with build.located_funclet before scanning recovers
  exactly the same 60 reference tuples as before: owner 41, fold 10, EH 5,
  alias 4. No changed code target or wrong binding is concealed by that count.
- Scoped data shadow: three sources, zero findings. Converged data: ten
  addresses, no second or unjudged binding. No data/code-identity/header debt
  key belongs to the edited sources; other PingThread debt is left in place.
- `check_csv.py`: 98,252 function rows, 15,683 symbols, 2,215 data rows, OK.
  `git diff --check` passes.
- Read-only `ms_header_audit.py scan` on the three sources: three scanned,
  zero analysis failures, two conflicting files (the existing ICMP/Windows
  constants/prototypes and GameMemory::free). Those declarations and their
  queue entries are unchanged; no Microsoft-header cleanup is claimed.

## Remaining work and audit

The Thread_Function donor independently needs its throwing GameMemory::free
declaration to precede the allocator includes after composition. The normal
composer hoists its macro before its namespace declaration. The cleanup donor
under Common has a StringBase redefinition (cross-family handoff); the WWLib
Rva0055011A00550041 donor specializes basic_string's destructor after use.
Mixed sources and protected-register donors require their separate lanes.

No source path changes occur in this prerequisite or the inherited published
batch. The prepublication path audit covers the unpublished range plus staged
changes; no tool, hook, workflow, include, build input, registry or historical
EA path needs repointing. No protected register is edited or key retired.
File reduction, identity debt retired and newly recovered C++ bytes are each
zero. A successful dry-run is not a confirmed Luna landing or census change.

Other read-only trial: W3DGhostObject's ordinary merge accepts no files;
the STL donor has duplicate _STL::__false_type and a Common donor duplicates
vector. Its scene split still refuses increased hatch counts, as already
recorded in consolidation-split-device-20261025.md. No claim or edit there.

Inherited commits through 82645feee3 are already on origin/master; their stale
file/RVA claims were released at session start. The BFME 1 official-upstream
check found local clean c0385ef6 versus official 3de5959c; full reference-update
verification remains pending and no freshness success receipt was fabricated.

## Follow-up: allocator declaration ordering

The remaining worker-loop compile error has a local prefix-header trial.
PingThreadMemoryPrefix.h contains the donor's unchanged stdlib include,
throwing C-linkage GameMemory::free declaration and free macro together.
Both the seed and worker-loop donor include it before STL headers, so the
composer cannot hoist the macro ahead of its declaration or instantiate the
seed's allocators with a different declaration. This follows the already
landed local BfmeLadderStringPrefix.h composition prerequisite; no shared shim
or compiler flag is changed.

`./build.sh` on seed, startThreads and Thread_Function again verifies 22/22
rows, four literals and eight imports. Frozen checks pass the changed sources
and header. Saved pre-edit objects compared with allowed_symbols._object_defs
show **263 external code definitions unchanged** (248 seed, one startThreads,
14 worker loop), including their digests, sizes and COMDAT selection kinds.
All three objects' undefined-symbol sets are unchanged. Paths and link order
are unchanged, preserving selected code providers for external consumers.
Parent-EH-normalized scanning again gives the identical 60 binding tuples.
Receipts: build/sol-b5-ping-prefix-build.txt, prefix-before/*.obj and
prefix-proof.json. `eh_verify.py` on all three sources reports EXACT 5, no
exceptions or missing objects (build/sol-b5-ping-prefix-eh.txt).

The raw shadow code-identity report has one false positive: its old $L33627
pin now reads the preceding PingRequest cleanup when scanning
Unwind@00b988e4, reporting a wrong destructor at 0x00613AC0. The exact parent
EH graph places that row at $L33628; all five funclets are identified by the
normal byte verifier. This is recorded with re_log.py as a false-reject
diagnostic, explicitly noting that shadow reporting is not an enforcement
rejection. No checker, baseline, pin or ledger identity is changed to suppress
the finding. A tooling owner should make identity scanning use the same exact
parent-EH placement as the byte verifier, in a separate tested repair.

The follow-up publication audit includes the pending first prerequisite
(`3d502b66bf`, based on c85d92855d) and this staged change. There are no
source moves or deleted paths. The one new private header has exactly two
active source consumers (seed and Thread_Function), confirmed by repository
search and both compiled dependency receipts. Both consumers were rebuilt
together. No tool, hook, workflow, build input or path-keyed register requires
repointing; historical EA paths remain unchanged. Header count rises by one;
source-file reduction, debt retired and recovered bytes remain zero.

## Publication and claims

The first prerequisite was committed as 3d502b66bf; the publisher initially
retained it for batching. At this handoff's preparation, the pending range
is c85d92855d..HEAD plus the follow-up staged changes audited above. If the
runner still holds either commit, retain the following file claims until the
runner confirms publication, then release them and settle landed RVAs:

- Code/GameEngine/Source/GameNetwork/GameSpy/Thread/PingThread.cpp
- Code/GameEngine/Source/GameNetwork/GameSpy/Thread/PingThread_Pinger_startThreads.cpp
- Code/GameEngine/Source/GameNetwork/GameSpy/Thread/PingThread_PingThreadClass_Thread_Function.cpp
- Code/GameEngine/Source/GameNetwork/GameSpy/Thread/PingThreadMemoryPrefix.h
- reverse/attempt_support/consolidation-sol-b5-ping-20261026.md

All are held by yasinschroeder-codexb5. No inherited claims remain. Final
publication status and any rebased commit IDs are in the runner's session
metadata. No Luna merge or census improvement is claimed by this seat.

## Final normal composition result

`python3 tools/tu_skeleton.py --merge TU --dry-run` completes successfully
(build/sol-b5-ping-prefix-after.txt). It still accepts exactly seed,
startThreads and WWLib/Rva005503B1Factory.cpp: three files / 20 rows.
The worker-loop donor now compiles in the normal merger; its rejection is
`bytes`, replacing the earlier GameMemory::free compile diagnostic. The
normal report does not localize which row in that combined trial mismatches.
This is a demonstrated compile prerequisite repair, **not** a further
accepted-row increase. The net demonstrated acceptance gain this session is
four rows from the first declaration repair. No merge was applied.

The remaining combined-byte blocker for Thread_Function at 0x005501F4
(extent 400) is recorded through re_log.py. A later owner should investigate
merged compiler/header/template context with the supported scoped verifier;
standalone source remains fully byte-exact. The Common StringBase and
WWLib basic_string specialization compile blockers are unchanged.

The ordinary search took roughly 52 minutes on the container's 0.14 CPU
quota. It was polled to completion without duplicate launch. Ghost's
unchanged blocker was inspected separately; no further target is opened
at the end of this session. AptCIH is now allocated but was not attempted.
