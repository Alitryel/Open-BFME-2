# 0x004B1633 EmotionTrackerUpdate::update — Opus pass 2026-10-19

Start: bank 0.86233 (16 regions, 2193/2200 B). Result banked at
`reverse/attempts/0x004b1633.cpp`: 7 regions, 2195/2200 B, align_diff memory 29 / register 8
(was 54 / 22); score `1 - (6 + 29 + 8) / 661 = 0.93495`. Same includes, flags and callee views
as the earlier bank (`0x004b1633-20261019-w6`).

## Levers that worked (each n=1, cumulative)

1. Range test inlined (`if((range20>0 || range24>0) && forcedFrames==0)`, no `rangeEnabled`
   bool): 16 regions, and the bool is no longer materialized.
2. Else arm of the activation: `EmotionNugget *a=active;` local before
   `rva004DCC84(findObjectByID(targetID[a->entry->kind]),0)` keeps `active` in a callee-saved
   register and stops the two call arms tail-merging: 15 regions.
3. Closest block: `ObjectID id=closest->getID();` local cached in EDI across the two
   `findObjectByID` calls, compare `id!=targetID[kind]` first: 9 regions.
4. Shroud query: `const BfmePointFD *p=me->getPosition();` local before the
   `rva00739830(p,1,enemies)` call fixes argument evaluation order: 7 regions.

## Remaining residue

- +0x19 `mov [ebp-0x34],ebx` (data spilled at entry) and +0x29f..+0x2ac: retail zeroes EAX
  once (`xor eax,eax; mov [ebp-0x3c],eax; mov [ebp-0x40],eax`) and reuses it in
  `cmp [esi+0xa4],eax` across the `ja` merge. The `bool rangeEnabled=...` spelling (em9a)
  restores the entry spill but materializes the bool (+1 B, still 7 regions).
- +0x575/+0x586: retail loads `ebx=[esi-8]` (me) after the status test, calls
  `other->rva0028B511()` first, spills to `[ebp-0x18]`, calls me's, then reloads
  `ebx=[ebp-0x34]`. Ours calls other first but loads me after.
- +0x3b5: one extra 3-byte instruction (follows from the data/other spill choice).

## Disproven (inert or worse, from the 7-region body)

- chained `bestNeutral=bestAlly=0` (both orders); `bestAlly=bestNeutral` with `forcedFrames==(int)bestAlly`
- nesting the range test as `if(range...) if(forcedFrames==0)`
- enemies call nested inside the shroud call args (hoists pos)
- `Object *me=...` local before the closest-block status test (me's call goes first)
- swapped rank operands, with and without `me`; `static inline bool sameRank(a,b)` helper

Landing still needs rows or address-derived pins for 0x4B13D8 and 0x4DCC84 (both banked
partials) and the home TU `Code/GameEngine/Source/GameLogic/Object/Update/EmotionTrackerUpdate.cpp`.
