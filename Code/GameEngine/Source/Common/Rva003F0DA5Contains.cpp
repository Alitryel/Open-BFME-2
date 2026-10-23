// flags: region default (reverse/retail_inventory/flag_regions.csv)
// stlport
// ?rva003F0DA5@Rva003F0DA5@@QAE_NPAVCreateAHeroData@@@Z, retail 0x003F0DA5, 33 bytes.
// __thiscall bool contains via rowed _STL::find at 0x0020E873 over CreateAHeroData*
// range at +0/+4, returns found != end. Evidence: find row, caller 0x003F11EC passes
// element at +0/+4 shape with this from vector element, unlocks 0x003F11EC.
#include <algorithm>

class CreateAHeroData;

struct Rva003F1232Arg
{
	char m_pad00[0x2C];
	CreateAHeroData *m_data2C;	// +0x2C
};

class Rva003F0DA5
{
public:
	bool rva003F0DA5(CreateAHeroData *val);
	bool rva003F1232(const Rva003F1232Arg *arg);
private:
	CreateAHeroData **m_first;
	CreateAHeroData **m_last;
};

bool Rva003F0DA5::rva003F0DA5(CreateAHeroData *val)
{
	CreateAHeroData **found = _STL::find(m_first, m_last, val);
	return found != m_last;
}

// ?rva003F1232@Rva003F0DA5@@QAE_NPBURva003F1232Arg@@@Z, retail 0x003F1232,
// 15 bytes: the contains test above applied to the argument's +0x2C
// CreateAHeroData pointer (its call at 0x003F1239). Skeleton twin of
// LivingWorldBattle::rva003F48EF 0x003F48EF (Rva003F498ALoops.cpp).
bool Rva003F0DA5::rva003F1232(const Rva003F1232Arg *arg)
{
	return rva003F0DA5(arg->m_data2C);
}
