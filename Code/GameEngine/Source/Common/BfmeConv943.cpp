// Open-BFME5 conversions.

void __cdecl operator delete[](void *block);

extern char g_bfme943VftE1[];
extern char g_bfme943VftE2[];

class BfmeThing943E
{
public:
	void bfmeGo943E();
	char *m_bfmeVft;
	void *m_bfmeP;
	void *m_bfmeQ;
};

void BfmeThing943E::bfmeGo943E()
{
	void *p = m_bfmeP;
	m_bfmeVft = g_bfme943VftE1;
	if (p) {
		::operator delete[](p);
		m_bfmeP = 0;
	}
	void *q = m_bfmeP;
	m_bfmeVft = g_bfme943VftE2;
	if (q) {
		::operator delete[](q);
		m_bfmeP = 0;
		m_bfmeQ = 0;
	}
}

extern char g_bfme943VftF1[];
extern char g_bfme943VftF2[];

class BfmeThing943F
{
public:
	void bfmeGo943F();
	char *m_bfmeVft;
	void *m_bfmeP;
	void *m_bfmeQ;
};

// ?bfmeGo943F@BfmeThing943F@@QAEXXZ present-unmatched
void BfmeThing943F::bfmeGo943F()
{
	void *p = m_bfmeP;
	m_bfmeVft = g_bfme943VftF1;
	if (p) {
		::operator delete[](p);
		m_bfmeP = 0;
	}
	void *q = m_bfmeP;
	m_bfmeVft = g_bfme943VftF2;
	if (q) {
		::operator delete[](q);
		m_bfmeP = 0;
		m_bfmeQ = 0;
	}
}

extern char g_bfme943VftG1[];
extern char g_bfme943VftG2[];

class BfmeThing943G
{
public:
	void bfmeGo943G();
	char *m_bfmeVft;
	void *m_bfmeP;
	void *m_bfmeQ;
};

// ?bfmeGo943G@BfmeThing943G@@QAEXXZ present-unmatched
void BfmeThing943G::bfmeGo943G()
{
	void *p = m_bfmeP;
	m_bfmeVft = g_bfme943VftG1;
	if (p) {
		::operator delete[](p);
		m_bfmeP = 0;
	}
	void *q = m_bfmeP;
	m_bfmeVft = g_bfme943VftG2;
	if (q) {
		::operator delete[](q);
		m_bfmeP = 0;
		m_bfmeQ = 0;
	}
}

// Retail's data references in this unit's matched rows land on globals defined
// under other spellings at the same addresses (addend-corrected DIR32). Bind them.
#pragma comment(linker, "/alternatename:?g_bfme943VftE1@@3PADA=??_7?$SimpleDynVecClass@E@@6B@")
#pragma comment(linker, "/alternatename:?g_bfme943VftE2@@3PADA=??_7?$SimpleVecClass@E@@6B@")
