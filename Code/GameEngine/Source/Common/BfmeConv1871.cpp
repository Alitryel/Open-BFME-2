// These registrations reference the same 12-byte transaction records that
// Rva007B55E0TxnNameInits.cpp initializes as fsys/Ping and fsys/Goodbye.
// Reuse their data-row providers rather than allocating integer lookalikes.
struct Rva007B55E0TxnName;
extern Rva007B55E0TxnName g_Va00E0A1BC;
extern Rva007B55E0TxnName g_Va00E0A198;
// The two callbacks are rowed statics: Rva00661220Callback::forward and
// Rva007F4740::bfmeCbBZC.
class BfmeThingVJL;
class Rva00661220Callback
{
public:
	static void __cdecl forward(int value, BfmeThingVJL *thing);
};
class Rva007F4740Context;
class Rva007F4740
{
public:
	static void __cdecl bfmeCbBZC(void *unused, Rva007F4740Context *context);
};

class BfmeThingZC
{
public:
	virtual void bfmeV0ZC();
	virtual void bfmeV1ZC();
	virtual void bfmeV2ZC();
	virtual void bfmeSetZC(void *what, int flag);
};

class BfmeHostZC
{
public:
	virtual void bfmeH0ZC();
	virtual void bfmeH1ZC();
	virtual void bfmeH2ZC();
	virtual void bfmeH3ZC();
	virtual void bfmeAddZC(void *name, void *cb, void *owner);

	unsigned char m_bfmeHeadZC[0x6a4];
	BfmeThingZC *m_bfmeThingZC;
};

class BfmeOwnerZC
{
public:
	virtual void bfmeO0ZC();
	virtual BfmeHostZC *bfmeHostZC();

	void bfmeRegisterZC();

	unsigned char m_bfmePadZC[8];
	unsigned char m_bfmeSubZC[4];
};

void BfmeOwnerZC::bfmeRegisterZC()
{
	BfmeHostZC *host = bfmeHostZC();

	host->m_bfmeThingZC->bfmeSetZC(m_bfmeSubZC, 0);

	host->bfmeAddZC(&g_Va00E0A1BC, (void *)Rva00661220Callback::forward, this);
	host->bfmeAddZC(&g_Va00E0A198, (void *)Rva007F4740::bfmeCbBZC, this);
}
