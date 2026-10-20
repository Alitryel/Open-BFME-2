// cl: /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// Deque_base<BfmePod16> ctor retail 0x0041A157 75B. Same shape as the Pod28
// base at 0x0041A10C; calls rowed _M_initialize_map for BfmePod16 at
// 0x00419ED4 and ICF alloc_proxy bodies at 0x0014F3C4; unlocks 0x0041A6E5.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <deque>
#include <queue>
// Suppress this TU's non-retail copy of ??$__destroy_aux@U?$_Deque_iterator@UBfmePod16@@U?$_Nonconst_traits@UBfmePod16@@@_STL@@@_S:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod16;
namespace _STL { template <> void __destroy_aux<_Deque_iterator<BfmePod16,_Nonconst_traits<BfmePod16> > >(_Deque_iterator<BfmePod16,_Nonconst_traits<BfmePod16> >,_Deque_iterator<BfmePod16,_Nonconst_traits<BfmePod16> >,__false_type const &); }
struct BfmePod16 { int a[4]; };
template _STL::_Deque_base<BfmePod16, _STL::allocator<BfmePod16> >::_Deque_base(const _STL::allocator<BfmePod16> &, size_t);
template _STL::queue<BfmePod16, _STL::deque<BfmePod16, _STL::allocator<BfmePod16> > >::queue();
