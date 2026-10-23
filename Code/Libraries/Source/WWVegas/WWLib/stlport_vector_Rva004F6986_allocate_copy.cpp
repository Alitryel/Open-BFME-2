// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ??$_M_allocate_and_copy@PAURva004F6986@@@?$vector@URva004F6986@@V?$allocator@URva004F6986@@@_STL@@@_STL@@IAEPAURva004F6986@@IPAU2@0@Z
// retail 0x004F6BD8, 45 bytes.
//
// Dedicated no-EH instantiation of vector<Rva004F6986>::_M_allocate_and_copy,
// the 8-byte-element body. Evidence: the matched reserve
// ?reserve@?$vector@URva004F6986@@ at 0x004F8B21 calls it, with `sar 3` in the
// caller confirming the 8-byte stride, and the allocator it calls is the
// address 0x00523D6C already pinned as the STLport 8-byte `allocate`.
// The copy worker it calls is pinned at 0x004F6A88 as the __uninitialized_copy
// instantiation over that same element type, so the emitted callee name is the
// stock stlport one rather than a hand-rolled shim's.
//
// Spelled with the stock stlport headers and an explicit instantiation of the
// whole class, as stlport_vector_e8_allocate_copy.cpp does, which is what makes
// the emitted __uninitialized_copy symbol resolve to retail's.

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

struct Rva004F6986
{
	~Rva004F6986();
	char m_pad[8];
};

// Native 4F6A52 constructs the two counted handles through 44BD00;
// an implicit byte copy of the opaque eight-byte view loses both AddRefs.
class Rva004C5DD0
{
public:
	Rva004C5DD0(const Rva004C5DD0 &) throw();
private:
	void *m_handles[2];
};
namespace _STL {
template <> __declspec(noinline) inline void _Construct<Rva004F6986, Rva004F6986>(Rva004F6986 *dest, const Rva004F6986 &source)
{
	if (dest)
		new ((void *)dest) Rva004C5DD0(*(const Rva004C5DD0 *)&source);
}
}

template class _STL::vector<Rva004F6986, _STL::allocator<Rva004F6986> >;
