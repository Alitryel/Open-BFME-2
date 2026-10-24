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

## 2026-10-24 follow-up (claude-opus-5-5): a route that closes both blockers

Unit Rva008312E0StringReplace.cpp (1,351 B: 0x2AE50 + 0x284D0) is blocked by its COMDAT copies of erase and replaceBase.

1. **erase is solved.** See `rva008312e0-step1-erase-bound.cpp.txt`. Drop the class's own `erase`, `move` and `m_start/m_finish/m_end`. Derive `Rva008312E0String` from a TU-local full specialization `_STL::basic_string<char, char_traits<char>, allocator<char> >` that holds an inline `erase`, a static `move` and the three members. The COMDAT is then `?erase@?$basic_string@D...`, retail's rowed 0x12150. `./build.sh` passes 2/2 and link_check names only the replaceBase blocker.
2. **replaceBase: give retail's copy a proven owner.** See `bfmeconv1464-template-trial.cpp.txt`. It replaces the inline-asm lift in BfmeConv1464.cpp (row bfmeReplaceV24 0x2A610) with the step-1 view, and changes three things:
   - `replaceBase` becomes a member template `<class _ForwardIter>`;
   - `insertRange` becomes `inline`;
   - `__copy_trivial` becomes an inline definition. This is the decisive trial; the frame sizes were:

     | Trial | Frame |
     |---|---|
     | only `_Destroy` inline | 0xc4 |
     | allocate inline | 0xc8 |
     | `__copy_trivial` inline | 0xd4, retail's |

   The TU ends with `template Rva008312E0String &Rva008312E0String::replaceBase<char *>(...)`. The emitted `??$replaceBase@PAD@Rva008312E0String@@QAEAAV0@PAD000ABURva008312E0Tag@@@Z` is 279 B and matches retail 0x2A610 instruction for instruction, with the frame `sub esp,0xd4` and only the branch and call targets left to compare: assign 0x13270, erase 0x12150, insertRange 0x284D0. Relocations are not yet checked against the gate.
3. **Not done (wind-down):**
   - Repoint row 0x2A610 from `?bfmeReplaceV24@BfmeStrV24@@...` to the template name. `add_match --replace-rva` accepts only scaffold rows, so use `tools/rename.py` or docs/naming.md.
   - Drop the then-unused pins bfmeCopyChV24 and bfmeEraseV24.
   - In Rva008312E0StringReplace.cpp, make replaceBase the same member template (`_ForwardIter __m = __f;`) so its COMDAT name matches. Keep bfmeReplaceAliasedRange's frame at 0x9c and check it with ./build.sh.
   - Run link_check --refresh on both units. The expected gain is +1,351 B plus BfmeConv1464's own.
   - The BfmeConv1464 TU also emits an 863 B insertRange copy (frame 0xac), which is not retail's. Under retail-truth-3 it should lose to the proven Rva008312E0StringReplace copy; verify this with link_check.
