# Locomotor 0x001E6B8B: landed, with an honest one-state EH frame (2026-10-20)

Landed byte-exact (919 B), with its EH handler 0x00769FEE (10 B), in
`Code/GameEngine/Source/GameLogic/Object/LocomotorMoveTowardsPositionHorde.cpp`.

## The D8 scheduling wall
In the home unit the visible bodies of 0x1E685F, 0x1E56DC and 0x1E6007 keep the
goal copy from escaping, so retail's early `cmp [eax+0xd8]` happens without any
scheduling work. The wall only appeared in the standalone bank.

## The EH frame (FuncInfo 0xD3D650: maxState 1, {-1, NULL}, no try blocks)
WorldBuilder's unwind map shows the source of the frame:
- states 0 and 1 run the empty `~Coord3D` (wb 0x419060) for delta and goalPos;
- state 2 runs `~AsciiString` for `mcond` in a `D_ISLOG()` block (wb 0xAE8640).

The honest release form needs both of the following:
1. **Coord3D's empty user destructor** (retail row 0x000B3FD0, a lone `ret`):
   `#define COORD3D_VIEW_DTOR` before `Lib/Coord3DCtorView.h`.
2. **The twin's debug block as release compiles it**, with `D_ISLOG()` false and `DLOG` as
   `((void)0)`:
   `if(D_ISLOG()){ AsciiString mcond; ...rva000467B2(&mcond,1); DLOG(...); }`

What does not work:
- Any one of the two alone, the block without the call, or the call without the AsciiString:
  902 B and no frame.
- With a POD Coord3D, a constant-false block keeps the frame only when the function also has
  live objects with a user destructor.

## Same frame elsewhere
GameText.cpp `load` and HordeAIUpdatePoolKey.cpp share FuncInfo 0xD3D650. Both still use
the dead-static hack. GameTextTable::load's twin has an `if(0)` dump block with an
AsciiString, so both are worth re-testing with this mechanism.

Scratch: `build/agM/` (`funcinfo.py` dumps FuncInfo and the unwind map; `rows.py` scores
every row of the unit).
