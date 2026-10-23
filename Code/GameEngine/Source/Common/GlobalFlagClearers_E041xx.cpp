// Seventeen B2-native flag-word clearers on seventeen .data flag words
// (0x00E0414C-0x00E041D8):
//
//     mov eax,[<address>] / and al,<mask8> / mov [<address>],eax / ret
//
// Same /G7 byte-register narrowing as GlobalFlagClearers_E040xx.cpp (defaults
// emit `and eax,imm`). Each body carries a .rdata table slot. Identity is
// not recovered; names derive from addresses,
// following GlobalFlagClearers_E040xx.cpp.
// cl: /G7 /MD /EHsc /DNDEBUG

extern unsigned int g_Va00E0414C;
// g_Va00E0414C: matched references place it at VA 0xe0414c (zero-filled .bss).
unsigned int g_Va00E0414C;
extern unsigned int g_Va00E04154;
// g_Va00E04154: matched references place it at VA 0xe04154 (zero-filled .bss).
unsigned int g_Va00E04154;
extern unsigned int g_Va00E0415C;
// g_Va00E0415C: matched references place it at VA 0xe0415c (zero-filled .bss).
unsigned int g_Va00E0415C;
extern unsigned int g_Va00E04164;
// g_Va00E04164: matched references place it at VA 0xe04164 (zero-filled .bss).
unsigned int g_Va00E04164;
extern unsigned int g_Va00E0416C;
// g_Va00E0416C: matched references place it at VA 0xe0416c (zero-filled .bss).
unsigned int g_Va00E0416C;
extern unsigned int g_Va00E04174;
// g_Va00E04174: matched references place it at VA 0xe04174 (zero-filled .bss).
unsigned int g_Va00E04174;
extern unsigned int g_Va00E04180;
// g_Va00E04180: matched references place it at VA 0xe04180 (zero-filled .bss).
unsigned int g_Va00E04180;
extern unsigned int g_Va00E04188;
// g_Va00E04188: matched references place it at VA 0xe04188 (zero-filled .bss).
unsigned int g_Va00E04188;
extern unsigned int g_Va00E04190;
// g_Va00E04190: matched references place it at VA 0xe04190 (zero-filled .bss).
unsigned int g_Va00E04190;
extern unsigned int g_Va00E0419C;
// g_Va00E0419C: matched references place it at VA 0xe0419c (zero-filled .bss).
unsigned int g_Va00E0419C;
extern unsigned int g_Va00E041A4;
// g_Va00E041A4: matched references place it at VA 0xe041a4 (zero-filled .bss).
unsigned int g_Va00E041A4;
extern unsigned int g_Va00E041AC;
// g_Va00E041AC: matched references place it at VA 0xe041ac (zero-filled .bss).
unsigned int g_Va00E041AC;
extern unsigned int g_Va00E041B4;
// g_Va00E041B4: matched references place it at VA 0xe041b4 (zero-filled .bss).
unsigned int g_Va00E041B4;
extern unsigned int g_Va00E041BC;
// g_Va00E041BC: matched references place it at VA 0xe041bc (zero-filled .bss).
unsigned int g_Va00E041BC;
extern unsigned int g_Va00E041C4;
// g_Va00E041C4: matched references place it at VA 0xe041c4 (zero-filled .bss).
unsigned int g_Va00E041C4;
extern unsigned int g_Va00E041CC;
// g_Va00E041CC: matched references place it at VA 0xe041cc (zero-filled .bss).
unsigned int g_Va00E041CC;
extern unsigned int g_Va00E041D8;
// g_Va00E041D8: matched references place it at VA 0xe041d8 (zero-filled .bss).
unsigned int g_Va00E041D8;

unsigned int Rva0078FBE5ClearFlag(void)
{
	return g_Va00E0414C &= 0xFFFFFFFEu;
}

unsigned int Rva0078FBFCClearFlag(void)
{
	return g_Va00E04154 &= 0xFFFFFFFEu;
}

unsigned int Rva0078FC42ClearFlag(void)
{
	return g_Va00E0415C &= 0xFFFFFFFEu;
}

unsigned int Rva0078FC59ClearFlag(void)
{
	return g_Va00E04164 &= 0xFFFFFFFEu;
}

unsigned int Rva0078FC70ClearFlag(void)
{
	return g_Va00E0416C &= 0xFFFFFFFEu;
}

unsigned int Rva0078FC99ClearFlag(void)
{
	return g_Va00E04174 &= 0xFFFFFFFEu;
}

unsigned int Rva0078FCB0ClearFlag(void)
{
	return g_Va00E04180 &= 0xFFFFFFFEu;
}

unsigned int Rva0078FCC7ClearFlag(void)
{
	return g_Va00E04188 &= 0xFFFFFFFEu;
}

unsigned int Rva0078FCDEClearFlag(void)
{
	return g_Va00E04190 &= 0xFFFFFFFEu;
}

unsigned int Rva0078FCF5ClearFlag(void)
{
	return g_Va00E0419C &= 0xFFFFFFFEu;
}

unsigned int Rva0078FD70ClearFlag(void)
{
	return g_Va00E041A4 &= 0xFFFFFFFEu;
}

unsigned int Rva0078FDABClearFlag(void)
{
	return g_Va00E041AC &= 0xFFFFFFFEu;
}

unsigned int Rva0078FDC2ClearFlag(void)
{
	return g_Va00E041B4 &= 0xFFFFFFFEu;
}

unsigned int Rva0078FE2DClearFlag(void)
{
	return g_Va00E041BC &= 0xFFFFFFFEu;
}

unsigned int Rva0078FE76ClearFlag(void)
{
	return g_Va00E041C4 &= 0xFFFFFFFEu;
}

unsigned int Rva0078FF3DClearFlag(void)
{
	return g_Va00E041CC &= 0xFFFFFFFEu;
}

unsigned int Rva0078FFBFClearFlag(void)
{
	return g_Va00E041D8 &= 0xFFFFFFFEu;
}
