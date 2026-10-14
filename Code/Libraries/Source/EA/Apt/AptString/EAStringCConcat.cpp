// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ??HEAStringC@@QBE?AV0@ABV0@@Z
// Retail 0x006D46C0..0x006D47EC (300 bytes).
// EAStringC concatenation returning a new string: an empty receiver returns
// a copy of the other string and an empty other string returns a copy of the
// receiver; otherwise a string reserved for the summed size (rowed
// EAStringC(unsigned) 0x006D45F0) receives both texts with intrinsic memcpy
// and a terminator and its logical size is set (rowed SetSize 0x006D3BC0)
// before it is copied out (rowed copy ctor 0x006D2FC0) and released (rowed
// FreeData 0x006D2EB0 through the inline destructor as in EAStringCMid.cpp).
// Target fact kept as found: the cached hash word (+6) that is cleared is the
// receiver's (the saved this pointer is reloaded for it) not the result's.
// The operator name is a semantic pick from the body (receiver-left
// concatenation by value; ret 8 = hidden result + other); flags follow the
// EAStringCMid.cpp sibling.
extern "C" void *__cdecl memcpy(void *dst, const void *src, unsigned int count);
#pragma intrinsic(memcpy)

#include <string.h>
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)
class Rva006DB270;
extern Rva006DB270 *g_pChainBlockAllocator;
class Rva006DB160 {public:void *allocBlock(int blockSize);};

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

	EAStringC(const EAStringC &other);
	EAStringC(unsigned int nSize);
	EAStringC(const char *s) : m_pData(0) { Assign(s); }
	~EAStringC()
	{
		FreeData(m_pData);
	}
	void SetSize(int size);
	void Reserve(int size);
	void Assign(const char *text);
	unsigned int GetInternalMaxSize() const {return m_pData->m_uMaxSize;}
	void setCapacityWord_Rva006D2E00(unsigned int value);
	EAStringC operator+(const EAStringC &other) const;
	EAStringC operator+(const char *other) const;
};

// The four existing native helpers must be visible together: the sized
// constructor follows Reserve and SetSize; the return copy reads that result.
// This proves the local string does not escape and lets cl preserve its data
// pointer across the copy. Each helper independently retains its whole retail
// body and relocations. SetSize keeps its original assertion barrier.
extern EAStringC::StringDataC g_eaEmptyStringData;
__declspec(noinline) inline EAStringC::EAStringC(const EAStringC &other)
{
	StringDataC *otherData = other.m_pData;
	m_pData = otherData;
	if (otherData != &g_eaEmptyStringData) {
		if (!(otherData->m_uRefCount <= 0xFFFE)) {
			g_bfmeAptAssertAtE17734("m_pData->m_uRefCount <= 0xfffe", ".\\string\\EAString.inl", 0xE1);
			if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
		}
	}
	m_pData->m_uRefCount++;
}
__declspec(noinline) inline EAStringC::EAStringC(unsigned int nSize)
{
	m_pData = 0;
	if (nSize) {
		Reserve(nSize);
		SetSize(0);
		m_pData->m_uHash = 0;
		reinterpret_cast<char *>(m_pData)[sizeof(StringDataC)] = 0;
	} else {
		m_pData = &g_eaEmptyStringData;
		++g_eaEmptyStringData.m_uRefCount;
	}
}
__declspec(noinline) inline void EAStringC::Reserve(int size)
{
	EAStringC *self = this;
	if (!((unsigned)size > 0u)) {
		g_bfmeAptAssertAtE17734("uSize > 0", ".\\string\\EAString.inl", 0x4CB);
		if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
	}
	int rounded = (size + 12) & ~3;
	if (!((unsigned)rounded < 0xFFFFu)) {
		g_bfmeAptAssertAtE17734("uAllocateSize < 0xffff", ".\\string\\EAString.inl", 0x4D2);
		if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
	}
	StringDataC *data = (StringDataC *)(*(Rva006DB160 * *)&g_pChainBlockAllocator)->allocBlock(rounded);
	self->m_pData = data;
	data->m_uRefCount = 1;
	data = self->m_pData;
	data->m_uMaxSize = (unsigned short)(rounded - 9);
}
__declspec(noinline) inline void EAStringC::SetSize(int uSize)
{
	if (!(uSize <= GetInternalMaxSize())) {
		g_bfmeAptAssertAtE17734("uSize <= GetInternalMaxSize()", ".\\string\\EAString.inl", 0x5C);
		if (g_bfmeAptBreakOnAssertAtDDC01C) {
			__asm int 3
		}
	}
	m_pData->m_uSize = (unsigned short)uSize;
}
void EAStringC::setCapacityWord_Rva006D2E00(unsigned int value)
{
    m_pData->m_uMaxSize = (unsigned short)value;
}

EAStringC EAStringC::operator+(const EAStringC &other) const
{
	unsigned int size = m_pData->m_uSize;
	if (size == 0)
		return other;
	unsigned int otherSize = other.m_pData->m_uSize;
	if (otherSize == 0)
		return *this;
	unsigned int total = size + otherSize;
	EAStringC result(total);
	const char *source = (char *)m_pData + sizeof(StringDataC);
	char *text = (char *)result.m_pData + sizeof(StringDataC);
	memcpy(text, source, size);
	memcpy(text + size, (char *)other.m_pData + sizeof(StringDataC), otherSize);
	text[size + otherSize] = 0;
	result.SetSize(total);
	m_pData->m_uHash = 0;
	return result;
}

// Native 6D4F70..6D509D: right C-string concatenation. Same layout and
// ownership as the verified 300-byte overload; no volatile pointer workaround.
EAStringC EAStringC::operator+(const char *other) const
{
	unsigned int size = m_pData->m_uSize;
	if (size == 0)
		return other;
	unsigned int otherSize = strlen(other);
	if (otherSize == 0)
		return *this;
	unsigned int total = size + otherSize;
	EAStringC result(total);
	char *text = (char *)(result.m_pData + 1);
	memcpy(text, (char *)m_pData + sizeof(StringDataC), size);
	memcpy(text + size, other, otherSize);
	text[size + otherSize] = 0;
	result.SetSize(total);
	m_pData->m_uHash = 0;
	return result;
}

// Native 6D5160..6D5292: left C-string concatenation. The caller at 6FF980
// supports the argument order and return ABI; the original name is unknown.
EAStringC rva006D5160(const char *left, const EAStringC &right)
{
	unsigned int size = right.m_pData->m_uSize;
	if (size == 0)
		return EAStringC(left);
	unsigned int otherSize = strlen(left);
	if (otherSize == 0)
		return right;
	unsigned int total = otherSize + size;
	EAStringC result(total);
	char *text = (char *)result.m_pData + sizeof(EAStringC::StringDataC);
	memcpy(text, left, otherSize);
	memcpy(text + otherSize, (char *)right.m_pData + sizeof(EAStringC::StringDataC), size);
	text[otherSize + size] = 0;
	EAStringC *presult = &result;
	presult->SetSize(total);
	presult->m_pData->m_uHash = 0;
	return *presult;
}
