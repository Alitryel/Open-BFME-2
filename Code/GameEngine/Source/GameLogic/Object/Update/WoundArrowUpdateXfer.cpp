// cl: /MD
//
// ?xfer@WoundArrowUpdate@@MAEXPAVXfer@@@Z @0x004C6963 54B: slot 3 (offset 0x0C)
// of vtable 0x0085DF10 (class of ??0WoundArrowUpdate ctor 0x004C6905).
// Base SpecialAbilityUpdate xfer via rowed 0x0044F996 then IsLightCRC via Xfer
// slot 0x10 early-out then Version1 via rowed 0x000053EE then bool at +0x88
// via Xfer slot 0x90. Layout is the rowed WoundArrowUpdate class from
// WoundArrowUpdateCtor.cpp (base 0x88 plus bool at +0x88). Recipe is
// FellBeastSwoopPowerXfer slot-3 pattern with CRC gate.
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
class Thing;
class ModuleData;
class Object;
class DamageInfo;

#include "../../../../Include/Common/BfmeXfer.h"

class SpecialAbilityUpdate
{
protected:
	virtual void xfer(Xfer *xfer);
};

class WoundArrowUpdate : public SpecialAbilityUpdate
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	char m_pad[0x84];
	bool m_88;
};

void WoundArrowUpdate::xfer(Xfer *xfer)
{
	SpecialAbilityUpdate::xfer(xfer);
	if (xfer->IsLightCRC())
		return;
	xfer->Version1();
	*xfer == m_88;
}
