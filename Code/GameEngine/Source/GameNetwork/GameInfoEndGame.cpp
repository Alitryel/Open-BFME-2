// cl: /O1 /DNDEBUG /MD /EHsc
// ?endGame@GameInfo@@QAEXXZ @0x003FF296 (9B):
// GameInfo::endGame. BFME1 GameInfo.cpp donor verbatim minus DEBUG_ASSERTCRASH
// (compiled out under /DNDEBUG): clears inGame/inProgress at +0x10/+0x11.
// Layout from GameInfoGetSlotNum (pad 0x10 then inGame): two mov byte 0 + ret.

typedef bool Bool;
typedef int Int;

class GameSlot;
enum { MAX_SLOTS = 8 };

class GameInfo
{
public:
	void clearSlotList();
	void enterGame();
	void endGame();
	Bool isPlayerPreorder(Int index);
	void markPlayerAsPreorder(Int index);

private:
	// The existing TU verifies the preorder mask at +0x08 and the game
	// state flags at +0x10/+0x11. The slot array remains at +0x18.
	char m_pad[0x08];
	Int m_preorderMask;
	char m_pad0C[4];
	Bool m_inGame;
	Bool m_inProgress;
	char m_pad12[6];
	GameSlot *m_slot[MAX_SLOTS];
};

// ?enterGame@GameInfo@@QAEXXZ @0x003FF268 (9B): WorldBuilder names it
// GameInfo::enterGame (GameInfo.cpp, assert line 721 "Entering game at a bad
// time!", compiled out here): sets inGame, clears inProgress. Same shape in the
// BFME1 GameInfo.cpp donor.
void GameInfo::enterGame()
{
	m_inGame = true;
	m_inProgress = false;
}

void GameInfo::endGame()
{
	m_inGame = false;
	m_inProgress = false;
}
