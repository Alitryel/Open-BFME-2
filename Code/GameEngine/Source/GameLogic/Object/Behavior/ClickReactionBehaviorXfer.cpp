// cl: /DNDEBUG /MD
//
// ?xfer@ClickReactionBehavior@@MAEXPAVXfer@@@Z, retail 0x00459579, 50 bytes.
// Slot 3 (offset 0x0C) of vtable 0x0084125C: Version1 via rowed 0x000053EE,
// base UpdateModule xfer via rowed 0x0044DF9F, then int at +0x24 via Xfer
// slot 0x7C plus int at +0x28 via Xfer slot 0x7C.

#include "ClickReactionXferPrefix.h"

#include "ClickReactionBehaviorView.h"

void ClickReactionBehavior::xfer(Xfer *xfer)
{
	xfer->Version1();
	UpdateModule::xfer(xfer);
	*xfer == m_clicks;
	*xfer == m_cooldown;
}
