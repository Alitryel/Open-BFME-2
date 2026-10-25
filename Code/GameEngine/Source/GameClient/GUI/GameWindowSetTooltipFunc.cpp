// cl: /DNDEBUG /MD

// The BFME1 GameWindowFields.cpp donor assigns m_tooltip and returns OK.
// Retail at 0x0031416D confirms the field at +0x1EC and this 15B setter.
// The callback type follows the donor declaration; the field offset is target
// evidence from the retail store.
//
// GameWindow.cpp's view: the setter is class-inline there because retail
// winSetCallbacks expands it, so it is spelled the same way here. The anchor
// takes its address, which makes this unit emit the out-of-line copy
// (0x0031416D) as a COMDAT, the same linkage the class-inline copy has.

typedef int Int;

typedef unsigned int UnsignedInt;

enum
{
	WIN_ERR_OK = 0,
	WIN_ERR_INVALID_PARAMETER = -3,
	GGM_RESIZED = 16388
};

class GameWindow;

class WinInstanceData;

typedef void (*GameWinTooltipFunc)(GameWindow *, WinInstanceData *, UnsignedInt);

class GameWindow
{
public:
	Int winSetTooltipFunc(GameWinTooltipFunc tooltip) { m_tooltipFunc = tooltip; return WIN_ERR_OK; }

private:
	char m_unmodelled[0x1EC];
	GameWinTooltipFunc m_tooltipFunc;	// +0x1EC
};

// The anchor keeps the rowed body emitted.
// ?bfmeAnchorWinSetTooltipFunc@@YAXXZ absent-from-retail
void bfmeAnchorWinSetTooltipFunc()
{
	Int (GameWindow::*volatile setter)(GameWinTooltipFunc) = &GameWindow::winSetTooltipFunc;
}
