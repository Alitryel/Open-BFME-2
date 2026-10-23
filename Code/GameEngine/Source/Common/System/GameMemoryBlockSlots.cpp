// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Two memory-pool slot forwarders after the replaced C free (0x00030830).
// The slots are the MemoryPool exports Rva00030730Init resolves with
// GetProcAddress: VA 0x00DE03F4 is ?_GetBlockSize@MemoryPool@@YAIPAXI@Z and
// VA 0x00DE03EC is ?_VerifyIntegrity@MemoryPool@@YAXXZ. Names stay
// address-derived; the shapes come from the retail bytes.

void * g_00DE03F4;	// retail RVA 0x009E03F4 (.bss), defined here
void * g_00DE03EC;	// retail RVA 0x009E03EC (.bss), defined here

typedef unsigned int (__cdecl *GetBlockSizeFunction)(void *, unsigned int);
typedef void (__cdecl *VerifyIntegrityFunction)(void);

// --- 0x00030860 (19B): a null block has size 0; otherwise tail-jump into
// the block-size slot with the block and the heap word.
unsigned int rva00030860(void *block, unsigned int heap)
{
	if (block == 0)
		return 0;
	return ((GetBlockSizeFunction)g_00DE03F4)(block, heap);
}

// --- 0x00030880 (6B): tail-jump into the integrity-check slot.
void rva00030880()
{
	((VerifyIntegrityFunction)g_00DE03EC)();
}

// --- 0x00031420 (12B): forward a message to OutputDebugStringA. Its address
// is taken at 0x00033D37 (a GeneralAllocator trace-callback store).
extern "C" __declspec(dllimport) void __stdcall OutputDebugStringA(const char *text);

void rva00031420(const char *text)
{
	OutputDebugStringA(text);
}

// --- 0x00030850 (6B): tail-jump into the block-validity slot VA 0x00DE03F8
// (?_IsValidBlock@MemoryPool@@YA_NPAXI@Z), unreferenced.
void * g_00DE03F8;	// retail RVA 0x009E03F8 (.bss), defined here

bool rva00030850(void *block, unsigned int heap)
{
	return ((bool (__cdecl *)(void *, unsigned int))g_00DE03F8)(block, heap);
}

// --- 0x000308F0 (6B): tail-jump into the heap-allocator slot VA 0x00DE03E4
// (?_GetHeapAllocator@MemoryPool@@YAPAVGeneralAllocator@Allocator@EA@@I@Z),
// unreferenced.
namespace EA { namespace Allocator { class GeneralAllocator; } }
void * g_00DE03E4;	// retail RVA 0x009E03E4 (.bss), defined here

EA::Allocator::GeneralAllocator *rva000308F0(unsigned int id)
{
	return ((EA::Allocator::GeneralAllocator *(__cdecl *)(unsigned int))g_00DE03E4)(id);
}
