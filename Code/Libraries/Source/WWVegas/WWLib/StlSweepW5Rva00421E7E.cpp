// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// The element is BfmeE12: this destroy loop's only call goes to the rowed
// _Deque_iterator_base<BfmeE12>::_M_increment at 0x00421B1E (stlport_deque_e12_o1.cpp),
// and the deque<BfmeE12> units emit this same loop.
#include <deque>

struct BfmeE12 { float x, y, z; };

template void _STL::__destroy_aux<_STL::_Deque_iterator<BfmeE12, _STL::_Nonconst_traits<BfmeE12> > >(_STL::_Deque_iterator<BfmeE12, _STL::_Nonconst_traits<BfmeE12> >, _STL::_Deque_iterator<BfmeE12, _STL::_Nonconst_traits<BfmeE12> >, _STL::__false_type const &);
