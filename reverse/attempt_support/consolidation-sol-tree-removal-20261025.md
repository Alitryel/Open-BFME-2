# Tree-buffer removal consolidation prerequisite, 2026-10-25

Seat codexb; device pool. The current scoped planner and in-memory rebuilt
routing approve the tree-buffer TU and its in-pool removal donor. Existing
Luna handoff consolidation-device-20261025.md reports missing member/counter
errors. The normal before trial reproduces C2039 for rva000EB0E6 and C2065
for m_numTrees. No donor is accepted (build/sol-tree-before-2220.txt).

The destination now declares its existing removal method. The donor uses the
destination's existing m_count and m_44544 field spellings, with their unchanged
native +0x44540/+0x44544 offsets. This exposes no new layout or name evidence;
the record array and all virtual methods retain their prior declarations.

That first change alone compiled but lost the removal row in composition.
A pair-only probe through tu_skeleton.Verifier identifies only 0x000EB0E6 as
lost under all four strategies. Its 311-byte normalized disassembly shows two
five-byte calls to _ReadWriteBarrier where retail has no instructions. The
composer hoists the pragma ahead of its extern declaration. Keeping both in
one declaration-only extern C block preserves their order; no intrinsic,
optimization setting or escape hatch is added. The standalone body continues
to match; no nonmatching reconstruction was left in Code.

Verification and publication evidence are appended after the normal final
trial. Scratch receipts live under build/sol-tree-*; they are diagnostic and
never routing approval. The actual merge remains for the Luna seat.

## Acceptance and batch audit

The normal final dry run accepts the seed and removal donor, 17 matched rows,
and emits composed C++. Receipt: build/sol-tree-removal-final-after.txt.
The all-strategy pair probe also loses zero rows. Leave the two-file compatible
subset for Luna; the other declaration/record/string-header prerequisites in
the normal receipt, six mixed files and one protected donor remain.

./build.sh on both real source paths passes 18/18 rows, literal/float/import
checks and scoped source claims (build/sol-tree-removal-final-build.txt).
Declared-unmatched and class-gate checks pass. EH data is EXACT for both
parents, with no missing objects. Data identity scans two sources with zero
findings. Code identity scans 18 rows with no problems or new notes; direct
references have owner, EH or certified-alias verdicts. The Microsoft-header
owner scans both sources with no local Microsoft definitions. Neither source
has a header-queue or identity/data baseline entry to transfer or retire.
No owner, protected register, compiler flag or existing hatch is changed.

The publication audit covers the local outgoing range from the merge base
of fetched origin/master and HEAD (including inherited c1898b7266), plus this
staged prerequisite. It contains no source moves or deletions. Active tooling,
hooks, workflows, includes, build inputs, registries and fold proofs need no
path repair; historical EA paths remain. No merge was applied: source files
removed 0, C++ bytes recovered 0, identity keys retired 0. Keep the tree seed,
removal donor and this handoff file claims plus 0x000EB0E6 until publication;
release them once the publisher/runner confirms the landing.
