// cl: /MD
// ?rva00468FB4@Rva00468FB4@@QAEXPAVXfer@@@Z at retail 0x00468FB4 (40B). Unlock
// body calling rowed Xfer::Version1 0x000053EE plus pinned
// Rva003063A9XferThingTemplate 0x003063A9 plus Xfer slot 0x7C (int
// operator==). Evidence: callers at 0x0047513D and 0x0047516B in unclaimed
// 0x00474EA8; ThingTemplate pointer at +0x00 plus int at +0x04; ret 4 with
// Xfer stack arg.
class AsciiString;
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

#include "../../../../Include/Common/BfmeXfer.h"

class ThingTemplate;

void Rva003063A9XferThingTemplate(Xfer *xfer, const ThingTemplate **thing);

class Rva00468FB4
{
public:
	void rva00468FB4(Xfer *xfer);

private:
	const ThingTemplate *m_thing;
	int m_int;
};

void Rva00468FB4::rva00468FB4(Xfer *xfer)
{
	xfer->Version1();
	Rva003063A9XferThingTemplate(xfer, &m_thing);
	*xfer == m_int;
}
