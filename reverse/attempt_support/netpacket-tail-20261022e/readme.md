# NetPacket::getCommandList: late merging and loop-entry evidence

2026-10-22, gpt-6-astra, codexb2. Continue **only 0x00593F15**.
The accepted bank is unchanged: **7 resolved differing bytes / 1475**, no
unresolved relocations, EH **EXACT**, agreement **0.9952542372881356**.
This session generated 13,702 variants, scored 12,972, and found no exact body.
442 trials crossed the declared extent at a REL32 relocation; 288 generated
`continue` outside a loop and correctly failed C2044. These are unsuccessful
trials, not verifier false rejects. No production source, ledger, pin, gate or
compiler binary was changed. Do not land this body yet.

Inputs: BFME2 `3b035ec21a` (full revision, compiler command and DLL digest in
`measurements.json`), BFME1 `37c3022de1ab944c7ffe536440d637dc8199091c`.
Pull, check_csv and published-index fetch passed. BFME1 updating was skipped
because the active runner lock belonged to claudeb3; no success stamp was
written. The current home unit passes **162/162**, string, float and import
checks, and `find_declared_unmatched`. A fresh private bank compilation and
normal `explain_mismatch.py` reproduce +0x508 as the first difference.

## Bank and exclusions

Extent is **0x593F15..0x5944D8**: 1351 code bytes plus the 124-byte switch table.
The picker's 1351-byte size is stale. Bank resolved SHA256:
`c2f50c1fb2afd479eb03ce479f505d004ac98a5251c0efa07836076007cf838c`.
Permutation fitness, a different metric from byte agreement, is
0.9980172808694141. Retail Z completion restores EBX (`this`) from `[ebp-2c]`
then jumps backward to D's ESI cursor restore from `[ebp-14]`. The bank
restores ESI then EBX and jumps directly to the loop comparison. Everything
outside those seven bytes, including the switch table, matches.

History was read using `pick-hard --rva`, with the 20261020, 20261022, 20261022b, 20261022c and 20261022d
handoffs. Do not repeat their ordinary loop/tail/declaration meters, throw
factorials, real-home/provider visibility, single-index/cursor aggregate,
ABI/helper, EH-lifetime and compiler-profile trials. They cover control flow,
variable lifetime, types/layout, callee visibility and compiler settings.
No missing-function prerequisite is known. This session tests a new shared
explanation: predicates and duplicate actual calls can survive until after
allocation and change the location of a reload before their blocks merge.
The lead is the Locomotor recovery `559df2d80f7a19bd9d2ae40cd64954533e927bdc`
and the late-merging recipes in `docs/recipes.md`; no donor identity is inferred
from that compiler behavior.

## New result worth continuing

**`bedge_0040` gets the precise tail order and backward sharing.** Its patch is
preserved separately; it does not replace the better full-body bank. Starting
from the bank, put `packetLoopHead:` immediately before the while loop and
replace only Z's final cursor copy with:

```cpp
if (m_packetLen & 1) { i = offset; goto packetLoopHead; }
i = offset;
```

Both paths have identical semantics. The compiler deletes the predicate late.
The resulting body is 1465 bytes, with these instructions:

```
594414 call detach
594419 mov ebx,[ebp-2c]
59441c jmp 594267
...
594267 mov esi,[ebp-14]
59426a jmp 593f79
```

The meaningful structural difference is **loop rotation**. Its initial guard
is replaced by a top test at 593f79 and its bottom compare/jl by a jump there.
Mnemonic alignment finds those three regions; other parser instruction operands
agree after adjusting addresses. The top test also shifts code and table
relocations. EH placement reports `reloc_conflict: two placements for .text`.
Do not treat this as an exact candidate or patch machine code. The scorer
fills `__except_list` from the retail offset; when lengths differ this makes
that resolved epilogue operand misleading. Inspect the object's raw zero
operand when interpreting assembly, while retaining the normal gate result.

Read-only C2 tracing explains the improvement. Bank's final `this` reload was
an edge-compensation insertion (caller 0x1078BB3F) after the cursor assignment.
In this variant, it is a **per-reference reload**, caller 0x1078ADD4 at
function-relative source line 227, tuple opcode 0x33 with the `this` operand,
for the surviving packet-length predicate. This precedes the cursor copy.
The compiler later removes the predicate and shares the cursor-restore tail.
The traced object and ordinary private object have identical resolved hashes.

