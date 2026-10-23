// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001c1750.md plus retail only.
// No decoder source was consulted.
//
// PostProcMachineSpecificConfig (retail 0x001C1750, 881 bytes): cdecl, the
// single stack argument is unused. Fills the post-processing function-pointer
// dispatch table (26 slots plus one outlier) for the WMT, MMX or generic
// tier. Every slot target and its order follow the spec.
//
// Installs per-CPU-tier function pointers into the BFME video/image codec
// dispatch table: 26 contiguous slots plus one standalone outlier slot.
// Probes the tier via GetProcessorFlags (0x009B3A90, parked partial --
// declared extern and pinned since a pin does not require the callee to be
// converted): the SSE tier (top flag set) expands the loop-filter limit
// table for the SIMD filters (FillLoopFilterLimitValues_MMX) and installs the
// full SIMD set; the MMX tier (basic flag set) does the same expansion and
// installs the MMX-only set (mostly shared with the SSE tier); otherwise the
// generic scalar/table-driven set installs directly with no expansion.
// Sibling of FilterVert_MMX, HorizontalLine_1_2_Scale_MMX, the *FastDeInterlace family and
// FilteringC.cpp.

extern "C" void __cdecl GetProcessorFlags(int *pTierA, int *pTierB, int *pTierC);

// VP6 clean-room bodies (Code/Libraries/Source/VP6/), declared with the
// extern "C" signatures those units define.
struct POSTPROC_INSTANCE;
extern "C" void __cdecl FillLoopFilterLimitValues_MMX(void);
extern "C" int *__cdecl SetupDeblockValueArray_ForMMX(POSTPROC_INSTANCE *, int);
extern "C" int *__cdecl SetupBoundingValueArray_ForMMX(POSTPROC_INSTANCE *, int);
extern "C" void __cdecl LastVerticalBand_1_2_Scale_MMX(unsigned char *, unsigned int, unsigned int);

// Landed siblings, declared with their real signatures so the mangled name
// matches their existing row.
extern "C" void __cdecl FilterVert_MMX(void *, void *, int, const void *);
extern "C" void __cdecl HorizontalLine_1_2_Scale_MMX(const void *, int, void *);
extern "C" void __cdecl HorizontalLine_1_2_Scale_C(const void *, int, void *, int);
extern "C" void __cdecl HorizontalLine_3_5_Scale_MMX(const void *, int, void *);
extern "C" void __cdecl HorizontalLine_4_5_Scale_MMX(const void *, int, void *);
extern "C" void __cdecl VerticalBand_1_2_Scale_MMX(void *, int, int);
extern "C" void __cdecl VerticalBand_3_5_Scale_MMX(void *, unsigned int, unsigned int);
extern "C" void __cdecl LastVerticalBand_3_5_Scale_MMX(void *, int, int);
extern "C" void __cdecl VerticalBand_4_5_Scale_MMX(void *, unsigned int, unsigned int);
extern "C" void __cdecl LastVerticalBand_4_5_Scale_MMX(void *, int, int);
extern "C" void __cdecl WmtFastDeInterlace(void *, void *, unsigned int, int, int);
extern "C" void __cdecl MmxFastDeInterlace(void *, void *, unsigned int, int, int);
extern "C" void __cdecl CFastDeInterlace(void *, void *, unsigned int, int, int);
extern "C" void __cdecl FilterHoriz_Generic(void *, unsigned char *, int, const int *);
extern "C" void __cdecl FilterVert_Generic(void *, unsigned char *, int, const int *);
extern "C" int * __cdecl SetupBoundingValueArray_Generic(POSTPROC_INSTANCE *, int);
extern "C" int * __cdecl SetupDeblockValueArray_Generic(POSTPROC_INSTANCE *, int);
extern "C" void __cdecl FilterHoriz_Simple_C(void *, unsigned char *, int, const int *);
extern "C" void __cdecl FilterVert_Simple_C(void *, unsigned char *, int, const int *);
extern "C" void __cdecl FilteringHoriz_8_C(unsigned int, unsigned char *, int);
extern "C" void __cdecl FilteringVert_8_C(unsigned int, unsigned char *, int);
extern "C" void __cdecl FilteringHoriz_12_C(unsigned int, unsigned char *, int);
extern "C" void __cdecl FilteringVert_12_C(unsigned int, unsigned char *, int);

