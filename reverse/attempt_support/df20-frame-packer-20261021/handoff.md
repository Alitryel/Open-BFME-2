# 0xDF20 wide `money_put::do_put` (string): frame-packer round

Seat yasinschroeder-claudeb3, 2026-10-21, model claude-opus-5-5. The previous
round's handoff is `../df20-ret1-goto-20261021/handoff.md`.

The new bank `reverse/attempts/0x0000df20.cpp` has fit **0.9272**, aligned diff
nd 144, 2610 B (= retail), frame 0x118. The previous bank had 0.9127 (nd 185)
on the same scorer, `build/b3df20/sc.py` (`permute.fitness`).

## What changed in the bank

The new_digits constructor no longer calls the 3-arg `_M_range_initialize` from
inside the `do_put` frame. Two TU-local depth-0 forceinline specialisations
replace it:

```
template <> template <> __forceinline void basic_string<wchar_t>::_M_range_initialize(const wchar_t* f, const wchar_t* l) { _M_range_initialize(f, l, forward_iterator_tag()); }
template <> template <> __forceinline basic_string<wchar_t>::basic_string(const wchar_t* first,const wchar_t* last,const allocator<wchar_t>& a) : _String_base<...>(a) { _M_range_initialize(first,last); }
```

The `forward_iterator_tag` temporary now lives in the out-of-line 2-arg
function, so it no longer takes a byte in the `do_put` frame. The cost is a
structural error: at +0x452 ours calls the 2-arg overload with no tag push.
Retail calls the 3-arg 0xBF90 with `lea ecx,[esp+0x2e]; push ecx`.

`_MoneySignPolicy : random_access_iterator_tag { bool negative; }` now also
carries the sign flag in place of `bool __is_negative`. This is a slot hack:
- it reproduces retail's sharing of is_negative's dword with the symbol-copy tag;
- without it, the 2-arg base drops to 0.8922 (g40).

The original `_monetary.c` uses a plain `bool __is_negative`.

## Remaining residue (bank, `build/b3df20/dd.py`)

- +0x452: 2-arg out-of-line call instead of the 3-arg 0xBF90 with the tag at 0x2e.
- Byte slots:
  - ours: alloc temp 0x2b, ext tag shares it, gen_curr at 0x37;
  - retail: alloc/fwd tag 0x2e, gen_curr 0x2f, ext tag 0x4f.
- Dword permutations:
  - 0x28/0x30 swapped;
  - 0x44/0x48;
  - 0x50/0x5c (grouping/sign);
  - locale at 0x44 (retail 0x3c).
- Pads at 5dc/6be.
- +0x481: `xor edx,edx; mov dl,[eax]` where retail has `movsx eax,byte ptr [eax]`.
- +0x28c: dtor target (previous handoff, unchanged).

## Disproven this round (do not repeat)

- g34/g35: ctor and 2-arg specialisation × depth 0/1/2/255 × forceinline/inline.
  The best is `arfF` (the bank).
- g36: inline_depth 2..4 on the ctor with the natural chain (3-arg call)
  reproduces the old bank byte-for-byte. Whenever the fwd tag is a temp in the
  do_put frame, the old layout results.
- g37: tag form inside the ctor is inert:
  - named fwd/rai, temp rai, `iterator_traits<const wchar_t*>::iterator_category()`;
  - const-ref bound, block-scoped.
  Exceptions that are not usable:
  - a static tag: 0.9267, but structurally wrong (absolute address push);
  - `input_iterator_tag`: 0.9120.
- g38: the ext copy routed through `__copy_aux`/`__copy_ptrs`/`__false_type` at
  depth 0..3 keeps `__copy_aux` out of line (worse). The iterator_traits
  category at depth ≥2 inlines `__copy` (0.83).
- g39: a named ext tag at 7 do_put positions × 2 helper signatures is inert on
  both bases.
- g40: dropping the policy-sign hack on the 2-arg base gives 0.8922.
- `_STLP_ITERATOR_CATEGORY` outside a template is C2899. The explicit
  specialisation of the 3-arg member template hits C1001 (ICE), which is why the
  2-arg overload was specialised instead.
