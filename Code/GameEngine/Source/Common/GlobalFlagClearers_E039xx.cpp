// Twenty-seven B2-native flag-word clearers on 27 .data flag words
// (0x00E03904-0x00E039FC):
//
//     mov eax,[<address>] / and al,<mask8> / mov [<address>],eax / ret
//
// Same /G7 byte-register narrowing as GlobalFlagClearers_08.cpp (defaults
// emit `and eax,imm`). Each body carries a .rdata table slot. Identity is
// not recovered; names derive from addresses.
// following GlobalFlagClearers_E038xx.cpp.
// cl: /G7 /MD /EHsc /DNDEBUG

extern unsigned int g_Va00E03904;
// g_Va00E03904: matched references place it at VA 0xe03904 (zero-filled .bss).
unsigned int g_Va00E03904;
extern unsigned int g_Va00E0390C;
// g_Va00E0390C: matched references place it at VA 0xe0390c (zero-filled .bss).
unsigned int g_Va00E0390C;
extern unsigned int g_Va00E03914;
// g_Va00E03914: matched references place it at VA 0xe03914 (zero-filled .bss).
unsigned int g_Va00E03914;
extern unsigned int g_Va00E0391C;
// g_Va00E0391C: matched references place it at VA 0xe0391c (zero-filled .bss).
unsigned int g_Va00E0391C;
extern unsigned int g_Va00E03924;
// g_Va00E03924: matched references place it at VA 0xe03924 (zero-filled .bss).
unsigned int g_Va00E03924;
extern unsigned int g_Va00E03930;
// g_Va00E03930: matched references place it at VA 0xe03930 (zero-filled .bss).
unsigned int g_Va00E03930;
extern unsigned int g_Va00E03938;
// g_Va00E03938: matched references place it at VA 0xe03938 (zero-filled .bss).
unsigned int g_Va00E03938;
extern unsigned int g_Va00E03940;
// g_Va00E03940: matched references place it at VA 0xe03940 (zero-filled .bss).
unsigned int g_Va00E03940;
extern unsigned int g_Va00E03948;
// g_Va00E03948: matched references place it at VA 0xe03948 (zero-filled .bss).
unsigned int g_Va00E03948;
extern unsigned int g_Va00E03954;
// g_Va00E03954: matched references place it at VA 0xe03954 (zero-filled .bss).
unsigned int g_Va00E03954;
extern unsigned int g_Va00E03960;
// g_Va00E03960: matched references place it at VA 0xe03960 (zero-filled .bss).
unsigned int g_Va00E03960;
extern unsigned int g_Va00E0396C;
// g_Va00E0396C: matched references place it at VA 0xe0396c (zero-filled .bss).
unsigned int g_Va00E0396C;
extern unsigned int g_Va00E03978;
// g_Va00E03978: matched references place it at VA 0xe03978 (zero-filled .bss).
unsigned int g_Va00E03978;
extern unsigned int g_Va00E03984;
// g_Va00E03984: matched references place it at VA 0xe03984 (zero-filled .bss).
unsigned int g_Va00E03984;
extern unsigned int g_Va00E0398C;
// g_Va00E0398C: matched references place it at VA 0xe0398c (zero-filled .bss).
unsigned int g_Va00E0398C;
extern unsigned int g_Va00E0399C;
// g_Va00E0399C: matched references place it at VA 0xe0399c (zero-filled .bss).
unsigned int g_Va00E0399C;
extern unsigned int g_Va00E039A4;
// g_Va00E039A4: matched references place it at VA 0xe039a4 (zero-filled .bss).
unsigned int g_Va00E039A4;
extern unsigned int g_Va00E039B0;
// g_Va00E039B0: matched references place it at VA 0xe039b0 (zero-filled .bss).
unsigned int g_Va00E039B0;
extern unsigned int g_Va00E039B8;
// g_Va00E039B8: matched references place it at VA 0xe039b8 (zero-filled .bss).
unsigned int g_Va00E039B8;
extern unsigned int g_Va00E039C0;
// g_Va00E039C0: matched references place it at VA 0xe039c0 (zero-filled .bss).
unsigned int g_Va00E039C0;
extern unsigned int g_Va00E039C8;
// g_Va00E039C8: matched references place it at VA 0xe039c8 (zero-filled .bss).
unsigned int g_Va00E039C8;
extern unsigned int g_Va00E039D0;
// g_Va00E039D0: matched references place it at VA 0xe039d0 (zero-filled .bss).
unsigned int g_Va00E039D0;
extern unsigned int g_Va00E039D8;
// g_Va00E039D8: matched references place it at VA 0xe039d8 (zero-filled .bss).
unsigned int g_Va00E039D8;
extern unsigned int g_Va00E039E0;
// g_Va00E039E0: matched references place it at VA 0xe039e0 (zero-filled .bss).
unsigned int g_Va00E039E0;
extern unsigned int g_Va00E039E8;
// g_Va00E039E8: matched references place it at VA 0xe039e8 (zero-filled .bss).
unsigned int g_Va00E039E8;
extern unsigned int g_Va00E039F4;
// g_Va00E039F4: matched references place it at VA 0xe039f4 (zero-filled .bss).
unsigned int g_Va00E039F4;
extern unsigned int g_Va00E039FC;
// g_Va00E039FC: matched references place it at VA 0xe039fc (zero-filled .bss).
unsigned int g_Va00E039FC;

