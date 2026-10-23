// cl: /O2 /DNDEBUG /MD
// Donor: BFME1 EAStringCAssign.cpp at 0x008A0480.
// Target: 0x006D6250 calls ChangeBuffer and SetSize; uses length/hash at +2/+6
// and payload at +8. Preserve the donor copy operation with that SetSize call.

extern "C" void *__cdecl memcpy(void *, const void *, unsigned int);

int __cdecl utf8EncodedLength(int c);

class EAStringC
{
public:
	class StringDataC
	{
	public:
		unsigned short m_uRefCount;
		unsigned short m_uSize;
		unsigned short m_uMaxSize;
		unsigned short m_uHash;
	};

	static void FreeData(StringDataC *data);

private:
	enum CBPushZero
	{
		CB_NO_PUSH_ZERO,
		CB_PUSH_ZERO
	};

	StringDataC *m_pData;

	char *GetInternalBuffer() const
	{
		return reinterpret_cast<char *>(m_pData) + sizeof(StringDataC);
	}

	void ChangeBuffer(unsigned int uSizeToReserve, unsigned int uOffsetCopy,
		unsigned int uSizeCopy, CBPushZero ePushZero, unsigned int uInternalSize);

public:
	void SetSize(int size);
	EAStringC &Assign(const EAStringC &other);
	void rva006D4190(int c);
	EAStringC &rva006D61E0(int c);
};

extern EAStringC::StringDataC g_eaEmptyStringData;

EAStringC &EAStringC::Assign(const EAStringC &other)
{
	unsigned otherSize = other.m_pData->m_uSize;
	unsigned n = m_pData->m_uSize;
	if (n > otherSize)
		n = otherSize;
	ChangeBuffer(otherSize, 0, n, CB_PUSH_ZERO, n);
	char *dst = GetInternalBuffer();
	memcpy(dst, other.GetInternalBuffer(), otherSize);
	dst[otherSize] = 0;
	SetSize(otherSize);
	m_pData->m_uHash = other.m_pData->m_uHash;
	return *this;
}
EAStringC &EAStringC::rva006D61E0(int c)
{
	FreeData(m_pData);
	m_pData = &g_eaEmptyStringData;
	++g_eaEmptyStringData.m_uRefCount;
	int len = utf8EncodedLength(c);
	unsigned int n = m_pData->m_uSize;
	if (n > (unsigned int)len)
		n = len;
	ChangeBuffer(len, 0, n, CB_PUSH_ZERO, n);
	rva006D4190(c);
	return *this;
}
