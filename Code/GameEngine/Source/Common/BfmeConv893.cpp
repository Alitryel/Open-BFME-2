// BFME1 donor: reference/open-bfme-1/Code/GameEngine/Source/Common/BfmeConv893.cpp (FDE part only)
// Near-miss repair: BfmeHeldFDE head 0x200 in BFME1, 0x254 in BFME2
// (+0x54 drift verified at +0x0C: [eax+0x200] vs [eax+0x254]).

struct BfmeSubFDE
{
	virtual void bfmeV0();
	virtual void bfmeV1();
	virtual void bfmeV2();
	virtual void bfmeV3();
	virtual void bfmeV4();
	virtual void bfmeV5();
	virtual void bfmeV6();
	virtual void bfmeV7();
	virtual void *bfmeVirt8FDE();
};

struct BfmeHeldFDE
{
	unsigned char m_bfmeHead[0x254];
	BfmeSubFDE *m_bfmeS;
};

struct TransitionDamageFX
{
	void bfmeGoFDE();
	void bfmeUseFDE(void *r);
	unsigned char m_bfmeHead[8];
	BfmeHeldFDE *m_bfmeP;
};

void TransitionDamageFX::bfmeGoFDE()
{
	BfmeHeldFDE *h = m_bfmeP;
	if (h)
	{
		BfmeSubFDE *s = h->m_bfmeS;
		if (s)
			bfmeUseFDE(s->bfmeVirt8FDE());
	}
}
