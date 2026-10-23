# Apt display-list visitor at 0x006F7720

Result: closer bank, not an exact recovery. Symbol `?rva006F7720Sub@AptAnimationPoolData@@QAEXPAXH@Z`, retail extent 643 bytes. Destination from `repair_queue.py dest`: `Code/Libraries/Source/Apt/AptDisplayList.cpp`. No production source, ledger row, pin, gate code, git index, or git ref was changed. Input revision: `b1d0e1b731dbf0c91224258d1178026ea1d2da3f`. Model: `gpt-6.1-sol`.

## Measurements

Both sources were compiled at distinct fresh scratch paths with `BFME_OBJSTORE=off`, MSVC 7.1's default compiler and the bank's first `// cl: /DNDEBUG /MD` directive. These scratch sources use the default `/O2` build command. `align_diff.py` measured the original bank as 675 bytes and 194 instructions, with 7 structural regions, 18 memory differences and 9 register differences. The new bank emits 650 bytes and 191 instructions, with 1 structural region, 14 memory differences and 1 register difference. All 14 remaining memory lines are absolute relocation slots. The improvement is present in every measured defect class.

After the normal `compile_function` relocation resolution, positional differing bytes inside the 643-byte retail extent fall from 325 to 52. The respective overhangs are 32 and 7 bytes. Counting overhang separately gives 357 versus 59 differing or excess bytes. These positional figures describe the result; the structural and operand measurements establish eligibility for replacing the bank. The first 568 resolved bytes of the new body agree exactly. No direct-call symbol is unresolved. Score 0.989 reflects two aligned instruction defects (one extra load and one register operand difference) relative to 190 retail instructions.

## Identity and behavior

Native padding precedes the entry at RVA 0x006F7720. Its SEH prologue receives the object in ECX, and its `ret 8` at RVA 0x006F79A0 ends at 0x006F79A3. The Ghidra inventory's 636-byte extent cuts the epilogue. AptDisplayList.cpp assertion strings establish the unit. The original member name is unknown, so the existing address-derived name is preserved.

Retail proves mask count at stack-object offset +0x80, item info at +0x4C, next at +0x54, and signed 17-bit depth at +0x58. Calls target the existing insert/remove providers at 0x006F7570 and 0x006F7600. Callback addresses 0x006F7330 and 0x006F73A0 use the existing matched providers and the same three-argument cdecl stack ABI; the clip callback's result is discarded. Assertions, clip insertion, per-item visitation, expiration removals, front-shift removal and final destruction are retained.

The former flags blocker is resolved in the current checkout: `reverse/data_rows.csv` already owns RVA 0x00A17718 as `g_bfmeExtra1282Flags`, with its definition in Apt.cpp. The candidate references that provider instead of defining a second global. The BFME1 BfmeConv1038 donor was examined as a semantic lead only. No donor body, volatile view, layout, identity claim or EA comment was imported. Every original comment line from the bank remains, in order.

## Successful hypothesis

Retail's getters compare against the cached count in EDI. The old bank's getters instead read the separate member count. Pass the cached count explicitly to the checks. Front removal also uses the cached count for its assertion and initial bound, refreshes from the actual count within the shift loop, writes the decremented count, and returns it. Expressing that shift with an ordinary `for` loop reproduces retail's EDX bound, EAX copied item and ECX refreshed bound. Removing the inherited inner-loop compiler barrier restores the correct ESI callback and EDI count allocation. The initial inherited barrier remains.

## Exact blocker and ruled-out hypotheses

At retail +0x238, the target tests cached EDI. The candidate first loads the count member with `mov eax,[esp+0x90]`, then tests EAX. This extra seven-byte load shifts the remaining epilogue. Obtaining the same value through a reference to the member changes allocation or removes assertions. Visible noinline helper definitions establish non-escape information but also change allocation and, in several variants, eliminate the target's final getter assertion. They are not an improvement. Returning the count field instead of the local changes nothing. An explicit final count synchronization emits an extra store, so it is rejected. Moving the old front bound alone and retaining the inner-loop barrier also regress measured classes. No unsupported volatile operation, equal-arm expression, asm, emitted bytes or optimizer pragma was introduced.

The next useful experiment needs evidence for a count-lifetime representation that preserves the retail assertions while exposing the cached value to destruction. Repeating the reference, helper-visibility, return-field or final-store variants without new evidence is not justified.

## Reproduction and raw evidence

All trial sources, scripts, raw tool outputs and the untouched bank copy are retained under `build/apt-6f7720-w3/` by assignment. `hypotheses.md` records each hypothesis and its refuting observation before its experiment. `prior-verdicts.txt` contains all ten prior verdicts; none cited a separate target support file. `retail.log` is the raw boundary, helper and callback disassembly. `before-align.log` and `candidate-align.log` are the authoritative alignment measurements. `candidate-explain.log` contains the resolved side-by-side disassembly. `bytes-before-after.jsonl` gives the positional counts and every differing offset. `comment-preservation.log` verifies retained comments. `record.log`, `check-csv.log`, `pin-consistency.log`, `final-bank-align.log` and `final-receipt.json` record banking, final checks and clock readings. No background process or external publication was started.

`check_csv.py` and `pin_consistency.py --check` pass. The re-banked source reproduces the candidate's alignment. Exact comparison fails at +0x238 as described above; `add_match.py` and production-source build gates were not invoked. Final comment preservation and `git diff --check` pass in `final-hygiene.log`. The first hygiene check exposed CRLF endings introduced by the Windows scratch writer; `hygiene-crlf.log` retains that output, and only the changed bank and its candidate were normalized to LF. `changed-paths.txt` lists every task artifact and generated object-cache file.
