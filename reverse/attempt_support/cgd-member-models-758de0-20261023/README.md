# 0x758DE0: wider member targets and dispatch paths

The best bank is unchanged: **333 bytes, zero relocations, 31 positional
differences, 308/333 complete instruction-pair bytes aligned**, score
0.924924924924925. Its raw SHA256 is
`01e69aef7e003a734f1bc04dc4faf28fd44f3c0d6757d8db6f5fb935382ab90e`.
The ordinary virtual-interface control remains 333 bytes, 41 differences,
302 aligned bytes. No new body, production declaration or pin was landed.

The bank's reverse-only fastcall pair is still an **unproven ABI diagnostic**.
The new member-table and floating-bit models below are compiler experiments,
not evidence for original types or target inheritance. In particular, zero
raw adjustment words are NOT sufficient to preserve the receiver in the
12-byte virtual-inheritance model; see the emitted adjustment below.

## Preparation and existing evidence

Started with a clean tree and the previous session's verified camera landing
unpublished. Pulled/rebased; the resulting HEAD was
`bc1be94d46fe6296971fd0919ac592e9f1475dc7`, over origin/master
`06c1864a762ef6d20ba4eed1f5c758fb872e4625`. The standing camera assignment
0x102F83 is already matched, so the runner's banked-body fallback applies.
Read AGENTS.md, last-session metadata, recipes and scoped pick-hard history.
Ledger validation passed (98,107 function rows, 15,858 symbols, 2,140 data).
Fetched the published link index and objects. No wind-down signal was present.

BFME 1's clean checkout equals the committed pointer
`138757e9b74645fbcbb7724a7af2764e34931e11`. The fresh shared updater lock
belonged to codex8; skipped the update as instructed, without recording a
freshness success. No maintainer-only runner or broad source sweep was run.

Before this body, claimed and released 0x1B69C0. Its approved VP6 spec still
says upper=255-lower, whereas the native NEG and LEA [ESI+255] establish
upper=255+lower. Recorded the unchanged specification blocker under the
clean-room rule; no decoder source was read and no implementation was tried.

For 0x758DE0, read the vcall, source-shapes, local-registers, lowering,
final-schedule, state-boundaries, global-homes, edges, rounds, interference,
aggregate, dispatch, barriers and call-lowering evidence. Those packets have
already tested the recorded control-flow/loop shapes, variable scopes and
lifetimes, real-header/layout models, callee visibility and compiler settings.
The remaining concrete question was whether a different early representation
could move the inner table's definition past its argument uses, retaining a
memory call and the outer table. No missing callee has been identified.

## Corrected experiments

The retained families contain **3,840 successful compilations**, including
controls. There is no whole-body improvement. `summary.json` uses full
mnemonic-and-operand alignment; search.py's mnemonic-first metric is separate.
All compilation used private objects through compiler_command, never the
shared match cache. Inputs and tool hashes are in `inputs.json`.

| Family | Compilations | Distinct bodies | Question |
| --- | ---: | ---: | --- |
| doubleword | 512 | 24 | Does an eight-byte floating bit representation of the two prepare arguments change argument/target lowering? Eight constructions, helper argument order, direct/wrapped occurrences, ordinary/fastcall and local/direct value. |
| memberforms | 768 | 82 | Do 8-, 12- or 16-byte member targets behave differently after adjustment fields become constants? Four constructions, assignment order, cdecl/fastcall helper, callback selections and both controls. |
| membersites | 1,536 | 420 | Recombine those member representations independently at all six call occurrences, with zero-first or null-member initialization and both controls. |
| dispatchpaths | 1,024 | 135 | Can calls through a base declaration versus its same-slot override remain distinct until later CFG merging? Four predicates, statement/helper scope, three call regions, inner/outer casts, bridge and control. |

The doubleword family is a subset of an initial 1,536-case scalar search.
Its 1,024 integer cases overlap the earlier global-homes/wide.py.txt family;
they are **not new evidence** and are excluded above. The double-only generator
reproduces exactly the 512 already-compiled source files; their results were
retained without an unnecessary second full compilation. Some double models
emit three helper relocations. Their best full body, v1028, has no relocations
but grows to 421 bytes and aligns only 210/333 bytes. Its first-response
region rises from 19 to 23 aligned bytes by adding stack stores and x87
FLD/FSTP argument construction. This is not a usable local replacement.

Member-pointer setup initially used an incomplete virtual-inheritance type
that triggers C1001, and an unsupported __unspecified_inheritance spelling.
A later complete single-inheritance definition contradicted an explicit
multiple-inheritance declaration (C2292). These rejected setups are excluded.
The retained memberforms generator uses two real bases for the 8-byte model,
a defined virtual-base class for 12 bytes, and full_generality for 16 bytes.
All 768 corrected models compile. Initializing from a declared member and then
replacing its raw target can retain declared-member relocations (up to six),
such as MultiSource::p. Those models do not preserve the dynamic target;
they do not improve matching and are not valid callback reconstructions.

Independent per-occurrence recombination is uniformly negative: **no region
beats the bank**. membersites/v0008 (8-byte target, first-response prepare only)
and v1032 (16-byte counterpart) emit the same 336-byte body. They explicitly
load the slot into EAX and call EAX; the desired call [eax+0xc] does not fold.
v0520 (12-byte counterpart) is 348 bytes and additionally loads through the
putative virtual-base table and adds it to ECX. Thus this raw-zero model
does not even retain the ordinary receiver ABI and cannot be used as a
production candidate. All membersites bodies have zero relocations; that
alone does not make their invented class views valid.

Of the dispatchpaths cases, 672 select an actual base/override distinction;
the remaining 352 are controls or inactive casts. The new distinctions yield
no whole-body gain. v0660 raises the test region to 19 aligned bytes but
retains duplicate prepare sites and grows to 366 bytes. v0436 raises the
response region to 22 bytes while retaining a conditional split and growing
to 372 bytes. These have seven static CALLs instead of the bank's six and
different frame/register assignments. They cannot be spliced into the bank.
`call-windows.txt` and selected source texts preserve these distinctions.

## Verification and continuation

Eight independent variant.py compilations reproduced the raw code and
relocations of both controls and six selected diagnostics. Sizes, hashes,
complete-instruction scores and positional differences are retained in
`independent-checks.json`. Neither byte alignment nor the variant driver's
relocation patching is treated as a landing gate. The native extent is still
0x758DE0..0x758F2D: RET followed by three INT3 bytes. No new exact body was
found, so no add_match or production build was warranted.

The best bank is re-recorded unchanged and the claim released. Preserve its
ABI warning. The task remains the test's normal-address/table order, the
first response's late EAX table definition, and the ordinary-interface
reverse result-push/reload order. The compiler-state comparisons in the
preceding call-lowering packet still distinguish early operand lowering from
final instruction scheduling. These new representations add work or lose
memory-call folding; do not repeat them unchanged. No blocked-on RVA is
supported. This is an unfinished source/codegen task, not proof of an
external blocker or of an impossible C++ body.

To reproduce, copy the .py.txt and .cpp.txt files to a directory immediately
under build/, dropping .txt. Run each generator and `search.py FAMILY` with
eight private workers, then
`regions.py doubleword memberforms membersites dispatchpaths`.
Independently compile a retained source with
`python3 tools/variant.py SOURCE bfmeTwoCGD 0x758de0 333` and inspect its whole
raw object, including extent and relocations. The best bank is unchanged;
the next session should start there, not from a diagnostic regional winner.
