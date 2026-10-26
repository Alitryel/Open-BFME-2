// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// W3DShrubBuffer::drawShrubs, retail 0x000E89BD (624 bytes, ret 4): the shrub
// buffer's per-frame update before drawing, the Zero Hour drawTrees body
// reduced to its update half. It runs the sway update unless time is frozen
// or the game is paused, handles the deferred texture update, advances 30
// round-robin records' visibility state, then pushes aside visible upright
// records and refills the vertex buffers (0x000E7DF3) or only re-writes them
// (0x000E8365) before the draw pass 0x000E663B. Donor semantics: Open-BFME-1
// W3DTreeBuffer.cpp drawTrees; the BFME2 shrub fields are read from retail.
// Layout: records of 0xA0 at +0x1958 (count +0x4FB58), index counts vector at
// +0x28, texture at +0x38, swayRate +0x5BC, flags +0x4FB5C/D/E/6D/6E, byte
// +0x51274, step +0x51278, round-robin index +0x5127C.
#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../../GameEngine/Source/Common/GameLogicObjectLookupView.h"

struct BreezeInfo;
class GlobalData;
class ScriptEngine;
class PartitionManager;
class PlayerList;
enum ObjectShroudStatus { SHROUD_STATUS_A = 0 };

class Rva00203ACEByteField { public: unsigned char get() const; };
class Rva00203B08 { public: bool rva0020424FF(); };
class Rva00739800 { public: ObjectShroudStatus rva00739800(int, const Coord3D *) const; };
class Rva000EC9C6 { public: void rva000E663B(int); };

struct Rva000E89BDPlayer { unsigned char pad[0x54]; int index; };
struct Rva000E89BDPlayerList { unsigned char pad[0x10]; Rva000E89BDPlayer *local; };
struct Rva000E89BDGlobalData { unsigned char pad[0x1c]; bool flag1c; };
struct Rva000E89BDScriptEngine { unsigned char pad[0x1a4a8]; unsigned char breeze[1]; };

extern GlobalData *TheWritableGlobalData;
extern ScriptEngine *TheScriptEngine;
extern GameLogic *TheGameLogic;
extern PartitionManager *TheShroudManager;
extern PlayerList *ThePlayerList;

struct Rva000E89BDData
{
	unsigned char pad[0x14];
	unsigned int framesToMoveInward;
};

struct Rva000E89BDType
{
	unsigned char pad[0x20];
	const Rva000E89BDData *data;
	unsigned char pad24[0x5c - 0x24];
};

struct Rva000E89BDTree
{
	Coord3D location;
	unsigned char pad0c[0x40 - 0x0c];
	int treeType;
	bool visible;
	unsigned char pad45[0x5c - 0x45];
	float pushAside;
	float pushAsideDelta;
	unsigned char pad64[0x84 - 0x64];
	int toppleState;
	unsigned char pad88[0x9c - 0x88];
	int shroudState;
};

class Rva000E6406SwayView
{
public:
	void rva000E6406(const BreezeInfo &info);
};
class W3DShrubBuffer
{
public:
	void drawShrubs(int arg);
	void loadShrubsInVertexAndIndexBuffers(void);
	void rva000E8365(void);
	void rva000E76B8();

protected:
	void updateTexture();

private:
	// Match the seed's opaque base, record/type arrays and tail storage.
	void *m_baseVtable;
	unsigned char m_storage[0x5BC - 4];
	float m_pushRateScale;
	unsigned char m_pad5c0[0x1958 - 0x5C0];
	unsigned char m_records[2000 * 0xA0];
	int m_count;
	unsigned char m_4fb5c, m_4fb5d, m_4fb5e, m_4fb5f;
	unsigned char m_pad4fb60[0x4FB6C - 0x4FB60];
	unsigned char m_4fb6c, m_4fb6d, m_4fb6e, m_4fb6f;
	unsigned char m_types[64 * 0x5C];
	int m_numTypes;
	int m_51274;
	int m_51278;
	int m_5127c;
};

