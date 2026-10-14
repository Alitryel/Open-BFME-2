// cl: /MD /DNDEBUG
// Retail 0x00092024, 14 bytes (Ghidra-unlisted, after 0x00092014 and before
// the 0x00092032 deleting-destructor thunk): zero a 0x4C-byte object through
// the CRT memset import 0x006291AE. No caller found; owner and name are
// address-derived.
#include <string.h>

struct Rva00092024Block
{
	void clear();

	char m_bytes[0x4C];
};

void Rva00092024Block::clear()
{
	memset(this, 0, sizeof(*this));
}
