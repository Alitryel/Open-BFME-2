// cl: /MD
// ??0PlaceEventTranslator@@QAE@XZ, retail 0x0043216D, 29 bytes.
// Ctor stores vtable 0x00C3C9C0 then zeroes +0x04..+0x10 dwords and +0x14..+0x15 bytes. Evidence: single vtable store, caller 0x0023A502, no donor.
// Identity: vtable 0x00C3C9C0 slot 0 is the rowed
// PlaceEventTranslator::translateGameMessage 0x0043218A, whose fields
// (m_downPos +4, m_downFrame +0xC, m_upFrame +0x10, m_isDown +0x14,
// m_isDragging +0x15) are exactly the ones zeroed here; the caller attaches it
// at priority 30, Zero Hour's PlaceEventTranslator slot in GameClient::init.
// Retail's vtable has a second slot, the folded deleting destructor
// 0x004296EE (??_GRva0042CBB6); this view does not model it yet.
#include "../GameClient/MessageStream/PlaceEventTranslatorView.h"

PlaceEventTranslator::PlaceEventTranslator()
{
	m_downPos.x = 0;
	m_downPos.y = 0;
	m_downFrame = 0;
	m_upFrame = 0;
	m_isDown = false;
	m_isDragging = false;
}
