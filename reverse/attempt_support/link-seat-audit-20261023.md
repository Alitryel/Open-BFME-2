# Current-object link audit, 2026-10-23

BFME2 checkout `6766ac3df7`, upstream `29df93f943`, published census
`b711de3634` (14:28 UTC, retail-truth-4). No production edits, new claims,
new linked bytes or authored-C++ gain. This is a legacy preview, not a
self-strict or closed-strict result.

After pulling and passing `check_csv.py` (98,176 function rows), fetched the
published index and its available objects. Reviewed `link_rank.py --top 30`,
`--near 2`, `--top 100`, `class_views.py --blockers`, and
`repair_queue.py link --limit 10`. Excluded foreign file/body claims before
selecting existing authored units with at least 100 census bytes and at most
three blocker names. A current-object `link_check.py --paths-from` preview
of 134 such units already links 24 units / 28,787 bytes. These are inherited
repairs, not a session improvement. Examples include hcanim, FireLogicSystemObjects,
W3DGhostObjectScene, GSConfig, ArmySummaryCopy and the network child constructor.
The ignored receipts are `build/link-seat-near-current.txt` and
`build/link-seat-unclaimed-paths.txt`.

Remaining inspected causes retain their recorded prerequisites: opaque STL
record/provider ABIs, incorrect class/vtable views, missing shader singleton
providers, and helper-emission differences whose suppression changes matched
parents. Read the linked evidence before declining unchanged retries, including
`link-node-allocator-20261023.md`, `link-seat2-20261023-followup.md`,
`link-seat-current-providers-20261023.md`, and `hash-selection-link-20261022/readme.md`.
The BfmeRectVNH unwind still needs the folded base-destructor owner decision
recorded in its attempt log; no empty replacement destructor was introduced.

`name_globals.py --dry-run` on Rva00066A9ABody and both address-getter units
offered zero edits. `rehome_rows.py --limit 5` cannot read the absent
`build/link_census/census.log`; that artifact failure does not establish an
empty queue. No census, full link cycle, nightly or boot runner was started.

BFME1 remains clean at verified pointer `96c88c73a5cd1a58fc2f8db691beea50acd996db`.
Fetched official master `f5140c1cff6a58e16276fd6de6788186286953d4` has nine
changed game-source files and no header/layout changes. The existing paired
verification at `bfme1-reference-96c88c73-20261023/readme.md` establishes the
committed pointer, but the ignored freshness stamp remains stale. Do not mark
the newer inputs verified.

The one new old-input `BUILD_POOL=8 ./build.sh` baseline waited over six minutes
for `~/.cache/open-bfme-build.lock`, before function verification. `/proc`
reported `locks_lock_inode_wait`, with that lock as its only extra open file;
a nonblocking lock probe also reported contention. Interrupted only this seat's
waiting process (exit 130), leaving the external lock holder untouched. The
traceback terminates in `portable_lock.py` at `fcntl.flock(handle, mode)`.
Resume the paired old/new donor verification when the shared resource is
available. This is a retryable resource failure, not proof the link lane is
exhausted. No source/object restoration is needed and no claims remain from
this session. `progress.py origin/master` reports zero deltas in all coverage
and linking measures.
