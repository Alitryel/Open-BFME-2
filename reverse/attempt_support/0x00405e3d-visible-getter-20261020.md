# 0x00405E3D: visible science getter closes the hero loop

Result: partial, banked as closer. Symbol `?createContent@OldSchoolHelpBoxContentSource@@UAE?AUTreeHintRef00217D4C@@XZ`, retail RVA 0x00405E3D, 3287 bytes, checkout revision 226419d259fe. Model: claude-opus-5-5.

## Hypothesis and test

Hypothesis, written before the first experiment: the hero-loop residue (retail `mov ebx,eax` after the empty guard, where the bank reloads begin behind a `_ReadWriteBarrier`) comes from cl treating the by-value science vector as aliased, because its address goes to the opaque getter 0x0029FCB4. The sibling unit `Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarRappellerCount.cpp` shows that the same getter's visible body together with `/D_STLP_NO_EXCEPTIONS` changes how cl treats that vector, and the 0x00307EDC handoff shows the general rule (a local's fields are forwarded only when every callee receiving its address is visible and does not leak it). Refutation would have been an unchanged hero loop with the visible getter and the flag, with and without the barrier.

Outcome: confirmed. Neither lever alone changes anything (visible getter only, or flag only: 3292 B, identical to the bank). With both, the WorldBuilder twin's own spelling compiles to retail's hero loop exactly: a reference bound to the by-value result (WB stores `&temp` in a local), an `!empty()` guard, a plain `const_iterator` for loop, and no barrier. The same spelling without both levers gives 3282 B with 4 structural regions.

## Measurements (align_diff, BFME_OBJSTORE=off)

| Body | Bytes | Structural | Memory | Register |
|---|---:|---:|---:|---:|
| previous bank (reproduced) | 3292 | 2 | 35 | 4 |
| new bank (banked) | 3291 | 2 | 35 | 3 |
| lead (attempt_support .cpp.txt) | 3290 | 1 | 37 | 0 |

The new bank keeps the previous sciences spelling and has no barrier at all. Its residue is the known sciences one: at retail +0xBA it copies the button to ECX and keeps the count in EAX (retail keeps the button in EAX), and the size-1 arm reloads `m_commandButton` at +0x154.

The lead, `reverse/attempt_support/0x00405e3d-visible-getter-20261020-lead.cpp.txt`, replaces the sciences block with Zero Hour's plain structure (for loop with `size()` everywhere, `else if (size() == 1)`, WorldBuilder's declaration order thing, upgrade, science) plus one `_ReadWriteBarrier()` after the science initialisation. Its only real difference from retail is one extra `mov eax,[esi+0xc]` after the upgrade store (upgrade then lands in EAX instead of ECX). The two extra memory lines are alignment artefacts of that one inserted instruction. Because the memory count rises by two, the lead is not banked under the closer rule.

## What the barrier does in the lead

Barrier position probes on the plain spelling: only a barrier between the upgrade load and the first `size()` test works. Placed anywhere else (function end, castle branch, start of the `if (m_commandButton)` block, inside the loop, inside either arm, after the loop) the result stays at 35 to 39 structural regions, because cl materialises `&m_sciences` (`add eax,0xa4`) at every size site and hoists `mov edi,0xa4` out of the loop, which also takes EDI away from the zero constant. `_WriteBarrier` instead gives 16 regions.

Decisive probe: with no barrier, moving the upgrade load below the sciences block makes the whole sciences region retail-shaped (folded first test, hoisted end load in ECX, both arms reuse EAX), although the changed upgrade lifetime then reshuffles the function's callee-saved registers (18 regions). So the sole trigger is that the upgrade load shares the `m_commandButton` value with the sciences block. Retail shares that value and still folds, so retail's IL around the upgrade load differs in some way not found yet.

## Ruled out in this run

The science initialisation before the call, between call and upgrade, and after the upgrade, signed and unsigned loop index, `else if` against `if` for the purchase arm, `size()` against `(unsigned)(end()-begin())` at each of the four size sites (for loop and guarded do/while, 48 + 32 variants, with and without the barrier), and inline accessors `getScienceVec()` and `getCommandType()` (identical IL).

## Landing prerequisites

- The visible getter is a `__declspec(noinline) inline` copy of the rowed `?rva0029FCB4@Rva0029FCB4@@QAE?AV?$vector@W4ScienceType@@V?$allocator@W4ScienceType@@@_STL@@@_STL@@XZ` (32 bytes, emitted byte-faithful, calling the rowed vector copy 0x0054878E). Its home `Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarRappellerCount.cpp` defines it as an ordinary function, so landing needs that definition made select-any as in commit 7ebbac515c, and the home rebuilt with `./build.sh`.
- The new unit needs `/D_STLP_NO_EXCEPTIONS`. The intended home is WorldBuilder's `GameClient/GUI/GUICallbacks/ControlBarPopupDescription.cpp`; `repair_queue.py dest` only offers a neighbour heuristic (`Disp8DwordClearers.cpp`).
- The local formerly named `scienceLocked` is now Zero Hour's `fireScienceButton`, and Zero Hour's EA comments for the sciences loop are carried into both bodies.

Scratch: `build/h5e3d/` in the seat (trial sources, `*.align.txt`, generators `gen1.py` to `gen4.py`, `gen_final.py`, `trial.py`).
