# 0x473B36 HordeContain::instigateQuarrel - session 2026-10-19 21:50-22:00 PT (hans-agent-oct5)

Compile note: the bank's relative include `../../../../Include/GameLogic/ContainmentListView.h` only resolves from its Code/ home.
To build it from build/ for probes, swap in the absolute include.
Current bank: struct 4, mem 6, reg 4, 545 B vs 543. Real differing instructions R=17 / O=17.
The only real region is loop 2 (centroid distance, +0xA0..+0x101):
- Retail rotates loop 2: an entry test `cmp esi,eax; je` is scheduled before the 1/count scale.
- It walks the cached begin in ESI directly (no copy) and register-promotes `index` into EDX: `mov edx,[ebp-4]`, `inc edx`, `mov [ebp-8],edx`.
- Ours copies ESI to ECX, jumps to the test, and keeps index in memory (`inc [ebp-4]`).

## New finding (fsc): loop 2 exact, register map elsewhere wrong
Declare `ContainmentList::iterator first = outer.objects->begin();` before loop 1. Keep loop 1 on `it = outer.objects->begin()`.
Write loop 2 as `for (; first != outer.objects->end(); ++first, ++index)`, reading the member through `*first`.
Result: loop 2 matches retail exactly (rotation, index in EDX), at 542 B, struct 4 / mem 5 / reg 7, R=19.
The new wall is that `first` lands in ECX and loop 1's iterator in ESI, the reverse of retail. As a side effect, `push esi` sinks below the count<2 early-out, and the slot107 tail block moves.
Inert under fsc: `register`, decl placement (before it / center / best), while-form, separate loop-1 and loop-3 iterators. const_iterator: worse (535).
Worse: first before the size() count (535), loop 1 `it = first` (540).

## Other refuted ideas this session
Explicit if+do-while for loop 2 (538). Fresh it2 / per-loop scoped iterators: inert.
Cached `end` local: inert. A separate loop-3 index var: worse. `index = 1` right before loop 2 rotates it, but CSEs constant 1 into EDX (544).
A loop-2-local idx copy: rotates, but the frame becomes 0x14.
Open question: what gives retail's long-lived begin ESI over loop 1's iterator while still letting loop 2 consume it.
