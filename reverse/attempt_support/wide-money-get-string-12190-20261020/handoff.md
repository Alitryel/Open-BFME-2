# 0x00012190 wide money_get::do_get (string), round claude3 (2026-10-20)

Continues `wide-money-get-string-12190-20261019/handoff.md`. The new bank,
`reverse/attempts/0x00012190.cpp`, is fit 0.845 by the region scorer (the old
bank scores 0.8075 on the same scorer), with 182 differing instructions.

## Retail destruction map (target facts)

- **Wide strings:** `~_String_base<wchar_t>` (ICF-folded to 0xB3C0) is called
  out of line at 13 sites:
  - ternary temps of `__ns`/`__ps`/`__cs`, 2 each;
  - `__cs` at its scope end;
  - early group 1 at 0x12a15: `__buf`@esp+28, `__ps`@44 and `__ns`@38 (states
    9, 4 and 0), then inline `~locale` and a `jmp` to the 0x12c65 epilogue;
  - early group 2 at 0x12a8e: the value case after the inline narrow free, with
    a `jmp` to 0x12c51.
- **Final exit (0x12c0c..0x12c49):** frees the same three named strings inline.
- **Narrow strings:** freed inline everywhere (4 sites).
- **`~locale`:** always inline (`call [eax+8]`, 8 sites).
- **Prologue and `__i`:** the prologue is `push edi; xor edi,edi;
  mov [esp+0xc],edi`, and `__i` lives in edi.

## Candidates

| variant | fit | nd | B3C0 calls | free calls | note |
|---|---|---|---|---|---|
| v2 (banked) | 0.845 | 182 | 7 | 10 | `_MoneyNameStorage` owners, inline free; edi prologue ok; regions [1,22,71,40,34,2,12] |
| n6 | 0.829 | 182 | 13 | 4 | natural vendor body plus decl-only wide dtor before do_get; final exit merged into calls; loses the edi prologue and `__i` in edi; middle regions much better [19,24,10] |
| n1 | 0.782 | 214 | 0 | 20 | natural vendor body, all inline |

v2 also outlines the non-inline `locale::~locale` at two early exits
(0x12a58, 0x12be1). Retail does the reverse: the wide dtor is called at the
early exits and `~locale` stays inline. That is the only per-site split we have
seen c2 produce.

## Refuted (no change to the dtor call map)

- **Inliner budget:**
  - dead or live pads in do_get up to 9832 B;
  - dead IL inside the wide dtor body (1..24 statements; output identical to n1).
- **Wide dtor placement:**
  - defined after do_get (inline, plain or `__forceinline`);
  - non-inline, or a `_M_deallocate_block` specialization before do_get.
- **Explicit instantiation:** of `_String_base<wchar_t>`, `basic_string<wchar_t>`
  or `_STLP_alloc_proxy<wchar_t*,...>`.
- **Sibling TU:** do_get instantiated through the long-double sibling TU's
  prelude with the string do_get unsuppressed: fit 0.60..0.63.
- **Earlier rounds:**
  - flags `/Ob1 /Ob2 /Os /O1 /Og-`;
  - `inline_depth(1..8)`, hidden `/d2inl*` switches;
  - `extern template`.

## Untried leads

- Make n6 keep v2's prologue. n6's middle regions are the best seen; its loss
  is the `__i` register and the merged final exit. That points to the final-exit
  frees being a different object kind (for example a by-value
  `_MoneyNameStorage` copy whose dtor is inline) from the early-exit ones (named
  `basic_string` with the decl-only dtor).
- Mix types per name: `__ns`/`__ps` as `basic_string` (outlined dtor) and
  `__buf` as storage, or the reverse, and check which group each name joins.

## Round 4 (claude3, 2026-10-21): per-site inline_depth(0)

Bank replaced by `reverse/attempts/0x00012190.cpp` r25 (fit 0.898, nd 109; v2 was
0.845, nd 182). It starts from the natural vendor body, not v2.

- `#pragma inline_depth(0)` / `#pragma inline_depth()` *inside* do_get acts per
  statement:
  - around a declaration with a ternary initializer, the temp dtors go out of line;
  - around the symbol case's `break;`, the `__cs` scope-end dtor goes out of line;
  - around `return __s;`, every dtor at that return goes out of line, `~locale`
    included; `__forceinline` does not survive it.
- Per-site depth 1..3 has no effect.
- Return subsets r01..r31 (bit j = j-th loop `return __s;`): {0,3,4} best fit
  (0.898); {2} best nd (97).
- **Residue:**
  - depth-0 sites call `??1basic_string<G>` (resolves 0x142D70, the no-EH twin)
    where retail calls `~_String_base<G>` 0xB3C0. Retail inlined `~basic_string`
    and outlined only its base dtor, so it is not a depth-0 outline;
  - early exits outline `~locale` (retail keeps it inline);
  - retail inlines `__get_string` at all three sites with `const G*`.
- **Refuted this round:**
  - wide `~basic_string` specialization through the generic `_Destroy` or
    `__destroy_aux(__false_type)` (placed before `<locale>`): bytes identical to n1;
  - a non-inline explicit specialization of `~_String_base<wchar_t>` before
    `<locale>`: still inlined everywhere (20 `free` calls). MSVC 7.1 treats it as
    inline because the primary is defined in class. Only the decl-only form
    outlines it, and that is function-wide.
- **Retail map:** narrow do_get 0x11230 inlines all its string dtors (13 direct
  `free` calls). The wide one calls B3C0 13 times and `free` 7 times, so the split
  is wide-only.
- **Toy trials (shared with df20 money_put; `build/claude3/toy/` scratch, not tracked):**
  - first instantiating the wide dtor inside the function, versus before it,
    changes nothing;
  - 14 sequential objects with early returns, with a trivial or an EH-bearing
    (allocator-member) base dtor: every dtor site is inlined, while the third
    out-of-line-sized ctor is outlined in forward order;
  - 10 STLport wide strings with early returns: every dtor site is inlined.

  So no budget or instantiation-order effect reproduces retail's "early sites
  outlined, final teardown inline" split outside the real body.
