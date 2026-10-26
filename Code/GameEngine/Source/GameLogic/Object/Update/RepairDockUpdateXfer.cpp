// cl: /DNDEBUG /MD
//
// ?xfer@RepairDockUpdate@@MAEXPAVXfer@@@Z, retail 0x004A1255, 66 bytes.
// Virtual slot 3 (offset 0x0C) of vtable 0x00851C80 (class of rowed ctor
// ??0RepairDockUpdate@@QAE@PAVThing@@PBVModuleData@@@Z at 0x004A118B in
// RepairDockUpdateBehaviorCtor.cpp): base DockUpdate xfer via rowed
// 0x0058A410 then IsLightCRC early-out via Xfer slot 0x10 then Version1 via
// rowed 0x000053EE then ObjectID at +0x88 via rowed XferObjectID 0x003060B2
// then float at +0x8C via Xfer slot 0x70. Layout is DockUpdate base 0x88
// plus ObjectID plus float (ZH donor RepairDockUpdate.h: ObjectID
// m_lastRepair plus Real m_healthToAddPerFrame). Donor is ZH
// RepairDockUpdate plus BFME1 RepairDockUpdateConstructor.cpp.

#include "RepairDockUpdateView.h"

void RepairDockUpdate::xfer(Xfer *xfer)
{
	DockUpdate::xfer(xfer);
	if (xfer->IsLightCRC())
		return;
	xfer->Version1();
	XferObjectID(xfer, &m_lastRepair);
	*xfer == m_healthToAddPerFrame;
}
