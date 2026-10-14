void __cdecl operator delete[](void *block);

extern int g_bfmeVftAVJS[];
extern int g_bfmeVftBVJS[];

class BfmeThingVJS
{
public:
	void bfmeClearVJS(void);
	void *m_bfmeVfptr;
	int m_bfme04;
	int m_bfme08;
	void *m_bfme0c;
	int m_bfme10;
	void *m_bfme14;
	void *m_bfme18;
};

// ?bfmeClearVJS@BfmeThingVJS@@QAEXXZ
void BfmeThingVJS::bfmeClearVJS()
{
	m_bfmeVfptr = g_bfmeVftAVJS;
	m_bfme08 = 0;
	if (m_bfme0c)
	{
		::operator delete[](m_bfme0c);
		m_bfme0c = 0;
	}
	m_bfme10 = 0;
	if (m_bfme14)
	{
		::operator delete[](m_bfme14);
		m_bfme14 = 0;
	}
	m_bfmeVfptr = g_bfmeVftBVJS;
	if (m_bfme18)
		m_bfme18 = 0;
}

// Retail's data references in this unit's matched rows land on globals defined
// under other spellings at the same addresses (addend-corrected DIR32). Bind them.
#pragma comment(linker, "/alternatename:?g_bfmeVftAVJS@@3PAHA=??_7AABTreeClass@@6B@")
