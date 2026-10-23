// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ??$__uninitialized_copy@PBV?$vector@IV?$allocator@I@_STL@@@_STL@@PAV12@@_STL@@YAPAV?$vector@IV?$allocator@I@_STL@@@0@PBV10@0PAV10@ABU__false_type@0@@Z
// retail 0x00460F45 38 bytes. STLport __uninitialized_copy for 12-byte
// retail 0x00460F45 38 bytes. Stride-0xC sibling of the rowed AsciiString
// copy at 0x0002C4B2 and E8/E16 38B rows. Calls the vector _Construct dupe
// at 0x00460F18 (rowed as Rva00460F18Construct; the _Construct name itself is
// rowed at 0x000796E8), so the specialization below spells the STLport loop
// against that row and emits the 38B push-esi/edi body.

#include <vector>
#include <memory>

typedef _STL::vector<unsigned int, _STL::allocator<unsigned int> > VecUint;

// Retail's loop calls the placement copy at 0x00460F18, rowed as
// Rva00460F18Construct (stlport_construct_stl_types.cpp), not the _Construct
// at 0x000796E8, so this instantiation is spelled out to call that row.
void Rva00460F18Construct(void *dest, const void *source);

namespace _STL
{
template <>
VecUint *__uninitialized_copy<const VecUint *, VecUint *>(const VecUint *__first, const VecUint *__last, VecUint *__result, const __false_type &)
{
	VecUint *__cur = __result;
	for ( ; __first != __last; ++__first, ++__cur)
		Rva00460F18Construct(&*__cur, &*__first);
	return __cur;
}
}
