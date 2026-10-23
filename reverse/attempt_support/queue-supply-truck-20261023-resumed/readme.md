# queueSupplyTruck: resumed trials and a corrected WorldBuilder lifetime

Retail `?queueSupplyTruck@AIPlayer@@IAEXXZ`, RVA `0x004F37B0`, exclusive end
`0x004F3DB1`, **1537 bytes**. No exact recovery. The existing bank, score
0.7867, is unchanged. This session ended at the user's request to publish its
useful records; it did not establish that further reconstruction is impossible.
Model: GPT-6. Approximately 45 minutes before publication, including evidence
review and packaging.

## Findings worth carrying forward

1. **Correct the WorldBuilder lifetime attribution.** Its extra state 0 cleans
   the 12-byte center coordinate at `[ebp-0x80]`, through an empty destructor;
   `AICommandParms` is state 5 at `[ebp-0x364]`. The 20261023c handoff and the
   new team's archived history conflate them. The direct unwind-table proof,
   limits of the inference and reproducible decoder are in
   [wb-eh-correction.md](wb-eh-correction.md) and `verify-wb.py.txt`.
2. **The new team's two GH controls reproduce on this Windows machine.**
   With canonical ThingFactory and aiDock bindings, guard-GH emits 1557 bytes
   and clean-GH 1548. Both retain the required normal restores, but both have
   **two** base-vtable loads, before the repeating header and at the shared late
   join. Retail has one load **inside** the repeating header. Early ESI alone
   remains insufficient.
3. **Selected loose-arm qualified reads do not complete that regional split.**
   Sixteen new crosses used each GH control with volatile supply-AI storage;
   selected preferred-dock, ferrying or forced-state reads; selected Object
   template or aiDock-receiver reads; a volatile dock-ID local; or a qualified
   desired-count limit read. All retain the two ESI vtable loads. Sizes range
   from 1548 to 1562 bytes. Some aligned operands improve, but none is a stronger
   verified bank. Do not replay these exact eight changes on those two controls.
4. A fresh read-only stock-C2 trace of the clean historical control reproduces
   its target bytes and relocations across all 11 allocation rounds. It
   confirms the known broad vtable region; it supplies no new finishing rule.
   No allocation decisions or compiler files were changed.

## Other bounded negative trials

These apply to the clean historical control from the existing
`../queue-supply-truck-20261023-c2-root/clean-candidate.patch`, not to every
possible CFG. Their failure does not exclude untested combinations or source
representations. `trial-summary.json` records observed sizes and distinct raw
bodies by family; those counts concern scratch compiles, not recovered functions.

| Family | Trials | Result |
| --- | ---: | --- |
| One-member holders/reference aliases for scalar and pointer locals | 11 | All identical to clean control |
| Filter ctor/dtor placement, default args, typed null and Player argument/init forms | 11 | All identical |
| Iterator copy/assignment/empty destructor variants | 12 | Object variants inert; Team destructor changes allocation without solving it |
| Whole-local and selected-read qualification | 15 | Some local operand changes; no early vtable register load |
| Equivalent duplicated arms around existing operations | 42 | Some CFG changes; no finishing vtable split |
| Existing proven-unreachable iterator-null arms | 64 | Changed counter values/exits affect allocation, but no finishing split |
| Single compiler barrier at logical statement boundaries | 100 | 35 distinct bodies; no early vtable register load |
| Center wrappers, copy constructors and empty destructors | 8 | Three body shapes; no finishing split |
| Filter next/player/match fields and build-flag setter forms | 13 | Mostly inert; other changes do not solve allocation |
| Branch/loop joins and deferred normal restore shapes | 8 | No finishing split; do not infer semantic validity from successful compilation |
| Explicit post-string factory exit shapes | 6 | Both normal restores retained; no finishing split on that control |
| Conditional duplication of the complete query or individual filters | 12 | Early EDI in some enlarged bodies, wrong code/EH shape |

Six historical banks were also rebuilt; none supplied a better current body.
The seventh was a compile refusal caused by its old relative Coord3D include,
not evidence against the original candidate. Three initial controls and the
16 GH crosses bring the saved-result total to **328 trials / 327 successful
compiles**. This is an inventory of saved per-source results, not a timing or
coverage claim. Alignment diagnostics use unresolved COFF plus mnemonic
sequence matching and are not acceptance scores; they differ from the normal
gate's alignment and must not replace byte/relocation verification.

## Reproduction and handoff

`inputs.json` records the retained bank hash, exact control-source hashes,
effective compiler command and the stock-observer target-equality receipt.
Trials ran before and after pulling the new team dossier; packaging revision
is `778d2ec547`. The effective compiler is MSVC 13.10.3077, with the per-source
`/O1 /Ob1 /G7 /arch:SSE /Oy- /GX /DNDEBUG /MD` overriding earlier defaults.

The clean control is reproducible from the existing c2-root patch and its
documented base. For the new GH crosses, copy `probe.py.txt`,
`gh_prepare.py.txt` and `gh_loose_trials.py.txt` to
`build/truck-20261023/` without `.txt`. From the repository root run
`gh_prepare.py`, then `gh_loose_trials.py`, using the installed Python.
They reconstruct the two controls from the tracked team's base/patches and
compile only distinct private sibling objects via `build.try_compile_source`.
The decoder likewise runs from the repository root after copying to `build/`.
No gate, protected baseline, production source, pin or bank is changed.

For another attempt, address the documented **regional membership**, loose
Object EDI allocation, native first-loop rotation or shared local homes with
new evidence. Preserve both normal build-flag restores after string cleanup;
do not add an exception-time restore. The corrected WB coordinate lifetime is
a source lead, not evidence that the retail five-state EH table needs another
cleanup or that a previously inert empty-destructor trial must now succeed.
