// Six B2-native flag-word clearers on five scattered .data flag words
// (0x007785C9-0x0077979D):
//
//     mov eax,[<address>] / and al,<mask8> / mov [<address>],eax / ret
//
// Same /G7 byte-register narrowing as GlobalFlagClearers_08.cpp (defaults
// emit `and eax,imm`). Each body carries a .rdata table slot (0x00920670
// and on). Identity is not recovered; names derive from addresses,
// following GlobalFlagClearers_08.cpp.
// cl: /G7 /MD /EHsc /DNDEBUG

extern unsigned int g_Va00DFF0A8;
// g_Va00DFF0A8: matched references place it at VA 0xdff0a8 (zero-filled .bss).
unsigned int g_Va00DFF0A8;
extern unsigned int g_Va00DFF0E4;
// g_Va00DFF0E4: matched references place it at VA 0xdff0e4 (zero-filled .bss).
unsigned int g_Va00DFF0E4;
extern unsigned int g_Va00DFF108;
// g_Va00DFF108: matched references place it at VA 0xdff108 (zero-filled .bss).
unsigned int g_Va00DFF108;
extern unsigned int g_Va00DFF160;
// g_Va00DFF160: matched references place it at VA 0xdff160 (zero-filled .bss).
unsigned int g_Va00DFF160;
extern unsigned int g_Va00DFF17C;
// g_Va00DFF17C: matched references place it at VA 0xdff17c (zero-filled .bss).
unsigned int g_Va00DFF17C;

unsigned int Rva007785C9ClearFlag(void)
{
	return g_Va00DFF0A8 &= 0xFFFFFFFEu;
}

unsigned int Rva007785D6ClearFlag(void)
{
	return g_Va00DFF0A8 &= 0xFFFFFFFDu;
}

unsigned int Rva00778EA4ClearFlag(void)
{
	return g_Va00DFF0E4 &= 0xFFFFFFFEu;
}

unsigned int Rva007792F6ClearFlag(void)
{
	return g_Va00DFF108 &= 0xFFFFFFFEu;
}

unsigned int Rva0077942DClearFlag(void)
{
	return g_Va00DFF160 &= 0xFFFFFFFEu;
}

unsigned int Rva0077979DClearFlag(void)
{
	return g_Va00DFF17C &= 0xFFFFFFFEu;
}
