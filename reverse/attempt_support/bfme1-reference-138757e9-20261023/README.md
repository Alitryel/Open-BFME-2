# BFME 1 reference freshness: 138757e9

Controlled update from verified pointer
`f36a4db066aa61edeee90085a31d628eb829001d` to official master
`138757e9b74645fbcbb7724a7af2764e34931e11` at BFME 2 input HEAD
`158fdb4fe5f2f516d465e0cbfa6f5f4f3a127373`.

This is the prerequisite freshness check for the continuing 0x758DE0
assignment, not a change to its source, compiler or flags. The submodule
started clean at the verified pointer. This seat acquired the shared update
lock before fetching official master and preserved the old pointer for the
comparison. The four new commits change 16 game C++ files and five evidence
or ledger files; no headers, toolchain inputs or layout changed.

Both pointers passed `./build.sh` in full (`old-gate.txt`, `new-gate.txt`).
Each verified all 98,101 function rows, 2,139 data rows, literal/import
references, relocation names, pins, source claims and the no-op patch.
No update regressions or pre-existing failures were found. Both runs use
the same BFME 2 production sources and valid dependency caches.
The old run refreshed 610 stale objects; the new run reported all 23,421
translation units current. The clean new pointer is staged for the same commit as this evidence.

Resolved upstream game, inputs and ledger directories, the lift-lane tool,
Vector3 header and compiler DLL were checked to exist (`inputs.json`). No
layout migration or silent include substitution was needed.

`python3 tools/bfme1_sweep.py scan` refreshed the ignored donor cache at the
new donor revision. Its control check passed: 5,515 placements reproduce
independently matched boundaries (`sweep-refresh.txt`). Cache revision,
ledger blob and SHA256 are recorded in inputs.json and ignored cache
metadata. No existing donor compile-trial cache was present. This body's
private trials do not include donor headers; ZH inputs and flags are unchanged.
No broad task queue or maintainer-only verification runner was started.

After the new full gate passed, recorded success in ignored
`build/bfme1-last-check.txt`. The shared updater lock is released after this
verified pointer reaches origin/master; if publication is deferred, the next
session should settle that owned lock once the runner publishes the commit.
