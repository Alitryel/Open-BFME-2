// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// _Deque_base map setup for deque<BfmeE8>: _M_initialize_map 189B at
// 0x0073C8F0 plus the (alloc n) base ctor 76B at 0x0073CFE0 which calls it.
// Same placeholder-element convention as the sibling stlport_deque_e8_o1.cpp
// (BfmeE8 names only the element SIZE). Split into its own TU without /EHsc:
// retail carries no exception-handling frame for either function (the
// _STLP_TRY/_STLP_UNWIND rollback in vendor/stlport/stl/_deque.c compiles to
// nothing once _STLP_USE_EXCEPTIONS is off), while the sibling files need
// /EHsc for other members they host. /O2 inlines _M_create_nodes into
// _M_initialize_map (the /O1 probe outlines it as a call and lands 33B
// short); the node stride is 0x80 with shr-4 sizing (128/8 = 16 per node).
#include <deque>
struct BfmeE8 { int a, b; };

// Preserve the header's inline allocation, release and iterator arithmetic;
// their external retail copies belong to the sibling providers.
namespace _STL {
template <> __declspec(dllimport) __forceinline
BfmeE8 *allocator<BfmeE8>::allocate(size_t n, const void *) const {
    return n != 0 ? (BfmeE8 *)allocator<char>::allocate(n * sizeof(BfmeE8), 0) : 0;
}
template <> __declspec(dllimport) __forceinline
BfmeE8 **allocator<BfmeE8 *>::allocate(size_t n, const void *) const {
    return n != 0 ? (BfmeE8 **)allocator<char>::allocate(n * sizeof(BfmeE8 *), 0) : 0;
}
template <> __declspec(dllimport) __forceinline
void allocator<BfmeE8>::deallocate(BfmeE8 *p, size_t n) const {
    _STLP_ASSERT((p == 0) == (n == 0))
    if (p != 0) ::free((void *)p);
}
// The matched -= wrapper calls this helper out of line; its /O1 retail
// provider supplies the external definition.
template <> void _Deque_iterator_base<BfmeE8>::_M_advance(difference_type);

}

// Instantiate the four rowed operations rather than every deque member.
// Other optimization variants and the push-back unit own the remaining bodies.
template void _STL::_Deque_base<BfmeE8, _STL::allocator<BfmeE8> >::_M_initialize_map(size_t);
template _STL::_Deque_base<BfmeE8, _STL::allocator<BfmeE8> >::_Deque_base(
    const _STL::allocator<BfmeE8> &, size_t);
template void _STL::_Deque_base<BfmeE8, _STL::allocator<BfmeE8> >::_M_destroy_nodes(
    BfmeE8 **, BfmeE8 **);
template _STL::_Deque_iterator<BfmeE8, _STL::_Nonconst_traits<BfmeE8> > &
_STL::_Deque_iterator<BfmeE8, _STL::_Nonconst_traits<BfmeE8> >::operator-=(ptrdiff_t);
