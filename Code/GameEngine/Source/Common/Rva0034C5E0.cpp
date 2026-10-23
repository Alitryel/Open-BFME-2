// Retail RVA 0x0034C5E0, 84 bytes.
// Vtable 0x010E7D00 and the releaseBuffer call identify the constructor
// layout, but the owning class name remains unknown.

// cl: /Ireference/shims/moduledata /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ob2

class BfmeStringYK
{
public:
	BfmeStringYK()
	{
		m_bfmeDataYK = 0;
	}

	~BfmeStringYK()
	{
		bfmeClearYK();
	}

	void bfmeClearYK();

	void *m_bfmeDataYK;
};

// Base: the canonical Snapshot. Its inline ctor's vptr store is dead in
// retail, and unwind state 0 runs ~Snapshot (funclet 0x0077D6C0 jumps to
// 0x0049B47C). The virtual destructor is defined in Rva0034C5E0Dtor.cpp.
#include "Common/Snapshot.h"

class Rva0034C5E0 : public Snapshot
{
public:
	Rva0034C5E0();
	virtual ~Rva0034C5E0();

	BfmeStringYK m_bfmeStrYK;
	int m_bfmeAYK;
	int m_bfmeBYK;
};

// ??0Rva0034C5E0@@QAE@XZ
Rva0034C5E0::Rva0034C5E0()
{
	m_bfmeAYK = 1;
	m_bfmeBYK = 0;
	m_bfmeStrYK.bfmeClearYK();
}
