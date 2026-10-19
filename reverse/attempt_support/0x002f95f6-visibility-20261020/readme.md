# Pathfinder::FindGroundPath (0x002F95F6, 1988 B): callee visibility

Target: `?FindGroundPath@Pathfinder@@QAEPAVPath@@PAVObject@@PBUCoord3D@@1H@Z`, retail RVA 0x002F95F6, 1988 bytes, `/O1 /G7 /arch:SSE`. Identity is unchanged from the earlier verdicts: WB 0xD337F0 `Pathfinder::FindGroundPath` (pathfinder.cpp assertions 868..993) and the native boundary 0x2F95F6..0x2F9DBA. Model: claude-opus-5-5, 2026-10-20.

## Result

Banked as partial. The new bank is closer than the farm bank in every class that `tools/align_diff.py` reports, and it drops the two steering hacks the farm bank carried.

| measurement (align_diff, 1988 B) | farm bank (2026-10-17) | new bank |
|---|---|---|
| emitted size | 1997 B | 1981 B |
| structural regions | 36 | 12 |
| memory operand differences | 94 | 63 |
| register operand differences | 32 | 20 |
| frame (`sub esp`) | 0xAC | 0xAC (retail 0x94) |
| differing retail instructions, relocation fields masked | 140 of 652 | 93 of 652 |

The score passed to `re_log.py` is 1 - 93/652 = 0.857 under that masked count; the farm's 0.747 used a different count.

## The finding: retail compiled these callees in the same unit

Retail keeps `newCellCoord.x` in `edi` across calls that receive `&newCellCoord` (the 0x002E8B7A pool call at +0x5F0 and CalcExtraCosts at +0x643) and still reads x from `edi` afterwards (+0x617, +0x684). MSVC 7.1 only does that when the address does not escape, which needs the callee bodies in the same translation unit. The address flows into four retail functions, and all four compile byte-exact in this bank's context, so making them visible is consistent with retail building them in the same unit:

- 0x002E6BA1 `Rva002E6BA1::rva002E6BA1` (65 B, already rehomed into `pathfinder.cpp` on 2026-10-13).
- 0x002E8B7A `Rva002E8B7AInit` (33 B, same).
- 0x002EBC7F `rva002EBC7F` (40 B, row in `Code/GameEngine/Source/GameLogic/AI/Rva002EBC7F.cpp`). CalcExtraCosts passes its `destination` here, so without this body `&newCellCoord` still escapes. This one body is the switch: adding it moves `edi` from the neighbour cell to x and spills the neighbour to [ebp+0x54] exactly as retail does.
- 0x002F69E3, the `Rva002F4491Info` line walk (256 B, row in `Code/GameEngine/Source/GameLogic/AI/PathfinderCellLineWalks.cpp`). With it visible, the line-walk `start`/`end` stores are scheduled field by field as in retail (+0x3F6..+0x43A).

The template pointer is now an ordinary `PathfinderTemplateView *`. Retail loads it once and reads priority and flag through one register (+0x31C..+0x32E), which the non-volatile spelling reproduces exactly, so the old `volatile` member was a codegen lever that made that block worse. The `_ReadWriteBarrier` and `nx`/`ny` temporaries of the ring search are gone; the ring is ZH's plain `cell.x += offset` form.

## What remains

1. Ring search (+0x154..+0x237): ours updates `cell` with read-modify-write (`add [ebp+0x60],eax; push [ebp+0x60]`), retail computes into `eax`, pushes and stores. That is the shape of a non-escaping `cell`, and `cell` escapes through `Rva002E7875WorldToCell` (0x002E7875), which the bank only declares. Making 0x002E7875 visible as well (it is already defined in `pathfinder.cpp`) makes all eight probes match retail, but between the ring and the main loop `edi` then stays with `diameter` instead of passing to `goal` (+0x26C `mov edi,eax` and +0x770 reload), and the main loop's failure tail is laid out after the first test instead of at the end. That variant measures 2015 B, 14 regions, 148 memory, 19 register. Retail evidently had both: a non-escaping `cell` and `goal` in `edi`. Finding the source difference that keeps `goal` in `edi` with 0x002E7875 visible is the next experiment.
2. Frame 0xAC against 0x94. Retail packs the line-walk `end` at [ebp+0x24] (inside `adjusted`) and the trigger `world.y` spill into `hierarchicalTarget`; ours keeps them apart. Declaration order of `adjusted`/`clipped` was tested and is inert.
3. The two floor sites (+0x6B6, +0x6DB): retail `call [floor]; pop ecx; fstp; pop ecx`, ours `call; fstp; pop ecx; pop ecx`. Neither removing `math.h` nor the ZH `fast_float2long_round((float)floor(...))` spelling changed it.

## Hypotheses ruled out this run

- `/Oa` and `/Ow` (no-alias compiles): they change only one site, hoisting the TheTerrainLogic load above the `m_isTunneling` store at +0xDA, which is against retail, and leave the neighbour loop unchanged. Retail obeys aliasing there.
- Register priority: up to eight extra uses of `newCellCoord.x`, before or after the calls, never win `edi` while the struct's address escapes, with or without `/Oa`. The field is not a register candidate until the escape is removed, so no spelling of the loop can fix it.
- ZH-scoped loop declarations (`newCellCoord`, `newCell`, `newCostSoFar` at while-body scope) are inert on their own.
- Definition order of the visible helpers is inert, as docs/matching.md says. A `for(;;)` spelling of the main loop is worse (17 regions).
- Owner context without 0x002EBC7F: compiling this body inside a copy of the current `pathfinder.cpp` gives 2019 B, 36 regions, frame 0xA0 (the same as the W9-A1 verdict). Adding a visible 0x002EBC7F there gives 2015 B, 15 regions, 147 memory, 19 register, the same as remaining item 1.

## For the landing

The body belongs in `Code/GameEngine/Source/GameLogic/Pathfinder/pathfinder.cpp` (WB's file; it holds CalcExtraCosts, 0x002F0A72, AddToOpenList and the rehomed pool helpers). A landing there needs 0x002EBC7F and the 0x002F69E3 walk visible in that unit, which means rehoming their rows the way 0x002E8B7A was rehomed, then re-verifying every row of the unit (CalcExtraCosts and CalcCollisionFreeExtraCosts also call 0x002EBC7F). Reproduce the owner trial by copying `pathfinder.cpp`, adding `FindGroundPath`, `rva002E7749` and `BuildGroundPath` to `class Pathfinder` plus the private `iterateCellsAlongLine(const ICoord2D *, const ICoord2D *, PathfindLayerEnum, Rva002F4491Info *)` overload, appending the bank's `GroundMovementQuery`, `Rva002F4491Info`, `GroundTriggerGrid` and direction tables with the body, and turning relative includes into absolute paths for a scratch path.
