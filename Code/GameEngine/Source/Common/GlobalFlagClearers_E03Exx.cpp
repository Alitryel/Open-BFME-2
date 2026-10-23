// Twenty-three B2-native flag-word clearers on 23 .data flag words
// (0x00E03E00-0x00E03EF4):
//
//     mov eax,[<address>] / and al,<mask8> / mov [<address>],eax / ret
//
// Same /G7 byte-register narrowing as GlobalFlagClearers_08.cpp (defaults
// emit `and eax,imm`). Each body carries a .rdata table slot. Identity is
// not recovered; names derive from addresses.
// following GlobalFlagClearers_E03Dxx.cpp.
// cl: /G7 /MD /EHsc /DNDEBUG

extern unsigned int g_Va00E03E00;
// g_Va00E03E00: matched references place it at VA 0xe03e00 (zero-filled .bss).
unsigned int g_Va00E03E00;
extern unsigned int g_Va00E03E08;
// g_Va00E03E08: matched references place it at VA 0xe03e08 (zero-filled .bss).
unsigned int g_Va00E03E08;
extern unsigned int g_Va00E03E10;
// g_Va00E03E10: matched references place it at VA 0xe03e10 (zero-filled .bss).
unsigned int g_Va00E03E10;
extern unsigned int g_Va00E03E1C;
// g_Va00E03E1C: matched references place it at VA 0xe03e1c (zero-filled .bss).
unsigned int g_Va00E03E1C;
extern unsigned int g_Va00E03E28;
// g_Va00E03E28: matched references place it at VA 0xe03e28 (zero-filled .bss).
unsigned int g_Va00E03E28;
extern unsigned int g_Va00E03E30;
// g_Va00E03E30: matched references place it at VA 0xe03e30 (zero-filled .bss).
unsigned int g_Va00E03E30;
extern unsigned int g_Va00E03E38;
// g_Va00E03E38: matched references place it at VA 0xe03e38 (zero-filled .bss).
unsigned int g_Va00E03E38;
extern unsigned int g_Va00E03E44;
// g_Va00E03E44: matched references place it at VA 0xe03e44 (zero-filled .bss).
unsigned int g_Va00E03E44;
extern unsigned int g_Va00E03E50;
// g_Va00E03E50: matched references place it at VA 0xe03e50 (zero-filled .bss).
unsigned int g_Va00E03E50;
extern unsigned int g_Va00E03E5C;
// g_Va00E03E5C: matched references place it at VA 0xe03e5c (zero-filled .bss).
unsigned int g_Va00E03E5C;
extern unsigned int g_Va00E03E68;
// g_Va00E03E68: matched references place it at VA 0xe03e68 (zero-filled .bss).
unsigned int g_Va00E03E68;
extern unsigned int g_Va00E03E74;
// g_Va00E03E74: matched references place it at VA 0xe03e74 (zero-filled .bss).
unsigned int g_Va00E03E74;
extern unsigned int g_Va00E03E80;
// g_Va00E03E80: matched references place it at VA 0xe03e80 (zero-filled .bss).
unsigned int g_Va00E03E80;
extern unsigned int g_Va00E03E8C;
// g_Va00E03E8C: matched references place it at VA 0xe03e8c (zero-filled .bss).
unsigned int g_Va00E03E8C;
extern unsigned int g_Va00E03E98;
// g_Va00E03E98: matched references place it at VA 0xe03e98 (zero-filled .bss).
unsigned int g_Va00E03E98;
extern unsigned int g_Va00E03EA4;
// g_Va00E03EA4: matched references place it at VA 0xe03ea4 (zero-filled .bss).
unsigned int g_Va00E03EA4;
extern unsigned int g_Va00E03EB0;
// g_Va00E03EB0: matched references place it at VA 0xe03eb0 (zero-filled .bss).
unsigned int g_Va00E03EB0;
extern unsigned int g_Va00E03EBC;
// g_Va00E03EBC: matched references place it at VA 0xe03ebc (zero-filled .bss).
unsigned int g_Va00E03EBC;
extern unsigned int g_Va00E03EC8;
// g_Va00E03EC8: matched references place it at VA 0xe03ec8 (zero-filled .bss).
unsigned int g_Va00E03EC8;
extern unsigned int g_Va00E03ED4;
// g_Va00E03ED4: matched references place it at VA 0xe03ed4 (zero-filled .bss).
unsigned int g_Va00E03ED4;
extern unsigned int g_Va00E03EE0;
// g_Va00E03EE0: matched references place it at VA 0xe03ee0 (zero-filled .bss).
unsigned int g_Va00E03EE0;
extern unsigned int g_Va00E03EE8;
// g_Va00E03EE8: matched references place it at VA 0xe03ee8 (zero-filled .bss).
unsigned int g_Va00E03EE8;
extern unsigned int g_Va00E03EF4;
// g_Va00E03EF4: matched references place it at VA 0xe03ef4 (zero-filled .bss).
unsigned int g_Va00E03EF4;

