// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
//
// STLport 4.5.3 basic_ios<char>::imbue (stl/_ios.c), retail 0x00016110, 238
// bytes: the vendor body verbatim, instantiated on its own.
//
// Two build settings decide the bytes. _STLP_USE_MALLOC frees the cached
// grouping string's old buffer with plain free rather than the node
// allocator's size-checked operator delete, and _CRTIMP= makes that a direct
// call instead of one through the CRT import.

// The cached grouping string is assigned through _M_assign_dispatch<char*>,
// whose matched body at 0x000120F0 carries the public member signature in this
// reconstruction. Limit this access adaptation to the string header; layout
// and source semantics are unchanged.
#define private public
#define _STLP_BFME_COPY_TRIVIAL_EXTERN  // call retail's one __copy_trivial (vendor/stlport/stl/_algobase.h)
#include <stl/_alloc.h>
// Keep retail's inline character-buffer cleanup; the public allocator
// entry point is supplied by its separately verified owner.
namespace _STL {
template <> void __malloc_alloc<0>::deallocate(void *, size_t);
#pragma optimize("gsy", on)
template <> __forceinline void allocator<char>::deallocate(char *p, size_t) const { if (p != 0) free(p); }
template <> __forceinline void allocator<unsigned short>::deallocate(unsigned short *p, size_t) const { if (p != 0) free(p); }
#pragma optimize("", on)
}

#include <string>
#undef private
#include <ios>

#include <cstddef>
// bfme link decl-only begin
namespace _STL { template <> char * basic_string<char, char_traits<char>, allocator<char> >::erase(char *, char *); }
namespace _STL { template <> char * __char_traits_base<char, int>::move(char *, char const *, unsigned int); }
// bfme link decl-only end
// Suppress this TU's non-retail proxy<char> allocate copy (family2-LK3 row 30):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> char *_STLP_alloc_proxy<char*, char, allocator<char> >::allocate(size_t);
}
template _STL::locale _STL::basic_ios<char, _STL::char_traits<char> >::imbue(const _STL::locale &);
