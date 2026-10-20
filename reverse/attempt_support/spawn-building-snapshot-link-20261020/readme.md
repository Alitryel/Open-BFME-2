# SpawnBuilding Snapshot reconciliation

The parser at RVA 4E17EB emitted a one-slot `Rva004E179A` vtable; its destructor used the canonical abstract Snapshot base and emitted four slots with pure entries. The private transfer view introduced another one-slot base. Native table VA C61B78 proves the four entries: deleting destructor 8E1CFA, empty postprocess 4B3FD0, name getter 8E1794, transfer 8E1398. The complete getter literal is SpawnBuilding. The original class name remains unresolved.

A shared record declaration now uses canonical Snapshot with the supported capitalized, reference-transfer, nonconst-name surface. Parser, destructor and transfer agree on three AsciiString words at +4/+8/+C and bool +10; those offsets come from their own retail accesses. The existing six-byte getter moves from the literal-getter collection to this owner with the native virtual signature. The empty override is an ICF-proven one-byte fold at B3FD0, with no unique coverage gain. No new pin or alternate-name alias was added; the destructor's former local StringBase alias is removed.

Paired comparison against the same census index (b73720bed9, SHA in proof.json), refreshing all four objects in memory, finds the parser's vtable is its sole former blocker and all four objects clean afterwards. This newly links **129 unique legacy retail bytes**. The CLI's aggregate +130 includes a one-byte fold and is not unique coverage. Moving the existing getter contributes zero bytes. Both constructor and destructor table copies have four exact native targets; the compiler's vector-deleting name is a weak external to the verified scalar-deleting wrapper.

Acceptance: self-strict provider preparation on all four TUs; 64/64 ordinary rows, one data row and 57 literals verified; EH EXACT 2/2; declared-definition, class, CSV and converged-data checks pass. This is legacy link prediction with current self-strict objects, **not closed-strict closure**. Published census/status are not edited. `proof.py` reproduces the paired comparison while baseline objects under build/spawn-snapshot-link-20261020 remain available; proof.json records results.

Reference review: committed verified BFME1 a2c8039e61ad4dfb20c095d8eafe048248d31f25; reviewed existing canonical Snapshot/destructor convergence and prior ArmyControl handoff. No same-name SpawnBuilding donor body was found. The repair uses BFME2 native slots/layout; no BFME1 layout or address is imported. Today's tracked reference-update comparison already verifies this pointer; no submodule update was made here.

Recovery verification at 174358ae39 (2026-10-20): replayed the checkout's
preserved commit, keeping upstream 392ed1cf17's equivalent STL declarations.
Its 564 B gain was already upstream; the replay retains independent evidence,
not another gain. `stash apply --index` refused the moved CSV context without
changing the tree; ordinary stash apply then reconciled all saved edits.
The four restored providers pass the current byte gate (64/64 functions,
1 data row, 57 literals), self-strict preparation 4/4, EH EXACT 2/2, class
and declaration checks. Rerunning proof.py reproduces +129 unique legacy B;
closed-strict closure remains unmeasured. All ten restored untracked dump and
ZH sweep artifacts matched stash ^3 byte-for-byte and were copied to
build/recovery-preserved-untracked-20261020 (manifest.json) before removing
their untracked working copies. The original stash 0ca9d1daf5 and backup ref
refs/runner/preparation/1792481632747029577 remain intact.
