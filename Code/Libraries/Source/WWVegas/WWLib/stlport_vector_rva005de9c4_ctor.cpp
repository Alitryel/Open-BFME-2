// cl: /Ireference/shims/bfme2_ascii /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??0Rva005DE9E3@@QAE@I@Z @0x005DE9C4 31B
// Gap ctor: vtable 0x00876AFC plus Gen vector at +4 via rowed 0x005DE870 plus zero at +0x10.
// Evidence: between rows of stlport_vector_rva005de5b5_dtor.cpp; callee rowed 0x005DE870;
// Table C76AFC is owned by the rowed Rva005DE9E3 destructor; callers 0x005DEA09 0x005DEC0C 0x005DEE4B.
#include <vector>
// Suppress this TU's non-retail copy of ??1?$_Vector_base@UGen003AA0D0@@V?$allocator@UGen003AA0D0@@@_STL@@@_STL@@QAE@XZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Gen003AA0D0;
namespace _STL { template <> _Vector_base<Gen003AA0D0,allocator<Gen003AA0D0> >::~_Vector_base(); }
// Suppress this TU's non-retail copy of ??$_Construct@UGen003AA0D0@@U1@@_STL@@YAXPAUGen003AA0D0@@ABU1@@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Gen003AA0D0;
namespace _STL { template <> void _Construct<Gen003AA0D0,Gen003AA0D0>(Gen003AA0D0 *,Gen003AA0D0 const &); }
// Suppress this TU's non-retail copy of ?allocate@?$_STLP_alloc_proxy@PAUGen003AA0D0@@U1@V?$allocator@UGen003AA0D0@@@_STL@@@_STL@@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Gen003AA0D0;
namespace _STL { template <> Gen003AA0D0 * _STLP_alloc_proxy<Gen003AA0D0 *,Gen003AA0D0,allocator<Gen003AA0D0> >::allocate(unsigned int); }
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@UGen003AA0D0@@@_STL@@QBEXPAUGen003AA0D0@@I@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Gen003AA0D0;
namespace _STL { template <> void allocator<Gen003AA0D0>::deallocate(Gen003AA0D0 *,unsigned int) const; }
// Suppress this TU's non-retail copy of ?allocate@?$allocator@UGen003AA0D0@@@_STL@@QBEPAUGen003AA0D0@@IPBX@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Gen003AA0D0;
namespace _STL { template <> Gen003AA0D0 * allocator<Gen003AA0D0>::allocate(unsigned int,void const *) const; }

struct Gen003AA0D0
{
	virtual ~Gen003AA0D0();
	char m_pad[0x18 - 4];
};

class Rva005DE9E3
{
public:
	Rva005DE9E3(unsigned int n);
	virtual ~Rva005DE9E3();
private:
	_STL::vector<Gen003AA0D0, _STL::allocator<Gen003AA0D0> > m_04;
	int m_10;
};

Rva005DE9E3::Rva005DE9E3(unsigned int n)
	: m_04(n)
{
	m_10 = 0;
}
