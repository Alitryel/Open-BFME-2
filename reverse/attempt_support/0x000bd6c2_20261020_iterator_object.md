# 0x000BD6C2 W3DScriptedModelDraw event update: STLport iterator objects (2026-10-20, seat w6, second run)

## Result

Blocked. The bank `reverse/attempts/0x000bd6c2.cpp` (arm-advance spelling) stays the best body and is unchanged: re-measured at 898 B, 2 structural regions, 2 memory, 0 register differences.

Hypothesis tested: the original walks the destroy list with a real STLport iterator object (`++it`, `*it`) and one for-increment, and the `*it` read inside the particle arm (WorldBuilder 0x945CC0 `local_80`) survives as a node use because the iterator's `_M_node` is an aggregate field. Refuted: cl 7.1 enregisters `_M_node` like a plain pointer and merges every in-arm `*it` read with the type-test load, so each iterator spelling compiles to the same bytes as the raw-pointer single-increment spelling (the visible-erase state).

| body | size | structural regions | memory | register |
|---|---|---|---|---|
| bank (arm advance, unchanged) | 898 B | 2 | 2 | 0 |
| every iterator-object spelling below | 903 B | 2 | 9 | 1 |

The 903 B state has the node in EBX and the nugget and hoisted particle ID in EDI, and it does not share the list-destructor tail (+9 B), exactly as described in `reverse/attempt_support/0x000bd6c2_20261020_visible_erase.md`.

## Iterator spellings measured (all 903 B, 2 regions, 9 memory, 1 register)

The shim iterator mirrors STLport 4.5.3: `_List_iterator_base` holds `_M_node`, defines `_M_incr()` and the base `operator!=`/`operator==` taking `const _List_iterator_base&`; `_List_iterator<T,Traits>` derives from it with a user-written copy constructor, `operator*` returning `T&` to the node's data, and `operator++` calling `_M_incr()`. The shim list gained `begin()` and `end()`. In this body retail inlines both iterator helpers (`mov edi,[edi]`, `cmp edi,[ebp-0x14]`); their rowed out-of-line copies (`_M_incr` 0x0006E25E, `operator!=` 0x006CFE40) come from other units.

- Destroy loop `for(it=events.begin();it!=events.end();++it)`, type test `(*it)->type==9`, nugget re-read from `*it` inside the arm (WorldBuilder's shape), find loop over `particleIDs` with an iterator `id` and `erase(id)`.
- The same with the raw-pointer find loop.
- Post-increment `it++` (STLport `operator++(int)` with its temporary copy), in the destroy loop alone and in both loops.
- The iterator declared before the loop (default constructor) and assigned from `begin()`.
- All three list loops (create, destroy, find) as iterators.

## Mechanism probes (scratch only, not for landing)

- A `g_sink=(int)n;` store in the type-miss path (`else`) of the single-increment spelling does not flip the roles (911 B, 3 regions, 9 memory, 1 register). Together with the earlier probes (a node use anywhere inside the particle arm flips, one at the loop top does not), the decision is not a weighted use count or a per-block count: only a node reference inside the particle arm's region changes the order. This fits a region-based allocator in which the arm's own variables are coloured first, but that is an inference, not a measurement.
- The in-arm nugget read typed as an `unsigned` load, read through `EventNugget**`, or read as a `const int` at byte offset 8 of the node: each is merged with the type-test load (903 B, 2/9/1). cl merges these loads by address whatever their type.
- The whole destroy branch as a `__forceinline` member (`stopParticles(Rva00B9AC2&)`): identical to the inline spelling. Plain `inline` keeps it out of line (705 B caller).

## Compiler settings (none closer)

- On the bank: `/O2`, `/O1 /Ot` and `/Ox` give 1063 B (51 regions); `/G6` is identical; dropping `/arch:SSE` gives 896 B with 17 regions; the pinned `vc71-sp1` and `vc71-ddk-4035` compilers are identical.
- On the single-increment spelling: `/Ow`, `/EHs` and `/GR` are identical; `/Oa` gives 887 B with 14 regions and `/EHa` 925 B with 22 regions.

## Remaining mismatch and prerequisite (unchanged)

The bank's residue is the particle arm's own advance, scheduled before the handle destructor's EH-state store and not merged with the type-miss advance (+4 B); see `reverse/attempt_support/0x000bd6c2_20261020_arm_advance.md`. WorldBuilder's single for-increment means the original referenced the node inside the arm some other way, or reached retail's order by a route not yet found; no natural source reference in the arm that leaves no instruction has been found. Landing still needs 0x000C48DB and the strong 0x000B6D26 ctor in the same unit (`reverse/attempt_support/0x000bd6c2_20261020_strong_ctor.md`).

## Inputs

Unit flags as the home unit: `/O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc` with `/Ireference/shims/bfme2_ascii /ICode/Libraries/Include/Lib`. Each trial compiled at its own path and measured with `tools/align_diff.py`.
