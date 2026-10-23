// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#define _STLP_BFME_RB_MINMAX_IMPORT  // inline _Rb_tree_node_base::_S_minimum/_S_maximum without a COMDAT copy (vendor/stlport/stl/_tree.h)
#include <set>

// _Rb_tree_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _RbVal, class _RbLeft, class _RbRight>
static inline bool operator!=(const _Rb_tree_iterator<_RbVal, _RbLeft> &a,
                              const _Rb_tree_iterator<_RbVal, _RbRight> &b)
{ return a._M_node != b._M_node; }
}
struct Rva00419035Element {
 char bytes[8];
};
// Retail's copy reaches its own 115B _M_copy 0x00418E05 (the pair<const int,int>
// tree's shape): the element copies memberwise. Instantiate only the two
// rowed copy constructors.
template _STL::_Rb_tree<Rva00419035Element,Rva00419035Element,_STL::_Identity<Rva00419035Element>,_STL::less<Rva00419035Element>,_STL::allocator<Rva00419035Element> >::_Rb_tree(const _STL::_Rb_tree<Rva00419035Element,Rva00419035Element,_STL::_Identity<Rva00419035Element>,_STL::less<Rva00419035Element>,_STL::allocator<Rva00419035Element> >&);
template _STL::set<Rva00419035Element>::set(const _STL::set<Rva00419035Element>&);
