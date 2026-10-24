// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common

class Rva00160CE0
{
	void *m_00;
	int m_04;
	int m_player;
	char m_match;
	int m_affiliation;

public:
	Rva00160CE0 &set(int a, int b, char c);
};

// Retail vtable VA 0x0109689C; the alternate name defines no table.
extern "C" void *bfmeVftPartitionFilterPlayerAffiliation[];
#pragma comment(linker, "/alternatename:_bfmeVftPartitionFilterPlayerAffiliation=??_7Rva00261409Filter@@6B@")

Rva00160CE0 &Rva00160CE0::set(int a, int b, char c)
{
	m_player = a;
	m_04 = 0;
	m_00 = bfmeVftPartitionFilterPlayerAffiliation;
	m_match = c;
	m_affiliation = b;
	return *this;
}
