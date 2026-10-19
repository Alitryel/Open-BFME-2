// cl: /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??4Rva001DE727@@QAEAAV0@ABV0@@Z, retail 0x001DE727 85B chain.
// Evidence: 5 dwords + Rb_tree set at +0x14 via rowed assign 0x001DDC52 +
// 4B-POD vector at +0x20 via int pin at 0x0021C21B + 3 bytes at +0x2C.
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_BFME_RB_MINMAX_IMPORT  // inline _Rb_tree_node_base::_S_minimum/_S_maximum without a COMDAT copy (vendor/stlport/stl/_tree.h)
#include <map>
#include <vector>
// Suppress this TU's non-retail copy of ?_M_clear@?$vector@HV?$allocator@H@_STL@@@_STL@@IAEXXZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void vector<int, allocator<int> >::_M_clear(); }

// vector<int>/char destruction otherwise instantiates per-TU allocator
// deallocate COMDATs (one byte shape per TU flags); explicit
// dllimport+forceinline specializations take those calls inline so this
// TU emits no external copies. Bodies are verbatim primary.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void allocator<int>::deallocate(int* __p, size_t __n) const {
  _STLP_ASSERT( (__p == 0) == (__n == 0) )
    if (__p != 0) __sgi_alloc::deallocate((void*)__p, __n * sizeof(value_type));
}
template <> void _STLP_alloc_proxy<int*, int, allocator<int> >::deallocate(int*, size_t);
}

struct BfmeRecord001DD3BC
{
	unsigned char m_data[8];
};
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline void _Destroy<BfmeRecord001DD3BC>(BfmeRecord001DD3BC *p) { typedef BfmeRecord001DD3BC BfmeDestroyT; p->~BfmeDestroyT(); } }

bool operator<(const BfmeRecord001DD3BC &a, const BfmeRecord001DD3BC &b);

typedef _STL::_Rb_tree<BfmeRecord001DD3BC, BfmeRecord001DD3BC, _STL::_Identity<BfmeRecord001DD3BC>, _STL::less<BfmeRecord001DD3BC>, _STL::allocator<BfmeRecord001DD3BC> > BfmeRecord001DD3BCSetTree;

class Rva001DE727
{
public:
	Rva001DE727 &operator=(const Rva001DE727 &that);

private:
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	BfmeRecord001DD3BCSetTree m_set14; // +0x14
	_STL::vector<int, _STL::allocator<int> > m_vec20; // +0x20
	unsigned char m_2C;
	unsigned char m_2D;
	unsigned char m_2E;
};

Rva001DE727 &Rva001DE727::operator=(const Rva001DE727 &that)
{
	m_00 = that.m_00;
	m_04 = that.m_04;
	m_08 = that.m_08;
	m_0C = that.m_0C;
	m_10 = that.m_10;
	m_set14 = that.m_set14;
	m_vec20 = that.m_vec20;
	m_2C = that.m_2C;
	m_2D = that.m_2D;
	m_2E = that.m_2E;
	return *this;
}
