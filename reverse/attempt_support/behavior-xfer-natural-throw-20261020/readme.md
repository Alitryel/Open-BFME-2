# Natural exception handling in behavior and state transfers

Five existing transfer functions now use ordinary C++ `throw XferException`
instead of constructing a raw error buffer and calling the CRT directly.
All eight existing rows and 2,006 bytes remain exact:

| Source under `Code/GameEngine/Source/` | Parent RVA | Parent bytes | Existing EH |
| --- | --- | ---: | --- |
| `GameLogic/Object/Behavior/BezierProjectileBehaviorXfer.cpp` | 0x0045CA8E | 483 | 0x0078A535, 10 B |
| `GameLogic/Object/Behavior/SpawnBehaviorXfer.cpp` | 0x00460586 | 392 | 0x0078A7A0, 10 B |
| `GameLogic/Object/Behavior/PropagandaTowerBehaviorXfer.cpp` | 0x00481842 | 216 | none |
| `Common/StateMachineXfer.cpp` | 0x004D7744 | 535 | none |
| `Common/System/XferUpgradeMask.cpp` | 0x003064CB | 350 | 0x00779B02, 10 B |

The changes preserve the failure conditions: missing weapon templates,
missing spawn templates, a nonempty tracker list on load, inconsistent
state counts or IDs, failure to recover a default state, and an unknown
upgrade. The first four functions retain tag 5 and a null message; the
upgrade function retains tag 0 and a null message. No field, virtual call,
container operation, version branch, compiler flag or shared header changes.

Propaganda's unused version/error storage union is removed, as is Spawn's
function-wide raw error buffer. The two obsolete alternate names for
ThrowInfo disappear with their references. There are no new aliases,
pins, data owners, ledger rows or ranges.

Each native parent has a tail-merged throw site calling constructor RVA
0x0060C36E, passing ThrowInfo VA 0x00CFFD18, and calling runtime helper RVA
0x00629094. `native-throw-sites.json` records those instructions before the
source changes. The metadata independently names `.?AVXferException@@`,
an 8-byte object, destructor VA 0x0042BD30, copy constructor VA 0x004588C5
and type-info vtable VA 0x00C7C730. The class identity and ABI come from
retail metadata, not a guess based on source names.

The pinned BFME1 revision `92f6bbe8` supplies ordinary XferException throws
for Bezier and upgrade transfers. Spawn and StateMachine donor failure
guards corroborate the invalid-data behavior. Propaganda's pinned donor
still has a manual CRT bridge and storage union: its natural form here is
justified by the native metadata and complete compilation proof, not
represented as a donor cleanup.

The ordinary gate passes before and after, including the final whitespace
cleanup. `throw-evidence.json` records all eight row checks, every emitted
exception call/ThrowInfo relocation, source hashes and unchanged flags.
`metadata-graph.json` follows four exception metadata sections per object;
all 20 sections match retail outside relocation fields, whose external
providers are separately checked. Independent review resolves those
relocations and compares the complete sections.
`eh.json` reports all three existing parent exception graphs EXACT, with
no baseline exceptions or missing objects.

`paired-link.json` compares preserved original objects with final objects
against census `144ed0ccab` from 2026-10-20 15:34. Commands and compiler
environment are identical, and every link-blocker category is empty for
all five files both before and after. This is source repair: zero new
matched bytes and zero link gain. The existing verification rules and
normal commit hooks are unchanged.

Agent: Codex (runtime model not exposed).
