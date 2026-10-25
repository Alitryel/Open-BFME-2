// ?winSetParent@GameWindow@@QAEHH@Z
// partial score=0.93 date=2026-10-01
// cl: /MD
// ?winSetParent@GameWindow@@QAEHH@Z, retail 0x00314056, 78 bytes.
// Honest GameWindow method: detach from old parent/list then attach.
// Evidence: this+0x200 is GameWindow::m_parent (same offset as
// GameWindow_winGetScreenPosition.cpp); this passed as GameWindow* to
// rowed GameWindowManager::linkWindow/unlinkWindow/unlinkChildWindow
// (GameWindowManager_linkWindow.cpp); second half virtual call [eax+0xE0] on
// TheWindowManager (?TheWindowManager@@3PAVGameWindowManager@@A);
// returns 0 (xor eax) with ret 4.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef UnsignedInt WindowMsgData;

enum WindowMsgHandledType
{
	MSG_IGNORED,
	MSG_HANDLED
};

class GameWindow;

class GameWindowManager
{
public:
#define V(n) virtual void pad##n() = 0;
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7)
	V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15)
	V(16) V(17) V(18) V(19) V(20) V(21) V(22) V(23)
	V(24) V(25) V(26) V(27) V(28) V(29) V(30) V(31)
	V(32) V(33) V(34) V(35) V(36)
	virtual GameWindow *Virtual94() = 0;
	V(38) V(39)
	virtual void windowHiding(GameWindow *window) = 0;
	V(41) V(42) V(43) V(44) V(45) V(46) V(47)
	virtual GameWindow *winGetFocus() = 0;
	virtual Int winSetFocus(GameWindow *window) = 0;
	V(50) V(51) V(52) V(53) V(54) V(55)
	virtual void VirtualE0(GameWindow *win, GameWindow *parent) = 0;
	V(57)
#undef V
	virtual WindowMsgHandledType winSendSystemMsg(GameWindow *window, UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2) = 0;
	void linkWindow(GameWindow *win);
	void unlinkWindow(GameWindow *win);
	void unlinkChildWindow(GameWindow *win);
};

extern GameWindowManager *TheWindowManager;

class GameWindow
{
public:
	int winSetParent(int arg);
private:
	char m_pad[0x200];
	GameWindow *m_parent;
};

int GameWindow::winSetParent(int arg)
{
	GameWindowManager *mgr = *(GameWindowManager * volatile *)&TheWindowManager;
	if (m_parent == 0)
		mgr->unlinkWindow(this);
	else
		mgr->unlinkChildWindow(this);
	GameWindowManager *mgr2 = TheWindowManager;
	if (arg == 0) {
		mgr2->linkWindow(this);
		m_parent = 0;
	} else {
		mgr2->VirtualE0(this, (GameWindow *)arg);
	}
	return 0;
}
