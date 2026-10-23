// Twenty-six B2-native flag-word clearers on 26 .data flag words
// (0x00E03804-0x00E038FC):
//
//     mov eax,[<address>] / and al,<mask8> / mov [<address>],eax / ret
//
// Same /G7 byte-register narrowing as GlobalFlagClearers_08.cpp (defaults
// emit `and eax,imm`). Each body carries a .rdata table slot. Identity is
// not recovered; names derive from addresses.
// following GlobalFlagClearers_E037xx.cpp.
// cl: /G7 /MD /EHsc /DNDEBUG

extern unsigned int g_Va00E03804;
// g_Va00E03804: matched references place it at VA 0xe03804 (zero-filled .bss).
unsigned int g_Va00E03804;
extern unsigned int g_Va00E0380C;
// g_Va00E0380C: matched references place it at VA 0xe0380c (zero-filled .bss).
unsigned int g_Va00E0380C;
extern unsigned int g_Va00E03814;
// g_Va00E03814: matched references place it at VA 0xe03814 (zero-filled .bss).
unsigned int g_Va00E03814;
extern unsigned int g_Va00E0381C;
// g_Va00E0381C: matched references place it at VA 0xe0381c (zero-filled .bss).
unsigned int g_Va00E0381C;
extern unsigned int g_Va00E03828;
// g_Va00E03828: matched references place it at VA 0xe03828 (zero-filled .bss).
unsigned int g_Va00E03828;
extern unsigned int g_Va00E03834;
// g_Va00E03834: matched references place it at VA 0xe03834 (zero-filled .bss).
unsigned int g_Va00E03834;
extern unsigned int g_Va00E0383C;
// g_Va00E0383C: matched references place it at VA 0xe0383c (zero-filled .bss).
unsigned int g_Va00E0383C;
extern unsigned int g_Va00E03844;
// g_Va00E03844: matched references place it at VA 0xe03844 (zero-filled .bss).
unsigned int g_Va00E03844;
extern unsigned int g_Va00E03850;
// g_Va00E03850: matched references place it at VA 0xe03850 (zero-filled .bss).
unsigned int g_Va00E03850;
extern unsigned int g_Va00E03858;
// g_Va00E03858: matched references place it at VA 0xe03858 (zero-filled .bss).
unsigned int g_Va00E03858;
extern unsigned int g_Va00E03864;
// g_Va00E03864: matched references place it at VA 0xe03864 (zero-filled .bss).
unsigned int g_Va00E03864;
extern unsigned int g_Va00E03870;
// g_Va00E03870: matched references place it at VA 0xe03870 (zero-filled .bss).
unsigned int g_Va00E03870;
extern unsigned int g_Va00E03878;
// g_Va00E03878: matched references place it at VA 0xe03878 (zero-filled .bss).
unsigned int g_Va00E03878;
extern unsigned int g_Va00E03880;
// g_Va00E03880: matched references place it at VA 0xe03880 (zero-filled .bss).
unsigned int g_Va00E03880;
extern unsigned int g_Va00E03890;
// g_Va00E03890: matched references place it at VA 0xe03890 (zero-filled .bss).
unsigned int g_Va00E03890;
extern unsigned int g_Va00E03898;
// g_Va00E03898: matched references place it at VA 0xe03898 (zero-filled .bss).
unsigned int g_Va00E03898;
extern unsigned int g_Va00E038A4;
// g_Va00E038A4: matched references place it at VA 0xe038a4 (zero-filled .bss).
unsigned int g_Va00E038A4;
extern unsigned int g_Va00E038B0;
// g_Va00E038B0: matched references place it at VA 0xe038b0 (zero-filled .bss).
unsigned int g_Va00E038B0;
extern unsigned int g_Va00E038B8;
// g_Va00E038B8: matched references place it at VA 0xe038b8 (zero-filled .bss).
unsigned int g_Va00E038B8;
extern unsigned int g_Va00E038C4;
// g_Va00E038C4: matched references place it at VA 0xe038c4 (zero-filled .bss).
unsigned int g_Va00E038C4;
extern unsigned int g_Va00E038CC;
// g_Va00E038CC: matched references place it at VA 0xe038cc (zero-filled .bss).
unsigned int g_Va00E038CC;
extern unsigned int g_Va00E038D8;
// g_Va00E038D8: matched references place it at VA 0xe038d8 (zero-filled .bss).
unsigned int g_Va00E038D8;
extern unsigned int g_Va00E038E0;
// g_Va00E038E0: matched references place it at VA 0xe038e0 (zero-filled .bss).
unsigned int g_Va00E038E0;
extern unsigned int g_Va00E038E8;
// g_Va00E038E8: matched references place it at VA 0xe038e8 (zero-filled .bss).
unsigned int g_Va00E038E8;
extern unsigned int g_Va00E038F0;
// g_Va00E038F0: matched references place it at VA 0xe038f0 (zero-filled .bss).
unsigned int g_Va00E038F0;
extern unsigned int g_Va00E038FC;
// g_Va00E038FC: matched references place it at VA 0xe038fc (zero-filled .bss).
unsigned int g_Va00E038FC;

