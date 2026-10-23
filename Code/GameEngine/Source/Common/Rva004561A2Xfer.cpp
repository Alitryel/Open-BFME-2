// cl: /MD
//
// ?xfer@Rva004561A2@@MAEXPAVXfer@@@Z, retail 0x004562C0, 56 bytes. Virtual
// slot 3 (offset 0x0C) of vtable 0x008406D4 (class of rowed dtor
// ??1Rva004561A2@@UAE@XZ in Rva0024A797Derived.cpp): Version1 via rowed
// 0x53EE then base UpdateModule xfer via rowed 0x44DF9F then two bools at
// +0x20/+0x21 via Xfer slot 0x90. Layout is UpdateModule base 0x20 plus
// two bools. Identity is slot 3 plus the UpdateModule base call; class
// name stays honest Rva address name.

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

#include "../../Include/Common/BfmeXfer.h"

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

class Rva004561A2 : public UpdateModule
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	bool m_20;
	bool m_21;
};

void Rva004561A2::xfer(Xfer *xfer)
{
	xfer->Version1();
	UpdateModule::xfer(xfer);
	*xfer == m_20;
	*xfer == m_21;
}
