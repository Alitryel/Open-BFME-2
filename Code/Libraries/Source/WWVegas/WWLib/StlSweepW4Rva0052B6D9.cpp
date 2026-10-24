// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /Og /Os /Ob1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <hash_map>

struct Rva0052B6D9Element { char bytes[1]; bool operator<(const Rva0052B6D9Element&)const; bool operator==(const Rva0052B6D9Element&)const; };
// Declared only: retail's element copy is the rowed body at this name's pinned
// address; this TU's copy is not retail's.
namespace _STL { template <> void _Construct<pair<const int, Rva0052B6D9Element> , pair<const int, Rva0052B6D9Element> >(pair<const int, Rva0052B6D9Element>  *, const pair<const int, Rva0052B6D9Element>  &); }
namespace _STL {template<> struct hash<Rva0052B6D9Element> { unsigned operator()(const Rva0052B6D9Element&) const; };}

// Instantiate the recovered operation and its required template dependencies.
// The node's element copy is retail 0x0052B6AC, rowed as ?Rva0052B6ACConstruct@@YAXPAXPBX@Z; bind the
// call to that row instead of emitting this unit's own _Construct copy.
void Rva0052B6ACConstruct(void *dest, const void *source);
namespace _STL {
// ?_STL::_Construct absent-from-retail
static __forceinline void _Construct(_STL::pair<int const, Rva0052B6D9Element> *dest, const _STL::pair<int const, Rva0052B6D9Element> &source)
{
	Rva0052B6ACConstruct(dest, &source);
}
}
template _STL::_Hashtable_node<_STL::pair<int const, Rva0052B6D9Element> > * _STL::hashtable<_STL::pair<int const, Rva0052B6D9Element>, int, _STL::hash<int>, _STL::_Select1st<_STL::pair<int const, Rva0052B6D9Element> >, _STL::equal_to<int>, _STL::allocator<_STL::pair<int const, Rva0052B6D9Element> > >::_M_new_node(_STL::pair<int const, Rva0052B6D9Element> const &);
// The declared element copy binds to that row (tools/allowed_symbols.py --alternatenames).
#pragma comment(linker, "/alternatename:??$_Construct@U?$pair@$$CBHURva0052B6D9Element@@@_STL@@U12@@_STL@@YAXPAU?$pair@$$CBHURva0052B6D9Element@@@0@ABU10@@Z=?Rva0052B6ACConstruct@@YAXPAXPBX@Z")
