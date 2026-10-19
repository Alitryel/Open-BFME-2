# Compact bank for SelectionTranslator::translateGameMessage

The bank is one self-contained source at `reverse/attempts/0x0043003c.cpp`. It requires no files from `build/` or `reverse/attempt_support/`. The function is `?translateGameMessage@SelectionTranslator@@UAE?AW4GameMessageDisposition@@PBVGameMessage@@@Z`, RVA `0x0043003C`, target size 4054 bytes. This is a closer partial, not a matched row. The source and all logs are uncommitted.

## Measurements

The old bank emits 3458 bytes and measures 109 structural regions, 225 memory differences and 69 register differences. The compact bank emits 4048 bytes and measures 4 structural regions, 106 memory differences and 3 register differences. Positional differing bytes are 3594 before and 2585 after, supplementary to alignment. Relocation and branch differences are excluded from the comparison. Both emit more than three quarters of retail. The old farm bank's incorrect selection paths are replaced by the retained native recovery. The bank score is a conservative 0.90.

The retained candidate in `build/candidate-0043003c/` emits exactly the same parent bytes and relocation records as every successful compacting step. Its full context is no longer a banking prerequisite. The previous handoff at `reverse/attempt_support/0x0043003c-20261019-w8/readme.md` remains historical evidence; its claims about required external context headers are superseded by this package.

## Hypotheses and declaration context

All six prior parent verdicts and the cited evidence were reviewed. Prior donor scaffold evidence survives in `build/selection43003c-w8/prior-parent.cpp`; the earlier log's removed `reverse/attempts/0x0042fa0d.cpp` is that source. Existing donor revision attribution and descriptive comments are preserved in the bank. The current checkout is `1d7d3716bc22594f17dca9ec14b3d2ccd4a337c9`, with BFME 1 input revision `a18d9ed50607e9175de4d6568798d7d73119de09`.

The first hypothesis was that Object declarations unused by the parent could be removed while retaining its two bases, native ID access and the four called methods. The first compile exposed a transitive requirement from Team.h for the donor's TeamMemberList DLINK interface. Retaining that exact macro resolved the compile failure without changing the parent. The remaining hypotheses reused the real `Lib/BaseType.h` with the two adapted coordinate type names temporarily renamed, reduced MessageStream to the storage and declarations actually required, and inlined the remaining context into one source. The refutation condition for every step was any change to parent bytes, relocation names or required alignment counts, or a package exceeding 65536 bytes. Every successful step preserved all those measurements. The lexical audit also preserves every one of the original bank's 158 comment tokens, including eight inline comments from omitted Object declarations.

`build/selection43003c-compact-w8/hypotheses.md` records each experiment before compilation. `h1.align.log` is the raw failed compile. `h1a.align.log`, `h2.align.log`, `h3.align.log`, `h4.align.log` and `h5.align.log` are the successful reductions, with matching `.metrics.json` records. All original trial sources and raw outputs remain in that task folder. No nonmatching production source was created.

## Identity and remaining mismatch

Fresh retail checks confirm the previous RET at `0x0043003B`, parent start at `0x0043003C`, terminal RET4 at `0x0043100F` and exclusive end at `0x00431012`. The constructor at `0x0042FD9E` installs vftable VA `0x00C3C960`, whose first entry is VA `0x0083003C`. The body has an ECX receiver and one pointer stack argument. Selection call relationships and donor purpose support the member name; the WorldBuilder inline assert label does not. `identity-final.log` contains the raw bytes, disassembly and assertions.

Target facts remain the state bytes, virtual slots, field accesses, selection and message call graph. The integer ID-set type and the converting coordinate constructor remain structural inferences. The donor supplies the selection algorithm and EA comments. Trimming declarations creates no additional target identity or layout claim.

The four structural regions are unchanged: the contained-object register transfer at `0x0043048B`, an extra group reload near `0x00430C9E`, and missing group reloads at `0x00430CA6` and `0x00430D35`. Five callee names remain unresolved: integer hash lookup, map constructor, map destructor, map subscript and private deselect helper. Most of the memory count is the tool's classification of unrelocated globals. The prior native-allocator hashtable destructor still emits 53 bytes against retail's 57, and recursive helper and fold identity proofs remain prerequisites. No new pins were added, and no compiler-shape trials were repeated.

`repair_queue.py dest` returns `Code/GameEngine/Source/GameClient/MessageStream/SelectionXlat_selectFriendsWrapper.cpp` by a neighbor heuristic. The existing `SelectionXlatTranslateGameMessage.cpp` retains a prior parent to support its matched private-ABI helper. Neither was edited; final production placement remains part of finishing the exact body.

## Reproduction and checks

Set `BFME_OBJSTORE=off`. Delete the source's object and dependency receipt before calling `python tools/align_diff.py reverse/attempts/0x0043003c.cpp "?translateGameMessage@SelectionTranslator@@UAE?AW4GameMessageDisposition@@PBVGameMessage@@@Z" 0x0043003C 4054`. The probe script performs this invalidation itself.

Raw comparison logs are `build/selection43003c-compact-w8/before.align.log`, `retained.align.log`, `bank-final.align.log`, `before.explain.log` and `h5.explain.log`. Final raw gate results are `check-csv-final.log`, `pin-consistency.log`, `diff-check-final.log`, `bank-audit-final.log` and `record.log` in that folder. All pass. The earlier `diff-check.log` fails because the first package used CRLF; replacing CRLF with LF fixes it without changing the compiled parent. Final source size comes from `run-receipt.json` and is below the 65536-byte limit. All source comment content is preserved. `h1.align.log` and the initial lexical `verify.log` are retained failed probes, followed by the passing corrected checks. `run-receipt.json` records command exit statuses, the final bank size and elapsed clock time. `add_match.py`, `build.sh` and `find_declared_unmatched.py` are not applicable to this unrowed partial; no Code source or production ledger row changed. No network, claim, writing git operation or background task was started.

Changed review paths are the bank, the append-only attempt log and this handoff. Scratch sources, scripts and raw logs are under `build/selection43003c-compact-w8/`. Measurement also regenerates the corresponding object and dependency caches under `build/match/`; `artifacts.json` enumerates them. No process was left running.
