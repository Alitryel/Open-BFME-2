# Authored CRT runtime member recovery

Eight whole native bodies move from the MSVC 7.1 archive into real C++, adding 283 C++-exact bytes. One previously recovered six-byte getter is repaired without claiming another six bytes. Each new body has its own normal-hook commit; the setter commit also repairs its existing getter because both must see the same private storage.

| Body | Retail RVA | Bytes |
| --- | --- | ---: |
| `_RTC_Initialize` | 00629BF0 | 68 |
| `_RTC_Terminate` | 00629C34 | 68 |
| `_setdefaultprecision` | 00629C7E | 18 |
| `_RTC_InitBase` | 0075A61F | 38 |
| `_RTC_Shutdown` | 0075A645 | 18 |
| `_RTC_GetErrDesc` | 0075AC98 | 24 |
| `_RTC_SetErrorType` | 0075ACB0 | 33 |
| `_RTC_SetErrorFunc` | 0075ACD1 | 16 |
| Existing `_RTC_GetErrorFunc` repaired | 0075ACE1 | 6, already C++ |

The original COFF symbols establish identities and ABIs independently of the byte matches. Implementations were authored from retail and those native objects, using public SDK declarations. No Microsoft implementation source was read. All four native members (`initsect.obj`, `fp8.obj`, `init.obj`, `userapi.obj`) retire together in this publication. The error-level array remains provided by the retained native `error.obj`; this source does not define a second array.

The two section walkers retain genuine allocation-free C++ loops and per-callback SEH. The opening-sentinel operands have COFF addend +4: the four zero sentinels are at RVAs 008FD04C, 008FD054, 008FD058 and 008FD060, while callback entries at 008FD050 and 008FD05C point to `_RTC_InitBase` and `_RTC_Shutdown`. An initial zero-addend data assumption was correctly rejected by the data gate and repaired before committing. All four typed sentinel rows pass the ordinary data verifier (16 bytes).

`seh-sections.json` independently verifies both full twelve-byte SEH tables, including their filter and handler code pointers. The ordinary FuncInfo checker returns no graph for this form, so it is not claimed as proof of these tables.

`verification.json` verifies all nine complete authored bodies, the one-byte private once flag, four-byte private callback, sixteen-byte private description table and all four complete diagnostic strings (133 literal bytes). Compiler sizeof probes prove the callback and table sizes. Native TU-local linkage is preserved: the external-only data ownership ledger does not claim these private data. A callback-only getter TU would constant-fold the private datum; preserving the native setter/getter relationship retains its real storage.

The old getter's address-named external and artificial emission helper are removed, and their two hatch-register lines (three occurrences) are deleted. Only the repaired callback address record in data_ledger.csv is re-derived, using the repository's collect/choose policy and current exact COFF bindings. Its old 84-byte range is an upper bound to the next ledger address; the private callback itself is four bytes, not an 84-byte ownership claim. The record now names the real native private symbol and its source. Enforced data checking reports no findings without any baseline allowance.

Two admitted code-name pins bind the existing `_controlfp` and `_CRT_RTC_INIT` import thunks. Each entire six-byte FF25 body and exact msvcr71 IAT export is independently checked against the PE. Neither pin emits a new wrapper or counts as C++ progress. The x87 initializer requests 53-bit precision using mask 0x30000 and value 0x10000. The late RTC cluster has no voting flag region, so its verified O1/G7 flags remain explicit; no compiler-default override is added.

`focused-link.json` records a successful, non-executed DLL link forcing all nine routines from the four authored units, using the original vendored CRT and ordinary Win32 import libraries. This proves bounded symbol closure and absence of duplicate definitions. It does not prove full-game section placement, census results or runtime behavior. Final source placement finds no additional body or pin; the new-variant preview finds no conflict. The published census index still uses retail-truth-1 because it has no reference graph.

After ordinary builds, run `python3 reverse/attempt_support/0x00629bf0-crt-runtime/check_data.py` and `python3 reverse/attempt_support/0x00629bf0-crt-runtime/check_sections.py` from the repository root to reproduce the data, code and SEH checks. Reports and compiler probes stay under ignored build/.

The separate cookie initializer is banked at reverse/attempts/0x00629ca8.cpp: a complete 102-byte C++ draft whose remaining mismatch is POP ESI scheduling around the fallback branch. It is evidence only and contributes no progress. The type_info vector-deleting-destructor emission lead is recorded as blocked; no production type_info source was changed.
