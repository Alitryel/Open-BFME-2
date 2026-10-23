# Link lane: 341 units recoverable by dropping wrong local copies

Measured 2026-10-19 against the published census index (published at
`1e807fb266`; refresh with `tools/link_check.py --fetch-index`, which also brings
the compiled objects). `tools/link_rank.py` then reports

    20,332 of 23,246 authored units link (5,533,448 of 7,208,341 matched bytes)

## The candidate list

A unit that is *unlinked* but whose blockers are only duplicate/losing local
copies (no unresolved name, no `wrong_selected`, no bad address) can often be
repaired without touching bytes. Load the index and filter:

```python
import sys; sys.path.insert(0, 'tools')
import link_check as L
ix = L.load_index()
for src, info in ix['blockers'].items():
    if info.get('linked'):
        continue
    if info.get('unresolved') or info.get('wrong_selected') or info.get('addresses'):
        continue
    if info.get('duplicates') or info.get('losers') or info.get('unreferenced_differs'):
        print(ix['bytes'][src], src, info)
```

That yields **341 clean units** (plus 1,691 whose record also carries a harder
blocker). Ranked head, held-out bytes first:

```
11022  Code/GameEngine/Source/GameLogic/AI/AIAttackApproachTargetStateOnEnter.cpp      lose=5
 4387  Code/Libraries/Source/WWVegas/WW3D2/LineGroupClassRender.cpp                    lose=10
 3376  Code/Libraries/Source/WWVegas/WW3D2/PointGroupClassRva00179B50.cpp             lose=8
 3098  Code/GameEngine/Source/GameLogic/System/LivingWorld/LivingWorldRegion.cpp      dup=25
 2758  Code/GameEngine/Source/GameLogic/AI/AIGroupMoveFormation.cpp                    lose=4
 2487  Code/Libraries/Source/WWVegas/WW3D2/MeshClassRenderWithFXMaterial.cpp          lose=6
 2245  Code/GameEngine/Source/GameLogic/Map/TerrainLogicXfer.cpp                      lose=9
 1873  Code/GameEngine/Source/GameClient/GUI/ControlBar/UnitHelpSource.cpp             lose=1
 1663  Code/GameEngine/Source/GameNetwork/GameSpy/PeerDefsGameOptions.cpp              lose=2
 1640  Code/Libraries/Source/WWVegas/WWLib/stlport_narrow_ifstream.cpp                 lose=2
 ...
```

(`build/scratch/link_candidates.py` and `build/scratch/blocker_lookup.py`
reproduce this; both are scratch, untracked.)

## The recipe that works (established upstream)

Commit `52a2fc5046` ("Drop unreferenced unit-local inline copies in 189 more
units", +370 blockers cleared) puts

```cpp
__declspec(dllimport) __forceinline <existing inline body>
```

on a private view's inline method. `dllimport` suppresses the local COMDAT
emission; `__forceinline` keeps the unit's call sites compiling to the same
bytes. It applies only when the unit does not need the *out-of-line* copy.

## What I established (and what does not work)

* **The biggest single shared cause I found: `?isDisabled@Object@@QBE_NXZ`
  (`wrong_selected`, 6,333 bytes over 5 units).** Retail at `0x0023D394` is not a
  getter at all but an adjustor thunk:

  ```
  0x0023d394  add ecx, 0x1c8
  0x0023d39a  jmp 0x23c58b        ; BitFlags<11>::any(), out of line
  ```

  The matched row lives in
  `Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarRappellerCount.cpp`
  L336 (`return m_disabled.any();` where `any()` is not inline, so it tail-calls)
  -- offset **0x1C8**. `CashHackSpecialPowerAction.cpp` L32 and
  `GrabPassengerSpecialPowerDoAtObject.cpp` L29 agree (0x1C8), but the shared
  header `Code/GameEngine/Source/GameLogic/System/LogicDispatch/headers/gamelogic/object.h`
  L605 says `((const DisabledMaskType*)((const char*)this + 0x1A4))->any()`
  -- **0x1A4**, a different body. Any unit that emits that view's COMDAT is the
  wrong provider the census keeps, and the five correct units then fail
  `wrong_selected`. The cheap repair is `__declspec(dllimport) __forceinline` on
  every *wrong* emitting view (call sites stay inlined, so their matched bytes do
  not move) so the correct thunk wins; fixing the header's offset instead moves
  the inlined call sites of every unit that includes it and needs those rows
  re-verified first.
* **Folded alias rows cannot be repointed with `add_match`.** `0x00254B72` is an
  ICF fold with four ledger names (`??1Rva00254B72@@QAE@XZ`,
  `??1Rva0041573FArray@@QAE@XZ`, `??1BfmeObject544Array@@QAE@XZ`,
  `??1Rva00254FE4Member@@QAE@XZ`); `add_match ... --replace-existing` refuses
  because the RVA is already claimed by the first. `tools/rehome_rows.py --apply`
  therefore reports those as FAILED and moves nothing, even when its dry run
  prints MATCH. A move here needs a ledger edit by hand, not that tool.
* **A referenced `__declspec(noinline)` specialization is not fixable this way.**
  `UnitHelpSource.cpp` L22 specializes
  `StringBase<unsigned short>::isEmpty` as `noinline` precisely so its call sites
  match retail's *call*. Marking it `dllimport` turns the call into an indirect
  `__imp_` call (bytes change, rows break); making it `forceinline` inlines the
  call (bytes change too). The remaining repairs are either making the emitted
  body byte-equal to the kept copy or dropping the local emission while keeping
  the direct call -- neither is a one-attribute edit.
* **vftable + implicit dtor losers are class-level, not member-level.**
  `AIAttackApproachTargetStateOnEnter.cpp` (11,022 B, the largest clean unit)
  loses only `??_7...@@6B@` vftables and their implicit `??1...` dtors for three
  `Rva000421C8`-derived filters. `__declspec(novtable)`/`dllimport` on the class
  changes the vptr stores (bytes change); the honest fix is reconciling the
  class view. `tools/class_views.py --class Rva000421C8` shows 185 units, 52
  layouts, **header: -** (no canonical header yet) -- that is the prerequisite
  for this family, and `header_adopt_lane.py order` is the lane.
* **`0x004FF207` landed while I worked it** (`?rva004FF207@Rva004FF207@@QAEXXZ`
  in `Code/GameEngine/Source/Common/Rva004FF28ECtor.cpp`, 135 B), from the same
  WorldBuilder evidence; the banked body and its handoff were dropped.
* `0x00629188` is **`__EH_prolog`**, so the `mov eax, <big immediate>; call`
  head of many bodies (0x002D0A9, 0x00568182, 0x005E8DCF, 0x00333F37, ...) is a
  normal SEH prologue, not a mis-detected boundary.

`t=120 model=deepseek-v4.1-flash-free`
