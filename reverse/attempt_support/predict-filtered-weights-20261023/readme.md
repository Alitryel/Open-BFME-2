# 0x001C5E30: retained stack weights, 2026-10-23

Still partial. The bank improves from byte ratio 0.9752604 / fitness 0.9767397
to **0.98046875 / 0.9820901593**, still exactly 768 emitted bytes. Mnemonic
alignment counts **12 differing instructions**, down from 16. Nothing has
been added to the matched ledger. Continue this standing assignment.

Clean room: `reverse/vp6_cleanroom/specs/001c5e30.md`, retail, and this
repository only. No external decoder source was consulted. The ABI, offsets,
boundaries and callback destinations come from that spec and retail. The
private type and local names remain reconstruction choices, not independently
established original names. Builder/variance visibility trials also consulted
specs `001d8dd0.md` / `001d8a30.md` and their already matched repository bodies.

Inputs: BFME 2 local `2b7fcaaa56fdf0bb67550a0582f420aaefd4853f` (the pending
canMake recovery, subsequently rebased as `64bd2de47d`); MSVC 7.1 under Wine;
unchanged `/O2 /G6 /DNDEBUG /MD`. BFME 1 was not updated: the runner's
freshness lock belonged to codex4 and was less than six hours old. Ledger
validation and the published-object fetch completed before the attempt.

## What improved

`docs/recipes.md` explains that stack weights can survive equivalent-path
merging. Two such changes compose here:

1. In the filtered arm, duplicate `mvy = vectors[block].y; y = mvy;` under
   `if (pbi->profile != 0)`, with identical arms. The builder may change the
   profile/vector, but both paths reload the same vector after the call.
   C2 removes the branch and swaps the two raw-short stack homes. This alone
   gives fitness 0.9780773, byte ratio 0.9765625, 15 differing instructions.
2. Duplicate the complete size-threshold `if/else` under `if (x != 0)`.
   C2 again removes the branch; `limit` now shares the native raw-Y slot.
   This removes three more differing instructions. Predicates `mvy > 0` and
   `xPhase != 0` also produced the same winning bytes in the node sweep.

The bank has readable formatting/comments; its compiled bytes are identical
to the raw winning trial. Its resolved SHA256 is
`8b58496d456bd43a4635438b956c0b741b6e462474633429cc31fd335a2eec37`.
Retail's 768-byte SHA256 is
`4db8db0dc2d1b92c009d33e823955f3c4a75bd9a7cb5adab3f72f3a4784a0e52`.

## Exact remaining mismatch

| Value | Retail home | New bank home |
|-------|-------------|---------------|
| raw mvx | 0x18 | 0x20 |
| raw mvy | 0x1c | 0x1c |
| promoted y | 0x20 | 0x18 |
| limit | 0x1c | 0x1c |

In the unfiltered arm retail stores raw Y immediately, promotes into ECX,
copies ECX to ESI for the whole-pel calculation, adds ECX back to ESI, then
stores promoted Y. The bank promotes into ESI, copies it to EBP, spills it
early, adds it back from its home, and stores raw Y later. See
`best-vs-retail.diff` for the complete resolved comparison. The prologue,
x-term spill, instruction addresses, calls and all other tail instructions
match; remaining operand differences include the two swapped stack homes.

Two region winners are preserved as diagnostic sources, not progress:

- `unfiltered-near-native.cpp.txt` (783 B): duplicating the filtered
  `base = loopFilteredBlock; offset1 = 34;` under a loop-filter-mode condition
  gives native raw/promoted homes and the native unfiltered arm, except the
  final `mov edx,ecx`. However it changes the prologue to AL tests/source
  reloads, retains a dead post-builder loop-mode load, and stores immediate
  34s instead of using EDX. This explains the missing final EDX copy.
- `filtered-and-tail-native.cpp.txt` (780 B): duplicating the first four
  unfiltered assignments under `mask != 0` makes the filtered arm and tail
  native (ignoring branch-address shifts), but introduces a real unfiltered
  mask branch and a mask spill/source-home swap in the prologue.

## What this session actually tested

The previous `predict-filtered-slots-20261020/readme.md` and earlier linked
handoffs were read before editing. Do not repeat their declaration/base-term
permutations or three xPhase-position regimes. The following are new trials;
`search-summary.json` records counts and best scores, including failures.

- s1: phases factored after the arm join, preserving the post-builder mask
  reload; motion copies and inline accessors. No gain.
- s2/s4/s6/s10: setup primitives, contiguous sequences and sign-step blocks
  duplicated under initialized predicates, including nested duplicates and
  factorial combinations. These found the first gain and both region winners.
- s3/s20: local aggregates, nested aggregates, single-element arrays and
  correctly initialized scalar/reference aliases. s3 had 114 generator compile
  errors (field replacement and insertion inside a multiline statement);
  s20 corrected those errors and all 438 variants compiled. No gain.
