// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
#include "unicode_string.h"
// ?rva005B947D@AptOnlineHome@@QAEXHHH@Z @0x005B947D 104B
// Ticker formatted row: formats m_64's text plus two ints through rowed
// UnicodeString::format with fmt at VA 0x00C73BD0, then sets it under the
// index through rowed rva005B9378. Evidence: member +0x64 (UnicodeString
// m_64 in AptOnlineHome dtor TU), TheNullChr fallback at VA 0x00BBB5C4,
// callees rowed format/rva005B9378/releaseBuffer, 6 callers in 0x005B95B8.
class Rva005B9378
{
public:
	void rva005B9378(int index, const UnicodeString &value);
};

class AptOnlineHome
{
public:
	void rva005B947D(int index, int a, int b);
private:
	char m_pad[0x64];
	UnicodeString m_64;	// +0x64
};

void AptOnlineHome::rva005B947D(int index, int a, int b)
{
	UnicodeString tmp;
	tmp.format(L"%d%s%d%%", a, m_64.str(), b);
	((Rva005B9378 *)this)->rva005B9378(index, tmp);
}

struct FactionStatBlock
{
	int wins[4];
	int losses[4];
};

FactionStatBlock g_Va00E06484;	// retail RVA 0x00A06484 (.bss), defined here
FactionStatBlock g_Va00E064A4;	// retail RVA 0x00A064A4 (.bss), defined here
FactionStatBlock g_Va00E064C4;	// retail RVA 0x00A064C4 (.bss), defined here
FactionStatBlock g_Va00E064E4;	// retail RVA 0x00A064E4 (.bss), defined here
FactionStatBlock g_Va00E06504;	// retail RVA 0x00A06504 (.bss), defined here
FactionStatBlock g_Va00E06524;	// retail RVA 0x00A06524 (.bss), defined here
