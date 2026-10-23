# Q1Receiver0134FAAC::refresh 0x6227E0, r46 term-order study (2026-10-20, claude-opus-5-5, ~65 min)

Bank reverse/attempts/0x006227e0.cpp stays best: 3244/3244 B, EH exact, 8
start-cursor displacement operands in the two count tails (ours s2 s1 s0 in
both arms, retail s2 s0 s1). Scratch: build/nbr/r46/6227e0 (mc.py compiles to
its own .obj; mgrid.py mini grids; run.py full grids; ord.py labels n/f/s order).

VC7.1 term-order rules measured (mini TU deque<int>[7], same flags; confirmed
in the full body):
1. Source associativity/grouping is flattened (a+b+c == a+(b+c) == a+(b+c-x)).
2. Fixed context -> fixed order from source term order. Member addressing,
   source (a b c): pass 0 n:c b a f:a c b s:b c a; pass 1 (-x arm) n:c b a
   f:b a c s:c a b. Under that rule retail's pass 0 is impossible (f's last
   must equal s's first).
3. The order is reshuffled by the count of struct temporaries created earlier
   by inline expansion (iterator copies, struct-returning inlines; a discarded
   x.begin() shifts it with no code). Period 8: s every step, f every 2, n
   every 8. Count-only (which deque/where irrelevant). Plain loads, derefs,
   int-returning inlines and calls do not shift it.
4. Deque addressing per term: member m_deques78[k] (M), `queues` pointer local
   (P), reference local (R); `self=this` behaves as M. Deque 0 via P/R: n1 n2 n0
   and hoisted f1 right, but s0 always last at every shift 0..8 (the residue).
   Deque 0 via M: s0 moves, but f1 never hoists while n1 n2 n0 holds.
5. Grid 27 spellings x 8 shifts = 216 compiles: none gives retail's
   n1 n2 n0 f1 | f2 f0 s2 s0 s1 | f0 f2 s2 s0 s1. Ties at 8: k0 PMM/PMP/PPM/PPP,
   k1 RRM/RRP, k2 PRM/PRP. Raw byte offsets off this: 3194-3258 B.
Correction: the deque object is at +0x78 with _M_start at +8, so deque 0's start
cursor is not offset 0 from `queues`.
WB 0x167A320's tail order differs from retail (all f hoisted; pass 1 s1 s2 s0):
not an order oracle.

Untested: a deque-0 spelling that acts like P/R for n,f but not s (different
real container/wrapper layout, a phase-queue struct, a count accessor whose
inlined this is a separate temp without changing the inline budget: earlier
accessors gave 2656/3268 B); then select the shift with natural iterator-temp
changes (explicit iterator local in the eviction loop, empty() vs size()!=0,
end() temps in the find comparisons).
