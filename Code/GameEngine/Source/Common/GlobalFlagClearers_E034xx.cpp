// Twenty-three B2-native flag-word clearers on twenty-one .data flag words
// (0x00E03400-0x00E034E4):
//
//     mov eax,[<address>] / and al,<mask8> / mov [<address>],eax / ret
//
// Same /G7 byte-register narrowing as GlobalFlagClearers_08.cpp (defaults
// emit `and eax,imm`). Each body carries a .rdata table slot. Identity is
// not recovered; names derive from addresses,
// following GlobalFlagClearers_E033xx.cpp.
// cl: /G7 /MD /EHsc /DNDEBUG

extern unsigned int g_Va00E03400;
// g_Va00E03400: matched references place it at VA 0xe03400 (zero-filled .bss).
unsigned int g_Va00E03400;
extern unsigned int g_Va00E0340C;
// g_Va00E0340C: matched references place it at VA 0xe0340c (zero-filled .bss).
unsigned int g_Va00E0340C;
extern unsigned int g_Va00E03418;
// g_Va00E03418: matched references place it at VA 0xe03418 (zero-filled .bss).
unsigned int g_Va00E03418;
extern unsigned int g_Va00E03424;
// g_Va00E03424: matched references place it at VA 0xe03424 (zero-filled .bss).
unsigned int g_Va00E03424;
extern unsigned int g_Va00E03430;
// g_Va00E03430: matched references place it at VA 0xe03430 (zero-filled .bss).
unsigned int g_Va00E03430;
extern unsigned int g_Va00E0343C;
// g_Va00E0343C: matched references place it at VA 0xe0343c (zero-filled .bss).
unsigned int g_Va00E0343C;
extern unsigned int g_Va00E03444;
// g_Va00E03444: matched references place it at VA 0xe03444 (zero-filled .bss).
unsigned int g_Va00E03444;
extern unsigned int g_Va00E0344C;
// g_Va00E0344C: matched references place it at VA 0xe0344c (zero-filled .bss).
unsigned int g_Va00E0344C;
extern unsigned int g_Va00E03458;
// g_Va00E03458: matched references place it at VA 0xe03458 (zero-filled .bss).
unsigned int g_Va00E03458;
extern unsigned int g_Va00E03460;
// g_Va00E03460: matched references place it at VA 0xe03460 (zero-filled .bss).
unsigned int g_Va00E03460;
extern unsigned int g_Va00E0346C;
// g_Va00E0346C: matched references place it at VA 0xe0346c (zero-filled .bss).
unsigned int g_Va00E0346C;
extern unsigned int g_Va00E03478;
// g_Va00E03478: matched references place it at VA 0xe03478 (zero-filled .bss).
unsigned int g_Va00E03478;
extern unsigned int g_Va00E03480;
// g_Va00E03480: matched references place it at VA 0xe03480 (zero-filled .bss).
unsigned int g_Va00E03480;
extern unsigned int g_Va00E0348C;
// g_Va00E0348C: matched references place it at VA 0xe0348c (zero-filled .bss).
unsigned int g_Va00E0348C;
extern unsigned int g_Va00E03494;
// g_Va00E03494: matched references place it at VA 0xe03494 (zero-filled .bss).
unsigned int g_Va00E03494;
extern unsigned int g_Va00E034B0;
// g_Va00E034B0: matched references place it at VA 0xe034b0 (zero-filled .bss).
unsigned int g_Va00E034B0;
extern unsigned int g_Va00E034B8;
// g_Va00E034B8: matched references place it at VA 0xe034b8 (zero-filled .bss).
unsigned int g_Va00E034B8;
extern unsigned int g_Va00E034C4;
// g_Va00E034C4: matched references place it at VA 0xe034c4 (zero-filled .bss).
unsigned int g_Va00E034C4;
extern unsigned int g_Va00E034D0;
// g_Va00E034D0: matched references place it at VA 0xe034d0 (zero-filled .bss).
unsigned int g_Va00E034D0;
extern unsigned int g_Va00E034DC;
// g_Va00E034DC: matched references place it at VA 0xe034dc (zero-filled .bss).
unsigned int g_Va00E034DC;
extern unsigned int g_Va00E034E4;
// g_Va00E034E4: matched references place it at VA 0xe034e4 (zero-filled .bss).
unsigned int g_Va00E034E4;

unsigned int Rva00789EBDClearFlag(void)
{
	return g_Va00E03400 &= 0xFFFFFFFEu;
}

unsigned int Rva00789F03ClearFlag(void)
{
	return g_Va00E0340C &= 0xFFFFFFFEu;
}

unsigned int Rva00789F18ClearFlag(void)
{
	return g_Va00E0340C &= 0xFFFFFFFDu;
}

unsigned int Rva00789F3FClearFlag(void)
{
	return g_Va00E03418 &= 0xFFFFFFFEu;
}

unsigned int Rva00789F4CClearFlag(void)
{
	return g_Va00E03418 &= 0xFFFFFFFDu;
}

unsigned int Rva00789FB0ClearFlag(void)
{
	return g_Va00E03424 &= 0xFFFFFFFEu;
}

unsigned int Rva0078A0DFClearFlag(void)
{
	return g_Va00E03430 &= 0xFFFFFFFEu;
}

unsigned int Rva0078A1A6ClearFlag(void)
{
	return g_Va00E0343C &= 0xFFFFFFFEu;
}

unsigned int Rva0078A1BDClearFlag(void)
{
	return g_Va00E03444 &= 0xFFFFFFFEu;
}

unsigned int Rva0078A1D4ClearFlag(void)
{
	return g_Va00E0344C &= 0xFFFFFFFEu;
}

unsigned int Rva0078A23EClearFlag(void)
{
	return g_Va00E03458 &= 0xFFFFFFFEu;
}

unsigned int Rva0078A255ClearFlag(void)
{
	return g_Va00E03460 &= 0xFFFFFFFEu;
}

unsigned int Rva0078A27EClearFlag(void)
{
	return g_Va00E0346C &= 0xFFFFFFFEu;
}

unsigned int Rva0078A2C4ClearFlag(void)
{
	return g_Va00E03478 &= 0xFFFFFFFEu;
}

unsigned int Rva0078A2DBClearFlag(void)
{
	return g_Va00E03480 &= 0xFFFFFFFEu;
}

unsigned int Rva0078A34CClearFlag(void)
{
	return g_Va00E0348C &= 0xFFFFFFFEu;
}

unsigned int Rva0078A380ClearFlag(void)
{
	return g_Va00E03494 &= 0xFFFFFFFEu;
}

unsigned int Rva0078A411ClearFlag(void)
{
	return g_Va00E034B0 &= 0xFFFFFFFEu;
}

unsigned int Rva0078A43AClearFlag(void)
{
	return g_Va00E034B8 &= 0xFFFFFFFEu;
}

unsigned int Rva0078A49AClearFlag(void)
{
	return g_Va00E034C4 &= 0xFFFFFFFEu;
}

unsigned int Rva0078A53FClearFlag(void)
{
	return g_Va00E034D0 &= 0xFFFFFFFEu;
}

unsigned int Rva0078A5DCClearFlag(void)
{
	return g_Va00E034DC &= 0xFFFFFFFEu;
}

unsigned int Rva0078A622ClearFlag(void)
{
	return g_Va00E034E4 &= 0xFFFFFFFEu;
}
