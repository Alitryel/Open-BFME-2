# Link-repair findings, 2026-10-22 (afternoon seat)

Read-only investigation of three COMDAT blockers that remain after upstream's
decl-only batches and after `link_check.py --refresh` (53 stale objects
recompiled, 92 census definitions replaced). All work was reverted; nothing in
`Code/` was changed by this investigation.

## StlportVectorGrowthFootprints.cpp (6,419 B own bytes)

Live verdict (`tools/link_check.py --refresh`):

```
comdat    ??$_Destroy@PAUBfmeVectorRecord002AF478@@@_STL@@YAXPAUBfmeVectorRecord002AF478@@0@Z  (retail: not retail's body)
selected  ??$_Construct@UBfmePod128@@U1@@_STL@@YAXPAUBfmePod128@@ABU1@@Z  (the definition the link keeps is not retail's)
selected  ??$_Destroy@PAUBfmeVectorRecord002AF478@@@_STL@@YAXPAUBfmeVectorRecord002AF478@@0@Z
```

### `_Destroy<BfmeVectorRecord002AF478>` (pin 0x002B0CE7)

The unit's COMDAT copy is **byte-identical to the retail bytes at the pin**
modulo the relocated call (`build/scratch/cmp_obj.py`):

```
ours 25 56 8b 74 24 08 eb 0a 8b ce e8 .. .. .. .. 83 c6 24 3b 74 24 0c 75 f0 5e c3
ret  25 56 8b 74 24 08 eb 0a 8b ce e8 f7 e4 ff ff 83 c6 24 3b 74 24 0c 75 f0 5e c3
reloc at 10 -> ??1BfmeVectorRecord002AF478@@QAE@XZ
```

The remaining difference is the call target, not the code. Retail's
displacement resolves to 0x002AF1EC, whose bytes (`b8 6e 5b b7 00 e8 92 9f 37 00
51 56 8b ...`) do not match the rowed destructor at 0x005EA85F
(`8b 49 20 85 c9 74 05 e9 84 36 a9 ff c3`, `RvaNullReleaseMemberDtors.cpp`,
13 B, matched). So the census refusal is a **relocation-identity/ICF**
difference, not a body-shape difference: do not re-derive this body from
scratch. Either the 0x2B0CE7 pin or the dtor's pinned address needs reconciling
before the copy can be proven retail's.

### `_Construct<BfmePod128>` (pin 0x0032A2AF)

Pin note says `fold-proof=Code/GameEngine/Source/GameLogic/Map/SidesListCastleBuildLists.cpp`;
that unit still compiles 33/33 rows, but its `_Construct` copy is 22 B:

```
57 8b 7c 24 08 85 ff 74 0b 56 8b 74 24 10 6a 20 59 f3 a5 5e 5f c3
```

The pinned bytes start `b8 2b b5 b7 00 e8 cf ee 2f 00 51 8b 4d 08 89 4d f0 83 65 fc 00`
— `mov eax, imm32; call; push ecx; mov ecx,[ebp+8]; and dword ptr [ebp-4],0` —
which is the middle of a function that already uses `ebp`, not a function entry.
The exact 22-byte copy appears nowhere in `.text`
(`build/scratch/find_bytes_retail.py` -> 0 hits), so the producer's shape also
differs from retail's. Both the pin and the body need evidence before this
blocker can be cleared.

## Rva0016DEE0Cluster.cpp: DamageFX hash_map `erase(iterator)` (pin 0x00055612)

`DamageFX_hashtableNewNode.cpp` (368 B) is blocked because the only definer of
`hashtable<pair<const NameKeyType,DamageFX>,...>::erase(_Ht_iterator<...,_Const_traits,...>)`
is `Rva0016DEE0Cluster.obj` (link position 4428) and its copy is not retail's.
Experiments (all reverted):

1. Removing the unit's `template <> size_t vector<void*>::size() const;`
   decl-only makes the copy inline `(finish-start)>>2` exactly as retail does,
   and the row check stays 4/4; the copy shrinks 177 -> 159 B.
2. The remaining difference is retail's frame pointer (`55 8b ec` prologue).
   `#pragma optimize("y", off)` around `#include <hash_map>` has **no effect** on
   the emitted COMDAT (still 159 B, /Oy on), because the member template is
   emitted at end of TU after the pragma is reset.

Remaining route: an explicit specialization of `erase` defined in this TU under
`#pragma optimize("y", off)`, or a producer compiled with `/Oy-`. The consumer
cannot emit its own copy (it does not instantiate `erase`).

## Also checked, no action

- `??_7GameEngine@@6B@` (GameEngineCompleteDestructor.cpp, GameEngineDestructor.cpp):
  the two units emit a 56-byte GameEngine vtable because their class view is
  deliberately partial (comments in both files say so); the first copy
  (GameEngineInit.obj) is 152 B with 38 slots, listed in
  `build/scratch/row_compare.py Code/GameEngine/Source/Common/GameEngineInit.cpp`
  output. Modelling the 26 missing slots would unblock ~39 B of rows; not worth
  the class-view churn alone.
- `?Rva00559B4BCheck` duplicate (Rva00559CE5Wrapper.cpp): `#pragma optimize("y", on)`
  makes the wrapper's copy byte-identical to retail's 25-byte body and keeps its
  row matching, but the census still reports `duplicate` for **both** units, so
  identical duplicates are refused. `static` (internal linkage) removes the
  duplicate but changes the wrapper's own row (FAIL 1/1) — refuted.
