// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0?$list@UBfmeStringRecord002B4DC1@@V?$allocator@UBfmeStringRecord002B4DC1@@@_STL@@@_STL@@QAE@I@Z @ 0x002B8FF3 (106B).
// list<BfmeStringRecord002B4DC1> fill ctor size_type only; List_base via folded Coord3D row 0x00280A8D,
// fill insert via rowed 0x002B815B, wide temp teardown via 0x00036E70. Evidence: callees rowed, shape matches
// list<UnicodeString> fill ctor precedent 0x0043C072.
#include <list>
// Suppress this TU's non-retail copy of ?_M_create_node@?$list@UBfmeStringRecord002B4DC1@@V?$allocator@UBfmeStringRecord002B4DC1@@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmeStringRecord002B4DC1;
namespace _STL { template <> _List_node<BfmeStringRecord002B4DC1> * list<BfmeStringRecord002B4DC1,allocator<BfmeStringRecord002B4DC1> >::_M_create_node(BfmeStringRecord002B4DC1 const &); }
// Suppress this TU's non-retail copy of ?clear@?$_List_base@UBfmeStringRecord002B4DC1@@V?$allocator@UBfmeStringRecord002B4DC1@@@_S:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmeStringRecord002B4DC1;
namespace _STL { template <> void _List_base<BfmeStringRecord002B4DC1,allocator<BfmeStringRecord002B4DC1> >::clear(); }

template <typename T> class StringBase
{
	friend struct BfmeStringRecord002B4DC1;
private:
	void releaseBuffer();
	void *m_data;
};

struct BfmeStringRecord002B4DC1
{
	StringBase<unsigned short> m_head;
	int m_a;
	int m_b;
	BfmeStringRecord002B4DC1() { m_head.m_data = 0; m_a = 0; m_b = 3; }
	~BfmeStringRecord002B4DC1() { m_head.releaseBuffer(); }
};
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline void _Construct<BfmeStringRecord002B4DC1,BfmeStringRecord002B4DC1>(BfmeStringRecord002B4DC1 *p,BfmeStringRecord002B4DC1 const &v) { new (p) BfmeStringRecord002B4DC1(v); } }

template _STL::list<BfmeStringRecord002B4DC1, _STL::allocator<BfmeStringRecord002B4DC1> >::list(unsigned int);
