// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva00566D7B@Rva00566D7B@@QAEXABVRva004E32F2@@@Z retail 0x00566D7B 8B
// Evidence: chain lane callee push_back Rva004E32F2 0x00566BB4; add ecx 0x60 plus jmp tail same shape as rowed 0x00566AB7.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>
class Rva004E32F2
{
public:
	Rva004E32F2(const Rva004E32F2 &o);
	virtual ~Rva004E32F2();
private:
	char m_pad[0x14];
};
class Rva00566D7B
{
public:
	void rva00566D7B(const Rva004E32F2 &v);
private:
	char m_pad00[0x60];
	_STL::vector<Rva004E32F2> m_vec60;
};
// bfme link decl-only begin
namespace _STL { template <> void _Destroy<Rva004E32F2 *>(Rva004E32F2 *,Rva004E32F2 *); }
namespace _STL { template <> void _Destroy<Rva004E32F2>(Rva004E32F2 *); }
namespace _STL { template <> void __destroy<Rva004E32F2 *,Rva004E32F2>(Rva004E32F2 *,Rva004E32F2 *,Rva004E32F2 *); }
namespace _STL { template <> void __destroy_aux<Rva004E32F2 *>(Rva004E32F2 *,Rva004E32F2 *,_STL::__false_type const &); }
namespace _STL { template <> Rva004E32F2 * __uninitialized_copy<Rva004E32F2 *,Rva004E32F2 *>(Rva004E32F2 *,Rva004E32F2 *,Rva004E32F2 *,_STL::__false_type const &); }
namespace _STL { template <> Rva004E32F2 * __uninitialized_fill_n<Rva004E32F2 *,unsigned int,Rva004E32F2>(Rva004E32F2 *,unsigned int,Rva004E32F2 const &,_STL::__false_type const &); }
namespace _STL { template <> void vector<Rva004E32F2,_STL::allocator<Rva004E32F2> >::_M_insert_overflow(Rva004E32F2 *,Rva004E32F2 const &,_STL::__false_type const &,unsigned int,bool); }
namespace _STL { template <> void vector<Rva004E32F2,_STL::allocator<Rva004E32F2> >::push_back(Rva004E32F2 const &); }
// bfme link decl-only end
void Rva00566D7B::rva00566D7B(const Rva004E32F2 &v)
{
	m_vec60.push_back(v);
}
