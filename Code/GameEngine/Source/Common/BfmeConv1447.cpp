// Retail embedded-table destructor; parent lifetime proof: 0x0075A080 and
// unwind entries 0x007AB790/0x007AB79B call the same whole cleanup body.
void __cdecl operator delete(void *place);

struct BfmeNodeVMN
{
	char m_bfmePad00[0x30];
	BfmeNodeVMN *m_bfme30;
};

class Rva009A4620VMNView
{
public:
	~Rva009A4620VMNView() throw();
	BfmeNodeVMN *m_bfme00[0x2b7b];
	BfmeNodeVMN *m_bfmeadec;
	unsigned char m_tail[8];
};

Rva009A4620VMNView::~Rva009A4620VMNView() throw()
{
	unsigned i;
	BfmeNodeVMN *p;

	for (i = 0; i < 0x2b7b; ++i)
	{
		p = m_bfme00[i];
		while (p != 0)
		{
			BfmeNodeVMN *n = p->m_bfme30;

			::operator delete(p);
			p = n;
		}
	}

	p = m_bfmeadec;
	while (p != 0)
	{
		BfmeNodeVMN *n = p->m_bfme30;

		::operator delete(p);
		p = n;
	}
}
