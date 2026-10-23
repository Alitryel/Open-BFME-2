// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// Bodies ported from Open-BFME-1's GameEngine/Source/Common/BfmeConv815.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus
// /O1). Compiled that way each body below places uniquely on unclaimed
// game.dat .text by masked whole-.text search, and ./build.sh reproduces it
// byte for byte: BfmeThingE63::isValid 0x00453124 (42B),
// BfmeThingD02::contains 0x00261353 (21B). Callee addresses are read off
// retail's call sites (reverse/symbols.csv). Only the placed bodies are
// carried; the donor's other definitions are omitted.

struct BfmeThing174
{
	unsigned char pad[0x50c];
	int m_val50C;
	int toInt(int dummy);
};


struct BfmeArg171
{
	unsigned char pad[0x10];
	float f10;
};

struct BfmeThing171
{
	unsigned char pad[0x500];
	int m_preAttackDelay;
	int scaleToInt(BfmeArg171 *arg);
};


// Native 0x00261353 calls the established Object shroud query at 0x0028D2A2.
// Its enum result and player index use the same 32-bit ABI as the donor view.
enum CellShroudStatus
{
	CELLSHROUD_CLEAR,
	CELLSHROUD_FOGGED,
	CELLSHROUD_SHROUDED,
	CELLSHROUD_COUNT
};
class Object
{
public:
	CellShroudStatus getShroudStatusForPlayer(int playerIndex) const;
};
// Slot 1 (allow) of partition filter vftable 0x00C0716C.
class Rva00261353Filter
{
public:
	virtual ~Rva00261353Filter();
	virtual bool allow(Object *obj);
	unsigned char m_pad[0x4];
	int m_val8;
};

bool Rva00261353Filter::allow(Object *obj)
{
	return obj->getShroudStatusForPlayer(m_val8) == CELLSHROUD_FOGGED;
}

class BfmeSub9BB
{
public:
	void doAction();
};

struct BfmeSub4_9BB
{
	unsigned char pad[0xc4];
	char m_flagC4;
};

struct BfmeThing9BB
{
	unsigned char pad[4];
	BfmeSub4_9BB *m_sub4;
	unsigned char pad2[0x34];
	char m_flag3C;
	char m_flag3D;
	void checkAndRun();
};


class BfmeObjEB2
{
public:
	void trigger(int a, int b);
};

class BfmeMgrEB2
{
public:
	BfmeObjEB2* find(int id);
};

class GameLogic;
extern GameLogic *TheGameLogic;

struct BfmeSubEB2
{
	unsigned char m_pad[0x7c];
	int m_id;
};

struct BfmeThingEB2
{
	unsigned char m_pad[0x8];
	BfmeSubEB2 *m_sub;
	void doTrigger();
};


class BfmeSubHelperCAB
{
public:
	int checkState(void *a, void *b, void *c);
};

struct BfmeThingCAB
{
	unsigned char m_pad[0x8];
	BfmeSubHelperCAB *m_helper;
	void *m_argC;
	void *m_attackType;
	bool isMatch(void *param);
};


struct BfmeItemE63
{
	unsigned char pad[0x14];
	void *m_p14;
	unsigned char pad2[0x24 - 0x18];
	char m_flag24;
	bool checkValid();
};

// The call at 0x00453124 targets the existing static CastleMemberBehavior
// lookup at 0x00395708. Retail passes the owner Object pointer stored at +8;
// retain the donor field view and cast the returned Module only for its fields.
class Module;
class CastleBehavior
{
public:
	static Module *rva000395708(Object *obj);
};

struct BfmeThingE63
{
	unsigned char pad[8];
	int m_id;
	bool isValid();
};

bool BfmeThingE63::isValid()
{
	int id = m_id;
	BfmeItemE63 *item = (BfmeItemE63 *)CastleBehavior::rva000395708((Object *)id);
	if (item && item->m_p14 && !item->m_flag24 && item->checkValid())
		return true;
	return false;
}
