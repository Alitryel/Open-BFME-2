# 0x2F71A6 Pathfinder::internal_findHierarchicalPath — single exit (opus r13, 2026-10-20)

Bank: `reverse/attempts/0x002f71a6.cpp`, fit 0.91609 (len 4611 vs 4605, nd 126; was 0.88601/nd 269).
Base: `0x002f71a6-frame-20261020/k0c0pf.cpp.txt` (HSO ctor options, plain `ICoord2D goalBlockNdx`).

## Found (target evidence: retail frame offsets)

The prior bank had two reached-goal exits (one inside `if(useMineshaft)`, one
after the portal loop). MSVC tail-merges them, but the frame packer counted
both copies' references, so point/options/goalBlockNdx were ordered wrong.
One exit after the portal block, guarded `if(!reachedGoal && zone...)`, gives
retail's frame exactly: point -0x28, options -0x1c, goalBlockNdx -0xc. (A goto
to a `found:` label at the function end scores identically.)

## Remaining residue

1. Entry: retail `push esi; mov esi,[ebp+0x70]` (rawTo in esi, `from` in edi);
   ours keeps `this` in ecx->ebx. The waypoint cursor lives in edi with home
   slot [ebp+0x2c] and `xor edi,edi` is the zero register after the loop.
2. Stack-slot permutation in the scan / portal region (follows from 1).

## Threshold finding (structural inference, probes in g3..g6)

Retail's register shape appears only when the function is below a size
threshold. Cut ladder on the best body (g3/g4): removing scan blocks, portal,
bridge, re-goal, barriers or the vector erase alone does not flip it; c11
(c10 minus `extent`) flips. On c11, adding before the loop:
- `if(g)g2=1;` (volatile or not) -> flips back (g5 L*/T*, g6 B1/N1);
- plain stores, calls x4, `if/else` with two stores, `?:` -> stay flipped (g6).
So the threshold counts conditional branch blocks (if/else and ?: get
if-converted), not statements or calls. Retail therefore has fewer
branch blocks than our source. Candidates not yet tried: scan conditions
written as ZH's separate `if(...) continue;`, `if(k&1)offset=-offset` x4,
`(m_pathInfo?..:0)`, inline hierarchyClosed/Open helpers with branches,
goalCell-null return shape (retail separate `xor eax,eax; jmp` at +0x2a8).

## Disproved this session (do not repeat)

- Dropping any subset of extent / initialCell / wasMineshaft / zone1 /
  parentLayer from the full body (g2): no flip.
- Cuts c1..c10 (scan blocks, portal, bridge, re-goal, barriers, erase): no flip.

Scripts: `g1` single-exit variants, `g2` diag removal combos, `g3`/`g4` cut
ladder, `g5`/`g6` dummy-block probes, `flip.py` prints the entry signature,
`offs.py` compares ebp-offset ref counts, `rng.py` slices an asm dump.
Scoring: `0x002f71a6-frame-20261020` score/fr helpers.
