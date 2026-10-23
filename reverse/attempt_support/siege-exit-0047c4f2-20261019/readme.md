# SiegeEngineContain exitObjectViaDoor

Exact result: `?exitObjectViaDoor@SiegeEngineContain@@UAEXPAVObject@@W4ExitDoorType@@@Z`, RVA `0x0047C4F2`, 1077 bytes, in `Code/GameEngine/Source/GameLogic/Object/Contain/SiegeEngineContainXfer.cpp`. `add_match.py` verified both rows in the unit, recorded `landed`, and deleted the prior bank. No pins or verifier changes were needed. All changes remain uncommitted.

## Identity and ABI evidence

Retail constructor RVA `0x0047C21E` stores the ExitInterface vtable VA `0x00C46F48` at object offset `+0x30`; slot 2 is VA `0x0087C4F2`. WorldBuilder VA `0x011A9380` independently names `SiegeEngineContain::exitObjectViaDoor` and identifies the original SiegeEngineContain.cpp source. Retail ends with `ret 8` at RVA `0x0047C924`, ending exclusively at `0x0047C927`. It reads the owner and module data at ExitInterface offsets `-0x28` and `-0x2C`, tests the closed flag at `+0xF4`, and calls contain slot 41 from receiver `-0x10`. Raw evidence is in `build/siege-exit-w8/identity-retail.log`, `retail.txt`, and `wb.txt`.

The BFME1 OpenContain implementation is a semantic guide for obstacle handling and path commands. The target's filter, ladder and wall branches, layouts, arithmetic and callees were checked against BFME2 retail. The command and vector-assignment definitions come from existing byte-verified BFME2 units; both emitted helper copies were independently checked against their existing owner rows and match exactly. The address-derived helper identities are retained. The corrected declarations use protected Object::findModule and Object::rva0028ACDC(int), as the existing retail providers require.

## Experiments and measurements

All nine prior verdicts were read first. Their cited `build/big/siege-exit/helper_real_flags.cpp` and `wave7/packets/G1-r9/COORD3D.md` are absent in this checkout; none cites a tracked attempt_support file. Hypotheses and refutation conditions were recorded before probes in `build/siege-exit-w8/hypotheses.md`.

| Probe | Result |
|---|---|
| Original bank | 1102 bytes, one structural region, 20 memory and seven register operand differences reported by align_diff. |
| Corrected declarations | Identical emitted code. |
| Shared named allocator | Refuted: frame remains 0x74, with two additional register differences. |
| Visible full vector assignment and command wrapper with the bank's scalar radius placement | Frame becomes native 0x68, both vectors share -0x44, and the two cleanup tails merge. The remaining difference is one missing four-byte EH-state clear. |
| Restore only the existing throwing deallocator specialization | Exact 1077 bytes after strict relocation resolution. |
| Integrate into the destination unit | Exact after preserving the closed flag as a bool lvalue. Existing 464-byte xfer remains exact. The visible command wrapper is inline and noinline, preserving its body for optimization without introducing a second strong definition. |

Relocation-masked positional differing bytes within the 1077-byte retail extent fall from 500 to zero; excess emitted bytes fall from 25 to zero. This positional count is supplementary: align_diff structural regions fall from one to zero and register differences from seven to zero. Its remaining 18 memory differences are relocation placeholders, not defects. `home-inline-explain.log` reports exact after resolving all relocations, including the call identities. Machine-readable measurements are in `build/siege-exit-w8/before-after.json`. Trial sources, disassemblies, raw logs and command receipts remain in that task folder.

## Verification and coordinator action

`add-match.log` passes both unit rows, string literals, floating constants and imports. `final-build-lf.log` is the final build after restoring the source's original LF line endings. `final-declarations.log` passes find_declared_unmatched with --fail; `pin-consistency.log` passes. `final-evidence.log` verifies both emitted helper bodies. All these raw logs live under `build/siege-exit-w8/`.

`check-csv.log` records a FileNotFoundError: working-tree check_attempts enumerates the still-indexed bank and attempts to read it after add_match removed it. The worker is forbidden to stage files, so it cannot update that index state. The coordinator must stage the bank deletion together with the source and ledger changes, then rerun `python tools/check_csv.py`. The verifier was left unchanged. No network, claims, Git write, verification runner, or background task was used.

Elapsed time and command return codes are recorded in the task folder. Model: gpt-6.1-sol.
