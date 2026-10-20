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

## Merge note (claudeb4, 2026-10-21)

Both parallel banks rescored with one scorer (`build/m12190/score.py`, fit =
.5 mnemonic + .3 instruction + .2 byte): claude3 r25 (commit e7ee3c9b6c) fit
0.9000, nd 80, 2860 B, D=10 F=9; claudeb4 `o_g` fit 0.9766, nd 21, 2820 B,
D=13 F=7 (retail D=13 F=7). The bank keeps `o_g`; r25's per-site
inline_depth(0) findings stay below for the remaining residue.

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

## Round claudeb4 (2026-10-20, later): bank fit 0.9766, nd 21

The new bank (`reverse/attempts/0x00012190.cpp`, scratch name `o_g`) reproduces
retail's full destruction map. With states, the call sequence is
`D5 D4 Da D9 D10 Df Df F15 F14 F14 D14 D14 D14 F-1 D D D F F F`, where D is the
wide dtor 0xB3C0 and F is free 0x30830. It equals retail.

### What produces the map

- **Leaks-check shim.** `template <> inline allocator<unsigned short>::~allocator()
  { if (_MONEY_LEAKS_CHECK) free(0); }` before `<locale>`, with `free` declared
  with C++ linkage (`_INC_STDLIB` suppressed).
- **Why it works.** The shim gives the inlinee a proxy EH state. c2 then outlines
  the ternary temps, the `__cs` scope end and both early-exit groups, and inlines
  only the final exit. This split is structural, not budget: with four final-exit
  locals (`ex/e1`), all four are inlined and the early exits stay out of line.
- **No proxy state, no split.** Without a proxy state everything inlines (D=0):
  - a vendor or trivial allocator;
  - `extern "C"` free, `free(...) throw()` or `__declspec(nothrow)` free;
  - a leaks call to another C++ function while free is `extern "C"`;
  - shims on `deallocate`, `_M_deallocate_block` or `~_String_base` (dt/v0..v8).
- **Noinline `~_String_base`.** It gives D=13 F=5, fit 0.9147.

### Residue

1. **Tag store and bool slot.** `_M_assign_dispatch<wchar_t*>` (A, 0x130A0) is
   visible, so c2 knows A ignores its `__false_type` tag. It drops retail's
   `mov byte [esp+0x1e],0` and shifts the bool slot.
   - Diagnostic `q_diag`: a defined specialization calling an opaque
     `__tag_sink(&t)` fixes both (fit 0.9847, nd 16). That is not a landable body.
   - Every decl-only member-template specialization form ICEs (C1001).
2. **Proxy EH states.** The three inlined final-exit dtors carry proxy states
   0x16/0x17/0x18 (parents 9/4/0, proxies at ebp-0xb4/-0x98/-0xa4). Retail stores
   the parent states 9/4/0 instead. States 0..0x15 equal retail's in parents and
   object offsets.
3. **Load order.** `mov edx,[esp+0xec]` is scheduled before the `[esi+4]` store
   at 0x12bf3; retail loads it after.

### Retail facts

- **D's own frame.** D (0xB3C0) has state 0, whose funclet is `[ebp-0x10]+8` →
  0x69E440, a 1-byte `ret` (the folded empty `~_STLP_alloc_proxy`). So retail's
  string dtor did carry a proxy state, but its inline copies in do_get do not.
- **Funclet targets.** Wide funclets jump to D, narrow ones to 0x542D70.

### Refuted this round (no change from o_g/q_diag)

- **Compile order:** a noinline helper before or after do_get that does any of:
  - destroys a wide string or `_String_base`;
  - explicitly destroys `_STLP_alloc_proxy`;
  - holds a proxy or an allocator across a throwing call;
  - passes a temporary wide string.
- **Shim tweaks:** a `throw()` exception specification on the shim dtor.
- **Explicit locals:** an extra explicit local (`ex/e1`): fit 0.72, because the
  extra dtor goes out of line at the early exits.

### Landing caveat

The 13 calls name `??1?$basic_string@G...`. Its symbol-map candidates are
0x142D70 (an ICF twin row), not 0xB3C0; `??1?$_String_base@G` is pinned at
0xB3C0 (`symbols.csv:2764`). The scratch scorer forces both names to 0xB3C0. An
exact body may still need the ledger to resolve `~basic_string<G>` to 0xB3C0.
