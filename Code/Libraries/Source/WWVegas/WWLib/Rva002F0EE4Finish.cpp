// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// STLport 4.5.3 __pop_heap_aux over the pathfinder priority queue of
// _Rva002EBB53Wrap pointers, retail 0x002F0EE4, 30 bytes. Called by pop_heap
// 0x002F1F02 (call at 0x002F1F10); forwards (first, last - 1, last - 1,
// *(last - 1), comp, 0) to __pop_heap 0x002EF27D (StlSweepW4Rva002EF27D.cpp).
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

extern template void _STL::__pop_heap(_Rva002EBB53Wrap **, _Rva002EBB53Wrap **, _Rva002EBB53Wrap **, _Rva002EBB53Wrap *, Rva002EBB53Compare, int *);
template void _STL::__pop_heap_aux(_Rva002EBB53Wrap **, _Rva002EBB53Wrap **, _Rva002EBB53Wrap **, Rva002EBB53Compare);
