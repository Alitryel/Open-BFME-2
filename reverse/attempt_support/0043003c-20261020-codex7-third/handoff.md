# SelectionTranslator::translateGameMessage, third continuation 2026-10-20

Continued only the previous session's 0x0043003C fallback (4054 bytes), after
claiming it. The prior handoff, `../0043003c-20261020-codex7-resume/handoff.md`,
remains the starting point. The best body is unchanged at score 0.98; do not
replace it with any diagnostic here. No production source, function ledger or
pin ledger changed.

## Retained body and remaining work

The current bank emits 4054 bytes with zero structural regions and two operand
differences. Outside 184 COFF relocation fields, exactly five bytes differ:
C6B, C6C, C6D, C6E, C6F. Retail loads the requested group from [ebp-10h] into
EAX and compares against [ebx+0Ch]; the bank loads that saved field into EAX
and compares against the requested stack value instead. All other unmasked
bytes, including relative branches, agree. The exact boundary is still
0043003C..00431012, RET4 at 0043100F. Fresh raw, alignment and extent reports
are retained here. These are diagnostic checks, not a full-byte acceptance.

The five unresolved callee admissions remain 42F9DA (deselectAll), 43001D
(integer-map constructor), 42FE40 (subscript), 42FD1C (destructor) and 2888D4
(_M_find). Do not add duplicate real names or infer identity from call positions.
The first is currently owned by ScriptActions::Rva0042F9DAEmit and has a prior
receiver repair plus a live ScriptActions caller; its identity/callers need
reconciliation rather than a casual rename. The STL calls need whole-body,
relocation and owner proof under the current fold-pin rules. /EHs still gives
the required 57-byte destructor. These are prerequisites of this same parent,
not separate queue work.

## New evidence and trials

All families start from the improved 4054-byte bank (SHA256 before this
session's re_log prefix:
9a4702f3c6fc22a564c3d7e800f8b6545051faf779eb5e64755074a77f363eb1).
The ten families completed 770 successful diagnostic compiles.
Families 26 and 34 revisit ideas that previously ran only on the older
4050-byte bank; their allocation context has changed. The bank itself is not
changed. Every scratch source compiles to its own object; no manual call to
build.compile_source or shared match-cache compilation was used.

| Family | Evidence-backed question and outcome |
| --- | --- |
| 25b, 64 | Compiler symbol/temporary numbering: 0..63 initialized unused local controls. All 4054/0/2. Diagnostic only, never bank. |
| 26, 192 | Recombine the prior six real NativeUI virtual getters, native Object::getDrawable and Player squad getter bodies, validation-helper/frame-result shapes on the improved bank. Best remains 4054/0/2. Body visibility can worsen unrelated regions. |
| 27, 80 | Twenty equivalent equalities through direct/value/ref helpers: subtraction, XOR, complements, negation, range relations, Boolean selections and widened comparisons. Some reduce operand-difference count while adding instructions; none improves the whole body. |
| 28, 64 | Independently isolate the normal-arm group uses through pointer/ref/value loads and signedness, with saved-vs-requested true-arm arguments. Saved argument remains 4054/0/2; requested argument returns 4050/3/4. |
| 29, 64 | Embed the actual SelectionXlat declaration, signed long saved field, guard vs inner group scope, declaration/assignment split, signed long local, argument choice and final-store order. No improvement. |
| 30, 128 | WB local-order evidence: scoped deselection, forceinline free/static wrappers, Player predeclaration, squad split declaration, Bool/Int validity, argument choice and final-store order. Best remains 4054/0/2. |
| 31, 64 | Sixteen true-arm argument selections through direct/local/value/ref helpers, including equality-proven conditionals, signed-range selection and saved-field pointer/ref. Best remains 4054/0/2; select expressions can add branches. |
| 32, 64 | Diagnostic compiler assumptions for facts already proven by the guard and equality, independently combined with argument choice. These are not proposed source. No improvement. |
| 33, 18 | Selection ID-set key type: int/long/unsigned variants/ObjectID enum, real hash<int> vs default, and true-arm argument choice. No improvement. |
| 34, 32 | Single-element STL equal/find/count and memcmp, both argument orders, inline-ref wrapper and active /Oi setting. No improvement. |

WorldBuilder's unoptimized frame assigns normal-arm Player at 334 before the
deselection message at 338, then squad at 33C, objects at 340, count at 344,
iterator at 348. In the instructions the deselection message is emitted before
Player is assigned. This is consistent with an inline helper or nested local
scope, rather than requiring the Player assignment to move across the calls.
Family 30 tested that inference concretely without changing call order. The
other frame offsets remain in the earlier handoffs. Source-local order is
inferred from this debug build, not independently established retail BFME2
source identity.

Family25's initial generator created unused-variable C4189 errors in 63 of 64
scratch sources. Corrected25b initializes and casts each local to void. This
is a generator error, not a verifier false reject; the failed controls are not
counted as completed compiles. Family33 initially failed ten scratch compiles because MSVC 7.1 requires
spacing between nested template closing brackets. Only those ten were rerun
after correction; the other eight successes were reused. These failures also
are generator errors. Family26's time-by-value helper may reorder a
saved-time read before a virtual call; those are diagnostic controls only.

These trials concretely cover control flow, lifetime/scope, types/layout,
callee visibility/inlining and compiler settings on the improved bank. Do not
repeat them unchanged. The next hypothesis must explain the requested-group
EAX choice without restoring its premature ESI hoist. Reconcile the remaining
callee ownership/fold proofs as concrete prerequisites of this body where
useful; keep the parent outside Code/ until exact and admissible.

## Reproduction and checks

From the repository root:

```
python3 reverse/attempt_support/0043003c-20261020-codex7-third/reproduce.py
python3 reverse/attempt_support/0043003c-20261020-codex7-third/reproduce.py --family 30 --name w30_001
python3 reverse/attempt_support/0043003c-20261020-codex7-third/reproduce.py --family 31 --list
```

The default freshly compiles the retained bank and writes raw and extent
reports under build/. Other families assert the exact starting-body hash,
removing only later re_log comment prefixes. Generators are preserved here;
family26 composes the previously tracked 17/19/20 generators. receipt.json
records counts and exact inputs. The metric masks relocations and ignores
branches; the retained-bank raw report separately checks every unmasked byte,
and the extent checker checks jump tables and tails. No full match is claimed.

Startup pull --rebase and check_csv passed (97407 functions, 15962 symbols,
1120 data). AGENTS.md was unchanged and less than 24 hours from its last read.
BFME1 stayed at 92f6bbe8e1dcdb46b5d27da0674313efc822b790; the live shared
update lock named claudeb2, so this seat skipped updating as instructed and did
not certify freshness. No broad sweep, other target or maintainer-only runner
was started. Final progress and normal commit-hook results are in the session
report. The claim is released for a safe continuation of this same task.
