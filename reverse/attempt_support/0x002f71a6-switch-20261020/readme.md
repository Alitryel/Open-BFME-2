# 0x2F71A6 Pathfinder::internal_findHierarchicalPath, r14 handoff (2026-10-20)

Bank: `reverse/attempts/0x002f71a6.cpp`, fit 0.99893, length 4605 (exact), 3 differing
instructions. Model claude-opus-5-5. Earlier handoff: `../0x002f71a6-exit-20261020/`.

## What fixed the register shape (target evidence)

The WorldBuilder twin (D4FAE0) has a switch temp (`local_8e8`) in the mineshaft
waypoint scan, so the type test is a `switch`, not an `if`:

```cpp
for(Waypoint *way=...getFirstWaypoint();way;way=way->next) {
  switch(way->type) { case 8: if(... && way->isValidUnitType(obj)) { ... } break; }
}
```

With the for-scoped `Waypoint *way` cursor this alone reproduces all four retail
register shapes the r13 handoff attributed to a "branch-count threshold": entry
rawTo in esi / from in edi, cursor in edi with home `[ebp+0x2c]`, `xor edi,edi`
zero register after the loop, and rawTo reloaded into esi at the loop exit.
The entry `_ReadWriteBarrier()` was removed; the closest-path tail now names
`PathfinderGroundInfo *info=candidate.cell->m_pathInfo;` before the call.

`ev.py.txt` prints shape flags E/C/Z/R plus fit for a list of variants.

## Remaining residue (3 instructions, retail 0x141..0x164 relative)

Retail:
```
mov eax,[ebp+0x68]; movss xmm1,[esi+4]; movss xmm0,[esi]; subss xmm0,[eax+0x38]
movss [ebp-0x40],xmm1; subss xmm1,[eax+0x3c]; movss [ebp-0x44],xmm0
movaps xmm0,xmm1; movss xmm1,[ebp-0x44]
```
Ours:
```
mov eax,[ebp+0x68]; movss xmm0,[esi]; subss xmm0,[eax+0x38]; movss xmm1,[esi+4]
subss xmm1,[eax+0x3c]; movss [ebp-0x44],xmm0; movaps xmm0,xmm1; movss xmm1,[ebp-0x44]
movss [ebp-0x40],xmm0
```
Retail stores the *unsubtracted* loc.y into delta.y (-0x40) and never stores the
subtracted y back: the copy is kept but y's in-place subtraction is dead-store
eliminated into a register (delta.y only feeds the dist), while x's difference is
spilled. Only the first delta (way->location - obj position) differs; the second
(way->location - rawTo) matches.

## Disproved in r14 (g23..g25)

inline `Sub`/`LengthSqr2D` helpers (pointer and reference forms), an empty
destructor on the HierarchyPoint local (WB EH states), ctor field order, subtraction
order xyz/yxz/xy/yx/zxy, dist expression order, a `const Coord3D *pos` local,
`Coord3D delta=way->location` (worse, len 4600).

## Untried ideas

A separate y temporary; delta declared outside the loop or before the switch; a
distinct second delta variable; a getPosition()-style inline accessor returning
`const Coord3D*`; differences computed without in-place stores; `Real` typedefs.
