# 0x002423E3 load-screen teardown stage (1436 B, SEH)

## Result

Banked as `partial` under `?rva002423E3@GameLogic@@QAE_NXZ` in `reverse/attempts/0x002423e3.cpp` (claude-opus-5-5, 2026-10-20). The body compiles to all 1436 bytes and 391 instructions with zero structural regions. With relocations masked, 23 instructions still differ, and every one of them is a stack-frame offset: the candidate's frame is `sub esp, 0xC` where retail has `sub esp, 0x10`, so every local below `ebp-0x14` sits 4 bytes higher. Each call and global relocation resolves to retail's target under an existing ledger or pin name. The exceptions are the file-static `g_00DFE788` and the 0x002419AB constructor (see "Landing prerequisites").

| measurement (`tools/align_diff.py`, 1436) | earlier farm bank `?deleteLoadScreen@GameLogic@@QAEXXZ` | this bank |
|---|---|---|
| emitted size | 1247 B / 327 insns | 1436 B / 391 insns |
| structural regions | 36 | 0 |
| register differences | 26 | 7 (all frame offsets) |
| memory differences excluding reloc operands | 20 | 16 (all `[ebp-x]` frame offsets) |

## Identity and ABI (target evidence)

- Every exit sets `mov al, 1` before `ret`, so the function returns `bool`. The pinned void name `?deleteLoadScreen@GameLogic@@QAEXXZ` cannot emit that byte, so the bank keeps an address-derived name.
- The Zero Hour `deleteLoadScreen` shape (`if (m_loadScreen) { delete m_loadScreen; m_loadScreen = NULL; }` on `+0x120`) is the separate row 0x0023C7D2, which this body calls twice. The Zero Hour `updateLoadProgress` shape is 0x0023C7BB. BFME 1's twin 0x0038D100 (its bank `targets/game/reverse/attempts/0x0038d100.cpp`) reached the same conclusion there.
- The only caller is GameEngine's client-subsystem update 0x00225C12, which passes `TheGameLogic` in `ecx` and ignores `al`. Its source `Code/GameEngine/Source/Common/GameEngineClientSubsystems.cpp` declares `void deleteLoadScreen(void)`. The call bytes are the same either way, but linking needs that declaration renamed to the landed name.
- The home unit is `Code/GameEngine/Source/GameLogic/System/GameLogicInit.cpp`. The float at 0x00DFE788 is `static float g_00DFE788` there (0x0024004D writes 98.0 to it), so the body cannot live in another unit.

## What the source has to be (each point measured)

- The callback holder is built by implicit conversion from the 8-byte `Rva0023E323` value (`AsciiString` group name plus frame `m_90`): `Rva003FE7E6(Rva0023E323(fadeGroup, m_90), &g_00E02EC4)`. The converting constructor is out of line at 0x002419AB. Writing `Rva00211E75Callback(...)` explicitly makes cl build a temporary and copy it (+12 B per site). An inline derived constructor puts the wrong pointer in `ebx`, and passing two separate parameters `(AsciiString, int)` pushes them separately.
- `rva001DCD1C` has to be visible as an inline body that cl still calls out of line. Retail keeps `TheAudio` in `esi` across that call, and cl does so only when it can see the callee does not write memory. An explicit local reproduces the same bytes, but it is not the natural source.
- The two `OpaqueRefElement4` temporaries passed to `rva0023DCCE` keep EH states 3 and 4 (unwind 0x0010F149), but retail runs no release for them on the normal path. cl drops those releases only when the bodies of `rva0023DCCE`, `OpaqueRefElement4::operator=` (0x00239099) and `Rva000A8C9B::clear` (0x000A8C9B) are all visible in the unit (n=1, but decisive: +28 B either way). Retail places 0x0023DCCE and 0x0023DC8E inside GameLogic's address range, which is consistent with that.

## Remaining mismatch: one 4-byte frame slot

Retail's slots are as follows:

- `-0xD`: `restoreMouse`.
- `-0x14`: only the case 2/3 `FadeWholeScreen` string (EH state 2).
- `-0x18`: the setGroup esp-save in the fade-out block, the case 0/6 string (state 1) and the second temporary.
- `-0x1C`: the lock guard, every esp-save and the first temporary.

