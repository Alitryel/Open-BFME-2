// ??0Rva004E4F82@@QAE@XZ
// cl: /Ireference/shims/bfmelist /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva004E4F82@@QAE@XZ @0x004E4F82 144B
// __thiscall no-arg ctor: six floats +0..+0x14 zero, +0x18 zero,
// +0x24=1.0f +0x28=20.0f +0x2c=60.0f, +0x30=-1,
// list<int> at +0x34 via rowed List_base<int> 0x004EC36C,
// list<BfmePod8> at +0x38 via rowed List_base<BfmePod8> 0x0035C9A6.
// Caller 0x004E556E in 0x004E5559. The native /O1 /arch:SSE /G7 profile
// with ordinary alias analysis preserves both this initializer's early -1
// store and the shared list constructor's native node-link store order when
// the 1.0f value is represented as the read-only compiler literal it is.
#include <list>
// Suppress this TU's non-retail copy of ?clear@?$_List_base@UBfmePod8@@V?$allocator@UBfmePod8@@@_STL@@@_STL@@QAEXXZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod8;
namespace _STL { template <> void _List_base<BfmePod8,allocator<BfmePod8> >::clear(); }

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
template <> _List_base<int, allocator<int> >::_List_base(const allocator<int> &);
}

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
template <> void _List_base<int, allocator<int> >::clear();
}

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
template <> _List_base<int, allocator<int> >::~_List_base();
}

// list<int> destruction otherwise instantiates per-TU deallocate
// COMDATs (one byte shape per TU flags); explicit dllimport+forceinline
// specializations take those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void allocator<_List_node<int> >::deallocate(_List_node<int>* __p, size_t __n) const {
  _STLP_ASSERT( (__p == 0) == (__n == 0) )
    if (__p != 0) __sgi_alloc::deallocate((void*)__p, __n * sizeof(value_type));
}
template <> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<_List_node<int> *, _List_node<int>, allocator<_List_node<int> > >::deallocate(_List_node<int> *__p, size_t __n) {
  allocator<_List_node<int> >().deallocate(__p, __n);
}
}
struct BfmePod8 { int a[2]; };
inline bool operator==(const BfmePod8 &x, const BfmePod8 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod8 &x, const BfmePod8 &y) { return x.a[0] < y.a[0]; }

// Native .rdata 0x007BB8D8 is the canonical compiler literal 1.0f.
// g_00BC6258 was the retail address alias (RVA 0x007C6258) of the constant 60.0f; the literal is the source.

class Rva004E4F82
{
public:
    Rva004E4F82();
    float m_00;
    float m_04;
    float m_08;
    float m_0C;
    float m_10;
    float m_14;
    float m_18;
    int m_1C;
    int m_20;
    float m_24;
    float m_28;
    float m_2C;
    int m_30;
    _STL::list<int, _STL::allocator<int> > m_34;
    _STL::list<BfmePod8, _STL::allocator<BfmePod8> > m_38;
};

Rva004E4F82::Rva004E4F82() : m_30(-1), m_18(0.0f), m_24(1.0f), m_28(20.0f), m_2C(60.0f)
{
    m_00 = 0.0f;
    m_04 = 0.0f;
    m_08 = 0.0f;
    m_0C = 0.0f;
    m_10 = 0.0f;
    m_14 = 0.0f;
}