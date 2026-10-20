# Pathfinder::internal_findHierarchicalPath (0x002F71A6, 4605 B): plain-local structure, frame order rule

Target `?internal_findHierarchicalPath@Pathfinder@@IAEPAVPath@@_NHPAVObject@@PBUCoord3D@@200PAU4@@Z`, retail RVA 0x002F71A6, 4605 bytes. The bank, `reverse/attempts/0x002f71a6.cpp` (fitness 0.88601, 4613 B), is unchanged. Model: claude-opus-5-5, 2026-10-20. This continues `../0x002f71a6-budget-20261020/readme.md`.

## Result

No new bank. The best plain-local body, `k0c0pf.cpp.txt`, scores 0.86378 (4609 B) and loses to the bank. The cause is frame order: ours puts `point` above `options`, and every slot below them shifts. That body carries two confirmed source facts the bank lacks, so it is the better starting point once the frame order is solved.

| body | len | nd | slots off | point | options | goalBlockNdx |
|---|---|---|---|---|---|---|
| bank (SearchStorage struct emulation) | 4613 | 269 | 122 | -0x28 | -0x1c | -0xc |
| k0c0pf (plain locals + HSO ctor) | 4609 | 426 | 149 | -0x18 | -0x28 | -0xc |
| retail | 4605 | | | -0x28 | -0x1c | -0xc |

`fr.py.txt` prints these columns. Copy it to `build/h72/` beside the bank's `score.py` (`compile_` uses `build.try_compile_source` into a local .obj, never the shared cache).

## Confirmed source facts (retail evidence)

1. **`goalBlockNdx` is a plain local `ICoord2D goalBlockNdx;`** (the ZH shape), not a struct member. Only this gives retail's CSE of `goalCell->m_info`: `mov edi,[edi]` at +0x485 and `mov esi,[esi]` at +0xa50.
2. **`options` has type Rva002E8BCF** (16 B: `Int surfaces; Bool f4, f5; Int maxLayer; Bool fC`), the same class as the out-of-line ctor at 0x2E8BCF (`Code/GameEngine/Source/Common/Rva002E8BCFCtor.cpp`). Here it is built by an inline five-argument ctor with the calls inside the argument list:
   `Int priority=obj->m_template->priority; Bool flag=obj->m_template->flag; HSO options(surfaces,!flag,priority-1,obj->rva0028AFBB(),obj->rva0028AC62());`
   Right-to-left evaluation calls AC62 first, and the layerFlag spill moves to retail's `[ebp+0x28]` (separate locals put it at +0x2b). `g22.py.txt` generates this family. k1 (`__forceinline`) and k2 (other store order) are no better.

## MSVC 7.1 frame order in big frames (probe-established)

The probes are `probe_gen8.py.txt` and `probe_gen9.py.txt`, read with `probe_run3.py.txt`. An `int arr[40]` forces locals past the disp8 window.

- Locals sort by density = static reference count / size. Higher density gets the higher address, nearer `ebp+0x58`. Loop depth adds no weight.
- Exact density tie between different sizes: the larger local (more refs) goes higher, whatever the use order.
- Exact tie at equal size: the local used later goes higher. Declaration order is irrelevant.
- Small frames (all disp8) order differently: P3 always sits above a 16-B struct there.
- Reference weights (gen9):
  - A field-wise copy counts 3 refs: HierarchyPoint ctor, copy ctor, explicit fields, `set()`, `copyCoord3D`.
  - A POD copy or `HierarchyPoint::operator=` counts 1.
  - An inline `this` adds nothing, and a repeated dead store is not counted.

In the full function, final counts are identical in ours and retail: point (adjustTo, 12 B) 15, options (16 B) 20, goalBlockNdx (8 B) 10. All three are density 1.25. Retail's order (gb, options, point) is the tie rule with options winning as the larger local. Ours puts point above options, so point must count at least one more ref in our source before tail merge/CSE.

## Next hypothesis (untested, start here)

`k0c0pf` writes the reached-goal exit twice, once inside the mineshaft branch (about line 184) and once after the portal loop (about line 228):

```
if(parentCell!=goalCell)...; m_isTunneling=false; path=...; rva002F40E7(); goalCell->ReleaseInfo(); goalCell->ReleaseInfo(); *adjustedTo=adjustTo; return path;
```

The compiler tail-merges the two copies, but before the merge `adjustTo` has 16 refs (density 1.333) and outranks options. ZH writes the exit once, inside the while loop (AIPathfind.cpp about lines 7681-7690). With one copy in source, point should tie options, and options should go higher, as in retail.

Spellings to try:
- a single `if(reachedGoal)` after the mineshaft handling, with the mineshaft case falling through;
- a goto to one shared exit label;
- a ZH-style loop body with one exit.

Check each with `fr.py` for `pt[-0x28] op[-0x1c] gb[-0xc]`. If the exit is already single in retail's shape but point is still high, look for other duplicated or CSE'd `adjustTo` reads, such as the `to=&adjustTo` alias uses.

## Remaining residue apart from the frame

- +0x1131: retail has `mov eax,[eax]; push 1; push eax`, ours `push 1; push dword ptr [eax]`.
- +0x116f: retail's merged tail reloads parentCell from memory (`mov ecx,[ebp+0x54]; cmp [ebp+0x50],ecx ... push [ebp+0x50]`), while ours uses `esi`. This also points at a different source shape of the shared exit.
- End: ours has an extra `mov edi,[ebp+0x54]; mov ecx,edi`.
- The positive-offset scalar slots are permuted (for example the var live 0xeb-0x1160 sits at retail +44, ours +64). This should mostly follow from the frame order.
- The block-threshold register regime (rawTo/cursor at entry) is still open; see the budget handoff.

## Ruled out

The c2.dll `DO_REJECTED_*` strings belong to the vectorizer only and have nothing to do with this frame or allocation.
