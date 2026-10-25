# AIFlankAttackTactic consolidation awaits Xfer header adoption (2026-10-25)

Allocated destination: `Code/GameEngine/Source/GameLogic/SkirmishAI/AITacticalAI/AITacticsGenerator/OffensiveTactics/AIFlankAttackTactic.cpp` (shard 0/5, unheld). The planner was freshly generated under the destination's `OffensiveTactics/` parent and its currency check passed. Dry run accepted the existing TU, `Code/GameEngine/Source/Common/AIFlankAttackTacticImp_DoXfer.cpp`, and `Code/GameEngine/Source/Common/AIFlankAttackTactic.cpp` (10 rows) with no compile rejections.

The same dry run reported `adopt_first: {'Code/GameEngine/Source/Common/AIFlankAttackTacticImp_DoXfer.cpp': ['Xfer']}`. This donor's Xfer private view is in the header-adoption queue and the merger warns that the class gate will refuse that private copy at commit. Header adoption/declaration repair belongs to Sol. No merge was applied and no claims were acquired; resume only after the Xfer queue prerequisite is resolved.
