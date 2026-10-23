// Ten B2-native flag-word clearers on nine scattered .data flag words
// (0x0076144C-0x00767CD3):
//
//     mov eax,[<address>] / and al,<mask8> / mov [<address>],eax / ret
//
// Same /G7 byte-register narrowing as GlobalFlagClearers_08.cpp (defaults
// emit `and eax,imm`). Each body carries a .rdata table slot (0x00904734
// and on). Identity is not recovered; names derive from addresses,
// following GlobalFlagClearers_08.cpp.
// cl: /G7 /MD /EHsc /DNDEBUG

extern unsigned int g_Va00DEA2FC;
// g_Va00DEA2FC: matched references place it at VA 0xdea2fc (zero-filled .bss).
unsigned int g_Va00DEA2FC;
extern unsigned int g_Va00DEA308;
// g_Va00DEA308: matched references place it at VA 0xdea308 (zero-filled .bss).
unsigned int g_Va00DEA308;
extern unsigned int g_Va00DEAF10;
// g_Va00DEAF10: matched references place it at VA 0xdeaf10 (zero-filled .bss).
unsigned int g_Va00DEAF10;
extern unsigned int g_Va00DEBFF0;
// g_Va00DEBFF0: matched references place it at VA 0xdebff0 (zero-filled .bss).
unsigned int g_Va00DEBFF0;
extern unsigned int g_Va00DEC0D8;
// g_Va00DEC0D8: matched references place it at VA 0xdec0d8 (zero-filled .bss).
unsigned int g_Va00DEC0D8;
extern unsigned int g_Va00DEC3B4;
// g_Va00DEC3B4: matched references place it at VA 0xdec3b4 (zero-filled .bss).
unsigned int g_Va00DEC3B4;
extern unsigned int g_Va00DF3678;
// g_Va00DF3678: matched references place it at VA 0xdf3678 (zero-filled .bss).
unsigned int g_Va00DF3678;
extern unsigned int g_Va00DF6F08;
// g_Va00DF6F08: matched references place it at VA 0xdf6f08 (zero-filled .bss).
unsigned int g_Va00DF6F08;
extern unsigned int g_Va00DF6FC8;
// g_Va00DF6FC8: matched references place it at VA 0xdf6fc8 (zero-filled .bss).
unsigned int g_Va00DF6FC8;

unsigned int Rva0076144CClearFlag(void)
{
	return g_Va00DEA2FC &= 0xFFFFFFFEu;
}

unsigned int Rva007614F7ClearFlag(void)
{
	return g_Va00DEA308 &= 0xFFFFFFFEu;
}

unsigned int Rva00761520ClearFlag(void)
{
	return g_Va00DEAF10 &= 0xFFFFFFFEu;
}

unsigned int Rva00763B63ClearFlag(void)
{
	return g_Va00DEBFF0 &= 0xFFFFFFFEu;
}

unsigned int Rva00763B78ClearFlag(void)
{
	return g_Va00DEBFF0 &= 0xFFFFFFFDu;
}

unsigned int Rva00763E50ClearFlag(void)
{
	return g_Va00DEC0D8 &= 0xFFFFFFFEu;
}

unsigned int Rva00764823ClearFlag(void)
{
	return g_Va00DEC3B4 &= 0xFFFFFFFEu;
}

unsigned int Rva007665ADClearFlag(void)
{
	return g_Va00DF3678 &= 0xFFFFFFFDu;
}

unsigned int Rva007669B0ClearFlag(void)
{
	return g_Va00DF6F08 &= 0xFFFFFFFEu;
}

unsigned int Rva00767CD3ClearFlag(void)
{
	return g_Va00DF6FC8 &= 0xFFFFFFFDu;
}
