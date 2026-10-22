# AptMpGameSetup 0x004404AC: merged team branch, five-byte residue

The assignment remains unfinished, with a better bank at
`reverse/attempts/0x004404ac.cpp` (score 0.99). A fresh isolated compile emits
526 bytes / 183 instructions, zero structural differences and five differing
operand bytes. The previous bank had 31 differing bytes, all caused by the
receiver/index ESI/EDI exchange. That exchange is now closed. The only residue
is EAX/ECX for the initial team-window value and its locked flag:

| Address | Bank | Retail |
| --- | --- | --- |
| 0x4405EC | `mov ecx,[ebx]` | `mov eax,[ebx]` |
| 0x4405EE | `test ecx,ecx` | `test eax,eax` |
| 0x4405F9 | `sete al` | `sete cl` |
| 0x440608 | `test al,al` | `test cl,cl` |
| 0x440612 | `push ecx` | `push eax` |

`residue.txt` records the full-row comparison and call sites. All 25 object
relocations resolve; there are 27 call sites, 23 direct and four indirect.
Earlier notes/commentary saying sixteen calls were an incorrect count.
No exact match or credited recovery is claimed. Code, ledger rows, pins,
compiler binaries, tools and baselines are unchanged.

## New hypothesis and measured result

The previous handoffs showed that source-level CFG blocks can change C2's
allocation priorities even when their instructions disappear. Rather than
repeat the disproven early index copy or preview-address motion, this session
tested duplicated equivalent widget blocks which C2 can merge.

`duplicate-132` duplicates the entire existing `if (*team)` block under
`if (slot == 0)` and its else arm. Both arms retain the original rule read,
short-circuit condition, HideList call, post-call pointer reload and enable
call. The predicate has no side effects. This is a matching source variant,
not a claim that the original source contained that spelling. C2 removes the
extra branch and duplicate instructions, preserving the whole 526-byte shape.
The goto equivalent `duplicate-133` gives the same result.

A read-only C2 trace confirms initial insertion priorities change from
`this=41, slot=49` to `this=39, slot=31`. Reference counts change from 12/14
to 13/15. The merged variant has two `locked` candidates, IDs 9 and 11,
each priority 5 and two references. `merge-costs.json` preserves the initial
candidates and receiver/index per-block contributions; their sums agree with
the insertion priorities. Persistent roles become retail's this=ESI,
slot=EDI. The new short EAX/ECX residue is confined to the team block.

A second read-only measurement closes the preceding session's question about
the entry cost multiplier. The original first block has factor count three;
the known early-index-copy control has five, both frequency one. The extra
two referenced candidates are the original slot and its index copy (cost one
each); receiver cost is four in both. The captured bitset header is unchanged.
This explains the receiver's extra eight cost in that control without needing
a hidden new instruction. The control itself is still rejected because it
moves the index save/load across the game-null branch. `entry-counts.json`
and `early-control.patch` preserve this new measurement, not another attempt
to land the already disproven control.

## Completed searches and exclusions

The canonical families below total 6,832 generated trials, all compiling.
None beats five bytes. `results.json` preserves compact score histograms.
The counts exclude an earlier superseded shared-storage run with 96 generator
scope errors; its corrected 512-member rerun is included below. A missing
space in one helper parameter and switch-case declaration scopes were also
fixed before the canonical runs. These were scratch-generator errors, not
verifier false rejects.

| Family | Trials | Result |
| --- | ---: | --- |
| Equivalent widget-region duplication | 256 | Masks of five widget regions, four predicates, if/else or goto. Team duplication with slot-zero predicate gives the new five-byte bank. |
| Nested team duplication and flag types | 1,024 | Eight slot predicates, independent bool/char/unsigned-char/int flags, expression and declaration order. Best five; 768 retain the best instruction shape. |
| Nested shared team storage | 512 | Shared flag/output storage, factored null guard, if/goto forms and four types. Best five after correcting goto lexical scopes. |
| Nested team-window/flag bindings | 512 | Pointer/reference window locals, eight flag bindings, shared output, four condition forms and scopes. Best five. |
| Flat shared team storage | 512 | Same shared-storage family against the original bank. Best five; other zero-structure results retain 16 operand differences. |
| Flat window/flag bindings | 512 | Same binding family against the original bank. Best five. |
| Narrower merge boundaries | 864 | Seven factoring points, eight predicates, four flag types and four if/goto/switch forms. Best 16; narrower merges disturb other registers. Non-equivalent post-HideList guards and const assignments were excluded. |
| Merge predicates and shared flags | 384 | 32 existing slot/field/pointer/boolean predicates, three control forms and four shared-storage masks. Best five. |
| Short-local symbol ordering | 1,040 | k=0..64 inert initialized locals, four declaration points and four types, on the new merged control. Every result is the same five-byte residue. |
| Inline rule-accessor contracts | 192 | Six helper forms, four result types, reference/value variants, inline/forceinline and expression spelling. Best five; no unresolved symbols. |
| Local allocation contracts | 1,024 | Five register-hint bits, four rule-read qualifications, four call-argument forms and two output initialization forms. 768 best-shape twins; 256 worse. |

