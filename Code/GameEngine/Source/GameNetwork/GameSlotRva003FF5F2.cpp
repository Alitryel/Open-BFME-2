// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// ?rva003FF5F2@GameSlot@@QAEXABVAsciiString@@@Z @0x003FF5F2 36B
// GameSlot AsciiString setter at +0x1a8: rowed-pin AsciiString assign
// 0x000366F0 then rowed StringBase trim 0x00037CF0 then rowed toUpper
// 0x00036B60 just landed; callers 0x005A1A0B 0x005A42BF 0x005A5180.
#include "ascii_string.h"


typedef int Int;
typedef bool Bool;
class UnicodeString;
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

class GameSlot
{
public:
	void rva003FF5F2(const AsciiString &other);
	void setState(SlotState state, UnicodeString name, const GameSlotConnectInfo *connectInfo);
	Bool isHuman() const;
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
	// Existing TU fields end at +0x30; the AsciiString setter uses +0x1A8.
	char m_pad30[0x1A8 - 0x30];
	AsciiString m_name;
};

void GameSlot::rva003FF5F2(const AsciiString &other)
{
    m_name = other;
    m_name.trim();
    m_name.toUpper();
}
