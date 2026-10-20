// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Target evidence: Ghidra boundary 0x004677FD, 34 bytes. Retail allocates
// 0x10 bytes through 0x000307F0, constructs the payload at +8 through the
// independently matched helper at 0x00467763, then returns the allocation.
// The caller at 0x00467D8E writes the two list links at +0 and +4. The
// address-derived name preserves uncertainty: an existing list<T*> pin at this
// address conflicts with the payload helper's pair-copy behavior.
#include <memory>
#include <list>

void __cdecl Rva00467763Construct(void *dest, const void *source);

void *__stdcall Rva004677FDCreateNode(const void *src)
{
	char *block = _STL::allocator<char>::allocate(0x10, 0);
	Rva00467763Construct(block + 8, src);
	return block;
}
