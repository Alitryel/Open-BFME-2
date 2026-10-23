// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
class BfmeSubDDA
{
public:
	int bfmeTailDDA();
	unsigned char m_bfmeHead[0x39];
	bool m_bfmeFlag;
};

class BfmeThingDDA
{
public:
	int bfmeGoDDA();
	unsigned char m_bfmeHead[0x68];
	BfmeSubDDA *m_bfmeSub;
};

int BfmeThingDDA::bfmeGoDDA()
{
	BfmeSubDDA *s = m_bfmeSub;
	if (s != 0 && s->m_bfmeFlag)
		return s->bfmeTailDDA();
	return 0;
}

// Each retail call in this body reads an address the ledger already carries
// under the rowed name below; bind the donor spelling to that owner so one
// address keeps one definition.
//   0x00271898 -> ?rva00271898@Rva00271826@@QAEPBURva00271898Color@@XZ
#pragma comment(linker, "/alternatename:?bfmeTailDDA@BfmeSubDDA@@QAEHXZ=?rva00271898@Rva00271826@@QAEPBURva00271898Color@@XZ")
