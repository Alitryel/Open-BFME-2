# Git batch transport repair — 2026-10-20

Large ledger and link-preview checks stalled on this Mac with Python 3.14 and 3.12. Process samples showed the Python parent writing requests while Git was writing replies; both were blocked on their bounded pipes. Switching Python versions did not reliably resolve the issue.

The two affected readers now give Git regular temporary files for stdin, stdout and stderr, following the existing `shadow_budget.py` transport precedent. They read captured output before reconstructing the same `CompletedProcess`. The request bytes, command, working directory, return code, stdout/stderr, parser loops, error types and validation decisions are unchanged. In particular, the existing final short-body slice behavior remains unchanged and has an explicit parity test.

Independent checks pass under Python 3.12.14 and 3.14.3: 20 transport regressions and all 21 concrete gate-exploit refusals per runtime, both real staged ledger checks, and 844 old/new parser differential cases. The only exploit-suite skip is an empty fixture parameter set, also empty at the base revision. The previously stalled two-source `link_check.py` preview completes under Python 3.14 in 10.13 seconds, with both units link-clean and unchanged 1,152-byte accounting.

Broader optional tests found five existing failures: four progress tests (three unavailable historical Git revisions and an existing source-lane expectation), and one empty-data-ledger orphan expectation. Each failure was independently reproduced against the unchanged original tool outside the repository; the logs are retained here. These failures are not repaired in this transport-only change.

The frozen hashes, independent reviews, exact commands and limits are recorded in `proof.json` and the accompanying reports. No game source, header, ledger, compiler flags, baseline or validation predicate changed. This repair claims no newly recovered or linked bytes and no successful full-engine baseline. Normal commit and publication hooks remain required.
