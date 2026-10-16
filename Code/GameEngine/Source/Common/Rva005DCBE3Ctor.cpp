// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /MD
// ??0Rva005DCBE3@@QAE@ABVAsciiString@@H@Z @0x005DCBC7 28B
// Evidence: pin ??0Rva005DCBE3@@QAE@ABVAsciiString@@H@Z; caller 0x005AAA06 in Rva004ECECDTacticCtors.cpp; callee pin ??0Rva004ECECD@@QAE@ABVAsciiString@@H@Z; gap between rows in Rva004EDCE9Derived.cpp.
#include "ascii_string.h"

class AITactic
{
public:
	AITactic(const AsciiString &s, int n);
	virtual ~AITactic();
};

class Rva005DCBE3 : public AITactic
{
public:
	Rva005DCBE3(const AsciiString &s, int n);
	virtual ~Rva005DCBE3();
};

// ??0Rva005DCBE3@@QAE@ABVAsciiString@@H@Z
Rva005DCBE3::Rva005DCBE3(const AsciiString &s, int n) : AITactic(s, n)
{
}

// The retail call in this body reads 0x004ED3D1, an address the ledger already
// carries as ??0AITactic@@QAE@ABVAsciiString@@_N@Z. Bind the donor spelling to that rowed owner so one
// address keeps one definition and the unit links.
#pragma comment(linker, "/alternatename:??0AITactic@@QAE@ABVAsciiString@@H@Z=??0AITactic@@QAE@ABVAsciiString@@_N@Z")
