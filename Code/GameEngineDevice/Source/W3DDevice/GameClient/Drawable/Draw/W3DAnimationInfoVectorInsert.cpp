// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// ?insert@?$vector@VW3DAnimationInfo@@V?$allocator@VW3DAnimationInfo@@@_STL@@@_STL@@QAEPAVW3DAnimationInfo@@PAV3@ABV3@@Z
// retail 0x00538944, 149 bytes: STLport 4.5.3 vector<W3DAnimationInfo>::insert.
//
// Ported from the Open-BFME-1 donor
// game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DAnimationInfoVectorInsert.cpp
// (reference/open-bfme-1 @ 6583b3c1). Compiled at /O1 it is a unique masked
// placement on unclaimed .text. Its callees are the pinned W3DAnimationInfo
// helpers: _Construct 0x00469C61, copy constructor 0x0004254E,
// __copy_backward_ptrs 0x005B2B1E and _M_insert_overflow 0x0047008E. The
// same addresses carry the ledger's BfmeFloat4Record00469C61 vector family.
// The donor's element model is kept: sixteen bytes with an out-of-line copy
// constructor and no destructor (a destructor adds a destroy loop retail lacks).
// The member is instantiated explicitly instead of through the donor's anchor.
#define _STLP_NO_EXCEPTIONS 1
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>
// Suppress this TU's non-retail copy of ?_M_clear@?$vector@VW3DAnimationInfo@@V?$allocator@VW3DAnimationInfo@@@_STL@@@_STL@@IAEXXZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class W3DAnimationInfo;
namespace _STL { template <> void vector<W3DAnimationInfo,allocator<W3DAnimationInfo> >::_M_clear(); }
// Suppress this TU's non-retail copy of ??$_Destroy@PAVW3DAnimationInfo@@@_STL@@YAXPAVW3DAnimationInfo@@0@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class W3DAnimationInfo;
namespace _STL { template <> void _Destroy<W3DAnimationInfo *>(W3DAnimationInfo *,W3DAnimationInfo *); }
// Suppress this TU's non-retail copy of ?allocate@?$_STLP_alloc_proxy@PAVW3DAnimationInfo@@V1@V?$allocator@VW3DAnimationInfo@@@_ST:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class W3DAnimationInfo;
namespace _STL { template <> W3DAnimationInfo * _STLP_alloc_proxy<W3DAnimationInfo *,W3DAnimationInfo,allocator<W3DAnimationInfo> >::allocate(unsigned int); }
// Suppress this TU's non-retail copy of ??$__uninitialized_fill_n@PAVW3DAnimationInfo@@IV1@@_STL@@YAPAVW3DAnimationInfo@@PAV1@IABV:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class W3DAnimationInfo;
namespace _STL { template <> W3DAnimationInfo * __uninitialized_fill_n<W3DAnimationInfo *,unsigned int,W3DAnimationInfo>(W3DAnimationInfo *,unsigned int,W3DAnimationInfo const &,__false_type const &); }
// Suppress this TU's non-retail copy of ??$__uninitialized_copy@PAVW3DAnimationInfo@@PAV1@@_STL@@YAPAVW3DAnimationInfo@@PAV1@00ABU:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class W3DAnimationInfo;
namespace _STL { template <> W3DAnimationInfo * __uninitialized_copy<W3DAnimationInfo *,W3DAnimationInfo *>(W3DAnimationInfo *,W3DAnimationInfo *,W3DAnimationInfo *,__false_type const &); }
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@VW3DAnimationInfo@@@_STL@@QBEXPAVW3DAnimationInfo@@I@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class W3DAnimationInfo;
namespace _STL { template <> void allocator<W3DAnimationInfo>::deallocate(W3DAnimationInfo *,unsigned int) const; }
// Keep __node_alloc<true,0>::deallocate inline-only: every call here is inlined,
// and this TU's /O1 COMDAT copy differs from the copy the link keeps.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _STLP_CALL __node_alloc<true, 0>::deallocate(void *__p, size_t __n)
{ if (__n > (size_t)_MAX_BYTES) __stl_delete(__p); else _M_deallocate(__p, __n); }
}

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DModelDraw.h
class W3DAnimationInfo
{
public:
	W3DAnimationInfo(const W3DAnimationInfo &other);

private:
	char m_bfmeBody[0x10];
};

template _STL::vector<W3DAnimationInfo>::iterator
	_STL::vector<W3DAnimationInfo>::insert(_STL::vector<W3DAnimationInfo>::iterator, const W3DAnimationInfo &);
