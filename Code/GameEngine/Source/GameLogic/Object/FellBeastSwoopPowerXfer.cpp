// cl: /MD
//
// ?xfer@FellBeastSwoopPower@@MAEXPAVXfer@@@Z @0x004C6CE2 45B: slot 3 (offset 0x0C)
// of vtable 0x0085DF80 (class of ??0FellBeastSwoopPower ctor 0x004C6C1E).
// Version1 via rowed 0x000053EE then base SpecialAbilityUpdate xfer via rowed
// 0x0044F996 then bool at +0x88 via Xfer slot 0x90. Layout is the
// rowed FellBeastSwoopPower class from FellBeastSwoopPowerCtor.cpp (base
// 0x88 plus bool at +0x88). Recipe is PoisonedBehaviorXfer slot-3 pattern.
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

#include "../../../Include/Common/BfmeXfer.h"

class SpecialAbilityUpdate
{
protected:
	virtual void xfer(Xfer *xfer);
};

class FellBeastSwoopPower : public SpecialAbilityUpdate
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	char m_pad[0x84];
	bool m_88;
};

void FellBeastSwoopPower::xfer(Xfer *xfer)
{
	xfer->Version1();
	SpecialAbilityUpdate::xfer(xfer);
	*xfer == m_88;
}
