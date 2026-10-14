// cl: /O1 /arch:SSE /G7 /MD /DNDEBUG
// Retail 0x00094D3A..0x00094D44: one cdecl int argument.
// The matching getter at 94B87 and cloud transition at 953B3 prove the
// existing int mode owner. Historical setter name remains unproven.
extern int g_Va00DB47EC;
void Rva00094D3ASet(int mode) { g_Va00DB47EC=mode; }
