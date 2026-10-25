# Consolidation handoff: Keyboard.cpp

Dry run accepted no donors. The in-prefix donors were rejected with these
diagnostics:

- `KeyboardCheckKeyRepeat.cpp`: `error C2953: '_STL::allocator' : template class has already been defined` and `error C2365: 'KEY_STATE_DOWN' : redefinition`.
- `KeyboardRva00232A42.cpp`: `error C2039: 'rva00232A42' : is not a member of 'Keyboard'`.
- `KeyboardRva00232AE8.cpp`: `error C2953: '_STL::allocator' : template class has already been defined`.
- `rva00232B7BRva00232B7BFarm.cpp`: `error C2953: '_STL::allocator' : template class has already been defined`.

These need declaration/template reconciliation by Sol. No source or ledger
changes were made.
