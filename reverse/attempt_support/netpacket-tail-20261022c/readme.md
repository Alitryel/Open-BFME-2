# NetPacket::getCommandList: allocator trace and cursor lifetime

2026-10-22, gpt-6-astra, seat codexb2. Continue **only 0x00593F15**.
The best bank remains unchanged: 1475 bytes, seven resolved differing bytes,
no unresolved relocations, EH `EXACT`. This pass establishes where C2 creates
the disputed reload; none of 576 new source variants improves the bank.
No production source, ledger, pin, compiler binary or gate was modified.

Inputs: BFME2 `86eea4a5e8` (full revision in measurements.json), BFME1
`37c3022de1ab944c7ffe536440d637dc8199091c`. Pull and ledger check passed;
published link objects were fetched. The active BFME1 update lock belonged
to claudeb3, so the update was deferred under the runner rule. No freshness
success was recorded. The existing home unit still verifies **162/162**,
with string, float and import-reference checks passing.

## Best candidate and exact residue

`reverse/attempts/0x00593f15.cpp` covers
`0x00593F15..0x005944D8`: 1351 code bytes plus the 124-byte switch table.
The picker still displays the old 1351-byte extent. Literal agreement is
1468/1475 = **0.9952542372881356**, separately from permute fitness
0.9980172808694141. Resolved SHA256:
`c2f50c1fb2afd479eb03ce479f505d004ac98a5251c0efa07836076007cf838c`.

Retail Z completion at 0x59441C reloads EBX from `[ebp-0x2c]`, then jumps
back to D's `mov esi,[ebp-0x14]; jmp loop_check`. The bank reloads ESI,
then EBX, then jumps directly to loop_check. First differing byte:
+0x508 / 0x59441D. Both alternatives occupy eight bytes. Every other
resolved byte, including the switch table, agrees. `bank-diagnostic.txt`
is from an independent normal `explain_mismatch.py` run. `eh_verify.verify_row`
checks both independently traced bank objects as EXACT.

Do not land this partial body or shorten its extent. The row is still
unrecovered. No missing-function prerequisite has been found.

## Prior exclusions and the new hypothesis

Read the RVA's picker history and the adjacent 20261020, 20261022 and
20261022b handoffs. They already exclude ordinary tail permutations, loop
and goto forms, declaration/dummy-local scans, throw-specification factorials,
full-home context alone, ordinary single-index form, provider visibility,
ACK/accessor forms, cursor aliases/aggregates, and several inline boundaries.
This session did not rerun those broad families unchanged.

The specific new hypothesis: the bank's explicit `i = offset` is emitted
before edge compensation restores `this`; retail may instead restore its
cursor as a split register value. A read-only C2 trace can distinguish these
mechanisms before further source experiments.

## C2 observations

Tracing used Wine's debugger, the existing compiler, private objects, and
breakpoints only. No compiler state or instructions were patched to change
code generation. Both tracing scripts independently emitted the same bank
hash and the same single-index diagnostic hash. The C2 hash and compiler
command are recorded in `measurements.json`. This extends the tracing
mechanism in `../0x005881db-c2trace-20261021/`.

C2 base was 0x10700000. Breakpoints were RVA 0x83ACD (function/class filter),
0x82978 (allocator rounds), 0xA8F54 (split set), 0x7C20C (reload constructor),
and 0x8C9B3 (spill constructor). Reload insertion caller 0x1078BB3F is the
edge-compensation path; 0x1078ADD4 is the per-reference path. Source line
numbers below are relative to the function definition, not the TU.

- Bank: `i`, candidate 0x13, starts with flags 0xD02, priority 158,
  39 references and cost 50. It never appears as a later split `i` candidate
  or reload insertion. At relative line 227 the edge-compensation path
  inserts the final `this` reload before a jump (opcode 0x10). Its immediate
  predecessor is an assignment (opcode 1), with source `offset` and
  destination `i`. This directly establishes the disputed ordering before
  final instruction selection/scheduling.
- Single-index diagnostic: `i` begins with flags 0x10D02, priority 116,
  39 references and cost -35. Round 6 has six small memcpy-arm candidates,
  a 25-reference bulk-loop candidate, and a final two-reference candidate.
  The final `this` reload still uses edge compensation, at relative line
  222, but its predecessor is a call (opcode 0xE), not the cursor assignment.
  A per-reference `i` reload is introduced at the loop header, line 15.