unsigned int Rva0078BE48ClearFlag(void)
{
	return g_Va00E03804 &= 0xFFFFFFFEu;
}

unsigned int Rva0078BEFEClearFlag(void)
{
	return g_Va00E0380C &= 0xFFFFFFFEu;
}

unsigned int Rva0078BF27ClearFlag(void)
{
	return g_Va00E03814 &= 0xFFFFFFFEu;
}

unsigned int Rva0078BF3EClearFlag(void)
{
	return g_Va00E0381C &= 0xFFFFFFFEu;
}

unsigned int Rva0078BF67ClearFlag(void)
{
	return g_Va00E03828 &= 0xFFFFFFFEu;
}

unsigned int Rva0078BF90ClearFlag(void)
{
	return g_Va00E03834 &= 0xFFFFFFFEu;
}

unsigned int Rva0078BFA7ClearFlag(void)
{
	return g_Va00E0383C &= 0xFFFFFFFEu;
}

unsigned int Rva0078BFD0ClearFlag(void)
{
	return g_Va00E03844 &= 0xFFFFFFFEu;
}

unsigned int Rva0078C03EClearFlag(void)
{
	return g_Va00E03850 &= 0xFFFFFFFEu;
}

unsigned int Rva0078C055ClearFlag(void)
{
	return g_Va00E03858 &= 0xFFFFFFFEu;
}

unsigned int Rva0078C081ClearFlag(void)
{
	return g_Va00E03864 &= 0xFFFFFFFEu;
}

unsigned int Rva0078C098ClearFlag(void)
{
	return g_Va00E03870 &= 0xFFFFFFFEu;
}

unsigned int Rva0078C0AFClearFlag(void)
{
	return g_Va00E03878 &= 0xFFFFFFFEu;
}

unsigned int Rva0078C0C6ClearFlag(void)
{
	return g_Va00E03880 &= 0xFFFFFFFEu;
}

unsigned int Rva0078C0EFClearFlag(void)
{
	return g_Va00E03890 &= 0xFFFFFFFEu;
}

unsigned int Rva0078C106ClearFlag(void)
{
	return g_Va00E03898 &= 0xFFFFFFFEu;
}

unsigned int Rva0078C11DClearFlag(void)
{
	return g_Va00E038A4 &= 0xFFFFFFFEu;
}

unsigned int Rva0078C146ClearFlag(void)
{
	return g_Va00E038B0 &= 0xFFFFFFFEu;
}

unsigned int Rva0078C16FClearFlag(void)
{
	return g_Va00E038B8 &= 0xFFFFFFFEu;
}

unsigned int Rva0078C186ClearFlag(void)
{
	return g_Va00E038C4 &= 0xFFFFFFFEu;
}

unsigned int Rva0078C22AClearFlag(void)
{
	return g_Va00E038CC &= 0xFFFFFFFEu;
}

unsigned int Rva0078C2B8ClearFlag(void)
{
	return g_Va00E038D8 &= 0xFFFFFFFEu;
}

unsigned int Rva0078C2F3ClearFlag(void)
{
	return g_Va00E038E0 &= 0xFFFFFFFEu;
}

unsigned int Rva0078C30AClearFlag(void)
{
	return g_Va00E038E8 &= 0xFFFFFFFEu;
}

unsigned int Rva0078C428ClearFlag(void)
{
	return g_Va00E038F0 &= 0xFFFFFFFEu;
}

unsigned int Rva0078C4A1ClearFlag(void)
{
	return g_Va00E038FC &= 0xFFFFFFFEu;
}

