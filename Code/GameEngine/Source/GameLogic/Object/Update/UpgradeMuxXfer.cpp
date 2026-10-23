// cl: /MD
//
// ?upgradeMuxXfer@UpgradeMux@@MAEXPAVXfer@@@Z, retail 0x004CE397, 34 bytes.
// Virtual slot 16 (offset 0x40) of UpgradeMux member vtable 0x0083FC88 (class
// of rowed AutoHealBehavior ctor 0x00452592, member at +0x20) and same body
// at slot 16 of ReplenishUnits/AttributeModifierAura/RadiateFear/
// ObjectCreation/AudioLoop/DetachableRider member vtables plus slot 28/32 of
// UpgradeModule-primary vtables (StealthUpgrade etc). Version1 via rowed
// 0x000053EE then bool at +0x4 via Xfer slot 0x90. Called this+0x20 by 12
// derived xfers (0x0045242B etc). Donor ZH UpgradeModule.h protected virtual
// UpgradeMux::upgradeMuxXfer plus BFME1 FireWeaponWhenDamagedBehaviorXfer.

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

class UpgradeMux
{
protected:
	virtual void upgradeMuxXfer(Xfer *xfer);

private:
	bool m_upgradeExecuted; // +4 (vptr at +0)
};

void UpgradeMux::upgradeMuxXfer(Xfer *xfer)
{
	xfer->Version1();
	*xfer == m_upgradeExecuted;
}
