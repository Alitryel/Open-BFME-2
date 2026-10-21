# 0xDF20 money_put::do_put (wide): late-fold W carriers vs. format-loop unroll

Session 2026-10-21, model=claude-opus-5-5. The bank `reverse/attempts/0x0000df20.cpp`
is unchanged (0.9993 under ledger naming).
Earlier handoffs: `df20-funclet-naming-20261021` (true naming), `df20-inline-budget-20261021`
(inliner thresholds), `df20-frame-packer-20261021`.

## Base

`a9` = bank with the `#pragma inline_depth(0)` moved from before `__curr_sym`
(bank line 213) to just before the `__sign` statement (depth(255) back after it).
Under TRUE naming (S/D = 0x142D70, W = 0xB3C0; scorer `build/b3df20/sct.py -m`)
a9 = 0.9986, nd 2. The only residue is S where retail calls W at 41e/42f.
Blanking a9's sign pragmas (`v0_a9s0`) gives 0.9958, len 2610, unrolled, map all S.

## New compiler fact

Any branch the optimizer folds *late* stops the 4-iteration unroll of
`for (int __i = 0; __i < 4; ++__i) if (__format.field[__i] == (char) money_base::space) ++__length;`.
The rolled loop gives 2613 B, one extra stack slot (most offsets +4) and nd ~258.

- Late folds that break it: `if (x != x)`, `if (&local == 0)`, and `this == 0` inside an inlined W.
- Folds that keep the unroll: front-end or const-prop folds (`if(0)`, `sizeof`, `int z=0; if(z)`,
  self-assign, `+= 0`) and real branches.
- Removing real code does not restore the unroll, so this is not a size budget.
- Retail's unrolled shape (offset 0x584): `mov eax,[eax]; cmp al,1; mov [esp+0x44],eax; jne; inc esi; cmp ah,1; ... shr eax,0x10; cmp al,1; ... cmp ah,1`.

## Carrier result (evidence: `ex_n6_k9_s0.cpp.txt`, generator `gen.py.txt`)

This variant adds a W specialisation with `if (this == 0) exit(1);` x6 before
`_Destroy(_M_start, _M_finish + 1)`, keeps 9 S phantoms and drops the sign pragmas.
Its destructor map is exactly retail's under true naming:
S@236 S@259 S@28c W@375 W@398 W@3bb W@3d7 W@41e W@42f.
But fit is 0.8652, len 2613, nd 258, because the late fold rolls the format loop.

These carriers give the same map with the same loss:
- `(void*)this == (void*)&global` x6;
- `this == &_M_end_of_storage` x3;
- `&_M_finish == 0` x3;
- double abort x5;
- volatile store x8, `this < 16` and `exit` x7.

Other carriers fail differently:
- `free(0)` adds EH, so W is outlined everywhere;
- a global store (`gs`/`gv`) changes nothing in the map.

## Disproven this session (do not repeat)

- Extern template declarations of S/P/A/B: inert.
- Natural STLport explicit class instantiation: 0.5471.
- Explicit specialisation vs instantiation: identical.
- Profiles: vc71-ddk-4035 is identical to RTM; vc71-sp1 is worse.
- /Ob1 on bank, a9 and w0 (with or without pragmas, with or without an inline `~locale`): no gain.
- Format-loop rewrites on the carrier variant:
  - `unsigned i` and `while`: still rolled;
  - pointer loop: len 2610 and the right map, but nd 120 because slots still differ
    (0x14 vs 0x10, 0x4c vs 0x28, 0x30 vs 0x20);
  - manual unroll (four `if` statements): nd 156.
- So the late fold perturbs slot allocation beyond the loop itself.

## Open leads

1. Find a W cost carrier that the inliner counts but that folds before the unroll
   pass (const-prop or front-end fold that still costs inliner units). `_MoneyPhantom`
   in W was covered by earlier grids (W never outlined), so it needs a different
   cost class. Tested at the end of this session (`gen7`, n = 2/6/10/16 on a9s0):
   - `if (_MONEY_LEAKS_CHECK) exit(1)`: inert (0.9958 at every n), a front-end fold
     with no inliner cost;
   - `((_MoneyPhantom*)this)->~_MoneyPhantom()` and `{ _MoneyLeak l; }` in W:
     0.9315, 2626 B at every n, an EH or shape change rather than a cost effect.
   Still untried: a `static const bool` or template-parameter constant guarding a
   non-inlinable call.
2. Alternatively, find why a late-folded block blocks the unroller (block count
   before folding?) and find a source shape that unrolls regardless.
3. Landing under true naming needs the 8-10-unit ledger reconciliation described in
   `df20-funclet-naming-20261021/handoff.md` in any case.
