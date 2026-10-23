# OpenContain::exitObjectViaDoor 0x0046525F: landed through c2's symbol numbering (2026-10-20)

Landed byte-exact (1152 B) in `Code/GameEngine/Source/GameLogic/Object/Contain/OpenContainExitObjectInAHurry.cpp`. Its sibling exitObjectInAHurry 0x004656DF stays exact.

Before this, the only residue was the 50.0 scale block. Retail multiplies x and y from memory (`movaps xmm,s; mulss xmm,[delta.x/y]`) and preloads z. The bank preloaded all three.

## What decides the scale's operand order

The 13.10.3077 c2.dll was traced with the lab debugger (`build/compiler-causal-lab-20261015/trace_compiler.py`), using a hardware watchpoint on the multiply tuple's operand list.

- **Where the order is set.** `dop2_InitialOptsAndSetup` (c2 RVA 0x60539) sets it. Inside it, `FactCanonSort` (0x5CC68) sorts every commutative node's operands with `MscMergeSort` and `OptCmpHashVal` (0x6A394). The larger hash goes first.
- **How a leaf is hashed** (`OptHashNode`, case at 0x5DF16).
  - For a variable leaf, F is the symbol number at `[sym+0x1C]`. The hash is `0x10000 | (((F<<5)>>16) ^ ((F & 0x7FF) << 5))`, which is 32·F for F < 2048.
  - A constant (kind 7) gets no 0x10000 bias, so a literal multiplier always sorts last.
- **How symbols are numbered.** Number by number:
  - The first 32 symbols are numbered in first-assignment order: parameters, named locals, and the pieces c2 splits a struct into as its fields are touched. A Coord3D touched x, y, z takes six: parent, x, rest(+4), y, rest(+8), z.
  - The function's globals follow. Here `s_exitDist` / the 50.0 global is #38.
  - Every later local is numbered after the temporaries, from about #189 on.

## Applying the rule

Retail's split needs delta.x and delta.y inside the first 32 symbols and delta.z outside them.

In the bank, delta's parent was #32 (outside). The named copies `theAI`, `pf` and `goalView`, plus branch 1's `pathfinder`, held slots the WorldBuilder twin (wb 0x1196CE0) does not have.

| Spelling | Bytes | Slots |
|---|---|---|
| Twin's form: `TheAI->getPathfinder()`, `ai->goalView->goal` | Same as the named copies | None |
| Plain inlined `TheAI->pathfinder` | Changes allocation | — |
| Removing `pos` | Changes code (retail keeps it in esi) | — |

The fixes are byte-neutral except the scale block itself:
- `savedGoal.z` moves after delta.y. Its two pieces then land between delta.y and delta.z: delta is #28, x is #29, y is #31, z is #291. The traced keys show the global (#38) first for x and y and delta.z first for z.
- The twin's statement order (`target = startPosition` before the scale; scale x, y, z) gives retail's schedule for the third `movsd`.

The 50.0 global is retail .data 0x00DC97E4. It gets a data row in the same unit (`BfmeOpenContainExitDistance`).

## For the same family (0x5AA2D9, 0x17D770, GiantBird 0x36AFFC)

1. Count first-slab symbols before the scaled struct.
2. Look for named copies that the twin reaches through accessors.
3. Check which fields fall on either side of #31.

The scratch tools:
- `build/xs/trace/canon_trace.py` dumps the slab and sort keys.
- `xprobe.py` prints the scale multiplies' keys.
- `swap_watch.py` watches an operand list.
- `pass_tuples.py` dumps tuples at pass entries.

These are untracked. They were rebuilt from the lab's Tracer.
