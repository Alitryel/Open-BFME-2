// cl: /Ob2 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /DNDEBUG /D_STLP_NO_EXCEPTIONS /DWIN32 /D_WINDOWS
// stlport
// STLport 4.5.3 _Bit_iter::operator+=(difference_type), retail 0x00068E03
// (18 bytes, RET4): save this, call the matched
// _Bit_iterator_base::_M_advance (0x000660F7), return this. Retail has no
// caller of this copy. Flags follow stlport_vector_bool_copy.cpp, the unit
// that places _M_advance and the bit-iterator operators around it.
//
// Identity: the mutable and const iterator instantiations compile to the
// same bytes, so which one retail kept is an ICF guess; the mutable
// vector<bool>::iterator spelling is used.
#include <vector>
template _STL::_Bit_iter<_STL::_Bit_reference, _STL::_Bit_reference *> &
	_STL::_Bit_iter<_STL::_Bit_reference, _STL::_Bit_reference *>::operator+=(int);
