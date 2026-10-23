// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// A vendored instantiation unit. It exists so the linker-selected bodies of
// this container appear as COMDATs that build/objplace.py can place against
// unlanded functions; the suffix says which optimisation level, because for
// these containers different bodies survive the link from different units.
#define _STLP_BFME_RB_MINMAX_IMPORT  // inline _Rb_tree_node_base::_S_minimum/_S_maximum without a COMDAT copy (vendor/stlport/stl/_tree.h)
#include <map>
// bfme link decl-only begin
namespace _STL { template <> _Rb_tree<int, pair<int const, void *>, _Select1st<pair<int const, void *> >, less<int>, allocator<pair<int const, void *> > >::~_Rb_tree(); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ?_M_copy@?$_Rb_tree@HU?$pair@$$CBHPAX@_STL@@U?$_Select1st@U?$pair@$$CBHPAX@_STL@@@2@U?$les:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> _Rb_tree_node<pair<int const ,void *> > * _Rb_tree<int,pair<int const ,void *>,_Select1st<pair<int const ,void *> >,less<int>,allocator<pair<int const ,void *> > >::_M_copy(_Rb_tree_node<pair<int const ,void *> > *,_Rb_tree_node<pair<int const ,void *> > *); }

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
// Retail compares these keys unsigned: _M_lower_bound 0x004FF3B6 and
// _M_upper_bound 0x004FF539 use jb/jae (as in RvaTreeEraseRangeFamily.cpp).
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return (unsigned int)a < (unsigned int)b; }
}

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}
template class _STL::map<int, void *, _STL::less<int>, _STL::allocator<_STL::pair<const int, void *> > >;

// Whole-class instantiation of this tree. It reproduces count (retail 0x004FF8B1)
// byte for byte; their calls read the tree's matched STL helpers.
template class _STL::_Rb_tree<int,_STL::pair<int const ,void *>,_STL::_Select1st<_STL::pair<int const ,void *> >,_STL::less<int>,_STL::allocator<_STL::pair<int const ,void *> > >;

// The module-pointer registry uses the same independently verified trivial
// node lifetime. Emit its actual typed clear and recursive erase providers
// here with the established kept STL lifetime family.
struct Rva004ABDDCEntry;
typedef _STL::_Rb_tree<Rva004ABDDCEntry *, Rva004ABDDCEntry *,
    _STL::_Identity<Rva004ABDDCEntry *>, _STL::less<Rva004ABDDCEntry *>,
    _STL::allocator<Rva004ABDDCEntry *> > ModuleKeyRegistryTree;
template void ModuleKeyRegistryTree::clear();
