// cl: /DNDEBUG /MD
// ?xfer@ObjectDefectionHelper@@MAEXPAVXfer@@@Z, RVA 0x004DF76E, 84 bytes.
// Slot 3 of vtable 0x007FBD40 (class of ObjectDefectionHelper ctor 0x0028C955).
// Base Rva004DF81B xfer via rowed 0x004DF81B then IsLightCRC early-out via Xfer slot 0x10
// then Version1 via rowed 0x000053EE then uint at +0x20 plus uint at +0x24 via Xfer slot 0x78
// plus float at +0x28 via Xfer slot 0x70 plus bool at +0x2C via Xfer slot 0x90.
// Layout is the rowed 0x30-byte class from ObjectDefectionHelperCtor.cpp
// (ObjectHelper base 0x20 plus uint uint float bool). Recipe is the
// OneRingPenaltyUpdateXfer slot-3 pattern.
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

class Rva004DF81B
{
public:
	void xfer(Xfer *xfer);
};

class ObjectDefectionHelper
{
protected:
	virtual void xfer(Xfer *xfer);
private:
	char m_pad[0x20 - 4];
	unsigned int m_20;
	unsigned int m_24;
	float m_28;
	bool m_2C;
};

void ObjectDefectionHelper::xfer(Xfer *xfer)
{
	((Rva004DF81B *)this)->xfer(xfer);
	if (xfer->IsLightCRC())
		return;
	xfer->Version1();
	*xfer == m_20;
	*xfer == m_24;
	*xfer == m_28;
	*xfer == m_2C;
}
