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
struct Rva002F307AElement {
 Rva002F307AElement(); Rva002F307AElement(const Rva002F307AElement&);
 ~Rva002F307AElement(); Rva002F307AElement&operator=(const Rva002F307AElement&);
 char bytes[8];
};
bool operator<(const Rva002F307AElement&,const Rva002F307AElement&);
// MSVC also instantiates the unused member-tree destructor with this constructor.
// Keep that operation external; this unit recovers only default construction.
namespace _STL { template <> _Rb_tree<Rva002F307AElement, Rva002F307AElement, _Identity<Rva002F307AElement>, less<Rva002F307AElement>, allocator<Rva002F307AElement> >::~_Rb_tree(); }

// Emit only the rowed constructor; unrelated set operations require element bodies.
template _STL::set<Rva002F307AElement>::set();
