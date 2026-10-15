# Inlined locomotor-set accessor copies

## Concurrent upstream landing

Upstream `98cc6712ab9f9803141ec909751aefa37f416930` landed the same emission
repair for these three files and five peers while this independent trial was in
progress. Reconciliation retains upstream's source in all three files, including
its force-inlined WallUpgrade accessor. This commit records independent
verification only: it contributes no additional conflict reduction, source
change, authored bytes or linked bytes over that upstream repair. The paired
results below describe the isolated pre-upstream trial, not a fresh gain against
current master. The trial's WallUpgrade direct-field variant was not retained.
After reconciliation, scoped strict preparation again verifies all 17 rows and
EH verification finds all three parent graphs EXACT. Every normalized nondebug
section in the retained upstream objects equals the corresponding trial object;
`upstream-reconciliation.json` records the final source/object/receipt hashes.
The final enforced data check retains the same three baselined findings.

## Independent trial

At BFME 2 base `c936f400ed38cf7c4d39c6dc27b8c7c3fbbf3fd4`, three current
objects emitted the same unused seven-byte `AIUpdateInterface::getLocomotorSet`
COMDAT (`8d81cc010000c3`). The census selected a different first copy. The
matched callers already inline their existing +0x1CC field view. This repair
removes the unused out-of-line copies without changing that view or any caller.

WallUpgradeUpdateScan uses its existing public field directly. The two AI state
units retain their private member access through a force-inlined dllimport
definition. No imported call, new undefined symbol, or linker directive results.
This does not reconcile all AIUpdateInterface layouts or establish a canonical
class contract.

## Controlled local measurement

The runner index has measurement commit `825b86983f`, timestamp
`2026-10-15 12:37`, underlying census `5986a99448`, and SHA256
`672f6ffe10798a1e82a1516e32c7d579bd787503faae7ee6beabb6e4cca2b93c`.
Each paired comparison refreshes only the tested source into a separate copy of
that same index, using saved strict-current before and after objects. The index
and tracked link status were not changed. Proof JSON records object, source and
receipt hashes and full paired findings.

| Source basename | Retained COMDATs identical | Local findings before -> after | Remaining dependencies |
| --- | ---: | ---: | --- |
| WallUpgradeUpdateScan.cpp | 30 | 3 -> 2 | ObjectStatusMask::Rva0023DA79, Pathfinder::rva002EDFF9 |
| AIFollowPathStateMethods.cpp | 25 | 2 -> 1 | AIStateMachine::getGoalPathPosition |
| AIGuardRetaliateStates.cpp | 41 | 5 -> 4 | State::onExit, State::slot01, State::slot02, State::slot03 |

Only the accessor section and its external definition disappear in each object.
Every retained nondebug section, normalized relocation, external binding and
linker directive is identical; the removed accessor has no nondebug incoming
relocations. Local `$L` labels and `.sxdata` symbol indices were normalized to
their actual targets. Existing data-reference facts and all three baselined
data findings are identical before/after.

This is a strict-current body check and a LEGACY local selection improvement,
not a closed-strict link result. All three units remain unlinked. Authored C++
coverage and existing linked retail bytes both grow by zero. No full census or
maintainer-only link runner was started.

## Checks

- Strict `link_check.py --prepare-current` before and after: 17/17 ledger rows;
  normal final `./build.sh` on all three sources: 17/17, 12 string literals,
  five float literals, zero named imports, no skipped checks.
- `eh_verify.py` before/after: all three parent graphs EXACT; both renamed
  funclet labels resolve through the unchanged parent EH data.
- `data_check.py --enforce`: three existing findings, zero outside baseline.
  `--converged`: eight addresses, zero second names, zero unjudged rows.
- `class_gate.py`, `find_declared_unmatched.py`, `link_check.py --new-variants`,
  `check_csv.py` and `git diff --check` pass.
- `place_bodies.py` rescan of all touched units: zero bodies, zero pins.
- Plain `link_check.py` reports the seven unchanged missing dependencies above
  and exits 1 as expected; paired proof isolates the three removed conflicts.

The scratch object/receipt snapshots and normalization assertions are under
`build/wall-locomotor-link-20261015/`. To reproduce after scratch cleanup, compile
each source at the base and repaired revisions with its recorded `// cl:` flags
through the normal scoped build/strict preparation, preserving both objects and
receipts. Compare COMDAT bytes plus relocation digests, then compare nondebug
sections with local relocation targets and `.sxdata` indices normalized; refresh
each pair separately against the identified index. Do not infer fresh link
closure from a different or missing index.

## Donor review and boundaries

Reviewed BFME 1 donor `66b19a8e95a4add525ef808fcea088e306798e2b` (suppress
conflicting Apt allocation copies) for its dllimport/forceinline emission
treatment, and `c1315665a1b22beb7e6d9279548fe5b1c26ed1f9` for removal of an
unused conflicting constructor. These are compiler-shape precedents only; no
donor layout, identity or implementation was imported. BFME 2's whole-body and
object comparisons establish this local repair.

BFME 1 remains at verified gitlink `a7c38d3b2597121f178ab5190b3062478823257d`;
the overdue upstream update (initially `3a5eb7a27d25a9192ca16872ae5446a5cde592f1`,
subsequently fetched `98f9c4fc7`)
has a live file claim from another worker and a prior comparative-gate blocker.
The checkout, gitlink and freshness-success stamp were preserved. Broader class
reconciliation, the seven missing dependencies and full-game verification remain
separate work.
