# Pathfinder::internal_findHierarchicalPath (0x002F71A6, 4605 B): one cause behind the entry and cursor residue

Target `?internal_findHierarchicalPath@Pathfinder@@IAEPAVPath@@_NHPAVObject@@PBUCoord3D@@200PAU4@@Z`, retail RVA 0x002F71A6, 4605 bytes. Bank `reverse/attempts/0x002f71a6.cpp` (score 0.88601) is unchanged. Model: claude-opus-5-5, 2026-10-20. Every compile below is a single probe (n=1) with the default compiler unless stated.

## Result

Blocked, bank kept. No new body was banked, because every probe that reproduces retail's register shape is a cut-down diagnostic, not a complete body.

Bank as measured this round (`tools/align_diff.py`, size 4605): ours 4613 B, 40 structural regions, 171 memory and 39 register operand differences (91 relocation and 238 branch lines are not defects).

## Finding: the residue is one budget effect, not five spelling problems

Earlier seats listed five separate residues in the first 0x270 bytes: retail loads rawTo into `esi` first and delays `mov ebx,ecx`; retail keeps the mineshaft waypoint cursor in `edi` with a home slot and `lea esi,[edi+0xc]`; the waypoint loop is inverted (`test edi,edi; mov [home],edi; je`) where ours jumps to the bottom test; retail reloads rawTo into `esi` after the loop; and retail caches zero in `edi` (`xor edi,edi; cmp eax,edi; push edi`).

All five appear and disappear together, and what switches them is the number of variables in the rest of the function, not anything in the mineshaft block:

- dP (the bank reduced to setup, the main loop spine and both tails; `mk.py.txt` builds it) gives ours' shape: rawTo in a scratch `ecx`, the cursor only in memory, and no zero register.
- dQ is dP minus one unused, address-taken `Disp32IntPair extent` local and its `get` call. It gives all five retail features at once: `push esi; mov esi,[rawTo]`, delayed `mov ebx,ecx`, the cursor in `edi` with a home slot, the inverted loop, the rawTo reload into `esi` after the loop, and `xor edi,edi; cmp esi,edi`.
- Removing `Bool reachedGoal` from dP instead of `extent` flips it the same way. So does removing the closest-cell tail, or reducing the main loop body to `PutOnClosedList`.
- Cutting the body anywhere before the main loop (dE, dB, dC, dD) always enregisters the cursor and rawTo.

So cl 7.1 has a per-function budget of tracked variables. Over budget, it gives up register allocation for rawTo, the waypoint cursor and the zero constant. Within budget, it reproduces retail.

## What counts toward the budget (n=1 each)

| probe on a body at or one over the edge | effect on the cursor |
|---|---|
| remove the unused address-taken `extent` aggregate | admitted (counts) |
| remove `Bool reachedGoal` (a cross-block flag) | admitted (counts) |
| add a short-lived `void*` used inside one block, at the top or at the end | no effect (does not count) |
| add the same `void*` live across an `if`/`else`, at the top or at the end | pushes the cursor out (counts; position does not matter) |
| one, two or four extra `g_sink=(int)way` stores, or one or three opaque `sink(way)` calls | no effect: the cursor is dropped regardless of its own use count |
| remove the float `distance` local | no effect |
| remove the single-use `layer` local | no effect |
| hand-expand one `allocateInfo` instance | identical code (inline parameters do not count) |
| remove the `zones` or `to` alias pointers | identical code (folded) |
| drop every `_ReadWriteBarrier` | no effect |

The full body overshoots the budget by several variables. Removing `initialCell`, `wasMineshaft` and `zone1` together (not semantic, diagnostic only) still leaves the cursor in memory, and so does doing that and dropping the four scan blocks, the portal loop or the bridge loop. Removing all of the bridge, goal-switch, portal and scan blocks plus the vector erase leaves dP, which is still one over.

## Ruled out this round (n=1 each)

- The CandidateStorage union as the cause on its own: a plain for-scoped `Waypoint *way` and a plain `PathfindCell *closestCell` (dK) compile to the same memory-homed cursor.
- Callee visibility: `rva002E8BF8` and its 0x002E7917 clamp wrapper are already visible in the bank context. Adding visible copies of the leaf getters 0x002E6ECA, 0x002E6E6C, 0x002E6B06 and 0x002E6AF3 gives byte-identical output for both the bank and dK. A visible body for the `rva002E79A8` view behind `Rva002E8C4DCall`, or a visible typed helper for the `closest` point, changes nothing either.
- Compiler build: `// compiler: vc71-sp1` gives byte-identical output to the default compiler for dK and dP.

## What the next seat should do

1. The open question is why retail's full body fits the budget while ours, with the same blocks and calls (all 139 REL32 sites already audited), is several variables over. The main loop's allocation already matches retail, so the excess must be variables that cost budget without changing the loop's registers: cross-block scalars and address-taken aggregates that EA's source did not have, or had in a scope the budget does not charge. Candidates in the bank to examine against retail's stack slots: `SearchStorage` and `CandidateStorage` themselves, `HierarchyPoint originalTo`, the mineshaft `delta`, the bridge-loop `ICoord2D temp` swap, `wasMineshaft`, `initialCell`, `parentLayer` and the separate `startDistance`/`endDistance`.
2. Use dP and dQ as the test bench: a source change that removes a counted variable from the bank's spine should turn dP into dQ's shape. `mk.py.txt` rebuilds dA, dK, dE, dL, dP and dQ from the bank (`python mk.py.txt <bank.cpp> <outdir>`); it was checked to reproduce the trial sources byte for byte.
3. Do not spend trials on cursor spellings, loop forms, barriers, sinks, alias pointers or the union: none of them changes the budget.

Scratch evidence for this round (listings, probes and align logs) is in `build/h71/` of the seat checkout, which is not tracked.