unsigned int Rva0078C4F2ClearFlag(void)
{
	return g_Va00E03904 &= 0xFFFFFFFEu;
}

unsigned int Rva0078C509ClearFlag(void)
{
	return g_Va00E0390C &= 0xFFFFFFFEu;
}

unsigned int Rva0078C53AClearFlag(void)
{
	return g_Va00E03914 &= 0xFFFFFFFEu;
}

unsigned int Rva0078C59DClearFlag(void)
{
	return g_Va00E0391C &= 0xFFFFFFFEu;
}

unsigned int Rva0078C60BClearFlag(void)
{
	return g_Va00E03924 &= 0xFFFFFFFEu;
}

unsigned int Rva0078C634ClearFlag(void)
{
	return g_Va00E03930 &= 0xFFFFFFFEu;
}

unsigned int Rva0078C68AClearFlag(void)
{
	return g_Va00E03938 &= 0xFFFFFFFEu;
}

unsigned int Rva0078C6A9ClearFlag(void)
{
	return g_Va00E03940 &= 0xFFFFFFFEu;
}

unsigned int Rva0078C714ClearFlag(void)
{
	return g_Va00E03948 &= 0xFFFFFFFEu;
}

unsigned int Rva0078C765ClearFlag(void)
{
	return g_Va00E03954 &= 0xFFFFFFFEu;
}

unsigned int Rva0078C7E5ClearFlag(void)
{
	return g_Va00E03960 &= 0xFFFFFFFEu;
}

unsigned int Rva0078C82BClearFlag(void)
{
	return g_Va00E0396C &= 0xFFFFFFFEu;
}

unsigned int Rva0078C897ClearFlag(void)
{
	return g_Va00E03978 &= 0xFFFFFFFEu;
}

unsigned int Rva0078C8AEClearFlag(void)
{
	return g_Va00E03984 &= 0xFFFFFFFEu;
}

unsigned int Rva0078C8E2ClearFlag(void)
{
	return g_Va00E0398C &= 0xFFFFFFFEu;
}

unsigned int Rva0078C977ClearFlag(void)
{
	return g_Va00E0399C &= 0xFFFFFFFEu;
}

unsigned int Rva0078C9A0ClearFlag(void)
{
	return g_Va00E039A4 &= 0xFFFFFFFEu;
}

unsigned int Rva0078C9FBClearFlag(void)
{
	return g_Va00E039B0 &= 0xFFFFFFFEu;
}

unsigned int Rva0078CA8BClearFlag(void)
{
	return g_Va00E039B8 &= 0xFFFFFFFEu;
}

unsigned int Rva0078CAF6ClearFlag(void)
{
	return g_Va00E039C0 &= 0xFFFFFFFEu;
}

unsigned int Rva0078CB3CClearFlag(void)
{
	return g_Va00E039C8 &= 0xFFFFFFFEu;
}

unsigned int Rva0078CBB6ClearFlag(void)
{
	return g_Va00E039D0 &= 0xFFFFFFFEu;
}

unsigned int Rva0078CC01ClearFlag(void)
{
	return g_Va00E039D8 &= 0xFFFFFFFEu;
}

unsigned int Rva0078CC5CClearFlag(void)
{
	return g_Va00E039E0 &= 0xFFFFFFFEu;
}

unsigned int Rva0078CC85ClearFlag(void)
{
	return g_Va00E039E8 &= 0xFFFFFFFEu;
}

unsigned int Rva0078CCC8ClearFlag(void)
{
	return g_Va00E039F4 &= 0xFFFFFFFEu;
}

unsigned int Rva0078CDA4ClearFlag(void)
{
	return g_Va00E039FC &= 0xFFFFFFFEu;
}

