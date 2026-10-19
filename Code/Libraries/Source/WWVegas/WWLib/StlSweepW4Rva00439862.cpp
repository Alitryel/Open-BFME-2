// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
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
// The rowed caller Rva00243177::rva00439965 (0x00439965) erases ObjectID keys
// from the manager's int-keyed record map, so the element is a trivial 4-byte
// key compared as a signed int (retail's bound bodies 0x00382A92/0x004FF471
// are the int-int map twins). The donor's declared ctor/copy/assign/dtor were
// over-specification that left ??1Rva00439862Element@@QAE@XZ unresolved; make
// the element trivial and give the free operator< the inlined int compare.
struct Rva00439862Element {
 int m_key;
 char m_pad[4];
};
inline bool operator<(const Rva00439862Element &left, const Rva00439862Element &right)
{
 return left.m_key < right.m_key;
}

// Instantiate the recovered operation and its required template dependencies.
template unsigned int _STL::_Rb_tree<Rva00439862Element, Rva00439862Element, _STL::_Identity<Rva00439862Element>, _STL::less<Rva00439862Element>, _STL::allocator<Rva00439862Element> >::erase(Rva00439862Element const &);
