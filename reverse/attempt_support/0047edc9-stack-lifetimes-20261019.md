# AnimalAIUpdate stack lifetime retry

Result: blocked. The original bank is byte-for-byte unchanged. No reconstruction was placed in Code, and no ledger row, pin, shared header or verifier was changed. The symbol is `?update@AnimalAIUpdate@@UAE?AW4UpdateSleepTime@@XZ`, RVA `0x0047EDC9`, extent 2916 bytes ending at `0x0047F92D`. The intended new home is `Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/AnimalAIUpdate.cpp`, as established by the retail source literal. The destination picker instead heuristically returns its existing DestinationLayer sibling; that heuristic is not a source-identity claim.

## Inputs and measurements

The tested revision is `9bc9d37e48e9dfea48691889f89f50b7c2bc62a5`. The checked-out BFME1 reference is `a18d9ed50607e9175de4d6568798d7d73119de09`; the inherited bank cites semantic donor `9cbfb551`. All three actual prior verdicts were read, including the third verdict at shortened RVA spelling `0x47EDC9`, the complete bank and its header's tested hypotheses. None cites a separate BFME2 support path. The referenced BFME1 bank and its `targets/game/reverse/identity_evidence/002B32A0-native-context-retry.md` handoff were also read. No reference refresh or network operation ran.

| Trial | Emitted bytes | Row byte differences | Excess emitted bytes | Relocation-masked differences including excess | Frame |
|---|---:|---:|---:|---:|---|
| baseline | 2923 | 1767 | 7 | 1611 | 0xA4 |
| h1 | 2918 | 1784 | 2 | 1633 | 0x98 |
| h2 | 2972 | 2323 | 56 | 2171 | 0xA0 |
| h3 | 2923 | 1767 | 7 | 1611 | 0xA4 |
| h4fields | 2919 | 1783 | 3 | 1623 | 0x98 |
| h4new | 2932 | 1769 | 16 | 1619 | 0x98 |
| h5length2 | 2923 | 1769 | 7 | 1613 | 0xA4 |
| h5length3 | 2923 | 1769 | 7 | 1613 | 0x98 |

Row byte differences compare explain_mismatch's patched 2916-byte output with retail, before any alignment or normalization. Excess bytes are reported separately because that tool truncates its patched output to the requested row extent. Thus the retained bank has 1767 differing row positions plus 7 excess emitted bytes, both before and after this attempt. The relocation-masked metric additionally includes excess bytes and is a separate diagnostic. The inherited score of 0.96 is not a positional byte agreement score. Every successful explain process exited zero as a diagnostic; none reported matching bytes. All candidates had zero unresolved direct callees. Sources, unedited explain output, unedited probe output, object measurements, raw bytes and disassembly differences are under `build/animal-47edc9/`; `manifest.txt` lists the complete files and tool-cache receipts.

## Hypotheses and refutations

`build/animal-47edc9/hypotheses.md` was written before the corresponding experiments. H1 explicitly reused the no-emitter distance local as the later destination. Its frame shrank to 0x98 but its byte differences worsened. H2 also reused it for the returning delta; assignment introduced block-copy and register changes and worsened the result substantially. H3 enabled the canonical empty Coord3D destructor; the main body was unchanged. H4 replaced the new assignment in H1 with placement copy construction or member-wise copying; neither improved the baseline. H5 exposed only the canonical 3D length helper or only the 2D helper, instead of repeating the previously tried combined exposure. The 3D-only case reduced the frame but did not reproduce retail's coordinate/filter overlap, and both variants worsened the byte count. Their standalone helper bodies independently match the complete 372-byte and 108-byte retail helpers with zero differing patched bytes and zero unresolved calls (`audit.log`). The diagnostic `normalized_instruction_edits` field in probe JSON is intentionally secondary and does not select the bank.

## Identity, ABI and remaining blocker

`retail.log` decodes the complete native body, its 121-byte constructor, the following destructor and the WorldBuilder debug body at VA 0x011B2240. The native decoder consumes exactly 2916 bytes and ends in a plain RET at 0x0047F92C. The constructor installs target vtable VA 0x00C47B8C at complete-object offset 0x10, whose first slot is VA 0x0087EDC9. The bank header's vtable 0x010C5590 is a stale BFME1 address, not target evidence. Primary virtual slot 0x238 resolves through the target table to VA 0x00668B20. The secondary receiver, data at -0x0C, object at -8, state machine at +0x20 and the native Coord3D/Object access offsets were checked against those bytes. The callee RET operands and complete callee disassembly are preserved in `callee-bodies.log` and `audit.log`. All 56 direct call sites, in chronological order, bind to the same retail destinations as their bank declarations. Native source-path and CritterDesync literals, the constructor table and the WorldBuilder counterpart support the AnimalAIUpdate identity; the BFME1 body remains a semantic guide rather than independent target naming or layout proof.

The first difference remains at +0x0C: frame allocation 0xA4 versus retail 0x8C. The bank emits 2923 bytes versus 2916. Retail places returning delta, no-emitter delta and no-emitter destination at EBP-0x34 with relationship temporary at EBP-0x3C overlapping that storage; emitter destination is at -0x24 and state/radius spill at -0x28. Baseline puts the returning delta with emitter destination, relationship at -0x48, and a separate no-emitter delta at -0x54. Longer displacements and branch distances then shift the remainder. The tested lifetime, destructor, copy-form and selective-visibility explanations do not close this. No additional experiment is justified by the evidence gathered in this run. Reopen with evidence explaining this exact stack packing without the observed copy or register regressions.

## Checks and clock

`check_csv.log`: PASS. `pin_consistency.log`: PASS. `audit.log`: PASS for full decode, constructor table, chronological direct-call bindings and both visible standalone coordinate helpers. Exact-body verification: FAIL for the baseline and every trial, with raw `*.explain.log` files. `build.sh`, add_match and find_declared_unmatched were not run because there is no matching source to land or changed Code source. `record.log` records the blocked verdict through re_log.py. No git mutation, network operation, claim, verification runner, background process or subagent was started.

The retained clock window is 2026-10-19 01:04:50 UTC to 2026-10-19 01:14:52 UTC, 10.03 minutes, measured from clock readings. It starts at the first retained timestamp after the initial instruction read. Model: gpt-6.1-sol. `receipt.json` stores the clock and unchanged bank hash. All changes are uncommitted.
