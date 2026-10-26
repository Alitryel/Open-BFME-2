# Connection.cpp consolidation blocked (2026-10-26)

Allocated destination: `Code/GameEngine/Source/GameNetwork/Connection.cpp` (shard 0/5, unheld); `--check-tu` passed. The scoped `name_lane.py consolidate --under Code/GameEngine/Source/GameNetwork/` report and snapshot check passed. The current TU plan has 11 approved rows, 3 candidate donors, 1 mixed donor, and 5 protected-path refusals.

The dry run accepted no donors. `ConnectionInit.cpp` needs class/member reconciliation (`C2039: 'rva0058BAA7' is not a member of 'Connection'`; `C2065: 'm_unknown08' : undeclared identifier`). `Connection_doSend.cpp` needs class/member reconciliation (`C2039: 'doSend' is not a member of 'Connection'`; `C2065: 'm_lastTimeSent' : undeclared identifier`). The remaining error detail was truncated by the tool's dry-run summary. The protected-path donors were refused because their source paths are keyed in protected path registers.

The mixed file `Connection_clearCommandsExceptFrom.cpp` contains one row for `Connection.cpp` and one with no approved TU. Its `--split FILE --for TU --dry-run` was refused: `the residual loses matched rows (flag region or a shared helper)`. No source/ledger changes or claims were made. Revisit only after Sol reconciles the class/member declarations or the split residual preserves both matched rows, and after the protected-path register prerequisite is handled.
