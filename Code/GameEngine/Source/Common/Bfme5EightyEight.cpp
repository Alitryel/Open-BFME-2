// A pair of vectors handed in at once.
//
// BFME1 byte-identical donor (reference/open-bfme-1
// Code/GameEngine/Source/Common/Bfme5EightyEight.cpp); trimmed to the single
// T1 body the sweep places.

class BfmeVecHF
{
public:
	int m_bfmeX;
	int m_bfmeY;
	int m_bfmeZ;
};

class Gen_0094AC70
{
public:
	void bfmeSetPair(const BfmeVecHF *lhs, const BfmeVecHF *rhs);
private:
	unsigned char m_bfmeFlag;					// +0x000
	unsigned char m_bfmeGap[3];					// +0x001
	int m_bfmeState;							// +0x004
	BfmeVecHF m_bfmeA;							// +0x008
	int m_bfmeGap2[84];							// +0x014
	BfmeVecHF m_bfmeB;							// +0x164
};

void Gen_0094AC70::bfmeSetPair(const BfmeVecHF *lhs, const BfmeVecHF *rhs)
{
	m_bfmeState = 0;

	m_bfmeA.m_bfmeX = lhs->m_bfmeX;
	m_bfmeA.m_bfmeY = lhs->m_bfmeY;
	m_bfmeA.m_bfmeZ = lhs->m_bfmeZ;

	m_bfmeB.m_bfmeX = rhs->m_bfmeX;
	m_bfmeB.m_bfmeY = rhs->m_bfmeY;
	m_bfmeB.m_bfmeZ = rhs->m_bfmeZ;

	m_bfmeFlag = 0;
}
