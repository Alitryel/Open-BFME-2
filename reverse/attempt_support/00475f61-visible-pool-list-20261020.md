# 0x00475F61: visible pooled-list members and C++ free (partial)

Symbol `?rva00475F61@Rva00475F61Iface@@UAEXAAV?$vector@PAVObject@@V?$allocator@PAVObject@@@_STL@@@_STL@@@Z`, retail RVA 0x00475F61, 1668 bytes, bank `reverse/attempts/0x00475f61.cpp`. The banked body is measurably closer than the 0.38 bank it replaces; it is not exact. Model: claude-opus-5-5. Inputs: checkout 9a334fe1b74a48c9b99c97685e0ad11d154ee822, reference/open-bfme-1 0dc8a26a9c6041c73dc564754cd059dc54faa72a, flags unchanged from the bank (`/O1 /G7 /arch:SSE /EHsc`, STLport).

## Result

Every number below is `tools/align_diff.py <file> <symbol> 0x00475F61 1668` with `BFME_OBJSTORE=off` and a fresh object per trial.

| Source | Emitted | Structural regions | Memory | Register |
| --- | ---: | ---: | ---: | ---: |
| previous bank (score 0.38) | 1677 B | 29 | 105 | 27 |
| new bank | 1659 B | 17 | 67 | 20 |

Retail is 1668 bytes, 471 instructions. The new body is 9 bytes short of retail without dropping anything: it carries the same 42 call relocations as the old bank, and the shortfall sits in the register and layout differences listed below.

## What changed and why

1. **Pooled-list members are visible again.** The old bank declared `list<Object*,Rva001EB984PoolAllocator>::insert` and `_List_base<...>::~_List_base` as body-less explicit specializations, and `vector<PooledMemberList>::~vector` likewise. cl 7.1 then had to assume that the local `groups` vector escapes, because its destructor reaches an opaque function. Retail proves the opposite: it computes `groups.size()` once in the names-loop preheader, after the loop guard (`mov [ebp-0x30],eax; sar dword ptr [ebp-0x30],2` at 0x476268), which is loop-invariant code motion that needs an unaliased `groups`. With the STLport bodies visible and both inner loops written `i < groups.size()`, our compile hoists it to exactly that place. Controlled diagnostics: with only the `~_List_base` declaration restored, `groups` escapes again (size recomputed every iteration, 26 regions); with only the `insert` declaration restored, hoisting survives. Scratch probes confirmed that cl hoists `vector::size()` across opaque calls when the constructor, destructor and push_back are visible template bodies.
2. **STLport frees through the C++-linkage `_STL::free`.** With every body visible and the CRT's `extern "C" free`, cl proved `groups`' teardown nothrow and dropped retail's `or dword ptr [ebp-4],-1` before the vector destructor (0x476474). Declaring `namespace _STL { void __cdecl free(void *); }` around the STL includes, as the existing units for 0x00030830 do (`?free@_STL@@YAXPAX@Z` is pinned there), restores the store.
3. **One reference per matched group.** Retail computes `&groups[i]` once (`lea edx,[eax+ecx*4]` at 0x4764D2 and `lea eax,[eax+ecx*4]` at 0x4765A3) and keeps it in `[ebp-0x1c]` across the calls of both arms; `PooledMemberList &group = groups[i]` in each arm reproduces that.
4. **AICommandInterface is a base at +0x20** of the AI update class (as in Zero Hour's `AIUpdateInterface : UpdateModule, AICommandInterface`) instead of a member reached through an accessor. This alone changed no bytes; it is kept because it is the more faithful shape.

The helper instantiations the unit now emits compare, outside relocation windows, as follows against the retail callees: `vector<PooledMemberList>::push_back` = 0x00475F2A (55 B, 0 differing bytes), `~vector` = 0x004758D6 (30 B, 0), `list::push_back` = 0x001EC03C (26 B, 0), `list::insert` = 0x001EBD16 (37 B, 0), `_List_base::clear` = 0x001EB130 (42 B, 0). The pool-allocator model still differs in `_List_base` construction (0x001EB984, ours 29 B against 40 B), `~_List_base` (0x001EB769, 25 B against 29 B) and `erase(first,last)` (0x004758F4, 54 B against 51 B). These are leads for the scoped helper bindings, not proofs.

## Remaining mismatch (17 regions)

- **Rank comparison in the first loop** (4 regions at +0x231..+0x262): retail CSEs `&m_indices` into EBX and spills the first rank into the shared `[ebp-0x18]` slot. Writing `m_indices[...]` directly with named `a` and `b` reproduces that block exactly, but cl then gives `a` its own slot, the frame grows to 0x9C and every stack operand shifts (13 regions, 113 memory, 29 register), so it was not banked. Single-expression comparisons are worse: cl materializes both key temporaries before either call.
- **Names-loop back edge** (+0x4E1..+0x4ED): retail increments the iterator in ECX and carries it into the loop head; ours uses `add [mem],4` and jumps to a reload block. Because the preheader then ends with a `jmp`, cl places the first loop's found block (push_back into `groups[i]`) in that gap (+0x30E) instead of after the epilogue (+0x530 in retail). Post-increment, `const_iterator`, a pointer to the names vector and a const entry pointer changed nothing.
- **Template versus team in EBX** (+0x323, +0x346, +0x498): retail keeps the team in EBX across `memset` and spills the template to `[ebp-0x18]`; ours does the reverse.
- **AI receiver** (+0x615, +0x662, +0x65A): retail loads `m_ai` into EAX and forms the receiver with `lea ecx,[eax+0x20]`; ours loads into ECX and adds. The base-class model did not change it.
- Stack homes are a permutation of retail's: the same variables share slots, but retail orders them temps/`a`/`tmpl` at -0x18, held/iterator/entry at -0x1C, index at -0x20, while ours puts held/iterator at -0x18 and the temps at -0x30. Most of the 67 memory differences are this permutation.

## Ruled out in this run

Loop-1 `i < groups.size()` while `groups` still escapes (size recomputed per iteration, 28 regions). A visible vector destructor alone (no change). Single-expression or swapped-operand rank comparisons (26 regions). Iterator spellings for the names loop (no change). Declaring the replacement pointer before the template lookup (18 regions).

## Resumption

Start from the bank. The highest-value open question is cl's stack-slot packing: if `a` can share retail's `[ebp-0x18]` slot, the `m_indices` spelling gains four regions at no cost. The names-loop back edge is the second lever, since fixing it should also move the found block behind the epilogue. Landing still needs the scoped helper bindings above and a home unit; `repair_queue.py dest` offers only the StlportVectorPushBackFamily.cpp neighbour heuristic.
