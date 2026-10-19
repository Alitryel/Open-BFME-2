// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001b68d0.md 001b6890.md 001b6930.md
// 001bff20.md 001bd630.md plus retail only. No decoder source was consulted.
// Post-processor instance (0xC8 bytes): create, delete and per-frame setup.
extern "C" void *__cdecl memset(void *block, int value, unsigned int bytes);
#pragma intrinsic(memset)

struct POSTPROC_INSTANCE;
struct POSTPROC_VERSIONED
{
	int version;                  // 0x00
	unsigned char pad04[8];
	int frameQIndex;              // 0x0C
	unsigned char pad10[8];
	unsigned char *fragmentInfo;  // 0x18
	int fragmentInfoSize;         // 0x1C
	unsigned char codedMask;      // 0x20
	unsigned char pad21[3];
	int *fragmentQIndex;          // 0x24
	unsigned char pad28[8];
	int *boundingValues;          // 0x30
	unsigned char pad34[4];
	int *deblockValues;           // 0x38
	unsigned char pad3C[0x50];
	unsigned int unitFragments;   // 0x8C
	unsigned char pad90[0x34];
	int addNoiseMode;             // 0xC4
};

extern "C" void __cdecl DeletePostProcBuffers(void *instance); // 0x001B65F0
void __cdecl bfmeFreeOneJT(void *block);                // 0x001B6410 duck_free
extern "C" void __cdecl ChangePostProcConfiguration(void *instance, void *config); // 0x001B67E0

class Rva001B6400Allocation
{
public:
	enum AllocationTag { Bucket_GLUE_NOT_IMPLEMENTED = 0 };
	static void *__cdecl operator new(unsigned int bytes, AllocationTag tag); // 0x001B6400 duck_malloc
};

struct Rva009AF490Context;
struct Rva009ACBA0Context;
struct Rva009AF530Context;
struct Rva009ACC40State;
extern "C" int *__cdecl SetupBoundingValueArray_Generic(Rva009AF490Context *, int); // 0x001BFE80
extern "C" int *__cdecl SetupDeblockValueArray_Generic(Rva009ACBA0Context *, int); // 0x001BD590
extern int *g_bfmeFilterLimit;   // 0x00E22CE0 loop-filter limit table pointer
extern int *g_bfmeDeblockLimit;       // 0x00E22CEC deblock limit table pointer
// The deblock and bounding value-array builders are slots 1 (VA 0x00E22F80)
// and 2 (VA 0x00E22F84) of the codec dispatch table at VA 0x00E22F7C that
// PostProcMachineSpecificConfig (PostProcMachineSpecificConfig.cpp) defines
// and fills.
typedef void (__cdecl *BfmeDispatchFn)();
struct BfmeCodecDispatchTable
{
	BfmeDispatchFn slot[26];
};
extern BfmeCodecDispatchTable g_bfmeCodecDispatch;
#define g_slotSetupBoundingValues (*(int *(__cdecl **)(Rva009AF530Context *, int))&g_bfmeCodecDispatch.slot[2])
#define g_slotSetupDeblockValues (*(int (__cdecl **)(Rva009ACC40State *, int))&g_bfmeCodecDispatch.slot[1])

// RVA 0x001B68D0
extern "C" void __cdecl DeletePostProcInstance(POSTPROC_INSTANCE **instance)
{
	if (*instance != 0)
	{
		DeletePostProcBuffers(*instance);
		bfmeFreeOneJT(*instance);
		*instance = 0;
	}
}

// RVA 0x001B6890
extern "C" POSTPROC_INSTANCE *__cdecl CreatePostProcInstance(void *config)
{
	POSTPROC_VERSIONED *instance = (POSTPROC_VERSIONED *)Rva001B6400Allocation::operator new(0xC8, Rva001B6400Allocation::Bucket_GLUE_NOT_IMPLEMENTED);
	POSTPROC_INSTANCE *result = 0;
	if (instance)
	{
		memset(instance, 0, 0xC8);
		ChangePostProcConfiguration(instance, config);
		instance->addNoiseMode = 1;
		result = (POSTPROC_INSTANCE *)instance;
	}
	return result;
}

// RVA 0x001B6930
extern "C" void __cdecl UpdateFragQIndex(POSTPROC_INSTANCE *ppi)
{
	POSTPROC_VERSIONED *p = (POSTPROC_VERSIONED *)ppi;
	unsigned int i = 0;
	int q = p->frameQIndex;
	while (i < p->unitFragments)
	{
		unsigned char info = p->fragmentInfo[p->fragmentInfoSize * i];
		if ((p->codedMask & info) != 0)
			p->fragmentQIndex[i] = q;
		++i;
	}
}

// RVA 0x001BFF20
extern "C" void __cdecl SetupLoopFilter(POSTPROC_INSTANCE *ppi)
{
	POSTPROC_VERSIONED *p = (POSTPROC_VERSIONED *)ppi;
	int limit = g_bfmeFilterLimit[p->frameQIndex];
	if (p->version >= 2)
		p->boundingValues = SetupBoundingValueArray_Generic((Rva009AF490Context *)p, limit);
	else
		p->boundingValues = g_slotSetupBoundingValues((Rva009AF530Context *)p, limit);
}

// RVA 0x001BD630
extern "C" void __cdecl SetupDeblocker(POSTPROC_INSTANCE *ppi)
{
	POSTPROC_VERSIONED *p = (POSTPROC_VERSIONED *)ppi;
	if (p->version >= 2)
	{
		int limit = g_bfmeDeblockLimit[p->frameQIndex];
		p->deblockValues = SetupDeblockValueArray_Generic((Rva009ACBA0Context *)p, limit);
	}
	else
	{
		int limit = g_bfmeDeblockLimit[p->frameQIndex];
		p->deblockValues = (int *)g_slotSetupDeblockValues((Rva009ACC40State *)p, limit);
	}
}
