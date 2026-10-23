// cl: /O1 /Oy- /arch:SSE /G7 /DNDEBUG /MD
// Native Ghidra 00306703..0030675A: 87 bytes, cdecl (Xfer*, Object**).
// Xfer slot 1 is loading, as established by the rowed enum/list xfers.
// The two paths transfer ObjectID via rowed 003060B2; load resolves it through
// canonical GameLogic::findObjectByID 00049DC5 and save reads Object +74.
// Those calls establish the pointer/ID roles independently of the byte match.
// The returned Xfer* is the original first argument; helper name stays RVA-based.

#include "../../Common/GameLogicObjectLookupView.h"

class Snapshot;
class AsciiString;
class UnicodeString;
class PooledString;
class Coord3DBase;
struct ICoord3D;
struct Region3D;
struct IRegion3D;
class Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
class RealRange;
struct RGBColor;
class RGBAColorReal;
class RGBAColorInt;
struct XferUnknown11;
#include "../../../Include/Common/BfmeXfer.h"

struct Rva00306703ObjectView
{
    char unknown00[0x74];
    ObjectID id;
};

extern GameLogic *TheGameLogic;
void XferObjectID(Xfer *xfer, ObjectID *id);

Xfer *Rva00306703Xfer(Xfer *xfer, Object **object)
{
    ObjectID id;
    if (xfer->IsLoading())
    {
        XferObjectID(xfer, &id);
        *object = TheGameLogic->findObjectByID(id);
    }
    else
    {
        id = INVALID_OBJECT_ID;
        if (*object)
            id = reinterpret_cast<Rva00306703ObjectView *>(*object)->id;
        XferObjectID(xfer, &id);
    }
    return xfer;
}
