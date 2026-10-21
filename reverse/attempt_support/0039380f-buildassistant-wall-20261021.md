# 0x0039380F BuildAssistant::rva0039380F (wall layout), 2026-10-21

Model: claude-opus-5-5. Bank before: 0.845, 168 differing bytes, frame 0xF0.
New bank: 120 differing bytes (2224/2217 B). Every register now matches retail.
What is left is stack-slot packing: frame 0xF4 against retail's 0xE8, plus
disp8/disp32 growth and a small reordering in the hub block (+0x6c9..+0x6f4).

## What closed the register allocation (factorial, 1368 compiles)
Eleven factors were crossed (generator: `build/b38/fgen.py`).
- `Coord3D previous=current;` as a struct copy (movsd x3), restored with
  `current.z=previous.z`. Earlier rounds disproved this alone (the 0 in edi);
  it works together with the next two changes.
- `terrainPiece=module->getTerrainPiece();` written plainly. The bank's
  `(index?..:..)` hack is no longer needed.
- `half=...getBoxMinorRadius(); half-=1.f;` in both places.
- Loop step written member-wise, y first:
  `Coord3D step; step.y=half*unit.y; step.x=half*unit.x; step.z=0.f;`.
  WB evaluates the y temp first.
- Keep `connected = endAtObject && ...`. The if-form is worse.

Inert or worse: `endPoint=*end` (+130), ternary hub, brace hub step,
funds/index order, the `blocked` if-form, member-wise diff.
The terr hack variant reaches 72 bytes, but only by adding a branch and call,
so it is not honest code.

## Slot gap (from /FAs: `build/b38/slots.py SRC`)
| Item | Retail | Ours |
|---|---|---|
| filter $T + delta + loop step.x | -0x68 | delta alone at -0x8c (the extra 12 B) |
| loop step.y | -0x84, inside delta2's 8-byte slot | |
| hub step.x | previous colour (-0x98) | |
| hub step.y | module colour (-0x34) | |
| endPoint + diff | -0x5c | |

So retail scalar-replaces both step structs.

## New lead, not finished
`Lib/Coord3DCtorView.h` and `Coord2DCtorView.h` describe Coord3D with user
constructors. In WB every Coord3D/Coord2D local has an EH state.
- With ctor-form steps `Coord3D step(unit.x*half,unit.y*half,0.f)`, the hub
  step moves into previous' colour as in retail (`build/b38/c/c1.cpp`,
  120 -> 129 bytes; new 4-byte $T temps at -0x70).
- `delta`/`diff` in ctor form evaluate the subtractions right to left, which is
  wrong. Keep those member-wise.

Next: cross header (POD / CtorView / + `COORD3D_VIEW_DTOR`) with the step,
delta, delta2, unit and diff forms, ranked on differing bytes and frame
`sub esp,0xE8`.
