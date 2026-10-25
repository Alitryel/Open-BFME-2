// Address-valued getters from the ConstIntGetters5.cpp family.
// Named data providers supply recovered globals; unresolved values
// remain literal until their providers are recovered.
//
// Cold-slice B8-imm32 const-int returners without vtable carriage (twin-free TU).
//
// Same 6-byte shape as ConstIntGetters4.cpp (mov eax,<IMM32> / ret) but for
// bodies with no .rdata vtable slot, no direct callers and no branch sources:
// each follows a ret-imm (C2-04-00) and is an unclaimed leaf, so the opaque
// address-derived name witnesses only the address and the returned constant.
// Kept in a fresh TU so this batch does not contend with the hot
// ConstIntGetters4 appends on origin/master. No // cl: line (defaults match
// the frameless 6-byte shape).


// ?Rva001DB686Get@@YAHXZ @ 0x001db686 (6B): returns 0x00c0cd88.
// Follows a ret-4 (prev C2-04-00), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
struct FieldParse;
struct _D3DADAPTER_IDENTIFIER8;
extern "C" const FieldParse __identifier("?m_controlBarSchemeFieldParseTable@ControlBarSchemeManager@@2QBUFieldParse@@B")[];
extern "C" char __identifier("?ProcessorString@CPUDetectClass@@0PADA")[48];
extern "C" _D3DADAPTER_IDENTIFIER8 __identifier("?CurrentAdapterIdentifier@DX8Wrapper@@1U_D3DADAPTER_IDENTIFIER8@@A");
extern const char *g_Va00DC85C4Names[9];

int Rva001DB686Get(void)
{
	return (int)__identifier("?m_controlBarSchemeFieldParseTable@ControlBarSchemeManager@@2QBUFieldParse@@B");
}


// ?Rva0011C460Get@@YAHXZ @ 0x0011c460 (6B): returns 0x00dec5e8.
// int3-padded both sides, no direct callers. Opaque address-derived name.
int Rva0011C460Get(void)
{
	return (int)&__identifier("?CurrentAdapterIdentifier@DX8Wrapper@@1U_D3DADAPTER_IDENTIFIER8@@A");
}


// ?Rva0033A7BBGet@@YAHXZ @ 0x0033a7bb (6B): returns 0x00dc85c4.
// Follows a call plus ret tail. No direct callers. Opaque
// address-derived name.
int Rva0033A7BBGet(void)
{
	return (int)g_Va00DC85C4Names;
}


// ?Rva00611030Get@@YAHXZ @ 0x00611030 (6B): returns 0x00e08c58.
// int3-padded both sides, no direct callers. Opaque address-derived name.
int Rva00611030Get(void)
{
	return (int)__identifier("?ProcessorString@CPUDetectClass@@0PADA");
}

