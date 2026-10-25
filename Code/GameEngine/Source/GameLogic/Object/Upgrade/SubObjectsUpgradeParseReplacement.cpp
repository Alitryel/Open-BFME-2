// cl: /Ireference/shims/bfme2_ascii
// stlport
//
// Target 0x004B5293 (88B), Ghidra boundary FUN_008b5293. Retail derives an
// eight-byte vector length, appends one record, then reads three INI tokens
// and calls AsciiString::set at record offsets +0/+4; the middle token result
// is discarded. The four-argument INI field
// callback ABI is supported by the stack reads and callees. It likely parses
// a two-string SubObjectsUpgrade record; the exact key and callback identity
// are unresolved, so the target symbol remains address-derived.

#include "ascii_string.h"
#include <vector>

struct BfmeStringRecord000B94D2
{
	AsciiString m_first;
	AsciiString m_second;
};

// The existing row at 0x000C4D34 owns this one-argument resize.
namespace _STL {
template <> void vector<BfmeStringRecord000B94D2>::resize(unsigned int);
}

class INI
{
public:
	const char *getNextTokenOrNull(const char *seps);
};

void __cdecl rva004B5293(INI *ini, void *instance, void *store, const void *userData)
{
	_STL::vector<BfmeStringRecord000B94D2> *records =
		(_STL::vector<BfmeStringRecord000B94D2> *)store;
	unsigned int newSize = (unsigned int)(records->end() - records->begin()) + 1;
	records->resize(newSize);

	BfmeStringRecord000B94D2 *record = records->end() - 1;
	const char *token = ini->getNextTokenOrNull(0);
	if (token != 0)
		record->m_first.set(token);

	ini->getNextTokenOrNull(0);
	token = ini->getNextTokenOrNull(0);
	if (token != 0)
		record->m_second.set(token);
}
