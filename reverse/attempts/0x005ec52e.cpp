// ??MS4SortElem8@@QBE_NABU0@@Z
// partial score=0.95 date=2026-10-19
// cl: /O2 /Os /DNDEBUG /MD /EHsc
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class AsciiString;
bool operator<(const AsciiString &a, const AsciiString &b);

struct S4SortElem8
{
	const void *m_bfmeFirst;
	const void *m_bfmeSecond;
	bool operator<(const S4SortElem8 &other) const;
};

struct S4SortRecord
{
	int m_00;
	char m_name[4];
	char m_pad08[0x9C - 0x08];
	int m_9C;
};

struct S4SortTemplate
{
	char m_pad000[0x110];
	unsigned int m_low : 26;
	unsigned int m_first : 1;
};

bool S4SortElem8::operator<(const S4SortElem8 &other) const
{
	const S4SortTemplate *theirs = (const S4SortTemplate *)other.m_bfmeSecond;
	unsigned int theirsW = *(const unsigned int *)((const char *)theirs + 0x110);
	const S4SortTemplate *mine = (const S4SortTemplate *)m_bfmeSecond;
	unsigned int mineW = *(const unsigned int *)((const char *)mine + 0x110);
	_ReadWriteBarrier();
	mineW &= 0x4000000;
	bool first = mineW != 0;
	bool otherFirst = (theirsW >> 26) & 1;
	if (first != otherFirst)
		return mineW != 0;
	const S4SortRecord *a = (const S4SortRecord *)m_bfmeFirst;
	const S4SortRecord *b = (const S4SortRecord *)other.m_bfmeFirst;
	if (a->m_9C != b->m_9C)
		return a->m_9C > b->m_9C;
	return *(const AsciiString *)a->m_name < *(const AsciiString *)b->m_name;
}

