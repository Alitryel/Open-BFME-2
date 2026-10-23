# NetPacket::getCommandList: live Z cursor and remaining callee visibility

2026-10-22, gpt-6-astra, codexb2. Continue **only 0x00593F15**.
The best bank is unchanged: **7 resolved differences in 1475 bytes**, no
unresolved relocations, EH **EXACT**. This session compiled 1176 new variants;
1173 scored and three correctly failed the extent check. No production source,
ledger, pin, gate or compiler binary changed. This is an unfinished assignment,
not a claim that its source hypotheses are exhausted.

Inputs: BFME2 `eb42efa896` (full revision and compiler command in
`measurements.json`), BFME1 `37c3022de1ab944c7ffe536440d637dc8199091c`.
Pull and `check_csv` passed; the published link index/objects were fetched.
The active BFME1 update lock belonged to claudeb3, so freshness updating was
skipped under the runner rule, without recording success. The current home
unit passes **162/162**, string, float and import-reference checks; its
`find_declared_unmatched` check passes.

## Best candidate and prior exclusions

The bank at `reverse/attempts/0x00593f15.cpp` covers
`0x00593F15..0x005944D8`, 1351 code bytes plus the 124-byte switch table.
The picker's 1351-byte display is stale. Agreement is 1468/1475 =
**0.9952542372881356**; permute fitness is separately 0.9980172808694141.
Resolved SHA256:
`c2f50c1fb2afd479eb03ce479f505d004ac98a5251c0efa07836076007cf838c`.
Independent private compilation and normal `explain_mismatch.py` confirm it.

At Z completion retail restores **this in EBX** from `[ebp-0x2c]`, then
jumps to D's **cursor restore in ESI** from `[ebp-0x14]`. The bank does
ESI then EBX and jumps directly to the loop check. First difference:
+0x508 / 0x59441D. Everything outside those seven bytes, including the whole
switch table, matches. Do not shorten the extent or land this partial body.

History was read with `pick-hard --rva`, plus the adjacent 20261020,
20261022, 20261022b and 20261022c handoffs. Already disproven there:
ordinary tail/loop/goto permutations, declaration and dummy-local meters,
ordinary throw factorials, full home alone, one address-taken index alone,
ordinary accessor/ACK/inheritance forms, cursor aggregates and aliases,
copy boundaries, whole-parser helpers, explicit destruction and RAII restore,
and the listed compiler profiles. Those families were not rerun unchanged.

New hypotheses: extract the entire repeated-command arm rather than its
completion; alter the loop latch's cursor/condition lifetime; keep the cursor
live through Z and trace its allocation; expose the remaining reader/list
callees and test definition order before their callers; combine real home
visibility with single-index compiler profiles. These test control flow,
variable lifetime, types/layout, callee visibility/inlining and settings.

## New trials

All used private objects through `compiler_command`, then relocation-aware
`compile_function` with an explicit object; eight workers. No manual
`compile_source` call or shared-cache poisoning. Scoring arrays are capped at
the real 1475-byte extent; raw symbol sizes are recorded separately. Scores
on shifted or longer bodies are diagnostic, not acceptance.

| Family | Variants | Result |
|---|---:|---|
| z-inline | 128 | Whole Z helper before increment/guard or after guard, free/member, bool/pointer result, parameter references, inside/outside cursor publication. All inline; 16 shapes, best unchanged. |
| deep-visibility | 128 | All subsets of actual bodies Rva00592496Read, Rva00592520Read, Rva005922FBRead, Rva005923C5Read and Rva00590D19Add, plain versus inline-noinline, bank/single index in real home. Two shapes: bank 1475, single 1493. The target-backed auxiliary class views preserve allocation sizes and field offsets. No improvement. |
| pointer-latch | 108 | Select &i or &offset at each leaf and load at common latch; local/persistent pointer, independent D/Z forms, selection timing, direct/reference/temporary read. Pointer never escapes into readers. Fourteen shapes, best unchanged. |
| condition-latch | 128 | Saved Bool/Int loop condition, independent D/Z publication order and continue/break, initialization and polarity. Twenty-two shapes; best fitness 0.941646 at 1480 raw bytes. |
| single-profiles | 36 | Twelve optimizer profiles across standalone, actual home and all five extra providers, all using the single-index source. 33 scored, eight shapes; best 0.918603 at 1493. The three /Ot trials have relocations extending beyond 1475 and are correctly refused. No extent inflation. |
| live-cursor | 256 | Retain/omit Z offset store and copy-back; D-local offset; cached byte/byte-reference/uint tag; ACK if/switch; message scope; combined increment; bound reference. Twelve shapes; best bank unchanged. Diagnostic live_210000 gets the cursor split but regresses frame, header code and EH. |
| clone-scope | 288 | Three typed inline ACK cloning helpers; bank/live cursor, tag cache, previous-ref value/reference, last-message capture before/after allocation, return/out parameter, base/typed local and index initialization position. Twenty-four shapes; best 0.885535 at 1484. All final variants compile and resolve. |
| list-visibility | 80 | Actual list ctor/reset/addMessage subsets, ordinary/noinline, standalone and home bank/single plus live cursor. Fourteen shapes, best unchanged. Reset retains the verified node layout/detach/delete semantics; addMessage has its real comparator and virtual sort-number declaration. The ctor's existing explicit-vtable view is scratch evidence only. |
| provider-order | 24 | Move the five extra provider bodies before all home definitions, before readGameMessage, or before getCommandList; reverse their order; bank/single and plain/inline-noinline. Two shapes, same as deep-visibility. Earlier definitions do not remove the single-index regression. |