- Toy probes (`build/b3df20/toy6`), an EH-framed function with derived empty tags:
  - the alloc-like and fwd temps merge;
  - the first in-loop tag reuses that slot;
  - the second in-loop tag gets its own slot, which is retail's pattern.
  None of these changes that layout:
  - forceinline helper wrappers (named, temp, depth 0, nested const-ref);
  - distinct overloads;
  - an 8-byte by-value iterator returned through `cp(...)`.
  So the toy does not reproduce why do_put merges the sym/ext/alloc tags. It is
  not caused by helper wrapping or by the iterator ABI.

- permute.py on the old bank (1248 trials) reached 0.9258, but only through
  semantics-breaking edits: it moved `__is_negative = ...` into the
  `if (__is_negative)` body and changed `*__s++` to `*++__s`. Its harmless edits
  are inert on the new bank: all 64 variants of g41 score 0.9272. Those edits
  are `/Op`, `__grouping[0] = __grouping[0] + __frac_digits`, `const` on width
  and `__ffield`, and the comparisons `4 > __i` and `0 != __frac_digits`.

## Second round, same day (g42-g47, all disproven)

- g42: route the ext and sym copies through a depth-0
  `__money_copy_aux(..., __false_type()/_BothPtrType::_Ret())` with a temp or
  named category tag, at helper depths 0, 1 and 2. Depth 0 or 1 leaves the aux
  call out of line (0.9243); depth 2 gives a 0x110 frame (0.8612); routing the
  sym copy through aux gives 0.8861 or 0.8922.
- g43 copy specialisation: a temp rai tag, an `iterator_traits` temp and the
  natural `__copy_aux` chain with a forceinline `__copy_aux` specialisation
  (variant c3) are all byte-identical to the bank, so c3 is an equivalent and
  more natural spelling. Calling through `_BothPtrType` without the aux
  specialisation, dropping the specialisation, or keeping only the aux
  specialisation all score 0.73-0.74.
- g44 declaration reorders (frac before grouping, sep after grouping, point
  after sep, width later, gen_curr later): all equal or worse. The current order
  is best.
- g45: removing the artificial block around `__curr_sym`, hoisting
  `__sign_policy`, and the braces of the space-count loop are all inert. The bank
  now drops the block and the braces.
- g46: `__curr_sym.begin()` without the `static_cast` is inert (adopted). A
  non-const `__sign.begin()+1` is worse (0.8618, 2613 B).
- g47 allocator lifetime: a named allocator at the top or at the use, a
  const-ref-bound temporary, `__digits.get_allocator()`. All worse (0.9001 or
  0.9161), and none reproduces retail's byte slots.

Slot-weight finding (`build/b3df20/slots.py`, push-normalised offsets): the
heavily used dwords sit lowest (0xc has 16 uses, 0x10 has 12, 0x20 has 13), so
the packer orders units by reference weight. The dword permutations
(0x28/0x30, 0x44/0x48, 0x50/0x5c) follow from a different composition of the
byte units. Ours puts alloc and the ext tag in one byte unit (0x2b) and gen_curr
alone (0x37). Retail puts {alloc 0x2e, gen_curr 0x2f} in one dword and the ext
tag alone (0x4f). The 0x17 slot is shared by liveness between is_neg and the
sym tag. Toy t7 (`build/b3df20/toy6/t7.cpp`: an allocator temp passed to a ctor
and a spilled bool) shares a byte between the forward tag and the bool by
liveness, while A, RT1 and RT2 stay distinct. The pattern is context-sensitive,
and no toy has reproduced retail's exact layout yet.

## Untried angles

- Change reference weights so gen_curr shares a dword with alloc and the ext
  tag is alone (for example, read gen_curr once more, or test it through a
  copy).
- Grow the toy towards do_put until the ext tag merges:
  - two EH-tracked strings live across the loop;
  - the `__intl ? a : b` facet selection;
  - the `switch` over `money_base::pattern` with copies in several cases.
  The first change that merges the tags names the cause.
- The natural STLport chain through `_M_initialize_dispatch(f,l,_Integral())`,
  which has a `__false_type` temporary. Earlier ctor families (see
  `df20-constructor-visibility-20261020`) covered primary vs specialised ctors,
  but not explicitly the dispatch temp's slot interaction with the 2-arg base.
- `movsx` at +0x481: the fill character is read through `char` vs
  `unsigned char` (`__grouping[0]`?). Try a `(int)(signed char)` or a plain
  `char` local.

