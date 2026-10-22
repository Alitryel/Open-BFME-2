# canMake: priority construction before register colouring

Continue the standing assignment `AIBuildableWallSegment::canMake`,
`0x00596e15`, retail 218 B. The best bank is unchanged: **216 B, diagnostic
fitness 0.945980, normalized instruction difference count 6**, masked SHA256
`21a3f8f3243cb7b71022d189657993f03de236d0f2c6ca0516628a7e138820c9`.
No byte-exact C++ coverage or ledger row was added. The bank is re-recorded
with its score without replacing it with a worse experiment.

Read `../canmake-early-cleanup-20261022/readme.md` for both 216 B regional
winners and `../canmake-priority-context-20261022/readme.md` for conflict and
colouring evidence. The bank still uses EBX rather than ESI for failure
returns and tests status 7 before status 0. Retail's extra two-byte default
jump is absent, shifting success cleanup and the epilogue two bytes earlier.
All bytes through +0x83 are exact. The saved 223 B ESI alternative still
retains redundant value arithmetic and places failure cleanup too late.

## New phase evidence

The previous handoff observed allocation after priorities existed. These
read-only traces locate their construction inside c2 build 3077:

- Before the call at c2+0x83ac8 to +0x82473, both return-related records have
  raw priority word 3 = 0. At +0x83acd, before first colouring, they already
  have the final initial priorities: bank 8, ESI control 36.
- A hardware watchpoint on record+0x0c observes every priority write during
  that call. Nothing writes compiler data or patches emitted instructions.
  The compiler module digest is recorded in `receipt.json`.
- The bank's raw word-3 sequence is **0, 1, 2, 3, 5, 7, 8**. The ESI control's
  is **0, 1, 2, 3, 30, 34, 36**. Thus the difference is present before later
  range splitting, rather than created solely by it.
- The large ESI contribution occurs in one block: raw local-use word 6 = 9,
  EDX multiplier = 3, contribution 27 at +0x83a56. The analogous bank
  contribution has word 6 = 1 and multiplier 2. The code multiplies word 6
  by EDX and adds it to word 3. These are observed arithmetic facts; a full
  interpretation of c2's anonymous records is not established.
- A second watchpoint on record+0x18 shows the ESI block's word 6 changing
  0 -> 3 -> 6 -> 9. Contributing tuple word 1 values are 0x1ad and 0x2e;
  their raw tuples/operands are preserved. Their relation to the emitted
  conditional value arithmetic is inferred, not an independently decoded
  opcode table. The bank's corresponding contributions are ordinary
  word-1=1 tuples with weight 1.

`allocator-observations.json` preserves initial tables, transitions, registers,
stacks and relevant tuple words. Record index 10 is the bank's return-related
record; index 11 is the ESI control's. Their identification follows the prior
colour trace and final register correlation, not a decoded source-local name.

The earlier call at +0x83ab7 to **+0x844a4** supplies a direct bridge
between those observations and the source experiment. `ir-tables.py.txt`
snapshots source/destination operands before and after that call:

- Both cases have 17 observed IR blocks. The bank keeps all 111 tuples. The
  ESI control goes from 114 to 113, deleting one opcode-1 copy tuple.
- Before the call, the ESI control's 0x1ad/0x2e arithmetic operands belong to
  their own temporary identity. A following copy reads that identity and
  writes the shared failure-return identity.
- After the call, that copy is gone. Both arithmetic tuples' relevant operands
  point to the shared return record; the AND destination also names its symbol.
  The later priority pass therefore charges their uses to the same record as
  the literal 9/2 returns. This is observed coalescing inside +0x844a4, not a
  complete decoding of all that call's responsibilities.
- The bank has no corresponding arithmetic-copy join. Its return record
  receives plain opcode-1 moves. Its extra 0x1ad tuple belongs to the earlier
  quote-result/flags calculation, not this return record.

`join-observations.json` preserves the relevant tuples and both source and
destination operand lists. Its raw pointers are run-local observations. The
operation identification is supported by the isolated control's emitted
`sbb esi,esi; and esi,2`; no general c2 opcode table is asserted.

All twelve ordinary/traced control objects reproduce their expected masked
body hashes and pass `eh_verify.verify_row` **EXACT**. The ESI control remains
223 B, hash `cee9ad3381596a8b9ccaf90853784474f08e8fba700151736cb48a163c332648`.
A failed untyped Wine watch expression was corrected to `watch *(int*)addr`;
only the successful typed-watch observations are retained.

## Completed source experiments: do not repeat unchanged

There were **3,948 final trials**, zero compiler errors, zero unresolved
main-body relocations and zero exact candidates. Scores and private relocation
patching are diagnostic, not the repository's byte/identity acceptance gates.

