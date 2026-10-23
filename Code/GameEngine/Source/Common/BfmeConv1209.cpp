// Open-BFME5 conversions.

struct BfmeS1209
{
	float m_bfme00, m_bfme04, m_bfme08, m_bfme0c, m_bfme10, m_bfme14, m_bfme18, m_bfme1c;
};

// BFME1 calls the imported bfmeNotify1209 here (dllimport). Retail BFME2
// instead indirects through the callback cell at 0x00E177A4 (NULL in the
// vanilla image; filled at runtime), so the callee is modeled as a
// function-pointer global whose DIR32 slot the gate patches from retail.
// Matched DIR32 witness places this callback cell at VA 0x00E177A4 in the
// zero-filled .data tail; retail starts NULL and fills it at runtime.
extern "C" void (__cdecl *bfmeNotify1209Callback)(void *a) = 0;

class BfmeA1209
{
public:
	void bfmeOp1209(const BfmeS1209 *a);
	float m_bfme00, m_bfme04, m_bfme08, m_bfme0c, m_bfme10, m_bfme14, m_bfme18, m_bfme1c;
};

void BfmeA1209::bfmeOp1209(const BfmeS1209 *a)
{
	m_bfme00 = a->m_bfme00 * m_bfme00;
	m_bfme04 = a->m_bfme04 * m_bfme04;
	m_bfme08 = a->m_bfme08 * m_bfme08;
	m_bfme0c = a->m_bfme0c * m_bfme0c;
	m_bfme10 = a->m_bfme10 + m_bfme10;
	m_bfme14 = a->m_bfme14 + m_bfme14;
	m_bfme18 = a->m_bfme18 + m_bfme18;
	m_bfme1c = a->m_bfme1c + m_bfme1c;
	bfmeNotify1209Callback(this);
}
