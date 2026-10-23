# queueSupplyTruck: coordinated research, 2026-10-23

Completed research attempt by gpt-6.1-sol. **No exact match or production change.** The
official bank is preserved. This dossier consolidates independent retail,
history and tool research, followed by isolated experiments. The user explicitly
authorized independent work alongside the external claim; its ownership was
untouched.

## Boundary and inputs

`?queueSupplyTruck@AIPlayer@@IAEXXZ` is protected, nonvirtual, no-argument
`void __thiscall`. Retail RVA **0x004F37B0**, exclusive end **0x004F3DB1**:
**1537 bytes, 450 instructions**, ending in RET at +600. No trailing padding;
six CC bytes inside the body are operands. The historical 1531-byte figure
describes an earlier emitted candidate. Retail SHA256:
`937f85d239ba2d15dc947ae023ecdf197e1afab03d250a47ed6088372e2e162b`.

Experiments used BFME2 `f2a14a8d788ef2eea0872efe2b03b5a51a804dbb` and verified
BFME1 `96c88c73a5cd1a58fc2f8db691beea50acd996db`. A read-only fetch found newer
BFME1 commits, but another contributor owns the reference-update scope. No
pointer or successful-freshness stamp was advanced. Today's tracked full-gate
evidence for the retained pin is in `../bfme1-reference-96c88c73-20261023/`.
Compiler: MSVC 13.10.3077, `/O1 /Ob1 /G7 /arch:SSE /Oy- /GX`; complete command
and compiler hashes are in `baseline-provenance.json.txt`.

Target evidence confirms info gatherers +78/+7C, three 24-byte Object iterators,
8-byte Team PMF (the containing iterator is correctly 16 bytes), filter cleanup
immediately after the query, five EH states, and both normal build-flag restores
after string cleanup. Supply interface slots are +14/+30/+3C; command-interface
base adjustment is +20, real aiDock RVA26C3AC. No direct TheAI access occurs.
TheGameLogic, ThingFactory and KINDOFMASK_NONE must use canonical globals.

## Reproducible controls and useful changes

`canonical-base.cpp.txt` is the cleaner historical c7 with canonical mask,
ThingFactory and aiDock bindings. It still contains the inherited loose-loop
barrier, so "cleaner" does not mean ready to land. It emits **1537 B,
19 mnemonic-difference regions / 70 aligned memory / 22 register-or-other
differences**, raw-body hash prefix `853d4f1cea07`. Removing that barrier gives
1537 / 19/72/23, `b3cb48df3eaf`. The freshly reproduced official bank remains
1535 / 21/69/13, `0b7e6e1ef011`; it has older aiDock shim bindings and artificial
steering forms. Do not replace it based on these alternative diagnostic scores.

Each patch here applies directly to the supplied canonical base:

| Patch | Bytes | r/m/g | Result |
|---|---:|---:|---|
| `guard-gh.patch.txt` | 1557 | 18/72/19 | All original Object guards, correct restores; G/early ESI/Z/T |
| `clean-gh.patch.txt` | 1548 | 19/75/20 | Removes only iterator-implied Object null guards; same features |
| `dynamic-end-pair.patch.txt` | 1546 | 22/73/17 | First ESI/EDI pair with a freshly read end each guard; wrong rotation |
| `shortage-goto.patch.txt` | 1558 | 20/59/19 | Correct info/desired homes; string EH state numbered before filters |
| `shortage-goto-loose-null.patch.txt` | 1551 | 20/59/19 | Same slot tradeoff, only loose redundant guard removed |
| `first-count-inline.patch.txt` | 1537 | 19/70/22 | Barrier-free, meaningful count helper forced inline diagnostically |

The new restore shape is behavior-preserving: exhaustion restores through the
while condition; success jumps outside the string scope to restore; exhaustion
bypasses the success restore. Both paths restore once after string cleanup.
This obtains the build-list entry guard, local ECX zero and direct query test
without deleting a restore. It does **not** obtain retail's precise vft placement.

**Strict H remains unsolved.** Retail's repeating header is +EC, its only
`mov esi,0xBC26E0` is +F0 (relocation +F1), inside that header. New GH candidates
preload ESI before their repeating header and reload it after factory success.
An early ESI load alone is not H. Retail also keeps recount Object in ESI and
loose Object in EDI; every tested composition still reloads loose Object to EAX.

The safe first-pair form materializes a new `end()` return at each header guard.
It preserves dynamic reloads, but adds an entry reload and an unconditional
outer backedge. Splitting entry/latch guards or using refreshed guarded-do forms
recovers native rotation while reverting the register pair. Combining it with
the shortage-goto slot improvement loses the ESI vft allocation. Correct info
and desired homes do not imply correct supplySource sharing or H.

