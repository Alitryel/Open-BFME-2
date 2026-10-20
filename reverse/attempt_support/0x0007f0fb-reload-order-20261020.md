# 0x0007F0FB camera reflection setup: four spill reloads in the wrong order (2026-10-20)

Banked candidate: 1921/1921, bytediff 8, nd 2.
- Source: `reverse/attempts/0x0007f0fb.cpp`.
- Earlier bank: round 3 (16-float Matrix4 ctor, temporary clip plane).
- Effort: claude-opus-5-5 subagent plus main session.

## Residue
Two lines differ in the reload block +0x109..+0x129, after the call at +0x104:

| | Reload order |
|---|---|
| retail | xmm6 [ebp-0xf4], xmm5 [-0xf8], xmm4 [-0xfc], xmm3 [-0x100] |
| ours | xmm5, xmm4, xmm3, xmm6 |

The four values are spilled before the call at +0xcf..+0xe7, in the same order in both, and are live across it. Their reloads form a basic block of their own.

## Mechanism (inference)
The reloads have no successors in that block, so their scheduler priorities tie. Their order is therefore the register allocator's split-range reload insertion order. Ours inserts the xmm6 value last.

## Next
- Find which candidate order the allocator uses when it inserts reloads at the end of a split range. Use `build/xs/trace/regalloc_trace.py` (the xmm candidates' numbers and priorities) and the scratch `build/agL/split.py`.
- Then change the declaration or first-use order of the four values (or their priorities) so that the xmm6 value is inserted first.