- s5/s11: signed/unsigned raw representations with explicit short promotions;
  int/long promotions; alternative equivalent sign-correction and phase
  operands. No gain.
- s7: actual matched builder/variance helper bodies visible before/after the
  body, typed/opaque builder arguments, exception specifications. All final
  96 trials compiled; only five distinct parent bodies. No gain.
- s8: inline function extraction of the body/setup/tail and identity helpers.
  Diagnostic trials only: some speculative setup-by-value cases read locals
  before assignment and were never bank candidates or oracle evidence.
- s9: separate address-calculation and persistent magnitude values, six
  lifetime/placement choices per axis, int/long. All corrected trials compile;
  no gain.
- s12/s13: recombinations of the region winners with offset chaining/copies,
  stride positions and offset signedness. No gain. s13's first generator had
  a potentially uninitialized stride in duplicated arms; it was fixed and
  rerun before retaining the results. Those are diagnostic sources only.
- s14: settings crossed with the first improved bank and region winners:
  G5/G6/G7, O1/O2/Ox, Ob0/Ob1/Ob2/default, Og-/GF/Zp1. No gain.
- s15: threshold magnitude/boolean temporaries and duplicated dispatch tails.
  No gain.
- s16: C frontend on type-correct versions of the four seeds. No gain; no
  name or pin was changed for these diagnostic trials.
- s17: individual dispatch subtrees duplicated under seven initialized
  predicates, depths one to three. Found the second gain (threshold subtree).
- s18: that late-threshold change recombined with s2/s4/s10/s11. No further
  gain (4,502 trials).
- s19: twelve independent setup choices, half factorial (2,048 trials), on
  both useful retained-weight changes. No further gain.
- s21: hoist selected raw loads/promotions/phases before the profile tests,
  still reloading after the mutating builder; direct/short/int builder
  arguments and placements around frame selection. No gain.
- s22: idempotent setup sequences in fixed-trip loops, counts 1/2/4/8 and
  three loop forms (960 trials). No gain; only 11 distinct bodies.
- s23: profile/loop-mode/mask field access through force-inlined getters,
  pointer/reference parameters, boolean/integer return spelling, and
  function-scope field reference aliases on three seeds. No gain.
- One permute run on the first improved bank: 784 trials, no gain after
  600 non-improving trials. Do not restart that run unchanged.

There are 15,488 stored generated-trial records, 15,374 successful compiles,
plus that permute run. Generated diagnostics are not all independently proven
equivalent; only the bank is the validated continuation. No exact trial was
found. Search objects went to unique scratch paths via `compiler_command`,
never through `compile_source` into the shared match cache. The final
`explain_mismatch.py` diagnostic used its normal, separate cache entry.

## Validation and resumption

Run from the repository root:

```
python3 reverse/attempt_support/predict-filtered-weights-20261023/reproduce.py --oracle
```

This recompiles the bank to an isolated scratch object, resolves every DIR32
and REL32 against the five known targets, scores exactly the 768-byte proven
extent, and runs the existing native dispatch oracle. It requires capstone and
Unicorn (`unicorn==2.1.4` was used). The bank passes **1,238/1,238** cases,
including all threshold-byte values, builder-mutated vectors, call arguments,
preserved registers and cdecl stack balance. Pixel algorithms are stubbed;
this is dispatch evidence, not full pixel-output verification or byte equality.

`explain_mismatch.py` independently confirms a 768-byte symbol and the first
difference at +0x84. Plain `align_diff.py ... 768` nevertheless searches for CC
padding and extends retail to 952 B across the next function; its raw COFF
operands also retain unresolved data references. Do not use that unadjusted
report to replace the proven boundary or the resolved comparison here.

Before handoff, rebased both pending commits onto upstream `c737f56831`,
preserving both independent additions in the `docs/recipes.md` conflict.
`AGENTS.md` had not changed. Ledger validation passed (98,091 functions).
Rechecked the inherited canMake landing: its home TU passed 5/5 rows including
the EH data/funclet placement, and `Rva0039205CDtor.cpp` passed 2/2. Recompiling
this predictor bank and rerunning the oracle after the rebase produced the
identical `validation.json` report. The canMake recovery remains a separate
commit; this bank adds no matched bytes.

Next investigation should target the promoted-Y split lifetime while retaining
the native early xPhase/x-term spill and EAX source lifetime. Alternatively,
start from the preserved unfiltered region winner: find a control-flow/source
shape that keeps its raw/promoted slots but restores the EDX constant and CL
profile tests. The simple accessor, hoist, offset-copy, loop and equivalent-path
combinations above are already tested; this is still a compiler-shape problem,
not a known missing callee. No source, pin or ledger workaround was landed.

Scratch: `build/predict-filtered-20261023/` (not required to reproduce the bank).
Model: gpt-6.1-sol.
