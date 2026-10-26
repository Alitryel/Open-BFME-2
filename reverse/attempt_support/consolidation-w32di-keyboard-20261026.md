# Win32DIKeyboard consolidation blocker, 2026-10-26

Allocated destination: `Code/GameEngineDevice/Source/Win32Device/GameClient/Win32DIKeyboard.cpp`.
The planner and currency check passed. The current in-memory TU plan approves
8 rows from the destination and `DirectInputKeyboardOpen.cpp`; the unchanged
merge dry run accepts no donor. At generated TU line 368, the donor fails with
C2039 (`m_table` is not a member of `IDirectInput8`) and C2227 (left of
`->m_table` must point to class/struct/union). No source or ledger changes or
claims were made. Sol owns the declaration prerequisite.
