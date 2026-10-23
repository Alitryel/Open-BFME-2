# Object-type vector ownership handoff

Base 4a31eab426; existing O1 G7 bfmealloc/bfme2_ascii compiler settings;
BFME1 reference reviewed at 4483e88da1c2. Current-object preview against published
census 3f413ed3ff holds out 214 authored bytes. The only blocker is the competing
ObjectTypes-pointer vector::_M_insert_overflow: the first copy is emitted by
ScriptEngineDoXfer, while this unit's 140-byte growth body was recursively proven
when its 49-byte push_back fold was admitted at 4DFCB0. Growth native target is
2DFCF6. That provider address is currently claimed by another worker.

Directly calling the existing vector<const ModuleData*>::push_back owner through
an equal three-word pointer-vector view removes this competing instantiation,
but changes the parent: two pushes for locals instead of one, local at EBP-F0
instead of reusing argument +8, and extra reload after the call. Making newVec
const produces identical mismatching bytes. Both trials fail the 145-byte parent
and its funclet, while the getter and EH handler pass. Saved diagnostic patch is
not a repair. No novel pin was attempted against another worker's provider.

Do not suppress the local growth copy and bind silently to the unproven first
copy. Revisit when native growth 2DFCF6 ownership or its class/header dependency
has been repaired; keeping the visible native append body may be needed for the
parent's escape analysis. Restored all source edits; no linked gain claimed.
