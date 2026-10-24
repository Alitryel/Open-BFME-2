# Rva008312E0StringReplace.cpp link blockers (replaceBase @0x2A610, erase @0x12150)

Session 2026-10-24, model=claude-opus-5-5, link-repair lane.

The unit (rows 0x2AE50, 0x284D0; 1,351 B) does not link because its COMDAT copies of
`?erase@Rva008312E0String@@QAEPADPAD0@Z` (pin 0x12150) and
`?replaceBase@Rva008312E0String@@...` (pin 0x2A610) are not retail's bodies.

- erase: SOLVED in isolation. An out-of-class `inline` definition wrapped in
  `#pragma optimize("gty", on)` / `#pragma optimize("", on)` emits retail's 57 B
  (call [__imp__memmove]) and both rows stay OK 2/2. A declaration-only erase breaks
  bfmeReplaceAliasedRange (its /Ob1 frame slots need the definition).
- replaceBase: every instruction matches retail except the frame: ours `sub esp,0x44`,
  retail `sub esp,0xd4` (this at [ebp-0xd4]; 30 B longer from disp32 encodings).
  0x90 = insertRange's own frame (retail 0x284D0 `sub esp,0x90`), i.e. retail's
  /Ob1 reserved the slots of the declined insertRange inside replaceBase.
  * `inline` on insertRange's definition: replaceBase 279 B, frame 0xc4 (0x10 short),
    but bfmeReplaceAliasedRange frame 0x9c -> 0x104 (row FAIL). With unoptimized
    in-class erase: replaceBase 0xc8, bfmeReplaceAliasedRange 0x10c.
  * `#pragma inline_depth(2)` around bfmeReplaceAliasedRange: no effect on its frame.
  * moving replaceBase out of class after insertRange: no effect (c2 sees the whole TU).
  Open: why retail's bfmeReplaceAliasedRange does not reserve insertRange's slots while
  replaceBase does, and the missing 0x10 (nested declined callees inside insertRange?).
- 0x2A610 is currently rowed by an inline-asm lift (`BfmeConv1464.cpp`
  `BfmeStrV24::bfmeReplaceV24`); a matching replaceBase here would also retire that lift.

`variant-inline-insertrange.cpp.txt`: the source with optimized erase, out-of-class
replaceBase and inline insertRange (replaceBase 0xc4, bfmeReplaceAliasedRange FAIL).