Already tested with this new result: 16 explicit loop/latch forms, guarded
conditional jumps into the body, and eight separate initial/bottom-guard
forms. Explicit bottom-tested loops revert to the bank's wrong order; separate
guards tend to change allocation. None retained both the desired tail and
retail's loop layout. `dualguard_07002` is merely the old seven differences
plus a changed EH state byte; it is not an improvement. Only one unique
compiled shape across these families has the desired shared tail.

A concrete next angle is to keep the packet-length predicate live through
allocation while allowing the ordinary rotated loop: use this reload-placement
evidence to choose a different late-merging control boundary, rather than
repeating the saved loop-form grid. The regional winner is available to combine
with a genuinely new compiler/source finding. The assignment remains unfinished.

## Trials and allocation findings

| Family | Generated | Finding |
| --- | ---: | --- |
| merged-calls | 576 | Actual detach/ref/require-ID calls duplicated in identical arms; three cursor bases, eight predicates, D/Z/both. Best unchanged. |
| merged-store | 384 | Cursor, detach-through-copy, ref-through-copy and full completion; if/switch/local goto/local next. Best unchanged. |
| merge-factorial | 6138 | Six 1023-mask families: ten independent D/Z call boundaries, reader calls, ACK construction, six headers and addMessage; bank/single/live-Z cursors and two selectors. No improvement. |
| union-cursor | 96 | Overlapping cursor names, direct/nested/array layouts and copies. All collapse to the same ordinary single-index shape. |
| header-weight | 756 | Four predicates and every nonempty mask of six header copies, three cursor bases. No improvement. |
| depth-probes | 8 | Nested duplicated header calls raise the address-taken cursor's allocation weight. |
| header-depth | 1712 | Per-header depths 0/1/2 and one depth-3 arm, single/live-Z cursors. No improvement. |
| backedge-merge | 576 | Six conditional continue/goto forms around four completion spans. Finds regional winner above. |
| loop-rotation | 768 | Sixteen loop forms with eight predicates, two branch polarities, D/Z/both. Correct layout loses tail improvement. |
| body-backedge | 384 | Bound-checked conditional jumps into loop body. Additional comparisons or allocation changes remain. |
| dual-guard | 2304 | Separate initial and bottom guards; completion spans/polarities. 288 invalid continue forms, 2016 scored. No improvement. |

The single-index header-weight probe (mode 1, selector 0, mask 63, depth 1)
raises initial `i` priority from 116 to **159**, references 39 to **51**, cost
-35 to **-11**; it still splits. Depth 2 raises these to **291/75/37** and
avoids the later split, but produces 1537 bytes, worse than the bank.
Read-only coloring shows why weight alone is insufficient: bank `i` has
available registers `[4,7,8]` and gets 7 (ESI); depth-2 `i` has `[1,2,3,4]`
and gets 1 (EAX). These are available registers at that allocation step,
not a permanent architectural constraint. No register-only residue emerged,
so permute was not rerun. Details and independent object checks are preserved.

## Reproduction

Copy the `*.py.txt` files to ignored `build/netpacket-20261022e/`, removing
`.txt`. Run from repository root. `search.py` uses eight private object paths
and normal `compile_function` relocation resolution, never shared-cache
`compile_source`. Run a named generator to reproduce a family; invoke
`merge_factorial.py MODE SELECTOR` for its six combinations. The untouched
bank is its input. `header_weight.source(1,0,63,1)` makes the weight probe;
`depth_probes.py` produces the nested probes. `merged_store` and depth-probe
regeneration were checked against every preserved scratch source.

To inspect the regional winner without rerunning a family, copy the bank to
an ignored `bedge_0040.cpp`, then apply `bedge_0040.patch` to that explicit
scratch filename. Compile privately with the saved search driver.
`inserts.py SRC OBJ`, `trace.py SRC OBJ`, and `color_trace.py SRC OBJ` only read
compiler state using debugger breakpoints; they never patch registers or memory.
Use 18-word candidate records. The tuple decoder must not infer arbitrary call
operand layouts. `observations.json` contains the pertinent records; the full
raw traces remain in ignored scratch. `measurements.json` records all counts,
best scores, errors, inputs and traced-object equivalence checks.
