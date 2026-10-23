// cl: /MD
//
// ?xfer@GhostObject@@MAEXPAVXfer@@@Z, retail 0x003059F5, 154 bytes.
// Slot 3 (offset 0x0C) of vtable 0x0080793C (class of ??1GhostObject@@UAE@XZ).
// Donor: ZH GeneralsMD GhostObject::xfer (parent ObjectID via getID at Object
// +0x74 plus XferObjectID plus IsLoading-gated findObjectByID via TheGameLogic
// plus XferException on missing plus angle then position). BFME2 repairs:
// IsLightCRC early-out via Xfer slot 0x10, Version1 via rowed 0x000053EE,
// ObjectID at +0x0C via rowed XferObjectID 0x003060B2, IsLoading via Xfer slot
// 0x04, float at +0x1C via Xfer slot 0x70, Coord3DBase at +0x10 via Xfer slot
// 0x60. Layout is Snapshot base (vptr) plus +0x04/+0x08 pad giving +0x0C parent
// (cf. retail mov [esi+0x0C] and [eax+0x74] getID), Coord (12B) at +0x10 then
// float at +0x1C (0x10+0x0C=0x1C contiguous). Recipe is PoisonedBehaviorXfer
// slot-3 pattern with Xfer decl verbatim.

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

#include "../../../Include/Common/BfmeXfer.h"

class Coord3DBase
{
public:
	float x;
	float y;
	float z;
};

#include "../../Common/GameLogicObjectLookupView.h"

void XferObjectID(Xfer *xfer, ObjectID *objectID);

// Retail ThrowInfo names the 8-byte XferException class and its rowed
// copy constructor and destructor (see Common/System/XferException.cpp).
class XferException
{
public:
	XferException(int tag, const char *format, ...);
	XferException(const XferException &that);
	~XferException();

	char *text;
	int tag;
};

class Object
{
public:
	ObjectID getID() const { return m_id; }
	unsigned char m_pad[0x74];
	ObjectID m_id;
};


extern GameLogic *TheGameLogic;

#include "../../../../../reference/shims/moduledata/Common/Snapshot.h"

class GhostObject : public Snapshot
{
protected:
	virtual void crc(Xfer *xfer);
	virtual void loadPostProcess();
	virtual void xfer(Xfer *xfer);

private:
	unsigned int m_04;
	unsigned int m_08;
	Object *m_parentObject; // +0x0C
	Coord3DBase m_10; // +0x10
	float m_1C; // +0x1C
};

void GhostObject::xfer(Xfer *xfer)
{
	if (xfer->IsLightCRC())
		return;
	xfer->Version1();
	ObjectID parentObjectID = INVALID_OBJECT_ID;
	if (m_parentObject)
		parentObjectID = m_parentObject->getID();
	XferObjectID(xfer, &parentObjectID);
	if (xfer->IsLoading()) {
		m_parentObject = TheGameLogic->findObjectByID(parentObjectID);
		if (parentObjectID != INVALID_OBJECT_ID && m_parentObject == 0) {
			throw XferException(5, 0);
		}
	}
	*xfer == m_1C;
	*xfer == m_10;
}