An initial clone-helper prototype omitted the explicit base-pointer cast
required by the bank's non-derived ACK views: 144 setup compile errors were
fixed and rerun. The table counts the 288 corrected variants once, not those
failed prototypes. This was not a gate false reject. All 1173 scored variants
have no unresolved relocations. `measurements.json` retains both best literal
and best alignment scores, sizes, hashes and refusal messages for each family.

## C2 trace: evidence and limits

`live_210000` removes Z's offset store and copy-back while retaining D's
separate offset, and caches the tag as an unsigned int. `live-cursor.patch`
is its complete delta against the bank. It is **1515 raw bytes**, with
1261 literal differences in the capped comparison, and EH differs by six
bytes at `.text$x @0x79D139`. It is not a better bank. Both independent traced
objects have resolved SHA256
`90654f8810e3c50c20875599ae0eb83f1525f99a9af02175f0e72543de9631a3`.

The Wine debugger used breakpoints only, as in the previous handoff; no
compiler state or instructions were patched to influence code generation.
C2 base 0x10700000, allocator/split/reload/spill breakpoints and field decoding
are documented in 20261022c. Named records retain only the first 18 valid
record words; trailing allocation contents are not evidence.

- Bank, from the preceding trace: i has initial priority 158, 39 references,
  cost 50 and no split/reload request. Its explicit offset-to-i assignment
  precedes the final this edge-compensation request.
- Live variant: initial i priority **58**, 39 references, cost 45; round 2's
  i piece has flags 0x10D02, priority 78, 39 references and cost 39. It now
  spills at relative line 170 (Z increment), caller C2+0x3F0B2.
- At relative line **195**, inside the **ACK0 branch**, edge compensation
  calls the reload constructor for **this, then i** (caller C2+0x8BB3F),
  both against a block-end tuple, opcode 0x2C4. This is an insertion-request
  order, **not proof of a contiguous machine-code reload pair**.
- Actual output restores i into **EBX** at 0x5943A6 amid ACK0's field copies.
  It reads this from `[ebp-0x30]` into **EAX** at the common loop check
  0x59444C. The Z completion itself has no cursor reload. `live-tail.txt`
  preserves these emitted instructions. The bank's EBX/ESI roles differ.
- Stack slot -0x24 holds the live cursor on ACK0 but is reused by constructor
  temporaries on other branches where i remains in EBX. These disjoint
  lifetimes are not a corrupted cursor or compiler defect.

This establishes a real change from an explicit cursor assignment to a split
cursor, but the split edge and allocation are wrong. Neither provider order
nor the tested ACK helper lifetimes moves it to the desired final edge.
A focused next investigation can inspect the live i piece's interference
neighbors at ACK0 versus the final detach, then choose a source change from
that evidence. The present trace records rounds and insertion requests,
not that interference graph. Do not treat a trace request order or a capped
score as matching output. No missing-function prerequisite was found.

## Reproduction and handoff

Copy `generators/*.py.txt` without `.txt` into
`build/netpacket-20261022d/`, run from repository root, then `prepare.py`.
It constructs bank/single and home controls directly from tracked inputs;
no older ignored scratch directory is required. Run `deep_visibility.py`
before `profiles.py` or `provider_order.py`; run `live_cursor.py` before
`list_visibility.py`. Other families are independent. `clone_scope.py`
generates the corrected full family in one run. Use the exact input revisions
in measurements.json when reproducing historical scores.

For read-only traces, run `trace.py` and `inserts.py` on live_210000.cpp with
separate private object paths. Large raw logs and generated variants stay in
ignored build/. Bank, claim release and structured runner outcome accompany
this handoff. Continue this assignment next session; do not move to another
body or repeat these families unchanged.
