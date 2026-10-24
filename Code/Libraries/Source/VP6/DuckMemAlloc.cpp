// cl: /O2 /G6 /Ob1 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001b63c0.md 001b6400.md 001b64d0.md
// plus retail only. No decoder source was consulted.
// EA duck_mem shim: core allocate (through the installed allocator object at
// 0x00DFDA54, else the engine allocator), its tagged overload and strcmp.
#include "DuckMem.h"

extern int G00DFDA54;

class DuckAllocatorObject
{
public:
	virtual void *allocate(unsigned int size, void *descriptor);
};

namespace _STL
{
void *vectorSmallAllocate(unsigned int bytes, unsigned int alignment); // 0x004307F0 engine allocate
}

// RVA 0x001B63C0
extern "C" void *__cdecl duck_malloc(unsigned int size)
{
	DuckAllocatorObject *allocator = *(DuckAllocatorObject **)&G00DFDA54;
	if (allocator)
	{
		unsigned int descriptor[3] = { 0, 0, 0 };
		return allocator->allocate(size, descriptor);
	}
	return _STL::vectorSmallAllocate(size, 0);
}

// RVA 0x001B6400: /Ob1 keeps this call to the core out of line, as in retail.
void *__cdecl duck_malloc(unsigned int size, int)
{
	return duck_malloc(size);
}

extern "C" int __cdecl strcmp(const char *, const char *);
#pragma intrinsic(strcmp)

// RVA 0x001B64D0
extern "C" int __cdecl duck_strcmp(const char *first, const char *second)
{
	return strcmp(first, second);
}
