// Twenty-four B2-native flag-word clearers on 24 .data flag words
// (0x00E03704-0x00E037FC):
//
//     mov eax,[<address>] / and al,<mask8> / mov [<address>],eax / ret
//
// Same /G7 byte-register narrowing as GlobalFlagClearers_08.cpp (defaults
// emit `and eax,imm`). Each body carries a .rdata table slot. Identity is
// not recovered; names derive from addresses.
// following GlobalFlagClearers_E036xx.cpp.
// cl: /G7 /MD /EHsc /DNDEBUG

extern unsigned int g_Va00E03704;
// g_Va00E03704: matched references place it at VA 0xe03704 (zero-filled .bss).
unsigned int g_Va00E03704;
extern unsigned int g_Va00E0370C;
// g_Va00E0370C: matched references place it at VA 0xe0370c (zero-filled .bss).
unsigned int g_Va00E0370C;
extern unsigned int g_Va00E03718;
// g_Va00E03718: matched references place it at VA 0xe03718 (zero-filled .bss).
unsigned int g_Va00E03718;
extern unsigned int g_Va00E03720;
// g_Va00E03720: matched references place it at VA 0xe03720 (zero-filled .bss).
unsigned int g_Va00E03720;
extern unsigned int g_Va00E0372C;
// g_Va00E0372C: matched references place it at VA 0xe0372c (zero-filled .bss).
unsigned int g_Va00E0372C;
extern unsigned int g_Va00E03738;
// g_Va00E03738: matched references place it at VA 0xe03738 (zero-filled .bss).
unsigned int g_Va00E03738;
extern unsigned int g_Va00E0374C;
// g_Va00E0374C: matched references place it at VA 0xe0374c (zero-filled .bss).
unsigned int g_Va00E0374C;
extern unsigned int g_Va00E03754;
// g_Va00E03754: matched references place it at VA 0xe03754 (zero-filled .bss).
unsigned int g_Va00E03754;
extern unsigned int g_Va00E03760;
// g_Va00E03760: matched references place it at VA 0xe03760 (zero-filled .bss).
unsigned int g_Va00E03760;
extern unsigned int g_Va00E03768;
// g_Va00E03768: matched references place it at VA 0xe03768 (zero-filled .bss).
unsigned int g_Va00E03768;
extern unsigned int g_Va00E03770;
// g_Va00E03770: matched references place it at VA 0xe03770 (zero-filled .bss).
unsigned int g_Va00E03770;
extern unsigned int g_Va00E0377C;
// g_Va00E0377C: matched references place it at VA 0xe0377c (zero-filled .bss).
unsigned int g_Va00E0377C;
extern unsigned int g_Va00E03788;
// g_Va00E03788: matched references place it at VA 0xe03788 (zero-filled .bss).
unsigned int g_Va00E03788;
extern unsigned int g_Va00E03794;
// g_Va00E03794: matched references place it at VA 0xe03794 (zero-filled .bss).
unsigned int g_Va00E03794;
extern unsigned int g_Va00E0379C;
// g_Va00E0379C: matched references place it at VA 0xe0379c (zero-filled .bss).
unsigned int g_Va00E0379C;
extern unsigned int g_Va00E037A8;
// g_Va00E037A8: matched references place it at VA 0xe037a8 (zero-filled .bss).
unsigned int g_Va00E037A8;
extern unsigned int g_Va00E037B4;
// g_Va00E037B4: matched references place it at VA 0xe037b4 (zero-filled .bss).
unsigned int g_Va00E037B4;
extern unsigned int g_Va00E037C0;
// g_Va00E037C0: matched references place it at VA 0xe037c0 (zero-filled .bss).
unsigned int g_Va00E037C0;
extern unsigned int g_Va00E037C8;
// g_Va00E037C8: matched references place it at VA 0xe037c8 (zero-filled .bss).
unsigned int g_Va00E037C8;
extern unsigned int g_Va00E037D8;
// g_Va00E037D8: matched references place it at VA 0xe037d8 (zero-filled .bss).
unsigned int g_Va00E037D8;
extern unsigned int g_Va00E037E0;
// g_Va00E037E0: matched references place it at VA 0xe037e0 (zero-filled .bss).
unsigned int g_Va00E037E0;
extern unsigned int g_Va00E037E8;
// g_Va00E037E8: matched references place it at VA 0xe037e8 (zero-filled .bss).
unsigned int g_Va00E037E8;
extern unsigned int g_Va00E037F0;
// g_Va00E037F0: matched references place it at VA 0xe037f0 (zero-filled .bss).
unsigned int g_Va00E037F0;
extern unsigned int g_Va00E037FC;
// g_Va00E037FC: matched references place it at VA 0xe037fc (zero-filled .bss).
unsigned int g_Va00E037FC;

