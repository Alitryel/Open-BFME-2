// cl: /Ireference/shims/bfmelist /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?Rva002AAC9EEqual@@YAHPBURva002AAC9ERange@@0@Z @0x002AAC9E 61B: float-range equal via size xor plus Rva002AA32FEqual; caller 0x002ADC03 pushes 2 ptrs; unblocks 0x002ADC03.
struct Rva002AAC9ERange
{
	float const* m_begin;
	float const* m_end;
};

bool __cdecl Rva002AA32FEqual(float const* first, float const* last, float const* other);

int __cdecl Rva002AAC9EEqual(Rva002AAC9ERange const* lhs, Rva002AAC9ERange const* rhs)
{
	int aSize = (char const*)lhs->m_end - (char const*)lhs->m_begin;
	int bSize = (char const*)rhs->m_end - (char const*)rhs->m_begin;
	if ((((aSize ^ bSize) & -4) == 0) && Rva002AA32FEqual(lhs->m_begin, lhs->m_end, rhs->m_begin))
		return 1;
	return 0;
}
