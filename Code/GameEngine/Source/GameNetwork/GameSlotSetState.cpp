// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?setState@GameSlot@@QAEXW4SlotState@@VUnicodeString@@PBUGameSlotConnectInfo@@@Z @0x003FFC28 (399B):
// GameSlot::setState. BFME1 GameInfo.cpp donor (GameSlot::setState) with BFME2
// deltas proven by retail: SLOT_PLAYER 6 with new AI state 5, clear of six ints
// (color/start/bfme14 -1, template -2, team -1, bfme20 0), virtual reset at +0x10,
// GUI:Open/EasyAI/MediumAI/HardAI/BrutalAI/Closed fetch+set with EH temps,
// connectInfo 8B copy to +0x38. Callees isAI rowed 0x3FF127, set pinned 0x37150,
// releaseBuffer rowed 0x36E70. TheGameText VA 0x009FF0BC fetch slot 0x3C.

#include "GameInfoSlotView.h"

class GameTextInterface
{
public:
	virtual ~GameTextInterface() {}
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual UnicodeString fetch(const char *label, bool *exists = 0) = 0;
};

extern GameTextInterface *TheGameText;

void GameSlot::setState(SlotState state, UnicodeString name, const GameSlotConnectInfo *connectInfo)
{
	if (!(isAI() && (state == SLOT_EASY_AI || state == SLOT_MED_AI || state == SLOT_BRUTAL_AI || state == SLOT_AI_5)))
	{
		m_color = -1;
		m_startPos = -1;
		m_bfme14 = -1;
		m_playerTemplate = -2;
		m_teamNumber = -1;
		m_bfme20 = 0;
	}
	if (state == SLOT_PLAYER)
	{
		reset();
		m_state = state;
		text30 = name;
	}
	else
	{
		m_state = state;
		m_isAccepted = true;
		m_hasMap = true;
		switch (state)
		{
		case SLOT_OPEN:
			text30 = TheGameText->fetch("GUI:Open");
			break;
		case SLOT_EASY_AI:
			text30 = TheGameText->fetch("GUI:EasyAI");
			break;
		case SLOT_MED_AI:
			text30 = TheGameText->fetch("GUI:MediumAI");
			break;
		case SLOT_BRUTAL_AI:
			text30 = TheGameText->fetch("GUI:HardAI");
			break;
		case SLOT_AI_5:
			text30 = TheGameText->fetch("GUI:BrutalAI");
			break;
		case SLOT_CLOSED:
		default:
			text30 = TheGameText->fetch("GUI:Closed");
			break;
		}
	}
	connect38 = *connectInfo;
}
