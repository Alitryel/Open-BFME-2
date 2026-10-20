// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?_M_insert_overflow@?$vector@VRva001ED03C@@V?$allocator@VRva001ED03C@@@_STL@@@_STL@@IAEXPAVRva001ED03C@@ABV3@ABU__false_type@2@I_N@Z @0x001ED476 183B.
// STLport vector<Rva001ED03C> growth path; same 183B shape as rowed 0x001ED13A for 36-byte element.
// Evidence: callees rowed 0x005DFB2C 0x001ED21E 0x001ED1F1 0x001ED244 0x001ED3A2; caller 0x001ED576; imul 0x24 stride.
// Retail keeps one unsigned max, RVA 0x00013740 (the vendored STLport row). This unit's
// flags (/G7) compile a different copy, and retail kept another unit's. This unit-local
// overload keeps the inlined code and offers the link no second copy.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#define _STLP_NO_EXCEPTIONS 1
#include <vector>

class Rva001ED03C
{
	char m_body[0x24];
public:
	Rva001ED03C(const Rva001ED03C &that);
	~Rva001ED03C();
};

// The native clear at 1ED3A2 calls the rowed 1ED34A destruction loop,
// whose 36-byte record destructor is 1ED0DE. The copy and destructor
// address names describe the same campaign record (see its parser).
class Rva001ED0DE
{
public:
    ~Rva001ED0DE();
private:
    unsigned char unknown[0x24];
};
extern "C" void __cdecl free(void *);

namespace _STL
{
template <> void _Construct<Rva001ED03C, Rva001ED03C>(Rva001ED03C *, const Rva001ED03C &);
template <> void _Destroy<Rva001ED0DE *>(Rva001ED0DE *, Rva001ED0DE *);
template <> __declspec(noinline) inline void vector<Rva001ED03C>::_M_clear()
{
    _STL::_Destroy((Rva001ED0DE *)_M_start, (Rva001ED0DE *)_M_finish);
    Rva001ED0DE *storage = (Rva001ED0DE *)_M_start;
    if (storage != 0) free(storage);
}
}

template void _STL::vector<Rva001ED03C>::_M_insert_overflow(
    Rva001ED03C *, const Rva001ED03C &, const _STL::__false_type &, unsigned int, bool);
// ?push_back@?$vector@VRva001ED03C@@V?$allocator@VRva001ED03C@@@_STL@@@_STL@@QAEXABVRva001ED03C@@@Z @0x001ED549 55B.
// STLport vector<Rva001ED03C>::push_back over growth path 0x001ED476.
// Evidence: callees rowed 0x001ED1F1 0x001ED476; caller 0x001ED5F3; add 0x24 stride.
template void _STL::vector<Rva001ED03C>::push_back(const Rva001ED03C &);
