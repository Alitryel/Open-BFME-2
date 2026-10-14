// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ICF twin of ??4BfmeAssignRecord172@@QAEAAU0@ABU0@@Z (0x001EB20E,
// BfmeAssignRecord172Assign.cpp): the element of the STLport sweep at
// 0x001EB86E is the same 172-byte record, and its assignment is that body.
// Same flags and layout as the owner.
#include "ascii_string.h"
class Rva001EAFC1
{
public:
	Rva001EAFC1 &operator=(const Rva001EAFC1 &other);
private:
	unsigned char m_data[24];
};
struct Block128 { int a[32]; };
struct Rva001EB86EElement
{
	int m_00;
	AsciiString m_04;
	int m_08;
	int m_0C;
	Block128 m_10;
	int m_90;
	Rva001EAFC1 m_94;
	Rva001EB86EElement &operator=(const Rva001EB86EElement &other);
};
Rva001EB86EElement &Rva001EB86EElement::operator=(const Rva001EB86EElement &other)
{
	m_04 = other.m_04;
	m_08 = other.m_08;
	m_0C = other.m_0C;
	m_10 = other.m_10;
	m_90 = other.m_90;
	m_94 = other.m_94;
	return *this;
}