Scratch (untracked): `build/b3df20/g34`–`g40` generators and variants,
`cur2.cpp` (= bank), `dd.py`, `odis.py`, `probe.py`, `runm.sh`, `toy6/`.

## Round g48-g58 (2026-10-21): tag packing solved, bank 0.9993

Base: g50 `2Bnna`. It is retail-structured: a depth-2 forceinline range ctor
calls the 3-arg 0xBF90, with a plain `bool __is_negative`. It scored 0.9127
(nd 185) before the fix.

**Finding: the visibility of the `__copy` callee decides the tag slots.**
- When do_put's TU has compiled `__copy<const wchar_t*, _MoneyOut, int>`
  (0xE9C0), c2 knows that the `const random_access_iterator_tag&` parameter
  does not escape. It then overlaps both out-of-line tag temporaries with the
  allocator/forward-tag byte.
- With an opaque callee, retail's exact packing appears:
  - the sym tag shares esp+0x17 with is_neg;
  - alloc and fwd sit at 0x2e, next to gen_curr at 0x2f;
  - the ext tag is alone at 0x4f.
- Controls:
  - An extern `__tuse(tag)` replacing one copy fixes that copy's tag only (g52
    u0/u1/u2).
  - A same-TU definition of the callee placed after do_put still merges (x4),
    also when it is `noinline` (x6).
  - The same definition storing `&tag` to a global does not merge (x5). So the
    analysis is a parameter escape analysis, not an ordering effect.
  - Toy `build/b3df20/toy7` reproduces it: an extern `use()` gives distinct
    slots, a TU-defined `use()` merges them.
- Spelling:
  - Declare the explicit specialisation
    `template <> _MoneyOut __copy<const wchar_t*, _MoneyOut, ptrdiff_t>(...)`
    before its first use, and do not define it.
  - Route the four inlined copies through the `long` distance instantiation
    (`__copy(first, last, result, tag, (long*)0)` in the `copy`
    specialisation): the body is identical and the mangled name is different.
  - A hand-written loop in `copy` costs 4 instructions at +0x772 (0.9953).
  - Direct `__copy(..., random_access_iterator_tag(), (ptrdiff_t*)0)` calls at
    the sym/ext sites instead of the depth-0 helpers are worse (0.8754).
  - `copy()` at the sym site is worse (0.9084).
- Why retail was opaque is open. The 0xE9C0 COMDAT is owned by
  `stlport_wide_num_put.cpp`. Retail's do_put TU apparently did not see its
  body: a separate instantiation unit, or `_STLP_NO_...` config.

**The only remaining difference is the +0x28c destructor relocation.** The
return-1 path destroys `__curr_sym`. Ours calls `~_String_base<G>` there,
which the ledger maps to 0xB3C0; retail calls 0x142D70. Every other byte and
relocation matches under the current ledger naming.

The +0x28c reloc and the destructor naming:
- Under the naming that `df20-funclet-naming-20261021` proves, the bank is the
  mirror image. Retail calls S (0x142D70) at 236/259/28c and W (0xB3C0) at
  375..42f. The bank calls W at 236/259 (the depth-0 pragma on `__curr_sym`)
  and S at 28c and 375..42f (the phantom cost on S).
- The natural retail mechanism looks like this: W is inlined at the three early
  sites with S outlined, and W is outlined at the six late sites.

Phantom grid (g53/g55-g58, curr_sym depth 0/1/2/255, return-1 depth 0/1/2/255,
kS 0..12 phantoms on S, kW 0..30 phantoms on W):
- kS <= 8: S always inlined.
- kS >= 9: S always outlined, and W never outlined, for any kW.
- kS < 9 with kW >= 1: W is outlined at exactly the six late sites (W@37c..43b,
  fit 0.9330). This is the retail budget pattern for W, but the early S stays
  inlined.
- inline_depth 1 and 2 are inert in every placement. Depth 0 at the return-1
  statement outlines W at 28c, but also the narrow grouping and the locale, so
  the tail is not shared (0.9349).
- No grid point gives early "W inlined, S outlined" together with late "W
  outlined".

Next steps:
1. Ledger world (the gate today): only 28c has to call W<G>.
2. Corrected-naming world: needs the ledger reconciliation listed in
   `df20-funclet-naming-20261021` (about 8 units), then a source that outlines
   S under an inlined W early and outlines W late. Try S with a real EH-framed
   body, as retail's own 0xB3C0 shape suggests for its framed destructor.

