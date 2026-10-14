// Small unrowed .text bodies from the 0x00654850..0x00681AAF (/O2) region.
// Retail bytes establish every shape; no caller is recovered and the owning
// classes are unknown, so each keeps an address-derived name and a view of
// only the fields it touches. Callees are the rowed bodies the jmp targets.

// ?rva0066D4F0@Rva0066D4F0@@QAEXH@Z @0x0066D4F0 10B: store the argument at +0x4C.
class Rva0066D4F0
{
public:
	void rva0066D4F0(int value);
private:
	char m_pad[0x4c];
	int m_4c;
};
void Rva0066D4F0::rva0066D4F0(int value)
{
	m_4c = value;
}

// Destructors whose only non-trivial member is a BfmeMsg (rowed virtual
// ??1BfmeMsg@@UAE@XZ 0x00655780, called directly for a member).
class BfmeMsg
{
public:
	virtual ~BfmeMsg();
};

// ??1Rva00665970@@QAE@XZ @0x00665970 8B: BfmeMsg member at +0x14.
class Rva00665970
{
public:
	~Rva00665970();
private:
	char m_pad[0x14];
	BfmeMsg m_14;
};
Rva00665970::~Rva00665970()
{
}

// ??1Rva0066CAC0@@QAE@XZ @0x0066CAC0 8B: BfmeMsg member at +0x10.
class Rva0066CAC0
{
public:
	~Rva0066CAC0();
private:
	char m_pad[0x10];
	BfmeMsg m_10;
};
Rva0066CAC0::~Rva0066CAC0()
{
}

// ?rva00674BA0@Rva00674BA0@@QBEPAXXZ @0x00674BA0 11B: rowed lea-field getter
// 0x0066D7D0 on the object at +0x0C of the object held at +0x08.
class Rva0066D7D0LeaField
{
public:
	void *get() const;
};
struct Rva00674BA0Inner
{
	char m_pad[0x0c];
	Rva0066D7D0LeaField *m_0c;
};
class Rva00674BA0
{
public:
	void *rva00674BA0() const;
private:
	char m_pad[0x08];
	Rva00674BA0Inner *m_08;
};
void *Rva00674BA0::rva00674BA0() const
{
	return m_08->m_0c->get();
}

// ?rva0066CA80@Rva0066CA80@@QAEXXZ @0x0066CA80 5B (called from 0x006661DA):
// clear the chain member at +0 through the rowed Rva00800550Chain::clear
// 0x0066C970.
class Rva00800550Chain
{
public:
	void clear();
};
class Rva0066CA80
{
public:
	void rva0066CA80();
private:
	Rva00800550Chain m_chain;
};
void Rva0066CA80::rva0066CA80()
{
	m_chain.clear();
}

// ??0Rva00665B70@@QAE@XZ @0x00665B70 13B: default constructor zeroing three words.
class Rva00665B70
{
public:
	Rva00665B70();
private:
	int m_00;
	int m_04;
	int m_08;
};
Rva00665B70::Rva00665B70()
{
	m_04 = 0;
	m_00 = 0;
	m_08 = 0;
}

// ?rva00674A20@Rva00674A20@@QAEHXZ @0x00674A20 8B: post-increment of the +0
// counter, returning the old value.
class Rva00674A20
{
public:
	int rva00674A20();
private:
	int m_00;
};
int Rva00674A20::rva00674A20()
{
	return m_00++;
}
