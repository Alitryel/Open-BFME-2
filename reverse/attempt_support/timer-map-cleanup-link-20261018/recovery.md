Preparation recovery, 2026-10-18
================================

The preparation record names original HEAD dff7252ad2, upstream 86b4160a87,
and retained backup refs/runner/preparation/1792339470908518456. There is
no stash or resync stash in that record; the stash list is empty. The
original evidence and commits remain reachable through the backup ref.

The interrupted rebase replayed the timer and getter commits. Its last
commit, dff7252ad2, conflicted only in comments: upstream 327ed4930f already
contains every multilist code change from that commit. It was skipped,
preserving upstream's comments and implementation. Its historical +519 B
is already covered upstream and is not a new recovery gain.

The outgoing dry-run hook passed 190/190 functions, six exact EH graphs,
literal/import checks and enforced converged-data checks. Before the
publisher obtained its shared cooldown slot, master advanced through
fbfbd57b23. That recovery documents that bc019a9f4e's /EHs setting already
makes Rva00359290Dtor.cpp link without the saved tree destructor declaration.
The waiting publisher was stopped before publication to reconcile this.

Remove the redundant saved declaration, retaining the exact upstream
source. Paired ordinary link_check previews with and without it both link
165 B for the timer unit. Explicit --prepare-current passes all four byte
rows with strict reusable receipts; its two EH graphs are EXACT. The
historical proof.json is retained as evidence against its original inputs;
its +165 B is not an incremental gain over current upstream.

The getter rehoming remains useful: the paired historical evidence records
516 -> 612 B (+96 B) of legacy predicted linked getter coverage. The current
five-unit preview, both before and after removing the timer declaration,
reports 516 -> 777 B versus census c2c5ac8c27 (2026-10-18 11:36), including
the 165 B timer repair already upstream. Two address-getter units still
have hard-coded-address blockers. No new authored C++ bytes or closed-strict
gain is claimed. Current logs and the removed declaration's source backup
are retained under ignored build/recovery-*.

No new tasks were selected. All saved changes are either replayed, retained
in the backup, or superseded by the cited upstream implementations.
