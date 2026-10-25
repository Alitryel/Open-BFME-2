# GameSlot split prerequisite, 2026-10-25

Seat codexb, GameNetwork pool. The Luna handoff
`gamenetwork-pingthread-followup-20261025.md` reported that carving the constructor
and reset from GameSlotCtor.cpp into GameInfo.cpp failed on missing reset.
The current split trial reproduced it: nine carved byte rows matched alone,
but the selected GameInfo GameSlot view omitted the virtual method and the
owning members needed by construction. Simply enriching the constructor view
then exposed the seed's inline anchor preceding that selected declaration.

GameInfo.cpp and GameSlotCtor.cpp now include the same private
GameInfoSlotView.h. It combines the existing target-proven 0x1AC-byte layout,
Snapshot virtual order, owning strings and CreateAHeroData with the seed's
existing accessor declarations and field spellings. The reset body uses those
same field spellings. This reconciles existing views; no new donor name or
layout is inferred from byte equality. GameSlot has no registered canonical
header. All function definitions and ledger owners stay in their original
sources. No split or merge is applied in this prerequisite commit.

Acceptance:

- `./build.sh GameInfo.cpp GameSlotCtor.cpp`: 20/20 existing rows match,
  including the five funclets whose compiler labels were renumbered.
- Declared-unmatched passes both files; EH reports two EXACT parents.
- The normal split dry run accepts seed plus carved donor, 19 rows, no rejected
  donor, nine carved rows exact alone, one residual row preserved.
- Code identity scans 20 rows with no new findings. The same two pre-existing
  divergent map/tree end COMDAT findings remain in shadow. The 20 reported
  ordinary provider bindings are unchanged. Five former funclet bindings are
  omitted by that scanner after label renumbering; build's parent-EH resolution
  verifies every funclet and eh_verify confirms both complete graphs.
- Data identity has zero findings. The owning Microsoft-header refresh finds
  zero definitions in both sources and the header. No corresponding canonical
  header queue or source-keyed code/data identity baseline entries exist; no
  debt key is retired or transferred.

Receipts: build/sol-gameslot-before.txt, sol-gameslot-build.txt,
sol-gameslot-after.txt (intermediate declaration-order refusal),
sol-gameslot-shared-build.txt, sol-gameslot-shared-after.txt,
sol-gameslot-identity-before.txt and sol-gameslot-identity-after.txt.

Leave the accepted split to Luna:
`python3 tools/tu_skeleton.py --split Code/GameEngine/Source/GameNetwork/GameSlotCtor.cpp --for Code/GameEngine/Source/GameNetwork/GameInfo.cpp`.
Its ordinary acceptance checks, current routing and claims still apply.
No files removed, recovered bytes, identity retirement or linking gain are
claimed; one private header is added.

The outgoing batch audit compares the merge base of origin/master and HEAD,
plus these staged edits: there are no pending source moves or deleted paths.
The new quoted include resolves beside both sources and the destination TU.
Active tooling, hooks, workflows, includes, build inputs, registries and fold
proofs require no repointing; historical EA paths remain untouched. Incoming
origin-only IPEnumeration/NetCommand/udp moves are not unpublished seat work.
Keep claims for the two sources, new header, this handoff and RVAs 0x003FF50C
and 0x003FFB4C until publication is confirmed.
