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
// The element is the HotKey map's 8-byte value pair<const AsciiString,
// TreeHintRef00217D4C>: the rowed Rva00358B65 destructor 0x00358B65 tears it
// down (StringBase narrow at +0 via releaseBuffer, TargetRef at +4), and the
// rowed free AsciiString operator< 0x0005598C (AsciiStringLess.cpp) is its
// comparison. The declared-only element dtor and operator< otherwise left
// ??1Rva003597C3Element@@QAE@XZ and ??M@YA_NABURva003597C3Element@@0@Z
// unresolved, so bind both to those rowed owners as inline views.
struct Rva00358B65 { ~Rva00358B65(); };
class AsciiString;
bool __cdecl operator<(const AsciiString &left, const AsciiString &right);
struct Rva003597C3Element {
 Rva003597C3Element(); Rva003597C3Element(const Rva003597C3Element&);
 ~Rva003597C3Element() { ((Rva00358B65 *)this)->Rva00358B65::~Rva00358B65(); }
 Rva003597C3Element&operator=(const Rva003597C3Element&);
 char bytes[8];
};
inline bool operator<(const Rva003597C3Element &left, const Rva003597C3Element &right)
{
 return operator<(*reinterpret_cast<const AsciiString *>(&left),
                  *reinterpret_cast<const AsciiString *>(&right));
}

// Instantiate the recovered operation and its required template dependencies.
template unsigned int _STL::_Rb_tree<Rva003597C3Element, Rva003597C3Element, _STL::_Identity<Rva003597C3Element>, _STL::less<Rva003597C3Element>, _STL::allocator<Rva003597C3Element> >::erase(Rva003597C3Element const &);
