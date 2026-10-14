// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
// Open-BFME5 conversions: allocate-then-initialise bodies.

void * __cdecl operator new(unsigned int n);

namespace _STL {

class __new_alloc
{
public:
	static void *allocate(unsigned int n);
};

}

extern void *g_bfme5RefVtable;

struct Bfme5RefNode
{
	void *m_bfmeVptr;
	int m_bfmeRefCount;
	int m_bfmePad;
};

class Bfme5RefHolderA
{
public:
	Bfme5RefHolderA(int unused);

	Bfme5RefNode *m_bfmeNode;
};

Bfme5RefHolderA::Bfme5RefHolderA(int unused)
{
	Bfme5RefNode *q = (Bfme5RefNode *)operator new(12);
	Bfme5RefNode *p;

	if (q) {
		q->m_bfmeRefCount = 0;
		q->m_bfmeVptr = &g_bfme5RefVtable;
		p = q;
	} else {
		p = 0;
	}

	m_bfmeNode = p;

	if (p)
		++p->m_bfmeRefCount;
}

// ??0Rva0023FC10@@QAE@URva0023FC10Arg@@@Z, retail 0x0023FC10 (19B, RET4).
// Target evidence: a constructor whose only work is running the holder
// constructor above on this, handing it the address of its own one-word
// by-value argument, then returning this (twin skeleton of the by-value
// timer-binder ctor 0x005C7D37). The holder row spells that parameter as an
// unused int, so the address is passed through that spelling. Owner, the
// argument's type and the holder's real parameter type are unresolved.
struct Rva0023FC10Arg
{
	int m_word;
};

class Rva0023FC10
{
public:
	Rva0023FC10(Rva0023FC10Arg arg);

	Bfme5RefHolderA m_holder;
};

Rva0023FC10::Rva0023FC10(Rva0023FC10Arg arg)
	: m_holder((int)&arg)
{
}
