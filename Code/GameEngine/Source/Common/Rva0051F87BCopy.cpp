// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva0051F87B@@QAE@ABV0@@Z @ 0x0051F87B, 165 bytes.
// Copy ctor for 0x50-byte record with vtable 0x0086745C at +0: UnicodeString
// at +4 via rowed StringBase@G 0x00037050, int at +8, AsciiString at +0xC via
// rowed StringBase@D 0x000365F0, int at +0x10, Rva0039C151 at +0x14 via rowed
// 0x0051ECC3, Rva004EE501 at +0x20 via rowed 0x0051ED0A, three
// vector<unsigned> at +0x2C/+0x38/+0x44 via rowed 0x002CFAB9. Evidence:
// chain from 0x0051ED0A; callers 0x0051F920 0x005205DA; vtable store at [this]
// names ctor; offsets from lea/push pairs; precedent Rva0036105BCopyCtor.cpp.
#include <vector>

#include "ascii_string.h"
#include "unicode_string.h"

class Rva0039C151
{
public:
	Rva0039C151(const Rva0039C151 &other);
	~Rva0039C151();
private:
	char m_data[12];
};

class Rva004EE501
{
public:
	Rva004EE501(const Rva004EE501 &other);
	~Rva004EE501();
private:
	char m_data[12];
};

class Xfer0051FFF5;

class Rva0051F87B
{
public:
	virtual void Rva0051FFF5(Xfer0051FFF5 *x);
	Rva0051F87B(const Rva0051F87B &other);
private:
	UnicodeString m_04;
	int m_08;
	AsciiString m_0C;
	int m_10;
	Rva0039C151 m_14;
	Rva004EE501 m_20;
	_STL::vector<unsigned int, _STL::allocator<unsigned int> > m_2C;
	_STL::vector<unsigned int, _STL::allocator<unsigned int> > m_38;
	_STL::vector<unsigned int, _STL::allocator<unsigned int> > m_44;
};

Rva0051F87B::Rva0051F87B(const Rva0051F87B &other)
	: m_04(other.m_04)
	, m_08(other.m_08)
	, m_0C(other.m_0C)
	, m_10(other.m_10)
	, m_14(other.m_14)
	, m_20(other.m_20)
	, m_2C(other.m_2C)
	, m_38(other.m_38)
	, m_44(other.m_44)
{
}
