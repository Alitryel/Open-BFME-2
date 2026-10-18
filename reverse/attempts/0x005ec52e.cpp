// ??MS4SortElem8@@QBE_NABU0@@Z
// partial score=0.97 date=2026-10-18
// ??MS4SortElem8@@QBE_NABU0@@Z
// partial score=0.88 date=2026-10-14
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// Bank for 0x005EC52E; append to Code/GameEngine/Source/GameClient/GUI/ScoreRowSort.cpp (S4SortElem8 declared there).
// S4SortElem8::operator<, retail 0x005EC52E (102B, the pin above): entries
// whose +4 template has flag bit 26 set sort first; then the higher +0x9C
// value of the +0 record; then that record's +4 name (the rowed
// AsciiString operator< 0x0005598C). Field meanings are not recovered.
class AsciiString;
bool operator<(const AsciiString &a, const AsciiString &b);	// 0x0005598C

struct S4SortElem8
{
	const void *m_bfmeFirst;
	const void *m_bfmeSecond;
	bool operator<(const S4SortElem8 &other) const;
};

struct S4SortRecord
{
	int m_00;
	char m_name[4];		// +0x04 AsciiString
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
	const S4SortTemplate *mine = (const S4SortTemplate *)m_bfmeSecond;
	unsigned int mineW = *(volatile unsigned int *)((const char *)mine + 0x110);
	const S4SortTemplate *theirs = (const S4SortTemplate *)other.m_bfmeSecond;
	unsigned int theirsW = *(const unsigned int *)((const char *)theirs + 0x110);
	unsigned int mineF = mineW & 0x4000000;
	unsigned int theirsF = (theirsW >> 26) & 1;
	bool first = mineF != 0;
	bool otherFirst = theirsF != 0;
	if (first != otherFirst)
		return mineF != 0;
	const S4SortRecord *a = (const S4SortRecord *)m_bfmeFirst;
	const S4SortRecord *b = (const S4SortRecord *)other.m_bfmeFirst;
	if (a->m_9C != b->m_9C)
		return a->m_9C > b->m_9C;
	return *(const AsciiString *)a->m_name < *(const AsciiString *)b->m_name;
}
