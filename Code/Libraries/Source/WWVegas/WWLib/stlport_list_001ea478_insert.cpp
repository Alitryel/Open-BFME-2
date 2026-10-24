// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?insert@?$list@UBfmeStringRecord001EA478@@V?$allocator@UBfmeStringRecord001EA478@@@_STL@@@_STL@@QAE?AU?$_List_iterator@UBfmeStringRecord001EA478@@U?$_Nonconst_traits@UBfmeStringRecord001EA478@@@_STL@@@2@U32@ABUBfmeStringRecord001EA478@@@Z @0x001EA958 37B
// list<BfmeStringRecord001EA478>::insert 37B calling rowed _M_create_node at
// 0x001EA507 then list hook insertion; identical shape to list<int>::insert
// at 0x005925E2 and TreeKey insert at 0x002A1BC6; caller 0x001EA9A7 in
// 0x001EA994; T is 8-byte record (two AsciiStrings in StringRecordCopyBFME2).
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}


struct BfmeStringRecord001EA478 { unsigned char m_data[8]; };
inline bool operator==(const BfmeStringRecord001EA478 &, const BfmeStringRecord001EA478 &) { return false; }
inline bool operator<(const BfmeStringRecord001EA478 &, const BfmeStringRecord001EA478 &) { return false; }

typedef _STL::list<BfmeStringRecord001EA478, _STL::allocator<BfmeStringRecord001EA478> > BfmeStringRecord001EA478List;
// Declared only: the single-node erase is retail's rowed body at 0x004E7B6E.
namespace _STL { template <> BfmeStringRecord001EA478List::iterator BfmeStringRecord001EA478List::erase(BfmeStringRecord001EA478List::iterator); }
template class _STL::list<BfmeStringRecord001EA478, _STL::allocator<BfmeStringRecord001EA478> >;

// The declared erase binds to that row (tools/allowed_symbols.py --alternatenames).
#pragma comment(linker, "/alternatename:?erase@?$list@UBfmeStringRecord001EA478@@V?$allocator@UBfmeStringRecord001EA478@@@_STL@@@_STL@@QAE?AU?$_List_iterator@UBfmeStringRecord001EA478@@U?$_Nonconst_traits@UBfmeStringRecord001EA478@@@_STL@@@2@U32@@Z=?Rva004E7B6EErase@@YGXPAPAXPAURva004E7B6ENode@@@Z")
