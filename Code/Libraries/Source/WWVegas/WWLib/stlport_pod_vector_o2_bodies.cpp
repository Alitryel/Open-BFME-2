// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// Pristine STLport 4.5.3 vector members for placeholder POD elements, as
// emitted at /O2. BfmePod36 stands for the real 36-byte element; the placed
// body's stride fixes the size. No retail caller is claimed.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>
// Suppress this TU's non-retail copy of ?_M_set@?$vector@UBfmePod36@@V?$allocator@UBfmePod36@@@_STL@@@_STL@@IAEXPAUBfmePod36@@00@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod36;
namespace _STL { template <> void vector<BfmePod36,allocator<BfmePod36> >::_M_set(BfmePod36 *,BfmePod36 *,BfmePod36 *); }
// Suppress this TU's non-retail copy of ?size@?$vector@UBfmePod36@@V?$allocator@UBfmePod36@@@_STL@@@_STL@@QBEIXZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod36;
namespace _STL { template <> unsigned int vector<BfmePod36,allocator<BfmePod36> >::size() const; }
// Suppress this TU's non-retail copy of ?_M_clear@?$vector@UBfmePod36@@V?$allocator@UBfmePod36@@@_STL@@@_STL@@IAEXXZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod36;
namespace _STL { template <> void vector<BfmePod36,allocator<BfmePod36> >::_M_clear(); }
// Suppress this TU's non-retail copy of ?deallocate@?$_STLP_alloc_proxy@PAUBfmePod36@@U1@V?$allocator@UBfmePod36@@@_STL@@@_STL@@QA:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod36;
namespace _STL { template <> void _STLP_alloc_proxy<BfmePod36 *,BfmePod36,allocator<BfmePod36> >::deallocate(BfmePod36 *,unsigned int); }
// Suppress this TU's non-retail copy of ?allocate@?$_STLP_alloc_proxy@PAUBfmePod36@@U1@V?$allocator@UBfmePod36@@@_STL@@@_STL@@QAEP:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod36;
namespace _STL { template <> BfmePod36 * _STLP_alloc_proxy<BfmePod36 *,BfmePod36,allocator<BfmePod36> >::allocate(unsigned int); }
struct BfmePod36 { int a[9]; };
template class _STL::vector<BfmePod36, _STL::allocator<BfmePod36 > >;
