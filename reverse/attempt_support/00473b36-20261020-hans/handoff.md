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

Follow-up 22:05-22:10 PT: cached end across loops 1-2 and unsigned index were inert. Under fsc, an explicit count loop from first (538) and std::distance(first,end) (542, R=37) were both worse.

## Session 2 (22:12-22:35 PT): banked m1, R 17->14
Banked: declare `ContainmentList::iterator first = outer.objects->begin();` right after `int count = size();`, before the `count < 2` early-out. Loop 2 walks `first`.
Result: struct 4 / mem 4 / reg 1, 537 B. Loops 1-3 all match retail now (loop 1 copies first ESI to ECX; loop 2 index is in EDX).
Two diffs remain, both in the size() count loop:
- (a) It isn't rotated. Retail does `xor edi,edi; cmp ecx,eax; je <return>` then a do-while; ours jumps to the test.
- (b) Begin goes to ECX and is copied to ESI after the loop. Retail loads ESI first and the count loop walks an ECX copy.
Refuted on top of m1:
- Defining first BEFORE size() (any form: decl, assignment, named end first, count loop from first): loop-1 regs collapse, 535-542 B, R~36.
- Count via a for/while/std::distance loop: identical. The (int) cast, size_t, and a const list ref: same or worse.
- An empty()-guard before or with count<2 adds retail's entry test (q2), but loops 1-2 regress (541 B, R=21).
- Explicit do-while count: 535. loop3 sharing `first`: inert.
Next idea: q2 reproduces retail's entry test, so look for why its loop-1/2 allocation regresses.

## Session 3 (22:22-22:30 PT): banked u4, R 14->12
Banked: `int count = 0; if (!outer.objects->empty()) count = (int)outer.objects->size();`, then `first`.
This reproduces retail's empty entry test (`cmp ecx,eax; je <return>`): 541 B, struct 4 / mem 4 / reg 1, insns 12/13.
The guard is redundant source; treat it as a hypothesis.
A hand-written do-while count under the guard (v3) rotates the count loop: 539 B, insns 12/12.
One diff remains: begin is loaded into ECX for the count and moved to ESI afterwards. Retail loads ESI first and counts on an ECX copy.
Every form that defines `first` before the count regresses (z1-z4, v1, v2: 531-539 B, R 16-61). Equivalent guard spellings are identical; a ternary is worse.
