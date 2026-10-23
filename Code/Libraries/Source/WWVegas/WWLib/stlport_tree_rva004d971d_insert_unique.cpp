// cl: /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?insert_unique@?$_Rb_tree@IVRva004D971D@@URva004DA0B7OrderKey@@U?$less@I@_STL@@V?$allocator@VRva004D971D@@@4@@_STL@@QAE?AU?$pair@U?$_Rb_tree_iterator@VRva004D971D@@U?$_Nonconst_traits@VRva004D971D@@@_STL@@@_STL@@_N@2@ABVRva004D971D@@@Z @0x004DA264 134B: insert_unique for unsigned-key Rva004D971D tree via rowed _M_insert 0x004DA0B7 plus _M_decrement 0x000242C0. Evidence: same 134B leaf shape as PodMap insert_unique 0x00422918 same calls; unsigned first-dword compare; callers at 0x004DA34A and 0x004DBC6F.
#include <map>

// The unsigned compare is inlined into insert_unique (retail compares in
// place); an inline-only specialization keeps it there and emits no
// less<unsigned>::operator() copy in a shape retail's 0x00758C50 lacks.
namespace _STL {
template <> __declspec(dllimport) __forceinline bool less<unsigned>::operator()(const unsigned &a, const unsigned &b) const { return a < b; }
}

// __malloc_alloc<0> allocate/deallocate otherwise instantiate per-TU
// COMDATs (one byte shape per TU malloc/free wiring); explicit
// dllimport+forceinline specializations take those calls inline so this
// TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void *__malloc_alloc<0>::allocate(size_t __n)
{ void *__r = malloc(__n); if (!__r) __r = _S_oom_malloc(__n); return __r; }
template <> __declspec(dllimport) __forceinline
void __malloc_alloc<0>::deallocate(void *__p, size_t)
{ free((char *)__p); }
}
class Rva004D971D
{
	char m_opaque[40];
public:
	__declspec(nothrow) Rva004D971D(const Rva004D971D &);
	~Rva004D971D();
};
struct Rva004DA0B7OrderKey
{
	const unsigned &operator()(const Rva004D971D &v) const
	{
		return *reinterpret_cast<const unsigned *>(&v);
	}
};
typedef _STL::_Rb_tree<unsigned, Rva004D971D, Rva004DA0B7OrderKey, _STL::less<unsigned>, _STL::allocator<Rva004D971D> > Rva004DA0B7Tree;
// _M_insert calls the rowed _M_create_node 0x004D9CD1
// (stlport_tree_rva004d971d.cpp); declaring the specialization keeps this
// unit from emitting its own differing copy.
namespace _STL {
template <> _Rb_tree_node<Rva004D971D> *Rva004DA0B7Tree::_M_create_node(const Rva004D971D &);
}
template _STL::pair<Rva004DA0B7Tree::iterator, bool> Rva004DA0B7Tree::insert_unique(const Rva004D971D &);

// Retail 0x004DA342 (20B, RET 8): an insert over the same tree held at +0
// that forwards the hidden return pair and the value straight to the
// insert_unique above. The owner's identity is not established; its name is
// address-derived.
class Rva004DA342Map
{
public:
	_STL::pair<Rva004DA0B7Tree::iterator, bool> insert(const Rva004D971D &value);
private:
	Rva004DA0B7Tree m_tree;
};

_STL::pair<Rva004DA0B7Tree::iterator, bool> Rva004DA342Map::insert(const Rva004D971D &value)
{
	return m_tree.insert_unique(value);
}
