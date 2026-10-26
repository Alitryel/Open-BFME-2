# ExperienceTracker header acceptance, 2026-10-26, codex

Allocated destination: Code/GameEngine/Source/GameLogic/Object/ExperienceTracker.cpp, family A shard 0/2; runner --check-tu exits 0. Current --plan approves 44 rows with six donor and six mixed files. The scoped planner was regenerated under Code/GameEngine/Source/GameLogic/Object/ and its --check passed. Its path hints grant no merge approval; its packet still flags compiler settings, duplicate private views, mixed routing, and include context.

The recorded GameLogic header-queue failure refers to the old Rva0039AF9B.cpp private view and missing m_i114. The current destination already includes Common/GameLogicObjectLookupView.h. No C++ was changed in this repair. The supported command:

```
python3 tools/header_adopt_lane.py accept --class GameLogic Code/GameEngine/Source/GameLogic/Object/ExperienceTracker.cpp
```

passes and retires exactly one row from reverse/header_queue.tsv. This is fresh acceptance of existing adoption, not a newly demonstrated donor unblock. No identity/data key is retired. No source paths, byte ownership, COMDAT providers or consumer bindings change in this commit.

## Checks and remaining prerequisites

- ./build.sh Code/GameEngine/Source/GameLogic/Object/ExperienceTracker.cpp: 25/25 matched, one float literal verified, two renumbered funclet labels verified through parent EH data. find_declared_unmatched passes; class_gate passes; check_csv passes (98,272 function rows).
- Current ordinary --merge TU --dry-run exits 2, with no verified merge of two donors. Both ExperienceTrackerXfer sources still fail on ExperienceLevelHandle declaration order. BfmeConv813.cpp lacks matching m_valC/m_f8 members; Rva0039B1F9Refresh.cpp lacks matching bfmeUpdate/level declarations; Rva0039B548Method.cpp lacks matching rva0039B548/m_38 declarations. These are separate prerequisites, untouched here. Mixed and placeholder rows remain where they are.
- Scratch evidence: build/codex-experience-{plan,planner,accept,build,trial,link-check}.txt and build/consolidation/codex-experience/. No merge, split, census or maintainer-only measurement ran.

The outgoing path audit includes the three pending receiver/canonical-header commits from dfc0c39c28 through 9584682028 plus this queue retirement. There are no source moves/removals. The only new source paths are SquishCollideView.h and BeaconClientUpdateView.h; each has two verified direct consumers, with no active tool/hook/workflow/build-input/registry path repairs needed. Historical path strings remain. Independently incoming origin changes are distinguished from this seat's own log. Detailed code/data, selected-COMDAT and provider/consumer comparisons remain in the three prerequisite handoffs; this queue-only retirement cannot change those facts.

Keep the ExperienceTracker file claim and this handoff claim until publication is confirmed, together with the earlier pending batch's claims. Then release the file claims and settle landed RVAs. This session's total header debt retirement is two rows; recovered bytes, identity retirement and file reduction remain zero.
