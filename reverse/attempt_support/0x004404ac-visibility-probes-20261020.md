# RVA 0x004404AC: callee visibility and allocation probes

## Result

Blocked. The bank `reverse/attempts/0x004404ac.cpp` is unchanged and remains the best body. Measured with `tools/align_diff.py` against the home `Code/GameEngine/Source/GameClient/GUI/MpGameSetupSlots.cpp` (bank appended, region flags `/O1 /G7 /arch:SSE`), it emits 526 of 526 bytes with 0 structural regions, 7 memory and 24 register operand differences, all of them the `this`/`slot` exchange (ours `this`=EDI and `slot`=ESI, retail `this`=ESI and `slot`=EDI). The same holds with the home's own define set (without `/DBFME_ASCII_DTOR_DECL`). No candidate in this run is closer. Model: claude-opus-5-5.

## Hypothesis tested first: callee visibility

The fleet lever (a local whose address reaches a callee is unaliased only when the callee's body is visible) was tested on every callee that could plausibly have been visible in retail's AptMpGameSetup unit. Each trial appended the bank to the home and added only the named bodies.

| Trial | What was visible | Outcome |
| --- | --- | --- |
| getter | `Rva0043DA65::rva0043DA65` (0x0043DA65, inside retail's unit range) as `__declspec(noinline) inline` | identical bytes, same swap |
| copy constructor | `MpGameSetupComboRef(const MpGameSetupComboRef &)` (pin 0x0027EA56) as noinline inline | identical bytes, same swap |
| constructor and destructor | both, the destructor empty as retail's 0x000B3FD0 | 488 bytes: cl drops the destructor call and the whole EH frame, so retail's TU did not see an empty destructor body (refuted) |
| members hidden | home cut to its declarations, so `HandleHeroSelection` and `UpdateHeroDisplay` are declaration-only | identical bytes, same swap |

`rva00323736` is a matched 308-byte body in `GadgetImageComboBox.cpp` and receives the combo's address, so the combo escapes in retail as well; its visibility cannot change any combo load here. The visibility lever does not apply to this body.

## Spellings tested and ruled out (all identical bytes and the same swap unless noted)

- Clamp into a separate index: ternary `slot == -1 || slot >= 8 ? game->v13() : slot`, the inverted ternary, and an if/else copy. cl merges the variables before colouring.
- Nesting: everything under `if (game)`, the valid-slot check as `if (slot != -1 && slot < 8) { ... }`, and both together.
- An early `if (slot != game->v13()) return;` instead of the local-slot block (same CFG, same result), and `game->v13() == slot` operand order.
- Team block: repeated `m_team[slot]` instead of the pointer local, and `bool teamEnable = enable && !observer && !locked; if (!teamEnable) HideList(...)`, in both combinations.
- Do-while forms of the AI loop (with and without `++i` in the condition).
- Changing code, rejected: swapped hero-rule arms (3 structural regions), a materialized `bool isLocal` or `bool ruled` (+5 bytes each), ZH's `i < 8 && !found` loop condition and `found = !observer` (+8 to +10 bytes, still swapped).

## Diagnostic findings (scratch only, never landable)

1. A single extra `this` reference flips the allocation to retail's in any block that does not already reference `this`: at the top, in the combo, handicap and player-template blocks, the team body, both hero rule arms, the hero else-if, the local-slot block entry, the has-map block, the host check and the AI loop. It does not flip in a block that already references `this` (the hero rule compare block, the preview call block), nor inside `if (!observer)`. Load uses (`m_2d0`) and pointer stores behave the same. Equivalent extra `slot` references never flip it.
2. Removing single `slot` references (the `slot >= 8` half of the second check, or the `HandleHeroSelection` argument) does not flip it.
3. Ending `this`'s live range before the found computation (preview receiver taken from a global) flips the main allocation to retail's. So the cost that loses `this` the ESI register is its live range through the local-slot found computation, where it is live across about eight conditionals but referenced only once, at the preview call.

The gap is therefore smaller than one reference in a block nested three deep, and it comes from `this` spanning the found computation. A fix has to give `this` an additional referencing block or shorten what it spans, with identical emitted code. No natural spelling tried here does either.

## Closest structural variant (not banked)

A preview pointer local, `AptMapPreview *preview = (AptMapPreview *)&m_60;` declared at the top of the local-slot block (or just before `if (slot == game->v13())`) and used as `preview->rva0057C597(found);`, gives retail's allocation everywhere: align_diff reports 0 memory and 0 register differences. It costs 2 structural regions (528 bytes): cl ends `this` there and turns ESI into the preview pointer with `add esi, 0x60`, then passes it as `mov ecx, esi` where retail has `lea ecx, [esi+0x60]`. By the closer rule (structural regions first) this is not closer than the bank, so it is recorded here only. It confirms finding 3: retail's `this` still reaches the preview call (its `lea` proves it), so retail's source lowers that live range's cost by some other means. Declaring the pointer before the observer computation is worse (3 structural regions, 8 register differences).

## Next step, if any

Only an IL-level difference that the final code does not show can close it, for example a construct whose extra `this` reference is removed after allocation. Statement-level spellings of the found computation that keep the code identical compile to the same IL. Unless new evidence about retail's source shape appears (a BFME 2 era source or symbol with this body), treat the body as blocked on cl 7.1's allocator.

Scratch for this run (untracked): `build/w3_4404ac/` in the seat checkout, with the trial generator scripts (`mk.py`, `variant*.py`, `grid*.py`, `probe*.py`), every trial source `t_*.cpp` and its `*.align.log`.
