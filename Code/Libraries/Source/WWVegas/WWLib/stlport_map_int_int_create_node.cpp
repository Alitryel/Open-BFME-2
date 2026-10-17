// cl: /D_STLP_NO_EXCEPTIONS /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// Dedicated /O1 /D_STLP_NO_EXCEPTIONS + bfmealloc instantiation so _M_create_node calls the byte
// allocator at 0x307F0 and out-of-line _Construct. The existing map<int,int>
// units lack bfmealloc and inlined a different shape.
// A separate retail copy specialization owns 0x21C2CC; the unsuffixed
// compiler name is already claimed by the distinct 0x2CF6CF implementation.
// Keep this TU-local method spelling address-scoped without changing its type.
#define _M_copy _M_copy_0021C2CC
#define _STLP_BFME_RB_MINMAX_IMPORT  // inline _Rb_tree_node_base::_S_minimum/_S_maximum without a COMDAT copy (vendor/stlport/stl/_tree.h)
#include <map>
// bfme link decl-only begin
namespace _STL { template <> pair<_Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > >, bool>::pair(_Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > > const &, bool const &); }
namespace _STL { template <> _Rb_tree<int, pair<int const, int>, _Select1st<pair<int const, int> >, less<int>, allocator<pair<int const, int> > >::~_Rb_tree(); }
namespace _STL { template <> _Rb_tree<int, pair<int const, int>, _Select1st<pair<int const, int> >, less<int>, allocator<pair<int const, int> > > & _Rb_tree<int, pair<int const, int>, _Select1st<pair<int const, int> >, less<int>, allocator<pair<int const, int> > >::operator=(_Rb_tree<int, pair<int const, int>, _Select1st<pair<int const, int> >, less<int>, allocator<pair<int const, int> > > const &); }
namespace _STL { template <> _Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > > _Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > >::operator++(int); }
namespace _STL { template <> _Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > > & _Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > >::operator++(); }
namespace _STL { template <> _Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > > & _Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > >::operator--(); }
namespace _STL { template <> void _Rb_tree<int, pair<int const, int>, _Select1st<pair<int const, int> >, less<int>, allocator<pair<int const, int> > >::clear(); }
namespace _STL { template <> bool _Rb_tree<int, pair<int const, int>, _Select1st<pair<int const, int> >, less<int>, allocator<pair<int const, int> > >::empty() const; }
namespace _STL { template <> unsigned int _Rb_tree<int, pair<int const, int>, _Select1st<pair<int const, int> >, less<int>, allocator<pair<int const, int> > >::erase(int const &); }
namespace _STL { template <> void _Rb_tree<int, pair<int const, int>, _Select1st<pair<int const, int> >, less<int>, allocator<pair<int const, int> > >::erase(_Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > >, _Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > >); }
namespace _STL { template <> void _Rb_tree<int, pair<int const, int>, _Select1st<pair<int const, int> >, less<int>, allocator<pair<int const, int> > >::erase(_Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > >); }
namespace _STL { template <> pair<_Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > >, bool> _Rb_tree<int, pair<int const, int>, _Select1st<pair<int const, int> >, less<int>, allocator<pair<int const, int> > >::insert_unique(pair<int const, int> const &); }
// bfme link decl-only end

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}
#undef _M_copy
template class _STL::map<int, int, _STL::less<int>, _STL::allocator<_STL::pair<const int, int> > >;

typedef _STL::_Rb_tree<int,_STL::pair<const int,int>,_STL::_Select1st<_STL::pair<const int,int> >,_STL::less<int>,_STL::allocator<_STL::pair<const int,int> > > IntCopyTree;
template IntCopyTree::_Rb_tree(const IntCopyTree &);
