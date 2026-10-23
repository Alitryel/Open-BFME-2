// Eighteen B2-native flag-word clearers on 17 .data flag words
// (0x00E03A04-0x00E03AF8):
//
//     mov eax,[<address>] / and al,<mask8> / mov [<address>],eax / ret
//
// Same /G7 byte-register narrowing as GlobalFlagClearers_08.cpp (defaults
// emit `and eax,imm`). Each body carries a .rdata table slot. Identity is
// not recovered; names derive from addresses.
// following GlobalFlagClearers_E039xx.cpp.
// cl: /G7 /MD /EHsc /DNDEBUG

extern unsigned int g_Va00E03A04;
// g_Va00E03A04: matched references place it at VA 0xe03a04 (zero-filled .bss).
unsigned int g_Va00E03A04;
extern unsigned int g_Va00E03A0C;
// g_Va00E03A0C: matched references place it at VA 0xe03a0c (zero-filled .bss).
unsigned int g_Va00E03A0C;
extern unsigned int g_Va00E03A18;
// g_Va00E03A18: matched references place it at VA 0xe03a18 (zero-filled .bss).
unsigned int g_Va00E03A18;
extern unsigned int g_Va00E03A20;
// g_Va00E03A20: matched references place it at VA 0xe03a20 (zero-filled .bss).
unsigned int g_Va00E03A20;
extern unsigned int g_Va00E03A28;
// g_Va00E03A28: matched references place it at VA 0xe03a28 (zero-filled .bss).
unsigned int g_Va00E03A28;
extern unsigned int g_Va00E03A30;
// g_Va00E03A30: matched references place it at VA 0xe03a30 (zero-filled .bss).
unsigned int g_Va00E03A30;
extern unsigned int g_Va00E03A3C;
// g_Va00E03A3C: matched references place it at VA 0xe03a3c (zero-filled .bss).
unsigned int g_Va00E03A3C;
extern unsigned int g_Va00E03A48;
// g_Va00E03A48: matched references place it at VA 0xe03a48 (zero-filled .bss).
unsigned int g_Va00E03A48;
extern unsigned int g_Va00E03A54;
// g_Va00E03A54: matched references place it at VA 0xe03a54 (zero-filled .bss).
unsigned int g_Va00E03A54;
extern unsigned int g_Va00E03A5C;
// g_Va00E03A5C: matched references place it at VA 0xe03a5c (zero-filled .bss).
unsigned int g_Va00E03A5C;
extern unsigned int g_Va00E03A64;
// g_Va00E03A64: matched references place it at VA 0xe03a64 (zero-filled .bss).
unsigned int g_Va00E03A64;
extern unsigned int g_Va00E03A6C;
// g_Va00E03A6C: matched references place it at VA 0xe03a6c (zero-filled .bss).
unsigned int g_Va00E03A6C;
extern unsigned int g_Va00E03AD0;
// g_Va00E03AD0: matched references place it at VA 0xe03ad0 (zero-filled .bss).
unsigned int g_Va00E03AD0;
extern unsigned int g_Va00E03ADC;
// g_Va00E03ADC: matched references place it at VA 0xe03adc (zero-filled .bss).
unsigned int g_Va00E03ADC;
extern unsigned int g_Va00E03AE8;
// g_Va00E03AE8: matched references place it at VA 0xe03ae8 (zero-filled .bss).
unsigned int g_Va00E03AE8;
extern unsigned int g_Va00E03AF0;
// g_Va00E03AF0: matched references place it at VA 0xe03af0 (zero-filled .bss).
unsigned int g_Va00E03AF0;
extern unsigned int g_Va00E03AF8;
// g_Va00E03AF8: matched references place it at VA 0xe03af8 (zero-filled .bss).
unsigned int g_Va00E03AF8;

unsigned int Rva0078CDF5ClearFlag(void)
{
	return g_Va00E03A04 &= 0xFFFFFFFEu;
}

unsigned int Rva0078CE38ClearFlag(void)
{
	return g_Va00E03A0C &= 0xFFFFFFFEu;
}

unsigned int Rva0078CEB5ClearFlag(void)
{
	return g_Va00E03A18 &= 0xFFFFFFFEu;
}

unsigned int Rva0078CF02ClearFlag(void)
{
	return g_Va00E03A20 &= 0xFFFFFFFEu;
}

unsigned int Rva0078CF19ClearFlag(void)
{
	return g_Va00E03A28 &= 0xFFFFFFFEu;
}

unsigned int Rva0078CF30ClearFlag(void)
{
	return g_Va00E03A30 &= 0xFFFFFFFEu;
}

unsigned int Rva0078CF64ClearFlag(void)
{
	return g_Va00E03A3C &= 0xFFFFFFFEu;
}

unsigned int Rva0078CFCAClearFlag(void)
{
	return g_Va00E03A48 &= 0xFFFFFFFEu;
}

unsigned int Rva0078CFF3ClearFlag(void)
{
	return g_Va00E03A54 &= 0xFFFFFFFEu;
}

unsigned int Rva0078D0DDClearFlag(void)
{
	return g_Va00E03A5C &= 0xFFFFFFFEu;
}

unsigned int Rva0078D157ClearFlag(void)
{
	return g_Va00E03A64 &= 0xFFFFFFFEu;
}

unsigned int Rva0078D19DClearFlag(void)
{
	return g_Va00E03A6C &= 0xFFFFFFFEu;
}

unsigned int Rva0078D26FClearFlag(void)
{
	return g_Va00E03AD0 &= 0xFFFFFFFEu;
}

unsigned int Rva0078D286ClearFlag(void)
{
	return g_Va00E03ADC &= 0xFFFFFFFEu;
}

unsigned int Rva0078D293ClearFlag(void)
{
	return g_Va00E03ADC &= 0xFFFFFFFDu;
}

unsigned int Rva0078D381ClearFlag(void)
{
	return g_Va00E03AE8 &= 0xFFFFFFFEu;
}

unsigned int Rva0078D3B6ClearFlag(void)
{
	return g_Va00E03AF0 &= 0xFFFFFFFEu;
}

unsigned int Rva0078D523ClearFlag(void)
{
	return g_Va00E03AF8 &= 0xFFFFFFFEu;
}

