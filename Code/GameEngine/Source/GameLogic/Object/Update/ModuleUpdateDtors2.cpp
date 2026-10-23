// cl: /O1 /GX- /MD /DNDEBUG
// Trial: opaque dtor at 0x004907C9 (vtab + consts + member-method call).


class PoolMember
{
public:
	void Rva00268902();

private:
	unsigned char m_pad[16];
};

// Base dtor resolves to the opaque pin at 0x00451F45.
class Rva00451F45
{
public:
	virtual ~Rva00451F45();
};

class Rva004907C0 : public Rva00451F45
{
public:
	virtual ~Rva004907C0();

private:
	unsigned char m_pad04[8];
	const void *m_p0C;
	const void *m_p10;
	unsigned char m_pad14[12];
	const void *m_p20;
	unsigned char m_pad24[0x88 - 0x24];
	PoolMember m_mem88;
};

static int s_07C9_0C;
static int s_07C9_10;
static int s_07C9_20;

// ?Rva004907C0::~Rva004907C0 present-unmatched
Rva004907C0::~Rva004907C0()
{
	m_p0C = &s_07C9_0C;
	m_p10 = &s_07C9_10;
	m_p20 = &s_07C9_20;
	m_mem88.Rva00268902();
}
