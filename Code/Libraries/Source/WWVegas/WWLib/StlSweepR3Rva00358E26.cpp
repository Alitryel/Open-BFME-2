// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
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

// _Rb_tree_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _RbVal, class _RbLeft, class _RbRight>
static inline bool operator!=(const _Rb_tree_iterator<_RbVal, _RbLeft> &a,
                              const _Rb_tree_iterator<_RbVal, _RbRight> &b)
{ return a._M_node != b._M_node; }
}

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}



struct Rva00358E26Record { char word;
// ?Rva00358E26Record::operator< present-unmatched
bool operator<(const Rva00358E26Record&b)const{return word<b.word;}
// ?Rva00358E26Record::operator== present-unmatched
bool operator==(const Rva00358E26Record&b)const{return word==b.word;}
};
namespace _STL {template<>struct __type_traits<Rva00358E26Record>:__type_traits_aux<1>{};}

typedef _STL::_Rb_tree<int, _STL::pair<int const, Rva00358E26Record>,
	_STL::_Select1st<_STL::pair<int const, Rva00358E26Record> >,
	_STL::less<int>, _STL::allocator<_STL::pair<int const, Rva00358E26Record> > > Rva00359269Tree;


// Retail's range erase calls the rowed tree clear at 0x00358DFD and node erase at
// 0x00358D27; suppress this TU's own copies and bind the template names to those rows.
namespace _STL {
template <> void _Rb_tree<int, pair<int const, Rva00358E26Record>, _Select1st<pair<int const, Rva00358E26Record> >, less<int>, allocator<pair<int const, Rva00358E26Record> > >::clear();
template <> void _Rb_tree<int, pair<int const, Rva00358E26Record>, _Select1st<pair<int const, Rva00358E26Record> >, less<int>, allocator<pair<int const, Rva00358E26Record> > >::erase(_Rb_tree<int, pair<int const, Rva00358E26Record>, _Select1st<pair<int const, Rva00358E26Record> >, less<int>, allocator<pair<int const, Rva00358E26Record> > >::iterator);
}
#pragma comment(linker, "/alternatename:?clear@?$_Rb_tree@HU?$pair@$$CBHURva00358E26Record@@@_STL@@U?$_Select1st@U?$pair@$$CBHURva00358E26Record@@@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHURva00358E26Record@@@_STL@@@2@@_STL@@QAEXXZ=?rva00358DFD@Rva00358D62@@QAEXXZ")
#pragma comment(linker, "/alternatename:?erase@?$_Rb_tree@HU?$pair@$$CBHURva00358E26Record@@@_STL@@U?$_Select1st@U?$pair@$$CBHURva00358E26Record@@@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHURva00358E26Record@@@_STL@@@2@@_STL@@QAEXU?$_Rb_tree_iterator@U?$pair@$$CBHURva00358E26Record@@@_STL@@U?$_Nonconst_traits@U?$pair@$$CBHURva00358E26Record@@@_STL@@@2@@2@@Z=?erase@?$_Rb_tree@URva0027EA49@@U1@U?$_Identity@URva0027EA49@@@_STL@@U?$less@URva0027EA49@@@3@V?$allocator@URva0027EA49@@@3@@_STL@@QAEXU?$_Rb_tree_iterator@URva0027EA49@@U?$_Nonconst_traits@URva0027EA49@@@_STL@@@2@@Z")

// Instantiate the recovered member; retain only its required template dependencies.
template void _STL::_Rb_tree<int, _STL::pair<int const, Rva00358E26Record>, _STL::_Select1st<_STL::pair<int const, Rva00358E26Record> >, _STL::less<int>, _STL::allocator<_STL::pair<int const, Rva00358E26Record> > >::erase(_STL::_Rb_tree_iterator<_STL::pair<int const, Rva00358E26Record>, _STL::_Nonconst_traits<_STL::pair<int const, Rva00358E26Record> > >, _STL::_Rb_tree_iterator<_STL::pair<int const, Rva00358E26Record>, _STL::_Nonconst_traits<_STL::pair<int const, Rva00358E26Record> > >);

// Incidental target placement 0x00358FA5: donor member spelling/layout remains an inference.
template unsigned int _STL::_Rb_tree<int, _STL::pair<int const, Rva00358E26Record>, _STL::_Select1st<_STL::pair<int const, Rva00358E26Record> >, _STL::less<int>, _STL::allocator<_STL::pair<int const, Rva00358E26Record> > >::erase(int const &);

// Native 0x00359269..0x0035926E is an independent tail entry to the
// verified key erase at 0x00358FA5, with ECX and its reference argument
// unchanged. The existing tree view establishes the forwarding interface;
// neither the original wrapper name nor its containing application type
// is established, so retain an address-derived wrapper.
class Rva00359269 : public Rva00359269Tree
{
public:
	unsigned int rva00359269(const int &key);
};

unsigned int Rva00359269::rva00359269(const int &key)
{
	return erase(key);
}
