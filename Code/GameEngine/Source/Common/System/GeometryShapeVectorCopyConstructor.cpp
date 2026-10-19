// cl: /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii
// stlport
// Open-BFME: vector<GeometryShape> copy constructor, retail 0x000FDE60.
//
// GeometryInfo's exact copy constructor calls this body through ILT
// 0x00027570 for its +0x2C member.  The element layout and memberwise copy are
// independently exact in GeometryShapeCopyConstructor.cpp: seven dwords,
// StringBase<char> at +0x1C, and the enabled byte at +0x20.
// The explicit instantiation also emits the canonical get_allocator,
// allocator-proxy, and vector-base dependencies at 0x000FCB00, 0x000FCCD0,
// and 0x000FD230.

// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#define _STLP_BFME_COPY_TRIVIAL_EXTERN  // call retail's one __copy_trivial (vendor/stlport/stl/_algobase.h)
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>
#include "ascii_string.h"

typedef bool Bool;

#include "../../../../Libraries/Include/Lib/Coord3D.h"
// Keep __node_alloc<true,0>::deallocate inline-only: every call here is inlined,
// and this TU's /O1 COMDAT copy differs from the copy the link keeps.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _STLP_CALL __node_alloc<true, 0>::deallocate(void *__p, size_t __n)
{ if (__n > (size_t)_MAX_BYTES) __stl_delete(__p); else _M_deallocate(__p, __n); }
}

struct GeometryShape
{
	int m_type;
	float m_height;
	float m_majorRadius;
	float m_minorRadius;
	Coord3D m_centerOffset;
	AsciiString m_name;
	Bool m_enabled;
	char m_unmodelled21[0x03];

	GeometryShape();
	~GeometryShape();
	GeometryShape(const GeometryShape &other);
public:
	GeometryShape &operator=(const GeometryShape &);
};

template class _STL::vector<GeometryShape>;

// erase (retail 0x002B0CB0) and its __copy_ptrs forwarder (0x002B0B71) are
// not GeometryShape's: retail erase destroys the vacated tail element through
// 0x002AF1EC (vector<AsciiString> at +0x14, buffer at +8, AsciiString at +0)
// and the __copy loop (0x002AF6C5) assigns through 0x002AF505, where
// GeometryShape's own dtor is the 0x00255D17 tail jump (GeometryInfo's
// shape-vector dtor 0x00050A79 reaches it per 0x24 element) and its assign
// is 0x00063627.  Opaque view of that other 0x24-byte record.
struct Rva002AF6C5Element
{
	~Rva002AF6C5Element();
	Rva002AF6C5Element &operator=(const Rva002AF6C5Element &other);

	unsigned char m_pad[0x24];
};

template Rva002AF6C5Element *_STL::vector<Rva002AF6C5Element>::erase(Rva002AF6C5Element *);
