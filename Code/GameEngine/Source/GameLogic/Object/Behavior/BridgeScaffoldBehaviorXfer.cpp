// cl: /MD
//
// ?xfer@BridgeScaffoldBehavior@@MAEXPAVXfer@@@Z, retail 0x00458638,
// 115 bytes. Slot 3 (offset 0x0C) of vtable 0x00840C54 (class of rowed ctor
// ??0BridgeScaffoldBehavior@@QAE@PAVThing@@PBVModuleData@@@Z in
// BridgeScaffoldBehaviorCtor.cpp): base UpdateModule xfer via rowed
// 0x0044DF9F then IsLightCRC early-out via Xfer slot 0x10 then Version1 via
// rowed 0x000053EE then enum at +0x24 via rowed XferScaffoldTargetMotion
// 0x00305DFA then three coords at +0x28/+0x34/+0x40 via Xfer slot 0x60 plus
// two floats at +0x4C/+0x50 via Xfer slot 0x70 plus coord at +0x54 via slot
// 0x60. Layout is the rowed ctor shape (UpdateModule base 0x20 plus one
// interface vptr at +0x20 giving +0x24 start); donor is ZH
// BridgeScaffoldBehavior::xfer (xferVersion first plus xferUser/xferCoord3D/
// xferReal) with BFME2 base-first plus light-CRC plus Version1 order.

#include "BridgeScaffoldXferPrefix.h"
#include "BridgeScaffoldBehaviorView.h"

void XferScaffoldTargetMotion(Xfer *xfer, int *value);

void BridgeScaffoldBehavior::xfer(Xfer *xfer)
{
	UpdateModule::xfer(xfer);
	if (xfer->IsLightCRC())
		return;
	xfer->Version1();
	XferScaffoldTargetMotion(xfer, (int *)&m_targetMotion);
	*xfer == *(Coord3DBase *)&m_createPos;
	*xfer == *(Coord3DBase *)&m_riseToPos;
	*xfer == *(Coord3DBase *)&m_buildPos;
	*xfer == m_lateralSpeed;
	*xfer == m_verticalSpeed;
	*xfer == *(Coord3DBase *)&m_targetPos;
}
