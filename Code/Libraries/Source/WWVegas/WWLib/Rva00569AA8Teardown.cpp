// cl: /O1 /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// ?rva00569AA8@Rva00569AA8@@QAEXXZ @0x00569AA8 21B
// Linkbody 27B: clears +0x64 via and-zero then rowed teardown 0x5694CD then tail-jmps to rowed Rb_tree clear 0x56926C for +0x20 member.
// Evidence: retail push esi; mov esi,ecx; and [esi+0x64],0; call 0x5694CD; lea ecx,[esi+0x20]; pop esi; jmp 0x56926C. Callers 0x3EDC21 rowed and 0x3EDC85 unclaimed.
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>
struct Rva00568FE4Key { float x; float y; unsigned short w; unsigned short pad; };
namespace _STL {
// Nothing here calls the set's node deallocation out of line; its unreferenced
// copies differed from the first ones in link order. Declared imported and
// force-inlined, they are not emitted.
template <> __declspec(dllimport) __forceinline
void allocator<_Rb_tree_node<Rva00568FE4Key> >::deallocate(_Rb_tree_node<Rva00568FE4Key> *__p, size_t) const
{ if (__p != 0) ::free((void *)__p); }
template <> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<_Rb_tree_node<Rva00568FE4Key> *, _Rb_tree_node<Rva00568FE4Key>, allocator<_Rb_tree_node<Rva00568FE4Key> > >::deallocate(_Rb_tree_node<Rva00568FE4Key> *__p, size_t __n)
{ __stl_alloc_rebind(__STATIC_CAST(_Base&, *this),(_Rb_tree_node<Rva00568FE4Key>*)0).deallocate(__p, __n); }
}
struct Rva00568FE4Less {
  bool operator()(const Rva00568FE4Key &a, const Rva00568FE4Key &b) const {
    if (a.x < b.x) return false;
    if (a.x > b.x) return true;
    if (a.y < b.y) return false;
    if (a.y > b.y) return true;
    return a.w < b.w;
  }
};
typedef _STL::_Rb_tree<Rva00568FE4Key, Rva00568FE4Key, _STL::_Identity<Rva00568FE4Key>, Rva00568FE4Less, _STL::allocator<Rva00568FE4Key> > Rva00568FE4Tree;

class Rva00569393
{
public:
	void rva005694CD();
};

class Rva00569AA8
{
public:
	void rva00569AA8();
private:
	char m_pad00[0x20];
	Rva00568FE4Tree m_20;
	char m_padAfter[0x44 - sizeof(Rva00568FE4Tree)];
	int m_64;
};

void Rva00569AA8::rva00569AA8()
{
	m_64 &= 0;
	((Rva00569393 *)this)->rva005694CD();
	return m_20.clear();
}
