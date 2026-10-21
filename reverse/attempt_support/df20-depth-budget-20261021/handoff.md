# 0x0000DF20 wide money_put::do_put(string): depth/budget window search (2026-10-21)

Follows `df20-frame-packer-20261021/handoff.md` and
`df20-funclet-naming-20261021/handoff.md`. Bank `reverse/attempts/0x0000df20.cpp`
is unchanged: fit 0.9993 under the ledger naming, len 2610, frame 0x118, nd 1.
The only residue is the return-1 site @0x28c, which calls S<G> (0xB3C0) where
retail calls 0x142D70. Under the true naming (W<G>->0xB3C0, S<G>->0x142D70) the
best body is `df20-frame-packer-20261021/a9d0sig-true-naming-0.9986.cpp.txt`.
Its only residue is return 2 (41e/42f), which calls S where retail calls W.

## Disproved this round (do not repeat)
All runs used MSVC 7.1 with the flags of the bank header (/EHsc /MD, STLport 4.5.3).

- **g4-g8:** these trials were inert under `#pragma inline_depth(0)`:
  - forceinline specialisations of W, S and D (`_M_deallocate_block`);
  - phantom-dtor budgets, which are position-independent;
  - W carriers without branches.

  Phantoms that reference free in W add EH states (frame grows).
- **g9:** the base was a9s0 with the true scorer. It crossed W-specialisation
  carriers × n{1,2,3} × kS{9..32}:
  - `__destroy_aux`/while carriers at kS 9/12 were inert (0.9958);
  - empty for-loops inlined everything (0.9417);
  - kS>=16 flipped globally to 2530 B (0.9290).
- **g10:** the base was the bank with the ledger scorer.
  `#pragma inline_depth(1,2,3,4,5,6,8)` was placed around return 1 (the whole
  `if`, or the `return` only). Every setting was inert (0.9993, same map).
- **h3:** the base was the bank. The grid crossed phantom budgets kS{0,3,6,8,9}
  × kD{0,4,8,9,12} × kW{0,1,2,4,8}. The results:
  - kD>=9 puts D at all 7 sites (0.9958);
  - kW>=1 puts W at the late sites;
  - S+D in the right range puts S at all 7 sites (the bank map);
  - high totals collapse the returns (2530 B);
  - low totals inline everything (2594 B).
- **h4:** a finer grid kS{1,2,4,5,7} × kD{5,6,7,8}, kW 0, showed the same three
  phases:
  - S+D 9..12 puts S at all sites (0.9993);
  - S+D <=8 inlines everything;
  - S+D >=13 gives 2530 B.

  No point outlines 28c differently from the late sites. The inliner decides
  per callee and per function, not per site, once depth(0) is off.
- **Funclet and WB-order re-check:** in WorldBuilder (VA 0x6e71a0), F (0x6e7be0)
  is the first deferred COMDAT after do_put and is first referenced @0x236.
  B (0x6e4540) is emitted after an earlier function in the same TU. This agrees
  with the true naming.

## Verdict
The inliner disproved every per-site mechanism under the ledger naming:
- control flow (ret1-goto, lifetime-fold);
- lifetime and scope;
- types and layout (frame-packer);
- callee visibility (destructor/constructor-visibility, forceinline
  specialisations);
- compiler settings (inline_depth, budgets).

28c and the late sites must call different bodies. This only happens when the
names differ, which is the true naming. DF20 stays walled until the wide-string
dtor naming is reconciled ledger-wide: W<G>->0xB3C0 and S<G>/S<char>/W<char>
->0x142D70. That unlinks 10 units (19.3 KB) that emit 14 B W<G> COMDATs, listed
in `df20-funclet-naming-20261021`. After the rename, resume from
a9d0sig-true-naming (0.9986) and work only the return-2 S/W choice.

Scratch: `build/b3df20/` (sc.py ledger scorer, sct.py true scorer, runt.sh,
h3gen.py/h4gen.py, s3/gen9.py, gen10.py).
