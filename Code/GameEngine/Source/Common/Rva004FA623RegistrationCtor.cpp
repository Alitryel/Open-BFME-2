// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ??0Rva004FA623@@QAE@ABVAsciiString@@@Z, retail 0x004FA623, 24 bytes.
// Derived constructor of the counted-note registration family: it calls the
// rowed base constructor 0x0052B894 (registers the name, writes the base
// vptr) and then installs vtable VA 0x00C63398 - the same derived vtable the
// "SpawnArmy" startup initializer 0x007B33C5 (Rva007B4874Registrations.cpp)
// writes by hand after building that global in place. Skeleton twin of the
// derived copy constructor 0x004CA125. The application class is unknown;
// the name is address-derived.

#include "ascii_string.h"

class Rva0052B894Registration
{
public:
	Rva0052B894Registration(const AsciiString &name);
	virtual ~Rva0052B894Registration();
};

class Rva004FA623 : public Rva0052B894Registration
{
public:
	Rva004FA623(const AsciiString &name);
	virtual ~Rva004FA623();
};

Rva004FA623::Rva004FA623(const AsciiString &name)
	: Rva0052B894Registration(name)
{
}
