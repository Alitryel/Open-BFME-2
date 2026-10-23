// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

// push_heap over the pathfinder priority queue of _Rva002EBB53Wrap pointers:
// retail 0x002F0D35 calls the rowed __push_heap_aux<_Rva002EBB53Wrap **,
// Rva002EBB53Compare> 0x002EF216 (Rva002EF216Push.cpp), whose view this repeats.
#include <algorithm>

struct _Rva002EBB53Inner {
    char m_pad[0x10];
    unsigned short m_key;
};
struct _Rva002EBB53Wrap {
    _Rva002EBB53Inner *m_inner;
};
// Empty comparator, greater-than on the payload key: the smallest key is on
// top of the heap.
struct Rva002EBB53Compare {
    bool operator()(const _Rva002EBB53Wrap *a, const _Rva002EBB53Wrap *b) const
    {
        return a->m_inner->m_key > b->m_inner->m_key;
    }
};

extern template void _STL::__push_heap_aux(_Rva002EBB53Wrap **, _Rva002EBB53Wrap **, Rva002EBB53Compare, int *, _Rva002EBB53Wrap **);
template void _STL::push_heap(_Rva002EBB53Wrap **, _Rva002EBB53Wrap **, Rva002EBB53Compare);
