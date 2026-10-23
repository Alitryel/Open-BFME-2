// Seven B2-native flag-word clearers on seven .data flag words
// (0x00DFEC4C-0x00DFECF8):
//
//     mov eax,[<address>] / and al,<mask8> / mov [<address>],eax / ret
//
// Same /G7 byte-register narrowing as GlobalFlagClearers_08.cpp (defaults
// emit `and eax,imm`). Each body carries a .rdata table slot. Identity is
// not recovered; names derive from addresses,
// following GlobalFlagClearers_DFEExx.cpp.
// cl: /G7 /MD /EHsc /DNDEBUG

extern unsigned int g_Va00DFEC4C;
// g_Va00DFEC4C: matched references place it at VA 0xdfec4c (zero-filled .bss).
unsigned int g_Va00DFEC4C;
extern unsigned int g_Va00DFEC60;
// g_Va00DFEC60: matched references place it at VA 0xdfec60 (zero-filled .bss).
unsigned int g_Va00DFEC60;
extern unsigned int g_Va00DFEC80;
// g_Va00DFEC80: matched references place it at VA 0xdfec80 (zero-filled .bss).
unsigned int g_Va00DFEC80;
extern unsigned int g_Va00DFECE0;
// g_Va00DFECE0: matched references place it at VA 0xdfece0 (zero-filled .bss).
unsigned int g_Va00DFECE0;
extern unsigned int g_Va00DFECE8;
// g_Va00DFECE8: matched references place it at VA 0xdfece8 (zero-filled .bss).
unsigned int g_Va00DFECE8;
extern unsigned int g_Va00DFECF0;
// g_Va00DFECF0: matched references place it at VA 0xdfecf0 (zero-filled .bss).
unsigned int g_Va00DFECF0;
extern unsigned int g_Va00DFECF8;
// g_Va00DFECF8: matched references place it at VA 0xdfecf8 (zero-filled .bss).
unsigned int g_Va00DFECF8;

unsigned int Rva007735C6ClearFlag(void)
{
	return g_Va00DFEC4C &= 0xFFFFFFFEu;
}

unsigned int Rva0077388BClearFlag(void)
{
	return g_Va00DFEC60 &= 0xFFFFFFFEu;
}

unsigned int Rva00773EB8ClearFlag(void)
{
	return g_Va00DFEC80 &= 0xFFFFFFFEu;
}

unsigned int Rva007742BCClearFlag(void)
{
	return g_Va00DFECE0 &= 0xFFFFFFFEu;
}

unsigned int Rva007742D3ClearFlag(void)
{
	return g_Va00DFECE8 &= 0xFFFFFFFEu;
}

unsigned int Rva007742EAClearFlag(void)
{
	return g_Va00DFECF0 &= 0xFFFFFFFEu;
}

unsigned int Rva00774313ClearFlag(void)
{
	return g_Va00DFECF8 &= 0xFFFFFFFEu;
}
