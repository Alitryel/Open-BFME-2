# Link-seat resource blocker and triage

BFME2 input: `27dd681fd25e39dcb7a019cae17765c4e55d2f84`.
Model: gpt-6.1-sol. No source changes or linked-byte gain retained.
The published census fetched this session is `456ce161c5`,
2026-10-23 06:28, retail-truth-4. No census or full link runner was started.

## Required reference freshness check

The clean verified BFME1 pointer and checkout remain
`96c88c73a5cd1a58fc2f8db691beea50acd996db`. Official master fetched this
session is `f5140c1cff6a58e16276fd6de6788186286953d4`. Previous successful
old/new verification is recorded in
`reverse/attempt_support/bfme1-reference-96c88c73-20261023/readme.md`.
No successful freshness timestamp was written this session.

The required same-input baseline `./build.sh` was started once, logging to
ignored `build/seat-link-freshness-before.log`. Baseline image checks passed
and 14 library members were extracted. It then waited for the shared full-build
compiler lock. At termination after 17m44s, its Python process was in
`locks_lock_inode_wait`, holding the open lock descriptor for
`/home/agent/.cache/open-bfme-build.lock`. No row verification result was
reported. Only this session's waiting process was terminated (exit 143);
the shared lock and its holder were not modified. This is a temporary resource
failure, not a byte failure or evidence that the repair queues are empty.

Before advancing the pointer, rerun that baseline, then verify the new inputs
and compare failures under identical conditions as AGENTS.md requires. The
fetched change contains nine C++ source edits and no header, toolchain or layout
changes. The existing layout migration and lift tool are present. Reviewed
donor repairs include ScoreScreen's external parent, TerrainRoads' duplicate
helper removal, EAStringCMid's inline default constructor, and narrow-string
assign declarations in the online-slot and NAT units. BFME2's corresponding
TerrainRoads and EAStringCMid providers already link; no new gain is claimed.

## Link probes

`check_csv.py` passed. Reviewed `link_rank.py --top 30 --near 2`,
`class_views.py --blockers`, and `repair_queue.py link --limit 8`.
Current-object previews of 156 sole-blocker units found 40 linking units
(7,430 legacy bytes), and 390 near-link units found 62 linking units
(11,573 legacy bytes). These are inherited repairs on master, not session
improvements. No self-strict or closed-strict gain was measured.
Diagnostic outputs remain under ignored `build/seat-*`.

The inspected address-getter, shader and related `name_globals.py --dry-run`
probes produced no rewrites. `rehome_rows.py --limit 3` could not run because
the downloaded index has no `build/link_census/census.log`; this secondary
artifact failure is not an empty queue. No census was launched to create it.
Existing FVF, string and allocator failed trials were read and left deferred.
Fresh claims on other workers' units were respected.

## MultiplayerSettings constructor prerequisite

Current-object `link_check.py` confirms the exact cached 159-byte constructor
at RVA `003811D8` has two unresolved names: nonvirtual
`??1SubsystemInterface@@QAE@XZ` and `?g_00C191B8@@3QBQBXB`.
The canonical SubsystemInterface destructor is virtual (`UAE`), while this
constructor uses an empty private base and a separately initialized vptr.
The linked MultiplayerSettings destructor already composes the canonical
12-byte base. A declaration-only change therefore needs an ABI/codegen check,
not an alias between the destructor names.

Independently, retail's first word at RVA `008191B8` is VA `00781277`, the
rowed MultiplayerSettings deleting destructor. This contradicts the current
`00381293` destructor row's assertion that no vtable references it. Resolve
that class contract and the unowned table before attempting a local missing-
destructor repair. No source variant, pin, table definition or rename was
tested or retained. A concise blocked finding is recorded through re_log.py.

All claims taken this session were released. The runner result is retryable
resource failure; resume the reference baseline before further source edits.
