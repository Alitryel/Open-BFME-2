# Drawable shroud: a register-correct split-tail control

Resume only `?onComingOutOfShroud@Drawable@@AAEXXZ`, RVA 0x0027893E,
747 retail bytes. Preserve `reverse/attempts/0x0027893e.cpp`, score 0.995.
Fresh ordinary `explain_mismatch` and complete-symbol comparison still give
748 B / 220 instructions, with one actual difference at instruction 201,
+0x2BA: `mov ecx,[ebp-0x10]` instead of retail's `mov ecx,edx`. Branch target
instruction indices agree. The initial positional diff at +0x35 is the shifted
branch displacement, not another defect.

This session found useful regional evidence, but no improved eligible bank or
match. No Code, ledger, pin, compiler setting or verifier change is claimed.
Keep the exclusions and causal cost evidence in
`../drawable-shroud-allocator-cost-20261022/README.md` and its linked handoffs.

## New ordinary source control

Start with genuine separate revealed/shrouded notification tails, then replace
both bit-6 clear predicates with unsigned OR comparisons:

```
(m_status | ~0x40U) != ~0U
(castleDraw->m_status | ~0x40U) != ~0U
```

The result is **757 B / 224 instructions**, with every other register and stack
slot agreeing with retail, including the final `mov ecx,edx`. The only differing
instruction regions, after masking actual relocations and checking aligned
branch targets, are these two predicates:

| Retail offset | Ordinary variant | Retail |
| --- | --- | --- |
| +0x18F | `mov eax,[esi+0x114]; or eax,-65; cmp eax,-1; je ...` | `test byte ptr [esi+0x114],0x40; jne ...` |
| +0x220 | `mov eax,[eax+0x114]; or eax,-65; cmp eax,-1; je ...` | `test byte ptr [eax+0x114],0x40; jne ...` |

Each expanded predicate costs 5 B and two instructions. This is a region
winner, not a better whole-body bank. The mixed algebra controls reach 755 B
with different bit-test encodings; none is exact.

`native_or.patch` reproduces the clean control directly from the unchanged
bank. Copy the bank to `<scratch>/native_or.cpp`, then from the repository root
run `git apply --unidiff-zero --directory=<scratch> reverse/attempt_support/drawable-shroud-mask-order-20261023/native_or.patch`.
The clean replay's full raw symbol **and relocation list** equal the original
matrix winner and both passive trace objects. Their SHA-256 and detailed
instruction differences are in `observations.json`.

## Passive allocator observation

Use the pinned MSVC 7.1 C2 and the previous handoff's passive `trace_colors.py`:

| Ordinary source | 0x80 candidate +0x0C field | Holder +0x0C field | Order |
| --- | ---: | ---: | --- |
| Common-tail bank | 10 | 13 | holder before mask |
| Original split-tail control | 14 | 13 | mask before holder |
| New split-tail OR control | 12 | 13 | holder before mask |

The new mask candidate still has refs=5, cost=1 and allowed register ID 4
(EBX); the holder still has refs=9, cost=15 and allowed IDs 4/8 (EBX/EDI).
The new holder is coloured EDI. These are measured record fields and order;
the full formula producing +0x0C has not been decoded. Do not equate that
field with cost at +0x40. The previous session's diagnostic cost intervention
is still ineligible and was not repeated here.

A second passive trace reads record +0x14: it points to the next candidate
record, not to a neighbour bitmap. The holder points to candidate 7, and
candidate 7 points to candidate 11. `trace_header5.py.txt` preserves that small
probe; copy it and the previous handoff's `wdbg.py.txt` as `.py` into scratch.
Its output object also equals the ordinary control, including relocations.
An exploratory attempt to interpret +0x14 as a bitmap failed on invalid memory;
it supplied no compiler or source evidence and must not be repeated.

## Finite source trials

All 3,848 generated sources compiled, in private objects with eight workers.
3,813 scored normally. The other 35 correctly hit the existing REL32 extent
check because their variant's relocation extends past the real 747 B row;
these are not false rejects and do not justify changing the extent. No exact
or improved eligible whole-body result. Counts include equivalent outputs.

| Generator family | Trials | Finding |
| --- | ---: | --- |
| `mask_cost` | 256 | Kind-47 spelling, bit-6 algebra, mask sharing/types; new OR control above |
| `guard_cost` | 256 | Final guards: if/switch/loops/conditional, cached predicate types, unsigned dead-bit forms; best unchanged |
| `whole_inline` | 192 | Free/member whole-body helpers, parameters/depth; even forceinline leaves a wrapper and unresolved helper |
| `successor` | 512 | NetPacket shared-successor recipe: 8 real predicates, four tail stages, edge forms and declarations; 24 extent refusals, best original split state |
| `status_algebra` | 576 | 24 equivalent bit-6 predicates independently at both sites; best 755 B, wrong predicates |
| `status_inline` | 512 | 16 value/reference/char/member/template/enum accessor forms independently at both sites; unchanged best |
| `mask_width` | 648 | Nine independent mask widths on both arms; bool/byte and signed/unsigned storage views; unchanged best |
| `status_or` | 384 | Further OR/XOR/arithmetic/narrow comparisons, excluding already tried 4x4; five extent refusals, no exact |
| `status_bitfield` | 512 | Four unsigned bitfield storage widths and eight predicate forms at each site, common/split tails; six extent refusals, unchanged best |

The `.py.txt` generators preserve these exact finite families. To replay them,
copy a generator as `.py` into scratch; place `native_split.cpp` beside it using
the previous handoff's patch. Run from the repository root. Field views in
these probes are compiler hypotheses at proven offsets, not new layout facts.
Initial generator-only errors (switch scope, helper friendship and overlapping
mask-name replacement) were corrected and the affected families rerun; the
table describes final complete runs. A signed-overflow-prone dead-test form
was replaced with an unsigned shift before the final guard run.

## Handoff

The remaining source question is now narrower: preserve the split-tail
control's correct Object web and the new earlier holder/mask ordering while
emitting the two original byte TESTs. Repeating the listed arithmetic, accessor,
bitfield, guard or width matrices without a changed explanation has no value.
The common-tail bank remains a separate one-instruction path to exactness.
No missing-function prerequisite or `blocked-on=` RVA was found. Production
integration still belongs in `Code/GameEngine/Source/GameClient/Drawable.cpp`
after a match; its current undeclared-definition check is clean.

Inputs: BFME2 a0cbc61c525ef15fd004599ab1870ba4ee39711a; verified BFME1 pointer
42bba2ddbd5cb895d99293583891d3b7315fa49e. Flags unchanged: O1, Ob1,
d2inlS100, static STLport, G7, SSE, MD, EHsc, DNDEBUG. Compiler hashes are in
the JSON. Startup pull and ledger check passed; published object index fetched.
The recent BFME1 update lock belonged to claudec2, so this seat skipped the
update without marking freshness successful. Fresh ordinary mismatch and raw
residue checks reproduce the bank above; ledger check passes. No full gate,
link cycle or runtime verification is claimed.

About 30 minutes, model gpt-6.1-sol. Preserve the bank, release the claim and
resume this same unfinished body. Session outcome remains `in_progress`.
