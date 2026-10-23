// Eighteen B2-native flag-word clearers on 17 .data flag words
// (0x00E01DE0-0x00E048F8):
//
//     mov eax,[<address>] / and a<l,h>,<mask8> / mov [<address>],eax / ret
//
// Same /G7 byte-register narrowing as GlobalFlagClearers_08.cpp (defaults
// emit `and eax,imm`). Each body carries a .rdata table slot. Identity is
// not recovered; names derive from addresses,
// following GlobalFlagClearers_DFxx.cpp.
// cl: /G7 /MD /EHsc /DNDEBUG

extern unsigned int g_Va00E01DE0;
// g_Va00E01DE0: matched references place it at VA 0xe01de0 (zero-filled .bss).
unsigned int g_Va00E01DE0;
extern unsigned int g_Va00E01E30;
// g_Va00E01E30: matched references place it at VA 0xe01e30 (zero-filled .bss).
unsigned int g_Va00E01E30;
extern unsigned int g_Va00E01E8C;
// g_Va00E01E8C: matched references place it at VA 0xe01e8c (zero-filled .bss).
unsigned int g_Va00E01E8C;
extern unsigned int g_Va00E01EB0;
// g_Va00E01EB0: matched references place it at VA 0xe01eb0 (zero-filled .bss).
unsigned int g_Va00E01EB0;
extern unsigned int g_Va00E01EB8;
// g_Va00E01EB8: matched references place it at VA 0xe01eb8 (zero-filled .bss).
unsigned int g_Va00E01EB8;
extern unsigned int g_Va00E01EE8;
// g_Va00E01EE8: matched references place it at VA 0xe01ee8 (zero-filled .bss).
unsigned int g_Va00E01EE8;
extern unsigned int g_Va00E01EF0;
// g_Va00E01EF0: matched references place it at VA 0xe01ef0 (zero-filled .bss).
unsigned int g_Va00E01EF0;
extern unsigned int g_Va00E01EF8;
// g_Va00E01EF8: matched references place it at VA 0xe01ef8 (zero-filled .bss).
unsigned int g_Va00E01EF8;
extern unsigned int g_Va00E021E0;
// g_Va00E021E0: matched references place it at VA 0xe021e0 (zero-filled .bss).
unsigned int g_Va00E021E0;
extern unsigned int g_Va00E02808;
// g_Va00E02808: matched references place it at VA 0xe02808 (zero-filled .bss).
unsigned int g_Va00E02808;
extern unsigned int g_Va00E02810;
// g_Va00E02810: matched references place it at VA 0xe02810 (zero-filled .bss).
unsigned int g_Va00E02810;
extern unsigned int g_Va00E02818;
// g_Va00E02818: matched references place it at VA 0xe02818 (zero-filled .bss).
unsigned int g_Va00E02818;
extern unsigned int g_Va00E02820;
// g_Va00E02820: matched references place it at VA 0xe02820 (zero-filled .bss).
unsigned int g_Va00E02820;
extern unsigned int g_Va00E02F24;
extern unsigned int g_Va00E032C0;
// g_Va00E032C0: matched references place it at VA 0xe032c0 (zero-filled .bss).
unsigned int g_Va00E032C0;
extern unsigned int g_Va00E04608;
// g_Va00E04608: matched references place it at VA 0xe04608 (zero-filled .bss).
unsigned int g_Va00E04608;
extern unsigned int g_Va00E048F8;
// g_Va00E048F8: matched references place it at VA 0xe048f8 (zero-filled .bss).
unsigned int g_Va00E048F8;

unsigned int Rva0077CB98ClearFlag(void)
{
	return g_Va00E01DE0 &= 0xFFFFFFFEu;
}

unsigned int Rva0077D98AClearFlag(void)
{
	return g_Va00E01E30 &= 0xFFFFFFFEu;
}

unsigned int Rva0077E24EClearFlag(void)
{
	return g_Va00E01E8C &= 0xFFFFFFFEu;
}

unsigned int Rva0077E48CClearFlag(void)
{
	return g_Va00E01EB0 &= 0xFFFFFFFEu;
}

unsigned int Rva0077E57FClearFlag(void)
{
	return g_Va00E01EB8 &= 0xFFFFFFFEu;
}

unsigned int Rva0077E778ClearFlag(void)
{
	return g_Va00E01EE8 &= 0xFFFFFFFEu;
}

unsigned int Rva0077E7D5ClearFlag(void)
{
	return g_Va00E01EF0 &= 0xFFFFFFFEu;
}

unsigned int Rva0077E87EClearFlag(void)
{
	return g_Va00E01EF8 &= 0xFFFFFFFEu;
}

unsigned int Rva0077EBADClearFlag(void)
{
	return g_Va00E021E0 &= 0xFFFFFFFEu;
}

unsigned int Rva00780EDCClearFlag(void)
{
	return g_Va00E02808 &= 0xFFFFFFFEu;
}

unsigned int Rva00780EE9ClearFlag(void)
{
	return g_Va00E02808 &= 0xFFFFFFFDu;
}

unsigned int Rva00780F00ClearFlag(void)
{
	return g_Va00E02810 &= 0xFFFFFFFEu;
}

unsigned int Rva00780F8DClearFlag(void)
{
	return g_Va00E02818 &= 0xFFFFFFFEu;
}

unsigned int Rva00780FA4ClearFlag(void)
{
	return g_Va00E02820 &= 0xFFFFFFFEu;
}

unsigned int Rva00784B78ClearFlag(void)
{
	return g_Va00E02F24 &= 0xFFFFFEFFu;
}

unsigned int Rva00787AA4ClearFlag(void)
{
	return g_Va00E032C0 &= 0xFFFFFFFEu;
}

unsigned int Rva0079477AClearFlag(void)
{
	return g_Va00E04608 &= 0xFFFFFFFEu;
}

unsigned int Rva00795288ClearFlag(void)
{
	return g_Va00E048F8 &= 0xFFFFFFFEu;
}

