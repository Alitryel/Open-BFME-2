// Open-BFME5 conversions (trimmed; only bfmeGo1015L is placed, the rest is
// declared-only).

class BfmeI1015A
{
public:
	void bfmeDo1015A(int a, int b, int c);
};

class BfmeI1015B
{
public:
	void bfmeDo1015B(int a, int b);
};

class BfmeI1015
{
public:
	void bfmeGo1015I(int a, int b, int c);
};


class BfmeMgr1015
{
public:
	virtual void bfmeVM01015();
	virtual void bfmeVM11015();
	virtual void bfmeVM21015();
	virtual void bfmeFree1015(int h, int f);
};

class GenAlloc; GenAlloc *Gen007EFFC0();

class BfmeL1015
{
public:
	void bfmeGo1015L(void);
	void bfmeReset1015(void);

	char m_bfmePad[0x10];
	int m_bfmeCount;
	int m_bfmeH;
};

// ?bfmeGo1015L@BfmeL1015@@QAEXXZ
void BfmeL1015::bfmeGo1015L(void)
{
	if (m_bfmeH != 0)
		((BfmeMgr1015 *)Gen007EFFC0())->bfmeFree1015(m_bfmeH, 0);

	m_bfmeH = 0;
	m_bfmeCount = 0;
	bfmeReset1015();
}

class BfmeSub1015
{
public:
	virtual void bfmeVS01015();
	virtual void bfmeVS11015();
	virtual void bfmeVS21015();
	virtual void bfmeVS31015();
	virtual void bfmeVS41015();
	virtual void bfmeVS51015();
	virtual void bfmeVS61015();
	virtual void bfmeVS71015();
	virtual void bfmeVS81015();
	virtual void bfmeVS91015();
	virtual int bfmeTry1015(int a, int b);
};

class BfmeM1015
{
public:
	void bfmeGo1015M(int a, int b);
	void bfmeFallback1015(int a, int b);
};

class BfmeReg1015
{
public:
	virtual void bfmeVR01015();
	virtual void bfmeVR11015();
	virtual void bfmeVR21015();
	virtual void bfmeVR31015();
	virtual void bfmeVR41015();
	virtual void bfmeVR51015();
	virtual void bfmeVR61015();
	virtual void bfmeVR71015();
	virtual void bfmeVR81015();
	virtual void bfmeVR91015();
	virtual void bfmeDrop1015(int h);
};

class BfmeO1015
{
public:
	void bfmeGo1015O(int h);
};
