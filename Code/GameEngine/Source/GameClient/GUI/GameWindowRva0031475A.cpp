// cl: /DNDEBUG /MD /EHsc
// ?winBringToTop@GameWindow@@QAEHXZ, retail 0x0031475A, 128 bytes.
// Honest GameWindow method returning 0 or -3: detach path via Remove plus
// manager slot 0xE0, else search manager list via slot 0x94 walking +0x1F8
// for this then B92/A89, then notify +0x210 object via slots 0x1C/0x18.
// Evidence: this+0x200 parent and +0x1F8 next match GameWindow layout in
// GameWindowManager_linkWindow.cpp; rowed unlinkWindow/linkWindow/unlinkChildWindow; TheWindowManager
// ?TheWindowManager@@3PAVGameWindowManager@@A; WIN_ERR codes 0/-3.

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

class Gadget210
{
public:
	virtual void g00(); virtual void g01(); virtual void g02(); virtual void g03();
	virtual void g04(); virtual void g05();
	virtual void Virtual18(GameWindow *win);
	virtual void Virtual1C(GameWindow *win);
};

class GameWindow
{
public:
	int winBringToTop();
	int winGetCursorPosition(int *x, int *y);
	int winActivate();
	int winHide(bool hide);
private:
	char m_pad00[0x08];
	int m_status;
	char m_pad0C[0x24 - 0x0C];
	int m_cursorX;
	int m_cursorY;
	char m_pad2C[0x1F8 - 0x2C];
	GameWindow *m_next;
	GameWindow *m_prev;
	GameWindow *m_parent;
	GameWindow *m_child;
	char m_pad20C[0x210 - 0x208];
	Gadget210 *m_210;
};

int GameWindow::winBringToTop()
{
	GameWindowManager *mgr = TheWindowManager;
	GameWindow *parent = m_parent;
	if (parent != 0) {
		mgr->unlinkChildWindow(this);
		TheWindowManager->VirtualE0(this, parent);
	} else {
		GameWindow *cur = mgr->Virtual94();
		while (cur != this) {
			if (cur == 0)
				return -3;
			cur = cur->m_next;
		}
		TheWindowManager->unlinkWindow(this);
		TheWindowManager->linkWindow(this);
	}
	Gadget210 *g = m_210;
	if (g != 0) {
		g->Virtual1C(this);
		g->Virtual18(this);
	}
	return 0;
}

// ?winActivate@GameWindow@@QAEHXZ, retail 0x003147DA, 28 bytes.
// Calls winBringToTop then winHide(false) on success; sets status bit0.
// Evidence: chain caller of 0x0031475A; or [esi+8],1 matches m_status;
// rowed ?winHide@GameWindow@@QAEH_N@Z.

int GameWindow::winActivate()
{
	int returnCode = winBringToTop();
	if (returnCode != 0)
		return returnCode;
	m_status |= 1;
	winHide(false);
	return 0;
}

// ZH names plus native IME call at 0x233947 and loads at +0x24/+0x28.
int GameWindow::winGetCursorPosition(int *x, int *y)
{
	if (x) *x = m_cursorX;
	if (y) *y = m_cursorY;
	return 0;
}
