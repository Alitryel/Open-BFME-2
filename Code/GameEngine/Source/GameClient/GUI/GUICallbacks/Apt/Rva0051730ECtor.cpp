extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
// cl: /O1 /G7 /arch:SSE /MD
// ??0Rva0051730E@@QAE@XZ @0x0051730E 28B
// Native 0x0051730E..0x00517329: thiscall constructor returning this that
// fills a seven-dword record with -1,-1,-1,0,0,-1,0. No direct caller or data
// reference was found, so owner and field roles are unproven and the name is
// address-derived; it sits between the AptOnline shell bodies 0x00517207 and
// the handle constructor 0x0051732A.
struct Rva0051730E
{
	int m_first;
	int m_second;
	int m_third;
	int m_count;
	int m_value;
	int m_index;
	int m_extra;
	Rva0051730E();
};

Rva0051730E::Rva0051730E()
{
	m_first=-1;
	_ReadWriteBarrier();
	m_second=-1;
	m_third=-1;
	m_count=0;
	m_value=0;
	m_index=-1;
	m_extra=0;
}
