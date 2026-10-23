// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// 4-byte element with copy ctor only (no dtor): force _Construct on n==1 while
// letting _M_clear collapse to free (trivial destroy), matching retail 0x00532ED9.

#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>
struct Rva005334A4Element {
	unsigned short a;
	unsigned short b;
	Rva005334A4Element(const Rva005334A4Element &source)
		: a(source.a), b(source.b) {}
};
namespace _STL {
template <> inline __declspec(noinline)
void _Construct<Rva005334A4Element, Rva005334A4Element>(
	Rva005334A4Element *destination, const Rva005334A4Element &source)
{
	::new ((void *)destination) Rva005334A4Element(source);
}
}

template void _STL::vector<Rva005334A4Element, _STL::allocator<Rva005334A4Element> >::_M_insert_overflow(
	Rva005334A4Element *, const Rva005334A4Element &, const _STL::__false_type &, unsigned int, bool);
