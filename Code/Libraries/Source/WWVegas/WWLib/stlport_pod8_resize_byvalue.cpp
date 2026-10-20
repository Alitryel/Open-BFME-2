// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
//
// Pod8 vector resize with the fill value taken BY VALUE (retail 0x005FF96A,
// 63B, ends ret 0xC). STLport 4.5.3 only declares the const-ref resize, so
// this TU derives from the real _STL::vector<BfmePod8> instantiation (same
// headers and flags as stlport_pod_vector_malloc_bodies.cpp, whose prologue
// already matches retail through the erase call) and adds the by-value
// overload retail was built with. The by-value parameter is what emits
// retail's lea edi,[esp+0x10] plus push edi argument forwarding. Callees
// resolve to the rowed 2-argument erase (0x003FA4DB) and _M_fill_insert
// (0x000B02B6).
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

#include "../../../../GameEngine/Source/Common/BattlePromptArmyPanelClipImplView.h"
// Suppress this TU's non-retail copy of ?allocate@?$allocator@UBfmePod8@@@_STL@@QBEPAUBfmePod8@@IPBX@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod8;
namespace _STL { template <> BfmePod8 *allocator<BfmePod8>::allocate(size_t, const void *) const; }

void BfmePod8Vector::resize(unsigned int n, BfmePod8 x)
{
	if (n < size())
		erase(begin() + n, end());
	else
		_M_fill_insert(end(), n - size(), x);
}

// ?resize@BfmePod8Vector@@QAEXI@Z @ 0x000B0857 (23B). One-argument resize
// forwarding an indeterminate default pod to the rowed by-value resize
// above; the two filler pushes carry the incoming ecx. Callers 0x000B0DA8
// and 0x000B0F82.
void BfmePod8Vector::resize(unsigned int n)
{
	BfmePod8 x;
	resize(n, x);
}

// ?rva005FF9C5@Rva005FF9C5@@QAEXI@Z @ 0x005FF9C5 (19B). A second one-argument
// resize over the same vector, whose default pod is {0, -1}; it forwards to
// the rowed by-value resize 0x005FF96A. Owner type unrecovered.
class Rva005FF9C5 : public BfmePod8Vector
{
public:
	void rva005FF9C5(unsigned int n);
};

void Rva005FF9C5::rva005FF9C5(unsigned int n)
{
	BfmePod8 x;
	x.a[0] = 0;
	x.a[1] = -1;
	resize(n, x);
}