| Family | Trials | New interaction and finding |
| --- | ---: | --- |
| `arithmetic` | 768 | Thirty-two Boolean-dependent arithmetic return forms at four failure sites, direct/local predicate storage, both 216 B contexts and the 218 B success-tail control. Some select ESI with retained arithmetic; none produces early ESI cleanup. |
| `predicate` | 672 | Value/reference/pointer/result-reference status storage, predicates before/after the failed guard, Boolean/integer predicate types and order, four joined status conditions and both label orders. Best is the existing other 216 B regional shape. |
| `profiles` | 144 | RTM, hash-pinned SP1 and DDK-4035 profiles, Og/Og-, Os/Ot, Ob1/Ob2 and Gy/Gy-, combined with both 216 B contexts and the saved ESI control. No improvement. |
| `induction` | 720 | Actual executable induction latches, not the preceding seat's first-iteration returns: up/down loops, 1/2/4 iterations, signed/unsigned counters and ten accumulator shapes at all four failures. No improvement. |
| `backedge` | 300 | Conditional backedges without an executed latch on the proved path: empty waits, conditional break/return, and unreachable updates. Three starting contexts; deduplicated source count shown. No ESI return variant. |
| `mask-identities` | 576 | Twelve mask/shift/arithmetic identities, shifts 4/8/12, both 216 B contexts, four failure sites and local/direct predicates. Intended to retain value dependence through allocation and simplify afterward. No ESI return variant. |
| `dead-value` | 768 | Place conditional return arithmetic in the unreachable zero arm of the late-folding insufficient-funds shape: eight branch/loop/switch forms, twelve expressions and four predicates, both 216 B contexts. Only eight emitted bodies; no improvement. |

One arithmetic formula initially failed the intended identity for return 2.
It was corrected and its 24 affected combinations recompiled. The receipt
and saved full-family driver use those corrected results; the superseded
24 diagnostics are not counted. All arithmetic/loop experiments execute only
where the enclosing condition proves the needed predicate. No production
volatile, exception, class-layout or naming contract is asserted by a trial.

This builds on, rather than repeats, the prior control-flow, variable lifetime,
layout/type, callee visibility and compiler-setting trials. The WB twin was
reread: 24-byte quote, 12-byte position temporary, five return homes, and nested
status tests remain the existing evidence. The matched BuildAssistant ctor and
its quote view were checked again; no new target layout or donor identity was
established. There is no demonstrated missing-function prerequisite.

## Reproduction and next investigation

Run from the repository root:

```sh
python3 reverse/attempt_support/canmake-precolour-20261022/replay.py.txt --list
python3 reverse/attempt_support/canmake-precolour-20261022/replay.py.txt dead-value
```

Drivers use the preceding handoff's frozen 204 B starting input and generated
regional contexts; all outputs are private `build/` objects. No call uses
`build.compile_source` or overwrites the production object cache. The seven
full result tables remain reproducible; receipt digests and compact summaries
are tracked instead of thousands of diagnostic sources/objects.

Generate the two trace inputs with the previous handoff's `funds_after` and
`esi` replay modes. `phase-trace.py.txt INPUT.cpp OUTPUT.obj` observes priority
construction and insertion. `priority-watch.py.txt INPUT.cpp OUTPUT.obj INDEX`
observes priority writes; `uses-watch.py.txt` takes the same arguments and
observes local-use writes and contributing tuples. Use index 10 for the bank,
11 for ESI. `ir-tables.py.txt INPUT.cpp OUTPUT.obj` snapshots pre-priority
source/destination tuple lists across +0x844a4. These offsets are specific to the recorded RTM c2 module.

The copy-join step is now located; do not repeat that observation as the
next experiment. A concrete next investigation is to trace **construction of
these alias/return records before +0x83aac**, or inspect the move-join criteria
inside +0x844a4. Compare the two 216 B regional contexts and the 223 B ESI
control. Determine whether a source-visible copy/lifetime relationship can
retain first-round return allocation without retained arithmetic. The new
identities and unreachable-value arms above fold too early or keep unwanted
instructions. Identify a transformation order before choosing another family;
repeating redundant uses, loop wrappers or arbitrary scopes is not a new
hypothesis. Keep both regional winners and the ESI control.

## Checks and session handoff

Initial pull/rebase was current. `check_csv.py` passes (98,069 functions,
15,856 symbols, 2,131 data rows). The home's declared-definition check passes;
`./build.sh AIBuildableWallSegment.cpp` passes 2/2 existing bodies plus source,
string, float and import checks. Published link-index fetch completed; no
maintainer-only runner was started. All saved diagnostic scripts parse.

BFME 1 remains at verified pointer `42bba2ddbd5cb895d99293583891d3b7315fa49e`.
Freshness was due but deferred under the live foreign update lock owned by
`claudec2`, as the runner requires. No success timestamp was written. The
standing assignment overrides broad sweeps and alternate queues.

The claim is released after this handoff is committed. Reclaim this same
unfinished body next session. No failed reconstruction was put in `Code/`;
no source, symbol pin, gate, baseline or class contract changed.
