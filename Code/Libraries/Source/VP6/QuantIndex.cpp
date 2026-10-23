// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001b7070.md 001b71c0.md 001c4740.md
// 001c47c0.md plus retail only. No decoder source was consulted.
struct BfmeS1040;
extern "C" void __cdecl VP6_init_dequantizer(BfmeS1040 *s, int version); // 0x001B70A0
extern void (__cdecl *g_bfmeQuantIndexBuilder)(BfmeS1040 *s);   // 0x00E22F74, InitLibrary.cpp

// 0x007D8560 identity index (ledger g_bfmeIdentityIndex), 0x007D8460 zig-zag order.
extern int g_bfmeIdentityIndex[];
extern unsigned int vp6DequantIndex[64];

// Retail .data tables, contents cited in specs 001c4740/001c47c0:
// 0x00DB7C28 MMX zig-zag order, 0x00DB7D28 MMX transpose index,
// 0x00DB7E28 WMT transpose index.
int vp6MmxZigzag[64] = {
	0, 1, 5, 6, 14, 15, 27, 28, 2, 4, 7, 13, 16, 26, 29, 42,
	3, 8, 12, 17, 25, 30, 41, 43, 9, 11, 18, 24, 31, 40, 44, 53,
	10, 19, 23, 32, 39, 45, 52, 54, 20, 22, 33, 38, 46, 51, 55, 60,
	21, 34, 37, 47, 50, 56, 59, 61, 35, 36, 48, 49, 57, 58, 62, 63,
};
int vp6MmxTransposeIndex[64] = {
	0, 8, 1, 2, 9, 16, 24, 17, 10, 3, 32, 11, 18, 25, 4, 12,
	5, 26, 19, 40, 33, 34, 41, 48, 27, 6, 13, 20, 28, 21, 14, 7,
	56, 49, 42, 35, 43, 50, 57, 36, 15, 22, 29, 30, 23, 44, 37, 58,
	51, 59, 38, 45, 52, 31, 60, 53, 46, 39, 47, 54, 61, 62, 55, 63,
};
int vp6WmtTransposeIndex[64] = {
	0, 8, 1, 2, 9, 16, 24, 17, 10, 3, 4, 11, 18, 25, 32, 40,
	33, 26, 19, 12, 5, 6, 13, 20, 27, 34, 41, 48, 56, 49, 42, 35,
	28, 21, 14, 7, 15, 22, 29, 36, 43, 50, 57, 58, 51, 44, 37, 30,
	23, 31, 38, 45, 52, 59, 60, 53, 46, 39, 47, 54, 61, 62, 55, 63,
};

struct Quantizer
{
	int frameQ;
	int quality;
	unsigned char pad0[0x30];
	int cached;
	int thresholds[64];
	int *index;
	unsigned char inverse[64];
};

// RVA 0x001B7070
extern "C" void __cdecl VP6_BuildQuantIndex_Generic(Quantizer *q)
{
	q->index = g_bfmeIdentityIndex;
	for (int i = 0; i < 64; ++i)
		q->inverse[vp6DequantIndex[i]] = (unsigned char)i;
}

// RVA 0x001B71C0: rebuild the index and dequantizer when the quality changed.
extern "C" void __cdecl VP6_UpdateQ(Quantizer *q, int version)
{
	if (q->thresholds[q->frameQ] != q->cached)
	{
		q->cached = q->quality;
		((void (__cdecl *)(Quantizer *))g_bfmeQuantIndexBuilder)(q);
		VP6_init_dequantizer((BfmeS1040 *)q, version);
	}
}

// RVA 0x001C4740: install the MMX transpose index and invert the composition
// of the MMX zig-zag order with it, four scan positions per pass.
extern "C" void __cdecl VP6_BuildQuantIndex_ForMMX(Quantizer *q)
{
	q->index = vp6MmxTransposeIndex;
	for (int i = 0; i < 64; i += 4)
	{
		q->inverse[vp6MmxTransposeIndex[vp6MmxZigzag[i]]] = (unsigned char)i;
		q->inverse[vp6MmxTransposeIndex[vp6MmxZigzag[i + 1]]] = (unsigned char)(i + 1);
		q->inverse[vp6MmxTransposeIndex[vp6MmxZigzag[i + 2]]] = (unsigned char)(i + 2);
		q->inverse[vp6MmxTransposeIndex[vp6MmxZigzag[i + 3]]] = (unsigned char)(i + 3);
	}
}

// RVA 0x001C47C0: the same inversion through the WMT transpose index.
extern "C" void __cdecl VP6_BuildQuantIndex_ForWMT(Quantizer *q)
{
	q->index = vp6WmtTransposeIndex;
	for (int i = 0; i < 64; i += 4)
	{
		q->inverse[vp6WmtTransposeIndex[vp6MmxZigzag[i]]] = (unsigned char)i;
		q->inverse[vp6WmtTransposeIndex[vp6MmxZigzag[i + 1]]] = (unsigned char)(i + 1);
		q->inverse[vp6WmtTransposeIndex[vp6MmxZigzag[i + 2]]] = (unsigned char)(i + 2);
		q->inverse[vp6WmtTransposeIndex[vp6MmxZigzag[i + 3]]] = (unsigned char)(i + 3);
	}
}
