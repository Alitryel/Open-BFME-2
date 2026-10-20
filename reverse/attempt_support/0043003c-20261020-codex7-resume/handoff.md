# SelectionTranslator::translateGameMessage, continued 2026-10-20

Only the previous session's unfinished fallback, 0x0043003C (4054 bytes), was
worked. Its claim was acquired before trials. Start from the updated
`reverse/attempts/0x0043003c.cpp`, score 0.98. The earlier handoff in
`../0043003c-20261020-codex7/` still supplies identity, WB evidence, the
contained-object fix and the five callee-admission prerequisites.

## Improvement and exact residue

The previous bank emitted 4050 bytes with three structural regions and four
nonbranch operand differences. The new candidate `w22_01` emits **4054 bytes**,
with **zero structural regions and two operand differences**. Independent raw
comparison leaves only five differing bytes outside 184 COFF relocations:

| Offset | Retail | Candidate |
| --- | --- | --- |
| +C6A | `mov eax,[ebp-10h]` (requested group) | `mov eax,[ebx+0Ch]` (saved group) |
| +C6D | `cmp eax,[ebx+0Ch]` | `cmp [ebp-10h],eax` |

The differing byte offsets are C6B, C6C, C6D, C6E and C6F. Relative branch bytes
outside relocations agree. `build.body_extent_problems` reports no jump-table,
tail or truncated-extent problems. This does **not** admit external callees or
prove a full byte match. Retained raw, alignment and extent reports are beside
this note. The real boundary remains 0043003C..00431012, ending in RET4 at
0043100F.

The sole source change is in the case 62..71 double-tap arm: pass
`m_lastGroupSelGroup` rather than `group` to rva002AA176. The dominating equality
proves these values equal. Between the comparison and the argument evaluation,
`localPlayer43003C()` only reads ThePlayerList+10h; there is no intervening
mutating call. This is an equivalent reconstruction, not a claim that the
original source used this spelling. The change splits the requested group's
live range and restores retail's EAX push, PlayerList ECX load, and normal-arm
ESI reload after deselection. MSVC instead keeps the saved group in EAX for the
comparison. No padding, inert locals or inline assembly was added.

## New trials and disproven explanations

The prior history and linked handoffs were read first. These trials begin from
the earlier 4050-byte bank, with its original flags and declaration context.
Each generated source compiled to its own object using compiler_command;
build.compile_source and its shared match cache were never called manually.
The ten completed families contain 1024 successful diagnostic compiles.
`receipt.json` preserves every outcome count; the generators reproduce them.

| Family | New interacting choices and result |
| --- | --- |
| 15, 128 | Direct invalidation vs Bool validity; final store order; long group; Int validity; raw state offsets; const count and != loop. No improvement. Store reversal and != loop worsen. |
| 16, 128 | Nested/duplicated normal arms, reordered test tree, goto join, Boolean temporary/switch; negated conditions; direct invalidation; store order. No improvement. |
| 17, 64 | Real inline bodies for six NativeUI virtual getters, independently combined. All baseline. Offsets were read from retail's base vtable at RVA7FD410: +570 frame, +568 count, +20 list, +7F8 scrolling, +238 command, +810 quit. |
| 18b, 64 | Extract validation into forceinline helper; group value/ref/pointer, signedness, time value/pointer, parameter order, Bool/direct invalidation. A 4058-byte diagnostic fixes the first comparison region but introduces a saved-time preload and wrong normal-arm allocation. Not bankable. Pointer-time controls restore baseline. |
| 19, 64 | Object::getDrawable inline/noinline bodies at native +84; real noinline Player squad getter (+708 indexed slots, range 0..9); direct invalidation; virtual frame getter; vector ref/pointer alias. No improvement. Body visibility often changes many other regions. |
| 20, 64 | Separate virtual frame result as helper parameter, explicit preceding statement vs call argument, time pointer/value, group ref/pointer and argument order. No improvement. Explicit getter-first forms test the saved-time preload explanation without reordering that read. |
| 21, 192 | Final-store inline setter, all 24 argument orders; pointer/ref destinations, value/const-ref sources, void/unused Int return. Every body is the original 4050/3/4. |
| 22, 64 | Equality-proven saved-group argument in true arm; comparison order, direct invalidation, long group, Int validity, elapsed helper. **Saved-group argument with Bool validity fixes structural regions.** Direct invalidation interacts badly (4062/6/20); retain Bool validity. Sixteen winners are 4054/0/2. |
| 23, 128 | On the new arm shape: equality helper Bool/Int returns, ref/value parameters and argument order, direct/early-return equality; argument from member/local snapshot/assignment to group, direct invalidation. Helpers and snapshot retain 4054/0/2; assignment adds a store; direct invalidation worsens. |
| 24, 128 | On the new arm shape: group const/ref/register/unsigned/enum declaration, copied reference; equality-proven bitwise/narrowed/algebraic arguments; Bool/direct validity. No improvement over w22_01. |

Initial family18 placed its helper before localPlayer43003C's declaration and
failed all 64 scratch compiles. Corrected 18b replaces it; these were generator
errors, not gate false rejects. In 18b, passing time by value reads the field
before the virtual getter. That reordered read, and cached group-value controls,
are counterfactual diagnostics only. Never bank them based on region count.
The native leaf bodies used for family19 were checked at RVA5508E2 (7 bytes,
Drawable +84) and RVA2AA176 (27 bytes, Player slots +708).

Control flow, lifetime/scope, types/layout, callee visibility/inlining and compiler
settings were concretely tested across this and the prior session. These new
findings narrow the remaining allocation question; do not repeat unchanged
families. A next hypothesis should explain why retail chooses the requested
group as the equality value while avoiding its PRE hoist into ESI.

## Reproduction and handoff

Run from the repo root:

```
python3 reverse/attempt_support/0043003c-20261020-codex7-resume/reproduce.py
python3 reverse/attempt_support/0043003c-20261020-codex7-resume/reproduce.py --family 22 --name w22_00 w22_01
python3 reverse/attempt_support/0043003c-20261020-codex7-resume/reproduce.py --family 18b --name w18b_01 w18b_17
```

The default freshly compiles the current bank. Other families reconstruct the
session's exact input by undoing only the new argument and re_log prefix, with
an input SHA256 assertion. Outputs stay under build/. Use --list to inspect a
family without compiling. The shared diagnostic implementation is the prior
tracked reproduce.py. The metric skips branches and masks relocations; the new
wrapper also reports every unmasked byte and calls the normal extent/table
checker for 4054-byte bodies. These probes are not substitutes for build.sh,
callee identity, pin admission or link acceptance.

The five unresolved callee bindings remain: deselectAll 42F9DA, integer-map
constructor 43001D, subscript 42FE40, destructor 42FD1C and _M_find 2888D4. Do
not pin them merely by call position. /EHs still emits the 57-byte destructor.
No production source, function ledger or pin ledger changed. The retained
parent remains outside Code/ until exact bytes and those admission checks pass.

Session checks: pull --rebase completed, check_csv passed (97406 functions,
15961 symbols, 1120 data), and the bank and selected controls were freshly
compiled. BFME1 stayed at 92f6bbe8e1dcdb46b5d27da0674313efc822b790. Another
seat (claudeb2) owned the live shared update lock, so this seat skipped updating
as instructed and did not certify freshness. AGENTS.md was unchanged and under
24 hours since its last read. No broad sweep, other target or maintainer-only
verification runner was started. Final acceptance and publication results are
recorded in the session report.
