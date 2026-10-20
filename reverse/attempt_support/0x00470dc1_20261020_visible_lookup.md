# 0x00470DC1: visible GameLogic::findObjectByID

Result: a closer fragment bank for `?rva00470DC1@HordeContain@@UAEXXZ` (retail RVA 0x00470DC1, 1699 bytes, home `Code/GameEngine/Source/GameLogic/Object/Contain/HordeContainIface11CSlots.cpp`). It is not exact. Nothing under `Code/` was changed; the bank's view patch carries every edit.

## Measurements (align_diff, BFME_OBJSTORE=off, fresh object per trial)

| Source | Emitted | Structural regions | Memory | Register | Home rows exact |
| --- | ---: | ---: | ---: | ---: | ---: |
| previous bank (score 0.9) | 1688 B | 11 | 50 | 22 | 148/148 |
| new bank | 1683 B | 8 | 30 | 17 | 148/148 |

The new bank's view patch was applied to a fresh copy of the home and recompiled; it reproduced the selected trial's body byte for byte.

## What closed the attack-pair and frame differences

Hypothesis: retail caches `TheGameLogic` in ESI across the first `findObjectByID` call (+0x19A) without a local, because the retail unit could see the callee's body. Evidence: WorldBuilder's debug body of the same method (WB 0x010B73E0, via `tools/wb_show.py 0x00470DC1`) loads the global twice and stores no local, so the original source has no cached pointer; cl 7.1 can only reuse a global across a call it can analyse. Zero Hour's GameLogic.h defines `findObjectByID` inline, and `SpawnBehavior_update.cpp` already models it as the header inline over the STLport `hash_map<ObjectID, Object *, hash<int>, equal_to<ObjectID>>` at +0xB4. Refutation criterion: the TheGameLogic reload, the GameLogic spill and the shifted frame slots survive. Observed: they are gone. The frame now equals retail's, including the shared [ebp-0x18] slot for the ID temporary, attacker and length, and the attacker's memory home with its later ESI reload. A throwaway-use probe (one extra straight-line use of the old cached local) had shown the same allocation flip, which is how the gap was located.

The emitted copies are byte-equal to retail: `GameLogic::findObjectByID` to 0x00049DC5 (37 bytes) and the hashtable `_M_find` to 0x002888D4 (47 bytes). Both names are select-any everywhere else (`GameLogicFindObjectByID.cpp` defines the lookup `inline`; `_M_find` is a template).

Making the lookup visible changed one existing home row, 0x0046DEA1 (the module register after the second loop's lookup: ECX in retail, EAX in ours). Testing the member pointer before naming it (`if (member->m_254) { Rva0046B850Module *module = member->m_254; ...`) restores it under visibility, so all 148 home rows stay exact. Semantics are unchanged.

The side offset is scaled through a member-wise copy (`HordeOffset3D scaled(side)`), which also fixes the order of the final position stores (11 to 10 regions before the lookup change).

## Remaining mismatch (all SSE scheduling)

1. Third-branch slot scale (retail +0x364..+0x3BC): retail converts the slot into XMM3 and preloads pos.y and pos.z before the call-argument pushes; ours folds them.
2. Perpendicular dot product and side scale (+0x472..+0x4DD): retail loads `side` and keeps side.y and side.z in XMM1 and XMM2 for the later scale; ours loads `toClosest` and folds `side`.
3. Held-slot 5.0 scale (+0x5E2..+0x620): retail preloads pos.x, pos.y and pos.z and multiplies y and z lazily; ours scales each component in turn.

## Ruled out in this run (identical output, or a trade that is not closer)

- Visible `Coord3D::normalize`, `length`, `GetLength2D` and `Normalize2D` copies, also with the side-scale variants: identical.
- All 12 term and operand orders of the dot product, and a dot helper taking pointers or references: identical.
- Building `toClosest` before `delta` and `side`: worse (17 regions). Building it with `set` and `sub`: identical.
- Null-check structure (`if (target && attacker)`, split ifs), wrapping the pair code under the bit test, declaring `attacker` and `target` first: identical.
- The `continue` form of the +0x170 membership test: worse (16/65/22).
- Named `attackerPos` locals: 12/44/20 or 18/105/38, a trade.
- Held-arm and slot-scale spellings: a member-wise copy before scaling the held position reproduces the three preloads but gives 11/24/14 (more regions); per-component `*=`, `scaleInlined` and a float local are identical.

## Landing notes

The view patch adds `#include <hash_map>`, the `ObjectPtrHash` typedef and the +0xB4 member to the home's existing private GameLogic view (an edit to an existing private copy, which the class gate does not refuse). Run `find_declared_unmatched` on the home once the body lands, because the home then emits the select-any `findObjectByID`. The link census was not run. Scratch trials and logs are in `build/w6_470dc1/` of the seat that produced this bank. Model: claude-opus-5-5.
