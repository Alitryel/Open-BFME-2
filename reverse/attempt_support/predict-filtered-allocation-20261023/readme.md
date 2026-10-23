# Predictor allocation follow-up

Target remains unrowed: `0x001C5E30..0x001C6130`, 768 bytes,
`?Rva009B5530Prepare@@YAXPAURva009B5830State@@PAXH@Z`.
Only approved clean-room spec `reverse/vp6_cleanroom/specs/001c5e30.md`,
retail and repository code were read. No decoder source was consulted.
Input BFME2 `3eaf822ff05b788b143fed982c482a90129e4cc3`; BFME1 pointer
`f890413e75e671748215ba2ef3304aa7953993e9`. The active codex4 freshness
lock was respected. Flags remain O2/G6/NDEBUG/MD, unmodified MSVC 3077.

Read the complete picker history and all three earlier handoffs first.
They already excluded ordinary declaration ordering, motion integer types,
arithmetic orders/splits, statement permutations, flags and compiler builds,
buffer lifetimes, builder helpers and ordinary permute. The prior invalid
farm bank is not reused. There is no missing callee. WorldBuilder has no
match for this body.

The new hypothesis was allocation cost before equivalent-path merging,
following the compiler mechanism in docs/recipes.md. Six finite families
compiled in private scratch, eight workers, without using compile_source or
the shared match cache. results.json records their counts and hashes:

* 432 single-operation duplicates, three known phase-placement regimes,
  six predicates and both structured and labelled forms.
* 9,216 combinations of ten duplicate-operation choices, three regimes and
  three predicates. Four choices affect both setup arms together.
* 48 variants of the earlier handoff's untried shared-mask/phase join.
* 768 qualifications of the actual motion/mask/frame reads.
* 1,152 inline capture/promotion/phase/whole-pel helpers, with value,
  reference and integer parameter choices. This tests local lifetime and
  inlining without consulting prohibited headers.
* 4,096 combinations of source selection, mask, builder-call, filtered
  buffer/stride and unfiltered capture/promotion costs. These test whether
  the slot-correct early-phase regime can retain the native entry code.

Total: 15,712 valid source variants; none exact. Initial generator errors
affected 384 pointer qualifications and 576 helper spellings. Those were
corrected and the affected variants rerun, all successfully; rejected
sources are not negative matching evidence. Each family includes a baseline.
Full resolved extents, rather than an instruction score alone, determine
exactness. The diagnostic aligner ignores branch destinations for ranking;
it does not grant admission.

The current bank emits exactly 768 bytes, with 22 raw differing positions
and 15 differing aligned instructions under this scorer. These metrics
differ from the earlier bank's published fitness; its 0.975 metadata and
source are preserved rather than silently replaced with a weaker claim.
The best small alternative has 21 positions / 14 instructions different.
It duplicates the unfiltered mvy capture under `mask`; one raw-short store
moves earlier and mvy receives its native home, but mvx and limit then use
different homes. It does not solve the Y role or promoted-Y home. Preserve
the canonical bank; alternative.patch is a zero-context patch against the
recorded bank, for regional investigation rather than a claimed recovery.

The existing retail dispatch oracle passes 1,238/1,238 cases on that
alternative, including every threshold byte, builder-mutated vectors,
callee arguments, cdecl stack balance and preserved registers. Pixel
callees are stubbed; no pixel algorithm or full equivalence is claimed.
oracle-alternative.json binds the source and native/compiled bodies.
Unicorn 2.1.4 was installed only in ignored scratch. The unchanged oracle's
compiled-reader was redirected to the isolated object, with ordinary COFF
relocations resolved; no gate object was substituted.

Read-only C2 packing traces show promoted y has weight 5, while raw mvx
and mvy each have weight 3; packing.json retains the node words. This is
consistent with y's extra unfiltered spill/reload and earlier stack home.
The node's size is at +0x20, weight at +0x38, index at +0x3C; an initial
scratch display confused those fields, corrected in the saved records.

Eighteen explicitly **diagnostic-only** debugger compiles changed initial
register priorities of y (symbol 13, originally 159) or mvy (17, 125), at
candidate insertion return site 0x1078474F. Values 0,50,90,125,130,159,
180,256,400 either preserve the baseline or regress; none improve it.
These objects never enter the normal cache, ledger or acceptance process.
diagnostic.json preserves the controls. This rules out these initial
priority changes alone, not subsequent split/coalescing decisions.

No source, row, pin, baseline or verifier change. All generated objects
remain ignored under build/vp6-1c5e30-20261023. Copy the .py.txt scripts
there, remove .txt, and use search.py modes to replay. Its input comes from
git at the recorded revision. trace.py and diagnostic.py use the debugger
helper adapted from the collision recovery; diagnostics require base.cpp
copied from the recorded bank. No modified-compiler object may be landed.
Next useful angle: explain the unfiltered Y/mvy split and coalescing decision,
rather than repeating the tested source-cost and initial-priority families.
The existing best bank remains available; claim released. About 13 minutes,
model gpt-6.1-sol.
