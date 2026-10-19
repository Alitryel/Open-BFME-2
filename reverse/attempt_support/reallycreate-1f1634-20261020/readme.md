# GenericObjectCreationNugget::reallyCreate (0x001F1634, 2618 B)

## Result

Partial bank: `reverse/attempts/0x001f1634.cpp` now holds a complete, semantically correct reconstruction that emits 2614 B against retail's 2618 B. `tools/align_diff.py` reports 5 structural regions, 31 memory, 3 register, 94 branch and 17 reloc operand differences (`align-after.txt`). Of the 31 memory lines, 26 are global or static data addresses (`[0]` against `[0xdf....]`), which the gate fills from retail, so 8 operand lines are real. The previous farm bank emitted 444 B (27 regions, under three quarters of the retail size, so its region count is not comparable; `align-before.txt`), dropped most of the body and returned the wrong type.

The bank defines `?reallyCreate@GenericObjectCreationNugget@@QBE?AV?$vector@PAVObject@@V?$allocator@PAVObject@@@_STL@@@_STL@@PBUCoord3D@@PBVMatrix3D@@MPBVObject@@I@Z`. Retail returns a 12-byte `vector<Object*>` through a hidden pointer (`ret 0x18`, copy constructor 0x001F206E into `[ebp+8]`, result-constructed flag at `[ebp-0x28]`). The consumers 0x001F14B6 and 0x001F2F0E call the existing pin `?reallyCreate@...QBE?AUNuggetCreated@@...`, a storage view derived from the same vector. Landing needs one name for the address; the coordinator chooses which.

## What blocks an exact landing

Two calls have no row or pin, and this seat could not add pins:

1. 0x001F21E8 (187 B, unrowed). Thiscall, `ret 4`, own EH frame (handler 0x0076B1C0). It walks TheTerrainLogic's waypoint list (virtual +0x84 first, +0x1C next), collects waypoints whose name (+0x08) starts with the nugget's +0x10C string, picks one with GameLogicRandomValue at line 0x7B5 and copies its location (+0x0C) into the Coord3D argument. Its only caller is this body (0x001F1C01). The bank calls it as `?rva001F21E8@GenericObjectCreationNugget@@IBEXPAUCoord3D@@@Z`. It is a unique body, not a fold, so the cleaner route is matching it rather than pinning.
2. 0x00211E58, called with the default-argument allocator temporary at `[ebp-0x39]`. The bank declares `vector<Object*>::vector(const allocator<Object*>&)` as an explicit specialisation so the call stays out of line (`??0?$vector@PAVObject@@V?$allocator@PAVObject@@@_STL@@@_STL@@QAE@ABV?$allocator@PAVObject@@@1@@Z`). The 29 bytes at 0x00211E58 are that constructor's body (zero +0 and +4, `_STLP_alloc_proxy` constructor 0x0054F3C4 on +8, `ret 4`); they are folded with the `_Vector_base<int>` and `<GameWindow*>` constructors already named there. A pin needs fold-proof: compile that constructor out of line with these flags and byte-compare it, including the REL32 to 0x0054F3C4.

Data references that need the data ledger's names checked: TheThingFactory 0xDFF000, ThePlayerList 0xDFEEE8, TheBuildAssistant 0xE027B8, TheTerrainLogic 0xDFEC50, TheGameLODManager 0xDFE144, TheScriptEngine 0xDFE16C, TheAI 0xDFF0F8 (converged; declared `class AI; extern AI *TheAI;` and cast), TheAudio 0xDFE6E8, the function static 0xDFDCDC with guard bit 1 at 0xDFDCE0, AsciiString::TheEmptyString 0xDE0878.

## Remaining mismatch (all measured on the bank)

