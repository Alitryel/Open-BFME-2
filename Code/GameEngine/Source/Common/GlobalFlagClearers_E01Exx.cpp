// Nine B2-native flag-word clearers on seven scattered .data flag words
// (0x0077CDC4-0x0077EBDC):
// The former77CDAD is the proven compiler cleanup of AI helper3449C5;
// that parent now owns the cleanup and its initialization guard.
//
//     mov eax,[<address>] / and al,<mask8> / mov [<address>],eax / ret
//
// Same /G7 byte-register narrowing as GlobalFlagClearers_08.cpp (defaults
// emit `and eax,imm`). Each body carries a .rdata table slot (0x00926600
// and on). Identity is not recovered; names derive from addresses,
// following GlobalFlagClearers_08.cpp.
// cl: /G7 /MD /EHsc /DNDEBUG

extern unsigned int g_Va00E01DF4;
// g_Va00E01DF4: matched references place it at VA 0xe01df4 (zero-filled .bss).
unsigned int g_Va00E01DF4;
extern unsigned int g_Va00E01DFC;
// g_Va00E01DFC: matched references place it at VA 0xe01dfc (zero-filled .bss).
unsigned int g_Va00E01DFC;
extern unsigned int g_Va00E01E38;
// g_Va00E01E38: matched references place it at VA 0xe01e38 (zero-filled .bss).
unsigned int g_Va00E01E38;
extern unsigned int g_Va00E01F00;
// g_Va00E01F00: matched references place it at VA 0xe01f00 (zero-filled .bss).
unsigned int g_Va00E01F00;
extern unsigned int g_Va00E01F08;
// g_Va00E01F08: matched references place it at VA 0xe01f08 (zero-filled .bss).
unsigned int g_Va00E01F08;
extern unsigned int g_Va00E02150;
// g_Va00E02150: matched references place it at VA 0xe02150 (zero-filled .bss).
unsigned int g_Va00E02150;
extern unsigned int g_Va00E02280;
// g_Va00E02280: matched references place it at VA 0xe02280 (zero-filled .bss).
unsigned int g_Va00E02280;

unsigned int Rva0077CDC4ClearFlag(void)
{
	return g_Va00E01DF4 &= 0xFFFFFFFEu;
}

unsigned int Rva0077CDDBClearFlag(void)
{
	return g_Va00E01DFC &= 0xFFFFFFFEu;
}

unsigned int Rva0077D9A9ClearFlag(void)
{
	return g_Va00E01E38 &= 0xFFFFFFFEu;
}

unsigned int Rva0077E895ClearFlag(void)
{
	return g_Va00E01F00 &= 0xFFFFFFFEu;
}

unsigned int Rva0077E8ACClearFlag(void)
{
	return g_Va00E01F08 &= 0xFFFFFFFEu;
}

unsigned int Rva0077EB71ClearFlag(void)
{
	return g_Va00E02150 &= 0xFFFFFFFEu;
}

unsigned int Rva0077EB8EClearFlag(void)
{
	return g_Va00E02150 &= 0xFFFFFFFDu;
}

unsigned int Rva0077EBC4ClearFlag(void)
{
	return g_Va00E02280 &= 0xFFFFFFF7u;
}

unsigned int Rva0077EBDCClearFlag(void)
{
	return g_Va00E02280 &= 0xFFFFFFEFu;
}
