// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /MD /DNDEBUG /EHsc
// ??0Rva004BE19D@@QAE@XZ, retail 0x004BE19D, 17 bytes: a constructor whose
// only work is copy-constructing its leading AsciiString from
// AsciiString::TheEmptyString (VA 0x00DE0878) through the rowed narrow
// StringBase copy constructor 0x000365F0. No caller or vtable reference
// names the class, so it is address-derived and only that member is
// modelled. Skeleton twin of the base-forwarding ctor 0x00531121.
#include "ascii_string.h"

class Rva004BE19D
{
public:
	Rva004BE19D();

private:
	AsciiString m_name;	// +0x00
};

Rva004BE19D::Rva004BE19D() : m_name(AsciiString::TheEmptyString)
{
}
