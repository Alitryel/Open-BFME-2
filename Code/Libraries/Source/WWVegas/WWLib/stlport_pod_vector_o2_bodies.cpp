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
// Suppress this TU's non-retail copy of ??$uninitialized_fill_n@PAUBfmePod36@@IU1@@_STL@@YAPAUBfmePod36@@PAU1@IABU1@@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod36;
namespace _STL { template <> BfmePod36 * uninitialized_fill_n<BfmePod36 *,unsigned int,BfmePod36>(BfmePod36 *,unsigned int,BfmePod36 const &); }
// Suppress this TU's non-retail copy of ?_M_fill_insert@?$vector@UBfmePod36@@V?$allocator@UBfmePod36@@@_STL@@@_STL@@QAEXPAUBfmePod:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod36;
namespace _STL { template <> void vector<BfmePod36,allocator<BfmePod36> >::_M_fill_insert(BfmePod36 *,unsigned int,BfmePod36 const &); }
// Suppress this TU's non-retail copy of ??$__uninitialized_copy@PAUBfmePod36@@PAU1@@_STL@@YAPAUBfmePod36@@PAU1@00ABU__false_type@0:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod36;
namespace _STL { template <> BfmePod36 * __uninitialized_copy<BfmePod36 *,BfmePod36 *>(BfmePod36 *,BfmePod36 *,BfmePod36 *,__false_type const &); }
// Suppress this TU's non-retail copy of ??$__uninitialized_copy@PBUBfmePod36@@PAU1@@_STL@@YAPAUBfmePod36@@PBU1@0PAU1@ABU__false_ty:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod36;
namespace _STL { template <> BfmePod36 * __uninitialized_copy<BfmePod36 const *,BfmePod36 *>(BfmePod36 const *,BfmePod36 const *,BfmePod36 *,__false_type const &); }
// Suppress this TU's non-retail copy of ??$__copy_backward@PAUBfmePod36@@PAU1@H@_STL@@YAPAUBfmePod36@@PAU1@00ABUrandom_access_iter:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod36;
namespace _STL { template <> BfmePod36 * __copy_backward<BfmePod36 *,BfmePod36 *,int>(BfmePod36 *,BfmePod36 *,BfmePod36 *,random_access_iterator_tag const &,int *); }
// Suppress this TU's non-retail copy of ??$_Construct@UBfmePod36@@U1@@_STL@@YAXPAUBfmePod36@@ABU1@@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod36;
namespace _STL { template <> void _Construct<BfmePod36,BfmePod36>(BfmePod36 *,BfmePod36 const &); }
// Suppress this TU's non-retail copy of ??$__copy@PAUBfmePod36@@PAU1@H@_STL@@YAPAUBfmePod36@@PAU1@00ABUrandom_access_iterator_tag@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod36;
namespace _STL { template <> BfmePod36 * __copy<BfmePod36 *,BfmePod36 *,int>(BfmePod36 *,BfmePod36 *,BfmePod36 *,random_access_iterator_tag const &,int *); }
// Suppress this TU's non-retail copy of ??$__copy_backward_ptrs@PAUBfmePod36@@PAU1@@_STL@@YAPAUBfmePod36@@PAU1@00ABU__false_type@0:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod36;
namespace _STL { template <> BfmePod36 * __copy_backward_ptrs<BfmePod36 *,BfmePod36 *>(BfmePod36 *,BfmePod36 *,BfmePod36 *,__false_type const &); }
// Suppress this TU's non-retail copy of ?_M_insert_overflow@?$vector@UBfmePod36@@V?$allocator@UBfmePod36@@@_STL@@@_STL@@IAEXPAUBfm:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod36;
namespace _STL { template <> void vector<BfmePod36,allocator<BfmePod36> >::_M_insert_overflow(BfmePod36 *,BfmePod36 const &,__false_type const &,unsigned int,bool); }
// Suppress this TU's non-retail copy of ??$__uninitialized_fill_n@PAUBfmePod36@@IU1@@_STL@@YAPAUBfmePod36@@PAU1@IABU1@ABU__false_t:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod36;
namespace _STL { template <> BfmePod36 * __uninitialized_fill_n<BfmePod36 *,unsigned int,BfmePod36>(BfmePod36 *,unsigned int,BfmePod36 const &,__false_type const &); }
// Suppress this TU's non-retail copy of ??$fill@PAUBfmePod36@@U1@@_STL@@YAXPAUBfmePod36@@0ABU1@@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod36;
namespace _STL { template <> void fill<BfmePod36 *,BfmePod36>(BfmePod36 *,BfmePod36 *,BfmePod36 const &); }
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
