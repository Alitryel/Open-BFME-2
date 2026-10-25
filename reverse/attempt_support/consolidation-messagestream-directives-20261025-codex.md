# MessageStream directive composition prerequisite

The seed-only C1004 blocker recorded in `consolidation-common-20261025b.md`
reproduces with the committed composer. It deduplicates the two closing
`#endif` directives and hoists function-scoped optimization changes.

`tu_skeleton.py` now preserves complete nested conditional regions as opaque
items, including their branches and closing directives. Optimization pragmas
travel with the donor's function sequence, retaining repeated resets. The
ordinary chunker and split extraction remain unchanged. Opaque conditional
types are not view-unioned; complicated declaration dependencies can still
refuse a merge. No byte acceptance, routing, protected-register or claim check
was relaxed.

Verification on 2026-10-25:

- Committed composer, current seed alone: C1004 unexpected EOF.
- Current seed: 13 ledger rows / 13 distinct matched RVAs. Revised composition
  preserves all 13 in each of `first`, `longest`, `union-first` and
  `union-longest`, compiled through the merge lane's scratch Verifier.
- Scoped planner regenerated and its `--check` passed. Ordinary plan reports
  43 approved rows, seven eligible files, six mixed files and two protected
  refusals. The full dry run retains the seed but finds no compatible second
  donor. It now reports the independent failures below, rather than losing
  the seed to C1004.
- `python3 -m unittest tools.tests.test_tu_skeleton`: 18 passed, including
  separate/nested conditional includes, conditional definitions/branches,
  repeated optimization resets and an unterminated-region refusal case.
- Combined skeleton, TU-structure and gate-exploit pytest run: 101 passed,
  one skipped, two pre-existing failures. Both failures reproduce unchanged
  when importing the committed `tu_skeleton.py`: the generated-placeholder
  fixture lacks current routing inputs, and the old repoint test calls the
  removed `repoint` API. They are not repaired or suppressed by this change.

Remaining MessageStream donors: CommandList append-list has a byte mismatch;
integer/wide arguments need enum/member agreement; struct arguments and copy
need Coord3D/ICoord2D include reconciliation; the destructor duplicates
SubsystemInterface; propagation needs TranslatorData/MessageTranslatorNode
agreement. Mixed and protected files remain untouched. Local ignored evidence:
`build/messagestream-prerequisite-{plan,dryrun}.txt` and the four
`build/messagestream-*-composition.cpp` outputs.

No game source or ledger moved in this prerequisite. Files removed, authored
C++ growth and identity debt retired are all zero. The outgoing range from
fetched `origin/master` at `0ae45ce317` plus this staged change has no moved or
deleted paths, so no path consumer needs repointing. File claims stay held
until publication is confirmed; release the MessageStream/tool/test scopes
after this commit lands.
