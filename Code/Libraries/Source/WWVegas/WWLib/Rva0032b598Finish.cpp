// cl: /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /DNDEBUG /D_STLP_NO_EXCEPTIONS /DWIN32 /D_WINDOWS
// stlport
//
// ??$_Construct@V?$vector@UBfmeE8@@V?$allocator@UBfmeE8@@@_STL@@@_STL@@V12@@_STL@@YAXPAV?$vector@UBfmeE8@@V?$allocator@UBfmeE8@@@_STL@@@0@ABV10@@Z
// @ 0x0032B598 (45B).  STLport placement-copy for a vector<BfmeE8> element:
// null-guarded placement new over one element, delegating out-of-line to the
// rowed vector<BfmeE8> copy ctor 0x004334D7.  Called per element by the
// 0xC-stride vector walkers 0x0032B5C5 / 0x0032B5EB / 0x0032E842 / 0x0032EA3F.
// Same 45B EH shape as the other _Construct<T,T> rows; the vendored header
// emits the EH state before the null test, which the hand-written
// `if (p) new (p) T(v)` free-function attempt banked one byte away.
#include <memory>
#include <vector>
// bfme link decl-only begin
namespace _STL { template <> void * __malloc_alloc<0>::allocate(unsigned int); }
namespace _STL { template <> void __malloc_alloc<0>::deallocate(void *, unsigned int); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@UBfmeE8@@@_STL@@QBEXPAUBfmeE8@@I@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmeE8;
namespace _STL { template <> void allocator<BfmeE8>::deallocate(BfmeE8 *,unsigned int) const; }
// Suppress this TU's non-retail copy of ??0?$_Vector_base@UBfmeE8@@V?$allocator@UBfmeE8@@@_STL@@@_STL@@QAE@IABV?$allocator@UBfmeE8:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmeE8;
namespace _STL { template <> _Vector_base<BfmeE8,allocator<BfmeE8> >::_Vector_base(unsigned int,allocator<BfmeE8> const &); }
// Suppress this TU's non-retail copy of ?allocate@?$_STLP_alloc_proxy@PAUBfmeE8@@U1@V?$allocator@UBfmeE8@@@_STL@@@_STL@@QAEPAUBfme:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmeE8;
namespace _STL { template <> BfmeE8 * _STLP_alloc_proxy<BfmeE8 *,BfmeE8,allocator<BfmeE8> >::allocate(unsigned int); }

struct BfmeE8 { int a, b; };

typedef _STL::vector<BfmeE8> ConstructE8Vec;

template void _STL::_Construct<ConstructE8Vec, ConstructE8Vec>(ConstructE8Vec *, const ConstructE8Vec &);