// ?drawShrubs@W3DShrubBuffer@@QAEXH@Z
void W3DShrubBuffer::drawShrubs(int arg)
{
	if (!(*reinterpret_cast<void **>(m_storage + 0x30)))
		return;
	if (!m_4fb6d)
		return;
	if (!((Rva000E89BDGlobalData *)TheWritableGlobalData)->flag1c)
		return;

	const BreezeInfo *info = (const BreezeInfo *)((Rva000E89BDScriptEngine *)TheScriptEngine)->breeze;
	bool pause;
	if (((Rva00203ACEByteField *)TheScriptEngine)->get() || ((Rva00203B08 *)TheScriptEngine)->rva0020424FF())
		pause = true;
	else
		pause = false;
	if (TheGameLogic && TheGameLogic->isGamePaused())
		pause = true;
	if (!pause)
		((Rva000E6406SwayView *)this)->rva000E6406(*info);

	m_4fb6d = false;
	if (m_4fb6e) {
		m_4fb6e = false;
		updateTexture();
	}
	if (!(*reinterpret_cast<void **>(m_storage + 0x34)))
		return;

	for (int k = 30; k > 0; k--) {
		if (m_5127c >= m_count)
			m_5127c = 0;
		reinterpret_cast<Rva000E89BDTree *>(m_records)[m_5127c].shroudState = 0;
		m_5127c++;
	}
	if (m_4fb5e)
		rva000E76B8();

	int playerIndex = ThePlayerList ? ((Rva000E89BDPlayerList *)ThePlayerList)->local->index : 0;
	for (int curTree = 0; curTree < m_count; curTree += m_51278) {
		int type = reinterpret_cast<Rva000E89BDTree *>(m_records)[curTree].treeType;
		if (type < 0)
			continue;
		if (reinterpret_cast<Rva000E89BDTree *>(m_records)[curTree].toppleState != 0)
			continue;
		if (!reinterpret_cast<Rva000E89BDTree *>(m_records)[curTree].visible)
			continue;
		if (!ThePlayerList || !TheShroudManager)
			reinterpret_cast<Rva000E89BDTree *>(m_records)[curTree].shroudState = 1;
		if (reinterpret_cast<Rva000E89BDTree *>(m_records)[curTree].shroudState == 0)
			reinterpret_cast<Rva000E89BDTree *>(m_records)[curTree].shroudState = ((Rva00739800 *)TheShroudManager)->rva00739800(playerIndex, &reinterpret_cast<Rva000E89BDTree *>(m_records)[curTree].location);
		if (reinterpret_cast<Rva000E89BDTree *>(m_records)[curTree].shroudState >= 3 || reinterpret_cast<Rva000E89BDTree *>(m_records)[curTree].shroudState <= 0)
			continue;
		if (pause)
			continue;
		if (reinterpret_cast<Rva000E89BDTree *>(m_records)[curTree].pushAsideDelta != 0.0f) {
			reinterpret_cast<Rva000E89BDTree *>(m_records)[curTree].pushAside += reinterpret_cast<Rva000E89BDTree *>(m_records)[curTree].pushAsideDelta;
			if (reinterpret_cast<Rva000E89BDTree *>(m_records)[curTree].pushAside >= 1.0f) {
				reinterpret_cast<Rva000E89BDTree *>(m_records)[curTree].pushAsideDelta = -1.0 / ((float)reinterpret_cast<Rva000E89BDType *>(m_types)[type].data->framesToMoveInward * m_pushRateScale);
			} else if (reinterpret_cast<Rva000E89BDTree *>(m_records)[curTree].pushAside <= 0.0f) {
				reinterpret_cast<Rva000E89BDTree *>(m_records)[curTree].pushAsideDelta = 0.0f;
				reinterpret_cast<Rva000E89BDTree *>(m_records)[curTree].pushAside = 0.0f;
			}
		}
	}

	(*reinterpret_cast<bool *>(&m_51274)) = (*reinterpret_cast<bool *>(&m_4fb5c));
	if ((*reinterpret_cast<bool *>(&m_4fb5c))) {
		loadShrubsInVertexAndIndexBuffers();
		(*reinterpret_cast<bool *>(&m_4fb5c)) = false;
	} else if (m_4fb5d) {
		m_4fb5d = false;
		rva000E8365();
	}
	if (*(*reinterpret_cast<int **>(m_storage + 0x24)) != 0)
		((Rva000EC9C6 *)this)->rva000E663B(arg);
}
