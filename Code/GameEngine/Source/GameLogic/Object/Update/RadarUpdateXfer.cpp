// cl: /MD
//
// ?xfer@RadarUpdate@@MAEXPAVXfer@@@Z @0x004A0CC3 76B: slot 3 xfer of RadarUpdate
// Vtable slot 3 of 0x008504EC and 0x00851A0C; prev 0x004A0CA7 deleting dtor and
// next 0x004A0D0F RadarUpdate::extendRadar. Retail calls rowed
// UpdateModule::xfer 0x0044DF9F then IsLightCRC via Xfer slot 0x10 early-out
// then rowed Version1 0x000053EE then uint at +0x20 via slot 0x78 and two
// bools at +0x24/+0x25 via slot 0x90. Layout is rowed RadarUpdate ctor TU
// (UpdateModule base 0x20 plus m_extendDoneFrame/m_extendComplete/m_radarActive).
// Recipe is PoisonedBehaviorXfer slot-3 pattern.
typedef unsigned int UnsignedInt;
typedef bool Bool;

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

class ObjectModule
{
public:
	ObjectModule(Thing *thing, const ModuleData *moduleData);
	virtual ~ObjectModule();

protected:
	const ModuleData *m_moduleData;
	Object *m_object;
};

class BehaviorModuleInterface { public: virtual void behaviorSlot(); };
class UpdateModuleInterface { public: virtual void updateSlot(); };

class UpdateModule : public ObjectModule,
	public BehaviorModuleInterface, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();
	void xfer(Xfer *xfer);

private:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_updateState;
};

class RadarUpdate : public UpdateModule
{
public:
	RadarUpdate(Thing *thing, const ModuleData *moduleData);

protected:
	virtual void xfer(Xfer *xfer);

private:
	UnsignedInt m_extendDoneFrame;
	Bool m_extendComplete;
	Bool m_radarActive;
};

void RadarUpdate::xfer(Xfer *xfer)
{
	UpdateModule::xfer(xfer);
	if (xfer->IsLightCRC())
		return;
	xfer->Version1();
	*xfer == m_extendDoneFrame;
	*xfer == m_extendComplete;
	*xfer == m_radarActive;
}
