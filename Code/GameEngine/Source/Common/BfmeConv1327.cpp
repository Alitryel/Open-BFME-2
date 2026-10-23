// Open-BFME5 conversions.

// ?bfmeDelTYA@BfmeThingTYA@@QAEPAXE@Z, retail 0x0066E3D0 (83B).
// Ported from Open-BFME-1 Code/GameEngine/Source/Common/BfmeConv1327.cpp
// (BFME1 0x00802110). Only the placed TYA deleter is defined here; the
// donor's TYB half stays out, so the unmatched-definition gate passes.
// Callees mirror the BFME1 pins: bfmeDtorBTYA at 0x00663FA0 and bfmeFreeTYA
// at 0x0065D030 were already pinned, bfmeDtorATYA at 0x0066D900 rides with
// this body. The vftable globals are masked DIR32.

extern void *g_bfmeVftATYA[];
extern void *g_bfmeVftBTYA[];

class BfmeSlotTYA
{
public:
	void bfmeDtorBTYA();
	char m_bfmePad[8];
};

class BfmeHeadTYA
{
public:
	void bfmeDtorATYA();
	char m_bfmePad[8];
};

void bfmeFreeTYA(void *p, int n);

class BfmeThingTYA
{
public:
	void *bfmeDelTYA(unsigned char flags);
	void rva008020D0();
	void *m_bfmeVft;
	int m_bfme04;
	char m_bfmePad[8];
	BfmeSlotTYA m_bfmeC;
	BfmeSlotTYA m_bfmeB;
	BfmeHeadTYA m_bfmeA;
	int m_bfme28;
	int m_bfme2c;
	char m_bfme30;
	char m_bfmePad2[0x24];
	char m_bfme55;
};

void *BfmeThingTYA::bfmeDelTYA(unsigned char flags)
{
	m_bfmeVft = g_bfmeVftATYA;
	m_bfme04 = 0;
	m_bfme28 = 0;
	m_bfme30 = 0;
	m_bfme55 = 0;
	m_bfme2c = 0;
	m_bfmeA.bfmeDtorATYA();
	m_bfmeB.bfmeDtorBTYA();
	m_bfmeC.bfmeDtorBTYA();
	m_bfmeVft = g_bfmeVftBTYA;
	if (flags & 1)
		bfmeFreeTYA(this, 0xd8);
	return this;
}

// Retail non-deleting cleanup at 0x008020D0 (BFME 1; here 0x0066E390, 0x40
// before the deleting wrapper, as in BFME 1): the deleting wrapper above proves
// the shared owner layout, vtable transitions and member-release order. Carried
// from the same donor, byte-identical; its name keeps the BFME 1 address token.
void BfmeThingTYA::rva008020D0()
{
	m_bfmeVft = g_bfmeVftATYA;
	m_bfme04 = 0;
	m_bfme28 = 0;
	m_bfme30 = 0;
	m_bfme55 = 0;
	m_bfme2c = 0;
	m_bfmeA.bfmeDtorATYA();
	m_bfmeB.bfmeDtorBTYA();
	m_bfmeC.bfmeDtorBTYA();
	m_bfmeVft = g_bfmeVftBTYA;
}

// Retail's data references in this unit's matched rows land on globals defined
// under other spellings at the same addresses (addend-corrected DIR32). Bind them.
#pragma comment(linker, "/alternatename:?g_bfmeVftATYA@@3PAPAXA=??_7Rva00802040Owner@@6B@")

// The global(s) below are defined elsewhere under another name at the same
// address (the census owner of that DIR32 target); bind this unit's spelling.
#pragma comment(linker, "/alternatename:?g_bfmeVftBTYA@@3PAPAXA=??_7Rva00802040OwnerBase@@6B@")
