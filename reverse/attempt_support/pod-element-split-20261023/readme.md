# BfmePodNN rows that retail splits across distinct element types

Finding (link census `retail-truth-4`, objects built at this tree): the provider
`Code/Libraries/Source/WWVegas/WWLib/stlport_pod_noexc_bodies.cpp` (2,718 bytes,
does not link) and dependents such as
`Code/GameEngine/Source/GameLogic/Object/Behavior/Rva00541913CopyCtor.cpp`
fail with `comdat`/`selected` "not retail's body" on `BfmePod28`/`BfmePod32`
vector members. `whywrong.py.txt` (run as `python3 build/whywrong.py <src>
<symbol-substring>`) names the failing relocation:

- `??0?$vector<BfmePod28>(const&)` (row 0x00541434, 71 B): retail's call at +0x35
  goes to `__uninitialized_copy` at **0x005411C8**, which is the row
  `__uninitialized_copy<Rva00541021>`; the ledger name `<BfmePod28>` resolves to
  0x00215F38. Both elements are 28 bytes, but retail instantiates them
  separately (their `_Construct` callees differ: 0x0054105B vs 0x00215F22).
- `_M_allocate_and_copy<BfmePod28>` (0x0054124E) calls the same 0x5411C8.
- `??0?$vector<BfmePod32>(const&)` (0x0052C823): call goes to 0x0052C27E, the
  ledger name resolves to 0x00421D28.

Cause: rows placed by masked search under one BfmePodNN spelling although the
0x541xxx / 0x52Cxxx neighbourhoods are other element types (Rva00541021 at
0x541021/0x5410E3/0x54124E/0x541709/0x541CD9 already has its own unit,
`stlport_vector_rva00541021_allocate_copy.cpp`). The rows 0x541434, 0x541BDF
(reserve) and 0x5849EF (insert) most likely belong to `vector<Rva00541021>`.

Not done: re-homing the rows needs an identity change (element type per address
cluster) in the ledger and every unit that declares the `<BfmePod28>` copy
constructor decl-only (`Rva00541913CopyCtor.cpp`, `Rva00540E82Init.cpp`,
`HordeMeleeSwarmXfer.cpp`, `BannerUI*.cpp`, ...). See docs/naming.md before
renaming. Expected payoff: the 2,718-byte provider plus its dependents link.

## Same cause, map<int,float>

`??A?$map<int,float>` (0x0033D042, 73 B, `Thing/IntFloatMapSubscript.cpp`) calls
`insert` at **0x00289147** (retail folds the int/int and int/float spellings;
`symbols.csv` pins the float name there). The ledger instead rows
`map<int,float>::insert` at 0x0035926E and `_Rb_tree<..., pair<const int,float>>::insert_unique`
at 0x003590C9, whose callers (`Rva00358FEERecord`, tree at 0x003591F4 in the
same unit) show they are the `map<int, Rva00358FEERecord>` pair. Retail truth
resolves a ledger row before a pin, so the operator[] row is judged "wrong" and
the float-map users (`ThingTemplateFloatMapStore.cpp`,
`PlayerTemplateProductionParsers_ParseProductionCostChange.cpp`) report
`selected`. Fix: retype those two rows to `Rva00358FEERecord` (see
docs/naming.md; they are inferred placeholders, not canonical names).

Trial (reverted): retyping rows 0x0035926E / 0x003590C9 to `Rva00358FEERecord`
makes the two float-map users link (+106 B) but `insert_unique` no longer
byte-matches at 0x003590C9. Retail's insert at 0x0035926E calls `~Rva00358E6A`
(0x00359231, a tree-holder destructor) in its EH cleanup, so the real value type
is a node holding a nested `Rva00358E6A` tree, not an 8-byte record. Needs that
class laid out first.
