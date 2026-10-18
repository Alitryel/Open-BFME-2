# AI parser copy reconciliation

At BFME2 95e70d958e, using published census c2c5ac8c27 (2026-10-18 11:36),
the same four explicitly current units predict 0 -> 199 B linked:
ChinookAIUpdate.cpp 20 B, TransportAIUpdateModuleDataBuildFieldParse.cpp 152 B,
and WorkerAIUpdateModuleDataParse.cpp 27 B. ModuleFactory.cpp remains blocked.
This is a paired legacy predictor improvement, not closed-strict or full-link evidence.

ChinookAIUpdate.cpp previously compiled the unverified ZH implementation to
retain two matched inline SupplyTruckAIUpdate setters. Its other definitions
emitted a competing SupplyTruckAIUpdateModuleData parser. Keep only those
setters through explicitly qualified calls to their original header definitions.
The original donor implementation remains in git history and BFME1
64d369b90170b7e9ec917d646f020b11f13eb0d5 under inputs/reference/.
No new layout, ABI, or class identity is inferred from byte equality.
A proposed temporary setter TU was byte-verified, then folded back into the
existing unit so the published index measures the same object universe.
The ledger, original setter notes and row locations are unchanged.

ModuleFactory's nonretail anchor took WorkerAIUpdate's data factory just to
emit its matched destructor. Construct the module data directly instead,
following the existing AutoDeposit pattern. This keeps all 58 rows including
its destructor/EH graph, without emitting the incompatible ZH Worker parser.
The actual target parser stays in its existing 27 B owner.

Acceptance:
- Strict preparation before: 9/9 rows in the three AI units and 58/58 in
  ModuleFactory.
- Strict preparation after: 67/67 rows, one empty string, float/import checks;
  renumbered ModuleFactory EH label verified through its parent EH graph.
- Same four-unit link_check command: before 0/4 clean, after 3/4 clean (+199 B).
- No new COMDAT variants; declaration and CSV checks pass.
- Published index sole-provider/reference audit: none of Chinook's 224 sole
  names had an incoming caller outside that object. No decoder source read.

Reproduce both link previews with:

    python3 tools/link_check.py Code/GameEngine/Source/Common/Thing/ModuleFactory.cpp Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/ChinookAIUpdate.cpp Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/TransportAIUpdateModuleDataBuildFieldParse.cpp Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/WorkerAIUpdateModuleDataParse.cpp

Remaining ModuleFactory debt includes missing GrantScience parser and
independent wrong-selected constructors, destructors and STL helpers; it is
not counted as linked.
