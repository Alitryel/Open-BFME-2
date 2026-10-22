// cl: /EHsc /Ireference/shims/bfme2_ascii
// stlport
// ??4?$vector@UBfmeRecord0040B61A@@...@QAEAAV01@ABV01@@Z, retail 0x0040B61A, 186 bytes.
// Evidence: same bytes as vector<GeometryRecord>::operator= except two calls:
// the destroy reads the rowed Rva0040B52EDestroy at 0x0040B52E, which frees a
// narrow string at +0 of a 16-byte element, and the uninitialized copy reads
// 0x0040B2FD. Its other calls read the neighbouring 0x0040B323, 0x0040B350
// and the rowed destroy-and-free 0x0040B5DE. The element name is generated;
// the string at +0 and the 16-byte stride come from those bodies. The
// AsciiString member and the int fields are placeholders: the string's exact
// type and the remaining fields are not established. The flags follow
// GeometryRecordVector.cpp; /MD with the STLport static-lib defines adds a
// distance argument retail does not pass.
#include <vector>

#include "ascii_string.h"
// Suppress this TU's non-retail copy of ?allocate@?$_STLP_alloc_proxy@PAUBfmeRecord0040B61A@@U1@V?$allocator@UBfmeRecord0040B61A@@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmeRecord0040B61A;
namespace _STL { template <> BfmeRecord0040B61A * _STLP_alloc_proxy<BfmeRecord0040B61A *,BfmeRecord0040B61A,allocator<BfmeRecord0040B61A> >::allocate(unsigned int); }
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@UBfmeRecord0040B61A@@@_STL@@QBEXPAUBfmeRecord0040B61A@@I@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmeRecord0040B61A;
namespace _STL { template <> void allocator<BfmeRecord0040B61A>::deallocate(BfmeRecord0040B61A *,unsigned int) const; }
// Keep __node_alloc<true,0>::deallocate inline-only: every call here is inlined,
// and this TU's /O1 COMDAT copy differs from the copy the link keeps.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _STLP_CALL __node_alloc<true, 0>::deallocate(void *__p, size_t __n)
{ if (__n > (size_t)_MAX_BYTES) __stl_delete(__p); else _M_deallocate(__p, __n); }
}

struct BfmeRecord0040B61A
{
	AsciiString m_str;
	int m_04;
	int m_08;
	int m_0C;
};

template _STL::vector<BfmeRecord0040B61A, _STL::allocator<BfmeRecord0040B61A> > &
	_STL::vector<BfmeRecord0040B61A, _STL::allocator<BfmeRecord0040B61A> >::operator=(
		const _STL::vector<BfmeRecord0040B61A, _STL::allocator<BfmeRecord0040B61A> > &);
