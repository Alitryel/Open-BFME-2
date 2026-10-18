// cl: /Ob2 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /DNDEBUG /D_STLP_NO_EXCEPTIONS /DWIN32 /D_WINDOWS
// stlport
// STLport4.5.3 bit-vector copy used by CreateAHeroData at+0x5C.
// Retail stores two pointer/bit-offset iterators and an end-of-storage pointer.
// Direct helper calls and the bit-count arithmetic establish the specialization.
#include <vector>
// Bind to the kept retail copies instead of emitting this unit's own.
namespace _STL { template <> _Bit_iter<_Bit_reference,_Bit_reference *>::_Bit_iter(); }
namespace _STL { template <> _Bvector_base<allocator<bool> >::_Bvector_base(allocator<bool> const &); }
// bfme link decl-only begin
namespace _STL { template <> _Bit_iter<_Bit_reference, _Bit_reference *>::_Bit_iter(); }
namespace _STL { template <> unsigned int * _Bvector_base<allocator<bool> >::_M_bit_alloc(unsigned int); }
namespace _STL { template <> void * __malloc_alloc<0>::allocate(unsigned int); }
namespace _STL { template <> void __malloc_alloc<0>::deallocate(void *, unsigned int); }
namespace _STL { template <> void allocator<unsigned int>::deallocate(unsigned int *, unsigned int) const; }
namespace _STL { template <> void _Bvector_base<allocator<bool> >::_M_deallocate(); }
// bfme link decl-only end
template _STL::vector<bool>::vector(const _STL::vector<bool>&);
