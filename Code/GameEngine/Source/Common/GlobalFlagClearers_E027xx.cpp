// Nine B2-native flag-word clearers on nine .data flag words
// (0x00E027A8-0x00E027FC):
//
//     mov eax,[<address>] / and al,<mask8> / mov [<address>],eax / ret
//
// Same /G7 byte-register narrowing as GlobalFlagClearers_08.cpp (defaults
// emit `and eax,imm`). Each body carries a .rdata table slot. Identity is
// not recovered; names derive from addresses,
// following GlobalFlagClearers_DFEExx.cpp.
// cl: /G7 /MD /EHsc /DNDEBUG

extern unsigned int g_Va00E027A8;
// g_Va00E027A8: matched references place it at VA 0xe027a8 (zero-filled .bss).
unsigned int g_Va00E027A8;
extern unsigned int g_Va00E027B4;
// g_Va00E027B4: matched references place it at VA 0xe027b4 (zero-filled .bss).
unsigned int g_Va00E027B4;
extern unsigned int g_Va00E027CC;
// g_Va00E027CC: matched references place it at VA 0xe027cc (zero-filled .bss).
unsigned int g_Va00E027CC;
extern unsigned int g_Va00E027D4;
// g_Va00E027D4: matched references place it at VA 0xe027d4 (zero-filled .bss).
unsigned int g_Va00E027D4;
extern unsigned int g_Va00E027DC;
// g_Va00E027DC: matched references place it at VA 0xe027dc (zero-filled .bss).
unsigned int g_Va00E027DC;
extern unsigned int g_Va00E027E4;
// g_Va00E027E4: matched references place it at VA 0xe027e4 (zero-filled .bss).
unsigned int g_Va00E027E4;
extern unsigned int g_Va00E027EC;
// g_Va00E027EC: matched references place it at VA 0xe027ec (zero-filled .bss).
unsigned int g_Va00E027EC;
extern unsigned int g_Va00E027F4;
// g_Va00E027F4: matched references place it at VA 0xe027f4 (zero-filled .bss).
unsigned int g_Va00E027F4;
extern unsigned int g_Va00E027FC;
// g_Va00E027FC: matched references place it at VA 0xe027fc (zero-filled .bss).
unsigned int g_Va00E027FC;

unsigned int Rva00780ACBClearFlag(void)
{
	return g_Va00E027A8 &= 0xFFFFFFFEu;
}

unsigned int Rva00780AF4ClearFlag(void)
{
	return g_Va00E027B4 &= 0xFFFFFFFEu;
}

unsigned int Rva00780D27ClearFlag(void)
{
	return g_Va00E027CC &= 0xFFFFFFFEu;
}

unsigned int Rva00780D3EClearFlag(void)
{
	return g_Va00E027D4 &= 0xFFFFFFFEu;
}

unsigned int Rva00780D79ClearFlag(void)
{
	return g_Va00E027DC &= 0xFFFFFFFEu;
}

unsigned int Rva00780DB7ClearFlag(void)
{
	return g_Va00E027E4 &= 0xFFFFFFFEu;
}

unsigned int Rva00780E59ClearFlag(void)
{
	return g_Va00E027EC &= 0xFFFFFFFEu;
}

unsigned int Rva00780E8AClearFlag(void)
{
	return g_Va00E027F4 &= 0xFFFFFFFEu;
}

unsigned int Rva00780EB3ClearFlag(void)
{
	return g_Va00E027FC &= 0xFFFFFFFEu;
}
