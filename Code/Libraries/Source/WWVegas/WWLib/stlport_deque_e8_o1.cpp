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
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <deque>
struct BfmeE8 { int a, b; };

// This TU emits its own copies of the deque members and helpers below, and
// they sort first in link order (this object, 0x549CD4 region, before
// stlport_deque_e8_initmap.cpp / _pushback_aux.cpp). They are the placeholder
// element's private instantiations, not retail's, so make them
// declaration-only: the retail provider is then the copy the link keeps.
namespace _STL {
template <> void _Destroy(_Deque_iterator<BfmeE8, _Nonconst_traits<BfmeE8> >,
                          _Deque_iterator<BfmeE8, _Nonconst_traits<BfmeE8> >);
template <> void __destroy(_Deque_iterator<BfmeE8, _Nonconst_traits<BfmeE8> >,
                           _Deque_iterator<BfmeE8, _Nonconst_traits<BfmeE8> >, BfmeE8 *);
template <> void __destroy_aux(_Deque_iterator<BfmeE8, _Nonconst_traits<BfmeE8> >,
                               _Deque_iterator<BfmeE8, _Nonconst_traits<BfmeE8> >,
                               const __false_type &);
template <> _Deque_iterator<BfmeE8, _Const_traits<BfmeE8> > &
              _Deque_iterator<BfmeE8, _Const_traits<BfmeE8> >::operator++();
template <> _Deque_base<BfmeE8, allocator<BfmeE8> >::_Deque_base(const allocator<BfmeE8> &, size_t);
template <> deque<BfmeE8, allocator<BfmeE8> >::deque(const allocator<BfmeE8> &);
template <> deque<BfmeE8, allocator<BfmeE8> >::~deque();
template <> void _Deque_base<BfmeE8, allocator<BfmeE8> >::_M_initialize_map(size_t);
template <> void _Deque_base<BfmeE8, allocator<BfmeE8> >::_M_destroy_nodes(BfmeE8 **, BfmeE8 **);
template <> void deque<BfmeE8, allocator<BfmeE8> >::pop_front();
template <> void deque<BfmeE8, allocator<BfmeE8> >::_M_pop_front_aux();
template <> void deque<BfmeE8, allocator<BfmeE8> >::_M_push_back_aux_v(const BfmeE8 &);
}

template class _STL::deque<BfmeE8, _STL::allocator<BfmeE8 > >;
