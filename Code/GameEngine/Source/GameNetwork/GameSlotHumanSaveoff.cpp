// cl: /O1

// GameSlot human test and original-info save-off: the two frameless
// accessors retail keeps outlined beside isOccupied (0x003FF0FB). BFME1
// GameInfo.cpp donors verbatim (DEBUG_LOG compiled out); the layout is the
// XferEnumHelpers GameSlot map (state@4, color@C, startPos@10,
// template@18, origColor@24, origStartPos@28, origTemplate@2C).

typedef int Int;
typedef bool Bool;

enum SlotState
{
	SLOT_OPEN = 0,
	SLOT_CLOSED = 1,
	SLOT_EASY_AI = 2,
	SLOT_MED_AI = 3,
	SLOT_BRUTAL_AI = 4,
	SLOT_AI_5 = 5,
	SLOT_PLAYER = 6
};

class GameSlot
{
public:
	Bool isHuman() const;
	void saveOffOriginalInfo();

private:
	void *m_vtable;                 // +0x00
	Int m_state;                    // +0x04
	Bool m_isAccepted;              // +0x08
	Bool m_hasMap;                  // +0x09
	Bool m_isMuted;                 // +0x0A
	char m_pad0B[1];                // +0x0B
	Int m_color;                    // +0x0C
	Int m_startPos;                 // +0x10
	Int m_bfme14;                   // +0x14
	Int m_playerTemplate;           // +0x18
	Int m_teamNumber;               // +0x1C
	Int m_bfme20;                   // +0x20
	Int m_origColor;                // +0x24
	Int m_origStartPos;             // +0x28
	Int m_origPlayerTemplate;       // +0x2C
};

// ?isHuman@GameSlot@@QBE_NXZ
// Retail 0x003FF0F1 (10B): the slot holds a human player.
inline Bool GameSlot::isHuman() const
{
	return m_state == SLOT_PLAYER;
}

// ?saveOffOriginalInfo@GameSlot@@QAEXXZ
// Retail 0x003FF0D4 (19B): snapshot the slot setup for late joiners.
void GameSlot::saveOffOriginalInfo()
{
	m_origPlayerTemplate = m_playerTemplate;
	m_origStartPos = m_startPos;
	m_origColor = m_color;
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. The anchor keeps this
// unit's copies for the rows; it is not retail code.
#pragma inline_depth(0)
// ?_bfmeGameSlotInlineAnchorGameSlotHumanSaveoff@@YAXPAVGameSlot@@@Z absent-from-retail
void _bfmeGameSlotInlineAnchorGameSlotHumanSaveoff(GameSlot *gameSlot)
{
    gameSlot->isHuman();
}
#pragma inline_depth()
