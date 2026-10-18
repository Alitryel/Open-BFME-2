// cl: /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /DNDEBUG /D_STLP_NO_EXCEPTIONS /DWIN32 /D_WINDOWS
// stlport
// STLport 4.5.3 vector copy at 0x2CFAB9. Retail allocates a four-byte-element
// range, then uses the established __copy_trivial helper at 0x179B0.
// unsigned int represents the observed scalar width; application enum/signed
// identity is not established. This operation preserves raw scalar values.
// The state-free allocator getter is a complete seven-byte alias at 21983A.
// The called base at 4F62A4 is the established ScienceType vector base: three
// pointer fields, count*4 allocation, initial begin==end and capacity=begin+n.
// Its retail allocator includes the allocation-hint argument. The base pin
// follows that independently decoded ABI/behavior, not a masked-call guess.
#include <vector>
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> _Vector_base<unsigned int,allocator<unsigned int> >::~_Vector_base(); }
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> _Vector_base<unsigned int,allocator<unsigned int> >::_Vector_base(unsigned int,allocator<unsigned int> const &); }
// bfme link decl-only begin
namespace _STL { template <> void * __malloc_alloc<0>::allocate(unsigned int); }
namespace _STL { template <> void __malloc_alloc<0>::deallocate(void *, unsigned int); }
// bfme link decl-only end
template _STL::vector<unsigned int>::vector(const _STL::vector<unsigned int>&);
