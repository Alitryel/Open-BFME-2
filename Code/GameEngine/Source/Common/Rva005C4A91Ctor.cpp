// cl: /DBFME_ASCII_DTOR_DECL /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
//
// ??0Rva005C4A91@@QAE@ABV?$StringBase@D@@@Z @0x005C49EF (46B)

#include "ascii_string.h"
#include <vector>

template <typename T> class StringBase;

// The base ctor is rowed with its StringBase<char> spelling
// (??0Rva004FA830@@QAE@ABV?$StringBase@D@@@Z, Rva004FA830Ctor.cpp).
class Rva004FA830 {
public:
	virtual ~Rva004FA830();
	Rva004FA830(const StringBase<char> &s);

private:
	AsciiString m_s;
};

class Rva005C4A91 : public Rva004FA830 {
public:
	Rva005C4A91(const AsciiString &s);
	virtual ~Rva005C4A91();

private:
	unsigned int unknown08;
	_STL::vector<AsciiString> member0C;
};

Rva005C4A91::Rva005C4A91(const AsciiString &s)
	: Rva004FA830(reinterpret_cast<const StringBase<char> &>(s))
	, unknown08(4)
	, member0C()
{
}
