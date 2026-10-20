# EmotionTrackerUpdate::update 0x004B1633: w2 handoff (2026-10-20)

## Result

Blocked; the bank `reverse/attempts/0x004b1633.cpp` is unchanged apart from one pointer comment to this file. It still emits 2194 B against retail 2200 B, with 2 structural regions, 25 memory and 3 register differences (`align-bank.txt`). The only non-relocation difference remains the case-2 layer compare at +0x572.

New finding: the case-2 call order is not decided by the spelling of the compare. It flips to retail's exact shape when the function carries more tracked locals ahead of the loop. A diagnostic copy of the bank that adds an inert `__forceinline` function with N chained `int` locals in the range-test condition (`forcedFrames==0` becomes `manyLocalsN(forcedFrames)==0`) compiles to a body with 0 structural regions, 0 register differences and 24 memory differences (all absolute relocations) for N = 122 to 126. That diagnostic is `tracked-locals-diagnostic-n124.cpp.txt`. It cannot land, because the chain is dummy code whose only purpose is to steer the compiler.

## Measurements (align_diff, each value n=1, flags `/O1 /arch:SSE /G7 /MD /EHsc`, STLport)

| Variant | Bytes | Regions | Memory | Register |
| --- | ---: | ---: | ---: | ---: |
| bank | 2194 | 2 | 25 | 3 |
| chain N = 40, 60, 80, 100, 120, 121 at the range test | 2194 | 2 | 25 | 3 |
| chain N = 122, 123, 124, 125, 126 at the range test | 2200 | 0 | 24 (relocations) | 0 |
| chain N = 127, 128 to 148 in steps of 4, 150 at the range test | 2206 | 2 | 47 | 3 |
| chain N = 124 at the function entry (`forcedFrames>0` test) | 2194 | 2 | 25 | 3 |
| chain N = 124 in the final 12-slot cleanup loop | 2194 | 2 | 25 | 3 |

At N = 127 and above, case 1 (+0x459) takes the retail case-2 shape as well, and `obj` moves from `[ebp-0x14]` to `[ebp-0x18]`. So the two compares sit five tracked symbols apart: retail compiled case 1 below the threshold and case 2 above it. Raw logs: `align-n121.txt`, `align-n122.txt`, `align-n126.txt`, `align-n127.txt`.

## Interpretation (structural inference, not established)

Below the threshold MSVC 7.1 forward-substitutes the inlined `getObject()` temp into its call, so the left operand (`IND(this-8)`) is heavier and is called first, and its result borrows ebx from `data`. Above it the temp stays a separate load ahead of the compare. The two receivers then tie, the right operand (`other`) is called first, the loaded owner pointer is the expression temp that borrows ebx, and `other`'s result is spilled to the dead cursor slot `[ebp-0x18]` and reloaded into ecx. That is exactly retail's case 2. The count is position-sensitive (the same chain at the entry or after case 2 does nothing), so it is not a plain total of locals.

The consequence for the reconstruction: retail's original `update()` created more tracked symbols ahead of the case-1 compare than the flat bank does. The bank reads most fields directly through private views, while the original went through engine headers. Which constructs supply the missing count is open. Measured so far: a BitFlags-style inline status test (`m_status.test(6)` on a `StatusBits` member at 0x94) costs nothing; with it the window still starts at N = 122 (s121 bank shape, s122/s124/s126 exact; `align-s121.txt`, `align-s122.txt`).

## Also ruled out in this run (each n=1, all identical to the bank unless noted)

- `obj` or `m_object` on the left of the case-2 compare: other is called first, but the owner is loaded after the call and other's result takes ebx.
- forceinline `Object::sameLayerAs(int)` called as `getObject()->sameLayerAs(other->rva0028B511())`: the order is right, but both inline locals live in memory (`[ebp-0x18]`, `[ebp-0x20]`) and the frame grows. The by-reference form `sameLayerAs(const int &)` loads the owner after the call. The same helper in a small test unit keeps both values in registers, so the memory homes are a property of the large function.
- a visible `__declspec(noinline) inline` copy of `Object::rva0028B511` (0x0028B511): no change.
- `other` declared before the loop or `Object *const`; `dist` declared outside the case-1 block; `closest` declared after `closestDist`; `data` read through `getModuleData()` (with or without const); `rva0028B511` non-const or returning an enum; inline identity wrappers around `other`.
- Removing the debug draw, the NeutralGollum lookup or the cleanup loop does not move the forceinline-helper locals into registers. Removing the TauntPointFilter block as well moves the owner pointer into ebx, while other's result stays in memory (diagnostic only).

## Next step

Rebuild the parts of `update()` ahead of the loop with the real engine accessor chains (module-data accessor, Thing/Object/Player getters, STLport containers, filter classes) instead of flat views. Use the chain as a meter: after each faithful change, bisect the N that the chain still needs, and stop when N = 0 lands inside the five-wide window. Never land the chain itself.

Landing also still needs a pin for the unrowed activation call `?rva004DCC84@Rva004DCC84@@QAEXPAVObject@@H@Z` at 0x004DCC84. Its home is `Code/GameEngine/Source/GameLogic/Object/Update/EmotionTrackerUpdate.cpp`, which already holds the selector 0x004B13D8.
