// cl: /O1 /arch:SSE /G7 /EHsc /MD /Ireference/shims/bfme2_ascii
//
// ICF twin of ??1Rva001EB63C@@QAE@XZ (0x001EB63C, Rva001EB05EDtor.cpp): the
// 216-byte element of the STLport vector at 0x002E2D10 is the same record
// (member at +0xB0 with its own destructor, strings at +0xD0/+0xD4), and its
// destructor is that body.
#include "ascii_string.h"
#include "unicode_string.h"

class Rva001EB05E
{
public:
	~Rva001EB05E();
private:
	char m_pad00[0xC];
	UnicodeString m_0C;
	AsciiString m_10;
};

struct Rva002E2D10Record
{
	~Rva002E2D10Record();
private:
	char m_pad00[0xB0];
	Rva001EB05E m_B0;
	char m_padC4[0xD0 - 0xC4];
	AsciiString m_D0;
	AsciiString m_D4;
};

Rva002E2D10Record::~Rva002E2D10Record()
{
}
