# Authored COM utility recovery

The native `Release\comutil.obj` member of the existing MSVC 7.1 COM support library supplies five independently named routines. The C++ here was reconstructed from retail disassembly, PE imports, the existing ledger names, and native object boundaries. No Microsoft implementation source was read or copied.

| Routine | Retail RVA | Full extent |
| --- | --- | ---: |
| `_com_util::CheckError(long)` | `006547B0` | 15 |
| `_variant_t(long,unsigned short)` | `006547C0` | 111 |
| `_variant_t::~_variant_t()` | `00654830` | 18 |
| `_com_util::ConvertStringToBSTR` | `00654850` | 352 |
| `_com_util::ConvertBSTRToString` | `006549B0` | 343 |

The string-to-BSTR extent includes its 328-byte instruction body and 24 bytes of same-section SEH scope metadata. The extent check rejected the shorter claim as truncated; the full 352 bytes agree with retail. The BSTR-to-string extent includes its catch funclet; no separate overlapping catch row is claimed. Its associative C++ exception graph is independently exact.

The 16-byte `_variant_t` view follows native tag accesses at offset zero and union accesses at offset eight. The three reserved words and unused union bytes remain untouched by the constructor. The native mangled constructor and destructor names establish class identity and ABI independently of the byte match.

PE import evidence establishes unsuffixed `kernel32.dll!lstrlen`, `WideCharToMultiByte`, `MultiByteToWideChar`, `GetLastError`, `SysAllocString`, `VariantClear`, and `msvcr71.dll!wcslen`. Retail uses the linker-owned public wcslen thunk at RVA `006291CC`, with IAT `00BBA6AC`. A six-byte C++ public wrapper matched but failed a focused real link with LNK2005 because the CRT import member defines its public thunk and IAT together. That unpublished attempt was retracted. The checked import pin is used instead.

All four previously library-backed rows move together in this publication, so the old `Release\comutil.obj` member is no longer selected by the matched-object inventory. Its private `vtMissing` storage is not reproduced under another global name: existing `g_bfmeArgDXE` in `BfmeConv793.cpp` already supplies the native 16-byte VT_ERROR / DISP_E_PARAMNOTFOUND value at VA `00DD7F18`; its exact cleanup at RVA `007B9B40` and registration at `007B55D0` are already authored. No retained COM member references `vtMissing`.

A bounded, non-executed DLL link forces all five authored routines with the other four native COM members (`comsupp`, `comraise`, `invkprxy`, `invkerr`) and normal CRT/Win32/OLE import libraries, omitting old `comutil`. This checks symbol closure and duplicate-definition removal within that scope. It is not a full-game census or a runtime test. The repository's normal byte/import/exception gates remain the production acceptance checks.
The final allocator binding uses the typed project veneer `CrtFree(void*)` at RVA `00628F98`, replacing the anonymous generated import placeholder without adding exact C++ bytes. Both this unit and the existing pointer-array RemoveAll caller use it. The global `_free` remains the game allocator at `00030830`. A focused link using the broad old generated import object failed on 68 unrelated unresolved imports; the final successful test uses the independently compiled typed provider instead.

The whole-current-ledger link preview refused to judge the tree because 10,592 providers lack current compiler evidence. No full-game LINKED result is claimed. The normal index new-variant check reports no new conflicting variants. The shadow code-identity checker still reports the compiler-generated `__except_handler3` reference as unowned: retail `00628FF0` is exactly `FF25` through `00BBA6E0`, whose PE import is `msvcr71.dll!_except_handler3`; the successful focused link resolves it through the CRT import library. No baseline entry was added.
