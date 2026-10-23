// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001b57d0.md and 001b8fb0.md plus
// retail only. No decoder source was consulted.
//
// Library-wide one-time setup (retail 0x001B57D0 VP6_VPInitLibrary) and the
// CPU specific selection of the quantizer index builder (retail 0x001B8FB0
// VP6_DMachineSpecificConfig).

int __cdecl Get_RDTSC_CPU_Speed(void);                       // 0x001B8E90 VP6_GetProcessorFrequency
extern "C" void __cdecl GetProcessorFlags(int *mmx, int *xmm, int *wmt); // 0x001C4390
extern "C" void __cdecl InitPostProcessing(void *, void *, void *, int); // 0x001B6520 InitPostProcessing
extern "C" void __cdecl VP6_BuildQuantIndex_ForWMT(void *quantizer); // 0x001C47C0
extern "C" void __cdecl VP6_BuildQuantIndex_ForMMX(void *quantizer); // 0x001C4740
extern "C" void __cdecl VP6_BuildQuantIndex_Generic(void *quantizer); // 0x001B7070
extern "C" void __cdecl InitVPUtil(void);                    // 0x001B8040

struct BfmeS1040;
typedef void (__cdecl *QuantIndexBuilder)(BfmeS1040 *);
// The quant index builder pointer (VA 0x00E22F74, zero-filled .bss);
// VP6_DMachineSpecificConfig picks the WMT, MMX or generic builder.
QuantIndexBuilder g_bfmeQuantIndexBuilder;
// Retail stores the hook twice on the generic path; volatile stores keep both.
#define QUANT_INDEX_HOOK (*(QuantIndexBuilder volatile *)&g_bfmeQuantIndexBuilder)
extern int g_bfmeSharedJX;                                   // 0x00E23300 processor frequency

// Retail 0x00BD8560: identity index 0..63 followed by the zig-zag inverse
// map, sized to the 0x200-byte gap before the next known global there.
int g_bfmeIdentityIndex[128] = {
	0, 1, 2, 3, 4, 5, 6, 7,
	8, 9, 10, 11, 12, 13, 14, 15,
	16, 17, 18, 19, 20, 21, 22, 23,
	24, 25, 26, 27, 28, 29, 30, 31,
	32, 33, 34, 35, 36, 37, 38, 39,
	40, 41, 42, 43, 44, 45, 46, 47,
	48, 49, 50, 51, 52, 53, 54, 55,
	56, 57, 58, 59, 60, 61, 62, 63,
	0, 1, 5, 6, 14, 15, 27, 28,
	2, 4, 7, 13, 16, 26, 29, 42,
	3, 8, 12, 17, 25, 30, 41, 43,
	9, 11, 18, 24, 31, 40, 44, 53,
	10, 19, 23, 32, 39, 45, 52, 54,
	20, 22, 33, 38, 46, 51, 55, 60,
	21, 34, 37, 47, 50, 56, 59, 61,
	35, 36, 48, 49, 57, 58, 62, 63,
};

// The library initializer fills the 64 native DC scale entries.
int g_00DFD950[64];
extern const unsigned short g_bfmeApplyTableC[64];
static int *const g_dcScale = g_00DFD950;
static const short *const g_dcQuant = (const short *)g_bfmeApplyTableC;
static const short *const g_dcQuantEnd = (const short *)(g_bfmeApplyTableC + 64);

// RVA 0x001B8FB0
extern "C" void __cdecl VP6_DMachineSpecificConfig(void)
{
	int xmm;
	int mmx;
	int wmt;

	GetProcessorFlags(&mmx, &xmm, &wmt);

	if (wmt != 0)
	{
		QUANT_INDEX_HOOK = (QuantIndexBuilder)&VP6_BuildQuantIndex_ForWMT;
		return;
	}

	if (mmx != 0)
	{
		QUANT_INDEX_HOOK = (QuantIndexBuilder)&VP6_BuildQuantIndex_ForMMX;
	}
	else
	{
		QUANT_INDEX_HOOK = (QuantIndexBuilder)&VP6_BuildQuantIndex_ForMMX;
		QUANT_INDEX_HOOK = (QuantIndexBuilder)&VP6_BuildQuantIndex_Generic;
	}
}

// RVA 0x001B57D0
extern "C" void __cdecl VP6_VPInitLibrary(void)
{
	g_bfmeSharedJX = Get_RDTSC_CPU_Speed();
	VP6_DMachineSpecificConfig();

	int *dst = g_dcScale;
	for (const short *src = g_dcQuant; (int)src < (int)g_dcQuantEnd; ++src, ++dst)
		*dst = *src / 2 + 2;

	InitPostProcessing(g_dcScale, g_dcScale, g_dcScale, 7);
	InitVPUtil();
}
