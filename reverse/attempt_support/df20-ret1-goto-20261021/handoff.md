# 0xDF20 wide `money_put::do_put` (string) — ret1 / cost-carrier round

Seat yasinschroeder-claudeb3, 2026-10-21, model claude-opus-5-5.
Bank: `reverse/attempts/0x0000df20.cpp`, fit 0.9127 on the
`build/b3df20` scorer (`permute.fitness`, aligned diff nd 185), 2610 B
(= retail), frame 0x118. The previous bank (29a0ce15eb) scores 0.8798 on
the same scorer (0.9067 on the claude3 scorer), 2562 B.

## Names used below

- W = `basic_string<wchar_t>::~basic_string`, S = `_String_base<wchar_t>::~_String_base`,
  D = `_M_deallocate_block`.
- Retail F = 0x00142D70 (14 B frameless `mov eax,[ecx]; test; je; push; call free`):
  the ledger rows W there, with D pinned to the same folded body.
- Retail B = 0x0000B3C0 (63 B, EH frame, state 0 across `free`): S is rowed there.

## Retail destructor site map (offsets from 0xDF20)

```
236 259  currency temporaries   F   (conditional, flags bl&8 / bl&4)
28c      empty-digits return     F   then jmp 0x841 (shared narrow/locale tail)
375 398 3bb 3d7  sign temporaries B
41e 42f  second early return     B   (sign, curr_sym)
final    teardown                inline (free)
```

Bank: `W@236 W@259 S@28c S@375 S@398 S@3bb S@3d7 S@41e S@42f`; only the
target at +0x28c differs.

## What landed this round

1. Plain `return __s;` at the empty-digits exit (r1) instead of the earlier
   depth-0 goto. With the carrier below, the bank reaches retail length.
2. **Frame-neutral cost carrier**: in a TU-local explicit specialisation of
   the wide `~_String_base`, nine calls
   `((_MoneyPhantom *)this)->_MoneyPhantom::~_MoneyPhantom();` (a struct
   whose only member has a destructor guarded by an enum constant 0).
   They compile to nothing but add inline cost.
   - Count ≥ 9: S is outlined at every cold site and inline in the final
     teardown, and the frame stays 0x118.
   - Count < 9 behaves like no carrier.
   - Unqualified forms (`p->~_MoneyPhantom()`, a temporary) drop the frame.
   - Carriers that are not destructor calls are inert.
3. Additive cost: a carriers in S plus b in D outline S when a+b ≥ 9 and
   b < 9. b ≥ 9 outlines D at every cold site instead (F everywhere,
   ret2 included).

## Disproven (do not repeat)

- r0 goto + carrier: W lands at +0x27e, the wrong position.
- r2 (depth 0 around the ret1 `return`) + carrier: W@28c, but the narrow and
  locale destructors at ret1 are outlined too and the tail merge breaks (2642 B).
- Per-site split by carrier combination: none. Every cold site makes the
  same decision. Per-site W comes only from depth-0 pragmas: cp1 on the
  currency declaration (kept), sp1 on the sign declaration (worse with the
  carrier).
- Reverse-order caller budget (gen20): k = 1..32 phantom carrier statements
  placed directly in `do_put` (before ret1, after ret1, before the final
  return) × cp0/cp1. All 60 variants are byte-identical to their cp baseline,
  so no caller-wide inline budget explains the per-site pattern.
- Slot factorial (gen19, 128 variants, all identical at nd 185):
  - the `_MoneySignPolicy` local placed at the top, after the negation, in
    the inner block, or as a temporary;
  - the external-copy tag and the copy-specialisation tag as a local vs a
    temporary;
  - `bool __is_negative = ...` as a single declaration;
  - the inner block removed;
  - the space-count for loop without braces, with a shared `int __i`.

## Remaining residue (bank)

1. +0x28c calls S where retail calls F. Retail's pattern is monotone:
   earlier sites are less inlined (F, then B, then inline). The same holds
   for `__copy`, which is outlined only at the symbol copy and the
   frac==0 value copy.
2. Byte temporaries: ours puts the new_digits allocator/tag temps (439/452)
   and the symbol-copy tag (6f8) in one unit at esp+0x13, with is_negative
   alone at 0x1b. Retail packs the allocator tag into 0x2e (next to the
   `__generate_curr` byte at 0x2f), the symbol-copy tag into is_negative's
   dead byte 0x17, and the external-copy tag into 0x4f. Consequences:
   - slots 0x14..0x4b sit 4 bytes high;
   - grouping/sign swap 0x5c/0x50 (retail 0x50/0x5c);
   - the fill_n copies at 6ac/902 swap 0x94/0x74 (retail 0x74/0x94).
3. The disp8/disp32 difference that follows moves alignment pads
   (ours `mov edi,edi` at 6be; retail `jmp 0x910; lea esp,[esp]; nop` at 906).

## Untried angles (next session)

- Read `__digits.size()` once before the currency `?:` (local `size_t`), so
  ret1 tests a register value.
- Declaration order of `__grouping` relative to `__curr_sym` and `__sign`
  (the 0x50/0x5c swap). Note gen19 showed the tag placements are inert.
- Fill_n call-site forms at 6ac vs 902 (the 0x74/0x94 swap).
- A helper split: STLport 4.5.3 `_monetary.c` keeps one body; check the
  WorldBuilder twin frame for locals that the bank does not have.
- Whether the F sites are D (W→S inlined, D outlined) rather than W. Both
  fold to F. A D-carrier with b ≥ 9 gives F at every cold site, so it would
  need the same per-site split as W.

Scratch generators (untracked): `build/b3df20/gen16.py`–`gen20.py`,
`odis.py` (our disassembly), `calls.py`, `slots.py`.
