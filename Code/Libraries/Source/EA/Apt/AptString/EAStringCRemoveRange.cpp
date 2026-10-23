// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ?rva006D54B0@EAStringC@@QAEHHH@Z, retail 0x006D54B0, 200 bytes.
// EAStringC remove range [start start+count): BFME1 donor EAStringCRemoveRange
// rva0089EEF0 shape: count<=0 or end<=0 empties via FreeData and empty singleton;
// start clamped to 0; end clamped to size; start==0 and end==size fast paths via
// ChangeBuffer; general path ChangeBuffer then memcpy tail with null.
// Callers 0x006EC50D 0x00708EBD unclaimed. Neighbour Mid shares flags and rows.
extern "C" void *__cdecl memcpy(void *, const void *, unsigned int);
#pragma intrinsic(memcpy)

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

	StringDataC *m_pData;

private:
	enum CBPushZero
	{
		CB_NO_PUSH_ZERO,
		CB_PUSH_ZERO
	};

	void ChangeBuffer(unsigned int uSizeToReserve, unsigned int uOffsetCopy,
		unsigned int uSizeCopy, CBPushZero ePushZero, unsigned int uInternalSize);

public:
	int rva006D54B0(int start, int count);
};

extern EAStringC::StringDataC g_eaEmptyStringData;

int EAStringC::rva006D54B0(int start, int count)
{
	int end = count + start;
	if (count <= 0)
	{
		FreeData(m_pData);
		m_pData = &g_eaEmptyStringData;
		++g_eaEmptyStringData.m_uRefCount;
		return 0;
	}
	if (end <= 0)
	{
		FreeData(m_pData);
		m_pData = &g_eaEmptyStringData;
		++g_eaEmptyStringData.m_uRefCount;
		return 0;
	}
	if (start < 0)
		start = 0;
	StringDataC *data = m_pData;
	int size = data->m_uSize;
	if (end >= size)
		end = size;
	if (start == 0)
	{
		int newSize = size - end;
		ChangeBuffer(newSize, end, newSize, CB_PUSH_ZERO, newSize);
		return newSize;
	}
	if (end == size)
	{
		ChangeBuffer(start, 0, start, CB_PUSH_ZERO, start);
		return start;
	}
	count = start + (size - end);
	ChangeBuffer(count, 0, start, CB_NO_PUSH_ZERO, count);
	memcpy(reinterpret_cast<char *>(m_pData) + sizeof(StringDataC) + start,
		reinterpret_cast<char *>(data) + sizeof(StringDataC) + end, size - end + 1);
	return count;
}
