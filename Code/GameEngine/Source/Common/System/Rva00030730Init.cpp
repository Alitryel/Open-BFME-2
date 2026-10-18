// cl: /MD
// ?InitFunctionPointers@MemoryPool@@YAXXZ @0x00030730 190B resolves the
// MemoryPool exports from the running module into the engine's pointer slots.
// Identity: WorldBuilder's own debug info names this body
// MemoryPool::InitFunctionPointers in its memorypool_allocator.cpp (WB
// 0x6FD840, 492B debug body, 13 export-string matches; the debug asserts
// compile away under NDEBUG, leaving this 190B extent).
// Evidence: leaf lane caller at 0x0002FFA0; memory_pool.cpp names retail MemoryPool and 0x00030730 resolver; 13 GetProcAddress stores into 0x00DE03E0..0x00DE0410 with gameMemAllocatePtr 0x00DE0404 gameMemFreePtr 0x00DE03FC g_Va00DE03E8 0x00DE03E8 rowed
extern "C" __declspec(dllimport) void *__stdcall GetModuleHandleA(const char *name);
extern "C" __declspec(dllimport) void *__stdcall GetProcAddress(void *hMod, const char *name);
typedef void (__cdecl *GameFreeFunction)(void *, int);
typedef void *(__cdecl *GameAllocateFunction)(unsigned int, int, const void *);
extern "C" GameFreeFunction __gameMemFreePtr;
extern "C" GameAllocateFunction __gameMemAllocatePtr;
extern void (__stdcall *g_Va00DE03E8)(unsigned int, unsigned int);
extern void *g_00DE0410;
extern void *g_00DE040C;
extern void *g_00DE0408;
void * g_00DE0400;	// retail RVA 0x009E0400 (.bss), defined here
extern void *g_00DE03F8;
extern void *g_00DE03F4;
void * g_00DE03F0;	// retail RVA 0x009E03F0 (.bss), defined here
extern void *g_00DE03EC;
extern void *g_00DE03E4;
void * g_00DE03E0;	// retail RVA 0x009E03E0 (.bss), defined here
namespace MemoryPool
{
void InitFunctionPointers()
{
	void *hMod = GetModuleHandleA(0);
	g_00DE0410 = GetProcAddress(hMod, "?_Init@MemoryPool@@YAXXZ");
	g_00DE040C = GetProcAddress(hMod, "?_Exit@MemoryPool@@YAXXZ");
	g_00DE0408 = GetProcAddress(hMod, "?_DumpFragmentation@MemoryPool@@YAXPAU_iobuf@@_NPBD@Z");
	__gameMemAllocatePtr = (GameAllocateFunction)GetProcAddress(hMod, "?_Allocate@MemoryPool@@YAPAXIW4AllocType@1@I@Z");
	g_00DE0400 = GetProcAddress(hMod, "?_Reallocate@MemoryPool@@YAPAXPAXIW4AllocType@1@I@Z");
	__gameMemFreePtr = (GameFreeFunction)GetProcAddress(hMod, "?_Free@MemoryPool@@YAXPAXW4AllocType@1@@Z");
	g_00DE03F8 = GetProcAddress(hMod, "?_IsValidBlock@MemoryPool@@YA_NPAXI@Z");
	g_00DE03F4 = GetProcAddress(hMod, "?_GetBlockSize@MemoryPool@@YAIPAXI@Z");
	g_00DE03F0 = GetProcAddress(hMod, "?_GetBlockHeap@MemoryPool@@YAIPAX@Z");
	g_00DE03EC = GetProcAddress(hMod, "?_VerifyIntegrity@MemoryPool@@YAXXZ");
	g_Va00DE03E8 = (void (__stdcall *)(unsigned int, unsigned int))GetProcAddress(hMod, "?_AddHeap@MemoryPool@@YAXII@Z");
	g_00DE03E4 = GetProcAddress(hMod, "?_GetHeapAllocator@MemoryPool@@YAPAVGeneralAllocator@Allocator@EA@@I@Z");
	g_00DE03E0 = GetProcAddress(hMod, "?_GetHeapAllocatorByIndex@MemoryPool@@YAPAVGeneralAllocator@Allocator@EA@@I@Z");
}
}
