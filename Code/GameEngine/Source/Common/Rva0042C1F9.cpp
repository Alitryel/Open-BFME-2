// cl: /O1 /EHsc /MD
// ?rva0042C1F9@Rva0042C1F9@@QAEPAV1@UHolder0042C1F9@@@Z, retail 0x0042C1F9, 65 bytes.
// Setter with ownership-transfer holder: takes old at +0, stores released holder ptr,
// calls old virtual slot0 with 0, deletes returned pointer via rowed operator delete,
// returns this. Evidence: single caller 0x0042C342, __thiscall via ecx plus ret 4,
// EH handler at 0xB875AE with scope table, shape twins Rva001F4206 plus Rva00180AB5.
void __cdecl operator delete(void *p);

struct Rva0042C1F9Helper
{
	virtual void *virt0(int x);
};

struct Holder0042C1F9
{
	Rva0042C1F9Helper *p;
	~Holder0042C1F9();
	Rva0042C1F9Helper *release();
};

class Rva0042C1F9
{
public:
	Rva0042C1F9Helper *m_ptr;
	Rva0042C1F9 *rva0042C1F9(Holder0042C1F9 h);
};

// ??1Holder0042C1F9@@QAE@XZ present-unmatched
inline Holder0042C1F9::~Holder0042C1F9()
{
	if (p)
		::operator delete(p);
}

// ?release@Holder0042C1F9@@QAEPAURva0042C1F9Helper@@XZ present-unmatched
inline Rva0042C1F9Helper *Holder0042C1F9::release()
{
	Rva0042C1F9Helper *t = p;
	p = 0;
	return t;
}

Rva0042C1F9 *Rva0042C1F9::rva0042C1F9(Holder0042C1F9 h)
{
	Rva0042C1F9Helper *old = m_ptr;
	m_ptr = h.release();
	void *q = old ? old->virt0(0) : 0;
	::operator delete(q);
	return this;
}
