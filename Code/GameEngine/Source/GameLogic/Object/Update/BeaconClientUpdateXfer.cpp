// cl: /MD /DNDEBUG
//
// ?xfer@BeaconClientUpdate@@MAEXPAVXfer@@@Z, retail 0x004C95C9, 62 bytes.
// Virtual slot 3 (offset 0x0C) of vtable 0x0085EB30 (VA 0x00C5EB30, class of
// rowed ctor ??0BeaconClientUpdate@@QAE@PAVThing@@PBVModuleData@@@Z in
// PointDefenseLaserUpdateCtor.cpp): Version1 via rowed 0x000053EE then base
// ObjectModule xfer via rowed 0x00560AE1 then IsLightCRC early-out via Xfer
// slot 0x10 then ParticleSystemID at +0x0C via rowed XferParticleSystemID
// 0x0030600A then uint at +0x10 via Xfer slot 0x78. Layout is ObjectModule
// base 0x0C plus int at +0x0C plus uint at +0x10. Donor is ZH
// BeaconClientUpdate::xfer (xferVersion plus ClientUpdateModule base plus
// xferUser plus xferUnsignedInt); BFME2 uses Version1 plus ObjectModule base
// plus IsLightCRC guard plus helper plus operator==.

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

void XferParticleSystemID(Xfer *xfer, int *value);

class ObjectModule
{
public:
	ObjectModule(Thing *thing, const ModuleData *moduleData);
	virtual ~ObjectModule();
	void xfer(Xfer *xfer);

protected:
	const ModuleData *m_moduleData;
	Object *m_object;
};

class BeaconClientUpdate : public ObjectModule
{
public:
	BeaconClientUpdate(Thing *thing, const ModuleData *moduleData);

protected:
	virtual void xfer(Xfer *xfer);

private:
	int m_particleSystemID;
	unsigned int m_lastRadarPulse;
};

void BeaconClientUpdate::xfer(Xfer *xfer)
{
	xfer->Version1();
	ObjectModule::xfer(xfer);
	if (xfer->IsLightCRC())
		return;
	XferParticleSystemID(xfer, &m_particleSystemID);
	*xfer == m_lastRadarPulse;
}
