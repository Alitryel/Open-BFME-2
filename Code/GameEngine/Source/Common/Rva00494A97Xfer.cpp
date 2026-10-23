// cl: /MD
//
// ?xfer@Rva00494A97@@MAEXPAVXfer@@@Z, retail 0x00494BBA, 42 bytes. Virtual
// slot 3 (offset 0x0C) of vtable 0x0084EA54 (class of rowed dtor
// ??1Rva00494A97@@UAE@XZ in OpaqueScalarDeletingDtors.cpp): Version1 via
// rowed 0x000053EE then base Rva00589079 xfer via rowed 0x00589215 then bool
// at +0x38 via Xfer slot 0x90 (bool overload, cf. DeflectSpecialPower xfer
// 0x004C5571 which xfers bytes at +0x3C/+0x3D via the same slot). Layout is
// Rva00589079 base 0x38 plus bool (base ends at +0x38 with float at +0x34).

class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
struct Coord3DBase
{
	float x;
	float y;
	float z;
};
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

class Rva00589079_E1
{
public:
	virtual void fe();
};

class Rva00589079_E2
{
public:
	virtual void fe();
};

class Rva00589079 : public UpdateModule, public Rva00589079_E1, public Rva00589079_E2
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	unsigned int m_28;
	int m_2C;
	unsigned int m_30;
	float m_34;
};

class Rva00494A97 : public Rva00589079
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	bool m_38;
};

void Rva00494A97::xfer(Xfer *xfer)
{
	xfer->Version1();
	Rva00589079::xfer(xfer);
	*xfer == m_38;
}
