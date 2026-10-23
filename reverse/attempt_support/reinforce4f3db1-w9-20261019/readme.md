# Result

Blocked: retain `reverse/attempts/0x004f3db1.cpp` byte for byte. The target is `?selectTeamToReinforce@AIPlayer@@MAE_NH@Z`, RVA `0x004F3DB1`, 985 bytes, destined for `Code/GameEngine/Source/GameLogic/AI/AIPlayerTeamBuild.cpp`. No source, ledger row, pin or bank was changed. All prior verdicts for both RVA spellings and both symbol spellings were read, including the earlier unlisted 0x4F3DB1 verdict. Their only cited surviving evidence path is the bank itself.

# Identity and ABI

Retail's AIPlayer vtable at RVA `0x00862DC8`, slot `+0x5C`, contains VA `0x008F3DB1`. The ILT at RVA `0x004EF45A` also jumps to this entry. The Ghidra inventory records the start and size. Retail starts with the EH prologue, returns with RET 4, and ends at the separately framed `0x004F418A` body. ZH's AIPlayer.cpp function establishes the semantic guide through the team-instance walk, two debug messages, recruitment and training; BFME2's offsets and extra record branch come from retail. Raw target disassembly also verifies countObjectsByThingTemplate RET 0x14, tryToRecruit RET 0x18, findFactory RET 0x0C, findTemplate RET 4, and the Team instance-next getter at +0x40. All bank REL32 names resolve. The same-arm expressions preserve values; no volatile self-store or omitted body operation was found in the bank. This is a source and disassembly review, not an execution proof.

# Experiments and refutations

Hypotheses and their refutation criteria were written before their experiments in `build/reinforce4f3db1-w9/hypotheses.md`. Each trial used a new source path, checked STOP_WORKER, and ran with BFME_OBJSTORE=off. The unchanged bank and seven trials were compiled with the bank's first cl line: MSVC 7.1, /O1 /Ob1 /G7 /arch:SSE /Oy-, STLport, and the existing BFME2 string/moduledata/allocation shims.

| Source label | Emitted bytes | Structural regions | Memory differences | Register differences |
|---|---:|---:|---:|---:|
| before | 997 | 20 | 52 | 21 |
| early-return | 997 | 20 | 52 | 21 |
| sink-1 | 999 | 25 | 60 | 21 |
| sink-2 | 1006 | 25 | 61 | 21 |
| sink-4 | 1021 | 27 | 61 | 21 |
| direct-manager | 996 | 20 | 52 | 21 |
| direct-name | 992 | 22 | 57 | 21 |
| direct-both | 996 | 20 | 52 | 21 |

The early failure return emitted the same whole symbol. The diagnostic sink writes did not obtain retail's selected-team EBX lifetime; instead `this` took ESI and the selected team remained spilled. These diagnostics change behavior and must never be banked. Removing either or both artificial equal-arm expressions failed the required alignment improvement: the 992-byte direct-name trial has more structural and memory differences, and direct-manager/direct-both leave all three defect classes unchanged. Do not adopt the lower positional counts as progress.

The retained bank has 690 differing patched prefix bytes and 12 extra symbol-tail bytes, or 702 positional differences in total. The direct-name trial has 636 plus 7, or 643, but is rejected by alignment. These positional counts include branch displacement effects and are not the acceptance metric. The remaining principal mismatch is retail retaining curTeam in EBX and proto at EBP-0x20, whereas the bank retains proto in EDI and spills curTeam at EBP-0x14; iterator and other stack homes then diverge. No further justified spelling experiment was identified after these results and the extensive earlier declaration, getter, guard and flag trials.

# Reproduction and evidence

Repository revision: `af72028f8f334a7becdfa74206ce7acfe6391b75`. BFME1 donor revision: `a18d9ed50607e9175de4d6568798d7d73119de09`. The retained bank is the best candidate under the assignment's metric. `before-align.txt`, `direct-name-align.txt`, and `bytes.txt` preserve raw comparison outputs. Every trial source, complete align_diff and explain_mismatch output, dependency receipt, probe script and raw retail audit remains under `build/reinforce4f3db1-w9/`; the generated objects and dependencies are under `build/match/build_reinforce4f3db1-w9_*`.

`align_diff.py` and `explain_mismatch.py` completed for all eight sources, with byte mismatches remaining. `check_csv.py` and `pin_consistency.py --check` passed; their raw logs are `build/reinforce4f3db1-w9/ledger.log` and `build/reinforce4f3db1-w9/pins.log`. No exact source was entered, so add_match, build.sh and find_declared_unmatched were not run. There were no background processes to stop. The bank's equality with the untouched before copy is asserted by `finish_checks.py`.
