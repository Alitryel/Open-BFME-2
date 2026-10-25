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



struct Rva0007989CRecord {  int word0;int word1;int word2; };
// Declared only: retail's element copy is the rowed body at this name's pinned
// address; this TU's copy is not retail's.
namespace _STL { template <> void _Construct<pair<const int, Rva0007989CRecord> , pair<const int, Rva0007989CRecord> >(pair<const int, Rva0007989CRecord>  *, const pair<const int, Rva0007989CRecord>  &); }


// Instantiate the recovered member; retain only its required template dependencies.
// The node's element copy is retail 0x0007975E, rowed as ?Rva0007975EConstruct@@YAXPAXPBX@Z; bind the
// call to that row instead of emitting this unit's own _Construct copy.
void Rva0007975EConstruct(void *dest, const void *source);
namespace _STL {
// ?_STL::_Construct absent-from-retail
static __forceinline void _Construct(_STL::pair<int const, Rva0007989CRecord> *dest, const _STL::pair<int const, Rva0007989CRecord> &source)
{
	Rva0007975EConstruct(dest, &source);
}
}
template _STL::_Rb_tree_node<_STL::pair<int const, Rva0007989CRecord> > * _STL::_Rb_tree<int, _STL::pair<int const, Rva0007989CRecord>, _STL::_Select1st<_STL::pair<int const, Rva0007989CRecord> >, _STL::less<int>, _STL::allocator<_STL::pair<int const, Rva0007989CRecord> > >::_M_create_node(_STL::pair<int const, Rva0007989CRecord> const &);
