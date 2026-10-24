// Clean room: reverse/vp6_cleanroom/specs/001b63c0.md 001b6400.md plus retail
// only. No decoder source was consulted.
// EA duck_mem shim allocators, owned by DuckMemAlloc.cpp.
#ifndef VP6_DUCKMEM_H
#define VP6_DUCKMEM_H

extern "C" void *__cdecl duck_malloc(unsigned int size);	// 0x001B63C0

// 0x001B6400: the tagged overload; the memory tag is ignored.
void *__cdecl duck_malloc(unsigned int size, int tag);

#endif
