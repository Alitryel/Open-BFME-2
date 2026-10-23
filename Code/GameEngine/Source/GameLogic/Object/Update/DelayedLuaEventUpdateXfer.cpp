// cl: /DNDEBUG /MD /GX
//
// ?xfer@DelayedLuaEventUpdate@@MAEXPAVXfer@@@Z, retail 0x004A8E0A, 113 bytes.
// Slot 3 (offset 0x0C) of vtable 0x00853A5C, same primary as rowed ctor
// 0x004A8E7B and dtor 0x004A8D4A and deleting dtor 0x004A8EEF. Base
// UpdateModule xfer via rowed 0x0044DF9F, IsLightCRC early-out via Xfer slot
// 0x10, Version(1,1) via Xfer slot 0x28, float at +0x70 via slot 0x70, bools
// at +0x74/+0x75 via slot 0x90, uint at +0x20 via XferRawBytes slot 0x24,
// then member DelayedLuaEventList at +0x24 via its slot-3 xfer (rowed
// 0x003316D2). Layout is the rowed class (UpdateModule base 0x20 plus m_f20
// +0x20 plus events +0x24 size 0x4C plus m_f70 +0x70 plus flags +0x74/+0x75)
// from DelayedLuaEventUpdateCtor/Dtor. Recipe is the InvisibilityUpdateXfer
// slot-3 pattern with DelayedLuaEventListXfer Version(1,1) and float/bool
// slots.

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

class DelayedLuaEventList
{
public:
	virtual ~DelayedLuaEventList();
	virtual void crc(Xfer *xfer);
	virtual void loadPostProcess();
	virtual void xfer(Xfer *xfer);

private:
	char m_pad[0x48];
};

class DelayedLuaEventUpdate : public UpdateModule
{
public:
	DelayedLuaEventUpdate(Thing *thing, const ModuleData *moduleData);

protected:
	virtual void xfer(Xfer *xfer);

private:
	unsigned int m_f20;
	DelayedLuaEventList m_events;
	float m_f70;
	bool m_f74;
	bool m_f75;
};

void DelayedLuaEventUpdate::xfer(Xfer *xfer)
{
	UpdateModule::xfer(xfer);
	if (xfer->IsLightCRC())
		return;
	Xfer::Version version(1, 1);
	*xfer == version;
	*xfer == m_f70;
	*xfer == m_f74;
	*xfer == m_f75;
	xfer->XferRawBytes(&m_f20, 4);
	m_events.xfer(xfer);
}
