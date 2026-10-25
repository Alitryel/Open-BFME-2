# Claims

AGENTS.md ("Hard rules: claims") states the rules. This is the mechanism, moved
from AGENTS.md in 2026-10.

## Taking a claim

`python3 tools/claims.py claim 0xRVA` claims a retail body (claim every RVA in a
batch). The pickers' `--claim` (`tools/next_work.py --claim`,
`tools/list_naked_candidates.py Code --claim`, `tools/repair_queue.py ms-headers
--claim`, `next_work.py --tier dx --claim`) claims while selecting and retries if
another worker won the race. Body edits take their RVA and an atomic per-file
lock together; class-wide work takes `class:NAME`, file-wide work `file:PATH`
(`claims.py claim class:NAME`).

Queues skip work whose footprint meets another seat's live claim in either claim
namespace: `refs/claims/`, or `refs/heads/claims/` on hosts set by
`bfme.claimNamespace`. Use one namespace per fleet. An orchestrator sets a
stable, distinct `BFME_CLAIM_OWNER` for each seat.

Claims are refs on origin. They expire after four hours and do not change
`master` publication. `python3 tools/claims.py list` shows owners.

## Settling and releasing

A verified `add_match` or `add_match_batch` keeps the claim and queues the row.
The claim is released once origin/master holds the row, the blobs of every file
the verified compile read and any `reverse/symbols.csv` pins you added. A debt
item's claim is released once origin/master no longer holds its debt lines.
Release any other scope claim by hand after the push.

The pickers' `--claim` and `claims.py claim` settle such landings (`claim` keeps
the RVAs it was asked for held); `python3 tools/claims.py release --landed` does
it on demand after a push. A landing that cannot be shown (an untracked or
ignored header) keeps its claim until it expires.

Release a banked, blocked or abandoned body with `claims.py release 0xRVA`.

## Renewing

Renew before expiry with `claims.py renew 0xRVA` when work lasts longer than four
hours. Renewing keeps the lease, so a queued landing still releases; re-running
`claim` on your own live claim also preserves its lease. If `renew` reports a
claim not renewed (taken over, not yours or not claimed), stop editing that work:
reclaim it or switch to other work.

`renew` and `release` also act on claims this checkout took before 2026-10-09
under the old `<user>@<host>` owner.

## When origin is unreachable

`claims.py claim` claims nothing and exits 2. The pickers then warn and serve the
work unclaimed, skipping any work origin showed another worker holding.