## Session 2026-10-21 (late): g69-g73 and inliner toys (bank still 0.9993)

All of these trials score at or below the bank. The only residue is still the
+0x28c reloc: the bank calls S (ledger 0xB3C0), where retail calls F (0x142D70).

Disproven trials (do not repeat):
- g69: a goto at return 1, which also repeats the earlier ret1-goto handoff.
  W is outlined at 27e and the result stores move after the call (0.9949).
- g70: a forceinline locale/narrow chain under a depth-0 return 1 (0.9349).
  The tail is still not shared.
- g71: `#pragma inline_depth(0)` placed at p1-p8 around return 1 and
  `__curr_sym`. inline_depth is sampled between `return` and `;`, and every
  destructor run at one return shares that depth. No placement separates
  curr_sym from the locale and grouping.
- g72: a forceinline helper that splits out curr_sym. C4714: a forceinline
  helper that has EH locals and returns a class by value is never inlined.
  Helpers that return void or have no EH locals do inline, but they change
  the frame.
- g73: `__curr_sym` as `const string_type&` or `const string_type`. Byte-
  identical to the bank. Without the depth-0 pragma it scores 0.9979.
- `__forceinline` never overrides depth 0.

Inliner facts from the toy8 toys (C++ linkage unless noted):
- Top-level W at a return is graded by a binary frequency class. A site
  guarded by a single `if` is warm (W inlined). A site nested under two `if`s
  is cold (W outlined). The condition form does not matter.
- Nested D and S decisions are uniform per carrier budget: D is outlined at
  b>=9 phantoms, S at a+b>=9, except inside loops, where the final site is hot.
- An early return makes the code after it colder.
- `extern "C"` toys inline differently (W is outlined everywhere), so toys
  must use C++ linkage.

Conclusion: in the ledger naming (28c mapped to F, S late) no return-statement
mechanism outlines only curr_sym and keeps the result stores first. The
remaining paths are:
1. The true-naming reconciliation in `df20-funclet-naming-20261021`
   (F=S, B=W). Under that naming the natural toy V3 a9 w1 reproduces retail.
   It is a class-level pass over the wide basic_string views in about 10
   units (19.3 KB of link cost), not a per-body change.
2. Untried: make only the return-1 site cold (a nested two-condition class)
   so that natural W grading outlines W there alone. This is unlikely, since
   retail's source has a single `if`, but it is cheap to test with the
   toy8/sm.sh harness.

## Session 2026-10-21 (evening): h1-h3 grids, frequency explanation (bank still 0.9993)

Scratch: `build/b3df20/h1/gen.py` (return-1 forms), `h2/` (kS x kD x curr_sym
depth), `h3gen.py` (kS in {0,3,6,8,9}, kD in {0,4,8,9,12}, kW in {0,1,2,4,8}). The
phantoms sit in the wide S, D (`_M_deallocate_block`) and W specialisations.

Disproven (do not repeat):
- h1, return-1 spelling. These are inert, with the same map as the bank:
  - nested constant ifs (`if(true)`, `if(1)`), the duplicate condition, and the duplicate `&&`;
  - `!size()`, the inner `size()<1`, and folded tautologies (`__intl||!__intl`, `__frac_digits>=0||<0`);
  - the `for(;;)` and `do while(0)` wrappers.
  
  These are worse:
  - `empty()` and `begin()==end()` score 0.978;
  - `switch` and `if(!=0);else` score 0.921;
  - `while` and `for(;cond;)` score 0.931.
  
  Frequency is computed after folding, so a folded second condition does not make the site colder.
- h2/h3, phantom budgets:
  - The D and S decisions are uniform across 28c and the late sites.
  - kD>=9 outlines D at all 7 sites (0.9958). kS+kD>=9 outlines S everywhere (the bank).
  - kW>=1 outlines W at the late sites only (0.9495, or 0.9415 when D is also outlined).
  - No grid point calls 0x142D70 (W or D) at 28c while the late sites keep S.

Why (structural inference, consistent with the toy8 facts):
- The late sites are the four sign temps, built in a *nested* ternary, so they sit two conditions deep and are cold. Return 2 follows the early return, so it is cold as well.
- Return 1 and the two currency temps (a single ternary) are warm.
- The binary W grading therefore outlines W exactly at the cold sites. That is retail's map under the true naming in `df20-funclet-naming-20261021` (warm: W inlined, S called = 0x142D70; cold: W called = 0xB3C0).
- Under the ledger naming, 28c would have to be *more* outlined than the colder late sites. No return-statement, budget or depth mechanism gives that without moving code.

