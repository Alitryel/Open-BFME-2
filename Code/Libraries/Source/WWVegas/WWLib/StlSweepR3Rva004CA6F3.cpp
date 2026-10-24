// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /O1 /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>

// vector<int> fill/insert otherwise instantiates the _Construct<int,int>
// COMDAT (one byte shape per TU flags); a file-static overload takes those
// calls instead so this TU emits no external copy.
#include <new>
namespace _STL {
static inline void _Construct(int *__p, const int &__val)
{ new (__p) int(__val); }
}
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <set>

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}










// Instantiate the recovered member; retain only its required template dependencies.
// Declared only (stl batch): retail's body for this name is the rowed one at its
// pinned address; this TU's copy is not retail's.
namespace _STL { template <> _STL::_Rb_tree_iterator<int,_STL::_Nonconst_traits<int> > _Rb_tree<int,int,_STL::_Identity<int>,_STL::less<int>,_STL::allocator<int> >::insert_equal(int const &); }
template _STL::_Rb_tree_iterator<int, _STL::_Const_traits<int> > _STL::multiset<int, _STL::less<int>, _STL::allocator<int> >::insert(int const &);

// The declared helper binds to that row (tools/allowed_symbols.py --alternatenames).
#pragma comment(linker, "/alternatename:?insert_equal@?$_Rb_tree@HHU?$_Identity@H@_STL@@U?$less@H@2@V?$allocator@H@2@@_STL@@QAE?AU?$_Rb_tree_iterator@HU?$_Nonconst_traits@H@_STL@@@2@ABH@Z=?rva004CA68B@AnimationSoundTree@@QAEPAPAUAnimationSoundTreeNode@@PAPAU2@PBX@Z")