unsigned int Rva0078EB7BClearFlag(void)
{
	return g_Va00E03E00 &= 0xFFFFFFFEu;
}

unsigned int Rva0078EB92ClearFlag(void)
{
	return g_Va00E03E08 &= 0xFFFFFFFEu;
}

unsigned int Rva0078EBD7ClearFlag(void)
{
	return g_Va00E03E10 &= 0xFFFFFFFEu;
}

unsigned int Rva0078EBEEClearFlag(void)
{
	return g_Va00E03E1C &= 0xFFFFFFFEu;
}

unsigned int Rva0078EC05ClearFlag(void)
{
	return g_Va00E03E28 &= 0xFFFFFFFEu;
}

unsigned int Rva0078EC2EClearFlag(void)
{
	return g_Va00E03E30 &= 0xFFFFFFFEu;
}

unsigned int Rva0078EC45ClearFlag(void)
{
	return g_Va00E03E38 &= 0xFFFFFFFEu;
}

unsigned int Rva0078EC5CClearFlag(void)
{
	return g_Va00E03E44 &= 0xFFFFFFFEu;
}

unsigned int Rva0078EC73ClearFlag(void)
{
	return g_Va00E03E50 &= 0xFFFFFFFEu;
}

unsigned int Rva0078ECE6ClearFlag(void)
{
	return g_Va00E03E5C &= 0xFFFFFFFEu;
}

unsigned int Rva0078ECFDClearFlag(void)
{
	return g_Va00E03E68 &= 0xFFFFFFFEu;
}

unsigned int Rva0078ED14ClearFlag(void)
{
	return g_Va00E03E74 &= 0xFFFFFFFEu;
}

unsigned int Rva0078ED2BClearFlag(void)
{
	return g_Va00E03E80 &= 0xFFFFFFFEu;
}

unsigned int Rva0078ED42ClearFlag(void)
{
	return g_Va00E03E8C &= 0xFFFFFFFEu;
}

unsigned int Rva0078ED59ClearFlag(void)
{
	return g_Va00E03E98 &= 0xFFFFFFFEu;
}

unsigned int Rva0078EDF6ClearFlag(void)
{
	return g_Va00E03EA4 &= 0xFFFFFFFEu;
}

unsigned int Rva0078EE5BClearFlag(void)
{
	return g_Va00E03EB0 &= 0xFFFFFFFEu;
}

unsigned int Rva0078EE72ClearFlag(void)
{
	return g_Va00E03EBC &= 0xFFFFFFFEu;
}

unsigned int Rva0078EE89ClearFlag(void)
{
	return g_Va00E03EC8 &= 0xFFFFFFFEu;
}

unsigned int Rva0078EEA0ClearFlag(void)
{
	return g_Va00E03ED4 &= 0xFFFFFFFEu;
}

unsigned int Rva0078EEB7ClearFlag(void)
{
	return g_Va00E03EE0 &= 0xFFFFFFFEu;
}

unsigned int Rva0078EEE8ClearFlag(void)
{
	return g_Va00E03EE8 &= 0xFFFFFFFEu;
}

unsigned int Rva0078EF1CClearFlag(void)
{
	return g_Va00E03EF4 &= 0xFFFFFFFEu;
}