// Unconverted gen-dump callees that already carry a functions.csv row (the
// row is the candidate; no new pin needed).
extern "C" void __cdecl FilterHoriz_MMX(void *, unsigned char *, int, void *);
extern "C" void __cdecl DeringBlockWeak_WMT(void *, void *, void *, int, int, int *);
extern "C" void __cdecl DeringBlockStrong_WMT(void *, void *, void *, int, int, int *);
extern "C" void __cdecl DeblockLoopFilteredBand_WMT(void);	// rowed C body (was address-named d_009bebb0)
extern "C" void __cdecl DeblockNonFilteredBand_WMT(void);	// rowed C body (was address-named d_009bfa40)
extern "C" void __cdecl DeblockNonFilteredBandNewFilter_MMX(void);	// rowed C body (was address-named d_009b9700)
struct Rva009C2170Ctx;
extern "C" void __cdecl FilterVert_Simple_MMX(Rva009C2170Ctx *, unsigned char *, int, const void *);
extern "C" void __cdecl FilterHoriz_Simple_MMX(Rva009C2170Ctx *, unsigned char *, int, const void *);
extern "C" void __cdecl FilteringHoriz_8_MMX(unsigned int, unsigned char *, int);
extern "C" void __cdecl FilteringHoriz_12_MMX(unsigned int, unsigned char *, int);
extern "C" void __cdecl FilteringVert_8_MMX(unsigned int, unsigned char *, int);
extern "C" void __cdecl FilteringVert_12_MMX(unsigned int, unsigned char *, int);
extern "C" void __cdecl ClampLevels_wmt(void *, int, int, int, int);
extern "C" void __cdecl PlaneAddNoise_wmt(void);	// rowed C body (was address-named d_009c0a30)
extern "C" void __cdecl DeringBlockWeak_MMX(void *, void *, void *, int, int, int *);
extern "C" void __cdecl DeringBlockStrong_MMX(void *, void *, void *, int, int, int *);
extern "C" void __cdecl DeblockNonFilteredBand_MMX(void);	// rowed C body (was address-named d_009b8130)
extern "C" void __cdecl PlaneAddNoise_C(unsigned char *, unsigned, unsigned, int, int);	// rowed C body (was address-named d_009a5f50)
extern "C" void __cdecl DeblockLoopFilteredBand_MMX(void);	// rowed C body (was address-named Rva009B6D80)
extern "C" void __cdecl ClampLevels_mmx(void *, int, int, int, int);
extern "C" void __cdecl PlaneAddNoise_mmx(unsigned char *, int, unsigned int, int, int);
extern "C" void __cdecl DeringBlockWeak_C(void *, const unsigned char *, unsigned char *, int, int, const int *);	// rowed C body (was address-named Rva009B18D0)
extern "C" void __cdecl DeringBlockStrong_C(void *, const unsigned char *, unsigned char *, int, int, const int *);	// rowed C body (was address-named Rva009B10E0)
extern "C" void __cdecl DeblockLoopFilteredBand_C(void);	// rowed C body (was address-named Rva009ACF90)
extern "C" void __cdecl DeblockNonFilteredBand_C(void);	// rowed C body (was address-named Rva009ADD80)
extern "C" void __cdecl DeblockNonFilteredBandNewFilter_C(void);	// rowed C body (was address-named Rva009AE6A0)
extern "C" void __cdecl VerticalBand_1_2_Scale_C(unsigned char *, int, unsigned int);
extern "C" void __cdecl LastVerticalBand_1_2_Scale_C(unsigned char *, int, unsigned int);
extern "C" void __cdecl HorizontalLine_3_5_Scale_C(const void *, int, void *);
extern "C" void __cdecl VerticalBand_3_5_Scale_C(unsigned char *, int, unsigned int);
extern "C" void __cdecl LastVerticalBand_3_5_Scale_C(unsigned char *, int, unsigned int);
extern "C" void __cdecl HorizontalLine_4_5_Scale_C(void);	// rowed C body (was address-named Rva009A91D0)
extern "C" void __cdecl VerticalBand_4_5_Scale_C(unsigned char *, int, unsigned int);
extern "C" void __cdecl LastVerticalBand_4_5_Scale_C(unsigned char *, int, unsigned int);
extern "C" void __cdecl ClampLevels_C(void *, int, int, int, int);

