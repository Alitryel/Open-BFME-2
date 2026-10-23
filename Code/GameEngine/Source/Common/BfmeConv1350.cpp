// Retail embedded-table destructor; parent lifetime proof: 0x0075A080 and
// unwind entries 0x007AB790/0x007AB79B call the same whole cleanup body.
// Node-deletion loop retained from the existing BFME 1 donor.

void __cdecl operator delete(void *p);

struct BfmeNodeVDB
{
	char m_bfmePad[0x30];
	BfmeNodeVDB *m_bfmeNext;
};

class Rva009A4620VDBView
{
public:
	~Rva009A4620VDBView() throw();
	BfmeNodeVDB *m_bfmeTable[0x493];
	BfmeNodeVDB *m_bfmeExtra;
	unsigned char m_tail[8];
};

Rva009A4620VDBView::~Rva009A4620VDBView() throw()
{
	for (unsigned i = 0; i < 0x493; ++i) {
		BfmeNodeVDB *p = m_bfmeTable[i];
		while (p) {
			BfmeNodeVDB *next = p->m_bfmeNext;
			operator delete(p);
			p = next;
		}
	}
	BfmeNodeVDB *p = m_bfmeExtra;
	while (p) {
		BfmeNodeVDB *next = p->m_bfmeNext;
		operator delete(p);
		p = next;
	}
}
