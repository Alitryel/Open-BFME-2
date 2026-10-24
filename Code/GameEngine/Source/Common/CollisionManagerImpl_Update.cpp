class CollisionManagerImpl
{
public:
	void bfmeOneCGD();
	void bfmeTwoCGD();
	void Update();
	void *m_bfmeFirst;
	unsigned char m_bfmeGap[0xc069];
	bool m_bfmeBusy;
};

void bfmeGlobalCGD();

void CollisionManagerImpl::Update()
{
	if (m_bfmeFirst != 0)
	{
		m_bfmeBusy = true;
		bfmeOneCGD();
		bfmeGlobalCGD();
		bfmeTwoCGD();
		m_bfmeBusy = false;
	}
}

// Retail calls UpdateSort without loading ECX (whole-program register reuse),
// so the call is spelled as a free function and bound to that row
// (tools/allowed_symbols.py --alternatenames).
#pragma comment(linker, "/alternatename:?bfmeGlobalCGD@@YAXXZ=?UpdateSort@CollisionManagerImpl@@QAEXXZ")
