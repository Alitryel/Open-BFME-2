// Allocate-and-fill factory.
//
// BFME1 byte-identical donor (reference/open-bfme-1
// Code/GameEngine/Source/Common/Bfme5FactoryStubs.cpp); trimmed to the single
// T1 body the sweep places. The redundant vtable stores survive via volatile
// lvalues standing in for the constructor boundary.

class Gen007F0130
{
public:
	static void *operator new(unsigned int n);
};

extern "C" char __identifier("??_7Rva006613E0@@6B@")[];
extern "C" char __identifier("??_7Gen007F4D00@@6BGen007F4D00Listener@@@")[];
extern "C" char __identifier("??_7Gen007F4D00@@6BGen007F4D00Owner@@@")[];

struct Bfme5Obj18
{
	void *m_bfmeV0;
	void *m_bfmeV4;
	int m_bfme08;
	int m_bfme0c;
	int m_bfme10;
	int m_bfme14;
};

Bfme5Obj18 * __cdecl bfme5MakeObj18(void)
{
	void *q = Gen007F0130::operator new(0x18);
	Bfme5Obj18 *p;

	if (q) {
		p = (Bfme5Obj18 *)q;
		*(void *volatile *)&p->m_bfmeV4 = __identifier("??_7Rva006613E0@@6B@");
		*(void *volatile *)&p->m_bfmeV0 = __identifier("??_7Gen007F4D00@@6BGen007F4D00Owner@@@");
		*(void *volatile *)&p->m_bfmeV4 = __identifier("??_7Gen007F4D00@@6BGen007F4D00Listener@@@");
		p->m_bfme08 = 0;
		p->m_bfme0c = 0;
		p->m_bfme10 = 0;
		p->m_bfme14 = 0;
		return p;
	}

	return 0;
}
