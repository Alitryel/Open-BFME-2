# 0x0000DF20: constructor visibility fixes the temporary flag slots

Continue this same wide STLport money_put string overload. The bank is improved
but remains partial: 2594/2610 bytes, retail frame 0x118, historical score 0.8114
retained conservatively. No matched row, Code source, symbol pin or gate changed.
There is no new exact C++ byte credit. Claim was released for the next session.

## Verified improvement and inputs

Parent 4032446a1e830ebdd34e13c1dceee2fa8aba0afe, origin/master
43c6a1a69e860178cc81bea4e681d31317aca3f8. MSVC 7.1 RTM, /EHsc /MD
/D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC and actual vendor STLport 4.5.3
headers. BFME 1 checkout remains 4483e88da1c2f3b9a273f779baac7458bd8bb891;
the successful freshness stamp was under 24 hours old. No pointer update was due.
Initial pull and check_csv passed. No other body was claimed or attempted.

The sole material source change is a declaration-only explicit specialization
of the wide allocator-base constructor, after string and before locale. Its
whole-body recursive fold at 0x689600 was verified and recorded by the earlier
session; this session adds no pin or new callee identity. Both visible and opaque
forms retain that call, but their alias/lifetime information differs.

Official align_diff changes 20 structural / 111 memory / 34 register differences
to 20 / 99 / 34. Official explain_mismatch still finds the first difference at
+0x2A, but the locale slot moves from esp+0x44 to esp+0x40 (retail esp+0x3C).
No unresolved ordinary callees remain. Both diagnostic tools ran successfully;
their success status does NOT mean the partial body byte-matches.

The associative 212-byte xdata agrees outside relocations, with no placement
conflicts. Its 337-byte associative text now differs in ONE nonrelocation byte,
down from 17: the first funclet uses lea ecx,[ebp-0xF0], retail [ebp-0xF4]. All
16 temporary-flag displacement differences disappear. EH verification still
reports bytes_differ, not EXACT. This comparison does not certify every masked
EH callee identity. checks.json and bank diagnostics record the measurements.
The optimized WorldBuilder twin and 23-state target map from the prior handoff
remain valid; that twin supplies no debug-local declaration order.

## Trials that should not be repeated unchanged

669 factorial variants, 645 compiling and emitting the parent, are recorded in
trials.jsonl and trial-summary.json. All compiles used official align_diff or
explain_mismatch with BFME_OBJSTORE=off and isolated source paths; no direct
compile_source calls. 24 range-initializer prototype trials hit compiler C1001,
UTC P2 main.c line 148. This is a compiler failure, not a gate false reject.

- Scalars, 256: const character/scalar locals, hoisted characters/negative
  declaration, unsigned pattern loops, int versus bool negative, split postfix
  assignment, named return iterator. Only int polarity/unsigned loops move
  output; none repairs cleanup or improves the original bank overall.
- Exception/optimizer declarations, 36: /EHsc, /EHs, /EHa, /GX, /Og-, /Oi-, /Os,
  /Oa, /Ow crossed with free C linkage and base destructor visibility. Some C
  free variants score better structurally but resolve to CRT thunk 0x628F98,
  NOT retail GameMemory free 0x30830. Rejected; never promote these or add a pin.
- Thin basic_string-derived wrappers, 112: currency/sign/new-digits subsets,
  parent depth 1/2/3/255, base visibility and wrapper destructor depth 0/255.
  No improvement; wrapper call names may be unresolved. No wrapper was banked.
- Iterator copy/assignment definitions, 64: implicit, memberwise and memcpy of
  the real eight-byte iterator, inline/forceinline, nothrow and base visibility.
  No improvement. Actual vendor operator++ is a no-op returning a reference;
  these expressions do not require another output-iterator temporary.
- Allocator lifetimes, 14: explicit default temporary, digits.get_allocator(),
  named/const/reference allocators at four scopes. get_allocator emits 2610
  bytes but is NOT exact (23/99/34); same-size output is insufficient proof.
  Named allocator variants worsen allocation. These use the pre-improvement bank.
- Range constructors, 9: actual _STLP_NEEDS_EXTRA_TEMPLATE_CONSTRUCTORS branch,
  primary versus explicit two-argument ctor, named/temporary tag and allocator
  copy expressions. Best explicit shape is 2594, 23/100/36, EH one byte.
- Range visibility, 24, and corrected forms, 24: base ctor opaque/visible,
  range initializer opaque/visible, primary/specialized ctor and named tag,
  plus the extra-constructor macro. Base ctor opacity produces the new bank.
  Opaque range prototypes, including noinline and explicit template arguments,
  hit C1001. A defined noinline specialization and a scratch vendor-header
  noinline definition compile but do not improve the bank. The verified range
  provider at BF90 documents its unused tag's effect on hidden-result reuse;
  merely exposing that unused tag does not fix this parent's last EH byte.
- Recombination on the new bank, 28: int negative, unsigned loops, first/second
  early gotos and final return inside/outside currency/sign scope. No stronger
  bank. regional-exit.cpp.txt emits 2626, 16/106/33 and removes locale call;
  worse locale/cleanup allocation remains. Preserve as a regional lead only.
- Stack visibility on the new bank, 48: locale plain/const/const-reference,
  nothrow wide base ctor, opaque narrow base ctor, visible wide copy ctor and
  base versus derived empty copy tag. Thirty-six are exactly the new metrics;
  changing the tag loses (2578, 23/124/40). No last-slot fix.
- Sign/currency helper context, 36: ternary/if/direct-return forceinline
  helpers, definition depths 0/1/255 and base destructor visibility. Added
  helper context loses overall or changes cleanup counts. Direct currency
  wrappers can also emit 2610 without matching. No promotion.
- Guard scopes, 18: retain early returns, invert conditions around the remaining
  body, or put the remainder in else, crossed with base destructor visibility.
  A second guard scores 2600, 15/92/35 and retains EH one byte, but moves the
  second early cleanup to the end (+0x9B2), unlike retail. This is an alignment
  count improvement from moved blocks, not stronger target control-flow proof.
  Keep the straight-line bank. The generator preserves every tested shape.

## Remaining mismatch and next session

Native normal cleanup has three whole-wide destructor calls, six base calls and
six frees; the bank has three whole calls, seven base calls, three frees and an
explicit locale call. First-return shared tail and final three wide destructions
remain wrong. Small scalar/allocator/tag homes also differ. Raw esp operands
around calls must be normalized for pushes before inferring object layout.

No ordinary missing callee blocks this target. The constructor finding is
positive evidence that visible unused parameters and alias analysis influence
the low frame independently of retained call instructions. A concrete next
matrix can combine this opacity with the previously separate allocator-source
and two-argument-constructor variants, then attribute any changed stack region.
Another unresolved question is how real header context makes final normal
wide cleanup inline while sign temporaries retain the verified base call;
blanket visibility and late-dead proxy lifetime already failed in prior sessions.
Do not repeat those families without a new interaction or target fact.

The pre-improvement bank is before.cpp.txt. To reproduce, restore it to
build/df20-scalars-20261020/bank.cpp, copy trials.py.txt to that directory as
trials.py, and copy the generator .py.txt files there with .py names. Run range
visibility before generators that consume its new-best scratch source. Scripts
use distinct variants and official tool entry points. Diagnostic text whitespace is normalized. Raw sources and logs are
also preserved in that scratch directory. Diagnostic scripts are evidence,
not hooked tools. No nonmatching reconstruction was left in Code.
