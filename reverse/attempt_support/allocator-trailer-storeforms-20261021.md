# 0x006C4730 GeneralAllocatorDebug realloc: store-form round (2026-10-21, claude-opus-5-5)

The bank `reverse/attempts/0x006c4730.cpp` is unchanged: 798 B, nd 18, with retail's
allocation, and only the backup trailer at +0x9b..+0xb3 differs. Earlier rounds:
`allocator-trailer-attractors-20261020.md`, `allocator-trailer-materialize-20261020.md`
and `allocator-trailer-copyprop-20261020.md`. Scratch for this round is `build/c6/`
(`score.py`, grids `g1`..`g5`). Every result below is measured against the full
798 B target.

## Target facts (new this round)
- The out-of-line sibling 0x6C1CC0 (`Rva006C33D0Purge_Rva006C1CC0.cpp`) has the
  same malloc+trailer shape. It tail-duplicates the folded store into both arms,
  as `mov word [ecx+eax-0xa],0; ret 8`. 0x6C3940 also folds, with an immediate.
- Only the inlined copy in the realloc keeps `lea ecx,[ecx+eax-0xa]; mov word [ecx],bx`
  at the join. An image scan for an unfolded `lea r,[a+b+d8]` followed by a store to
  `[r]` in matched rows finds only multi-use addresses. One example is Apt
  0x6E3E20, where `slot = m_slots[slot]` goes through a forceinline `int &`
  parameter, so the read folds and the write uses the lea.
- The `wpo_detect` claim that 0x6C2270 reads edi/esi is a false positive: it pushes them.

## Refuted this round (attractor in brackets)
- **Size phi with h reused, h4** [784, retail allocation, only the store folds].
  This is the closest size-phi form.
- **Per-arm reuse of h, the size parameter or `h &= M`** (h1-h3), and `register n` (e2)
  [814 flip].
- **Per-arm pointer with -6 folded, e1** [798, nd 197].
- **Dead or self-cancelling reads and stores at the trailer address** (d1-d9):
  - `old = *t`;
  - `*t &= 0`, `^= *t`, `-= *t`, `*t * 0`;
  - `(void)*t` after the store;
  - a dead store first.

  All are simplified before CSE [784].
- **Struct copy of a 2-byte `Len16 {ushort}`** (s1-s5, s8), in the bank and size-phi
  worlds, from `{0}`, by member assignment or via a named pointer
  [bank 18 / size phi 784]. `memcpy(t,&z,2)` with a named t also folds [784].
- **A forceinline or inline helper taking `unsigned short &`** (the Apt RMW analog,
  r1-r3, r5, r6, r8), and a named reference local (r4, r9)
  [bank 18 / size phi 784].
- **Run6-style `usable = n - 8; *(p + usable - 2) = 0`** (r7) [784].

## Still untried
- A source in which retail's join value is a compiler CSE temp, not a user
  variable. That needs a second, non-removable use of `p+n-10` in the same block
  that is not a call.
- An `oldChunk` placement that keeps the semantics. Permute showed that its live
  range alone moves the materialized form back to retail's allocation
  (`allocator-trailer-materialize-20261020.md`).
