// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?isPlayer@GameSlot@@QBE_NVAsciiString@@@Z @0x003FFEF5 (109B):
// GameSlot::isPlayer, AsciiString by-value overload. BFME1
// GameSlotIsPlayerAsciiThunk.cpp donor
// (reference/open-bfme-1/.../GameNetwork/GameSlotIsPlayerAsciiThunk.cpp):
// state==SLOT_PLAYER plus translate then name compareNoCase, ret 4. BFME2
// adaptations proven by the retail bytes:
// - SLOT_PLAYER is 6 (retail cmp [ecx+4],6; ZH numbers it 5).
// - m_name sits at +0x30 (retail lea ecx,[esi+0x30]; BFME1 places it at +0x28).
// Callees already settled: UnicodeString::translate is rowed at 0x6CB6A0,
// StringBase<G>::compareNoCase is rowed at 0x6AA4,
// StringBase<G>::releaseBuffer is rowed at 0x36E70,
// StringBase<D>::releaseBuffer is rowed at 0x36410. No new pins.

typedef int Int;
typedef bool Bool;

enum SlotState
{
	SLOT_OPEN,
	SLOT_CLOSED,
	SLOT_EASY_AI,
	SLOT_MED_AI,
	SLOT_BRUTAL_AI,
	SLOT_AI_5,
	SLOT_PLAYER
};

#include "ascii_string.h"
#include "unicode_string.h"

struct GameSlotConnectInfo;



class GameSlot
{
public:
	void rva003FF5F2(const AsciiString &other);
	void setState(SlotState state, UnicodeString name, const GameSlotConnectInfo *connectInfo);
	Bool isHuman() const;
	Bool isPlayer(AsciiString userName) const;
public:
	void saveOffOriginalInfo();
private:
	void *m_vtable;
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

// Use the seed TU field view, retaining the target UnicodeString access
// at +0x30 and the separate AsciiString member at +0x1A8.
Bool GameSlot::isPlayer(AsciiString userName) const
{
	UnicodeString uName;
	uName.translate(userName);
	Bool result;
	if (m_state == SLOT_PLAYER && text30.compareNoCase(uName) == 0)
		result = true;
	else
		result = false;
	return result;
}