First-count extraction, when forced inline, changes exactly four later cash
multiply instructions to retail's operand sequence, with no other instruction
change. Recount extraction is inert; loose extraction grows seven bytes and
changes allocation incorrectly. Ordinary inline emits extra calls. Likewise,
extracting the complete factory scan or queue construction adds calls with
ordinary inline and reproduces its control byte-for-byte when forced inline.
These helper boundaries are diagnostics, not evidence of original source.

## Experiment inventory and interpretation

Archived lane reports are plain `.md.txt` snapshots; paths within them refer to
the original ignored `build/queueSupplyTruck-research/` hierarchy. Most raw trial
sources/objects are intentionally not committed. Their exact measurements are
retained in the associated metrics tables; selected useful sources are patches
above. Initial research snapshots are `history.md.txt`, `retail-layout.md.txt`
and `tooling.md.txt`. They distinguish target facts, donor facts and inference.
Candidate text and patch context preserve the measured source verbatim,
including inherited whitespace; `git diff --check` therefore reports whitespace
in these evidence files. All six patches were independently applied and checked
to reproduce their measured source files exactly before archiving.

| Lane | Successful serial compiles | Main refutation |
|---|---:|---|
| cfg | 74 | Correct restores can recover G/early ESI/Z/T, but not H |
| zero | 185 | Local ECX zero alone does not recover G/H/T |
| iterators | 51 | List/end caching changes allocation but deletes retail reloads |
| cfg-refine | 112 | Query scopes, natural loop CFG and actual mask/API do not fix H |
| hoist-zero | 92 | Boolean recount moves homes but not Object/zero allocation |
| hoist-iterators | 94 | Dynamic-end first-pair gain has wrong rotation; native PMF is inert |
| compose | 76 | Demonstrated gains do not compose; split guards revert first pair |
| extraction | 26 | Useful whole-loop inline boundaries leave H unsolved |
| construction | 8 | Fully inlined template/queue extraction is byte-identical |
| phases | 20 | Complete supply-query/availability/refresh boundaries do not fix H |

These lanes total 738 successful private compiles, in addition to parent
controls. Four early construction-source compile refusals were corrected by
inserting the helper declaration alongside the already-present count helper;
they produced no candidate body and are excluded from the successful total.
The corrected construction generator is preserved; its retained results file
contains the four final first-count-context trials. The four base-context
successes reproduced the raw hashes documented above.

Parent controls additionally covered null/barrier and AI-local factorials,
immutable const references, actual filter And API, canonical bindings, RTM versus
4035 backend, GeometryInfo nesting, Thing prefix inheritance, constructor
initialization, home iterator comparison and a small flag cross. Most were
byte-identical. No evidence supports replaying declaration, accessor, ordinary
flag, iterator-spelling or backend sweeps.

r/m/g and scalar scores use mnemonic alignment on unrelocated COFF. They can
reward reorderings with many unmatched instructions; global operands may be
relocation artifacts. **Neither score, length nor call/EH audit is byte proof.**
Lane reports retain unmatched-instruction counts separately. Across the CFG,
zero, iterator, composition and fully inlined extraction candidates, ordered
45-call and five-state EH audits preserve required cleanup and reload behavior;
shortage-first forms have different EH numbering. No near match is accepted.

## Home-TU and tool receipts

`./build.sh Code/GameEngine/Source/GameLogic/AI/AIPlayerTeamBuild.cpp` passed
**60/60 rows**, 35 strings plus three empty references, six floats, and 23
funclet pins. An isolated unchanged home copy reproduced all 165 original COFF
definitions and relocations. Inserted candidates reproduced standalone target
bytes; existing code remained identical except compiler-local EH label names.
Proper protected `findModule` access is required for the real IBE mangling.
Read-only normal comparator calls on explicit private objects resolve all
canonical candidate calls, but fail bytes. No row was added. Provider/queueUnits
link acceptance is still required after an actual byte match.

`trial.py.txt` invokes `build.compiler_command` directly with an explicit private
sibling object, never `build.compile_source` or shared `build/match` writes.
Copy a source to `build/` with a `.cpp` extension and this script to `.py`, run
from repository root. It reads only the target extent; no large ledger dump.
Apply a selected patch to a copy of canonical-base first, e.g. with `patch
--output=build/qs-resume/candidate.cpp build/qs-resume/base.cpp < clean-gh.patch.txt`.
Use explicit flags: copying a Code TU loses region-derived defaults.
`compare_gate.py.txt` is read-only against already-built explicit objects;
its positional relocation differences are not acceptance. Do not run the older
shared-cache dumpobj probe unchanged.