unsigned int Rva0078B615ClearFlag(void)
{
	return g_Va00E03704 &= 0xFFFFFFFEu;
}

unsigned int Rva0078B65AClearFlag(void)
{
	return g_Va00E0370C &= 0xFFFFFFFEu;
}

unsigned int Rva0078B71DClearFlag(void)
{
	return g_Va00E03718 &= 0xFFFFFFFEu;
}

unsigned int Rva0078B734ClearFlag(void)
{
	return g_Va00E03720 &= 0xFFFFFFFEu;
}

unsigned int Rva0078B797ClearFlag(void)
{
	return g_Va00E0372C &= 0xFFFFFFFEu;
}

unsigned int Rva0078B7C0ClearFlag(void)
{
	return g_Va00E03738 &= 0xFFFFFFFEu;
}

unsigned int Rva0078B80DClearFlag(void)
{
	return g_Va00E0374C &= 0xFFFFFFFEu;
}

unsigned int Rva0078B87AClearFlag(void)
{
	return g_Va00E03754 &= 0xFFFFFFFEu;
}

unsigned int Rva0078B8FCClearFlag(void)
{
	return g_Va00E03760 &= 0xFFFFFFFEu;
}

unsigned int Rva0078B971ClearFlag(void)
{
	return g_Va00E03768 &= 0xFFFFFFFEu;
}

unsigned int Rva0078B99AClearFlag(void)
{
	return g_Va00E03770 &= 0xFFFFFFFEu;
}

unsigned int Rva0078BA7AClearFlag(void)
{
	return g_Va00E0377C &= 0xFFFFFFFEu;
}

unsigned int Rva0078BAF1ClearFlag(void)
{
	return g_Va00E03788 &= 0xFFFFFFFEu;
}

unsigned int Rva0078BB61ClearFlag(void)
{
	return g_Va00E03794 &= 0xFFFFFFFEu;
}

unsigned int Rva0078BBAEClearFlag(void)
{
	return g_Va00E0379C &= 0xFFFFFFFEu;
}

unsigned int Rva0078BBE9ClearFlag(void)
{
	return g_Va00E037A8 &= 0xFFFFFFFEu;
}

unsigned int Rva0078BC00ClearFlag(void)
{
	return g_Va00E037B4 &= 0xFFFFFFFEu;
}

unsigned int Rva0078BC29ClearFlag(void)
{
	return g_Va00E037C0 &= 0xFFFFFFFEu;
}

unsigned int Rva0078BC40ClearFlag(void)
{
	return g_Va00E037C8 &= 0xFFFFFFFEu;
}

unsigned int Rva0078BC95ClearFlag(void)
{
	return g_Va00E037D8 &= 0xFFFFFFFEu;
}

unsigned int Rva0078BCBEClearFlag(void)
{
	return g_Va00E037E0 &= 0xFFFFFFFEu;
}

unsigned int Rva0078BD0CClearFlag(void)
{
	return g_Va00E037E8 &= 0xFFFFFFFEu;
}

unsigned int Rva0078BD35ClearFlag(void)
{
	return g_Va00E037F0 &= 0xFFFFFFFEu;
}

unsigned int Rva0078BDE5ClearFlag(void)
{
	return g_Va00E037FC &= 0xFFFFFFFEu;
}

