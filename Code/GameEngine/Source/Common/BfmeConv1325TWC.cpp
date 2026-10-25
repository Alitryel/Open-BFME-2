// Byte-identical BFME1 donor extract (see reference/open-bfme-1/
// Code/GameEngine/Source/Common/BfmeConv1325.cpp). Only bfmeDelTWC is
// served; the donor's TWA/TWB siblings have no ledger rows, so the whole
// file cannot land as one TU.
class BfmeSinkTWC
{
public:
	virtual void bfmeV0TWC() = 0;
	virtual void bfmeV1TWC() = 0;
	virtual void bfmeV2TWC() = 0;
	virtual void bfmeDropTWC(void *p, int f) = 0;
};

class GenAlloc; GenAlloc *Gen007EFFC0();
void bfmeFreeTWC(void *p, int n);

class BfmeHeadTWC
{
public:
	void bfmeDtorTWC();
	char m_bfmePad[0x10];
};

class BfmeThingTWC
{
public:
	void *bfmeDelTWC(unsigned char flags);
	BfmeHeadTWC m_bfmeHead;
	int m_bfme10;
	void *m_bfmeItem;
};

void *BfmeThingTWC::bfmeDelTWC(unsigned char flags)
{
	if (m_bfmeItem)
		((BfmeSinkTWC *)Gen007EFFC0())->bfmeDropTWC(m_bfmeItem, 0);
	m_bfmeItem = 0;
	m_bfme10 = 0;
	m_bfmeHead.bfmeDtorTWC();
	if (flags & 1)
		bfmeFreeTWC(this, 0x20);
	return this;
}
