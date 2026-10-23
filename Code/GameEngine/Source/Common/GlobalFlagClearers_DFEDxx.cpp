// Sixteen B2-native flag-word clearers across fifteen .data flag words
// of one contiguous run (0x0077433C-0x00774780):
//
//     mov eax,[<address>] / and al,<mask8> / mov [<address>],eax / ret
//
// Twelve clear al bit 0, one clears al bit 1. Same /G7 byte-register
// narrowing as GlobalFlagClearers_08.cpp (defaults emit `and eax,imm`).
// Each body carries a .rdata table slot (0x0091B52C and on). Identity is
// not recovered; names derive from addresses, following
// GlobalFlagClearers_08.cpp.
// cl: /G7 /MD /EHsc /DNDEBUG

extern unsigned int g_Va00DFED00;
// g_Va00DFED00: matched references place it at VA 0xdfed00 (zero-filled .bss).
unsigned int g_Va00DFED00;
extern unsigned int g_Va00DFED08;
// g_Va00DFED08: matched references place it at VA 0xdfed08 (zero-filled .bss).
unsigned int g_Va00DFED08;
extern unsigned int g_Va00DFED10;
// g_Va00DFED10: matched references place it at VA 0xdfed10 (zero-filled .bss).
unsigned int g_Va00DFED10;
extern unsigned int g_Va00DFED18;
// g_Va00DFED18: matched references place it at VA 0xdfed18 (zero-filled .bss).
unsigned int g_Va00DFED18;
extern unsigned int g_Va00DFED20;
// g_Va00DFED20: matched references place it at VA 0xdfed20 (zero-filled .bss).
unsigned int g_Va00DFED20;
extern unsigned int g_Va00DFED28;
// g_Va00DFED28: matched references place it at VA 0xdfed28 (zero-filled .bss).
unsigned int g_Va00DFED28;
extern unsigned int g_Va00DFED30;
// g_Va00DFED30: matched references place it at VA 0xdfed30 (zero-filled .bss).
unsigned int g_Va00DFED30;
extern unsigned int g_Va00DFED38;
// g_Va00DFED38: matched references place it at VA 0xdfed38 (zero-filled .bss).
unsigned int g_Va00DFED38;
extern unsigned int g_Va00DFED40;
// g_Va00DFED40: matched references place it at VA 0xdfed40 (zero-filled .bss).
unsigned int g_Va00DFED40;
extern unsigned int g_Va00DFED48;
// g_Va00DFED48: matched references place it at VA 0xdfed48 (zero-filled .bss).
unsigned int g_Va00DFED48;
extern unsigned int g_Va00DFED54;
// g_Va00DFED54: matched references place it at VA 0xdfed54 (zero-filled .bss).
unsigned int g_Va00DFED54;
extern unsigned int g_Va00DFED5C;
// g_Va00DFED5C: matched references place it at VA 0xdfed5c (zero-filled .bss).
unsigned int g_Va00DFED5C;
extern unsigned int g_Va00DFED6C;
// g_Va00DFED6C: matched references place it at VA 0xdfed6c (zero-filled .bss).
unsigned int g_Va00DFED6C;
extern unsigned int g_Va00DFED74;
// g_Va00DFED74: matched references place it at VA 0xdfed74 (zero-filled .bss).
unsigned int g_Va00DFED74;
extern unsigned int g_Va00DFED7C;
// g_Va00DFED7C: matched references place it at VA 0xdfed7c (zero-filled .bss).
unsigned int g_Va00DFED7C;

unsigned int Rva00774353ClearFlag(void)
{
	return g_Va00DFED08 &= 0xFFFFFFFEu;
}

unsigned int Rva0077436AClearFlag(void)
{
	return g_Va00DFED10 &= 0xFFFFFFFEu;
}

unsigned int Rva00774381ClearFlag(void)
{
	return g_Va00DFED18 &= 0xFFFFFFFEu;
}

unsigned int Rva00774398ClearFlag(void)
{
	return g_Va00DFED20 &= 0xFFFFFFFEu;
}

unsigned int Rva007743AFClearFlag(void)
{
	return g_Va00DFED28 &= 0xFFFFFFFEu;
}

unsigned int Rva007743C6ClearFlag(void)
{
	return g_Va00DFED30 &= 0xFFFFFFFEu;
}

unsigned int Rva007743DDClearFlag(void)
{
	return g_Va00DFED38 &= 0xFFFFFFFEu;
}

unsigned int Rva00774461ClearFlag(void)
{
	return g_Va00DFED48 &= 0xFFFFFFFEu;
}

unsigned int Rva00774522ClearFlag(void)
{
	return g_Va00DFED54 &= 0xFFFFFFFEu;
}

unsigned int Rva00774539ClearFlag(void)
{
	return g_Va00DFED5C &= 0xFFFFFFFEu;
}

unsigned int Rva007746B0ClearFlag(void)
{
	return g_Va00DFED6C &= 0xFFFFFFFDu;
}

unsigned int Rva007746C7ClearFlag(void)
{
	return g_Va00DFED74 &= 0xFFFFFFFEu;
}

unsigned int Rva00774780ClearFlag(void)
{
	return g_Va00DFED7C &= 0xFFFFFFFEu;
}

unsigned int Rva0077433CClearFlag(void)
{
	return g_Va00DFED00 &= 0xFFFFFFFEu;
}

unsigned int Rva0077444AClearFlag(void)
{
	return g_Va00DFED40 &= 0xFFFFFFFEu;
}

unsigned int Rva007746A3ClearFlag(void)
{
	return g_Va00DFED6C &= 0xFFFFFFFEu;
}
