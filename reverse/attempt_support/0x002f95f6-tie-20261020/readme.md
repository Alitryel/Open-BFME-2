# Pathfinder::FindGroundPath (0x002F95F6, 1988 B): floor sites, ring, goal tie, frame

Target `?FindGroundPath@Pathfinder@@QAEPAVPath@@PAVObject@@PBUCoord3D@@1H@Z`, retail RVA 0x002F95F6, 1988 bytes. This round follows `../0x002f95f6-visibility-20261020/readme.md`. Model: claude-opus-5-5, 2026-10-20. Every result below is a single compile (n=1) measured with `tools/align_diff.py` at 1988 B.

## Result

Banked as partial: the floor-site fix alone, on top of the committed bank.

| bank | size | regions | memory | register | frame |
|---|---|---|---|---|---|
| committed bank (visible helpers) | 1981 B | 12 | 63 | 20 | 0xAC |
| new bank (plus floor fix) | 1981 B | 8 | 63 | 20 | 0xAC |

All eight remaining regions are the ring search (+0x154..+0x237). With relocation fields masked, 91 of 652 retail instructions differ (93 before), score 0.860.

## Findings

1. **Floor sites (+0x6B6, +0x6DB), fixed.** Retail's trigger-grid test floors through `math.h`'s float overload `floor(float)` and then rounds with `fld`/`fistp`, which is how `pathfinder.cpp` already spells its clip (`clipCellFloor`, `clipCellRound`). That gives retail's `call [floor]; pop ecx; fstp; pop ecx`. The bank now uses the same two helpers in `GroundTriggerGrid::isMarked`.
2. **Ring search, fixed only with WorldToCell visible.** With 0x002E7875 `Rva002E7875WorldToCell` visible (`worldtocell-visible.txt`), `cell` no longer escapes and all eight ring probes match retail.
3. **The goal and diameter tie (open).** With WorldToCell visible, `edi` stays with `diameter` from the ring to the main loop, where retail gives it to `goal` (+0x26C, reload at +0x770). That also moves the main loop's failure tail, so the body grows to 2015 B. The gap is one reference:
   - One extra use of `goal` anywhere outside the inner loop (sink probe `goal-probe.ed.txt`) flips `edi` to `goal` and restores retail's whole layout.
   - Dropping either loop-head reference to `diameter` (`info.diameter`, or the BuildGroundPath argument) also flips it.
   - WB's references to `goal` (`local_68`) and `diameter` (`arg_3`) match the body one for one, so no missing statement was found.
4. **Frame packing.** Visible copies of 0x002E75A3, 0x002E7917 and 0x002E8BF8 (`clip-helpers-visible.ed.txt`) take the frame from 0xA8 to 0xA0. Retail's 0x94 needs `hierarchicalTarget` not to escape. A visible stand-in for `internal_findHierarchicalPath` (diagnostic only, not code to land) gives frame 0x94 with every slot matching except one byte flag: the `rva0028AC62` result sits at +0x4C in retail and +0x4F in ours.
5. **Combined diagnostic.** Bank + WorldToCell + clip helpers + floor fix + goal sink + stand-in gives 1 region (the sink store itself), 18 memory lines (16 unrelocated global slots, plus the store and load of the +0x4C byte) and 0 register differences, at frame 0x94. So, apart from the tie and the byte flag, the body is complete once its same-unit callees are visible.

## Byte checks of the helper copies in the bank context

- 0x002E7749 `rva002E7749` (300 B): exact.
- 0x002E75A3 (304 B): structure exact; its memory lines are relocation constants.
- 0x002E8BF8 (43 B): exact.
- 0x002E7875 (162 B): structure exact; its memory lines are relocation constants.

## Tried without effect on the tie (n=1 each)

- ZH-faithful locals: `centerInCell`/`isHuman`, `MAX_OFFSET`, a `to` pointer, a function-scope `startCellNdx`, the parent declaration form, and `zone1, zone2` declared first.
- The `(0,0)` and `m_isMapReady` returns split into two ifs (as in WB), and the combined inner-loop conditions.
- Info and start/end statement order (the ZH order is worse), and removing the line-walk block braces.
- Assigning or declaring `goal` earlier.
- Visible copies of 0x002E7749 and of the 0x002F4491 line callback.
- Plain `inline` instead of `__forceinline` for `allocateInfo`/`isMarked`: not inlined, much worse.

## Next steps

- 0x002F71A6 `internal_findHierarchicalPath` (unrowed, bank `reverse/attempts/0x002f71a6.cpp`) must be matched before this body can reach retail's frame in `pathfinder.cpp`.
- The goal tie needs a natural source difference worth one reference. The probes above show it is exactly one reference on either side.
- `mk.py.txt` rebuilds trial sources from a copy of the bank plus `.ed` edit files (blocks of `OLD`, `=====`, `NEW`, separated by `%%%%%`).