- EH states for two objects whose destructors are empty. Retail gives the default-argument allocator temporary state 3 and the vector a separate state 4 while that temporary lives (both unwind actions are real: `lea ecx,[ebp-0x39]; jmp 0x000B3FD0` and `lea ecx,[ebp-0x34]; jmp 0x001F22A3`), and gives the horde member list returned by virtual +0x108 state 7 (unwind to 0x000B3FD0, the shared empty `ret`). Our compile drops all three states, so it emits `mov byte [ebp-4],0` instead of `mov dword [ebp-4],3`, misses `mov byte [ebp-4],7`, and every later state number is shifted (5 operand lines). Ruled out: an out-of-class empty destructor defined before or after the function, the `vc71-sp1` compiler, dropping `/D_STLP_USE_MALLOC`, and adding `/Ob1` (passed to cl, no change). The copy constructor unit 0x001F206E gets no state for its `get_allocator()` temporary with the same headers, so the difference looks specific to retail's ObjectCreationList.cpp build; 0x001F21E8 in the same retail unit also gives its allocator temporary a state.
- One instruction of scheduling in the random pick arguments (`dec eax` before rather than after `push file`); `(Int)size() - 1` did not move it.
- GameLODManager::isDebrisSkipped: retail `mov edx,ecx; and edx,[eax]; cmp edx,ecx`, ours `mov eax,[eax]; and eax,ecx; cmp eax,ecx`. Operand order, Int against UnsignedInt members and an out-of-class inline definition all gave the same code.

## Levers that worked (in the order found)

- KindOf tests: a word-array view whose `getWord` returns a const reference, with `test` and `isKindOf` forced inline. This gives retail's `test byte [x+0x114],0x10` and the merged `test byte [x+0x113],0xc0`. A by-value word or a plain mask expression gives `shr`/`test al,1`; the real STLport `bitset::test` is not inlined.
- Making `vector<Object*>(const allocator&)` opaque fixed the frame (allocator temporary at `[ebp-0x39]`, frame 0x1F0) and most stack offsets.
- `m_names` as a real `_STL::vector<AsciiString>` fixed the pick register (ecx) and the cross-jumped waypoint and spread call tails.
- Inline accessors for the player's +0x3BC flag object (`lea esi,[eax+0x3bc]` before the byte read) and for TheAI's pathfinder at +0x10.
- The spread-formation flags built in a separate local (`mov esi,0x80`, stored last), as in WorldBuilder.
- The waypoint start position copied member by member (retail uses `movss`, not `movsd`), while the fallback `resultPos = *sourceObj->getPosition()` is a block copy.

## Identity evidence

- Boundary: retail 0x001F1634..0x001F206E. The previous function 0x001F1609 ends with `ret` at 0x001F1633; the rowed vector copy constructor starts at 0x001F206E. FuncInfo 0x00D10624 (9 states) via handler 0x0076B194.
- WorldBuilder 0x00B050F0 `GenericObjectCreationNugget::reallyCreate`, ObjectCreationList.cpp, asserts 1592..1808, match score 1.0; its statement order is followed throughout. The random calls carry that file's lines 0x67D and 0x710.
- Zero Hour ObjectCreationList.cpp reallyCreate is the semantic guide (debris loop, container, spread formation, fade in and out). BFME 2 additions read from retail and WorldBuilder: hidden vector result, live-player gate, team owner by name (+0x108), terrain-object placement for KindOf 0x64/0x5E/0x5F, build-limit checks (+0x91, max simultaneous at template +0x5E0), clear-for-construction (+0x111), waypoint start (+0x10C), the player +0x3BC flag cleared around newObject and 0x0028CBFD, experience levels (+0xB0), pathfind map registration for KindOf 7, and horde member fade-in for KindOf 0x6D.
- Offsets are retail facts; member names in the bank are descriptive, not asserted EA names.

## Inputs

Flags: the PositionCreate unit's STLport line plus `/ICode/GameEngine/Include` for the shared `Common/BfmeAudioEventPrefix136.h` (the 0x88-byte event at `[ebp-0x174]` and `[ebp-0x1FC]`, constructor 0x002D97D6, destructor 0x002D9A43). Measured with `tools/align_diff.py <bank> <symbol> 0x001F1634 2618` after deleting the cached object.
