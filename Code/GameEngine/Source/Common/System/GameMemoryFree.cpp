// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// The retail memory-pool build replaces the C allocator entry points. Its
// free wrapper forwards the block with memory class 3 to the game allocator.

typedef void (__cdecl *GameFreeFunction)(void *, int);
extern "C" GameFreeFunction __gameMemFreePtr;

extern "C" void __cdecl free(void *block)
{
	__gameMemFreePtr(block, 3);
}

// STLport-side callers name this free _STL::free (cdecl, one pointer), pinned to 0x00030830; bind that spelling here.
#pragma comment(linker, "/alternatename:?free@_STL@@YAXPAX@Z=_free")

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:__free=_free")

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?freeWayPointVecStorage@@YAXPAX@Z=_free")

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?free@@YAXPAX@Z=_free")
