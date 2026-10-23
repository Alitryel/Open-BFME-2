// cl: -EHsc /Os -Ireference/open-bfme-1/game/gen_small
// stlport

// ?erase@?$vector@UGen_p48cd@@V?$allocator@UGen_p48cd@@@_STL@@@_STL@@QAEPAUGen_p48cd@@PAU3@@Z
// retail 0x003F5C72, 55 bytes. Dedicated TU ported from the Open-BFME-1 donor
// game/gen_small/tgrid_005.cpp (reference/open-bfme-1): the donor preamble and
// this one vector<Gen_p48cd> instantiation (the donor's other containers
// omitted). The synthetic payload reproduces the layout and lifecycle only;
// the function is the STLport vector erase idiom over a 48-byte
// copy-constructible payload.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#define _STLP_BFME_COPY_TRIVIAL_EXTERN  // call retail's one __copy_trivial (vendor/stlport/stl/_algobase.h)
#include <vector>
// Keep __node_alloc<true,0>::deallocate inline-only: every call here is inlined,
// and this TU's /O1 COMDAT copy differs from the copy the link keeps.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _STLP_CALL __node_alloc<true, 0>::deallocate(void *__p, size_t __n)
{ if (__n > (size_t)_MAX_BYTES) __stl_delete(__p); else _M_deallocate(__p, __n); }
}

struct Gen_p48cd { int a[12]; Gen_p48cd(); Gen_p48cd(const Gen_p48cd&); ~Gen_p48cd(); Gen_p48cd& operator=(const Gen_p48cd&); };
bool operator==(const Gen_p48cd&, const Gen_p48cd&);
bool operator<(const Gen_p48cd&, const Gen_p48cd&);

template class _STL::vector<Gen_p48cd >;
