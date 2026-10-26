#ifndef BFME2_REPAIR_DOCK_UPDATE_VIEW_H
#define BFME2_REPAIR_DOCK_UPDATE_VIEW_H

// Shared pool-key and transfer receiver. The existing transfer body proves
// the +0x88 ObjectID and +0x8C float after the opaque DockUpdate base.
// This partial view does not establish the constructor or action interfaces.
class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
struct Coord3DBase;
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

enum NameKeyType
{
	NK_UNKNOWN = 0
};

enum ObjectID
{
	INVALID_ID = 0
};

void XferObjectID(Xfer *xfer, ObjectID *objectID);

class __declspec(novtable) DockUpdate
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	char m_pad[0x88 - 4];
};

class RepairDockUpdate : public DockUpdate
{
public:
	virtual NameKeyType getModuleNameKey() const;
protected:
	virtual void xfer(Xfer *xfer);

private:
	ObjectID m_lastRepair;
	float m_healthToAddPerFrame;
};


#endif
