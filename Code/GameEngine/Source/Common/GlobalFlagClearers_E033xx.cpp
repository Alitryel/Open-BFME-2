// Twenty-one B2-native flag-word clearers on fourteen .data flag words
// (0x00E03304-0x00E033F0):
//
//     mov eax,[<address>] / and al,<mask8> / mov [<address>],eax / ret
//
// Same /G7 byte-register narrowing as GlobalFlagClearers_08.cpp (defaults
// emit `and eax,imm`). Each body carries a .rdata table slot. Identity is
// not recovered; names derive from addresses,
// following GlobalFlagClearers_E031xx.cpp.
// cl: /G7 /MD /EHsc /DNDEBUG

extern unsigned int g_Va00E03304;
// g_Va00E03304: matched references place it at VA 0xe03304 (zero-filled .bss).
unsigned int g_Va00E03304;
extern unsigned int g_Va00E03334;
// g_Va00E03334: matched references place it at VA 0xe03334 (zero-filled .bss).
unsigned int g_Va00E03334;
extern unsigned int g_Va00E03350;
// g_Va00E03350: matched references place it at VA 0xe03350 (zero-filled .bss).
unsigned int g_Va00E03350;
extern unsigned int g_Va00E0337C;
// g_Va00E0337C: matched references place it at VA 0xe0337c (zero-filled .bss).
unsigned int g_Va00E0337C;
extern unsigned int g_Va00E03384;
// g_Va00E03384: matched references place it at VA 0xe03384 (zero-filled .bss).
unsigned int g_Va00E03384;
extern unsigned int g_Va00E03390;
// g_Va00E03390: matched references place it at VA 0xe03390 (zero-filled .bss).
unsigned int g_Va00E03390;
extern unsigned int g_Va00E03398;
// g_Va00E03398: matched references place it at VA 0xe03398 (zero-filled .bss).
unsigned int g_Va00E03398;
extern unsigned int g_Va00E033A0;
// g_Va00E033A0: matched references place it at VA 0xe033a0 (zero-filled .bss).
unsigned int g_Va00E033A0;
extern unsigned int g_Va00E033A8;
// g_Va00E033A8: matched references place it at VA 0xe033a8 (zero-filled .bss).
unsigned int g_Va00E033A8;
extern unsigned int g_Va00E033B4;
// g_Va00E033B4: matched references place it at VA 0xe033b4 (zero-filled .bss).
unsigned int g_Va00E033B4;
extern unsigned int g_Va00E033D8;
// g_Va00E033D8: matched references place it at VA 0xe033d8 (zero-filled .bss).
unsigned int g_Va00E033D8;
extern unsigned int g_Va00E033E4;
// g_Va00E033E4: matched references place it at VA 0xe033e4 (zero-filled .bss).
unsigned int g_Va00E033E4;
extern unsigned int g_Va00E033F0;
// g_Va00E033F0: matched references place it at VA 0xe033f0 (zero-filled .bss).
unsigned int g_Va00E033F0;

unsigned int Rva00788149ClearFlag(void)
{
	return g_Va00E03304 &= 0xFFFFFFFEu;
}

unsigned int Rva007886AFClearFlag(void)
{
	return g_Va00E03334 &= 0xFFFFFFFEu;
}

unsigned int Rva007886C4ClearFlag(void)
{
	return g_Va00E03334 &= 0xFFFFFFFDu;
}

unsigned int Rva007886D1ClearFlag(void)
{
	return g_Va00E03334 &= 0xFFFFFFFBu;
}

unsigned int Rva007886EEClearFlag(void)
{
	return g_Va00E03334 &= 0xFFFFFFF7u;
}

unsigned int Rva00788A22ClearFlag(void)
{
	return g_Va00E03350 &= 0xFFFFFFFEu;
}

unsigned int Rva00788A37ClearFlag(void)
{
	return g_Va00E03350 &= 0xFFFFFFFDu;
}

unsigned int Rva00789673ClearFlag(void)
{
	return g_Va00E0337C &= 0xFFFFFFFEu;
}

unsigned int Rva00789688ClearFlag(void)
{
	return g_Va00E0337C &= 0xFFFFFFFDu;
}

unsigned int Rva0078969DClearFlag(void)
{
	return g_Va00E0337C &= 0xFFFFFFFBu;
}

unsigned int Rva007896B2ClearFlag(void)
{
	return g_Va00E0337C &= 0xFFFFFFF7u;
}

unsigned int Rva007899F7ClearFlag(void)
{
	return g_Va00E03384 &= 0xFFFFFFFEu;
}

unsigned int Rva00789AC7ClearFlag(void)
{
	return g_Va00E03390 &= 0xFFFFFFFEu;
}

unsigned int Rva00789AF0ClearFlag(void)
{
	return g_Va00E03398 &= 0xFFFFFFFEu;
}

unsigned int Rva00789B39ClearFlag(void)
{
	return g_Va00E033A0 &= 0xFFFFFFFEu;
}

unsigned int Rva00789B6DClearFlag(void)
{
	return g_Va00E033A8 &= 0xFFFFFFFEu;
}

unsigned int Rva00789BC2ClearFlag(void)
{
	return g_Va00E033B4 &= 0xFFFFFFFEu;
}

unsigned int Rva00789BDAClearFlag(void)
{
	return g_Va00E033B4 &= 0xFFFFFFFDu;
}

unsigned int Rva00789C2BClearFlag(void)
{
	return g_Va00E033D8 &= 0xFFFFFFFEu;
}

unsigned int Rva00789C8EClearFlag(void)
{
	return g_Va00E033E4 &= 0xFFFFFFFEu;
}

unsigned int Rva00789E36ClearFlag(void)
{
	return g_Va00E033F0 &= 0xFFFFFFFEu;
}
