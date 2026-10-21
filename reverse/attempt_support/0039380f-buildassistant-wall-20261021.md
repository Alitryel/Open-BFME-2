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

## Landed exact (2026-10-21, claude-opus-5-5)

The stack-packing residue (bank 0.88, 120 differing bytes) came from address escape, not from declaration order.
`delta.length()`, `normalize()` and `toAngle()` called non-visible out-of-line Coord3D/Coord2D members. c2 therefore treated each `this` as escaping, which extended those locals' live ranges to the end of the function.

The fix is to give those callees visible `__declspec(noinline) inline` bodies in the TU:
- `Coord3D::length` and `Coord3D::normalize`;
- `Coord2D::toAngle` (with an inline `Coord2D::length`).

The calls stay out of line at retail 0x3571, 0x35B6 and 0x5923. With the visible bodies, the colouring matches retail exactly: frame `sub esp,0xe8`.

Combined with the CtorView headers, the member-wise unit and the ctor-form steps, this gives an exact 2217 B match. It lives in `Code/GameEngine/Source/Common/System/BuildAssistantWallLocations.cpp`.

What did not get there:
- Making only length and normalize visible still left 32 differing bytes. The delta2/loop-$T colour was wrong until toAngle was visible too.
