# 0x0000DF20 wide money_put::do_put (string), round claude3 (2026-10-21)

Continues `../df20-allocator-eh-20261021/handoff.md`. New bank
`reverse/attempts/0x0000df20.cpp`: 2562 B, frame 0x118, fit 0.9067, nd 166.
On the same scorer (`build/claude3/mdf20/sc.py`, fit = .5 mnemonic + .3
instruction + .2 byte, call names learned by alignment) the previous bank
scores 0.8820, nd 189. Its recorded 0.8114 came from another scorer.

## Retail cleanup map (target facts)

Read with `smap.py` (dtor call, `lea ecx` slot, EH state stored before it):

| site | slot / state | retail |
|---|---|---|
| currency temporaries | 0x108/b, 0xf0/a | call 0x00142D70 |
| return 1 (`__digits.size() == 0`) | 0x68/5 | call 0x00142D70, then `jmp e761` |
| sign temporaries | 0xcc/14, 0xe4/13, 0xfc/12, 0x114/11 | call 0x0000B3C0 |
| return 2 (`__cp == __digits_first`) | 0x5c/a, 0x68/5 | call 0x0000B3C0 twice, then `jmp e761` |
| final exit | 0x9c, 0x5c, 0x68 | inline frees |

`e761` is the shared tail: inline narrow `__grouping` free plus inline
`~locale`. 0x00142D70 is the frameless 14 B body, 0x0000B3C0 the framed 63 B
one.

## New bank

The bank's opaque `~_String_base<wchar_t>` declaration is gone. Pragmas are
`inline_depth(0)` on the currency and sign declarations only. Map: `W@0x108/b
W@0xf0/a W@0xcc/14 W@0xe4/13 W@0xfc/12 W@0x114/11`, final teardown inline,
frame 0x118. Every temporary sits at retail's slot and state.

Residue:
- Both early returns tail-merge into the inline final teardown. Retail
  outlines the wide string destructor there and shares only the narrow and
  locale tail.
- The sign temporaries call `??1?$basic_string@G` (W). The ledger resolves W to
  0x00142D70 (row "ICF twin of the owner row"); retail calls 0x0000B3C0. The
  funclet evidence in `../wide-money-get-string-12190-20261021/handoff.md`
  says W really is 0x0000B3C0. If that row moves, these four calls become
  right and the currency ones wrong. Do not pin this away.

## Phantom-cost lever: inline-budget model (measured, not landable here)

Grids `build/claude3/mdf20/g1`..`g7` (scratch, not tracked) varied phantom
counts, which are empty member-dtor calls as in the 0x12190 recipe: `sb` in
`~_String_base<wchar_t>`, `db` in `_M_deallocate_block`, `bs` in
`~basic_string<wchar_t>`. They also varied Nop and Leak fillers and the four
per-site depths.
- Without pragmas, every cold site makes the same decision. The flip happens
  between sb 8 and 9 (db 0), or sb 10 and 11 (db 9). Nothing in between gives
  retail's mix of currency=D and sign=S.
- The final exit loses inlines first (`...FFSF`, `...FSSF`), so the budget is
  consumed in forward order. With a forward budget, retail's pattern is
  impossible: S inlined at the currency sites, outlined at the sign sites, and
  inlined again in full at the final exit.
- Depth 0 is per site and outlines the outermost callee (W). At a return it
  also outlines the narrow destructor and `~locale` (W w L), which breaks the
  shared tail. Depth 1 or more is a no-op.
- Best phantom map, `sb=10 db=9 dep=n,n,0,n`:
  `D@0x100/b D@0xe8/a D@0x68 W@0xc4/14..W@0x10c/11 D@0x5c D@0x68`, final
  inline. That is retail's map under the funclet naming, except return 2 is D D.
- **Any inlined phantom or filler costs the frame.** It drops to 0x110: two
  8-byte `ostreambuf_iterator` copies share a slot (retail 0x94 and 0x74).
  Every slot of 0x9c and above then shifts by 8, which costs nd more than any
  map gain. Phantom-free variants all keep 0x118. Phantoms are therefore out
  for this body.
- `/Ob1`: same maps, `~locale` outlined, frame 0x110.
- `permute.py --flags`: nothing closed.

## Next angles

1. Find a cost lever that adds no inline-scope symbols, so the frame survives,
   and makes the early returns outline the wide destructor alone.
2. Settle the W naming (0x00142D70 vs 0x0000B3C0) as its own ledger task
   first. It decides whether the currency or the sign sites are the ones to fix.
