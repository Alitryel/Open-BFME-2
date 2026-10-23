// cl: /DNDEBUG /MD
//
// Global operator new/delete route through the game's pluggable memory-manager
// function pointers (indirect __cdecl calls). The allocation pointer takes a
// tag alongside the memory class - the C allocator wrapper at 0x000307F0 passes
// its caller's tag through the same slot - and new/delete pass a null tag.
// Memory class 1 is scalar, 2 is array; class 3 belongs to malloc and free.

typedef void(__cdecl *GameFreeFunction)(void *, int);
typedef void *(__cdecl *GameAllocateFunction)(unsigned int, int, const void *);

// Six matched wrappers independently locate these runtime binding slots.
// Both four-byte pointers start at zero in BFME2; their types follow the
// existing wrapper call contracts rather than an allocator implementation.
extern "C" {
GameFreeFunction __gameMemFreePtr = 0;             // VA 0x00DE03FC
GameAllocateFunction __gameMemAllocatePtr = 0;    // VA 0x00DE0404
}

void __cdecl operator delete(void *block)
{
	if (block)
		__gameMemFreePtr(block, 1);
}

inline void __cdecl operator delete[](void *block)
{
	if (block)
		__gameMemFreePtr(block, 2);
}

void *__cdecl operator new(unsigned int size)
{
	return __gameMemAllocatePtr(size, 1, 0);
}

inline void *__cdecl operator new[](unsigned int size)
{
	return __gameMemAllocatePtr(size, 2, 0);
}

#pragma inline_depth(0)
// ?bfmeEmitMemOps@@YAXPAXI@Z present-unmatched
void bfmeEmitMemOps(void *p, unsigned int s)
{
	operator delete[](p);
	operator new[](s);
}
#pragma inline_depth()
