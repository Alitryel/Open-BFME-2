// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?DoXfer@Rva004E1B00@@UAEXAAVXfer@@@Z retail 0x004E1302 58B: virtual slot 3
// (offset 0x0C) of vtable 0x00C61DB4 (class of unrowed dtor ??1 at 0x004E1B00
// tearing down AsciiStrings at +8 then +4 before restoring Snapshot base
// 0x00BBB554). Snapshot order is dtor plus LoadPostProcess plus
// GetSnapshotName plus DoXfer per LivingWorldRegionConnectionDtor; slot 1 is
// the shared empty ret at 0x000B3FD0 and slot 2 is the rowed string getter at
// 0x004E133C returning MoveArmy. Body is Version 1 1 via Xfer slot 0x28 then
// AsciiString at +0x04 via Xfer slot 0x6C then AsciiString at +0x08 via Xfer
// slot 0x6C. Xfer declaration mirrors GpuDrawModuleInfoDoXfer for retail
// vtable 0x00BBB910. Layout is AsciiString at +4 plus AsciiString at +8.

#include "ascii_string.h"

class UnicodeString;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;

#include "../../Include/Common/BfmeXfer.h"

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

class Rva004E1B00Base
{
public:
	virtual ~Rva004E1B00Base() {}
};

class Rva004E1B00 : public Rva004E1B00Base
{
public:
	virtual ~Rva004E1B00();
	virtual void DoXfer(Xfer &xfer);

	AsciiString m_member04;
	AsciiString m_member08;
};

void Rva004E1B00::DoXfer(Xfer &xfer)
{
	Xfer::Version version(1, 1);
	xfer == version;
	xfer == m_member04;
	xfer == m_member08;
}
