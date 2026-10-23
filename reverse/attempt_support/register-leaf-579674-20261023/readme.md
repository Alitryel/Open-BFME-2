# Two-byte unowned range at 0x00579674

Resolved as the file-static GetBonusRowNum helper using a real matched caller.
See [the subsequent identity and compiler proof](../get-bonus-row-579674-20261023.md).
The earlier failed trial below is retained for provenance.

Retail 0x00579674..0x00579676 is INC EAX; RET. The preceding rowed
parseStatString ends in its own RET at 0x00579673; the following rowed
StrategicHUD::ParseRowNum begins at 0x00579676. Neither neighbor branches into
this range. There is no Ghidra function boundary here. A fresh whole-image
literal RVA/VA search and raw E8/E9, short and near conditional-transfer
scan find no candidate incoming reference. Computed references remain possible.
Earlier inventory evidence: parallel_recovery_20261022.md section 3.

A private GCC 15.2.0 x86_64-w64-mingw32 / -m32 experiment with an explicit
regparm(1) unsigned increment emits INC EAX; RET. This shows a possible
register-input C++ view, not the original identity or ABI. It is not supported
by the normal MSVC gate. The complete GNU COFF .text is four bytes 40 C3 00 00,
including two trailing zero bytes even with --no-pad-sections; it is NOT a
whole-object exact match to the two-byte retail range. No object was copied
into a production cache and no padding was discarded for admission.

The candidate command was:
GCC -x c++ -m32 -Os -fno-asynchronous-unwind-tables -fno-ident
-falign-functions=1 -Wa,--no-pad-sections -c candidate.cpp -o private.obj

The original ABI/callable boundary and a supported reproducible compiler
remain prerequisites. No row, pin, Code source or verification change was made.
No new C++ bytes are claimed. t=12 minutes; model=GPT-6.
