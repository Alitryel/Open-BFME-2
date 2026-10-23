// Ten B2-native flag-word clearers across ten .data flag words of one
// contiguous run (0x00781D99-0x00781E68):
//
//     mov eax,[<address>] / and al,0xFE / mov [<address>],eax / ret
//
// All ten clear al bit 0. Same /G7 byte-register narrowing as
// GlobalFlagClearers_08.cpp (defaults emit `and eax,imm`). Each body
// carries a .rdata table slot (0x0092CE54 and on). Identity is not
// recovered; names derive from addresses, following
// GlobalFlagClearers_08.cpp.
// cl: /G7 /MD /EHsc /DNDEBUG

extern unsigned int g_Va00E029F0;
// g_Va00E029F0: matched references place it at VA 0xe029f0 (zero-filled .bss).
unsigned int g_Va00E029F0;
extern unsigned int g_Va00E029FC;
// g_Va00E029FC: matched references place it at VA 0xe029fc (zero-filled .bss).
unsigned int g_Va00E029FC;
extern unsigned int g_Va00E02A1C;
// g_Va00E02A1C: matched references place it at VA 0xe02a1c (zero-filled .bss).
unsigned int g_Va00E02A1C;
extern unsigned int g_Va00E02A28;
// g_Va00E02A28: matched references place it at VA 0xe02a28 (zero-filled .bss).
unsigned int g_Va00E02A28;
extern unsigned int g_Va00E02A48;
// g_Va00E02A48: matched references place it at VA 0xe02a48 (zero-filled .bss).
unsigned int g_Va00E02A48;
extern unsigned int g_Va00E02A54;
// g_Va00E02A54: matched references place it at VA 0xe02a54 (zero-filled .bss).
unsigned int g_Va00E02A54;
extern unsigned int g_Va00E02A74;
// g_Va00E02A74: matched references place it at VA 0xe02a74 (zero-filled .bss).
unsigned int g_Va00E02A74;
extern unsigned int g_Va00E02A80;
// g_Va00E02A80: matched references place it at VA 0xe02a80 (zero-filled .bss).
unsigned int g_Va00E02A80;
extern unsigned int g_Va00E02AA0;
// g_Va00E02AA0: matched references place it at VA 0xe02aa0 (zero-filled .bss).
unsigned int g_Va00E02AA0;
extern unsigned int g_Va00E02AAC;
// g_Va00E02AAC: matched references place it at VA 0xe02aac (zero-filled .bss).
unsigned int g_Va00E02AAC;

unsigned int Rva00781D99ClearFlag(void)
{
	return g_Va00E029F0 &= 0xFFFFFFFEu;
}

unsigned int Rva00781DB0ClearFlag(void)
{
	return g_Va00E029FC &= 0xFFFFFFFEu;
}

unsigned int Rva00781DC7ClearFlag(void)
{
	return g_Va00E02A1C &= 0xFFFFFFFEu;
}

unsigned int Rva00781DDEClearFlag(void)
{
	return g_Va00E02A28 &= 0xFFFFFFFEu;
}

unsigned int Rva00781DF5ClearFlag(void)
{
	return g_Va00E02A48 &= 0xFFFFFFFEu;
}

unsigned int Rva00781E0CClearFlag(void)
{
	return g_Va00E02A54 &= 0xFFFFFFFEu;
}

unsigned int Rva00781E23ClearFlag(void)
{
	return g_Va00E02A74 &= 0xFFFFFFFEu;
}

unsigned int Rva00781E3AClearFlag(void)
{
	return g_Va00E02A80 &= 0xFFFFFFFEu;
}

unsigned int Rva00781E51ClearFlag(void)
{
	return g_Va00E02AA0 &= 0xFFFFFFFEu;
}

unsigned int Rva00781E68ClearFlag(void)
{
	return g_Va00E02AAC &= 0xFFFFFFFEu;
}
