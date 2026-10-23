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
class GameMessage;
enum GameMessageDisposition
{
	KEEP_MESSAGE = 0,
	DESTROY_MESSAGE = 1
};

class PlaceEventTranslator
{
public:
	PlaceEventTranslator();
	virtual GameMessageDisposition translateGameMessage(const GameMessage *msg);
private:
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	unsigned char m_14;
	unsigned char m_15;
};

PlaceEventTranslator::PlaceEventTranslator()
	: m_04(0), m_08(0), m_0C(0), m_10(0), m_14(0), m_15(0)
{
}
