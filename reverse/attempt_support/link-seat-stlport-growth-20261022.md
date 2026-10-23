# Link-repair findings, 2026-10-22 (afternoon seat)

Read-only investigation of three COMDAT blockers that remain after upstream's
decl-only batches and after `link_check.py --refresh` (53 stale objects
recompiled, 92 census definitions replaced). All work was reverted; nothing in
`Code/` was changed by this investigation.

## The census index is stale in two ways: re-verify every blocker live

`tools/link_rank.py` and `reverse/link_status.csv` read the 2026-10-22 18:01
census (`ab9b90af8c`); `tools/link_check.py SOURCE` recomputes the verdict live.

1. **Verdicts drift.** A live rescan of the 326 census two-blocker units found
   **75 that now link**. Examples: `GameLogic/Pathfinder/pathfinder.cpp`
   reports two sole blockers in `link_rank.py` but links live with
   **50,353 B**; `AptOnlineCustomMatchProcessGameSpyResponses.cpp` reports
   `S ?deallocate@?$allocator@G@_STL` but links live with **9,173 B**. Do not
   start from a ranked blocker without running `link_check` on the unit first.
2. **New units are invisible.** `link_check` refuses a source that is not in
   the census ("not in census ae3b3e68e2, so not previewable"). Symbols defined
   only by such a unit show up as `unresolved` in their consumers even though
   `reverse/functions.csv` has a matched row. Example: `Player::hasAnyRequiredSciences`
   (row 0x002AB7FD, 48 B, `Common/RTS/Player_hasAnyRequiredSciences.cpp`) makes
   `GameClient/InGameUISuperweapons.cpp` (1,291 B) report it as unresolved.
   Before treating an `unresolved` blocker as missing work, check
   `reverse/functions.csv` for a matched row of that name.

## CreateAHeroData vtable (VA 0x00C38D88, RVA 0x00838D88)

`Common/System/SaveGame/CreateAHeroDataDtor.cpp` (1,954 B) has a single live
blocker: `??_7CreateAHeroData@@6B@  (first: differs from the first copy in link
order)`. The retail table's four slots are:

```
0x00809D31  ??_E / deleting destructor   (row 0x00409D31, 28 B, this unit)
0x004B3FD0  shared empty RET             (loadPostProcess)
0x00809353  6 B getter                   (row 0x00409353, currently named
                                          ?name@Rva00409353Named@@QBEPBDXZ)
0x00808C11  1,489 B                      (row 0x00408C11, currently named
                                          ?DoXfer@CreateAHeroHero@@QAEXAAVXfer@@@Z)
```

The other two vtable copies disagree with each other:
`CreateAHeroDataCopy.obj` points slots 2/3 at public
`?crc@CreateAHeroData@@UAEXPAVXfer@@@Z` / `?xfer@...@@UAEX...`, while
`CreateAHeroDataCtor.obj` uses the protected spellings (`MAE`). **Neither
spelling has a row, a pin, or any definer anywhere in the tree** (only
`CreateAHeroDataCopy.obj` even mentions them), so copying the first copy's view
into the dtor unit would trade one comdat blocker for two unresolved ones. The
real slot-2/slot-3 identities (0x00409353 and 0x00408C11) are unreconciled with
their current ledger names; that reconciliation, not a class-view copy, is the
prerequisite.

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
## StlportVectorGrowthFootprints: the pins are right, the element views are not

Both pins that `link_check` holds against `WWLib/StlportVectorGrowthFootprints.cpp`
(6,419 B) are **correct**; the unit's class shadows are what is wrong. This
closes the "drop or re-point the pin" lane - every variant was tried live and
reverted.

`??$_Destroy@PAUBfmeVectorRecord002AF478@@@_STL` -> 0x002B0CE7 (25 B):

- Retail's own `_M_clear<vector<BfmeVectorRecord002AF478>>` row at 0x002B0F1E
  calls the body at 0x002B0CE7, and that body calls `0x002AF1EC`
  (`??1Rva002AF6C5Element`, 74 B, `Rva002AF1ECDtor.cpp`).
- There is a second 25-byte twin at 0x005EAA83 whose callee is `0x005EA85F`
  (13 B, shared with GeometryShape). Our `_Destroy` copy is a **masked match**
  there (`build/scratch/check_fold.py`, callee is the unit's
  `??1BfmeVectorRecord002AF478` pin = 0x005EA85F).
- Re-pinning `_Destroy` to the 0x005EAA83 twin is admitted by
  `tools/pin_admission.py --add ... --notes "fold-proof=<unit> ..."` and passes
  `pin_consistency --check`, but it makes the unit **worse**: the census then
  flags `??1?$vector@UBfmeVectorRecord002AF478...` and
  `_M_clear@?$vector@UBfmeVectorRecord002AF478...` as "not retail's body",
  because retail's copies call the 0x002B0CE7 twin (three blockers -> five).
  Reverted.
- The real defect is the dtor identity: `??1BfmeVectorRecord002AF478@@QAE@XZ`
  is pinned at 0x005EA85F, harvested by `locate.py` from this unit's own call
  site (circular); retail's destructor for the element is the 74-byte body at
  0x002AF1EC. Fixing it needs the element class's real layout (members that
  the 74-byte dtor releases), which the unit's `char m_pad[36]` shadow does not
  carry.

`??$_Construct@UBfmePod128@@U1@@_STL` -> 0x0032A2AF (45 B): also correct.

- Retail's caller rows prove it: `push_back` at 0x0032CA14 (stride 0x80) and
  `__uninitialized_fill_n` at 0x0032A2DC both call 0x0032A2AF.
- The body is the 45-byte SEH `_Construct` that calls `T::T(const T&)`; the
  unit compiles the 22-byte `rep movsd` form because it defines
  `_STLP_NO_EXCEPTIONS` and views `BfmePod128` as a trivial POD. The generic
  22-byte body occurs **nowhere** in `.text`
  (`6a 20 59 f3 a5`: 0 hits, `b9 20 00 00 00 f3 a5`: 0 hits), so the class is
  not POD in retail.
- Deleting either pin is also impossible: `stlport_pod_vector_bodies.cpp`'s
  matched `push_back` row calls `_Construct<BfmePod128>` and `build.py` refuses
  the row without the pin ("unresolved call(s): ... (add to reverse/symbols.csv)").

- `?Rva00559B4BCheck` duplicate (Rva00559CE5Wrapper.cpp): `#pragma optimize("y", on)`
  makes the wrapper's copy byte-identical to retail's 25-byte body and keeps its
  row matching, but the census still reports `duplicate` for **both** units, so
  identical duplicates are refused. `static` (internal linkage) removes the
  duplicate but changes the wrapper's own row (FAIL 1/1) — refuted.