typedef void (__cdecl *BfmeDispatchFn)();

struct BfmeCodecDispatchTable
{
	BfmeDispatchFn slot[26];
};

// Shared by the native post-filter dispatcher: table base VA 0x00E22F7C.
BfmeCodecDispatchTable g_bfmeCodecDispatch;
// The outlier slot just ahead of the table (VA 0x00E22F78): the 4/5
// horizontal scaler, read by AnyRatio_2D_Scale and Scale_4_5_2D.
BfmeDispatchFn g_bfmeCodecDispatchOutlier;

extern "C" void __cdecl PostProcMachineSpecificConfig(int version)
{
	int tierA, tierB, tierC;
	GetProcessorFlags(&tierA, &tierB, &tierC);
	if (tierC)
	{
		FillLoopFilterLimitValues_MMX();
		g_bfmeCodecDispatch.slot[15] = (BfmeDispatchFn)&FilterHoriz_MMX;
		g_bfmeCodecDispatch.slot[23] = (BfmeDispatchFn)&FilterVert_MMX;
		g_bfmeCodecDispatch.slot[2] = (BfmeDispatchFn)&SetupBoundingValueArray_ForMMX;
		g_bfmeCodecDispatch.slot[1] = (BfmeDispatchFn)&SetupDeblockValueArray_ForMMX;
		g_bfmeCodecDispatch.slot[16] = (BfmeDispatchFn)&DeringBlockWeak_WMT;
		g_bfmeCodecDispatch.slot[24] = (BfmeDispatchFn)&DeringBlockStrong_WMT;
		g_bfmeCodecDispatch.slot[10] = (BfmeDispatchFn)&DeblockLoopFilteredBand_WMT;
		g_bfmeCodecDispatch.slot[13] = (BfmeDispatchFn)&DeblockNonFilteredBand_WMT;
		g_bfmeCodecDispatch.slot[21] = (BfmeDispatchFn)&DeblockNonFilteredBandNewFilter_MMX;
		g_bfmeCodecDispatch.slot[9] = (BfmeDispatchFn)&FilterHoriz_Simple_MMX;
		g_bfmeCodecDispatch.slot[25] = (BfmeDispatchFn)&FilterVert_Simple_MMX;
		g_bfmeCodecDispatch.slot[8] = (BfmeDispatchFn)&HorizontalLine_1_2_Scale_MMX;
		g_bfmeCodecDispatch.slot[20] = (BfmeDispatchFn)&HorizontalLine_3_5_Scale_MMX;
		g_bfmeCodecDispatchOutlier = (BfmeDispatchFn)&HorizontalLine_4_5_Scale_MMX;
		g_bfmeCodecDispatch.slot[4] = (BfmeDispatchFn)&VerticalBand_1_2_Scale_MMX;
		g_bfmeCodecDispatch.slot[17] = (BfmeDispatchFn)&LastVerticalBand_1_2_Scale_MMX;
		g_bfmeCodecDispatch.slot[18] = (BfmeDispatchFn)&VerticalBand_3_5_Scale_MMX;
		g_bfmeCodecDispatch.slot[12] = (BfmeDispatchFn)&LastVerticalBand_3_5_Scale_MMX;
		g_bfmeCodecDispatch.slot[7] = (BfmeDispatchFn)&VerticalBand_4_5_Scale_MMX;
		g_bfmeCodecDispatch.slot[6] = (BfmeDispatchFn)&LastVerticalBand_4_5_Scale_MMX;
		g_bfmeCodecDispatch.slot[22] = (BfmeDispatchFn)&FilteringHoriz_8_MMX;
		g_bfmeCodecDispatch.slot[5] = (BfmeDispatchFn)&FilteringVert_8_MMX;
		g_bfmeCodecDispatch.slot[11] = (BfmeDispatchFn)&FilteringHoriz_12_MMX;
		g_bfmeCodecDispatch.slot[14] = (BfmeDispatchFn)&FilteringVert_12_MMX;
		g_bfmeCodecDispatch.slot[3] = (BfmeDispatchFn)&WmtFastDeInterlace;
		g_bfmeCodecDispatch.slot[19] = (BfmeDispatchFn)&ClampLevels_wmt;
		g_bfmeCodecDispatch.slot[0] = (BfmeDispatchFn)&PlaneAddNoise_wmt;
		return;
	}
	if (tierA)
	{
		FillLoopFilterLimitValues_MMX();
		g_bfmeCodecDispatch.slot[15] = (BfmeDispatchFn)&FilterHoriz_MMX;
		g_bfmeCodecDispatch.slot[23] = (BfmeDispatchFn)&FilterVert_MMX;
		g_bfmeCodecDispatch.slot[2] = (BfmeDispatchFn)&SetupBoundingValueArray_ForMMX;
		g_bfmeCodecDispatch.slot[1] = (BfmeDispatchFn)&SetupDeblockValueArray_ForMMX;
		g_bfmeCodecDispatch.slot[16] = (BfmeDispatchFn)&DeringBlockWeak_MMX;
		g_bfmeCodecDispatch.slot[24] = (BfmeDispatchFn)&DeringBlockStrong_MMX;
		g_bfmeCodecDispatch.slot[10] = (BfmeDispatchFn)&DeblockLoopFilteredBand_MMX;
		g_bfmeCodecDispatch.slot[13] = (BfmeDispatchFn)&DeblockNonFilteredBand_MMX;
		g_bfmeCodecDispatch.slot[21] = (BfmeDispatchFn)&DeblockNonFilteredBandNewFilter_MMX;
		g_bfmeCodecDispatch.slot[9] = (BfmeDispatchFn)&FilterHoriz_Simple_MMX;
		g_bfmeCodecDispatch.slot[25] = (BfmeDispatchFn)&FilterVert_Simple_MMX;
		g_bfmeCodecDispatch.slot[8] = (BfmeDispatchFn)&HorizontalLine_1_2_Scale_MMX;
		g_bfmeCodecDispatch.slot[20] = (BfmeDispatchFn)&HorizontalLine_3_5_Scale_MMX;
		g_bfmeCodecDispatchOutlier = (BfmeDispatchFn)&HorizontalLine_4_5_Scale_MMX;
		g_bfmeCodecDispatch.slot[4] = (BfmeDispatchFn)&VerticalBand_1_2_Scale_MMX;
		g_bfmeCodecDispatch.slot[17] = (BfmeDispatchFn)&LastVerticalBand_1_2_Scale_MMX;
		g_bfmeCodecDispatch.slot[18] = (BfmeDispatchFn)&VerticalBand_3_5_Scale_MMX;
		g_bfmeCodecDispatch.slot[12] = (BfmeDispatchFn)&LastVerticalBand_3_5_Scale_MMX;
		g_bfmeCodecDispatch.slot[7] = (BfmeDispatchFn)&VerticalBand_4_5_Scale_MMX;
		g_bfmeCodecDispatch.slot[6] = (BfmeDispatchFn)&LastVerticalBand_4_5_Scale_MMX;
		g_bfmeCodecDispatch.slot[22] = (BfmeDispatchFn)&FilteringHoriz_8_MMX;
		g_bfmeCodecDispatch.slot[5] = (BfmeDispatchFn)&FilteringVert_8_MMX;
		g_bfmeCodecDispatch.slot[11] = (BfmeDispatchFn)&FilteringHoriz_12_MMX;
		g_bfmeCodecDispatch.slot[14] = (BfmeDispatchFn)&FilteringVert_12_MMX;
		g_bfmeCodecDispatch.slot[3] = (BfmeDispatchFn)&MmxFastDeInterlace;
		g_bfmeCodecDispatch.slot[19] = (BfmeDispatchFn)&ClampLevels_mmx;
		g_bfmeCodecDispatch.slot[0] = (BfmeDispatchFn)&PlaneAddNoise_mmx;
		return;
	}
	g_bfmeCodecDispatch.slot[15] = (BfmeDispatchFn)&FilterHoriz_Generic;
	g_bfmeCodecDispatch.slot[23] = (BfmeDispatchFn)&FilterVert_Generic;
	g_bfmeCodecDispatch.slot[2] = (BfmeDispatchFn)&SetupBoundingValueArray_Generic;
	g_bfmeCodecDispatch.slot[1] = (BfmeDispatchFn)&SetupDeblockValueArray_Generic;
	g_bfmeCodecDispatch.slot[16] = (BfmeDispatchFn)&DeringBlockWeak_C;
	g_bfmeCodecDispatch.slot[24] = (BfmeDispatchFn)&DeringBlockStrong_C;
	g_bfmeCodecDispatch.slot[10] = (BfmeDispatchFn)&DeblockLoopFilteredBand_C;
	g_bfmeCodecDispatch.slot[13] = (BfmeDispatchFn)&DeblockNonFilteredBand_C;
	g_bfmeCodecDispatch.slot[21] = (BfmeDispatchFn)&DeblockNonFilteredBandNewFilter_C;
	g_bfmeCodecDispatch.slot[9] = (BfmeDispatchFn)&FilterHoriz_Simple_C;
	g_bfmeCodecDispatch.slot[25] = (BfmeDispatchFn)&FilterVert_Simple_C;
	g_bfmeCodecDispatch.slot[8] = (BfmeDispatchFn)&HorizontalLine_1_2_Scale_C;
	g_bfmeCodecDispatch.slot[4] = (BfmeDispatchFn)&VerticalBand_1_2_Scale_C;
	g_bfmeCodecDispatch.slot[17] = (BfmeDispatchFn)&LastVerticalBand_1_2_Scale_C;
	g_bfmeCodecDispatch.slot[20] = (BfmeDispatchFn)&HorizontalLine_3_5_Scale_C;
	g_bfmeCodecDispatch.slot[18] = (BfmeDispatchFn)&VerticalBand_3_5_Scale_C;
	g_bfmeCodecDispatch.slot[12] = (BfmeDispatchFn)&LastVerticalBand_3_5_Scale_C;
	g_bfmeCodecDispatchOutlier = (BfmeDispatchFn)&HorizontalLine_4_5_Scale_C;
	g_bfmeCodecDispatch.slot[7] = (BfmeDispatchFn)&VerticalBand_4_5_Scale_C;
	g_bfmeCodecDispatch.slot[6] = (BfmeDispatchFn)&LastVerticalBand_4_5_Scale_C;
	g_bfmeCodecDispatch.slot[22] = (BfmeDispatchFn)&FilteringHoriz_8_C;
	g_bfmeCodecDispatch.slot[5] = (BfmeDispatchFn)&FilteringVert_8_C;
	g_bfmeCodecDispatch.slot[11] = (BfmeDispatchFn)&FilteringHoriz_12_C;
	g_bfmeCodecDispatch.slot[14] = (BfmeDispatchFn)&FilteringVert_12_C;
	g_bfmeCodecDispatch.slot[3] = (BfmeDispatchFn)&CFastDeInterlace;
	g_bfmeCodecDispatch.slot[19] = (BfmeDispatchFn)&ClampLevels_C;
	g_bfmeCodecDispatch.slot[0] = (BfmeDispatchFn)&PlaneAddNoise_C;
}
