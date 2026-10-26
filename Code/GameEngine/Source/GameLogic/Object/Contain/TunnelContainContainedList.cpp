// cl: /O1 /DNDEBUG /MD
// stlport
// ?rva0047DD0F@TunnelContain@@UAE?AVRva0036AE51ListView@@XZ retail
// 0x0047DD0F, 30 bytes: slot 33 of TunnelContain's primary vtable
// (0x00847740; its object pointer is the +0x08 member, as in
// TunnelContain.cpp). Zero Hour's TunnelContain answers its contained-items
// list from the owning player's tunnel system; BFME 2 returns the tunnel
// tracker's (+0x2E8) two-pointer list view by value through the rowed
// Rva00466398::rva00466398 0x00466398, with no null checks.
#include "TunnelContainView.h"

Rva0036AE51ListView TunnelContain::rva0047DD0F()
{
	Player *owningPlayer = m_object->getControllingPlayer();
	return ((Rva00466398 *)owningPlayer->m_2E8)->rva00466398();
}
