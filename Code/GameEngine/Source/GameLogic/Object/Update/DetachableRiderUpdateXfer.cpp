// cl: /DNDEBUG /MD
//
// ?xfer@DetachableRiderUpdate@@MAEXPAVXfer@@@Z, retail 0x004AE7AD, 72 bytes.
// Virtual slot 3 (offset 0x0C) of vtable 0x00855468 (slot 0 deleting dtor at
// 0x004AE8DE, slot 2 name getter at 0x004AE7A7 returning the
// DetachableRiderUpdate string, slot 4 pool-key body at 0x004AE832).
// Version(1,1) via Xfer slot 0x28, then base UpdateModule xfer via rowed
// 0x0044DF9F, then bools at +0x20/+0x21 via Xfer slot 0x90. Layout is the
// rowed ctor TU DetachableRiderUpdateCtorModuleFactoryBody.cpp (UpdateModule
// base 0x20 plus m_flag20 at +0x20 plus m_flag21 at +0x21, 0x24 allocation).
// Recipe is the AIGateUpdateXfer/BloodthirstyUpdateXfer Version-first slot-3
// pattern with protected xfer.

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
	UpdateModule(Thing *thing, const ModuleData *data);
	virtual ~UpdateModule();
	void xfer(Xfer *xfer);

private:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_updateState;
};

class DetachableRiderUpdate : public UpdateModule
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	bool m_flag20;
	bool m_flag21;
};

void DetachableRiderUpdate::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 1);
	*xfer == version;
	UpdateModule::xfer(xfer);
	*xfer == m_flag20;
	*xfer == m_flag21;
}
