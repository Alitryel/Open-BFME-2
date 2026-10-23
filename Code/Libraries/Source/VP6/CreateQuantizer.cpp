// cl: /Ob0 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001b7810.md, 001b7860.md and
// 001b7990.md plus retail only. No decoder source was consulted.
//
// Quantizer construction (retail 0x001B7810..0x001B79D8):
//   DeleteQuantizerBuffers   0x001B7810  67 bytes, static, ESI = quantizer
//   AllocateQuantizerBuffers 0x001B7860 206 bytes, static, EAX = quantizer
//   VP6_CreateQuantizer      0x001B7990  73 bytes, cdecl
// MSVC gives both static helpers their private register conventions. Retail
// expands the buffer release inline at the start of the allocator and on its
// first failure path, so it is spelled as a macro there; the second failure
// path calls the out-of-line helper.

void bfmeFreeOneJT(void *what); // 0x001B6410 duck_free

class Rva001B6400Allocation // 0x001B6400 duck_malloc tagged wrapper
{
public:
	enum AllocationTag { Zero = 0 };
	static void *operator new(unsigned int size, AllocationTag tag);
};

struct QUANTIZER
{
	unsigned char m_pad0[0x180];
	void *yDequant;			// +0x180 aligned Y dequantiser
	void *uvDequant;		// +0x184 aligned UV dequantiser
	void *yDequantRaw;		// +0x188 raw Y allocation
	void *uvDequantRaw;		// +0x18C raw UV allocation
	unsigned char m_pad190[0x990 - 0x190];
};

#define DELETE_QUANTIZER_BUFFERS(q)			\
	if ((q)->yDequantRaw)					\
		bfmeFreeOneJT((q)->yDequantRaw);	\
	(q)->yDequantRaw = 0;					\
	(q)->yDequant = 0;						\
	if ((q)->uvDequantRaw)					\
		bfmeFreeOneJT((q)->uvDequantRaw);	\
	(q)->uvDequantRaw = 0;					\
	(q)->uvDequant = 0

// RVA 0x001B7810
static void DeleteQuantizerBuffers(QUANTIZER *pbi)
{
	DELETE_QUANTIZER_BUFFERS(pbi);
}

// RVA 0x001B7860
static int AllocateQuantizerBuffers(QUANTIZER *pbi)
{
	DELETE_QUANTIZER_BUFFERS(pbi);

	pbi->yDequantRaw = Rva001B6400Allocation::operator new(0xA0, Rva001B6400Allocation::Zero);
	if (!pbi->yDequantRaw)
	{
		DELETE_QUANTIZER_BUFFERS(pbi);
		return 0;
	}
	pbi->yDequant = (void *)(((unsigned int)pbi->yDequantRaw + 31) & ~31u);

	pbi->uvDequantRaw = Rva001B6400Allocation::operator new(0xA0, Rva001B6400Allocation::Zero);
	if (!pbi->uvDequantRaw)
	{
		DeleteQuantizerBuffers(pbi);
		return 0;
	}
	pbi->uvDequant = (void *)(((unsigned int)pbi->uvDequantRaw + 31) & ~31u);
	return 1;
}

extern "C" void *__cdecl memset(void *dest, int value, unsigned int count);
extern "C" void __cdecl VP6_DeleteQuantizer(void **quantizer);

// RVA 0x001B7990
extern "C" QUANTIZER *__cdecl VP6_CreateQuantizer()
{
	QUANTIZER *result = (QUANTIZER *)Rva001B6400Allocation::operator new(sizeof(QUANTIZER), Rva001B6400Allocation::Zero);
	QUANTIZER *pbi = result;
	if (!result)
		return 0;
	memset(result, 0, sizeof(QUANTIZER));
	if (!AllocateQuantizerBuffers(result))
	{
		VP6_DeleteQuantizer((void **)&pbi);
		result = pbi;
	}
	return result;
}
