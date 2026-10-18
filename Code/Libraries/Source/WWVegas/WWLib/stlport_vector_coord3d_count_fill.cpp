// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ??0?$vector@UCoord3D@@V?$allocator@UCoord3D@@@_STL@@@_STL@@QAE@IABUCoord3D@@ABV?$allocator@UCoord3D@@@1@@Z @0x0007C2AC 43B: STLport vector<Coord3D> count-fill ctor.
// Calls count-taking _Vector_base at 0x005C8C37 (rowed as PrereqUnitRec 60B; Coord3D spelling ICF twin same 12B stride) and 3-arg uninitialized_fill_n<Coord3D> at 0x000CA1D3 (rowed).
// Chain lane: caller of just-landed Coord3D fill_n wrapper 0xCA1D3. Callers at 0x7CED5 0x7CFF6 0x7D00E in FUN_0047c8ae.
// The explicit nothrow specialization keeps the 3-arg wrapper call out of line (43B) and, unlike /Ob0,
// lets the count _Vector_base compile to the retail 60B body instead of a one-byte-shorter non-retail copy.
#include <vector>
#include "../../../Include/Lib/Coord3D.h"
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> _Vector_base<Coord3D,allocator<Coord3D> >::~_Vector_base(); }
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(nothrow) void _Construct<Coord3D,Coord3D>(Coord3D *,Coord3D const &); }
// Call the rowed 3-arg wrapper at 0x000CA1D3 out of line; nothrow keeps the count-fill ctor EH-free.
namespace _STL { template <> __declspec(nothrow) Coord3D *uninitialized_fill_n<Coord3D*,unsigned int,Coord3D>(Coord3D*,unsigned int,Coord3D const&); }
template _STL::vector<Coord3D>::vector(unsigned int, const Coord3D&, const _STL::allocator<Coord3D>&);
