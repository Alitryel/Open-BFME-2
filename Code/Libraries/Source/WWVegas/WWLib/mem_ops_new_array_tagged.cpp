// cl: /DNDEBUG /MD
//
// Tagged array operator new, retail 0x006C4C30, 22 bytes.
// Same game-allocator table as mem_ops.cpp, memory class 2, with the
// extra argument forwarded as the allocation tag.

typedef void *(__cdecl *GameAllocateFunction)(unsigned int, int, const void *);
typedef void(__cdecl *GameFreeFunction)(void *, int);
extern "C" GameAllocateFunction __gameMemAllocatePtr;
extern "C" GameFreeFunction __gameMemFreePtr;

// The scalar twin, retail 0x006C4C10 (22 bytes): memory class 1.
void *__cdecl operator new(unsigned int size, unsigned int extra)
{
	unsigned tag = extra;
	unsigned bytes = size;
	return __gameMemAllocatePtr(bytes, 1, (const void *)tag);
}

void *__cdecl operator new[](unsigned int size, unsigned int extra)
{
	unsigned tag = extra;
	unsigned bytes = size;
	return __gameMemAllocatePtr(bytes, 2, (const void *)tag);
}

// The matching tagged deletes, retail 0x006C4C50 / 0x006C4C60 (14 bytes
// each): the tag is dropped and the block goes to the game's free pointer
// with memory class 1 / 2, as a tail call that reuses the tag's slot.
void __cdecl operator delete(void *block, unsigned int)
{
	__gameMemFreePtr(block, 1);
}

void __cdecl operator delete[](void *block, unsigned int)
{
	__gameMemFreePtr(block, 2);
}
