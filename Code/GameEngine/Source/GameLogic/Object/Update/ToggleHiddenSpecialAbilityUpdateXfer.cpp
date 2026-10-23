// cl: /DNDEBUG /MD
// ?xfer@ToggleHiddenSpecialAbilityUpdate@@MAEXPAVXfer@@@Z @0x004AE25C 42B slot 3.
// Retail runs Xfer::Version1, xfers uint at +0x88 via Xfer reverse-overload
// slot 0x78, then base SpecialAbilityUpdate::xfer. Evidence: vslot lane
// slot 3 of 0x008552D8; donor ToggleHiddenSpecialAbilityUpdate.cpp m_hidden;
// base size 0x88 from SpecialAbilityUpdateXfer TU and ctor TU m_88.

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

class SpecialAbilityUpdate
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	unsigned char m_pad[0x88 - 4];
};

class ToggleHiddenSpecialAbilityUpdate : public SpecialAbilityUpdate
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	unsigned int m_88;
};

void ToggleHiddenSpecialAbilityUpdate::xfer(Xfer *xfer)
{
	xfer->Version1();
	*xfer == m_88;
	SpecialAbilityUpdate::xfer(xfer);
}
