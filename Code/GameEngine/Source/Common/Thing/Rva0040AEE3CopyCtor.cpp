// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva0040AEE3@@QAE@ABV0@@Z @0x0040AEE3 27B
// Evidence: unlock lane; calls rowed vector<ScienceType> copy 0x0054878E; copies int at +0xC; caller 0x0040B16A.
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

// The science vector's assignment is the rowed body at 0x0021C21B
// (StlSweepW5Rva0021C21B.cpp); call it by that row's name.
struct Rva0021C21BElement { char bytes[4]; };
namespace _STL { template <> vector<Rva0021C21BElement, allocator<Rva0021C21BElement> > &vector<Rva0021C21BElement, allocator<Rva0021C21BElement> >::operator=(const vector<Rva0021C21BElement, allocator<Rva0021C21BElement> > &); }

enum ScienceType
{
	SCIENCE_NONE = 0
};

class Rva0040AEE3
{
public:
	Rva0040AEE3(const Rva0040AEE3 &other);
	Rva0040AEE3 &operator=(const Rva0040AEE3 &other);
private:
	_STL::vector<ScienceType> m_0000;
	int m_000C;
};

Rva0040AEE3::Rva0040AEE3(const Rva0040AEE3 &other)
	: m_0000(other.m_0000)
	, m_000C(other.m_000C)
{
}

Rva0040AEE3 &Rva0040AEE3::operator=(const Rva0040AEE3 &other)
{
	if (&other != this) {
		// Folded 4-byte assign 0x0021C21B, rowed under its element view's name.
		(_STL::vector<Rva0021C21BElement> &)m_0000 = (const _STL::vector<Rva0021C21BElement> &)other.m_0000;
		m_000C = other.m_000C;
	}
	return *this;
}
