class BfmeMakerRE
{
public:
	virtual void bfmeSpareRE0();
	virtual void bfmeSpareRE1();
	virtual void bfmeSpareRE2();
	virtual void bfmeSpareRE3();
	virtual void bfmeSpareRE4();
	virtual void bfmeDoRE();
};

struct BfmeHolderRE
{
	unsigned char m_bfmeHead[0x2a0];
	BfmeMakerRE *m_bfmeMaker;
};

struct Bfme5Obj18;
struct Bfme5Obj18 *bfme5MakeObj18();

class BfmeThingRE
{
public:
	void bfmeRunRE();
	unsigned char m_bfmeHead[4];
	BfmeHolderRE *m_bfmeHolder;
};

void BfmeThingRE::bfmeRunRE()
{
	BfmeHolderRE *holder = m_bfmeHolder;
	if (holder->m_bfmeMaker == 0)
		holder->m_bfmeMaker = (BfmeMakerRE *)bfme5MakeObj18();
	m_bfmeHolder->m_bfmeMaker->bfmeDoRE();
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?bfmeRunRE@BfmeThingRE@@QAEXPAX@Z=?bfmeRunRE@BfmeThingRE@@QAEXXZ")
