// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??0Rva001ED03C@@QAE@ABV0@@Z, retail 0x001ED03C, 109 bytes.
// Evidence: unlock lane copy ctor; callees rowed StringBase 0x000365F0 vector 0x000BC07E Rva001ECF66 0x001ECF66; caller 0x001ED20D.
#include <vector>

#include "ascii_string.h"

class Rva001ECF66
{
public:
	Rva001ECF66(const Rva001ECF66 &other);
};

class Rva001ED03C
{
public:
	Rva001ED03C(const Rva001ED03C &other);
private:
	AsciiString m_00;
	AsciiString m_04;
	AsciiString m_08;
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > m_0c;
	Rva001ECF66 m_18;
};

Rva001ED03C::Rva001ED03C(const Rva001ED03C &other)
	: m_00(other.m_00),
	  m_04(other.m_04),
	  m_08(other.m_08),
	  m_0c(other.m_0c),
	  m_18(other.m_18)
{
}
