// Twenty-five B2-native flag-word clearers on 23 .data flag words
// (0x00E03C00-0x00E03CF8):
//
//     mov eax,[<address>] / and al,<mask8> / mov [<address>],eax / ret
//
// Same /G7 byte-register narrowing as GlobalFlagClearers_08.cpp (defaults
// emit `and eax,imm`). Each body carries a .rdata table slot. Identity is
// not recovered; names derive from addresses.
// following GlobalFlagClearers_E03Bxx.cpp.
// cl: /G7 /MD /EHsc /DNDEBUG

extern unsigned int g_Va00E03C00;
// g_Va00E03C00: matched references place it at VA 0xe03c00 (zero-filled .bss).
unsigned int g_Va00E03C00;
extern unsigned int g_Va00E03C0C;
// g_Va00E03C0C: matched references place it at VA 0xe03c0c (zero-filled .bss).
unsigned int g_Va00E03C0C;
extern unsigned int g_Va00E03C14;
// g_Va00E03C14: matched references place it at VA 0xe03c14 (zero-filled .bss).
unsigned int g_Va00E03C14;
extern unsigned int g_Va00E03C20;
// g_Va00E03C20: matched references place it at VA 0xe03c20 (zero-filled .bss).
unsigned int g_Va00E03C20;
extern unsigned int g_Va00E03C28;
// g_Va00E03C28: matched references place it at VA 0xe03c28 (zero-filled .bss).
unsigned int g_Va00E03C28;
extern unsigned int g_Va00E03C34;
// g_Va00E03C34: matched references place it at VA 0xe03c34 (zero-filled .bss).
unsigned int g_Va00E03C34;
extern unsigned int g_Va00E03C3C;
// g_Va00E03C3C: matched references place it at VA 0xe03c3c (zero-filled .bss).
unsigned int g_Va00E03C3C;
extern unsigned int g_Va00E03C48;
// g_Va00E03C48: matched references place it at VA 0xe03c48 (zero-filled .bss).
unsigned int g_Va00E03C48;
extern unsigned int g_Va00E03C50;
// g_Va00E03C50: matched references place it at VA 0xe03c50 (zero-filled .bss).
unsigned int g_Va00E03C50;
extern unsigned int g_Va00E03C5C;
// g_Va00E03C5C: matched references place it at VA 0xe03c5c (zero-filled .bss).
unsigned int g_Va00E03C5C;
extern unsigned int g_Va00E03C68;
// g_Va00E03C68: matched references place it at VA 0xe03c68 (zero-filled .bss).
unsigned int g_Va00E03C68;
extern unsigned int g_Va00E03C74;
// g_Va00E03C74: matched references place it at VA 0xe03c74 (zero-filled .bss).
unsigned int g_Va00E03C74;
extern unsigned int g_Va00E03C80;
// g_Va00E03C80: matched references place it at VA 0xe03c80 (zero-filled .bss).
unsigned int g_Va00E03C80;
extern unsigned int g_Va00E03C88;
// g_Va00E03C88: matched references place it at VA 0xe03c88 (zero-filled .bss).
unsigned int g_Va00E03C88;
extern unsigned int g_Va00E03C94;
// g_Va00E03C94: matched references place it at VA 0xe03c94 (zero-filled .bss).
unsigned int g_Va00E03C94;
extern unsigned int g_Va00E03C9C;
// g_Va00E03C9C: matched references place it at VA 0xe03c9c (zero-filled .bss).
unsigned int g_Va00E03C9C;
extern unsigned int g_Va00E03CA4;
// g_Va00E03CA4: matched references place it at VA 0xe03ca4 (zero-filled .bss).
unsigned int g_Va00E03CA4;
extern unsigned int g_Va00E03CB8;
// g_Va00E03CB8: matched references place it at VA 0xe03cb8 (zero-filled .bss).
unsigned int g_Va00E03CB8;
extern unsigned int g_Va00E03CC0;
// g_Va00E03CC0: matched references place it at VA 0xe03cc0 (zero-filled .bss).
unsigned int g_Va00E03CC0;
extern unsigned int g_Va00E03CC8;
// g_Va00E03CC8: matched references place it at VA 0xe03cc8 (zero-filled .bss).
unsigned int g_Va00E03CC8;
extern unsigned int g_Va00E03CD0;
// g_Va00E03CD0: matched references place it at VA 0xe03cd0 (zero-filled .bss).
unsigned int g_Va00E03CD0;
extern unsigned int g_Va00E03CDC;
// g_Va00E03CDC: matched references place it at VA 0xe03cdc (zero-filled .bss).
unsigned int g_Va00E03CDC;
extern unsigned int g_Va00E03CF8;
// g_Va00E03CF8: matched references place it at VA 0xe03cf8 (zero-filled .bss).
unsigned int g_Va00E03CF8;

