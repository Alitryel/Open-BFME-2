# 0x0024877A GameLogic::rva0024877A — rebased patch + slot-order diagnostics (2026-10-20)

Target facts: 1349 B body; retail 1-byte frame homes destroyed -0xd, hidden -0xe,
{list allocator temp, all} share -0xf, visibleOnly -0x10.

## Rebased patch
`rebased-onto-current.diff` is `diff -u` against current `GameLogicInit.cpp` (HEAD at the time:
see the commit carrying this file). It applies the `#if 0` patch from `reverse/attempts/0x0024877a.cpp`
after reconciling it with later edits to the file:
- the patch's private Matrix3D view was dropped; a `__forceinline operator=` (Row copies) was added to the
  existing MatrixRow Matrix3D, which was moved above `class Thing`
- Drawable gains `isVisible()` (`m_visible` at +0x43C)
- the duplicate OpaqueRefCounted was replaced by `#include "../../../Include/Common/BfmeAudioEventPrefix136.h"`
- the two Team views were merged (`m_id` at +0x34 with `m_active`/`m_created`)
Result: 1349 B, 7 regions, 10 differing instructions, all from the one slot swap (ours: {alloc, all} -0xe,
hidden -0xf).

## Slot-order trials (all inert: same 10 diffs)
- forceinline / plain-inline helper `refreshHidden(obj)` used as `if (visibleOnly && refreshHidden(obj)) continue;`
- triple `if (hidden) continue;`, an extra `&& !all`, extra `all = false` stores, extra `hidden = true` stores
- `destroyed` declared after `records` just before the loop (only scheduling moves)
- `bool hidden;` at function scope ahead of `destroyed`

Diagnostics that do move slots (they are not candidates):
- removing `all`: {alloc, visibleOnly} at -0xe, hidden -0xf
- an extra `hidden &&` reference: hidden goes into a register; {alloc, all} -0xd, destroyed -0xe, visibleOnly -0xf
So slot order is not declaration order. The packing looks weight/first-use driven, but the model is unknown.

## Landing wall (independent of the slot swap)
- `_List_base<Rva0024076D>` ctor: compiles **exact** at 0x0023E83A (41 B). A fold-proof pin is viable
  (0x23E83A is owned by `_List_base<BfmePod80>`).
- `clear()`: 49 B, exact at 0x00243119 except the unresolved `??1Rva0024076D@@QAE@XZ`. That dtor is declared
  but not defined in any unit. Retail's dtor is 0x00240831, ledger-named `??1WorkerAIUpdateModuleData@@UAE@XZ`
  (ModuleFactory.cpp, placed by masked search). Proving it needs a defined `Rva0024076D::~Rva0024076D`
  (e.g. in Rva0024076DCtor.cpp) that compiles to that body, followed by fold-proof pins for the dtor, clear,
  the _List_base dtor (0x002461DA) and the ctor.
