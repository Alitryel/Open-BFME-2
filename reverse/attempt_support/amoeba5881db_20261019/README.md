# HordeMeleeAmoeba::updateMeleeAttack 0x5881DB (2199 B): 3-angle pass 2026-10-19

Result: blocked. The bank is unchanged: it compiles to 2196 B, 3 bytes short of retail. Model claude-opus-5-5.

## Remaining residue
- **(A) Loop-1 list node.** Ours keeps it in ebx, with its home slot at 0x70 and index at 0x60.
  Retail never gives it a register: it reloads the node into eax from [ebp+0x60] at the top
  and at the latch, and keeps index at 0x70. This accounts for the 3 bytes.
- **(B) `needsPosition=0` byte store.** Retail places it before the `lea esi` of the best->position
  MOVSD copy (right after the jbe at 0x5889C1). Ours places it between the 2nd and 3rd MOVSD.

## Key finding: (A) is decided by register pressure across the whole function, not by loop 1
Diagnostic cuts that change the code make loop 1 compile exactly like retail's latch
(`mov eax,[node]; mov eax,[eax]; mov ecx,[list]; cmp eax,[ecx]; mov [node],eax`):
- truncating after `_STL::sort`;
- deleting loop 2, the whole search block, the arrive/rest timer block, the first 3x3 search,
  or the fallback-search best update;
- deleting the single loop-1 idle-branch line `entry.position=unit->m_position; ...`
  (its MOVSD pins esi/edi).

These smaller cuts do not flip it: the forcePosition block, the attack-branch reset, the
rva0028ACEE call, either sqrt score line, the final FIFO call, either half of the timer block.

Retail's source therefore probably differs in the large loop-2 blocks (the timers and both
searches) in a way that keeps loop 2's bytes but shifts global register priority.

`flip.py.txt` reports in about 3 s whether the node left ebx (the unit is loaded from
[eax+8] instead of [ebx+8]). Screen variants with it before running the full scorer
(`h.py.txt`, 8 workers).

## WB 0x146DC50 facts
- Loop 1 is a real STLport `list<Object*>::iterator` loop: begin/end temps every iteration,
  inlined `operator!=`.
- WB's range object has a destructor (`if(owner) owner->vslot0(0)`); retail has none.
- WB's loop 2 has a per-iteration object with a destructor (apparently `best`); retail does not.
- WB is a newer build than retail: `/3.141` is a divide in WB and a multiply in retail, and
  rva002C97E8 takes 1 argument in WB and 2 in retail.
- The store order in the "go to best" block matches the bank.

## Ruled out (byte-identical to the bank unless noted), about 700 variants
- Loop 1 spelling:
  - declaration scope of node, unit, ai and index (30 combinations);
  - 114 single dead locals;
  - STLport iterator/const_iterator/post-increment, a hand iterator with a dtor or copy ctor;
  - inlined address-taking helpers (`advance(Node*&)`), with `Node **cur=&node` at nd 33;
  - fresh index copies in the style of the sibling's `int leader=follows`;
  - split checks, a cached size, an entry pointer, count forms, inline accessors.
- Shared variables across the two loops:
  - a shared unit is nd 149;
  - a shared candidate is 2166 B;
  - a shared entry pointer or index changes nothing.
- Function-scope list, held or victim-position copies: 2199 B but nd 98-120.
- (B):
  - all 6 orders of needsPosition/position/active;
  - all 24 orders of the idle-branch stores;
  - an entry ref or pointer, a {} scope, a bool local, a cell cast, a best pointer, a struct wrapper;
  - an early escape of &best, which also rules out aliasing with best.

## Next lever
Make small, behaviour-preserving changes to the users of esi/edi/ebx in loop 2: the timer
block and both 3x3 searches. Screen each with flip.py.
