// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva00501DD4Sub@@QAE@ABU0@@Z @0x005017B4 95B: Sub copy ctor copying 5 dwords plus two vectors; evidence rowed vector copy 0x00500DA0 twice rowed EH_prolog 0x00629188 callers 0x0050182D 0x0050185E 0x00501DE6 0x00501E0B and dtor layout 0x00501776
#include <vector>

struct Rva00501E3FElement
{
	unsigned int m_data[5];
	~Rva00501E3FElement();
};

struct Rva00501776
{
	int m_00;
	int m_04;
	int m_08;
	int m_0c;
	int m_10;
	_STL::vector<Rva00501E3FElement> m_14;
	_STL::vector<Rva00501E3FElement> m_20;
	Rva00501776(const Rva00501776 &that);
};

// bfme link decl-only begin
namespace _STL { template <> void _Construct<Rva00501E3FElement,Rva00501E3FElement>(Rva00501E3FElement *,Rva00501E3FElement const &); }
namespace _STL { template <> vector<Rva00501E3FElement,_STL::allocator<Rva00501E3FElement> >::~vector(); }
namespace _STL { template <> Rva00501E3FElement * __uninitialized_copy<Rva00501E3FElement const *,Rva00501E3FElement *>(Rva00501E3FElement const *,Rva00501E3FElement const *,Rva00501E3FElement *,_STL::__false_type const &); }
namespace _STL { template <> vector<Rva00501E3FElement,_STL::allocator<Rva00501E3FElement> >::vector(_STL::vector<Rva00501E3FElement,_STL::allocator<Rva00501E3FElement> > const &); }
// bfme link decl-only end
Rva00501776::Rva00501776(const Rva00501776 &that)
	: m_00(that.m_00)
	, m_04(that.m_04)
	, m_08(that.m_08)
	, m_0c(that.m_0c)
	, m_10(that.m_10)
	, m_14(that.m_14)
	, m_20(that.m_20)
{
}