unsigned int Rva0078DD56ClearFlag(void)
{
	return g_Va00E03C00 &= 0xFFFFFFFEu;
}

unsigned int Rva0078DD6DClearFlag(void)
{
	return g_Va00E03C0C &= 0xFFFFFFFEu;
}

unsigned int Rva0078DD96ClearFlag(void)
{
	return g_Va00E03C14 &= 0xFFFFFFFEu;
}

unsigned int Rva0078DDADClearFlag(void)
{
	return g_Va00E03C20 &= 0xFFFFFFFEu;
}

unsigned int Rva0078DDD6ClearFlag(void)
{
	return g_Va00E03C28 &= 0xFFFFFFFEu;
}

unsigned int Rva0078DDEDClearFlag(void)
{
	return g_Va00E03C34 &= 0xFFFFFFFEu;
}

unsigned int Rva0078DE16ClearFlag(void)
{
	return g_Va00E03C3C &= 0xFFFFFFFEu;
}

unsigned int Rva0078DE3FClearFlag(void)
{
	return g_Va00E03C48 &= 0xFFFFFFFEu;
}

unsigned int Rva0078DE8CClearFlag(void)
{
	return g_Va00E03C50 &= 0xFFFFFFFEu;
}

unsigned int Rva0078DEB7ClearFlag(void)
{
	return g_Va00E03C5C &= 0xFFFFFFFEu;
}

unsigned int Rva0078DEC4ClearFlag(void)
{
	return g_Va00E03C5C &= 0xFFFFFFFDu;
}

unsigned int Rva0078DF45ClearFlag(void)
{
	return g_Va00E03C68 &= 0xFFFFFFFEu;
}

unsigned int Rva0078DFA0ClearFlag(void)
{
	return g_Va00E03C74 &= 0xFFFFFFFEu;
}

unsigned int Rva0078DFB7ClearFlag(void)
{
	return g_Va00E03C80 &= 0xFFFFFFFEu;
}

unsigned int Rva0078E00FClearFlag(void)
{
	return g_Va00E03C88 &= 0xFFFFFFFEu;
}

unsigned int Rva0078E038ClearFlag(void)
{
	return g_Va00E03C94 &= 0xFFFFFFFEu;
}

unsigned int Rva0078E096ClearFlag(void)
{
	return g_Va00E03C9C &= 0xFFFFFFFEu;
}

unsigned int Rva0078E0C1ClearFlag(void)
{
	return g_Va00E03CA4 &= 0xFFFFFFFEu;
}

unsigned int Rva0078E11EClearFlag(void)
{
	return g_Va00E03CB8 &= 0xFFFFFFFEu;
}

unsigned int Rva0078E12BClearFlag(void)
{
	return g_Va00E03CB8 &= 0xFFFFFFFDu;
}

unsigned int Rva0078E142ClearFlag(void)
{
	return g_Va00E03CC0 &= 0xFFFFFFFEu;
}

unsigned int Rva0078E1FBClearFlag(void)
{
	return g_Va00E03CC8 &= 0xFFFFFFFEu;
}

unsigned int Rva0078E212ClearFlag(void)
{
	return g_Va00E03CD0 &= 0xFFFFFFFEu;
}

unsigned int Rva0078E29DClearFlag(void)
{
	return g_Va00E03CDC &= 0xFFFFFFFEu;
}

unsigned int Rva0078E30EClearFlag(void)
{
	return g_Va00E03CF8 &= 0xFFFFFFFEu;
}

