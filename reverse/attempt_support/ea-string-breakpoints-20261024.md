# EA string breakpoint-intrinsic repairs

Base5c7cb7f78b; pinned BFME1 reference32774ab03393709a7f14331ba8d98d281a55ffd9.
The existing donor identities, native ABI, layouts and call/data relationships
remain unchanged. These remove inline assembly inside already-counted .cpp
files; they add no unique C++ coverage bytes to progress.py.

## utf8EncodedLength, RVA006D3DB0,133 bytes

Replace both inline INT3 statements with the genuine VC7.1 __debugbreak
intrinsic. The shipped crtdbg.h line391 defines _CrtDbgBreak() with that same
intrinsic. Every code-point threshold, signed comparison, assertion operand,
line number, global and return remains unchanged. There is no new compiler
flag, ABI adapter, input restriction, pin or artificial register constraint.

Private compiler diagnostics compare the complete133-byte emitted body:
bytes_match=true, emitted_size=claimed_size=133, no mismatching byte, no
unresolved call, no mask and no extent problem. Its8 DIR32 operands remain
explicitly unchecked by the diagnostic harness; the ordinary whole-file gate
and normal hooks provide the required reference checks instead. Whole-file
build and add_match both pass1/1 with4 string literals, zero skipped strings,
zero compiler float literals and zero named imports. The declared-definition
check passes. The published link index7e43384268 predicts LINKS131->131 bytes;
that historical census figure is not a claim of additional linked coverage.

## EAStringC::FreeData, RVA006D2EB0,118 bytes

The release worker now uses genuine __debugbreak for both assertion traps.
Reference-count validation, decrement, singleton check and sized deallocation
are unchanged. No compiler barrier or flag change is needed for this body.
The whole reference-counting unit verifies36/36 function rows, its one data
row,46 string literals and the parent-EH-based funclet mapping; no references
are skipped. The existing named-identity and data relationships are retained.
The published index predicts LINKS3023->3023 bytes for the complete unit.

## ??0EAStringC@@QAE@ABV0@@Z, RVA0x006D2FC0, 70 bytes

This body now uses the genuine breakpoint intrinsic.
The normal whole-file gate passes all36 function rows and the data row,
46 string literals and all4 EH records through the normal commit hook.
Other bodies retain their native bytes; identity, ABI, flags and data owners
are unchanged. Whole-unit published-index link preview passes.

## ?Reserve@EAStringC@@QAEXH@Z, RVA0x006D3760, 127 bytes

This body now uses the genuine breakpoint intrinsic.
The normal whole-file gate passes all36 function rows and the data row,
46 string literals and all4 EH records through the normal commit hook.
Other bodies retain their native bytes; identity, ABI, flags and data owners
are unchanged. Whole-unit published-index link preview passes.

## ?Assign@EAStringC@@QAEXPBD@Z, RVA0x006D4BF0, 144 bytes

This body now uses the genuine breakpoint intrinsic.
The normal whole-file gate passes all36 function rows and the data row,
46 string literals and all4 EH records through the normal commit hook.
Other bodies retain their native bytes; identity, ABI, flags and data owners
are unchanged. Whole-unit published-index link preview passes.

## ?rva006D3490@EAStringC@@QBE_NPBD@Z, RVA0x006D3490, 125 bytes

This body now uses the genuine breakpoint intrinsic.
The normal whole-file gate passes all36 function rows and the data row,
46 string literals and all4 EH records through the normal commit hook.
Other bodies retain their native bytes; identity, ABI, flags and data owners
are unchanged. Whole-unit published-index link preview passes.

## ?rva006D3C20@EAStringC@@QAEXXZ, RVA0x006D3C20, 61 bytes

This body now uses the genuine breakpoint intrinsic.
The normal whole-file gate passes all36 function rows and the data row,
46 string literals and all4 EH records through the normal commit hook.
Other bodies retain their native bytes; identity, ABI, flags and data owners
are unchanged. Whole-unit published-index link preview passes.
