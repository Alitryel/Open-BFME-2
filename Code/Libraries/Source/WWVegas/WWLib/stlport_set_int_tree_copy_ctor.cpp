// cl: /O2 /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// STLport 4.5.3 _Rb_tree<int,int,_Identity<int>,less<int>> copy constructor at
// retail 0x00620CA0 (207B).
//
// Target evidence: the header node is a 0x14-byte allocation through the byte
// allocator 0x307F0, and the recursive copy it calls (0x002CF6CF) clones nodes
// through 0x004ABCC9, which the ledger owns as the integer-set _M_create_node
// (single dword value at +0x10). That makes this the set<int> tree copy. The
// ledger still spells 0x002CF6CF and its assignment caller 0x002CF742 as
// pair<const int,int> names; the pin below adds the set<int> spelling for the
// same address rather than editing those rows.
#include <set>
// bfme link decl-only begin
namespace _STL { template <> _Rb_tree_node<int> * _Rb_tree<int, int, _Identity<int>, less<int>, allocator<int> >::_M_create_node(int const &); }
// bfme link decl-only end

typedef _STL::_Rb_tree<int, int, _STL::_Identity<int>, _STL::less<int>, _STL::allocator<int> > IntSetTree;

template IntSetTree::_Rb_tree(const IntSetTree &);

// set<int>'s own copy constructor, retail 0x00621020 (19B): _M_t(__x._M_t)
// through the tree copy above, kept out of line.
template _STL::set<int, _STL::less<int>, _STL::allocator<int> >::set(const _STL::set<int, _STL::less<int>, _STL::allocator<int> > &);

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??0Q1ReceiverTreeStorage@@QAE@ABV?$set@UGen_t_009ee8e0_k4@@U?$less@UGen_t_009ee8e0_k4@@@_STL@@V?$allocator@UGen_t_009ee8e0_k4@@@3@@_STL@@@Z=??0?$_Rb_tree@HHU?$_Identity@H@_STL@@U?$less@H@2@V?$allocator@H@2@@_STL@@QAE@ABV01@@Z")
