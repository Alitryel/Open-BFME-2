# MessageStream integer and wide-character argument prerequisite

Follow-up to the MessageStream blockers in `consolidation-common-20261025b.md`
and the directive-composition repair in
`consolidation-messagestream-directives-20261025-codex.md`.

`GameMessageIntWideArgs.cpp` now uses the same BFME2 MessageStream header and
compile environment as the approved MessageStream seed. Its duplicate private
GameMessage/argument views are removed; the bodies use the existing header enum
values and union members. No layout, tag value, store order, symbol, ledger row,
or compiler-region override changes.

Verification on 2026-10-25:

- `./build.sh Code/GameEngine/Source/Common/GameMessageIntWideArgs.cpp`: 2/2
  byte exact (0x0030F936, 19 bytes; 0x0030FA2A, 26 bytes).
- `find_declared_unmatched.py` passed before and after the edit.
- Normal `tu_skeleton.py --merge Code/GameEngine/Source/Common/MessageStream.cpp
  --dry-run` accepts the seed plus this donor. Its report counts 14 non-alias
  addresses. A separate `tu_skeleton.Verifier` check of the complete proposed
  text against all 15 matched ledger rows, including the existing gen-alias at
  0x005F69C4, preserves all 15. Local report:
  `build/messagestream-arguments-dryrun.txt`.
- `git diff --check` passed. Normal commit hooks check the source again.

Leave the now-compatible donor for mechanical consolidation. No source paths
moved, files removed, bytes recovered, hatches added, or identity debt retired.

Remaining independent donors retain their dry-run blockers: canonical coordinate
or SubsystemInterface redefinitions, the translator-node pointer mismatch, and
CommandList virtual-call bytes. Mixed and protected sources remain untouched.
