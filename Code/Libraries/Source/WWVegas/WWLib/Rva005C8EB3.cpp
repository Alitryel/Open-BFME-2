// cl: /ICode/Libraries/Include /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva005C8EB3@@QAE@PAX@Z @0x005C8EB3 100B
// __thiscall ctor: copies 8 bytes from src at +0/+4, zeros +8, default-builds
// map<int,void*> at +0x2c via rowed 0x0033C432 and vector<BfmeE16> at +0x38
// via rowed Vector_base 0x00211E58 with explicit allocator temp at [ebp+0xb],
// zeros word at +0x44, byte at +0x46, sets 0x80 at +0x47, memsets 32B at +0xc.
// Evidence: callees rowed; caller 0x005C865B; layout size 0x48 matches
// Rva005C87F8Adjust sibling (8-dword array at +0xc, trailing bytes +0x46/+0x47).
#include "Lib/BfmeE16.h"
#include <map>
#include <vector>

struct Base0C
{
	Base0C(void *src)
	{
		m_00 = ((int *)src)[0];
		m_04 = ((int *)src)[1];
	}
	int m_00;
	int m_04;
};
class BfmePoolRef10
{
public:
	BfmePoolRef10() : m_ptr(0) {}
	~BfmePoolRef10();
	void *m_ptr;
};

// The map<int,void*> destructor otherwise emits this unit's own copy, which is
// not retail's body; the call links to the kept retail definition.
namespace _STL {
template <> _Rb_tree<int, pair<const int, void *>, _Select1st<pair<const int, void *> >, less<int>, allocator<pair<const int, void *> > >::~_Rb_tree();
}

class Rva005C8EB3 : public Base0C
{
public:
	Rva005C8EB3(void *src);
private:
	BfmePoolRef10 m_ref;
	int m_buf[8];
	_STL::map<int, void *, _STL::less<int>, _STL::allocator<_STL::pair<const int, void *> > > m_map;
	_STL::vector<BfmeE16, _STL::allocator<BfmeE16> > m_vec;
	unsigned short m_44;
	unsigned char m_46;
	signed char m_47;
};

Rva005C8EB3::Rva005C8EB3(void *src)
	: Base0C(src)
	, m_vec(_STL::allocator<BfmeE16>())
	, m_44(0)
	, m_46(0)
	, m_47((signed char)0x80)
{
	for (int i = 0; i < 8; i++)
		m_buf[i] = 0;
}
