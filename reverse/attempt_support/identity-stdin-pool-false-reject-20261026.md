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
