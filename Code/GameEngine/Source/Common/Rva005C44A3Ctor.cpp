// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7 /MD
// ??0Rva005C44A3@@QAE@ABV?$StringBase@D@@@Z @0x005C44A3 32B.
// The body first delegates to Rva004FA830's matched string constructor,
// clears two dwords, then installs the vtable at 0x008745D4.
#include "ascii_string.h"

class Rva004FA830
{
public:
	virtual ~Rva004FA830();
	Rva004FA830(const StringBase<char> &);

private:
	StringBase<char> m_s;
};

const char g_00C745D4[92] = { 55,69,156,0,223,68,156,0,195,68,156,0,82,67,156,0,252,69,199,0,240,69,199,0,0,0,0,0,65,76,76,95,65,82,77,73,69,83,0,0,84,72,73,83,95,84,69,82,82,73,79,82,73,84,89,0,66,111,110,117,115,75,101,121,0,0,0,0,83,116,114,101,110,103,116,104,101,110,105,110,103,82,97,110,103,101,0,0,0,0,0,0 };

class Rva005C44A3 : public Rva004FA830
{
public:
	Rva005C44A3(const StringBase<char> &);

private:
	int m_08;
	int m_0c;
};

Rva005C44A3::Rva005C44A3(const StringBase<char> &value)
	: Rva004FA830(value), m_08(0), m_0c(0)
{
	*(const char **)this = g_00C745D4;
}
