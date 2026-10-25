// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// stlport
// ?setMapSize@GameInfo@@QAEXI@Z @0x00400F5A (187B):
// GameInfo::setMapSize. BFME1 GameInfo.cpp donor verbatim (DEBUG_LOG compiled
// out) with the same BFME2 deltas as the setMapCRC twin 0x00400E9F: SLOT_PLAYER
// 6 via inlined isHuman plus direct m_hasMap at +0x09, MapMetaData CRC at +0x2C
// (node+0x40) compared against m_mapCRC at +0x44 (donor copy-paste, also in
// retail), m_map at +0x40, stored field m_mapSize at +0x48, m_inGame at +0x10,
// getLocalSlotNum at vtable +0x34 slot 13. TheMapCache at 0x00DFF12C,
// AsciiString copy/toLower/release via 0x365F0/0x36A70/0x36410, getSlot rowed
// 0x3FF29F. Twin of setMapCRC differing only by stored offset. No new pins.
#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits> &a, const _Rb_tree_iterator<T, RightTraits> &b)
{ return a._M_node != b._M_node; }
}

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

template <typename T> struct BfmeStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};

#include "ascii_string.h"


bool operator<(const AsciiString &left, const AsciiString &right);

namespace _STL
{
template <> struct less<AsciiString>
{
	bool operator()(const AsciiString &left, const AsciiString &right) const
	{
		return left < right;
	}
};
}

class MapMetaData
{
public:
	MapMetaData(const MapMetaData &other);
	~MapMetaData();
	char m_pad00[0x20];
	Int m_numPlayers;
	char m_pad24[0x08];
	UnsignedInt m_CRC;
	char m_rest[0x100 - 0x30];
};

class MapCache : public _STL::map<AsciiString, MapMetaData>
{
};

extern MapCache *TheMapCache;

#include "unicode_string.h"

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
	virtual Int getLocalSlotNum() const = 0;
	virtual void slot38() = 0;
	virtual void slot3c() = 0;
	virtual void slot40() = 0;
	virtual void closeOpenSlots();

	GameSlot *getSlot(Int slotNum);
	void setSlot(Int slotNum, GameSlot slotInfo);
	void setMapSize(UnsignedInt mapSize);
	Int getMaxPlayers();
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
	char m_pad38[0x08];
	AsciiString m_mapName;
	UnsignedInt m_mapCRC;
	UnsignedInt m_mapSize;
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

inline Bool GameSlot::isHuman() const
{
	return m_state == SLOT_PLAYER;
}

Int GameInfo::getMaxPlayers()
{
	if (!TheMapCache)
		return -1;
	AsciiString lowerMap = m_mapName;
	((StringBase<char> &)(lowerMap)).toLower();
	_STL::map<AsciiString, MapMetaData>::iterator it = TheMapCache->find(lowerMap);
	if (it != TheMapCache->end()) {
		MapMetaData tmp(it->second);
		Int n = tmp.m_numPlayers;
		return n;
	}
	return -1;
}

void GameInfo::setMapSize(UnsignedInt mapSize)
{
	m_mapSize = mapSize;
	if (!TheMapCache)
		return;
	if (m_inGame && getLocalSlotNum() >= 0) {
		AsciiString lowerMap = m_mapName;
		((StringBase<char> &)(lowerMap)).toLower();
		_STL::map<AsciiString, MapMetaData>::iterator it = TheMapCache->find(lowerMap);
		if (it == TheMapCache->end()) {
			GameSlot *slot = getSlot(getLocalSlotNum());
			if (slot->isHuman())
				slot->m_hasMap = false;
		} else if (m_mapCRC != it->second.m_CRC) {
			GameSlot *slot = getSlot(getLocalSlotNum());
			if (slot->isHuman())
				slot->m_hasMap = false;
		} else {
			GameSlot *slot = getSlot(getLocalSlotNum());
			if (slot->isHuman())
				slot->m_hasMap = true;
		}
	}
}
