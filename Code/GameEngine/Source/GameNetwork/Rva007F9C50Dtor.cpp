// cl: /O2
// 0x007F9C50: destructor. Three most-derived vptrs, drop the +0x6A8 heap
// object, clear the chain at +0x6AC, then walk 32 0x1C slots backward.

class GenAlloc
{
public:
	virtual void v0();
	virtual void v1();
	virtual void *acquire(int size, int flags);
	virtual void release(void *block, int flags);
};

extern GenAlloc *Gen007EFFC0();

void bfmeDeleteVMP(void *block, unsigned size);

// Retail clears the chain through 0x0066CA80, the rowed 5-byte forward to
// Rva00800550Chain::clear (0x0066C970); the call names that row.
class Rva0066CA80
{
public:
	void rva0066CA80();
};

class Rva007F9C50Base0
{
public:
	virtual void v0() = 0;
	~Rva007F9C50Base0() throw() {}
};

class Rva007F9C50Base4
{
public:
	virtual void v4();
};

class Rva007F9C50Base8
{
public:
	virtual void v8();
};

struct Rva007F9C50Node
{
	void *a;
	void *b;
	void *c;
};

class Rva007F9C50Heap
{
public:
	virtual void wipe(unsigned flag);
};

class Rva007F9C50 : public Rva007F9C50Base0, public Rva007F9C50Base4, public Rva007F9C50Base8
{
public:
	~Rva007F9C50() throw();
	virtual void v0();
	virtual void v4();
	virtual void v8();

private:
	char m_pad[0x1C];
	char m_slots[0x380];
	char m_pad3A8[0x300];
	Rva007F9C50Heap *m_6A8;
	Rva0066CA80 m_chain;
};

Rva007F9C50::~Rva007F9C50() throw()
{
	Rva007F9C50Heap *p = m_6A8;
	if (p)
		p->wipe(1);
	m_6A8 = 0;
	m_chain.rva0066CA80();

	char *edi = (char *)this + 0x3A8;
	int n = 0x20;
	do
	{
		Rva007F9C50Node *esi = *(Rva007F9C50Node **)(edi - 4);
		edi -= 0x1C;
		if (esi)
		{
			Gen007EFFC0()->release(esi->c, 1);
			esi->b = 0;
			esi->a = 0;
			esi->c = 0;
			bfmeDeleteVMP(esi, 0xC);
		}
		*(void **)(edi + 4) = 0;
		*(void **)edi = 0;
		*(void **)(edi + 8) = 0;
		*(void **)(edi + 0xC) = 0;
		*(void **)(edi + 0x10) = 0;
		*(void **)(edi + 0x14) = 0;
		*(void **)(edi + 0x18) = 0;
	} while (--n);
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??1Gen007FA290@@UAE@XZ=??1Rva007F9C50@@QAE@XZ")

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?v8@Rva007F9C50@@UAEXXZ=?process@Rva007FA340@@QAEXPAX@Z")
#pragma comment(linker, "/alternatename:?v4@Rva007F9C50@@UAEXXZ=?onConnectionMade@FeslConnectionHandler@@QAEXXZ")
#pragma comment(linker, "/alternatename:?v0@Rva007F9C50@@UAEXXZ=??_GGen007FA290@@UAEPAXI@Z")
