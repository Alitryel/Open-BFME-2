# DF20: allocator interactions and external EH call audit

Continue only 0x0000DF20, the unfinished wide STLport money_put string overload.
The stronger bank remains 2594/2610 bytes, frame 0x118, historical score 0.8114.
This session changes its explanatory comments only. No C++ body, ledger row,
pin, Code source or verification tool changed; exact C++ credit is zero.

## Inputs and checks

Parent cd30cf8a2aaa62ec9134e0f21139dc4f37520818. Initial tree was clean;
pull --rebase and check_csv passed (97648 functions, 15930 symbols, 1136 data).
Only DF20 was claimed. BFME 1's successful freshness stamp was 2026-10-20
08:02 UTC, less than 24 hours old; its recorded verified pointer is
0dc8a26a9c6041c73dc564754cd059dc54faa72a. The active checkout remains
4483e88da1c2f3b9a273f779baac7458bd8bb891. No reference update was due.

MSVC 7.1 RTM, official align_diff/explain_mismatch, BFME_OBJSTORE=off,
/EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC, actual vendor STLport
4.5.3 headers. Scratch overrides explicitly precede the vendor include path;
their generators preserve the complete header except the stated edits.
No direct build.compile_source calls or shared-header edits were made.

Fresh bank diagnostics reproduce 20 structural / 99 memory / 34 register
differences, first difference +0x2A (locale esp+0x40, retail +0x3C), and no
unresolved ordinary callees. Diagnostic exit zero does not mean exactness.
EH verification reports bytes_differ at 0x75BB60: one nonrelocation byte,
locale ebp-0xF0 versus retail -0xF4. The associative text is 337 bytes and
xdata 212 bytes, with no placement conflicts. See checks.json and bank logs.

## New external EH evidence

The previous one-byte measurement excluded relocations. bank.eh-calls.json
now records each external REL32 in the placed EH sections, its target from
retail, its COFF addend, and admission of the four relevant target addresses. Other
admitted candidates include jump thunks and folded funclets; the file records
the complete candidate count, without duplicating those large lists.

Of sixteen external calls/jumps, five agree: locale::~locale at 0x7150,
three narrow whole-string calls at 0x142D70, and the frame handler at 0x629182.
Eleven do not agree with the emitted names' admitted addresses:

- Nine emitted wide whole-string destructor calls target retail 0xB3C0;
  0x142D70 is admitted for their emitted name, but 0xB3C0 is not.
- One narrow and one wide allocator-base destructor call target retail
  0x142D70; 0xB3C0 is admitted for their emitted names, but 0x142D70 is not.

These are target call addresses, not newly proven source identities. The
14-byte body is also a deallocation helper fold; do not rename owners or add
pins to hide this discrepancy. The bank is not one byte away from an EH match.
An audit of the earlier 54 whole/base definition-placement objects and the
current primary-forceinline and implicit-destructor controls retains these
same eleven disagreements. Auditing unrelated EH shapes produces meaningless
addresses; compare call sites only after their placement and instruction shape
are established, as for this bank.

## Trials ruled out

There are 428 matrix cases, plus six corrected retries in trials.jsonl.
The preliminary explicit-empty-destructor run also needed specialization-order
repair; only its twelve corrected results are retained. All final cases emit
the parent. None improves the bank. EH measurements are in eh-summary.jsonl.

- Allocator/constructor interactions, 36: cross the improved opaque base ctor
  with explicit/default/digits.get_allocator/named/const/reference allocators,
  early allocator scopes, actual extra-template-constructor macro, two/three
  arguments, temporary/named range tag and depth 0/255. Four cases emit 2610
  bytes but still have 23/99/34 differences. The best remains 2594,20/99/34.
- Header context, 64: const currency/sign return values, visible locale copy
  plus noinline getloc, visible noinline facet lookup, base ctor opacity and
  base destructor visibility. The getter/locale/lookup choices are inert.
  Only the already known ctor/dtor visibility dimensions change output.
- Scalar reference lifetimes, 256: independently bind six widened characters
  to const references; cross const empty policy and unsigned-char negative.
  Every case retains the bank's size and alignment metrics.
- Explicit empty whole destructors, 12: wide/narrow/both, inline/forceinline,
  opaque/visible wide base. Removing POD _Destroy does not change the outcome
  or repair external EH call identities. Initial C2908 placement errors were
  corrected by declaring the opaque base destructor before specialization.
- Implicit whole destruction, 24: remove the primary whole destructor from
  a scratch header, cross no proxy / late-dead enum-zero proxy / nothrow proxy,
  ctor opacity and base visibility. Six C2908 cases were rerun with the base
  declaration before locale; all then compile. Implicit destruction is inert
  without the proxy. Proxy cases give 2645..2688 bytes and wrong cleanup/EH
  shape, including extra base/whole calls. This new interaction also fails.
- Primary-template attributes, 36: place default/forceinline/noinline on both
  primary destructors in the header before any locale instantiation, crossed
  with ctor/base visibility. Forceinline is inert. Noinline loses retail's
  required inline frees, yielding 2562 bytes and 28..33 structural regions.
  Attribute placement before instantiation does not fix EH callee selection.

These test control of constructor entry, local lifetime, real header/type
context, callee visibility and compiler/inlining attributes. Earlier handoffs
already cover source control flow and broad compiler settings; do not repeat
those unchanged. No missing ordinary callee is the current prerequisite.

## Remaining task and reproduction

Native normal cleanup remains three whole-wide calls, six base calls and six
frees. The bank has three whole-wide calls, seven base calls, three frees and
an explicit locale call. Early-return sharing, final wide destruction and the
locale slot remain wrong, in addition to the eleven EH callee discrepancies.

A concrete next investigation is a small unwind probe using the real headers
and the verified 63-byte/14-byte providers: establish what makes the compiler
lower a whole-string cleanup to the base in EH while retaining a whole call
at a normal depth-zero site. Require proof of both normal and unwind callees
before carrying any result into this parent. This has not been tested here.
Keep the current bank until a full-parent variant is stronger.

Reproduction: create build/df20-allocator-interaction-20261020, copy the tracked
bank there as bank.cpp and the diagnostic .py.txt files there as .py. Run the
matrix, header_context, scalar_refs, empty_destructor, implicit_proxy,
implicit_fix and primary_attributes generators. Then run verify_bank.py,
eh_scan.py, and eh_calls.py with the scratch bank.cpp path. They use isolated
sources and official diagnostic entry points. Full raw scratch is preserved
under build/; tracked scripts/results suffice to regenerate it.
