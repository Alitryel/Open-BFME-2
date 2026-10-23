# OpenContain exit: scale-block operand rank (w3, 2026-10-20)

Target `?exitObjectViaDoor@OpenContain@@UAEXPAVObject@@W4ExitDoorType@@@Z`, RVA 0x0046525F, 1152 bytes. The 0.99 bank `reverse/attempts/0x0046525f.cpp` is unchanged and still the best body: align_diff gives 1154 B, 3 structural regions, 10 memory and 3 register operand lines. The only defect left is the 50.0 scale block (retail +0x357..+0x3a9). Retail preloads `delta.z` before the `target = startPosition` block copy, then multiplies x and y as `movaps xmmN,xmm0; mulss xmmN,[delta.x/y]` and z as `mulss xmm1,xmm0`. The bank preloads all three components and multiplies registers, which costs one byte each for x and y.

## Result

Blocked. 86 trials, none closer than the bank. Two findings are new and should steer the next attempt.

## Finding 1: the 50.0 is a writable global, but that is inert

Retail VA 0xDC97E4 holds 50.0f in `.data` (not `.rdata`), between two OpenContain string-pointer tables. Only two instructions in all of `.text` reference it, both in this function (the `fld` compare at +0x343 and the `movss` at +0x357). WorldBuilder agrees: its copy at VA 0x21D7B8C is also in `.data` with exactly two references, both in the twin 0x01196CE0, where the scale is a call to MathCoord3D's `operator*=(Real)` (WB 0x41F8B0) with the global pushed by value. So the source spells a non-const file-scope `Real` (name unknown; there is no data-ledger row). Replacing the literal with a `static`, a plain global or an `extern` float changes nothing in any statement order or helper form (static/global/extern x zxy/xyz, inline `operator*=`/`scale`/`add` in WB order, forceinline free helpers as in ReplaceSelfUpgrade, `const float &`/pointer to the global, nested, const, by-reference and out-of-class operator definitions). All of these stay at 1154 B with 3 regions.

## Finding 2: the split is an operand-rank effect (diagnostic, not landable)

matching.md's rank rule 5 ("among locals, the variable first assigned later is loaded first") reproduces the split exactly when the multiplier is a local variable whose first assignment sits between the `delta.y` and the `delta.z` statements. These are diagnostic sources only, because the extra variable is a dummy store:

- `float s` first assigned before `delta.x`: every delta component is loaded first (the bank's form).
- First assigned between `delta.x` and `delta.y`: x folds, y and z load.
- First assigned between `delta.y` and `delta.z`: x and y fold (`movss/movaps s; mulss [x]`), z loads and multiplies by s. This is retail's form. With zxy order, z is also hoisted above the block copy (t_ra_mid_noreassign).
- First assigned after `delta.z`: all three fold. A computed multiplier (`exitScale+exitZero`) does the same; this is the earlier 1148 B "local float s" result.

A CSE'd literal or global ranks below every delta component, so the bank cannot fold. Reassigning the variable after `normalize` splits the web and reverts to the bank form. Inline-parameter symbols are not shared between expansions either. So in retail the multiplier behaves like a local that ranks between `delta.y` and `delta.z`, and no natural source variable doing that was found.

## Ruled out in this run (all measured with align_diff)

- Visibility of `length`/`normalize`: no effect on the block.
- Which delta components feed atan2, and atan2 wrappers taking values, references or a whole `Coord3D`: no effect.
- Statement position of the scale relative to the target copy (z before, x/y after, and so on): no effect.
- In-place versus temporary products, including z as a temporary with x and y in place: worse.
- Keeping the scaled delta live afterwards (diagnostic): no flip.
- Sharing `exitAngle` or `startPosition` with the door branch: no flip.
- Delta computed as a copy plus component subtracts: worse. z assigned first: no flip.
- /O2, /O2 /Os, /G6, /arch:SSE2, /Ob2: no flip; /Op is worse.

## Leads for the next agent

Two matched retail bodies show exactly this split with real C++: GiantBirdAIUpdate::rva0036AE79 (site 0x36AFFC, `scaleCoord(dir, m_538 / 2.0f)` on an out-param `dir`, in `Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/GiantBirdAIUpdate.cpp`) and ReplaceSelfUpgrade::upgradeImplementation (site 0x4B7690, `scaleCoord(step, -tmpl->getC8())` after the perp swap, in `Code/GameEngine/Source/GameLogic/Object/Upgrade/ReplaceSelfUpgradeImplementation.cpp`). In both, the multiplier is a computed value, yet z still ranks above it while x and y rank below. Working out why z ranks higher there (and whether a computed rather than CSE'd multiplier plus that property applies here) is the remaining concrete hypothesis. Raw trial sources and align_diff outputs are in `build/w3_46525f/` (t_*.cpp, t_*.align.txt) in seat w3.
