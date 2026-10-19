# examineNeighboringCells 0x2F83F5 (1803 B): 3-angle pass 2026-10-19

Result: blocked. The bank stays at nd 14 (size-exact, frame 0x90). Model claude-opus-5-5.

The residue is a three-object frame-slot cycle in [ebp-0x28..-0x15]:

| Object | Retail | Bank |
|---|---|---|
| flags | -0x28 | -0x1C, shared with end |
| strength-reduced bias (1-&flags) | -0x20 | -0x28 |
| end | -0x1C, shared with coords | -0x1C, shared with flags |
| coords | -0x1C, shared with end | -0x24 |

## Frame-packer model (VC7.1 /O1), measured over about 400 variants
- Slot sharing follows liveness from the first reference. Scope and declaration order don't matter: 59 placements of coords, flags and end were byte-identical.
- Weights count only references that survive copy propagation and CSE.
  - Pointer and reference aliases, dead inits and dead stores don't count, and neither do extra copy chains (42 variants inert).
  - Duplicated per-branch code that the compiler tail-merges later does count. The bank's per-branch struct copy of end weighs more than a scalar capture.
- Slots are ordered by summed weight, heaviest at the top. end joins the lighter 8-byte partner.
- Diagnostics that changed the code but flipped the pairing to retail's:
  - 8 extra flags reads;
  - removing the bias temp with the `(i&3)^1` index form;
  - an early store that forces flags to overlap end.

## Best structural candidate: msc_shared_coord.patch (nd 21; patch -l against reverse/attempts/0x002f83f5.cpp)
- One `ICoord2D end` declared at function top is reused as the loop cell.
- The endpoint is captured through scalars ex/ey.
- That gives retail's flags -0x28 and bias -0x20.
- Two problems remain:
  - The shared coordinate slot and {start, cellCount} are swapped (-0x18 vs retail -0x1C).
  - In block 1, goalCell is in edx instead of ecx, and x/y are in ecx/eax instead of edx/eax.
- With the bank's direct struct copy, the shared form is 1806 B because the x store doesn't tail-merge.

## WB/ZH facts (ZH AIPathfind.cpp:6121; WB D5BBE0)
- BFME2 drops ZH's adjacent[] and indexes the flags as `[(i-4)&3]` and `[(i-3)&3]`. This is byte-neutral.
- There is no aggregate flags init. ZH's `={false...}` gives 1833 B.
- The separate x/y locals are right. ZH's newCellCoord.x everywhere gives 1791 B.
- WB initializes end and newCellCoord from a global (a debug ICoord2D ctor). The equivalent static zero init is eliminated with no layout change.

## Next lever
- Add one or two surviving references to {start, cellCount} or i (or remove them from the shared coordinate) without changing code. Branch-duplicated code that tail-merges is the only such reference found.
- Then fix the endpoint register choice in the scalar-capture form.
