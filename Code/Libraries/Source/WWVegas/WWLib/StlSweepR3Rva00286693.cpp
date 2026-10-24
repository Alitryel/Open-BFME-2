// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /O1 /G7 /EHs /D_BFME_RETAIL_TREE_INSERT_LAYOUT /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <map>



struct Rva00286693Record {  int word0;int word1;int word2;int word3; };
// Declared only: retail's element copy is the rowed body at this name's pinned
// address; this TU's copy is not retail's.
namespace _STL { template <> void _Construct<pair<const int, Rva00286693Record> , pair<const int, Rva00286693Record> >(pair<const int, Rva00286693Record>  *, const pair<const int, Rva00286693Record>  &); }


// Instantiate the recovered member; retain only its required template dependencies.
template _STL::_Rb_tree_node<_STL::pair<int const, Rva00286693Record> > * _STL::_Rb_tree<int, _STL::pair<int const, Rva00286693Record>, _STL::_Select1st<_STL::pair<int const, Rva00286693Record> >, _STL::less<int>, _STL::allocator<_STL::pair<int const, Rva00286693Record> > >::_M_create_node(_STL::pair<int const, Rva00286693Record> const &);
// The declared element copy binds to that row (tools/allowed_symbols.py --alternatenames).
#pragma comment(linker, "/alternatename:??$_Construct@U?$pair@$$CBHURva00286693Record@@@_STL@@U12@@_STL@@YAXPAU?$pair@$$CBHURva00286693Record@@@0@ABU10@@Z=??$_Construct@VRva00285BEC@@V1@@_STL@@YAXPAVRva00285BEC@@ABV1@@Z")
