# Replace the stack-probe byte spray with the supplied CRT provider

Retail RVA 0x00629000..0x0062903D is the 61-byte MSVC 7.1 stack probe.
Both __chkstk and __alloca_probe are external symbols at offset zero in
build\intel\dll_obj\chkstk.obj of vendor/msvc71crt/msvcrt.lib. Its complete
61-byte section equals retail, with zero relocation fields. Object SHA256:
6c76684eb3c123899b38ec4233b2cf9bf3303d64b89884f01c04a6f0671e045a.
The bundled toolchain msvcrt.lib holds the identical object. libcmt.lib and
libcmtd.lib independently hold byte-identical 61-byte versions too.

Existing symbols.csv pins __chkstk and __alloca_probe already identify this
RVA. The __alloca_probe pin cites the native _ATL_SAFE_ALLOCA call path in
CImage::CreateFromGdiplusBitmap. The archive supplies both real symbol names,
and the complete runtime helper contract, rather than a guessed void() ABI.
No pointer values or instructions need reconstruction from a retail dump.

The old StackProbeBodyThunk.cpp consists entirely of a naked _emit spray.
Its original contents are archived here, unchanged, as evidence. It has no
other function row or code references. The old claim is retracted in its own
commit as required by add_match; the verified __chkstk library row follows
in a separate atomic commit. Both are published together. No new alias,
pin, compiler override or verifier change is needed.

This is 61 bytes of supplied-library coverage, not 61 newly authored C++
bytes. Ordinary C++ cannot express its EAX stack-allocation/return-address
contract. The existing stack checker and EH prologue also have nonordinary
entry contracts; this result does not establish C++ replacements for them.

## Related EH helper adopted; stack checker retained in assembly

The same existing archive also contains build\intel\dll_obj\ehprolog.obj,
whose complete 31-byte __EH_prolog section equals retail RVA 0x00629188,
with zero relocations. Object SHA256:
7949625b94a70bd9e337937ec23ca3adbc979d486f47d203b1942cb56b93ccf4.
Its old MASM owner is archived unchanged here and repointed using normal
add_match --replace-existing. Together __chkstk and __EH_prolog add 92
bytes of supplied-library coverage, not authored C++ credit.

The archive's ..\build\intel\dll_obj\stack.obj also matches all 35 bytes
of __RTC_CheckEsp and its REL32 to ?_RTC_Failure@@YAXPAXH@Z. Object SHA256:
df82d34b85b5b31b606f158fd9b7db335eb01fcf7e8fc5699876e2cd37d1c587.
A normal trial admission passed byte verification but exposed a new exclusive
duplicate @_RTC_CheckStackVars@8: the archive member brings a second copy of
the independently reconstructed 90-byte C++ checker in CRT/RtcStack.cpp.
Therefore the 35-byte checker remains on its original MASM owner. The trial
was reversed through normal verifying add_match before publication. No new
alias, forced multiple definition, weaker duplicate check, or loss of the
90-byte C++ recovery was accepted. This candidate earns zero new credit.

The shadow identity report also lists the existing private type_info copy
constructor duplicate. Its source and ti_inst.obj archive member were already
owners before this batch; neither definition was changed or newly introduced.
The two adopted objects chkstk.obj and ehprolog.obj define no such constructor.

Normal archive admission verifies all archive-owned rows, including the
new helper bodies; the stack-checker restoration verifies its entire 35-byte
MASM body too. No archive bytes, pins, baseline or gate were changed. The
security-cookie helper is also in the archive, but its recorded thin-body
rejection still applies; no weaker admission was tried.
