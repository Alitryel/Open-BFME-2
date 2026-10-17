// ??0Rva006F69D0@@QAE@PAXHH@Z
// partial score=0.946 date=2026-10-17
// ??0Rva006F69D0@@QAE@PAXHH@Z
// partial score=0.9397 date=2026-10-15
// cl: /O2 /MD /DNDEBUG
// Bank note: x87 float copies need an x87 TU (region default is SSE; a new TU needs a
// flag_defaults.py propose override). Only residue: retail loads `second` into dx
// before `mov eax,ecx` and gives the descriptor ecx; cl here moves this first.
extern const float BfmeZeroRange;

struct Rva006F69D0Descriptor
{
	int m_kind;
	unsigned int m_flags;
	char m_pad08[0x10 - 0x08];
	char m_block10[0x28 - 0x10];
	char m_block28[0x30 - 0x28];
	float m_float30;
	char m_pad34[0x38 - 0x34];
	unsigned short m_word38;
	char m_pad3A[0x3c - 0x3a];
	void *m_ptr3C;
};

class Rva006F69D0
{
public:
	Rva006F69D0(void *descriptor, int second, int fourth) throw();

	int m_00;
	void *m_04;
	void *m_08;
	void *m_0c;
	float m_10;
	unsigned int m_14;
	unsigned short m_18;
	unsigned short m_1a;
};

Rva006F69D0::Rva006F69D0(void *descriptor, int second, int fourth) throw()
	: m_18(0)
{
	int s = *(volatile int*)&second;
	const Rva006F69D0Descriptor *d = (const Rva006F69D0Descriptor *)descriptor;
	m_18 = (unsigned short)s;
	m_18 = (unsigned short)second;
	m_14 = d->m_flags;
	m_00 = fourth;
	m_1a = d->m_word38;
	if (d->m_flags & 4)
		m_04 = (void *)d->m_block10;
	else
		m_04 = 0;
	m_08 = (d->m_flags & 8) ? (void *)d->m_block28 : 0;
	m_0c = (d->m_flags & 0x80) ? d->m_ptr3C : 0;
	m_10 = (d->m_flags & 0x10) ? d->m_float30 : BfmeZeroRange;
}
