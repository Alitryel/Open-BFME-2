// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// Dedicated unit without the bfmelist __forceinline _M_create_node shim so
// list<BfmePod264>::insert calls the already-landed create_node at 0x00289EB2.
// Retail 0x00289ED7 (37 bytes) is the insert worker; same pattern as
// stlport_list_int_insert.cpp.
#include <list>
// Suppress this TU's non-retail copy of ?_M_create_node@?$list@UBfmePod264@@V?$allocator@UBfmePod264@@@_STL@@@_STL@@IAEPAU?$_List_:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod264;
namespace _STL { template <> _List_node<BfmePod264> * list<BfmePod264,allocator<BfmePod264> >::_M_create_node(BfmePod264 const &); }
// Suppress this TU's non-retail copy of ?clear@?$_List_base@UBfmePod264@@V?$allocator@UBfmePod264@@@_STL@@@_STL@@QAEXXZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod264;
namespace _STL { template <> void _List_base<BfmePod264,allocator<BfmePod264> >::clear(); }

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}

struct BfmePod264 { int a[66]; };
// bfme link decl-only BfmePod264
namespace _STL { template <> void _Construct<BfmePod264, BfmePod264>(BfmePod264 *, BfmePod264 const &); }
inline bool operator==(const BfmePod264 &x, const BfmePod264 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod264 &x, const BfmePod264 &y) { return x.a[0] < y.a[0]; }
template class _STL::list<BfmePod264, _STL::allocator<BfmePod264> >;
