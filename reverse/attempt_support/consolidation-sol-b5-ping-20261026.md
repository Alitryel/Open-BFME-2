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
