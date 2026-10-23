# Link repair seat handoff

Verified repairs at 2da4a2f1b3 and 3144b91183:

| Units | Newly linked bytes |
| --- | ---: |
| SimpleScene constructor and destructor | 1,364 |
| NarrowStringRecordCopyBFME2 | 850 |
| stlport_rb_tree_hint_0038d58c | 1,282 |
| Total | 3,496 |

Final current-object preview includes all four consumers plus the narrow-string
copy, assignment and bfmeDoPW comparison providers. All seven link; the paired
total changes from 313 to 3,809 bytes against published census b711de3634
(2026-10-23 14:28). The unchanged providers account for 313 bytes and earn no
new credit. These are legacy preview gains. No self-strict or closed-strict
gain is claimed, and no full census or link cycle was run.

Byte gates: Scene provider 9/9, Scene destructor 11/11, record copies 30/30,
tree 19/19. Commit hooks passed, including exact EH checks, ledger integrity,
pin consistency and enforced converged-data checks. Source editability passed.
The record/tree commit's shadow data check found no issues; the Scene unit's
existing shadow static-data naming findings were not changed. Details and
target evidence are in link-scene-getters-20261023.md and
link-string-providers-20261023/readme.md.

`python3 tools/progress.py origin/master` reports +0 unique C++ and +0 census
linked bytes. The unchanged census cannot reflect these scoped link repairs.
The three Scene getters are folded providers of already-covered retail bodies.

Follow-up work was restored or deferred with evidence and released claims:

- Ostringstream declarations pass 14/14 after correct funclet classification,
  but leave two helper conflicts; further assignment declaration hits MSVC
  C1001. The successful intermediate patch and exact failure are banked.
- VersionBlockParser passes 5/5 but calls the 80-byte range constructor at
  177E0 under the real name belonging to the distinct 85-byte body at 17830.
  The legacy pin masks this identity problem in the byte gate. Reconcile the
  constructor providers and callers before attempting helper suppression.
- The opaque record-node views at 1DDCC5 and 1FDC0F need the actual
  AsciiString-key pair layouts, not guessed one-byte mapped constructors.
- Hashable's full eleven-unit before/after preview already links 9,940 bytes
  with unchanged inputs after refresh. A trial removing the redundant early
  include also passed 25/25 but gained zero, so it was reverted. Initial
  single-unit checks against stale selected definitions are not new credit.
  HMorphAnim/Is_Excluded and HAnim/HRawAnim vtables remain separate blockers.

Queues checked: link_rank top and near, class_views blockers, repair_queue link,
and name_globals dry-run (zero rewrites). rehome_rows cannot survey because
build/link_census/census.log is absent; the published index is present. Do not
run a full census in this seat. Several independent ranked units have live
claims held by other seats; retain their ownership.

BFME1 master was fetched and linking changes reviewed. The verified pointer
remains 96c88c73; upstream f5140c1c still needs its paired full-byte freshness
verification before adoption. No successful freshness stamp was fabricated.

The session closes at its context reassessment boundary with the verified
repairs committed and no unfinished production source. The runner retries any
publication deferred by the shared account slot. Future work should use fresh
current-provider groups and the recorded blockers rather than count inherited
fixes or repeat the blocked declaration trials.
