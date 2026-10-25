// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?setSlot@GameInfo@@QAEXHVGameSlot@@@Z, retail 0x003FFDFA, 87 bytes.
// GameInfo::setSlot: index at [ebp+8] with 0..8 range check via +0x18
// pointer array, null check, slot-0 flag tweak (word04==6 sets flag08/flag09)
// then rowed 0x002DBAB9 assign and rowed 0x002294FD dtor of by-value 0x1AC
// element (ret 0x1B0 = 4+0x1AC). Layout from BfmeSaveElementAssign.cpp and
// GameInfoClearSlotList.cpp (pad 0x18 plus 8 slots). Evidence: chain caller
// of 0x002DBAB9; unblocks 0x00448423 0x00382623 0x0040052C; prev 0x003FFDB7
// next 0x003FFEF5; callers include 0x002300D7 0x003826FB.
#include "ascii_string.h"
#include "unicode_string.h"

typedef int Int;
typedef bool Bool;

class GameSlot;
struct GameSlotConnectInfo;

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

enum { MAX_SLOTS = 8 };

class GameInfo
{
public:
	// Vtable 0x008193C8 slot 17 (+0x44); the others are not reconstructed here.
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
	virtual void slot38() = 0;
	virtual void slot3c() = 0;
	virtual void slot40() = 0;
	virtual void closeOpenSlots();

	GameSlot *getSlot(Int slotNum);
	void setSlot(Int slotNum, GameSlot slotInfo);
	void clearSlotList();
	void enterGame();
	void endGame();
	Bool isPlayerPreorder(Int index);
	void markPlayerAsPreorder(Int index);

private:
	// The existing TU verifies the preorder mask at +0x08 and the game
	// state flags at +0x10/+0x11. The slot array remains at +0x18.
	char m_pad[0x04];
	Int m_preorderMask;
	char m_pad0C[4];
	Bool m_inGame;
	Bool m_inProgress;
	char m_pad12[6];
	GameSlot *m_slot[MAX_SLOTS];
};

class GameSlot
{
	friend class GameInfo;
public:
	GameSlot &rva002DBAB9(const GameSlot &other);
	GameSlot();
	GameSlot(const GameSlot &);
	virtual ~GameSlot();
	Bool isOccupied() const;
	void rva003FF5F2(const AsciiString &other);
	void setState(SlotState state, UnicodeString name, const GameSlotConnectInfo *connectInfo);
	Bool isHuman() const;
	Bool isPlayer(AsciiString userName) const;
public:
	void saveOffOriginalInfo();
private:
	Int m_state;
private:
	Bool m_isAccepted;
private:
	Bool m_hasMap;
private:
	Bool m_isMuted;
private:
	char m_pad0B[1];
private:
	Int m_color;
private:
	Int m_startPos;
private:
	Int m_bfme14;
private:
	Int m_playerTemplate;
private:
	Int m_teamNumber;
private:
	Int m_bfme20;
private:
	Int m_origColor;
private:
	Int m_origStartPos;
private:
	Int m_origPlayerTemplate;
public:
	void setPlayerTemplate(Int playerTemplate);
private:
	// Retail isPlayer(AsciiString) reads the UnicodeString at +0x30;
	// the existing AsciiString setter still uses the separate +0x1A8 word.
	// text30 is the offset spelling already used by GameSlotCtor.cpp.
	UnicodeString text30;
	char m_pad34[0x1A8 - 0x34];
	AsciiString m_name;
};

void GameInfo::setSlot(int index, GameSlot elem)
{
	if (index < 0 || index >= 8)
		return;
	GameSlot *slot = m_slot[index];
	if (!slot)
		return;
	if (index == 0) {
		elem.m_isAccepted = 1;
		if (elem.m_state == 6)
			elem.m_hasMap = 1;
	}
	slot->rva002DBAB9(elem);
}
