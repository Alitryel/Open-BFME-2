// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva005335B0@Rva005335B0@@QAEXGG@Z @0x005335B0 35B.
// Tiny thiscall building a 4B Rva005334A4Element from two words then
// push_back to the vector at +0x38. Evidence: rowed push_back 0x005334A4
// callee; caller 0x005337CA in 1173B unclaimed; neighbours 0x005334A4 STL
// flags and 0x005335D3 reset share the page.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>

struct Rva005334A4Element
{
	unsigned short x;
	unsigned short y;
};
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> void vector<Rva005334A4Element,allocator<Rva005334A4Element> >::push_back(Rva005334A4Element const &); }
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> void vector<Rva005334A4Element,allocator<Rva005334A4Element> >::_M_insert_overflow(Rva005334A4Element *,Rva005334A4Element const &,__false_type const &,unsigned int,bool); }
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> Rva005334A4Element * __uninitialized_fill_n<Rva005334A4Element *,unsigned int,Rva005334A4Element>(Rva005334A4Element *,unsigned int,Rva005334A4Element const &,__false_type const &); }
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> Rva005334A4Element * __uninitialized_copy<Rva005334A4Element *,Rva005334A4Element *>(Rva005334A4Element *,Rva005334A4Element *,Rva005334A4Element *,__false_type const &); }

class Rva005335B0
{
public:
	void rva005335B0(unsigned short a, unsigned short b);
private:
	char m_pad[0x38];
	_STL::vector<Rva005334A4Element> m_vec;
};

void Rva005335B0::rva005335B0(unsigned short a, unsigned short b)
{
	Rva005334A4Element tmp;
	tmp.x = a;
	tmp.y = b;
	m_vec.push_back(tmp);
}
