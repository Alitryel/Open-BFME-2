// cl: /DNDEBUG /MD
//
// ?xfer@DemoTrapUpdate@@MAEXPAVXfer@@@Z, retail 0x00495A74, 53 bytes.
// Slot 3 (offset 0x0C) of vtable 0x0084ED3C (class of rowed dtor ??1Rva00495916
// and ctor ??0DemoTrapUpdate at 0x004959B1). Version1 via rowed 0x000053EE
// then base UpdateModule xfer via rowed 0x0044DF9F then int at +0x20 via Xfer
// slot 0x7C plus bool at +0x24 via Xfer slot 0x90. Layout is rowed 0x28-byte
// class (UpdateModule base 0x20 plus m_nextScanFrames/m_detonated) from
// DemoTrapUpdateConstructor.cpp. Donor is ZH DemoTrapUpdate::xfer (xferVersion
// plus base plus xferInt/xferBool); BFME2 uses Version1 plus operator==.

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

class ObjectModule
{
public:
	ObjectModule(Thing *, const ModuleData *);
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

class DemoTrapUpdate : public UpdateModule
{
public:
	DemoTrapUpdate(Thing *thing, const ModuleData *moduleData);

protected:
	virtual void xfer(Xfer *xfer);

private:
	int m_nextScanFrames;
	bool m_detonated;
};

void DemoTrapUpdate::xfer(Xfer *xfer)
{
	xfer->Version1();
	UpdateModule::xfer(xfer);
	*xfer == m_nextScanFrames;
	*xfer == m_detonated;
}
