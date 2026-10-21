// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// The element type here is a STAND-IN. What the image fixes is the element
// SIZE - it is the stride in every loop and the shift in every distance - and
// a byte-exact body says only that the real element is a POD of that size.
// BfmeE8, BfmeE12 and BfmeE16 name that size and claim nothing more. The
// bodies are byte-exact; the mangled names carry a placeholder where the real
// instantiation's type belongs, and should be repointed if that type is ever
// identified from a call site.
#include <deque>
struct BfmeE8 { int a, b; };
// Only the rowed operations belong to this optimization variant. The map
// initializer is supplied by stlport_deque_e8_initmap.cpp at retail's address.
namespace _STL {
// Retain the header's inline operations without competing with their retail
// external copies in the /O1 sibling and the vector allocator providers.
template <> __declspec(dllimport) __forceinline
void allocator<BfmeE8>::deallocate(BfmeE8 *p, size_t n) const {
    _STLP_ASSERT((p == 0) == (n == 0))
    if (p != 0) ::free((void *)p);
}
template <> __declspec(dllimport) __forceinline
void _Deque_iterator_base<BfmeE8>::_M_increment() {
    if (++_M_cur == _M_last) {
        _M_set_node(_M_node + 1);
        _M_cur = _M_first;
    }
}
template <> void _Deque_base<BfmeE8, allocator<BfmeE8> >::_M_initialize_map(size_t);
}
template void _STL::deque<BfmeE8>::pop_front();
template _STL::deque<BfmeE8>::deque(const _STL::allocator<BfmeE8> &);
template _STL::deque<BfmeE8>::~deque();
template _STL::_Deque_iterator<BfmeE8, _STL::_Const_traits<BfmeE8> > &
_STL::_Deque_iterator<BfmeE8, _STL::_Const_traits<BfmeE8> >::operator++();
template void _STL::__destroy_aux<
    _STL::_Deque_iterator<BfmeE8, _STL::_Nonconst_traits<BfmeE8> > >(
    _STL::_Deque_iterator<BfmeE8, _STL::_Nonconst_traits<BfmeE8> >,
    _STL::_Deque_iterator<BfmeE8, _STL::_Nonconst_traits<BfmeE8> >,
    const _STL::__false_type &);
template void _STL::__destroy<
    _STL::_Deque_iterator<BfmeE8, _STL::_Nonconst_traits<BfmeE8> >, BfmeE8>(
    _STL::_Deque_iterator<BfmeE8, _STL::_Nonconst_traits<BfmeE8> >,
    _STL::_Deque_iterator<BfmeE8, _STL::_Nonconst_traits<BfmeE8> >, BfmeE8 *);
