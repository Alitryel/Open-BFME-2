// cl: /MD
// ?xfer@Rva00564522@@QAEXPAVXfer@@@Z @0x00564522 45B.
// Xfer tail for the +0x10 subobject of Rva003AE2A9 (caller 0x0056454F is
// its slot-3 xfer and passes this+0x10): Version1 via rowed 0x000053EE,
// float at +4 via Xfer slot 0x70 (==(float&)), bool at +0xC via Xfer slot
// 0x90 (==(bool&)). Slots are the reversed-overload layout the verbatim
// Xfer declaration reproduces: ==(float&) is 9th declared of 27 so it
// sits at 10+(27-9)=28, ==(bool&) 1st so at 10+(27-1)=36.
// Unblocks 0x0056454F. Member types stay undeclared beyond their retail
// offsets (+4, +0xC) and overload-selected static types.

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

#include "../../Include/Common/BfmeXfer.h"

class Rva00564522
{
public:
	void xfer(Xfer *xfer);
};

void Rva00564522::xfer(Xfer *xfer)
{
	xfer->Version1();
	*xfer == *(float *)((char *)this + 4);
	*xfer == *(bool *)((char *)this + 0xC);
}
