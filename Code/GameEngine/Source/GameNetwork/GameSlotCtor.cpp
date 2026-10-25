// cl: /O1 /Ireference/shims/bfme2_ascii /EHsc /MD
// GameSlot::GameSlot, native 0x003FFB4C..0x003FFBB4 (104B).
// Identity: the pin names it, and the body installs the GameSlot vftable
// 0x00BE7420, the same 0x1AC-byte layout whose copy constructor 0x002295D7
// and destructor 0x002294FD are matched in SaveGameInfoCopyBFME2.cpp.
// Zero Hour's GameSlot() only calls reset(); BFME2 additionally constructs
// its owning members: the strings at +0x30/+0x34/+0x1A8, the dword/word pair
// at +0x38/+0x3C, and the CreateAHeroData at +0x64. That member's constructor
// 0x00409C3D takes (0, 0, 0, UnicodeString::TheEmptyString, -1, 0xFF707070,
// -1), the same arguments CreateAHero's loader 0x0021F47E passes to a fresh
// 0x140-byte block, so they are its default arguments. reset() is the
// rowed 0x003FF50C. Field names past the established GameInfo view are offsets.
#include "GameInfoSlotView.h"

class Xfer;

typedef char GameSlotSizeCheck[sizeof(GameSlot) == 0x1AC ? 1 : -1];

GameSlot::GameSlot()
{
	reset();
}

// GameSlot::reset, native 0x003FF50C (230B), vtable slot 4 (+0x10, the
// virtual call setState makes). Zero Hour's reset() order: state CLOSED,
// accepted false, hasMap true, muted false, color/startPos -1, template -2
// (BFME2: observer), team -1, then the orig* trio at -1 after one zeroed
// dword. BFME2 then clears both strings, the connection record, the
// +0x40..+0x60 block, reassigns a default CreateAHeroData through its
// assignment 0x00409359, sets the +0x1A4 occupancy byte and empties +0x1A8.
void GameSlot::reset()
{
	m_state = 1;
	m_isAccepted = false;
	m_hasMap = true;
	m_isMuted = false;
	m_color = -1;
	m_startPos = -1;
	m_bfme14 = -1;
	m_playerTemplate = -2;
	m_teamNumber = -1;
	m_bfme20 = 0;
	m_origColor = -1;
	m_origStartPos = -1;
	m_origPlayerTemplate = -1;
	text30.clear();
	text34.clear();
	connect38 = GameSlotConnectInfo();
	word40 = 1;
	word44 = 0;
	flag48 = false;
	word4C = -1;
	word50 = 0;
	word54 = 0;
	word58 = 0;
	word5C = -1;
	flag60 = false;
	CreateAHeroData defaultHero;
	hero64 = defaultHero;
	flag1A4 = true;
	m_name = AsciiString::TheEmptyString;
}

// GameSlot table 0x00BE7420 slot 1 (loadPostProcess, the canonical Snapshot
// order) is the shared empty RET 0x000B3FD0, as in every GameSlot-derived
// table (0x00C19424, 0x00C3E4FC).
void GameSlot::loadPostProcess()
{
}
