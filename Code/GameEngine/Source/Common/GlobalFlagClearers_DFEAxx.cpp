// Twelve B2-native flag-word clearers on twelve .data flag words
// (0x00DFEAE0-0x00DFED40):
//
//     mov eax,[<address>] / and al,<mask8> / mov [<address>],eax / ret
//
// Same /G7 byte-register narrowing as GlobalFlagClearers_08.cpp (defaults
// emit `and eax,imm`). Each body carries a .rdata table slot. Identity is
// not recovered; names derive from addresses,
// following GlobalFlagClearers_DFE9xx.cpp.
// cl: /G7 /MD /EHsc /DNDEBUG

extern unsigned int g_Va00DFEAE0;
// g_Va00DFEAE0: matched references place it at VA 0xdfeae0 (zero-filled .bss).
unsigned int g_Va00DFEAE0;
extern unsigned int g_Va00DFEAE8;
// g_Va00DFEAE8: matched references place it at VA 0xdfeae8 (zero-filled .bss).
unsigned int g_Va00DFEAE8;
extern unsigned int g_Va00DFEB54;
// g_Va00DFEB54: matched references place it at VA 0xdfeb54 (zero-filled .bss).
unsigned int g_Va00DFEB54;
extern unsigned int g_Va00DFEC4C;
extern unsigned int g_Va00DFEC60;
extern unsigned int g_Va00DFEC80;
extern unsigned int g_Va00DFECE0;
extern unsigned int g_Va00DFECE8;
extern unsigned int g_Va00DFECF0;
extern unsigned int g_Va00DFECF8;
extern unsigned int g_Va00DFED00;
extern unsigned int g_Va00DFED40;

unsigned int Rva00772D90ClearFlag(void)
{
	return g_Va00DFEAE0 &= 0xFFFFFFFEu;
}

unsigned int Rva00772DB9ClearFlag(void)
{
	return g_Va00DFEAE8 &= 0xFFFFFFFEu;
}

unsigned int Rva00773046ClearFlag(void)
{
	return g_Va00DFEB54 &= 0xFFFFFFFEu;
}

// Rva007735C6ClearFlag: defined in GlobalFlagClearers_DFECxx.cpp (its row's unit).
unsigned int Rva007735C6ClearFlag(void);

// Rva0077388BClearFlag: defined in GlobalFlagClearers_DFECxx.cpp (its row's unit).
unsigned int Rva0077388BClearFlag(void);

// Rva00773EB8ClearFlag: defined in GlobalFlagClearers_DFECxx.cpp (its row's unit).
unsigned int Rva00773EB8ClearFlag(void);

// Rva007742BCClearFlag: defined in GlobalFlagClearers_DFECxx.cpp (its row's unit).
unsigned int Rva007742BCClearFlag(void);

// Rva007742D3ClearFlag: defined in GlobalFlagClearers_DFECxx.cpp (its row's unit).
unsigned int Rva007742D3ClearFlag(void);

// Rva007742EAClearFlag: defined in GlobalFlagClearers_DFECxx.cpp (its row's unit).
unsigned int Rva007742EAClearFlag(void);

// Rva00774313ClearFlag: defined in GlobalFlagClearers_DFECxx.cpp (its row's unit).
unsigned int Rva00774313ClearFlag(void);

// Rva0077433CClearFlag: defined in GlobalFlagClearers_DFEDxx.cpp (its row's unit).
unsigned int Rva0077433CClearFlag(void);

// Rva0077444AClearFlag: defined in GlobalFlagClearers_DFEDxx.cpp (its row's unit).
unsigned int Rva0077444AClearFlag(void);
