# AptTimeLine 0x00520CD1 allocation blocker

Result: blocked. The existing bank `reverse/attempts/0x00520cd1.cpp` is unchanged. The symbol remains `?rva00520CD1@AptTimeLine@@QAEXXZ`, RVA `0x00520CD1`, extent 684 bytes. `repair_queue.py dest` selects `Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptTimeLineCollectPlayerData.cpp`. No production source, pin or function row was changed. Inputs are checkout `9bc9d37e48e9dfea48691889f89f50b7c2bc62a5` and its existing references, using MSVC 7.1 and the bank's `/O1 /G7 /arch:SSE /MD /EHsc` settings and STLport shim includes. No donor source was imported.

All seven existing target verdicts were read, including the W9-O3 callee-name repair beyond the assignment's five listed verdicts. None cites a handoff path beyond the bank. Its header was read in full. The related `reverse/attempt_support/apt-timeline-cleanups-20261013/README.md` and `verify.py` were also read for receiver and record ownership context. New hypotheses and their refuting observations were written before their trials in `build/apt-520cd1-w5/hypotheses.md`.

The current bank compiles to exactly 684 bytes with 111 differing byte positions after `explain_mismatch.py` relocation processing. Earlier `nd=12` counts instruction deltas and is not a differing-byte count. The first mismatch is +0x1C5 (retail `0B`, bank `08`, the inner-search branch displacement). Everything before that offset matches. After the search, retail reloads the initial null slot into EDI on the not-found path and assigns the found slot to EDI. It subsequently retains that slot across the optional statistics block and spills the tactical pointer at EBP-0x1C. The bank retains the slot at EBP-0x1C and allocates tactical to EDI. This changes the slot-name address calculation, predicate receiver, statistics argument and final collector argument. The paths reconverge at the exact collector call at 0x00520F20. The 111-position count includes downstream instruction displacement and relocation-site shifts; those copied DIR32 values in a mismatching disassembly are not independent global-binding findings.

| Probe | Symbol bytes | Differing positions in compared extent | Observation |
|---|---:|---:|---|
| Baseline | 684 | 111 | Existing best body. |
| H1 visible flag getter | 667 | 469 | Changes earlier RTS allocation and worsens body. |
| H1b strategic getter visibility only | 682 | 206 | Slot remains spilled. |
| H2 shared RTS/strategic slot variable | 684 | 111 | Byte-identical to baseline. |
| H3 one diagnostic slot sink | 690 | 232 | Slot gets EBX and living-world player spills; tactical remains EDI. |
| H3 two diagnostic slot sinks | 696 | 229 | Same wrong allocation; symbol also exceeds extent. |
| H3 three diagnostic slot sinks | Not admitted | Not measured | Explain refuses a REL32 crossing the 684-byte extent. |
| H4 index-conditioned final slot value | 684 | 111 | Byte-identical to baseline. |
| H5 tactical result bound to const pointer reference | 684 | 111 | Byte-identical to baseline. |
| H4b index-conditioned complete collector call | 690 | 254 | Index becomes EBX, living-world player becomes EDI then spills, tactical remains EDI. |
| H4b index-conditioned statistics call | 690 | 248 | Same wrong allocation. |

For short probes the count includes missing bytes; for long probes it describes the gate's first 684 bytes and does not count the extra symbol bytes, which independently disqualify those candidates. Sink probes change behavior and are diagnostics only. No new candidate improves the baseline and no further evidence-backed experiment was identified.

Target identity and ABI evidence: native RET at 0x00520F7C establishes the full interval through 0x00520F7D. The rowed opener writes the mode at receiver +0x284 and calls this body at 0x005210C7 with the timeline singleton in ECX. The two rowed CollectPlayerData overloads at 0x00520792 and 0x00520923 and final rowed refresh at 0x0051FA13 support AptTimeLine ownership. The original method name remains unknown. Native slot lookup, living-world lookup, observing-player query and flag accessor were disassembled before shape trials; the baseline's direct call relocations resolve without new pins. The folded ParticleSystem getter and IDBufferClass setter are representation views, not evidence that a player or statistics panel has those original types. Full production-unit and EH admission remain required after any future exact body.

Raw evidence and all trial sources are under `build/apt-520cd1-w5/`: `baseline.explain.log`, `baseline.json`, `baseline.deltas.log`, native `retail-inspect.log`, per-probe `.explain.log`, `.json` and byte binaries. `measure.py` invokes the official explain tool and then reads its compiled object to count differing positions; it never manually compiles. The baseline copy and `receipt.json` verify that the bank's bytes were preserved. `checks.json` records exit codes for destination selection, `find_declared_unmatched.py` on the unchanged destination, `check_csv.py` and `pin_consistency.py --check`; all pass. No build or add_match admission was attempted because no exact candidate exists. No background task was started.
