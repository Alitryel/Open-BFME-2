// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /arch:SSE /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#define _STLP_BFME_RB_MINMAX_IMPORT  // inline _Rb_tree_node_base::_S_minimum/_S_maximum without a COMDAT copy (vendor/stlport/stl/_tree.h)
#include <set>
#include <memory>
#include <string>
#include <vector>
#include <utility>

// _Rb_tree_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _RbVal, class _RbLeft, class _RbRight>
static inline bool operator!=(const _Rb_tree_iterator<_RbVal, _RbLeft> &a,
                              const _Rb_tree_iterator<_RbVal, _RbRight> &b)
{ return a._M_node != b._M_node; }
}

struct Rva00388C0CElement { _STL::auto_ptr<unsigned> value;unsigned word0;Rva00388C0CElement(const Rva00388C0CElement&b);Rva00388C0CElement& operator=(const Rva00388C0CElement&b);bool operator<(const Rva00388C0CElement&)const;bool operator==(const Rva00388C0CElement&)const; };
// Instantiate only the rowed member, not the whole set: the rest of the
// container referenced element operations no unit defines.
typedef _STL::_Rb_tree<Rva00388C0CElement, Rva00388C0CElement,
	_STL::_Identity<Rva00388C0CElement>, _STL::less<Rva00388C0CElement>,
	_STL::allocator<Rva00388C0CElement> > Rva00388C0CTree;
template Rva00388C0CTree::_Link_type Rva00388C0CTree::_S_minimum(Rva00388C0CTree::_Link_type);
