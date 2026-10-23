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
