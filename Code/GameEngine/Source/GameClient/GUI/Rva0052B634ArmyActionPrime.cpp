// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD
//
// ?rva0052B634@@YAXXZ, retail 0x0052B634..0x0052B668 (52B, RET0): run the
// create entry of each of the four named living-world army-action
// registrations (Rva007B4874Registrations.cpp) once with the empty name --
// "IncreaseCommandPoints" (0x00E065B4), "SpawnArmy" (0x00E04500),
// "StrengthenArmy" (0x00E065B8) and "UpgradeTroops" (0x00E065BC). Each call
// is the registration's own vtable slot-1 body, called directly on the
// global object (ECX = the registration, AsciiString::TheEmptyString cached
// in ESI). The rowed bodies 0x0052B58F/0x004FAC99/0x0052B5C6 are spelled as
// stdcall factories (they never read ECX); this caller reaches them through
// address-named member views. No direct caller is known; the name is
// address-derived.

#include "ascii_string.h"

extern unsigned int g_Va00E04500;
extern unsigned int g_Va00E065B4;
extern unsigned int g_Va00E065B8;
extern unsigned int g_Va00E065BC;

class Rva0052B58FRegistration { public: void *rva0052B58F(const AsciiString &name); };
class Rva004FAC99Registration { public: void *rva004FAC99(const AsciiString &name); };
class Rva0052B5C6Registration { public: void *rva0052B5C6(const AsciiString &name); };
class Rva005C4A91;
class Rva0052B5FD { public: Rva005C4A91 *rva0052B5FD(const AsciiString &s); };

void rva0052B634()
{
	((Rva0052B58FRegistration *)&g_Va00E065B4)->rva0052B58F(AsciiString::TheEmptyString);
	((Rva004FAC99Registration *)&g_Va00E04500)->rva004FAC99(AsciiString::TheEmptyString);
	((Rva0052B5C6Registration *)&g_Va00E065B8)->rva0052B5C6(AsciiString::TheEmptyString);
	((Rva0052B5FD *)&g_Va00E065BC)->rva0052B5FD(AsciiString::TheEmptyString);
}

// Each retail call in this body reads an address the ledger already carries
// under the rowed name below. Bind the donor spelling to that owner so one
// address keeps one definition and the unit links.
//   5221529 reads ?Rva004FAC99Create@@YGPAVRva004FAC21@@ABV?$StringBase@D@@@Z
#pragma comment(linker, "/alternatename:?rva004FAC99@Rva004FAC99Registration@@QAEPAXABVAsciiString@@@Z=?Rva004FAC99Create@@YGPAVRva004FAC21@@ABV?$StringBase@D@@@Z")
//   5420431 reads ?rva0052B58F@@YGPAXPBX@Z
#pragma comment(linker, "/alternatename:?rva0052B58F@Rva0052B58FRegistration@@QAEPAXABVAsciiString@@@Z=?rva0052B58F@@YGPAXPBX@Z")
//   5420486 reads ?rva0052B5C6@@YGPAXPBX@Z
#pragma comment(linker, "/alternatename:?rva0052B5C6@Rva0052B5C6Registration@@QAEPAXABVAsciiString@@@Z=?rva0052B5C6@@YGPAXPBX@Z")
