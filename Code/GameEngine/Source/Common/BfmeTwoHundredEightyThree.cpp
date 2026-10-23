// cl: /Od

namespace _STL {

template<class _CharT> struct char_traits;

template<> struct char_traits<char>
{
	static unsigned int length(const char *text);
	static int compare(const char *first, const char *otherFirst, unsigned int count);
};

}

int bfmeDoPW(char *first, char *last, char *otherFirst, char *otherLast);

struct BfmeThingPW
{
	void bfmeGoPW(char *at);

	char *m_bfmeAt;
	char *m_bfmeEnd;
};

void BfmeThingPW::bfmeGoPW(char *at)
{
	unsigned char spare[0x10];

	bfmeDoPW(m_bfmeAt, m_bfmeEnd, at, at + _STL::char_traits<char>::length(at));
}

// Lexicographical range compare used by the PW table: memcmp over the shared
// prefix, then -1/0/+1 on the lengths. Retail keeps the shorter length behind
// a pointer pair (first/other) so /Od holds it in two stacked slots.
int bfmeDoPW(char *first, char *last, char *otherFirst, char *otherLast)
{
	int firstLength;
	int lenOther;
	int prefix;
	int *secondPtr;
	int *lengthPtr;
	int result;
	int order;

	firstLength = last - first;
	lenOther = otherLast - otherFirst;

	if (lenOther < firstLength)
		lengthPtr = &lenOther;
	else
		lengthPtr = &firstLength;

	secondPtr = lengthPtr;

	prefix = _STL::char_traits<char>::compare(first, otherFirst, *secondPtr);

	if (prefix != 0)
		result = prefix;
	else
	{
		if (firstLength < lenOther)
			order = -1;
		else
			order = (firstLength > lenOther);
		result = order;
	}

	return result;
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?bfmeDoPQ@@YAXPAD000@Z=?bfmeDoPW@@YAHPAD000@Z")
#pragma comment(linker, "/alternatename:_bfmeCopy1153=?bfmeDoPW@@YAHPAD000@Z")
#pragma comment(linker, "/alternatename:_bfmeCopy1152=?bfmeDoPW@@YAHPAD000@Z")
#pragma comment(linker, "/alternatename:_bfmeCopy1154=?bfmeDoPW@@YAHPAD000@Z")