The last three families address the new short-value residue, rather than
repeating the original persistent-role searches unchanged. `permute.py` was
also run once after the residue became local: `--minutes 1 --jobs 1`, 112
trials, starting/best score 0.9899, no exact match. Do not replay these scans
without evidence that changes their inputs or explains a specific interaction.

## Inputs, acceptance checks and reproduction

BFME2 trial HEAD was `6632078766993275014329c45d7a26878a396d73`, after a
nonrecursive pull to origin/master `12f7a75674`. The committed and clean
BFME1 checkout was `42bba2ddbd5cb895d99293583891d3b7315fa49e`.
Another seat's fresh BFME1 updater lock (owner `claudec2`) required skipping
a concurrent update; no freshness success was stamped and its lock was not
removed. Compiler/source hashes are in `inputs.json`. Flags remain
`/O1 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
/D_STLP_USE_STATIC_LIB`, STLport, MSVC 13.10.3077 under Wine.

Start ledger check passed: 98,068 function rows, 15,856 symbols and 2,128
data rows. The home unit's frozen-file check and `./build.sh` passed: five
matched functions, one data row, six literals plus its empty-string reference,
float and import checks. This verifies the existing home, not the target.
A separate fresh scratch compile of the annotated final candidate confirms
526 bytes, zero structural differences, five operand differences, no unresolved
relocations. Final ledger and diff checks passed. `python3 tools/progress.py origin/master`
reports +0 authored C++ bytes and +0 C++ exact bytes; the bank remains evidence.
Authored game C++ is 7,213,662 bytes (95.95%); total C++ exact is 7,957,448
bytes (98.28%).
No maintained verification runner was started.

Copy the `.py.txt` files here into ignored `build/4404ac-mergeweb/`, dropping
`.txt`. Recover the original input with:

```
git show 95b91a968e4b23bf0e770fdfd0cb761b6aa21685:reverse/attempts/0x004404ac.cpp > build/4404ac-mergeweb/bank.cpp
```

To reconstruct either control, first copy `bank.cpp` to `merged-control.cpp`
or `early.cpp`, then apply the corresponding zero-context patch with
`git apply --unidiff-zero --directory build/4404ac-mergeweb <patch-path>`.
Both reconstructions were checked byte-for-byte against the trial inputs.
The merged control's SHA256 is recorded. The tracked bank has improved
comments but the same code as `merged-control.cpp`. Do not overwrite the frozen original control.

`search.py` defaults to `bank.cpp`. Set `TRIAL_BASE` explicitly for the nested
families: `TRIAL_BASE=build/4404ac-mergeweb/merged-control.cpp`. Use
`TRIAL_TAG=flat-` for the flat shared-storage, window-binding and graph runs.
Short-local, helper and local-contract drivers explicitly read the merged
control. Predicates and initial duplication use the original control.
The corrected nested shared-storage run used `TRIAL_TAG=nested-fixed-`.
Compiles use `build.compiler_command`, isolated objects and eight workers;
never use `build.compile_source`. Remove scratch objects after dependency or
compiler changes: the source-equality cache is only valid for fixed inputs.
Comparison checks emitted size separately, and resolves across the complete
emitted extent; a short body or unresolved relocation cannot be an exact match.

For debugger reproduction use `trace.py duplicate-132`,
`trace_blocks.py duplicate-132`, `trace_entry.py bank` and
`trace_entry.py early` after generating/copying those sources. Sites and word
meanings are in the preceding blockcost/cost handoffs. Traces only set
breakpoints and read the unmodified compiler; no register or compiler-memory
writes were made. Later allocation passes must not be confused with the
initial insertion pass (initial return 0x1078474F, later 0x1078BAA4).

## Continue this body

The next concrete step is to inspect C2's short-register affinity,
interference and coalescing for the team-window temporary and the two locked
candidates, or isolate this exact merge in a small probe. The bank now gives
a useful control for distinguishing persistent allocation costs from the
five local EAX/ECX choices. Keep the full merge as the control: simple shared
variables, narrowed merges, inert-local ordering, inline rule getters and
register/volatile hints above have been tested. Existing history still
excludes the broad original role-swap families, compiler settings and callee
visibility grids. There is no identified missing function or external blocker.

Stay on this unfinished assignment. The proper home remains
`Code/GameEngine/Source/GameClient/GUI/Rva0043F483PopulatePlayerCombo.cpp`;
do not leave a nonmatching body there. On exact landing, row the parent's
emitted EH machinery in the same commit: retail's 10-byte EH stub is at
RVA 0x788A5E, and unwind funclets must be verified from this parent's object.
No new symbol pin is currently needed. Release the claim after banking so
future sessions can reclaim safely. Model: gpt-6.1-sol.