cl gives both case strings the same slot, so it needs one slot fewer. Tried without effect:

- Case order (four permutations).
- Braces around the whole case versus around the inner block.
- Copy-initialising the string.
- A forced-inline `queueFade` helper.
- `int mode` at else scope.
- `restoreMouse` declared at the top.
- `/EHsc`, `/GX` and `/G6`.
- Default-argument, converting-constructor, template and named-const forms of the temporaries.
- `/O2`, which is far worse, and `/Ob2`.

Temporaries in place of the named strings are worse (7 to 18 regions). The case 2/3 string's EH predecessor state is -1, so its scope is not nested inside the case 0/6 string's scope. Open leads: the exact block structure of the case 2/3 tail, and whether retail's frame allocator counts something in the switch scope that leaves no code.

## Landing prerequisites (for whoever closes the frame slot)

1. Put the body in `GameLogicInit.cpp` with that file's views. It needs Display slots `+0x10C`, `+0x110` and `+0x114` with fields `+0x115` and `+0x13C`, GameEngine `+0x5C`, NetworkInterface `+0xD0`, AudioManager `+0x44` and `+0x50`, and GlobalData `+0x9AD` and `+0x11C8`.
2. The `rva0023DCCE`, `operator=` and `clear` bodies must be visible in that unit. They are rowed today in `Code/GameEngine/Source/Common/Rva0023DCCESet.cpp` and elsewhere, so either rehome those rows into GameLogicInit.cpp or make them shared inline definitions. Check the link census for duplicate COMDATs.
3. 0x002419AB is rowed as `?rva002419AB@Rva002419ABOwner@@QAEPAXVAsciiString@@H@Z`, a fake constructor that returns `this`. The call needs `??0Rva00211E75Callback@@QAE@VRva0023E323@@@Z` (or a rename of that row) through `tools/pin_admission.py`.
4. Rename the pin `?deleteLoadScreen@GameLogic@@QAEXXZ,0x002423E3` and the caller's declaration to the bool address-derived name when the body lands.

## Round 2 (2026-10-20, claude-opus-5-5): frame closed, two EH state immediates left

Bank `reverse/attempts/0x002423e3.cpp` is now 1436 B with 2 differing instructions.
The frame slot is closed: the case 0/6 arm sits last in the switch and its `FadeWholeScreen` string is declared **unbraced at switch scope** (only the textually last case may do this; elsewhere it is C2360).
cl never shares an ancestor-scope local with a child block's local, so the case 2/3 string (braced) moves to -0x14, the case 0/6 string to -0x18 and the lock to -0x1C, all as in retail.

What is left: EH state numbers follow source declaration order.
- `24271a` (case 2/3): ours stores 1, retail 2.
- `2428ea` (case 0/6): ours stores 2, retail 1.

Retail therefore declared the case 0/6 string first in the source but in a scope that does not share with case 2/3.

Ruled out this round (diff count in brackets):
- Case 2/3's block through a forced-inline member `queueFade()` [2]. Moving case 0/6's block, or both, there instead [23].
- Case 2/3 last with its string at switch scope and case 0/6 braced first [13]. Its dtor slides to the end of the switch and the string slots swap.
- Case 0/6 first as a temporary `Rva0023E323(AsciiString("..."), m_90)` with a forced-inline Rva0023E323 ctor [2]. States and frame are right, but ours pushes `&g_00E02EC4` before constructing the string, while retail constructs it first.
- Case 2/3 as a temporary on the v11 order [4].
- `const AsciiString &r = AsciiString(...)` [36] and copy-init [23], both of which share the slot again.
- Case 2/3's tail moved behind a `goto` label after the switch [23], which shares as a sibling.

Open lead: something that gives a named string, declared textually before case 2/3's string, its own slot. Two untested candidates are a by-value helper taking the string, and a second switch.

Identity fact from the WB twin 0xCFF490: Rva003FE7E6 = `GameEngineEventSequencer::AddControl`.
