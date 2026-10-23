// cl: /Ob1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// STLport 4.5.3 heap workers over the pathfinder priority queue of
// _Rva002EBB53Wrap pointers, ordered by the unsigned short key at +0x10 of the
// payload each wrapper points to:
//   __push_heap   retail 0x002EBB53, 72 bytes
//   __adjust_heap retail 0x002EBB9B, 96 bytes
// Retail's call chain fixes the family: the priority-queue pop 0x002F301F
// calls pop_heap 0x002F1F02 -> __pop_heap_aux 0x002F0EE4 -> __pop_heap
// 0x002EF27D -> __adjust_heap 0x002EBB9B -> __push_heap 0x002EBB53, and
// __push_heap_aux 0x002EF216 calls __push_heap. Every caller passes the empty
// comparator by value. The element is a pointer: __push_heap_aux and
// __pop_heap_aux push *(last - 1) straight from memory, which a one-pointer
// struct element does not compile to. Wrapper, payload and comparator names
// are address-derived; the key compare is structural inference.
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

template void _STL::__push_heap(_Rva002EBB53Wrap **, int, int, _Rva002EBB53Wrap *, Rva002EBB53Compare);
template void _STL::__adjust_heap(_Rva002EBB53Wrap **, int, int, _Rva002EBB53Wrap *, Rva002EBB53Compare);
