// cl: /DNDEBUG /MD /GX-
// Rva00803080 pool init @ 0x008030C0 (71B).

// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
// auto_inline(off) keeps the iterator out of line: without it the functions
// here that build arrays inline the /O1 body and lose retail's call to ??_H.
struct BfmeVciAnchorElem { BfmeVciAnchorElem(); };
#pragma auto_inline(off)
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma optimize("", on)
#pragma auto_inline(on)
class Gen007F0150
{
public:
	static void *operator new(unsigned int size);
};

struct Rva00807BA0Ping;
Rva00807BA0Ping *Rva00807BA0(void);

extern "C" void *memset(void *, int, unsigned);

inline void *operator new(unsigned int, void *where)
{
	return where;
}

class Rva008030C0Elem
{
public:
	Rva008030C0Elem();
	int m_00;
	int m_04;
	int m_08;
	int m_0c;
};

class Rva00803080
{
public:
	void initPool();

	void *m_00;
	void *m_04;
	Rva00807BA0Ping *m_08;
	Rva008030C0Elem *m_0c;
	int m_10;
};

void Rva00803080::initPool()
{
	void *raw = Gen007F0150::operator new(0x800);
	Rva008030C0Elem *p;
	if (raw)
		p = new (raw) Rva008030C0Elem[0x80];
	else
		p = 0;
	m_0c = p;
	memset(p, 0, 0x800);
	m_10 = 0;
	m_08 = Rva00807BA0();
}
