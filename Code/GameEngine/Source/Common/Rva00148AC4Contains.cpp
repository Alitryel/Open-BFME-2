// cl: /O1
// stlport
// ?Rva00148AC4Contains@@YAEPAURva00148AC4Range@@PAVCreateAHeroData@@@Z @0x00148AC4 31B. Free-function contains via rowed _STL::find 0x0020E873 over range at +0/+4 returns found != end.
// Evidence: retail find call with [eax] [eax+4] and lea ecx stack ref plus cmp eax esi setne al; callers 0x00149073 0x001490C9; LINK BONUS via 0x00149002; model mirrors Rva003F0DA5Contains.
#include <algorithm>

class CreateAHeroData;

struct Rva00148AC4Range
{
	CreateAHeroData **m_first;
	CreateAHeroData **m_last;
};

unsigned char __cdecl Rva00148AC4Contains(Rva00148AC4Range *pRange, CreateAHeroData *pVal)
{
	return _STL::find(pRange->m_first, pRange->m_last, pVal) != pRange->m_last;
}
