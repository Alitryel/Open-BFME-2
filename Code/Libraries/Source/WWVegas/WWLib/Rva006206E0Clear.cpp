// cl: /O2 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// ?rva006206E0@Rva006206E0@@QAEXXZ, RVA 0x006206E0, 51 bytes.
// Evidence: chain calls 0x620390 just landed now all callees resolved; same page
// deque sentinel reset at [esi] plus size +4 matches siblings 0x620A00.

class Rva00620390
{
public:
	void rva00620390(void *node);
};

struct Rva006206E0Sentinel
{
	char m_pad0[4];
	void *m_head;
	void *m_next8;
	void *m_nextC;
};

class Rva006206E0
{
public:
	void rva006206E0();

	Rva006206E0Sentinel *m_sentinel;
	int m_size;
};

void Rva006206E0::rva006206E0()
{
	if (m_size == 0)
		return;
	((Rva00620390 *)this)->rva00620390(m_sentinel->m_head);
	m_sentinel->m_next8 = m_sentinel;
	m_sentinel->m_head = 0;
	m_sentinel->m_nextC = m_sentinel;
	m_size = 0;
}
