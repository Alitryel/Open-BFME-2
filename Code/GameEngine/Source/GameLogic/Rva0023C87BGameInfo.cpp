// cl: /O1 /DNDEBUG /MD /EHsc
//
// GameLogic method at retail 0x0023C87B (95B), between Rva0023C85EDisable and
// GameLogic::rva0023C8DA: the GameInfo of the game being played. With a
// network up it is the LAN API's game (TheLAN virtual slot 0xE0) or else
// TheGameSpyGame; a recorder in mode 1 (playback, read through the folded
// 0x0030F2C7 getter) gives the recorder's own GameInfo at +0x24; a game mode
// (+0x110) of 2 gives TheSkirmishGameInfo; otherwise NULL. ZH's GameMode
// numbering makes 2 the skirmish mode (structural inference). The receiver is
// most likely GameLogic (its neighbours are GameLogic methods and GameLogic
// keeps its game mode at +0x110), but the method is not established, so the
// view and the method keep address-derived names.

class NetworkInterface; extern NetworkInterface *TheNetwork;
class LANAPI; extern LANAPI *TheLAN;
class GameSpyStagingRoom; extern GameSpyStagingRoom *TheGameSpyGame;
class RecorderClass; extern RecorderClass *TheRecorder;
class GameInfo; class SkirmishGameInfo; extern SkirmishGameInfo *TheSkirmishGameInfo; // defined in SkirmishGameOptionsMenu.cpp

struct Bfme939Helper
{
	int get() const;
};

struct Rva0023C87BLan
{
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
	virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35();
	virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39();
	virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43();
	virtual void s44(); virtual void s45(); virtual void s46(); virtual void s47();
	virtual void s48(); virtual void s49(); virtual void s50(); virtual void s51();
	virtual void s52(); virtual void s53(); virtual void s54(); virtual void s55();
	virtual GameInfo *getMyGame();							// +0xE0
};

class Rva0023C87BLogic
{
public:
	GameInfo *rva0023C87B();

private:
	unsigned char m_pad00[0x110];
	int m_gameMode;											// +0x110
};

GameInfo *Rva0023C87BLogic::rva0023C87B()
{
	GameInfo *game = 0;
	if (TheNetwork) {
		if (TheLAN)
			game = ((Rva0023C87BLan *)TheLAN)->getMyGame();
		else
			game = (GameInfo *)TheGameSpyGame;
	} else if (TheRecorder && ((Bfme939Helper *)TheRecorder)->get() == 1) {
		game = (GameInfo *)((char *)TheRecorder + 0x24);
	} else if (m_gameMode == 2) {
		game = (GameInfo *)TheSkirmishGameInfo;
	}
	return game;
}
