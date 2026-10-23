// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva0030BA8C@Rva0030BA8C@@QAEXABUBfmeE8@@@Z, retail 0x0030BA8C, 20 bytes.
// Holder push via rowed vector E8 push_back 0x00539A2E plus flag at +0x24 set to 1.
// Evidence: callers 0x0030BAB7 0x003290F7 0x00330AC8; prev clear 0x0030B9CA same flags next Disp8Lea no-flags.
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
struct BfmeE8 { int a[2]; };
// bfme link decl-only begin
// The rowed body calls the 8-byte push_back 0x00539A2E
// (stlport_vector_e8_allocate_copy.cpp); this unit's /EH copy of its
// _M_insert_overflow is not retail's 0x00057C80, so it emits neither.
namespace _STL { template <> void vector<BfmeE8, allocator<BfmeE8> >::push_back(BfmeE8 const &); }
// bfme link decl-only end

struct Rva0030BA8C
{
	void rva0030BA8C(const BfmeE8 &val);
	_STL::vector<BfmeE8, _STL::allocator<BfmeE8> > m_vec;
	char m_pad[0x24 - 12];
	bool m_flag;
};

void Rva0030BA8C::rva0030BA8C(const BfmeE8 &val)
{
	m_vec.push_back(val);
	m_flag = true;
}
