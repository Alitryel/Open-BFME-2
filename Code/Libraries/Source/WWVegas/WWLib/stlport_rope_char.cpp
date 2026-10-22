// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /DNDEBUG /D_STLP_NO_EXCEPTIONS /DWIN32 /D_WINDOWS
// stlport

#include <rope>
// bfme link decl-only begin
namespace _STL { template <> void allocator<char>::deallocate(char *, unsigned int) const; }
namespace _STL { template <> void __malloc_alloc<0>::deallocate(void *, size_t); }
namespace _STL { template <> void * __malloc_alloc<0>::allocate(unsigned int); }
namespace _STL { template <> char *fill_n<unsigned int>(char *, unsigned int, const char &); }
namespace _STL { template <> char *uninitialized_fill_n<char *, unsigned int, char>(char *, unsigned int, const char &); }
// bfme link decl-only end

template class _STL::rope<char, _STL::allocator<char> >;

// _S_ref is unplaced: the former RVA 0x006C5300 candidate calls GlobalFree,
// not InterlockedIncrement. Its masked DIR32 match did not establish identity.
