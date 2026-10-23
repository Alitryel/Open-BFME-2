Exact: `?parseWindow@@YAPAVGameWindow@@PAVFile@@PAD@Z`, RVA `0x00316E8F`, 910 bytes, in `Code/GameEngine/Source/GameClient/GUI/GameWindowManagerScript.cpp`. `add_match.py` verified the row, recorded `landed` and deleted the score-zero bank. The changes remain uncommitted. Starting revision: `8a0843b9cf6fd749f00fca6cc938eb07e288a81c`. Reference pointer reviewed: `a18d9ed50607e9175de4d6568798d7d73119de09`. Model: `gpt-6.1-sol`.

The new prerequisite was the already landed 407-byte child parser in the real static-state owner. The previous seven verdicts and the two archived default-parser family banks were reviewed; those two archived banks differ only in the leading symbol comment. Their remaining old factory/record interfaces explain why merely repeating their File fixes would not finish this body. The farm bank itself has incorrect callback arguments, instance declarations and END/CHILD behavior, including an infinite loop. Its implementation was discarded rather than reshaped.

Identity follows the same-name Zero Hour parser already present in the owner, the target's NAME/STATUS/STYLE/callback dispatch table, required WINDOWTYPE/SCREENRECT parsing, DATA/END/CHILD control flow, constructor/destructor calls, and mutual child-parser calls. The local WorldBuilder lead independently supplies the same name and original source path, but remains a string-based lead rather than an exported target symbol. The reviewed BFME 1 parser supplies semantic and structural guidance; its 1328-byte body is not treated as target byte or layout evidence. All 37 EA comment lines in the owner's parseWindow body are preserved in their original order. Applicable EA factory comments are also retained.

Target instructions establish the whole boundary through `0x0031721D`, two stack parameters, the 52-byte creation record, imported strtok and isspace, File scanString at 0x24, Display width/height at 0x40/0x44, manager destruction at 0x8C, getDataTemplate(type, null), and actual private conventions for readUntilSemicolon, parseData, parseScreenRect, createWindow and parseChildWindows. Their real definitions remain visible together; no synthetic caller, pin, alias, asm, optimization pragma or scheduling device was added. The shared record is a target layout view; its original target type/global spelling is not established.

The five address-taken callbacks now export their existing cdecl implementations and store into one shared POD record, removing their independent callback datums. The owner's table includes the native WINCLASS entry and uses those real callback providers. Existing GameWindowManager and Display globals are retained and cast to local slot views. `data_check.py` reports zero shadow findings and zero second bindings at converged addresses.

Measurements are positional bytes after normal resolver patching, with missing bytes counted as differences: original bank 819 differing bytes (819 emitted bytes versus 910 target bytes; ten unresolved call sites), final body zero differing bytes (910 emitted bytes; no unresolved calls). Raw align_diff results are 38 structural regions, 19 memory differences and 40 register differences before; zero structural regions, 25 raw memory differences and zero register differences after. Every final memory difference is a DIR32 relocation, as the successful strict byte gate confirms. This is an exact result, not a claim of partial improvement from the raw operand counts. Both lengths and all 259 target instructions agree.

Changed deliverables:

- `Code/GameEngine/Source/GameClient/GUI/GameWindowManagerScript.cpp`.
- `Code/GameEngine/Source/GameClient/GUI/WindowScriptCreateRecord.h` (new).
- `Code/GameEngine/Source/GameClient/GUI/GameWindowManagerScript_parseWinClass.cpp`.
- `Code/GameEngine/Source/GameClient/GUI/GameWindowManagerScript_parseSystemCallback.cpp`.
- `Code/GameEngine/Source/GameClient/GUI/GameWindowManagerScript_parseInputCallback.cpp`.
- `Code/GameEngine/Source/GameClient/GUI/GameWindowManagerScript_parseDrawCallback.cpp`.
- `Code/GameEngine/Source/GameClient/GUI/GameWindowManagerScript_parseTooltipCallback.cpp`.
- `reverse/functions.csv` and `reverse/re_attempts.log`, changed only through add_match.py.
- `reverse/attempts/0x00316e8f.cpp`, deleted by add_match.py.
- This evidence file.

Raw evidence and trials remain in `build/parse-window-316e8f/`; normal object and dependency caches are in `build/match/`. The original bank and original owner are preserved there as byte copies. `hypotheses.md` records each new hypothesis, its evidence and its refutation condition before the corresponding experiment. `retail.log`, `table.log`, `wb-identity.log`, the recovered prior banks, all trial sources and the alignment logs permit the result to be rederived.

Verification receipts:

- PASS: registration and strict primary verification, `build/parse-window-316e8f/add-match-success.log`. The initial comma-containing note was rejected without mutation; its raw output remains in `add-match.log`.
- PASS: all 29 affected functions across six sources, with string, float and import checks, `build/parse-window-316e8f/verified-final.build.log`.
- PASS: all six changed sources' declared-definition checks, `build/parse-window-316e8f/declared-final.log`.
- PASS: pin consistency, `build/parse-window-316e8f/pin-consistency.log`.
- PASS: converged-data enforcement, `build/parse-window-316e8f/data-converged.log`; shadow data check, `build/parse-window-316e8f/data-shadow.log`.
- PASS: five exact EH metadata rows, `build/parse-window-316e8f/eh-verification.log` and `eh-verification.json`.
- PASS: byte counts and call resolution, `build/parse-window-316e8f/byte-counts.log`; alignment, `final.align.log`; source/comment audit, `source-audit.log`; whitespace check, `diff-check.log`.
- FAIL: working-tree `check_csv.py` crashes when its index-derived bank list reads the bank that add_match.py deleted, `build/parse-window-316e8f/check-csv.log`. The coordinator must stage the deletion and new header with the other deliverables, then rerun the required ledger check. No verifier was changed or bypassed, and no Git write was run here. The add_match claim-settlement warning likewise says the new header is not tracked yet; it does not invalidate byte verification.

No linking or runtime result is claimed. This checkout has no published link index, and no network or forbidden runner was used. No background task was started. Work began at `2026-10-19 05:17:20 UTC`; the final chat handoff reports the clock-measured elapsed minutes.
