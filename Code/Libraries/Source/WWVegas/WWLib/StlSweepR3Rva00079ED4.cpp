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

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}



struct Rva00079ED4Record {  char bytes[1]; };


// Instantiate the recovered member; retain only its required template dependencies.
// Declared only (stl batch): retail's body for this name is the rowed one at its
// pinned address; this TU's copy is not retail's.
namespace _STL { template <> _STL::_Rb_tree_iterator<_STL::pair<int const,Rva00079ED4Record>,_STL::_Nonconst_traits<_STL::pair<int const,Rva00079ED4Record> > > _Rb_tree<int,_STL::pair<int const,Rva00079ED4Record>,_STL::_Select1st<_STL::pair<int const,Rva00079ED4Record> >,_STL::less<int>,_STL::allocator<_STL::pair<int const,Rva00079ED4Record> > >::insert_unique(_STL::_Rb_tree_iterator<_STL::pair<int const,Rva00079ED4Record>,_STL::_Nonconst_traits<_STL::pair<int const,Rva00079ED4Record> > >,_STL::pair<int const,Rva00079ED4Record> const &); }
template _STL::_Rb_tree_iterator<_STL::pair<int const, Rva00079ED4Record>, _STL::_Nonconst_traits<_STL::pair<int const, Rva00079ED4Record> > > _STL::map<int, Rva00079ED4Record, _STL::less<int>, _STL::allocator<_STL::pair<int const, Rva00079ED4Record> > >::insert(_STL::_Rb_tree_iterator<_STL::pair<int const, Rva00079ED4Record>, _STL::_Nonconst_traits<_STL::pair<int const, Rva00079ED4Record> > >, _STL::pair<int const, Rva00079ED4Record> const &);

// The declared helper binds to that row (tools/allowed_symbols.py --alternatenames).
#pragma comment(linker, "/alternatename:?insert_unique@?$_Rb_tree@HU?$pair@$$CBHURva00079ED4Record@@@_STL@@U?$_Select1st@U?$pair@$$CBHURva00079ED4Record@@@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHURva00079ED4Record@@@_STL@@@2@@_STL@@QAE?AU?$_Rb_tree_iterator@U?$pair@$$CBHURva00079ED4Record@@@_STL@@U?$_Nonconst_traits@U?$pair@$$CBHURva00079ED4Record@@@_STL@@@2@@2@U32@ABU?$pair@$$CBHURva00079ED4Record@@@2@@Z=?rva00079D14@Rva00079D14Tree@@QAE?AURva00079D14Iter@@U2@ABVRva00079D14Value@@@Z")
