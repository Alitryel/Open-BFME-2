# ControlBar context evaluation at 0x0031D230

Result: blocked. Keep reverse/attempts/0x0031d230.cpp byte-for-byte unchanged. No candidate satisfies the closer-bank rule and no Code source, pin or function row changed. The symbol remains ?rva0031D230@ControlBar@@QAEXXZ; the retail extent is 968 bytes. The approved destination remains Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBar.cpp.

## Inputs and identity

Checkout: 1d7d3716bc22594f17dca9ec14b3d2ccd4a337c9. BFME 1 donor: a18d9ed50607e9175de4d6568798d7d73119de09. MSVC 13.10.3077 uses the bank's /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc flags and reference/shims/bfme2_ascii. BFME_OBJSTORE=off for every measurement; every trial had a distinct source path and its object removed first.

Ghidra records the exact start and extent. Retail has its EH prologue at RVA 0x0031D230 and final ret at 0x0031D5F7; the next row starts at 0x0031D5F8. The matched caller at 0x0053E4B1 tail-calls it with the same ControlBar receiver in ECX, and 0x0053E6E1 is a direct thunk. Its 47 calls reproduce the bank's call sequence and virtual slots, including 0x118, 0x124, 0x130, 0x70, 0xD8, 0xE0 and 0x4C. Existing callee rows and pins resolve every reference. ZH evaluateContextUI and WorldBuilder VA 0x00C2C270 support the purpose; the address-derived method name is retained because purpose correspondence alone does not prove the original BFME 2 spelling. These facts and the actual compiler command are in build/worker_0031d230/retail.log, wb-retail.log and callee-map.log.

## Preregistered experiments and measurements

All eight earlier target verdicts were read. The cited build/big/control_context_visibility.py, control_context_lifetime.py, control_context_roles.py and build/learnings-20261016 are absent here. Their exact old trials cannot be inspected. The bank's comments and its original bytes remain intact. Prior evidence and missing-path receipts are in prior-verdicts.log and evidence-availability.json under the task scratch directory. Each new hypothesis, its evidence and refutation rule was written to hypotheses.md before its trial.

H1 adopted the matched BFME 1 sibling's early returns after multi-selection and null-drawable cases. H2 replaced the list shim with ZH InGameUI.h's actual std::list<Drawable *> and used the existing STLport headers. H3 isolated const front()'s reference return in the original shim. H4 isolated H2's STLport header environment with the original shim. H5 spelled the later H2 front() as *begin(), the implementation used by STLport itself.

| Trial | Emitted bytes | Structural regions | Reported memory | Reported register | Positional differing bytes |
|---|---:|---:|---:|---:|---:|
| before | 967 | 4 | 18 | 3 | 716 |
| h1 | 967 | 4 | 18 | 3 | 716 |
| h2 | 959 | 3 | 22 | 9 | 755 |
| h3 | 967 | 4 | 18 | 3 | 716 |
| h4 | 967 | 4 | 18 | 3 | 716 |
| h5 | 959 | 3 | 22 | 9 | 755 |

The columns come from each trial's raw align_diff output and metrics receipt. Relocation and branch lines are not defects. The tool's reported memory class also includes unpatched global-address operands; those do not establish layout defects. Positional differing bytes are diagnostic only and do not rank candidates. H1, H3 and H4 emit exactly the original raw code. H2 and H5 emit identical raw code to each other. Hash comparisons are in raw-comparison.json. Each distinct source configuration was compiled once (n=1); raw object equality was checked separately.

H2 fixes the original contain-block allocation: drawable remains EBX, localPlayer is stored at [ebp-0x14], and context 3 receives the drawable. It also moves the early this/selectedDrawables allocations, merges the null-drawable and null-object exits, and changes a later list reload. Its lower structural-region count comes with more memory and register differences, so it must not replace the bank. H3 and H4 show that reference-return type and header environment alone do not produce this effect; H5 shows removing the later front wrapper is inert. The successful local allocation and its global regressions are coupled in the tested real-list form. No justified further experiment was selected.

The bank's remaining mismatch is still its extra drawable spill at +0x8C, localPlayer in EBX instead of [ebp-0x14], the shifted contain-block setup, a memory push of the drawable for context 3 instead of push EBX, and push EBX instead of the localPlayer stack slot for virtual slot 0x4C. It emits one byte fewer than retail.

## Checks and retained work

align_diff.py and explain_mismatch.py completed for before and h1 through h5; all remain byte mismatches with no unresolved callees. Raw outputs are build/worker_0031d230/<trial>-align.log and <trial>-explain.log. No build.sh or add_match.py run is claimed because there is no exact candidate. check_csv.py and pin_consistency.py --check pass; git diff --check passes. Raw logs are check-csv.log, pin-consistency.log and diff-check.log in that directory. Frozen-source checks are inapplicable because no source under Code changed.

Every trial source, source diff, script and raw probe log remains under build/worker_0031d230; its artifact-manifest.json also names the ordinary build/match object-cache files. Those files are intentionally retained for the coordinator under the assignment's evidence rule. All launched subprocesses completed; no background process was started. No network, claim, writing git command or verification runner was used.
