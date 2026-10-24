// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <algorithm>
#include <map>

struct Rva00358DA0Element { short words[1]; bool operator<(const Rva00358DA0Element&b)const { return words[0]<b.words[0]; } bool operator==(const Rva00358DA0Element&b)const {return words[0]==b.words[0];} };
// Declared only: retail's element copy is the rowed body at this name's pinned
// address; this TU's copy is not retail's.
namespace _STL { template <> void _Construct<pair<const Rva00358DA0Element, int> , pair<const Rva00358DA0Element, int> >(pair<const Rva00358DA0Element, int>  *, const pair<const Rva00358DA0Element, int>  &); }

// Instantiate the recovered operation and its required template dependencies.
// The node's element copy is retail 0x00358CA0, rowed as ?Rva00358CA0Construct@@YAXPAXPBX@Z; bind the
// call to that row instead of emitting this unit's own _Construct copy.
void Rva00358CA0Construct(void *dest, const void *source);
namespace _STL {
// ?_STL::_Construct absent-from-retail
static __forceinline void _Construct(_STL::pair<Rva00358DA0Element const, int> *dest, const _STL::pair<Rva00358DA0Element const, int> &source)
{
	Rva00358CA0Construct(dest, &source);
}
}
template _STL::_Rb_tree_node<_STL::pair<Rva00358DA0Element const, int> > * _STL::_Rb_tree<Rva00358DA0Element, _STL::pair<Rva00358DA0Element const, int>, _STL::_Select1st<_STL::pair<Rva00358DA0Element const, int> >, _STL::less<Rva00358DA0Element>, _STL::allocator<_STL::pair<Rva00358DA0Element const, int> > >::_M_create_node(_STL::pair<Rva00358DA0Element const, int> const &);
// The declared element copy binds to that row (tools/allowed_symbols.py --alternatenames).
#pragma comment(linker, "/alternatename:??$_Construct@U?$pair@$$CBURva00358DA0Element@@H@_STL@@U12@@_STL@@YAXPAU?$pair@$$CBURva00358DA0Element@@H@0@ABU10@@Z=?Rva00358CA0Construct@@YAXPAXPBX@Z")
