# Windows debt-verdict worker bootstrap failure

The normal push of `ae510bb7b4` failed before its outgoing byte gate. The
pre-push hook runs the selected historical repair_queue.py through
`python3 - verify-removed --range ...`. A code-identity verdict calls
allowed_symbols.definitions with more than 64 uncached objects and
BUILD_POOL=8. ProcessPoolExecutor starts workers with Windows spawn, which
tries to reopen the parent's `__main__.__file__`, `<stdin>`. No such source
file exists: OSError 22 is followed by BrokenProcessPool and the hook's
"retired debt has no passing outgoing verdict" refusal.

This is a checker execution failure, not a wrong-binding verdict. The
normal source/header gates have already passed and no retirement is excused.
All ledger objects exist and the INI provider is current, so this is distinct
from the earlier missing-cache refusal. The failed process has exited;
it was not interrupted or duplicated. The publication has not succeeded.

Reproduce with a stdin-driven Python process, the spawn start method,
BUILD_POOL greater than one and at least 65 uncached real COFF objects.
Use an isolated definitions-cache directory so the regression does not
depend on, remove or prepopulate the shared verifier cache. Include a
malformed-object control that must still raise Unreadable in strict mode.

The fix must preserve every definition, referrer, link-order and strict
parse check. It belongs in a separate verifier commit with a regression
test and Verifier-Change trailer; no baseline or game-source edit is needed.
Python's documented process-pool requirement is an importable __main__:
https://docs.python.org/3/library/concurrent.futures.html#processpoolexecutor

Local receipt: `build/codex-cleanup-20261025/iteration39-push.log`.
The next game candidate, StlSweepR3Rva005243FA.cpp, has been claimed but not
edited while this publication prerequisite is investigated.

## Separate checker repair

The regression uses 65 real, temporary COFF objects with a defined function
and an undefined callee. It forces spawn and runs both through stdin and
from an ordinary script file, with a separate malformed-object variant.
Before the fix, the two stdin cases fail with the same OSError 22 and
BrokenProcessPool; both file-entry controls pass. After the fix all four
pass, including strict rejection of the malformed object. Definition order,
digests, extents, exclusivity, referrers and cache rereads are checked.

definitions() now chooses a thread pool when __main__ has no actual script
file. Normal file-based CLI execution retains the process pool. Both use
the identical _object_defs parser, ordered map and strict Unreadable check;
no exception is caught to produce a passing verdict. Cache writes remain
sequential after all workers return. Independent review confirms the worker
and its parser helpers use local state.

The combined code-identity, library-source, repair-queue and gate-exploit
suites pass 325 tests. The sole skip is the empty parametrized promoted
audit-escape set: this checkout contains zero JSON fixtures in
tools/tests/fixtures/audit_escapes. All available exploit cases run and pass.
Receipts: `iteration40-spawn-red.log`, `iteration40-spawn-green.log` and
`iteration40-verifier-tests.log`. The next normal push is still required
to confirm the complete publication path; no publication success is assumed.