Verdict: DF20 is walled by the inverted wide-string destructor naming. The prerequisite is
the class-level reconciliation in `df20-funclet-naming-20261021/handoff.md`:
- W<G> moves to 0xB3C0, and S/D<G> to 0x142D70;
- the ten linked units that emit a 14 B W<G> COMDAT have to emit retail's 63 B framed W<G>, which calls S;
- then re-run the natural V3 a9 w1 shape on the real body (phantom cost on S so that S is never inlined; W at the default budget).

Shared-delta lead for that pass: in retail, S appears never to be inlined (warm sites call it, and the 63 B W<G> calls it), while D always folds into S's 14 B body.

## Session 2026-10-21 (late): reproducing 0xB3C0 and the inliner levers

Two files are banked here:
- `a9d0sig-true-naming-0.9986.cpp.txt` is the best body under the true naming: fit 0.9986, nd 2. Only return 2 (41e/42f) calls S where retail calls W.
- `w63-v2-b3c0-repro.cpp.txt` is the evidence for 0xB3C0.

**Target fact.** Retail 0xB3C0 is the 63 B framed W<G>. It is reproduced byte-for-byte when the TU specialises `_STLP_alloc_proxy<unsigned short*,unsigned short,allocator<unsigned short> >` with a non-empty destructor, `~_STLP_alloc_proxy() { if (0) free(_M_data); }`. Specialised that way, W keeps an EH frame and calls S out of line. S is also 63 B in that build. The funclet of 0xB3C0 calls 0x69E440 (an empty ret) on this+8, which is the proxy dtor before folding. So the units that should emit W<G> at 0xB3C0 need this proxy shape (or the source that produced it) as part of the naming reconciliation.

Disproven this session (bank 0.9993 under the ledger naming is unchanged):
- (a) W bodies on the `_Destroy` path are inert.
- (b) depth(1) on the sign or return statement is inert under kS=9.
- (c) depth(0) at return 2 also outlines w and L, costing +32 B.
- (d) A `__forceinline` locale and narrow chain does not survive depth(0).
- (e) W phantom kinds:
  - empty, folded and extern "C" phantoms cost nothing;
  - throw(), nothrow and _MoneyLeak phantoms add EH states (+16 B).
- (f) A real non-trivial proxy dtor inside do_put gives frame 0xd8 and proxy EH states. That is wrong for do_put, which has no proxy state.
- (g) A function-level `inline_depth` of 1–5 is worse; 6 and above is inert.
- (h) K-kind W phantoms at kW 16/32/64 with kS=9 never outline W.
- (i) t13 grid on a9d0sig: kS∈{0,4,8}, kW∈{1,2}, depth(1) before curr_sym, sig depth(0) on/off, depth(1) around return 1. All 48 variants give the same result: fit 0.9366, frame 0x118, W called at every late site, and nothing called at 236/259/28c. With S inlinable, the W phantom outlines W at the cold sites, but S is then inlined at the warm sites. No statement-level depth fixes that, because S has to be outlined everywhere while W is inlined only at warm sites.

Next angle: do the naming reconciliation first. Then search with S non-inlinable, which matches retail (S is never inlined anywhere), and with W at the default budget. The remaining residue is return 2, which is cold but must call W. Return 1 is warm and inlines W. Try changing the frequency of return 2 so it counts as cold: for example `__builtin`-free shapes such as a `goto` to a shared return.
- (j) t14, return-2 shapes on a9d0sig (true naming). These are inert, scoring 0.9986 with the same map:
  - duplicate nested condition, `!(!=)`, `do{}while(0)`;
  - the return moved inside the scanning loop;
  - a nested non-foldable condition with both arms returning.
  
  These are worse:
  - `__cp-__digits_first==0` scores 0.9572 (warm sites shift);
  - the `for` scan loop scores 0.9638 (return 2 merges into a shared exit, 2578 B);
  - `if(!=);else` scores 0.9147.
  
  Return 2's W/S choice did not respond to any frequency shape tried. The return-2 residue needs the reconciled S (never inlined) rather than a statement shape.
