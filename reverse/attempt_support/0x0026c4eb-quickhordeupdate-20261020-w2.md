# AIUpdateInterface::quickHordeUpdate 0x0026C4EB (2598 B), seat w2, 2026-10-20

## Result

Partial. The new bank `reverse/attempts/0x0026c4eb.cpp` is a complete, semantically faithful reconstruction under the pinned symbol `?quickHordeUpdate@AIUpdateInterface@@QAE?AW4UpdateSleepTime@@XZ` (the farm bank used `QAEXXZ`, a void return, which was wrong: retail returns 1 or `BfmeLogicFramesPerSecond` in EAX and the rowed caller `update` 0x0026E267 consumes it). It emits 2597 B and 709 instructions against retail's 2598 B and 709 instructions, with the same frame (`sub esp,0x6c`), the same stack slots and every call resolving to a rowed or pinned callee.

Measured with `tools/align_diff.py <file> ?quickHordeUpdate@AIUpdateInterface@@QAE?AW4UpdateSleepTime@@XZ 0x0026C4EB 2598`:

- new bank: 10 structural regions, 37 memory and 2 register operand differences (21 reloc, 98 branch lines are noise); 2597 B.
- farm bank before (compiled with its include fixed, under `?quickHordeUpdate@AIUpdateInterface@@QAEXXZ`): 24 regions, 19 memory, 10 register, but it emits only 459 B of 2598 B, so its region count is not comparable; it also dropped most of the body (no dead-object fall, no angle case, no horde-path branch, no matrix build, void return).

## Remaining mismatch (all scheduling or register choice, no semantic difference)

1. Retail +0x371: the rider check's `setModelConditionState(156)` is `test byte ptr [ebx+0x11f],0x10` / `or byte ptr [ebx+0x11f],0x10` in retail; ours CSEs the constant into EAX (`mov eax,0x10000000; test/or dword ptr [ebx+0x11c],eax`). The same inline gives the EAX form at every other set site in retail (bit 61 here, bit 156 in doLocomotor 0x0026A3A0 +0x7E5), so this site probably uses a different spelling or inline in the original.
2. Retail +0x43D: the container for the `container->getAI()->slot111() && isMoving()` test is loaded into EDI and advanced with `add edi,0x258`; ours loads it into EAX and uses `lea edi,[eax+0x258]`. The earlier container test at +0x333 matches.
3. Retail +0x48C..+0x4CC: in the step toward the goal, retail computes x, then loads and multiplies y and z, stores x after the y add, and adds z as `movss xmm0,[pos.z]; addss xmm0,xmm2`; ours stores each component in order and folds `pos.z`. Tried and worse or equal: `coordScale(&delta)` plus `coordAdd` (2612 B, stores the scaled delta), a scaled `step` temporary (11 regions), a copied `step` then scale (11 regions).
4. Retail +0x815 and +0x83F: in row 0 of the z rotation retail loads `c` and folds `Row[0][0]` (`fld [ebp-0xc]; fmul [ebp-0x6c]`); ours loads the row element first. Rows 1 and 2 match. Tried: `rotateZ(c,s)` with caller locals (this region set), `rotateZ(s,c)` with direct sin/cos arguments (14 regions), Row01-first store order (15 regions), `rotateZ(theta)` computing cos/sin inside (not inlined unless `__forceinline`; forceinline is the banked form, 10 regions and 2 fewer memory lines).
5. Retail +0x876..+0x881: the row 2 tail interleaves `fld [ebp-0x48]` before the `push ebx` of the getLayerForDestination call; likely a consequence of item 4.

## Levers that closed the large gaps (keep them)

- Fieldwise Coord3D copies for every position copy except `pos = m_locomotorGoalData` (retail uses `movsd` only there).
- A local for `m_curLocomotor` in the max-speed selection, a `const Coord3D *goal` for the delta copy, locals for the orientation and goal angle before `normalizeAngle`.
- `getValidSurfaces()` as an inline accessor for `+0x1DC` (retail materialises it in a register before pushing; a plain member push does not).
- The out-parameter of `0x00265AAB` in its own block, and the moved-distance computation in its own block: both are needed for retail's stack-slot sharing (`[ebp-0x14]` and `[ebp-0x2c]`), which took the frame from 0x80 to retail's 0x6c.
- An unrolled, inlined z rotation over an identity `Matrix3D(true)`.

## Identity and evidence

- Target facts: boundary 0x0026C4EB..0x0026CF11 (`leave; ret`, next row 0x0026CF11 rowed); the pin in `reverse/symbols.csv` names the UpdateSleepTime return; the only caller is the rowed `AIUpdateInterface::update` 0x0026E267; vslot 0x254 is doLocomotor (slot 149, as in `Rva0026A05DUpdate.cpp`); +0x3E0 brackets the state machine update as in 0x0026A05D; Object +0x438 bit 0 is the effectively-dead bit; +0x274 is the container (WorldBuilder asserts `obj->getContainedBy()` and `->getAI()` read it and +0x258).
- Donor facts: none; there is no BFME 1 or Zero Hour body. The WorldBuilder twin 0x00E3B6D0 is a different revision (it builds AICommandParms and calls aiDoCommand where retail calls aiIdle, and uses `/ 20.0f` where retail multiplies by 0.05f) and was used only for statement shapes and scopes (its EH states show the delta, info, offset and moved scopes).
- Structural inferences: the names `getValidSurfaces`, `m_C4` (likely gravity), `slot111`, `slot113`, `Rva0026C4EBContain::slot31` and `Rva0026C4EBRider::slot105` are address-derived or descriptive and unproven.

## Landing notes

`repair_queue.py dest` offers only a neighbour heuristic (AICommandInterfaceAttackCommands.cpp). The closest sibling is `Code/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterface_doLocomotor.cpp` (same views and flags); a new unit `Code/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterface_quickHordeUpdate.cpp` with the bank's `// cl:` line avoids touching a matched unit. No new pins are needed. Landing it unblocks the link of `AIUpdateInterfaceUpdate.cpp` (850 matched bytes). Trial sources and measurements from this seat are in the seat's `build/qhu/` (t1..t18, final).
