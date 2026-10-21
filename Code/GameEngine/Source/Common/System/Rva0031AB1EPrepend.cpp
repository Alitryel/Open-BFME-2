// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// Reconstruction of the 89B list prepend at 0x0031AB1E: throwing
// new-expression for the 0x2CC-byte node (ctor-throw unwind deletes
// via the scopetable), copy the arg string into +0x10, then swing the
// +0x2C head through the node returning it. Reuses the rowed new,
// delete (via placement scope) and StringBase set.
#include "ascii_string.h"

void *operator new(unsigned int size);

class Rva0031AB1ENode
{
public:
	Rva0031AB1ENode();
	unsigned char m_pad[0x10];
	AsciiString m_10;
	unsigned char m_pad14[0x18 - 0x14];
	void *m_18;
	unsigned char m_tail[0x2cc - 0x1c];
};

// The 0x2CC node's constructor 0x0035B8AA is rowed as Rva0035BB4B's.
class Rva0035BB4B
{
public:
	Rva0035BB4B();
private:
	unsigned char m_bytes[0x2cc];
};

class Rva0031AB1EOwner
{
public:
	Rva0031AB1ENode *rva0031AB1E(const AsciiString *arg);
	unsigned char m_pad[0x2c];
	Rva0031AB1ENode *m_2c;
};

Rva0031AB1ENode *Rva0031AB1EOwner::rva0031AB1E(const AsciiString *asciiString)
{
	Rva0031AB1ENode *fresh = (Rva0031AB1ENode *)new Rva0035BB4B();
	fresh->m_10 = *asciiString;
	Rva0031AB1ENode *old = m_2c;
	fresh->m_18 = old;
	m_2c = fresh;
	return fresh;
}
