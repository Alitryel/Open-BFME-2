// cl: /Ob2 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /DNDEBUG /D_STLP_NO_EXCEPTIONS /DWIN32 /D_WINDOWS
// stlport
// STLport 4.5.3 bit-vector fill constructor used by retail 0x0043FE13.
// Out-of-line base plus _M_initialize with an inlined 0/-1 fill loop.
#include <vector>
// bfme link decl-only begin
namespace _STL { template <> _Bit_iter<_Bit_reference, _Bit_reference *>::_Bit_iter(); }
namespace _STL { template <> unsigned int * _Bvector_base<allocator<bool> >::_M_bit_alloc(unsigned int); }
namespace _STL { template <> void * __malloc_alloc<0>::allocate(unsigned int); }
namespace _STL { template <> void __malloc_alloc<0>::deallocate(void *, unsigned int); }
// bfme link decl-only end
template _STL::vector<bool>::vector(unsigned, bool, _STL::allocator<bool> const &);
