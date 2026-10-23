// cl: /DNDEBUG /MD
//
// ?xfer@GiveUpgradeUpdate@@MAEXPAVXfer@@@Z, retail 0x0049C41C, 85 bytes.
// Slot 3 (offset 0x0C) of vtable 0x00851220 (class of ??0GiveUpgradeUpdate
// rowed at 0x0049C3AC in GiveUpgradeUpdateCtor.cpp).
//
// Evidence: rowed base ?xfer@SpecialAbilityUpdate@@MAEXPAVXfer@@@Z at
// 0x0044F996, IsLightCRC early-out via Xfer slot 0x10, Version1 via rowed
// 0x000053EE, then bool at +0x88 via Xfer slot 0x90, float at +0x8C via Xfer
// slot 0x70, bool at +0x89 via Xfer slot 0x90. Layout is the rowed
// GiveUpgradeUpdate class from GiveUpgradeUpdateCtor.cpp (SpecialAbilityUpdate
// base 0x88 plus bool m_firstFlag at +0x88 plus bool m_secondFlag at +0x89
// plus float m_value at +0x8C). BFME1 donor GiveUpgradeUpdate.cpp has the same
// two-bool plus trailing member shape.

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

private:
	unsigned char m_pad[0x88 - 4];
};

class GiveUpgradeUpdate : public SpecialAbilityUpdate
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	bool m_firstFlag;
	bool m_secondFlag;
	unsigned char m_pad[2];
	float m_value;
};

void GiveUpgradeUpdate::xfer(Xfer *xfer)
{
	SpecialAbilityUpdate::xfer(xfer);
	if (xfer->IsLightCRC())
		return;
	xfer->Version1();
	*xfer == m_firstFlag;
	*xfer == m_value;
	*xfer == m_secondFlag;
}
