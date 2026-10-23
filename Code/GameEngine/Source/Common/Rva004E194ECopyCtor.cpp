// ??0Rva004E194E@@QAE@ABV0@@Z @0x0052BE96 51B copy ctor vtable 0x00861CA8 ints plus StringBase via rowed 0x000365F0 caller 0x0052C3F3
// cl: /Ireference/shims/bfme2_ascii /MD
#include "ascii_string.h"

class Rva004E194E
{
public:
	virtual ~Rva004E194E();
	Rva004E194E(const Rva004E194E &other);
private:
	int m_04;
	int m_08;
	AsciiString m_0C;
	unsigned char m_10;
};

Rva004E194E::Rva004E194E(const Rva004E194E &other) : m_04(other.m_04), m_08(other.m_08), m_0C(other.m_0C), m_10(other.m_10)
{
}
