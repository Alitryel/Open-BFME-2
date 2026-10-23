// A name written into a numbered slot of a table.
//
// BFME1 byte-identical donor (reference/open-bfme-1
// Code/GameEngine/Source/Common/BfmeOneHundredSeventyOne.cpp); trimmed to the
// single T1 body the sweep places. The donor's sibling ctor
// (??0BfmeNodeAS@@QAE@PBUBfmeSpecAS@@@Z, under 16B) is declared, never defined.

class BfmeNodeAS;

class BfmeOwnerAS
{
public:
	unsigned char m_bfmeHead[0x98];		// 0x00
	BfmeNodeAS *m_bfmeLast;			// 0x98
	BfmeNodeAS *m_bfmeFirst;		// 0x9c
};

struct BfmeSpecAS
{
	BfmeOwnerAS *m_bfmeOwner;		// 0x0
	unsigned char m_bfmeGap[8];		// 0x4
	int m_bfmeExtra;			// 0xc
};

class BfmeNodeAS
{
public:
	BfmeNodeAS(const BfmeSpecAS *spec);

	BfmeOwnerAS *m_bfmeOwner;		// 0x0
	BfmeNodeAS *m_bfmeAfter;		// 0x4
	BfmeNodeAS *m_bfmeBefore;		// 0x8
	int m_bfmeExtra;			// 0xc
};

extern "C" unsigned int strlen(const char *text);
extern "C" char *strcpy(char *to, const char *from);

#pragma intrinsic(strlen, strcpy)

struct BfmeTableAT
{
	unsigned char m_bfmeHead[0x80];		// 0x000
	char m_bfmeNames[3][0x101];		// 0x080
	unsigned char m_bfmePad[1];		// 0x383
	int m_bfmeUsed[0x186];			// 0x384
	int m_bfmeSpare[1];			// 0x99c
};

void bfmeSetNameAT(BfmeTableAT *table, int slot, const char *name)
{
	if (strlen(name) < 0x101)
	{
		strcpy(table->m_bfmeNames[slot], name);

		table->m_bfmeUsed[slot] = 1;
		table->m_bfmeSpare[slot] = 0;
	}
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:_piStartedEnteringRoom=?bfmeSetNameAT@@YAXPAUBfmeTableAT@@HPBD@Z")
