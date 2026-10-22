// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// cl: /O1 /G7 /Oy- /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// The element is BfmeE8: this operator-'s only call goes to the rowed
// _Deque_iterator_base<BfmeE8>::_M_advance at 0x00549CD4 (stlport_deque_e8_o1.cpp).
#include <deque>

struct BfmeE8 { int a, b; };

// operator-= and operator+= inline into operator- (retail negates and calls _M_advance directly);
// stlport_deque_e8_o1.cpp keeps the out-of-line copy, so none is emitted here.
namespace _STL {
template <> __forceinline _Deque_iterator<BfmeE8, _Nonconst_traits<BfmeE8> > &
_Deque_iterator<BfmeE8, _Nonconst_traits<BfmeE8> >::operator+=(int __n) { this->_M_advance(__n); return *this; }
template <> __forceinline _Deque_iterator<BfmeE8, _Nonconst_traits<BfmeE8> > &
_Deque_iterator<BfmeE8, _Nonconst_traits<BfmeE8> >::operator-=(int __n) { return *this += -__n; }
}

template _STL::_Deque_iterator<BfmeE8, _STL::_Nonconst_traits<BfmeE8> > _STL::_Deque_iterator<BfmeE8, _STL::_Nonconst_traits<BfmeE8> >::operator-(int) const;
