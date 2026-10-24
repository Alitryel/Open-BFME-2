# Local reverse-engineering fleet

Create two additional writer/build roots with:

    python3 tools/setup_local_fleet.py

The primary checkout and clones under `~/Projects/open-bfme2-local-fleet/` have
independent build directories. Each default `tools/next_work.py` invocation
chooses one randomized candidate; no fixed slots or worker configuration are
installed.

Every writer follows `AGENTS.md`: finish one unit, verify it, stage specific
files, commit, pull with rebase, push, then pull again. Writers publish
optimistically to the same branch. If a push loses a race, rebase and retry.
Run long full gates in only one writer at a time.

Give each writer a distinct `BFME_CLAIM_OWNER` that stays the same for its
session. Workers selecting through `tools/next_work.py` or
`tools/list_naked_candidates.py` use `--claim`; workers selecting from the
reference lanes claim the chosen retail RVAs with `tools/claims.py claim`
before starting. The queues omit claims held in other clones or on other hosts.

The fleet manifest is machine-local at
`~/Projects/open-bfme2-local-fleet/fleet.json`. It lists only the primary and
writer clones. Re-running setup refreshes configuration without resetting them.

## Windows short-path recovery workers

Prepare ten isolated worker directories and explicit-command PowerShell launchers:

```powershell
python tools/setup_local_fleet.py --short-path --root D:/b2 --workers 10 `
  --branch codex/byte-exact-bodies --python C:/Python314/python.exe
D:/b2/w01.ps1 status
D:/b2/w01.ps1 python tools/next_work.py --claim
D:/b2/w01.ps1 verify Code/path/to/whole-file.cpp
```

Use an existing source branch name. This prepares directories, not running AI
agents. The effective Codex session capacity may be smaller than the prepared
fleet. Configure the supported `agents.max_concurrent_threads_per_session` setting
separately; a configured limit does not override managed session limits.

Setup refuses unrelated or dirty existing workers, and never resets a worker.
An interrupted clone or reference checkout may need explicit repair: inspect its
Git status and preserve local work before completing the pinned checkout, then
rerun setup. Setup does not automatically reset incomplete or stale references.
Each worker borrows the source's Git object database: retain the source checkout
and its object store, or dissociate the clone before removing it. Its worktree,
index, BFME 1 checkout and build outputs are independent. The BFME 1 checkout is
created locally at the worker's exact committed gitlink, without nested reference
initialization. Setup does not advance that gitlink or certify reference freshness;
follow the freshness and verified-update instructions in `AGENTS.md`.

The runner supplies one compiler slot, a stable distinct `BFME_CLAIM_OWNER`, UTF-8
Python, a working `python3` shim for hooks, and the fleet's shared blocker database.
Default Git author and committer are WumboJet; setup accepts explicit identity
options. A worker cloned from a private local branch fetches and tracks
`origin/master`; setup preserves an existing fetched tip and local commits.
Ordinary fetches disable recursive submodule fetching, including Git
commands spawned by Python tools. Required reference updates remain explicit.
Only the coordinator integrates and publishes commits; preserve the account-wide
five-minute push cooldown. Work whole candidate files, and land each recovered
body in its own verified commit when that is the user's requested granularity.

The launcher accepts `status`, `python ...`, `git ...`, `experiment ...`,
`blockers ...`, and `verify FILE...`. `verify` invokes the ordinary build entry
point on existing whole files. It cannot accidentally start a full gate with no
file arguments. Full gates and the maintainer-controlled verification runners
remain subject to `AGENTS.md`.

## Cached experiments

Keep complete candidate translation units under the worker's ignored `build/`
directory, preserving their required include paths and compiler directives:

```powershell
D:/b2/w01.ps1 experiment build/trials/candidate.cpp `
  --symbol '?Example@@YAHXZ' --rva 0x123456 --size 25
```

`tools/recovery_lab.py` calls `recovery_experiments.py`. Its objects, compiler logs
and JSON diagnostics live in private `build/recovery-experiments/` directories,
never `build/match`. The input key includes source, toolchain, command/environment,
retail image, resolver inputs and tools. Strict dependency receipts also check
opened headers and include search inventories, including newly shadowing headers.
Uncertain dependency capture and failed compiles are not reused. Concurrent
identical requests serialize; `--force` creates a fresh private compile.

The result names the first byte mismatch, instruction differences when Capstone
is installed, unresolved relocations and complete emitted extent. DIR32 operands
requiring ordinary data/string/float/import checks remain explicitly unchecked.
Every result says `diagnostic_only=true` and `landing_verified=false`, including
an exact candidate. Cached comparisons prove neither identity nor provenance.
Install successful candidates in their proper `Code/` translation units, verify
all bodies in the whole file, run the normal pin/data/identity/link checks and
hooks, and only then commit. This tool never changes ledgers, pins or claims.

## Shared prerequisite queue

All launchers set `BFME_BLOCKER_DB` to `D:/b2/blockers.sqlite3`. Keep this SQLite
database on the same local filesystem, not a network share. The queue stores
append-only evidence, affected RVAs, prerequisite dependencies and investigation
leases, which are separate from official retail claims:

```powershell
D:/b2/w01.ps1 blockers add crt-shift-lowering --title 'CRT shift lowering' `
  --prerequisite 'Emit the native count handling with the proven ABI' `
  --rva 0x629780 --rva 0x6297A0 --evidence 'Tracked bank: reverse/attempt_support/...'
D:/b2/w01.ps1 blockers claim crt-shift-lowering
D:/b2/w01.ps1 blockers show crt-shift-lowering
D:/b2/w01.ps1 blockers release crt-shift-lowering --blocked `
  --evidence 'Remaining mismatch and next prerequisite, with tracked evidence path'
D:/b2/w02.ps1 blockers list --claimable
```

Claim and renew retail bodies through `tools/claims.py` before working on them.
Use the queue's `claim` again to renew an investigation lease. Another worker's
live lease blocks edits. Resolved dependencies unlock waiting items; blocked
items require an explicit evidence-backed update to `--status open` before retry.
Bank substantial failed work under `reverse/attempt_support/` and use `re_log.py`
for repository attempt records. The machine-local SQLite file does not replace
either committed evidence or the existing repair queues.

Before ending a recovery batch, run `python3 tools/progress.py origin/master`;
report coverage gain separately from assembly removed in already-counted C++
files. Tooling setup itself adds no recovered bytes.
