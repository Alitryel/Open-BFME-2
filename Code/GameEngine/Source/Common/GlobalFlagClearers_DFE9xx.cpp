// Ten B2-native flag-word clearers on ten .data flag words
// (0x00DFE944-0x00DFE9CC):
//
//     mov eax,[<address>] / and al,<mask8> / mov [<address>],eax / ret
//
// Same /G7 byte-register narrowing as GlobalFlagClearers_08.cpp (defaults
// emit `and eax,imm`). Each body carries a .rdata table slot. Identity is
// not recovered; names derive from addresses,
// following GlobalFlagClearers_DFEExx.cpp.
// cl: /G7 /MD /EHsc /DNDEBUG

extern unsigned int g_Va00DFE944;
// g_Va00DFE944: matched references place it at VA 0xdfe944 (zero-filled .bss).
unsigned int g_Va00DFE944;
extern unsigned int g_Va00DFE988;
// g_Va00DFE988: matched references place it at VA 0xdfe988 (zero-filled .bss).
unsigned int g_Va00DFE988;
extern unsigned int g_Va00DFE990;
// g_Va00DFE990: matched references place it at VA 0xdfe990 (zero-filled .bss).
unsigned int g_Va00DFE990;
extern unsigned int g_Va00DFE998;
// g_Va00DFE998: matched references place it at VA 0xdfe998 (zero-filled .bss).
unsigned int g_Va00DFE998;
extern unsigned int g_Va00DFE9A0;
// g_Va00DFE9A0: matched references place it at VA 0xdfe9a0 (zero-filled .bss).
unsigned int g_Va00DFE9A0;
extern unsigned int g_Va00DFE9A8;
// g_Va00DFE9A8: matched references place it at VA 0xdfe9a8 (zero-filled .bss).
unsigned int g_Va00DFE9A8;
extern unsigned int g_Va00DFE9B0;
// g_Va00DFE9B0: matched references place it at VA 0xdfe9b0 (zero-filled .bss).
unsigned int g_Va00DFE9B0;
extern unsigned int g_Va00DFE9B8;
// g_Va00DFE9B8: matched references place it at VA 0xdfe9b8 (zero-filled .bss).
unsigned int g_Va00DFE9B8;
extern unsigned int g_Va00DFE9C4;
// g_Va00DFE9C4: matched references place it at VA 0xdfe9c4 (zero-filled .bss).
unsigned int g_Va00DFE9C4;
extern unsigned int g_Va00DFE9CC;
// g_Va00DFE9CC: matched references place it at VA 0xdfe9cc (zero-filled .bss).
unsigned int g_Va00DFE9CC;

unsigned int Rva0077118FClearFlag(void)
{
	return g_Va00DFE944 &= 0xFFFFFFFEu;
}

unsigned int Rva00771BCFClearFlag(void)
{
	return g_Va00DFE988 &= 0xFFFFFFFEu;
}

unsigned int Rva00771BE6ClearFlag(void)
{
	return g_Va00DFE990 &= 0xFFFFFFFEu;
}

unsigned int Rva00771BFDClearFlag(void)
{
	return g_Va00DFE998 &= 0xFFFFFFFEu;
}

unsigned int Rva00771C14ClearFlag(void)
{
	return g_Va00DFE9A0 &= 0xFFFFFFFEu;
}

unsigned int Rva00771C2BClearFlag(void)
{
	return g_Va00DFE9A8 &= 0xFFFFFFFEu;
}

unsigned int Rva00771C54ClearFlag(void)
{
	return g_Va00DFE9B0 &= 0xFFFFFFFEu;
}

unsigned int Rva00771C6BClearFlag(void)
{
	return g_Va00DFE9B8 &= 0xFFFFFFFEu;
}

unsigned int Rva00771C94ClearFlag(void)
{
	return g_Va00DFE9C4 &= 0xFFFFFFFEu;
}

unsigned int Rva00771E82ClearFlag(void)
{
	return g_Va00DFE9CC &= 0xFFFFFFFEu;
}
