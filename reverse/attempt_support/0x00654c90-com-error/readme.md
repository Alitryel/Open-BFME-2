# Native COM exception member recovered as C++

Five whole bodies replace `Release\comraise.obj` from the MSVC 7.1 COM support archive, totaling 251 C++-exact bytes. The archive identities and retail accesses establish identity and ABI separately from the byte match. No Microsoft implementation source was read. The SDK supplies declarations only.

| Body | Retail RVA | Complete extent |
| --- | --- | ---: |
| `_com_error(long,IErrorInfo*,bool)` | 00654C90 | 54 |
| `_com_raise_error` | 00654CD0 | 51 |
| `_com_error(const _com_error&)` | 00654D10 | 50 |
| `_com_error` virtual destructor | 00654D50 | 38 |
| Compiler-emitted scalar deleting destructor | 00654D80 | 58 |

Each body has its own normal-hook commit. `ComRaise.cpp` uses real constructors, reference counting, LocalFree, virtual destruction and a C++ throw. Its G6 exception was proposed and accepted through `flag_defaults.py`; G7 produced a different constructor. No assembly, naked body, emitted bytes, alias, address pin, or added gate debt was used.

`ComError.h` is the single canonical class declaration. The class-contract/header-adoption lane was run and the existing consumer passed adoption, then all affected bodies passed the header gate. The generator initially omitted special members and the uppercase static mapper; the declaration API was completed from the existing verified view and native identities, preserving the tool-frozen 16-byte layout. Supplemental contract evidence records that limitation. Retail constructor accesses establish vptr/result/interface/allocation at offsets 0/4/8/12; the throw uses 16 bytes, the destructor releases +8 and passes +12 to LocalFree. The allocation element type remains unknown and opaque. No unproved ownership default is declared.

`metadata.json` compares all nine public non-text COMRAISE sections against the native object, including relocation names/types/addends, then independently follows relocations from all five exact code bodies into retail. All 150 bytes of RTTI, vtable and throw metadata match, with consistent internal target placement. Ordinary FuncInfo verification returns no graph for these routines, so it does not substitute for this explicit throw-metadata proof. Run `python3 reverse/attempt_support/0x00654c90-com-error/check_metadata.py` after ordinary builds to reproduce; it reads objects and retail and writes its report only under ignored build/.

The first constructor commit passed the normal full byte gate: 96,250 functions, 500 data rows, and the full converged-address check (23,120 sources, nine addresses, no second names). The final five-row source passes 5/5, and the prior static mapper/exception-info consumer still passes 2/2 plus its two GUID rows. Final code-identity and shadow data checks report no new findings. Affected-source placement finds no additional body or pin.

`focused-link.json` records a successful non-executed DLL link forcing all 18 recovered COM routines with the authored four COM units and typed CRT-free provider. Only native invkprxy remains; old comraise, comsupp, comutil and invkerr are omitted. This proves bounded symbol closure and absence of duplicate definitions, not a full-game census or runtime behavior.
