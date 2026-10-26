# AptValueGCAllocator declaration prerequisite, 2026-10-26

Seat codexb5, Sol medium, family B shard 1/2. Base 6f56e094b7;
`/opt/runner/consolidation_queue.py --limit 20` allocates
`Code/Libraries/Source/Apt/AptValueGCAllocator.cpp` to this seat.
The tree and unpublished range were empty at entry; inherited PingThread
commits 61cac618e1 and 41e8dd8ef6 are already upstream.

## Evidence and change

The scoped Apt consolidation planner identifies the original retail path and
three verified literal operands in freeBlock. Its stale-map entries remain
hints; `tu_skeleton.py --plan` rebuilds routing in memory and approves five
rows from three sources. No map is committed. The planner's inline assertion
assembly warning describes the pre-existing INT3 barriers, not a new lift.
No alternative destination or donor identity is inferred from donor layout.

The normal merge dry-run initially accepted no files and exited 2. CleanPool
failed C2039 (missing member) and C3861 (GetFirstAptValue not found after the
invalid member definition). The allocated seed's pool-manager view already
declared the two traversal methods, but lacked CleanPool and the +0x14 count
used by the matched Common donor.

Add only `void CleanPool()`, twelve bytes of padding after the +4 first-pool
pointer, and `int mnItemsAllocated` at +0x14 to that existing seed view.
The field observation comes from the existing byte-verified CleanPool body;
this is a partial operand view, not a recovered complete class. Neither the
Common donor nor a shared header is edited. No function body, flags, pin,
alias, source path or ledger row changes.

The same normal dry-run now exits 0 and accepts the seed plus
`Code/GameEngine/Source/Common/AptValueGC_PoolManager_CleanPool.cpp`, verifying
four rows. This demonstrates one newly compatible donor (71 retail bytes),
not new recovered bytes or a confirmed Luna landing. Leave the merge to Luna.

## Verification and bindings

Local receipts use prefix `build/sol-b5-allocator-`:

- `./build.sh` seed and CleanPool before/after: 4/4 matched, sixteen string
  references, zero import/float failures. `find_declared_unmatched.py` on both
  passes; `class_gate.py` on the edited seed passes.
- `allowed_symbols.load/scan` before/after: identical ten owner bindings, no
  wrong binding. The normal `allowed_symbols.py --source` scan agrees.
- Saved before/after objects, examined through `allowed_symbols._object_defs`,
  have identical six external code definitions (five seed, one CleanPool),
  relocation-normalized digests, sizes and exclusivity. Each definition's
  COMDAT selection and section flags are identical: the two seed inline
  helpers retain selection 2 and the four rowed bodies selection 1. Both
  objects' undefined-symbol sets are identical. Object paths and link order
  stay fixed, so no selected provider or external consumer acquires a changed
  variant. `build/sol-b5-allocator-proof.py` asserts exact equality of these
  facts and every scanned code/data binding in the saved JSON receipts.
- `data_check.object_facts` before/after: identical data definitions and
  bindings, no unread rows. `data_check.py` reports zero shadow findings;
  `--converged` judges ten addresses with zero second names or unjudged rows.
- `eh_verify.py` on both: no EH rows, no nonexact or missing objects.
- Read-only `ms_header_audit.py scan` on both: no private Microsoft prototypes
  or conflicting files. Neither source is keyed in code/data identity,
  header_queue or ms_header_queue; no register entry is retired or transferred.
- `check_csv.py` after upstream pull: 98,252 functions, 15,683 symbols and
  2,215 data rows, OK. `git diff --check` passes.

The post-edit planner was initially run concurrently with the dry-run and
refused a disappearing temporary `.tu_skeleton.cpp` input. It was rerun after
the trial finished; no failed snapshot is accepted as current evidence.

## Remaining blockers and publication audit

`Code/GameEngine/Source/Common/Rva006D29E0Cluster.cpp` remains rejected with
C2084 for isAllocated and undeclared mValueBitfield. Its private inherited
bitfield view and out-of-line inline helper differ from the seed's local
view. It is a cross-family source with other row ownership; this seat neither
edits nor claims it. Hand this prerequisite to its assigned owner rather than
manually moving or dropping its rows. No verified acceptance gain for that
donor is claimed.

Audit covers `origin/master..HEAD` at 6f56e094b7 plus this staged seed and
handoff. There are no pending moves/deletions or changed include consumers,
build inputs, tools, hooks, workflows or path-keyed registries. Repository
search finds no active hard-coded tooling reference requiring repair.
Historical EA paths remain intact. Source-file reduction, identity-debt
retirement and newly recovered C++ bytes are all zero.

The claims fetch later advanced origin to 4e6c410b2f while local HEAD remained
6f56e094b7. `git log origin/master..HEAD` is empty; the reverse path changes
shown by that endpoint diff are incoming GameLogic commits, not outgoing
consolidation work. Publication rebases this seed-only edit over them.

The BFME 1 freshness check fetched official master b642d2462c while the clean
last verified checkout remains c0385ef6ba. Full reference-update verification
is pending; retain verified inputs and do not fabricate a freshness receipt.
No maintainer-only link cycle, smoke or nightly task was run.

Retain file claims for the seed and this handoff until publication is
confirmed; if the runner holds this commit, its next session releases those
two claims after landing. No RVA was moved or newly claimed.
