# 0x006227E0 Q1Receiver0134FAAC::refresh: per-arm deque addressing (2026-10-20, r55)

The bank went from 8 to 4 differing bytes (3244/3244 B, EH exact).
- Bank: `reverse/attempts/0x006227e0.cpp`.
- The change is in the tail only. It declares `Q1ReceiverQueue &r0/&r1/&r2 = m_deques78[k];` after `queues`, and addresses the deques differently in each arm:
  ```cpp
  if (pass == 0)
      m_field1e0 = r0.size() + r1.size() + r2.size();
  else
      m_field1e4 = m_deques78[0].size() + r1.size() + queues[2].size() - m_field1e0;
  ```
- The s (start-cursor) order and the f order are now retail's in both arms.

## The 4 remaining bytes
- They sit in the head-merged prefix before `test ebp,ebp` (the hoisted node terms).
- Retail loads n1 n2 n0: `[ebx+0xb4]`/`[0xc4]`, then `[0xdc]`/`[0xec]`, then `[0x9c]`/`[0x8c]`.
- The bank loads n0 n2 n1, so 0xb4<->0x8c and 0xc4<->0x9c swap at offsets +0xb23, +0xb2f, +0xb3d and +0xb45.

## Two exclusive families
Every grid lands in one of two families:
- **nd=8 (old bank):** n right, s wrong in both arms.
- **nd=4 (new):** n wrong, s right.

What decides the family is how deque 1 is addressed in arm0:
- Through the reference `r1`, s1 sorts below s0, which fixes s. In the key model of `0x006227e0-licm-hoisted-s0-20261020.md`, the same B number also lowers n1's key (32A + 64B) below n0.
- Through anything else, s stays wrong.

In arm1, deque 0 must be a member, either `m_deques78[0]` or `m_deques78->`, and deque 1 must be `r1`.

## Grids run (counts are compiles; nd = differing bytes)
- **g1, 729:** every M/P/R addressing in each arm, with all refs declared. Best nd=4: prr|rrr x mrm|mrp.
- **g3:** declaration placement of the refs. Inert, as long as the refs come after `queues`.
- **g4:** empty(), iterator local, const_iterator, set const_iterator. Best nd=8.
- **g5, 3567 of 4096:** adds pointer locals `pk->size()`. Best nd=10.
- **g6, 194:** arm control forms.
  - `if (pass)` / `!= 0` / `== 1` with the arms swapped: 145-312.
  - Two ifs, `else if`, `switch`: body +2 B.
  - A hoisted `int total` or `unsigned total`: 3011.
  - Only `if (pass == 0) ... else ...` works.
- **g7, 270:** arm1 spellings `{=S; -=}`, `-x + S`, `X0 - x + X1 + X2`, `(int)` casts. All identical: nd=4 at the same addressing.
- **g8, 1296:** deque 0 and 1 in both arms over m / p / r / x (pointer local, declared only when used) / `queues + k` / `m_deques78 + k`.
  - m is the same as `m_deques78 + k`, and p the same as `queues + k`.
  - The x forms do not help.
  - Floor nd=4, always the same n swap.
- **g9, 272:** inline count helpers.
  - Member inline (const or non-const, int or unsigned, loop body): 2713.
  - Free `static inline Q1Count3(q)` called with `m_deques78` or `queues`: 274-339.
  - All of these × 0-15 struct-temp shifts: no helper is near.
- **m1:** an int-local meter. Period 8, never 0.
- **m2, 952:** struct-temp meter, 56 g1 bases × 0-16 discarded `m_set190.m_tree.begin();`. Only k=0 and k=4 keep nd=4. No base goes below 4.
- **m3, 512:** struct-temp shift 0-255 on the bank and on the old nd=8 bank, to test key wraparound once temp numbers pass ~1365. Floors stay 4 and 8; above about 180 the code changes structurally. The n swap is invariant under uniform shifts.
- **g10, 32:** const on each ref and on the `queues` pointee or pointer. All inert, nd=4.
- **g11:** `deque<Rva009EF0D0Element *>` instead of `deque<int>`, with the casts dropped. The count tail changes from +0xb4a on (nd 349-351, plus 8 unresolved instantiations). Disproven.
- **permute.py:** it stops at once ("only constants or offsets differ"), because the residue looks like displacements. It cannot search this body.

## Not yet tried
- Changing the numbering of upstream code without changing its bytes (equivalent STL spellings in the keys loop and the eviction loop) to shift d1's A against its B.
- Recovering the c2 tracer (`build/agO`, not preserved) to read the A and B numbers of the nd=4 bank directly.
