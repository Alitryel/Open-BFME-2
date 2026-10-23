# privateFireWeapon at 0x002CE30A

The replacement bank is a complete 955-byte caller with eight remaining non-relocation byte differences. It replaces the semantically wrong 259-byte farm draft. The real caller reproduces the helper at 0x002CB594 byte for byte, including its ECX vector, EAX index, EDI object and ESI result convention. Neither function is admitted to the ledger. No production source, symbol pin or verifier was changed.

The bank defines `?privateFireWeapon@Weapon@@QAE_NPBVObject@@PBUCoord3D@@0H1_N2IPAH@Z`. Its helper is `?getLinearPosition@@YA?AUCoord3D@@ABV?$vector@UCoord3D@@V?$allocator@UCoord3D@@@_STL@@@_STL@@HPBVObject@@@Z`. The destination remains Code/GameEngine/Source/GameLogic/Object/Weapon.cpp, as reported by repair_queue.py dest. The old guessed name survives only in the preserved historical comment. The separate helper bank was left untouched.

## Measurements

All measurements used BFME_OBJSTORE=off and fresh objects. Raw outputs and all trial sources are under build/worker-002ce30a. The fresh before.cpp is the original bank, including its original comments.

| Candidate | Emitted/retail bytes | Structural regions | Memory differences | Register differences | Differing bytes after normal relocation resolution |
|---|---|---|---|---|---|
| Previous farm draft | 259/955 | 15 | 10 | 16 | 942, including 696 missing bytes; one unresolved computeBonus |
| Replacement | 955/955 | 0 | 6 | 8 | 12; one unresolved local getLinearPosition |
| Replacement with independently exact local helper resolved in a diagnostic map | 955/955 | 0 | 6 | 8 | 8; zero unresolved |
| Helper with the real caller | 199/199 | 0 | 1 | 0 | 0; zero unresolved |

The before body is below three quarters of retail, so its region count is not a valid closeness comparison. The complete, semantically correct replacement qualifies under the assignment's explicit incomplete/wrong-bank exception. Every replacement memory line is only a DIR32 operand. The helper's one memory line is also DIR32. The diagnostic map was local to byte_probe.py; it was used only after the emitted helper independently reproduced all 199 relocated bytes. It changed no pin, ledger or gate.

## Exact remaining blocker

The eight differing offsets are 0x5, 0x18, 0x1D, 0xE6, 0x130, 0x1A9, 0x2E4 and 0x2F1. The first is frame size 0x30 instead of 0x24. The other seven are bonus addresses at EBP-0x30 instead of EBP-0x24. Retail's six-float bonus region overlaps the later coordinate region at EBP-0x18. The candidate keeps both objects disjoint. The rowed fire-template provider ignores its bonus argument, but making its actual body visible, with both opaque and typed bonus arguments, did not reproduce the overlap. No safe source explanation for this allocation was established. No shortened bonus, out-of-bounds initialization, artificial union, expired pointer, volatile store or assembly was introduced to force it.

Before landing, reconcile the helper's proven componentwise Coord3D construction with the canonical header/contract, which still omits those constructors. The new boolean/boolean/unsigned parent spelling also differs from the opaque integer-word declarations in the three existing wrapper units. The nine-word stack ABI agrees, but those declarations and their existing old-name pin need a coherent provider/consumer repair once the parent is exact. Do not add a standalone standard-convention helper pin.

## Evidence and hypotheses

Target facts: the preceding function ends in RET 8 at VA 0x006CE307. The target starts at 0x006CE30A and ends in RET 0x24 at 0x006CE6C2, immediately before the wrapper at 0x006CE6C5. WorldBuilder 0x00BB7C40 names privateFireWeapon and exposes the same nine argument words and linear/scatter branches. Native calls and the existing matched providers establish the computeBonus, assistance, status, projectile-stream preparation, modifier, delay, ammo, drawable, special-template, fire-template, terrain and reload operations. The rowed INI parser at 0x002CE849 writes unsigned T into the linear record's z storage, independently confirming that the parent must read its bits as an integer rather than convert a float.

Donor facts: BFME1 revision a18d9ed50607e9175de4d6568798d7d73119de09 and the GeneralsMD Weapon.cpp provide the assistance, leech-range, barrel, scatter, ammo and reload semantics. Their older eight-argument bodies lack BFME2's linear path and differ in damage dispatch and reload sharing. Both donor functions were read in full and compared with the candidate. Every applicable EA comment remains at its corresponding operation; comments for removed mine/hack/deploy and shared-reload branches do not apply to this target. The boolean flag types and unsigned bonus mask follow donor declarations and native/WB byte accesses; they are supported source-type inferences, while their exact nine-word stack layout is target evidence. The unknown special flag and timingExtra144 retain neutral labels.

All earlier target/helper verdicts were read, including the return-value handoff at reverse/attempt_support/002cb594-return-value.md. Related crack-d/crack-g closure notes and the crack-e helper disposition were reviewed. hypotheses.md records each new hypothesis, evidence and refutation criterion before its trial.

Successful changes: a genuine nine-argument caller; return-by-value helper with the proven nontrivial coordinate copy; integer linear timing; componentwise scatter-pair initialization; reference-return maximum with native argument order; typed boolean flags, which fixed all three counter homes. Ruled out: scalar float timing, normalization of opaque integer flags, trivial aggregate scatter spills, actual fire-template provider visibility, typed bonus-reference visibility, function-scope target sharing, and earlier counter declaration/initialization. The provider integration initially omitted the STLport marker and selected wider Microsoft vectors; caller03 is a recorded setup failure, corrected in caller04. No synthetic helper driver was retained.

## Raw outputs and checks

before-align.log, best-align.log and best-helper-align.log are the authoritative alignment measurements. best-bytes.log contains full resolved byte counts, helper verification and the isolated local-helper diagnostic. best-explain.log records the unresolved-helper exact-match failure. retail.log preserves native, helper and WB disassembly. prior-verdicts.log preserves the prior rows; dest.log records source placement. caller01 through caller11 sources and logs preserve all trials. before.cpp preserves the old bank; best.cpp is the retained replacement. comment-audit.log checks preservation of every old bank comment and applicable donor comments. bank-align.log and bank-helper-align.log replay the saved bank with fresh objects.

check-csv.log and pin-consistency.log record the repository checks. No add_match.py, build.sh or find_declared_unmatched run is claimed: no exact production source was written. The candidate remains partial. No network, claims, git writes, commits, pushes, verification runners or background jobs were started. Timing is measured from the clock receipt in timing.json. Input BFME2 revision is ca8278b8461cc4ec8a443dc923e0f591b97c9e66. Compiler flags are the first cl line of the bank. model=gpt-6.1-sol.
