// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// STLport4.5.3 single-element insertion of list<SuperweaponInfo *> (element name
// donor-carried from ZH InGameUI.h). Retail 0x5925E2 calls the 29B node creator
// 0xB6447, then links its next/previous pointers and returns the iterator through
// the hidden result. Keep the node creator in its provider
// (stlport_list_superweaponinfo_copy.cpp) instead of inlining it here.
#include <list>
class SuperweaponInfo;
namespace _STL {
template<> list<SuperweaponInfo *>::_Node *list<SuperweaponInfo *>::_M_create_node(SuperweaponInfo *const &);
template list<SuperweaponInfo *>::iterator list<SuperweaponInfo *>::insert(list<SuperweaponInfo *>::iterator, SuperweaponInfo *const &);
}
