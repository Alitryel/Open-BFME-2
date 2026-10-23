// cl: /MD
//
// ?xfer@DelayedDeathBody@@MAEXPAVXfer@@@Z, retail 0x004C17CC, 62 bytes.
// Slot 3 (offset 0x0C) of vtable 0x0085BBE8 (class of ??0DelayedDeathBody
// rowed at 0x004C15B9 in DelayedDeathBodyCtor.cpp).
//
// Retail: Version1 via rowed 0x000053EE, then byte at +0x100 and byte at
// +0x101 each via Xfer slot 0x90 (the bool overload), then base
// ImmortalBody::xfer via rowed 0x004C20BA. No IsLightCRC in retail.
// Layout is ImmortalBody base 0x100 plus two bytes. The ctor TU models the
// tail as unsigned char, but the slot-0x90 call is the bool overload (same
// as the two slot-0x90 bools in Rva004C1866Xfer), so they are bool here.
// The direct base is RespawnBody per the ctor TU; it adds no xfer override,
// so retail reaches ImmortalBody::xfer and this TU calls it directly.
// Shape follows Rva004C1866Xfer/BodyModuleXfer slot-3 pattern.

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

class ImmortalBody
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	char m_pad04[0x100 - 4];
};

class DelayedDeathBody : public ImmortalBody
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	bool m_b100; // +0x100
	bool m_b101; // +0x101
};

void DelayedDeathBody::xfer(Xfer *xfer)
{
	xfer->Version1();
	*xfer == m_b100;
	*xfer == m_b101;
	ImmortalBody::xfer(xfer);
}
