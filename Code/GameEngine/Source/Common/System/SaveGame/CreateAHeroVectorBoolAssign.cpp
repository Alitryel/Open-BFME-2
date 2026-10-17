// cl: /Ob2 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// The vector<bool> member at CreateAHeroData+0x5C is established by the
// matched copy/destructor source and its 0x388F9B/0x3890D5 bit helpers.
// This explicit STLport instantiation recovers its complete assignment body.
#include <vector>
// bfme link decl-only begin
namespace _STL { template <> _Bit_iter<_Bit_reference, _Bit_reference *> copy<_Bit_iter<bool, bool const *>, _Bit_iter<_Bit_reference, _Bit_reference *> >(_Bit_iter<bool, bool const *>, _Bit_iter<bool, bool const *>, _Bit_iter<_Bit_reference, _Bit_reference *>); }
namespace _STL { template <> unsigned int * _Bvector_base<allocator<bool> >::_M_bit_alloc(unsigned int); }
// bfme link decl-only end
template _STL::vector<bool> &_STL::vector<bool>::operator=(const _STL::vector<bool> &);
