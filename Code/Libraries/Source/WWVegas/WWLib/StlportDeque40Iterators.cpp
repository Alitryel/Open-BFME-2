// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// STLport4.5.3 view of the target iterator stride; original element name and
// fields are unknown. Only the verified iterator or cleanup operations are claimed.
// Retail keeps one unsigned max, RVA 0x00013740 (the vendored STLport row). This unit's
// flags (/G7) compile a different copy, and retail kept another unit's. This unit-local
// overload keeps the inlined code and offers the link no second copy.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <deque>
struct BfmeOpaque40 { unsigned char bytes[40]; };
typedef _STL::_Deque_iterator<BfmeOpaque40, _STL::_Nonconst_traits<BfmeOpaque40> > BfmeDeque40Iterator;
typedef _STL::_Deque_iterator<BfmeOpaque40, _STL::_Const_traits<BfmeOpaque40> > BfmeDeque40ConstIterator;

// Instantiate the retained iterator and cleanup operations.
template int _STL::_Deque_iterator_base<BfmeOpaque40>::_M_subtract(const _STL::_Deque_iterator_base<BfmeOpaque40> &) const;
template void _STL::_Deque_iterator_base<BfmeOpaque40>::_M_advance(int);
template BfmeDeque40Iterator BfmeDeque40Iterator::operator+(int) const;
template BfmeOpaque40 &BfmeDeque40Iterator::operator[](int) const;
template BfmeDeque40ConstIterator &BfmeDeque40ConstIterator::operator+=(int);
template int BfmeDeque40Iterator::operator-(const BfmeDeque40Iterator &) const;
template BfmeOpaque40 &_STL::deque<BfmeOpaque40, _STL::allocator<BfmeOpaque40> >::operator[](unsigned int);
template void _STL::_Destroy(BfmeDeque40Iterator, BfmeDeque40Iterator);
template BfmeDeque40Iterator _STL::__uninitialized_copy(BfmeDeque40Iterator, BfmeDeque40Iterator, BfmeDeque40Iterator, const _STL::__false_type &);
template BfmeOpaque40 **_STL::copy(BfmeOpaque40 **, BfmeOpaque40 **, BfmeOpaque40 **);