No link_cycle, census, nightly, boot_smoke, emulator or publisher runner was
started. The published link index was fetched/reused. No production source,
ledger pin, gate, whitelist or claim has been changed by this attempt.

## Remaining work

A new explanation must address at least one measured dependency: keep the first
ESI/EDI pair with the native rotated latch; preserve Object in ESI/EDI in the two
later scans; obtain shared supplySource -14 and recount-zero packing without
changing EH numbering; or move the **single** ESI vft load into the repeating
header. Replaying a closed family or removing restore/cleanup behavior is not
progress. Complete supply-phase extraction is now closed too: ordinary inline
adds calls; query-only forced extraction produces the same four cash changes;
availability, full refresh and nested useful boundaries reproduce their
controls. All ten force diagnostics retain the ordered 45 calls, five EH states,
both normal restores and dynamic field reloads. All agents and compiler
processes for this attempt have finished. No independently supported new
finishing hypothesis remains from the investigated families; retain these
counterexamples and start with new IR evidence before another sweep.

## Subsequent stock-C2 observation

After this source-experiment checkpoint, rebasing exposed the independent
`../queue-supply-truck-20261023-c2-root/` observer and allocation evidence.
Its Windows/WOW64 debugger now runs locally under Wine using the official
CPython 3.11.9 embeddable AMD64 runtime. No extra dependencies were needed.
`observer.md.txt` gives exact setup, runtime SHA256 and commands;
`stock-observer-wine.py.txt` and the `observer-*.py.txt` files preserve the
private transport adaptation. It observes only its owned compiler child;
breakpoint instruction bytes are restored before stepping. No compiler
decision, IR, bitset, priority or executable/DLL file is modified.

Three sequential traces reproduced **all 62 emitted code definitions and their
ordered relocations** for each exact same-path normal/traced source. Complete
queueSupplyTruck bytes and relocation lists, source/compiler/object hashes and
comparison results are in `observer-*-equality.json.txt` and
`observer-summary.json.txt`. The baseline matches every published native
baseline membership signature, excluding process-specific indices. Runtime
binaries and large raw IR dumps remain under ignored build/.

The correct-restore GH vft candidate has round-3 actual membership **33/73**,
versus baseline **55/75**. GH excludes the recount region while retaining the
loose-harvester path. The late GH load +5CB is reached by **both recount
completion and factory success**, correcting earlier shorthand describing it
only as a postfactory reload. Early continues jump to +5D0 and bypass it; the
backedge skips the initial +EA load. This is an incomplete regional split,
not a strict-H recovery. Span endpoints alone do not establish membership.

The third trace is the weaker `n_expr_scope_shortagegoto` control, **1523 B**,
not the 1558/1551-byte slot-improving variants. Its exact source is preserved in
`observer-optional.patch.txt`; it loses early ESI and supplies no allocation fix.
The bounded follow-up is complete: all-Object-guards GH has round-3 membership
**34/75**, and the existing loose-helper control **34/74**. Both retain the
same recount-excluded / loose-included cut and early preload plus shared late
reload. Guard removal and whole loose extraction are therefore refuted as the
missing regional lever. Complete code/relocation preservation holds for **62/62**
and **63/63** emitted definitions respectively; both retain 45 ordered calls,
five EH states, fresh mutable-field reads and correct normal restore paths.
No distinct source-supported finishing hypothesis emerged, and no new source
variant sweep was started. Five stock traces total were run across these two
diagnostic rounds. All tasks and compiler processes have now finished.

`region-controls.md.txt`, `region-summary.json.txt`, `region-allocation.csv`,
the per-input equality/manifests, and `region-audit.json.txt` preserve the result.
`region-loose-helper.patch.txt` supplies the exact second control; the first is
the already-preserved guard-gh patch. Parent commit hashes changed during normal
rebases; source and compiler identity receipts, rather than ancestry of an old
local commit hash, establish control reproduction. Target bytes remain unmatched.

For a fresh checkout, restore script snapshots to their original relative
build/ hierarchy and remove the `.txt` suffix. The observer's prepare scripts
expect experiments/trial.py plus the exact controls reconstructed from the
patches above. Restore `observer-prepare-optional.py.txt` as
observer/prepare_optional.py. The regional audit additionally reads
extraction/analyze.py and extraction/final_audit.py **only for their function
definitions**; the minimal snapshots supplied here preserve exactly those
functions. Restore gh-control-calls.json.txt as extraction/gh_control.calls.json.
Compile the reconstructed original guard/loose control source paths privately
with trial.py before the regional audit compares their objects with fresh
same-path trace inputs. No shared-cache probe or explain_mismatch compile is
needed to resume this workflow.
