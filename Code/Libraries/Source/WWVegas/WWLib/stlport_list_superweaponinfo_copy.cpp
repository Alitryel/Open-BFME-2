// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element name is donor-carried (ZH); the four-byte element is target evidence.
// cl: /O1 /G6 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <list>
#include <memory>

// _List_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _IterTp, class _LeftTraits, class _RightTraits>
static inline bool operator!=(const _List_iterator<_IterTp, _LeftTraits> &a,
                              const _List_iterator<_IterTp, _RightTraits> &b)
{ return a._M_node != b._M_node; }
}

// 0x002A1383: the copy constructor of the map value list whose only retail
// callers are the pair<const AsciiString, list> copies 0x002A1538/0x002A1CC9
// (hinted insert 0x002A5895, InGameUI's TU region). Element name from ZH
// InGameUI.h (SuperweaponList = list<SuperweaponInfo *>); its twin 0x00445E8B
// (same calls, own EH table) is the tab-list copy rowed as list<int>.
class SuperweaponInfo;
template _STL::list<SuperweaponInfo *>::list(const _STL::list<SuperweaponInfo *> &);
// The single-element insert 0x005925E2 is emitted by stlport_list_superweaponinfo_insert.cpp;
// here it stays an external call from the range-insert dispatch, as in retail.
namespace _STL {
template<> list<SuperweaponInfo *>::iterator list<SuperweaponInfo *>::insert(list<SuperweaponInfo *>::iterator, SuperweaponInfo *const &);
template list<SuperweaponInfo *>::_Node *list<SuperweaponInfo *>::_M_create_node(SuperweaponInfo *const &);
}
