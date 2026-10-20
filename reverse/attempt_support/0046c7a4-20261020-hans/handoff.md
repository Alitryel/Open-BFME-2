# 0x0046C7A4 HordeContain::rva0046C7A4 -- hans-agent session 2026-10-20

Bank: reverse/attempts/0x0046c7a4.cpp (897B, align struct 10 / mem 34 / reg 9).
Tools used: capstone retail disasm of game.dat 0x46C7A4..+904 vs capstone of our obj, difflib on
normalised instructions (relocs masked). Real (non-reloc) differing insns: bank 35 retail / 33 ours.

## Retail register map (read from retail bytes)
* `this`: copied to ESI only for the slot-0x118 virtual call, spilled at once to [ebp-0x10]; every
  later use reloads it (ID-set latches `mov eax,[ebp-0x10]; cmp edi,[eax+0x54]`). `this` owns no
  callee-saved register anywhere.
* EBX: list end node (`p.m04->_M_node`) loaded once at the top (`mov ebx,[eax]; mov eax,[ebx]; cmp eax,ebx`)
  and still live in the final skipStatus list loop (`cmp esi,ebx`) -> a cached `last` iterator.
  In the empty (ID-set) branch EBX = pos; in the pos list loop EBX = iterator.
* begin is stored to [ebp-0x14] at the top and reused as the loop start of both list loops
  (`mov ebx,eax` / `mov esi,eax`) and for the final `*first` (mov eax,[ebp-0x14]; mov eax,[eax+8]).
* Neither list loop has an entry test (first != last already known) -> both start at `first`.
* skipStatus list loop returns through the same `mov eax,edi; jmp epilogue` stub as the ID-set
  skipStatus loop (obj local in EDI).

## New structural finding (variant_h2_first_last.cpp)
`first = p.m04->begin(); last = p.m04->end(); if (first == last)`, pos loop
`for (it = first; it != p.m04->end(); ++it)`, skip loop `for (it = first; it != last; ++it) { Object *obj = *it; ... return obj; }`,
`return *first;` reproduces retail's do-while loop shapes, the shared return stub, the cached begin
slot and the final front read. Real differing insns 32/33 (bank 35/33), align struct 12 (size 909).
The barrier in the pos loop is still required (without it 68/68).

## Remaining wall
Pure priority: our cl gives `this` EBX for the whole function, so `last` is spilled to [ebp-0x10]
and pos stays in memory in the ID branch; retail gives `this` nothing (last/pos/iterators win).
Measured inert or worse: inline distance helper taking pos (separate pos webs; identical obj),
pos/last sinks (reshuffle everything: this->EDI), first/last only partially applied (h1*, h2b-d: 896-913B, 12-17 regions).
Also inert: `const set<int> &ids = m_170` alias for the ID branch (identical obj, 32/33), and the whole
ID branch as a __forceinline free helper taking `const set<int>&` (param propagated to this+0x54;
`this` keeps EBX; 114/115). Next untried: m_170 reads under `&&`/ternary (matching.md weight lever),
and checking whether retail's `this` is a secondary-base pointer whose uses in source go through a
separately derived pointer (the call is on this-0xFC).

