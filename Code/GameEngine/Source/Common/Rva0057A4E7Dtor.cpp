// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// Retail 0x0057A4E7: 53-byte virtual destructor, paired with the slot-0
// deleting destructor 0x0057AAD5 in Rva0057A4E7Ctor.cpp's table at 0x00C6F098.
// The constructor proves the 8-byte polymorphic base and AsciiString at +8.
// Retail tears down that string, then the base at 0x0022167C, without resetting
// either vptr. novtable preserves those observed stores and the virtual ABI;
// the previous nonvirtual member view gave callers the wrong destructor name.
#include "ascii_string.h"

class __declspec(novtable) Rva0022167C
{
public:
	virtual ~Rva0022167C();
private:
	char m_bytes[4];
};

class __declspec(novtable) Rva0057A4E7 : public Rva0022167C
{
public:
	virtual ~Rva0057A4E7();
private:
	AsciiString m_at08;
};

Rva0057A4E7::~Rva0057A4E7()
{
}
