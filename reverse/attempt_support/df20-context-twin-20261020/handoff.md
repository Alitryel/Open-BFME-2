# 0x0000DF20: optimized twin, unwind displacement diagnosis and context trials

Continue this same wide STLport money_put string overload. The bank remains
partial at 2594/2610 bytes, frame 0x118, historical score 0.8114. This session
removes the unnecessary explicit pattern alignment: the complete emitted
function bytes and relocations are identical to the previous bank. No matched
row, Code source, pin or gate was changed; no new retail C++ bytes are claimed.

## Inputs and checks

Parent revision 79b31765348a1f5773de34426e78bbee274f58be. Default MSVC 7.1
RTM, /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC, vendored STLport 4.5.3.
Every compile used the official align_diff/explain_mismatch entry point with
BFME_OBJSTORE=off and distinct scratch paths. No direct compile_source calls.
BFME 1 checkout is 4483e88da1c2f3b9a273f779baac7458bd8bb891. Its successful
freshness-check stamp was under 24 hours old; this seat did not advance inputs.
The previous verified allocator-fold repair remains in the parent commit.

Initial pull and check_csv passed. Fresh final-bank align/explain confirms
2594 bytes, 20 structural regions, 111 memory and 34 register differences,
first difference +0x2A (locale slot 0x44 versus retail 0x3C), and no unresolved
ordinary callees. EH still fails; this is not an exact parent or an EH landing.
Final check results are in checks.json and bank-explain.txt. No ledger-backed
source changed, so another build.sh/link gate of the unchanged owner was not
needed. The bank was never left as a nonmatching Code reconstruction.

## New target evidence

WorldBuilder VA 0x006E71A0 contains the complete 2610-byte twin. All 767
instructions have equal offsets, sizes and opcodes; after masking 126 external
branch targets and in-image immediates, there are no remaining differences.
See twin.json for every masked site and twin.py.txt for the exact comparison.
This supports a common optimized library implementation; it does not establish
which compiler release or source input produced it, nor prove callee identities.
This twin is optimized and therefore supplies no debug-local declaration order.

Both target images have the same 23 unwind states and to-state sequence. Their
327-byte cleanup regions contain 70 identical instructions after masking direct
call/jump targets. See eh-graph.json and eh_graph.py.txt. This independently
confirms that the optimized shape is shared, including cleanup selection.

The bank's complete 212-byte associative xdata agrees with retail outside
relocation fields, with no relocation-placement conflicts. The 337-byte
associative text (cleanup region plus handler) differs in only 17 nonrelocation
bytes. All are stack displacements: locale [ebp-0xEC] versus [ebp-0xF4], and
16 accesses to temporary flags [ebp-0x11C] versus [ebp-0x124]. Thus the remaining
EH failure is local/flag placement rather than a different nonrelocation state
map. This is a diagnostic, not a claim that relocated callee identities match.

## Factorial trials: do not repeat unchanged

trials.json contains 357 results, 289 compiling and emitting the parent. The
remaining entries include initial declaration-order errors, corrected below,
and forceinline variants that emit no parent without an explicit emitter.
Transform scripts are preserved as diagnostic .py.txt files. All source files
and raw compiler logs remain under build/df20-context-20261020 in this checkout.

- Element destruction: generic wchar trait dispatch versus scalar pseudo-dtor
  loop versus an enum-false free body, crossed with opaque/visible base dtor,
  nothrow, direct sign initialization and const sign/currency. Generic and scalar
  paths give the same bank. Direct initialization and const locals are inert.
  Empty throwing paths add wrong states; nothrow or blanket visibility loses.
- Definition context: plain/inline/forceinline base dtor definitions at depths
  0/1/255, before/after parent, with/without proxy late-dead lifetime. Attributes
  and definition position are inert at fixed other factors. No better bank.
  Whole-dtor specializations initially failed as already instantiated; moving
  declarations before locale fixed all 36 trials. Their definition positions,
  attributes and depths likewise do not repair selective cleanup.
- Copy wrapper lifetime: by-value versus reference output parameters, local
  versus outer derived tag, temporary versus named random-access tag, and
  direct decimal assignment are inert. Removing wrappers with site-depth-zero
  direct __copy calls gives 2546 bytes, 26/148/50 and loses overall.
- Control flow: first and second early exits were independently changed to goto,
  with a currency/sign scope and final return inside/outside it. First-only goto
  with the normal return inside removes the explicit locale destructor call:
  2562 bytes, 20/117/29. Preserve regional-exit.cpp.txt and its align output as a
  regional lead, not the best bank. It still has wrong final wide cleanup and
  worsens memory/overall allocation. Other exit combinations lose too.
- Layout/lifetime: move the alignment attribute among 12 existing locals or
  remove it, crossed with int/bool polarity and loop-counter scope. Removing
  pattern alignment is byte-and-relocation inert with the separate bool local.
  Loop-counter scope is inert. Aligning locale reduces 111/34 to 100/32 but
  forces a locale slot unlike retail; do not promote a better count as proof of
  an unsupported alignment. Aligning currency with int polarity gives 92/32 but
  changes the retail byte-bool shape and loses structural fit.
- Template compilation context: specialized parent plain/inline/forceinline,
  explicit emitter, polarity declaration versus initialization, and pattern
  alignment. A generic primary definition initially conflicted with the header's
  _monetary.c body; suppressing that one include with its guard fixes all 24
  generic trials. Generic primary plus explicit member instantiation or emitter
  produces exactly the same 2594-byte metrics. Parent template status and these
  decorations do not explain this residue.

## Remaining work

The previous handoffs still apply. Native cleanup has three whole-wide calls,
six base calls and six frees; the bank has three whole-wide calls, seven base
calls, three frees and one explicit locale call. Final normal-exit wide cleanup
must inline without changing the sign temporary and early-return call choices.
No ordinary missing callee blocks work now. The shared optimized WB twin and
exact nonrelocation state map narrow the problem to local placement and
selective lowering of normal cleanup, not a missing debug-local reconstruction.
Do not repeat generic visibility, wrapper-parameter, template/emitter, global
inline-depth, blanket optimization or proxy-EH trials without new evidence.

To reproduce these matrices, restore the parent bank from the revision above
to build/df20-context-20261020/baseline.cpp, copy the diagnostic scripts there
without their .txt suffix, and run the selected script from the repository root.
Each uses official align_diff and eight independent compiler processes. No
helper agent, link cycle, census or maintainer-only runner was started.
