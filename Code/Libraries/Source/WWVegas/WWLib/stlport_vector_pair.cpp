// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport

#define _STLP_BFME_COPY_TRIVIAL_EXTERN  // call retail's one __copy_trivial (vendor/stlport/stl/_algobase.h)
#include <stl/_alloc.h>
namespace _STL { template <> void __malloc_alloc<0>::deallocate(void *, size_t); }
#include <vector>
// bfme link decl-only begin
namespace _STL { template <> void * __malloc_alloc<0>::allocate(unsigned int); }
// bfme link decl-only end

// Preserve retail's inlined buffer release while using the canonical public allocator.
namespace _STL {
#pragma optimize("gsy", on)
template <> __forceinline void allocator<pair<int, int> >::deallocate(pair<int, int> *p, size_t) const { if (p != 0) free(p); }
#pragma optimize("", on)
}

// Retail's allocation/copy target at 627960 has a neutral row name: its
// application record identity remains unknown. It copies two words per
// element and ignores the receiver. Forward this existing typed caller to
// that owner, preserving its ABI and every bit of the pair representation.
struct Rva00627960Element { unsigned word0, word1; };
class Rva00627960Vector {
public:
    Rva00627960Element *allocateCopy(unsigned,
        const Rva00627960Element *, const Rva00627960Element *);
};
namespace _STL {
template <> template <> __declspec(dllimport) __forceinline
pair<int, int> *vector<pair<int, int> >::_M_allocate_and_copy<const pair<int, int> *>(
    unsigned int n, const pair<int, int> *first, const pair<int, int> *last)
{
    return (pair<int, int> *)((Rva00627960Vector *)this)->allocateCopy(
        n, (const Rva00627960Element *)first, (const Rva00627960Element *)last);
}
}

template class _STL::vector<_STL::pair<int, int>, _STL::allocator<_STL::pair<int, int> > >;
