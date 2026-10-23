// cl: /Ireference/shims/bfme2_ascii
// Cold-slice B8-imm32 const-int returners (second twin-free TU).
//
// Same 6-byte shape as ConstIntGetters9.cpp (mov eax,<IMM32> / ret) for
// range-free bodies (no matched row contains the address). Every entry was
// vetted: unclaimed, unpinned, xref-empty, absent from re_attempts.log and
// deleted_rows.csv, exact-disx confirms mov/ret, and no short-jcc in the
// preceding 16B targets the mov (je-into-mov arms, jump-table case clusters
// and mid-fn fragments screened out). Opaque address-derived names witness
// only the address and the returned constant.
// The include path only brings in the canonical AsciiString header; the
// region defaults still match the frameless 6-byte shape.

#include "ascii_string.h"

// Declaration-only view of the field table Rva002DF99DGet returns.
struct FieldParse;
extern const FieldParse Rva002E048CFieldParseTable[];

// ?Rva002DF99DGet@@YAHXZ @ 0x002df99d (6B): returns 0x00c04310, the
// LivingWorldBuilding field table Rva002E048CBuildingBlockParse.cpp defines.
int Rva002DF99DGet(void)
{
	return (int)Rva002E048CFieldParseTable;
}

// ?Rva00318B39Get@@YAHXZ @ 0x00318b39 (6B): returns 0x00de0878,
// &AsciiString::TheEmptyString.
int Rva00318B39Get(void)
{
	return (int)&AsciiString::TheEmptyString;
}