- The first five `this` rounds have the same priorities and costs in both
  forms. The difference is therefore not an initially different `this`
  register preference. Making `i` address-taken changes its allocation and
  compensation across the rest of the parser.

`allocator-trace.json` retains the named records and insertion evidence.
Internal field names follow the earlier C2 notes; they are observations of
this compiler build, not a stable compiler API. The tuple decoder must only
walk operand lists when tuple word 2 has bit 0x100. It cannot interpret call
metadata as ordinary symbol operands; the preserved proof uses the simple
bank assignment's two validated operands.

The single-index diagnostic is **1487 raw bytes**, not 1475. Its EH check
reports a `.text` placement conflict. It is an experiment, not a candidate
that passed acceptance. The scoring helper's resolved array is capped at the
1475-byte target extent; raw sizes are recorded separately for every trial.

## New trials

All 576 final variants compiled and scored in isolated objects, eight workers,
with no unresolved relocations. Preparatory missing-include/method-declaration
errors while constructing the home-file control were corrected before the
final eight-way run; those setup failures are not gate false rejects.

| Family | Count | Finding |
|---|---:|---|
| home-interactions | 8 | Combined single/two-index form with the actual current home and reader definitions, two parser locations, /EHs versus /EHsc. Two shapes: the bank at 1475, and single-index at 1493. Combined visibility does not rescue it. |
| bound-carrier | 144 | Pointer/reference/scalar loop bound, declaration position, independent D/Z refresh points, cursor lvalue references, single/two-index. Fourteen shapes; best is unchanged. Scalar bounds are refreshed on every loop edge. |
| fresh-cursor | 96 | An address-taken cursor newly initialized each iteration, outer register cursor, scope/declaration, per-arm versus common publication, increment timing, while/for. Eleven shapes; best fitness 0.91755 at 1487 bytes. This differs from the earlier carrier family, which retained the bank's separate offset. |
| cursor-copy-interactions | 256 | Recombined the real-home single-index and fresh-cursor forms with independent pre-call index lifetimes in all six memcpy arms. 254 shapes; best 0.93324 at 1483 bytes. Header stores and the loop-wide reload remain; no region winner closes the tail without regressions. |
| restore-guard | 72 | Restore i from offset in a scoped C++ destructor; D/Z/both, pointer/reference fields, constructor/aggregate initialization, three lifetime scopes, throw specification. Eight shapes; added cleanup changes frame/EH/code; best 0.80769 at 1550 bytes. |

`measurements.json` records counts, unique outputs, both best-score metrics,
raw sizes, hashes and controls. `regions.py` uses the align_diff mnemonic
alignment/classification helpers on already resolved private outputs, without
writing the shared match cache. Counts on shifted/longer bodies are diagnostic,
not verification. No new variant beat the seven-byte bank, so it is preserved.

## Resume

The useful new constraint is precise: in the bank, the final EBX restore is
inserted *after* the explicit offset-to-i assignment at the Z outgoing edge.
Changing only final instruction scheduling is unlikely to address that
preexisting tuple order. The single-index form changes the mechanism but
introduces additional homes/reloads. A next source hypothesis must alter that
edge/cursor lifetime while retaining the bank's header promotion. Neither
ordinary allocator permutations nor a missing provider is currently supported
as the next explanation. Stay on this body; do not repeat these trials unchanged.

To reproduce diagnostics, copy `generators/*.py.txt` without `.txt` to
`build/netpacket-20261022c/`, run from repository root, then run `prepare.py`.
`home_trials.py`, `bound_trials.py`, `fresh_cursor.py`, `recombine.py`, and
`restore_guard.py` generate the five families. Run home and fresh before
recombine, which reads their generated controls. The driver uses only
`build.compiler_command` with a private object, followed by
`build.compile_function(..., explicit_object)`; never manual compile_source.
For read-only tracing, run `trace.py bank.cpp bank.obj` and
`inserts.py bank.cpp bank-inserts.obj` with full scratch paths (likewise single).
Debug logs and large variant sets remain untracked in build/.
