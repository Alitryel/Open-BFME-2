// cl: /Ireference/shims/bfme2_ascii /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ??4Rva002D0A11@@QAEAAV0@ABV0@@Z, retail 0x002D0A11 (18B, RET4).
// Target evidence: assigns the object's only member, a vector of the 20-byte
// record, through the rowed vector operator= 0x002D0726 (the only callee) and
// returns this -- the copy assignment of a class holding just that vector
// (twin skeleton of AsciiString::operator= 0x00001733). The record's vector
// assignment copies elements through the ModuleInfo::Nugget assignment, which
// fits ModuleInfo (whose only member is its Nugget vector), but no caller
// pins the owner, so the class keeps an address-derived name. The vector
// operator= is only declared here so the call stays out of line.
#include <vector>
#include "ascii_string.h"

struct BfmeStringRecord002CF4C6
{
	AsciiString text0;
	AsciiString text1;
	unsigned int word0;
	unsigned int word1;
	unsigned char flag0;
	unsigned char flag1;
	char m_pad[2];
	BfmeStringRecord002CF4C6();
	BfmeStringRecord002CF4C6(const BfmeStringRecord002CF4C6 &other);
	~BfmeStringRecord002CF4C6();
};

typedef _STL::vector<BfmeStringRecord002CF4C6> Rva002D0A11Records;
namespace _STL {
template <> Rva002D0A11Records &Rva002D0A11Records::operator=(const Rva002D0A11Records &);
}

class Rva002D0A11
{
public:
	Rva002D0A11 &operator=(const Rva002D0A11 &other);
private:
	Rva002D0A11Records m_records;
};

Rva002D0A11 &Rva002D0A11::operator=(const Rva002D0A11 &other)
{
	m_records = other.m_records;
	return *this;
}
