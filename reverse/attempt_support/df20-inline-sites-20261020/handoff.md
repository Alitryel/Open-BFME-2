# 0x0000DF20 money_put<wchar_t>::do_put(string): per-site inline levels

Bank: `reverse/attempts/0x0000df20.cpp`, fit 0.8114 at 2576 B (the earlier bank
was 0.7262 at 2528 B). Retail is 2610 B, frame `sub esp,0x118`. Ours is
`0x110`, 8 B short. Toolchain: MSVC 7.1 via `./build.sh`. Flags are those of
the stlport siblings: `/EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC`.

## Retail destructor sites (target evidence)

Main flow:

| Site | Retail form |
|---|---|
| grouping temps (narrow) +0x17D/+0x1A8 | inline free |
| curr_symbol temps +0x236/+0x259 | call 0x00142D70 |
| no-digits return, curr_sym +0x28C | call 0x00142D70, then `jmp +0x841` (shared tail: grouping free, locale, ret) |
| sign temps +0x375/+0x398/+0x3BB/+0x3D7 | call 0x0000B3C0 |
| no-value return +0x41E (sign), +0x42F (curr_sym) | call 0x0000B3C0, then `jmp +0x841` |
| end of function +0x807/+0x820/+0x839/+0x852 | inline free (new_digits, sign, curr_sym, grouping) |

The `__copy` helper behaves the same way: the currency and zero-fraction
copies call 0x0000E9C0, while the fractional and sign-tail copies are inline
loops. For every callee, early sites stay calls and late sites inline.

Funclets (0x0075BB60, 327 B):

- grouping (partial and full): 0x00142D70
- wide temps and named full strings: 0x0000B3C0
- new_digits: partial → 0x00142D70, full → 0x0000B3C0

The funclets are a separate row, so the main-body gate does not see them.

Ledger names:

- 0x00142D70: `~basic_string<wchar_t>`, `~basic_string<char>`, `_M_deallocate_block<char/wchar_t>`
- 0x0000B3C0: `~_String_base<char/wchar_t>`

So the funclet targets above are inverted against normal C++ semantics: partial
state → base dtor, full state → string dtor. Either these names are swapped in
this unit's view, or the funclets come from something else. This is unresolved
and changes no main-body relocation.

## Proven compiler facts (toys in a scratch dir, reproducible)

- `#pragma inline_depth(0)` inside a function body acts per call site. Calls
  emitted while depth 0 is in effect are not inlined; other sites are unaffected.
- A nonzero `inline_depth` is function-level. It is taken from the pragma state
  at the function's closing brace, even if the pragma comes after the last
  `return`. A per-site depth of 1 or 2 has no effect. A pragma alone therefore
  cannot inline `~basic_string` and still call `~_String_base` at chosen sites.
- With 8 extra inlined blocks, the c2 inline budget was never exhausted in this
  unit. Explicit instantiation of the wide `_String_base`/`basic_string` does
  not change inlining.

## Trials on this bank

| Trial | Result |
|---|---|
| Depth 0 around the curr_sym initialisation | the two temp sites call `~basic_string` (0x00142D70) at retail's offsets ✓ |
| Depth 0 around the no-digits return | curr_sym ✓, but grouping's `~basic_string<char>` becomes a call too, so the return no longer tail-merges into +0x841 |
| Opaque explicit-specialisation declaration of the wide `~_String_base` (lever from `stlport_wide_num_put_bool.cpp`) | sign temps and the no-value return call 0x0000B3C0 ✓ (21 B late), but the three wide end-of-function frees also become calls ✗. Fit 0.8108 → 0.8114. |

## What is left

The same local (`curr_sym`) needs three inline levels by exit:

- whole call at the no-digits return
- base call at the no-value return
- inline at the end

The grouping destructor at the no-digits return must stay inline so that the
return tail-merges.

No visibility lever reproduces this, because visibility is per function, and no
pragma lever does either: only depth 0 is per site.

Families tried:

- control flow: return placement and the tail merge
- lifetime: the `string_type` locals and temps
- types and layout: the proxy and base views (earlier handoffs)
- callee visibility: opaque base and opaque copy constructor
- compiler settings: inline_depth per site and per function

Budget order is refuted by a toy. Setup: `u4.cpp`-style, four wstring blocks,
64 calls of a `__forceinline` helper with 200 dead switch arms, run on a
constant. Results:

- calls placed at the start: every string site keeps a whole `~basic_string`
  call;
- calls placed before the final return: early sites inline and the final-exit
  sites become calls.

c2 therefore exhausts its budget in forward order, and whole sites drop out (no
partial base call appeared). Retail's late-inline pattern is the opposite, so
budget exhaustion does not explain it.

Untried angles:

- whether the 0x00142D70/0x0000B3C0 names are swapped in this unit's view.
  The funclets suggest it. A rename would move ledger rows that other units
  depend on, so it needs its own evidence.
- some other source construct where the end-of-function frees do not come from
  `~basic_string`, e.g. explicit releases in a wrapper, as in the
  `_BoolNameStorage` model of `stlport_wide_num_put_bool.cpp`.
