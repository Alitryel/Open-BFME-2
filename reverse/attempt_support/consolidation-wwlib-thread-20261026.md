# WWLib thread consolidation blocker, 2026-10-26

Allocated destination: `Code/Libraries/Source/WWVegas/WWLib/thread.cpp`.
The planner and currency check passed. The current in-memory TU plan approves
10 rows from `thread.cpp` and `ThreadClassLifecycle.cpp`; the unchanged dry run
accepts no donor. `ThreadClassLifecycle.cpp` fails with C3861:
`_beginthreadex` is not declared, even with argument-dependent lookup. No source
or ledger changes or claims were made. Sol owns the declaration prerequisite.
