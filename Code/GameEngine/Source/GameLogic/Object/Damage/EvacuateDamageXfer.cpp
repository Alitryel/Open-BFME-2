// cl: /MD
//
// ?xfer@EvacuateDamage@@MAEXPAVXfer@@@Z, retail 0x004BAC83, 44 bytes.
// Virtual slot 3 (offset 0x0C) of vtable 0x00859E2C (VA 0x00C59E2C, class of
// rowed ctor ??0EvacuateDamage@@QAE@PAVThing@@PBVModuleData@@@Z in
// EvacuateDamageCtorModuleFactoryBody.cpp): Version(1,2) via Xfer slot 0x28
// then base DamageModule xfer via rowed 0x004CE56D. No members and no
// IsLightCRC early-out in retail. Recipe is the WallHubBehaviorXfer and
// ReplaceSelfUpgradeXfer 44B Version-plus-base pattern with protected xfer.

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

#include "../../../../Include/Common/BfmeXfer.h"

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

class Rva004CE56D
{
public:
	virtual void baseAnchor();
	void xfer(Xfer *xfer);
};

class EvacuateDamage : public Rva004CE56D
{
protected:
	virtual void xfer(Xfer *xfer);
};

void EvacuateDamage::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 2);
	*xfer == version;
	Rva004CE56D::xfer(xfer);
}
