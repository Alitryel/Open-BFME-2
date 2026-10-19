// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??$__copy@PBV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@PAV12@H at
// retail 0x00079F8A (50B): stride-12 copy loop over narrow basic_string.
// Retail calls the rowed copy-assign at 0x000120C0, i.e. STLport 4.6-style
// operator= returning assign(__s); the vendored 4.5.3 header instead emits a
// self-check plus range-assign. The 4.6-style specialization below reconciles
// the version gap; it inlines into the loop. Caller 0x0007A414 in 0x0007A401.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <algorithm>
#include <string>
#include <cstddef>
// bfme link decl-only begin
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> > & basic_string<char, char_traits<char>, allocator<char> >::operator=(basic_string<char, char_traits<char>, allocator<char> > const &); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> > & basic_string<char, char_traits<char>, allocator<char> >::assign(basic_string<char, char_traits<char>, allocator<char> > const &); }
namespace _STL { template <> char * basic_string<char, char_traits<char>, allocator<char> >::erase(char *, char *); }
namespace _STL { template <> char * __char_traits_base<char, int>::move(char *, char const *, unsigned int); }
// bfme link decl-only end
// Suppress this TU's non-retail proxy<char> allocate copy (family2-LK3 row 30):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> char *_STLP_alloc_proxy<char*, char, allocator<char> >::allocate(size_t);
}
// Suppress this TU's non-retail proxy<char> deallocate copy (family2-LK3 row 28):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void _STLP_alloc_proxy<char*, char, allocator<char> >::deallocate(char*, size_t);
}

typedef _STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > NarrowStr12;

template NarrowStr12 &NarrowStr12::assign(const NarrowStr12 &);

// dllimport keeps it inline-only: the loop inlines it and the TU emits no
// operator= copy of its own (retail's 0x000120C0 serves the link).
template <> __declspec(dllimport) __forceinline NarrowStr12 &NarrowStr12::operator=(const NarrowStr12 &__s) { return assign(__s); }

template NarrowStr12 *_STL::copy<const NarrowStr12 *, NarrowStr12 *>(const NarrowStr12 *, const NarrowStr12 *, NarrowStr12 *);
