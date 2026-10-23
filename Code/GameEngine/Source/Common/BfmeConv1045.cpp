// Init a B1045 block and done its sub-array.
//
// BFME1 byte-identical donor (reference/open-bfme-1
// Code/GameEngine/Source/Common/BfmeConv1045.cpp); trimmed to the single T1
// body the sweep places.

// Open-BFME5 conversions.

extern "C" void *bfmeVft1045A[];
extern "C" void *bfmeVft1045B[];

class BfmeSub1045
{
public:
	void bfmeDone1045(void);

	char m_bfmePad[0x24];
};

class BfmeB1045
{
public:
	void bfmeGo1045B(void);

	void *m_bfmeVfptr;
	void *m_bfmeVfptr2;
	int m_bfme08;
	int m_bfme0c;
	int m_bfme10;
	char m_bfmePad[0xd0];
	BfmeSub1045 m_bfmeArr[8];
};

void BfmeB1045::bfmeGo1045B(void)
{
	int z = 0;

	m_bfmeVfptr = bfmeVft1045A;
	m_bfmeVfptr2 = bfmeVft1045B;
	m_bfme08 = z;
	m_bfme0c = z;
	m_bfme10 = z;

	BfmeSub1045 *p = &m_bfmeArr[8];
	int n = 8;

	do {
		p--;
		p->bfmeDone1045();
	} while (--n != 0);
}

// Retail's data references in this unit's matched rows land on globals defined
// under other spellings at the same addresses (addend-corrected DIR32). Bind them.
#pragma comment(linker, "/alternatename:_bfmeVft1045A=??_7Rva00800920Owner@@6BRva00800920Primary@@@")
#pragma comment(linker, "/alternatename:_bfmeVft1045B=??_7Rva00800920Owner@@6BRva00800920Sec@@@")
