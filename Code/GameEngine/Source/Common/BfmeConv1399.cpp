// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
// Open-BFME5 conversions.

class BfmeUniVKE
{
public:
	void bfmeCopyUVKE(const BfmeUniVKE &other);   // defined in another TU
	void *m_bfme00;
};

struct BfmeBlockVKE
{
	int m_bfmeArr[16];
};

class BfmeThingVKE
{
public:
	BfmeThingVKE *bfmeInitVKE(const BfmeThingVKE &other);
	BfmeUniVKE m_bfme00;
	char m_bfme04;
	char m_bfmePad05[3];
	int m_bfme08;
	int m_bfme0c;
	int m_bfme10;
	int m_bfme14;
	BfmeBlockVKE m_bfme18;
};

BfmeThingVKE *BfmeThingVKE::bfmeInitVKE(const BfmeThingVKE &other)
{
	m_bfme00.bfmeCopyUVKE(other.m_bfme00);
	m_bfme04 = other.m_bfme04;
	m_bfme08 = other.m_bfme08;
	m_bfme0c = other.m_bfme0c;
	m_bfme10 = other.m_bfme10;
	m_bfme14 = other.m_bfme14;
	m_bfme18 = other.m_bfme18;
	return this;
}
