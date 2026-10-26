# AptCIH consolidation prerequisite trial, 2026-10-26

Seat codexb5, Sol medium, family B shard 1/2. The runner's allocated queue
authorizes `Code/Libraries/Source/Apt/AptCIH.cpp`; its file claim and this
handoff claim belong to this seat. The scoped Apt planner was generated before
the trial, with original-path evidence and declaration/flag prerequisites
reviewed. No planner hint is treated as routing approval.

`tu_skeleton.py --plan Code/Libraries/Source/Apt/AptCIH.cpp` rebuilds the
stale TU map in memory: 37 approved rows, sixteen donor files and two mixed
files. All twelve rows in AptCIHLevel006E0B80.cpp are now approved for this TU.
No regenerated map is committed. Mixed AptCIHQueueClipEvents.cpp and
Rva006F7C10Clear.cpp require the supported split lane and are not absorbed by
this merge trial.

## Baseline evidence

The level donor observes parent +0x48, payload +0x4c and a code word +0x58.
The seed has nine virtual slots and no instance fields. The merge's safe
class union can add nonvirtual declarations but deliberately cannot add data
or virtual members. The MC-info donor has a different +0x5c field also called
m_code; these private views do not establish a complete shared class layout.

- `./build.sh Code/Libraries/Source/Apt/AptCIH.cpp
  Code/Libraries/Source/Apt/AptCIHLevel006E0B80.cpp`: 24/24 matched,
  36 literal references, one float, zero import failures. Both frozen-file
  checks pass. The seed's two funclet labels renumber to $L584/$L583; the
  verifier locates their exact parent EH entries at 0x007a90d8/0x007a90d0.
- The saved baseline objects and `allowed_symbols.load/scan` receipt contain
  24 rows, 42 code references (39 owner, one EH, two aliases), and 21 external
  code definitions (nine seed, twelve level donor). The receipt includes
  relocation-normalized definition digests, sizes, exclusivity, undefined
  symbol sets, COMDAT selections/flags, and data definitions/bindings.
  `build/sol-b5-cih-proof.py` uses the supported EH-parent resolver before
  scanning renumbered funclets; no gate or alias ledger is changed.
- `data_check.py` on both: zero shadow findings. `--converged`: ten judged
  addresses, zero second names or unjudged rows. `eh_verify.py`: one EH-bearing
  row EXACT, none nonexact or without an object.
- Neither source is keyed in code/data identity, header or Microsoft-header
  queues; AptCIH is not a registered canonical class. No debt retirement is
  implied by these clean scoped checks.

## Repair and scoped acceptance

The full normal baseline `tu_skeleton.py --merge ... --dry-run` captured its
source texts before any edit. It continues through alternate orders, flags
and the uncarried-override retry. Its result is baseline evidence, even though
the prerequisite was verified while that captured-text trial was running.

To isolate the concrete dependency, `build/sol-b5-cih-scope.py before|after`
calls the same `tu_skeleton._merge(..., dry_run=True)` routine with the seed
and level donor, after checking both against current routing and the header
queue. It retains every matched row in both files (24 total), every merge
strategy, and the normal override, region-default-loss and protected-register
checks. It writes no sources or ledgers. This scoped dependency comparison
does not claim that all sixteen donors compose together.

Before: accepted [], rejected level donor C2039 for rva006E0B80 missing from
AptCIH, no verified merge. Add the twelve existing nonvirtual level-accessor
declarations and its observed +0x44/+0x48/+0x4c/+0x58 operand view to the seed.
Keep all nine seed virtual slots. No body, flags, pin, global, path or ledger
changes; the level donor itself is unchanged. This remains a partial operand
view, not a recovered complete class.

After: accepted seed and level donor, all 24 rows, no rejection. Twelve donor
rows totaling 1,135 retail bytes are now compatible. This is a demonstrated
prerequisite improvement, not newly recovered bytes or a confirmed Luna
landing. The proposed merge would transfer the donor's existing flag override;
this source-only repair transfers or retires no register entry. Leave that
merge and its generated trailer to Luna.

- `./build.sh` both sources after: 24/24 matched, all 36 literals and the float
  verified. Both frozen-file checks and the seed's class gate pass. Funclets
  now spell $L606/$L605 and still verify at their exact parent EH entries.
- `build/sol-b5-cih-proof.py after` asserts exact equality with the saved
  baseline: all 21 external code definitions, digests, sizes, exclusivity,
  undefined symbols, COMDAT selections/flags, all 42 code references, and all
  data definitions/bindings. Object paths and link order stay unchanged, so
  no provider variant or external consumer acquires a changed definition.
- Post-edit `data_check.py`: zero shadow findings; `--converged`: ten judged
  addresses, zero second names or unjudged rows. `eh_verify.py`: EXACT 1,
  none nonexact or missing. `git diff --check` passes.
- Read-only `ms_header_audit.py scan` on both sources: zero private Microsoft
  prototypes, conflicting files or failures. No header queue is rewritten.

Local receipts have prefix `build/sol-b5-cih-`.

## Publication audit and remaining work

Audit includes pending 097bc60412 plus this seed and handoff. origin/master
advanced to 1474ec5538 during claims fetches while the local base remains
6f56e094b7. `git log origin/master..HEAD` identifies only the pending allocator
commit; reverse moves in the endpoint diff are incoming work, not outgoing
path changes. Our pending batch has no moves/deletions, changed includes,
build inputs, active tool/hook/workflow consumers or path-keyed registries.
An active-tools search for both CIH paths finds no hard-coded consumer.
Historical EA paths stay intact. No source reduction, identity debt retirement
or new C++ recovery is claimed.

Retain the seed, unchanged level donor and handoff file claims until confirmed
publication. If the runner holds the batch, its next session releases those
claims after landing. The allocator claims are recorded in its own handoff.
