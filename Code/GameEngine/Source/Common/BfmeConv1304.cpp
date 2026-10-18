// cl: /Od /Gy
// Open-BFME5 conversions.

// Defined by BfmeConv1303.cpp: retail has one STL diagnostic table.
extern void *g_bfmeTableSWA[27];

void bfmeWriteSXA(void *sink, ...);
void bfmeFlushSXA(void);

void bfmeGoSXA(int a, int b, int c, int d)
{
	bfmeWriteSXA(g_bfmeTableSWA[2], c, d, g_bfmeTableSWA[b], c, d, a);
	bfmeFlushSXA();
}

extern "C" __declspec(dllimport) void __cdecl abort(void);

void Rva00023D70Abort(void)
{
	abort();
}
