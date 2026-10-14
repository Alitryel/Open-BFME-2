// cl: /O1 /G7 /arch:SSE /EHsc /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/subsystem_bfme2 /Ireference/shims/moduledata /Ireference/shims/bfmealloc
// stlport
// ControlBar::init, retail 0x0031C83D..0x0031D230 (2547 B, RET 0): vtable
// 0x00C0CC88 slot 1, beside the ControlBar destructor (slot 0, scalar
// deleting 0x0031EB7A) and reset (slot 9). Zero Hour's ControlBar::init
// (GameEngine/Source/GameClient/GUI/ControlBar/ControlBar.cpp) is the semantic
// donor: the same "ControlBar.wnd:*" lookups, command-button bindings,
// marker positions, window managers and image lookups in the same order.
// BFME 2 differences read from retail: the INI loads are replaced by the
// SubsystemInterface legend loader (slot 2), there is no science-purchase
// layout or build tooltip layout, the command buttons are 32 windows built
// from the "ControlBar.wnd:ButtonCommand" template under a new full-screen
// command window (+0x68) and the options button lookup binds nothing.
// Member offsets are target evidence; their names follow the donor where
// the donor statement is the same, and are address-derived otherwise.
typedef bool Bool;
#include "ascii_string.h"
#include "subsystem_interface.h"
#include "../GameWindowManagerRecordView.h"
#include "ControlBarSchemeManagerView.h"
#include "../../../../../Libraries/Include/Lib/ICoord2D.h"

#ifndef NULL
#define NULL 0
#endif

typedef int Int;
typedef unsigned int UnsignedInt;
#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	NAMEKEY_MAX = 1 << 23
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *nameString);
	NameKeyType nameToKey(const AsciiString &nameString);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class GameWindow;
class WinInstanceData;
typedef void (*GameWinTooltipFunc)(GameWindow *, WinInstanceData *, UnsignedInt);
typedef void (*Rva0053EC21Func)(GameWindow *);

class GameWindow
{
public:
	Int winGetPosition(Int *x, Int *y);
	Int winGetScreenPosition(Int *x, Int *y);
	void snapshotCreateView(GadgetCreateView *view, bool keepInstance);
	UnsignedInt winGetStatus();
	void winSetUserData(void *userData);
	UnsignedInt winSetStatus(UnsignedInt status);
	UnsignedInt winClearStatus(UnsignedInt status);
	Int winSetSize(Int width, Int height);
	Int winSetPosition(Int x, Int y);
	Int winSetTooltipFunc(GameWinTooltipFunc tooltip);
};

// The window manager's virtual slots used here: 34 (+0x88) builds a window
// from a create view, 60 (+0xF0) finds a window by name key.
class GameWindowManager
{
public:
#define V(n) virtual void v##n();
	V(00) V(01) V(02) V(03) V(04) V(05) V(06) V(07) V(08) V(09)
	V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19)
	V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29)
	V(30) V(31) V(32) V(33)
	virtual GameWindow *createFromView(GadgetCreateView *view);	// +0x88
	V(35) V(36) V(37) V(38) V(39)
	V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47) V(48) V(49)
	V(50) V(51) V(52) V(53) V(54) V(55) V(56) V(57) V(58) V(59)
	virtual GameWindow *winGetWindowFromId(GameWindow *window, Int id);	// +0xF0
#undef V
};
extern GameWindowManager *TheWindowManager;

class Display
{
public:
#define V(n) virtual void v##n();
	V(00) V(01) V(02) V(03) V(04) V(05) V(06) V(07) V(08) V(09)
	V(10) V(11) V(12) V(13) V(14) V(15)
#undef V
	virtual UnsignedInt getWidth();		// +0x40
	virtual UnsignedInt getHeight();	// +0x44
};
extern Display *TheDisplay;

class Image;
class ImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};
extern ImageCollection *TheMappedImageCollection;

class CommandButton;
class WindowVideoManager { public: WindowVideoManager(); private: char m_opaque[0x24]; };
class AnimateWindowManager { public: AnimateWindowManager(); private: char m_opaque[0x38]; };

void commandButtonTooltip(GameWindow *window, WinInstanceData *instData, UnsignedInt mouse);
void Rva0053EC21(GameWindow *window);

enum ControlBarParentWindowType
{
	CP_MASTER,
	CP_COMMAND,
	CP_BUILD_QUEUE,
	CP_BEACON,
	CP_UNDER_CONSTRUCTION,
	CP_OBSERVER_INFO,
	CP_OBSERVER_LIST,
	CP_OCL_TIMER,
	NUM_CONTEXT_PARENTS
};

enum
{
	MAX_COMMANDS_PER_SET = 32,
	MAX_RIGHT_HUD_UPGRADE_CAMEOS = 5,
	CB_CONTEXT_NONE = 0,
	WIN_STATUS_RVA0031C83D_200 = 0x00000200,
	WIN_STATUS_RVA0031C83D_10000 = 0x00010000,
	WIN_STATUS_RVA0031C83D_20000 = 0x00020000,
	WIN_STATUS_USE_OVERLAY_STATES = 0x00200000,
	WIN_STATUS_RVA0031C83D_20000000 = 0x20000000
};

class ControlBar : public SubsystemInterface
{
public:
	virtual void init(void);

	void initObserverControls(void);					// 0x0050DE39
	void postProcessCommands(void);						// 0x0031AC39
	const CommandButton *findCommandButton(const AsciiString &name);	// 0x0031BE3C
	void setControlCommand(GameWindow *button, const CommandButton *commandButton);	// 0x0031B641
	void switchToContext(Int context, void *draw);				// 0x0031BF64

	static const Image *m_rankVeteranIcon;	// 0x00E01D00
	static const Image *m_rankEliteIcon;	// 0x00E01D04
	static const Image *m_rankHeroicIcon;	// 0x00E01D08

private:
	WindowVideoManager *m_videoManager;				// +0x0C
	AnimateWindowManager *m_animateWindowManager;			// +0x10
	AnimateWindowManager *m_animateWindowManagerForGenShortcuts;	// +0x14
	AnimateWindowManager *m_generalsScreenAnimate;			// +0x18
	ICoord2D m_defaultControlBarPosition;				// +0x1C
	char m_pad24[0x44 - 0x24];
	ControlBarSchemeManager *m_controlBarSchemeManager;		// +0x44
	GameWindow *m_contextParent[NUM_CONTEXT_PARENTS];		// +0x48
	GameWindow *m_commandWindowParent;				// +0x68
	char m_pad6C[0x84 - 0x6C];
	GameWindow *m_rightHUDWindow;					// +0x84
	GameWindow *m_rightHUDCameoWindow;				// +0x88
	GameWindow *m_rightHUDUpgradeCameos[MAX_RIGHT_HUD_UPGRADE_CAMEOS];	// +0x8C
	GameWindow *m_rightHUDUnitSelectParent;				// +0xA0
	GameWindow *m_communicatorButton;				// +0xA4
	char m_padA8[0xDC - 0xA8];
	GameWindow *m_commandWindows[MAX_COMMANDS_PER_SET];		// +0xDC
	char m_pad15C[0x1DC - 0x15C];
	Bool m_sideSelectAnimateDown;					// +0x1DC
	char m_pad1DD[0x248 - 0x1DD];
	const Image *m_genStarOn;					// +0x248
	const Image *m_genStarOff;					// +0x24C
	char m_pad250[0x278 - 0x250];
	Bool m_genStarFlash;						// +0x278
	Int m_lastFlashedAtPointValue;					// +0x27C
	ICoord2D m_controlBarForegroundMarkerPos;			// +0x280
	ICoord2D m_controlBarBackgroundMarkerPos;			// +0x288
	char m_pad290[0x298 - 0x290];
	GameWindow *m_radarAttackGlowWindow;				// +0x298
	Int m_rva0031C83D29C;						// +0x29C, set once the context windows exist
	void *m_commandWindowUserData;					// +0x2A0
};

// The create-view fields this body writes beyond the shared record view's
// named ones: the system callback at +0x24 and a cleared pointer at +0x2C.
static __forceinline void setRva0031C83DViewSystem(GadgetCreateView &view, Rva0053EC21Func system)
{
	*(Rva0053EC21Func *)(view.unknown32 + 4) = system;
}
static __forceinline void clearRva0031C83DView2C(GadgetCreateView &view)
{
	*(void **)(view.unknown32 + 12) = NULL;
}

void ControlBar::init(void)
{
	m_sideSelectAnimateDown = FALSE;
	loadIniFilesFromLegend();

	// post process step after loading the command buttons and command sets
	postProcessCommands();

	// Init the scheme manager, this will call it's won INI init funciton.
	m_controlBarSchemeManager = new ControlBarSchemeManager;
	m_controlBarSchemeManager->init();

	//Added this check because the builder uses the ControlBar, but doesn't care about
	//the GUI.
	if (TheWindowManager)
	{
		NameKeyType id;
		id = TheNameKeyGenerator->nameToKey("ControlBar.wnd:ControlBarParent");
		m_contextParent[CP_MASTER] = TheWindowManager->winGetWindowFromId(NULL, id);
		m_contextParent[CP_MASTER]->winGetPosition(&m_defaultControlBarPosition.x, &m_defaultControlBarPosition.y);

		id = TheNameKeyGenerator->nameToKey("ControlBar.wnd:UnderConstructionWindow");
		m_contextParent[CP_UNDER_CONSTRUCTION] = TheWindowManager->winGetWindowFromId(NULL, id);

		id = TheNameKeyGenerator->nameToKey("ControlBar.wnd:OCLTimerWindow");
		m_contextParent[CP_OCL_TIMER] = TheWindowManager->winGetWindowFromId(NULL, id);

		id = TheNameKeyGenerator->nameToKey("ControlBar.wnd:BeaconWindow");
		m_contextParent[CP_BEACON] = TheWindowManager->winGetWindowFromId(NULL, id);

		id = TheNameKeyGenerator->nameToKey("ControlBar.wnd:CommandWindow");
		m_contextParent[CP_COMMAND] = TheWindowManager->winGetWindowFromId(NULL, id);

		id = TheNameKeyGenerator->nameToKey("ControlBar.wnd:ProductionQueueWindow");
		m_contextParent[CP_BUILD_QUEUE] = TheWindowManager->winGetWindowFromId(NULL, id);

		id = TheNameKeyGenerator->nameToKey("ControlBar.wnd:ObserverPlayerListWindow");
		m_contextParent[CP_OBSERVER_LIST] = TheWindowManager->winGetWindowFromId(NULL, id);

		id = TheNameKeyGenerator->nameToKey("ControlBar.wnd:ObserverPlayerInfoWindow");
		m_contextParent[CP_OBSERVER_INFO] = TheWindowManager->winGetWindowFromId(NULL, id);

		// a full-screen copy of the command window parents the command buttons
		GameWindow *commandWindow = m_contextParent[CP_COMMAND];
		GadgetCreateView commandView;
		commandWindow->snapshotCreateView(&commandView, FALSE);
		commandView.status = commandWindow->winGetStatus();
		commandView.width = TheDisplay->getWidth();
		commandView.height = TheDisplay->getHeight();
		setRva0031C83DViewSystem(commandView, Rva0053EC21);
		clearRva0031C83DView2C(commandView);
		GameWindow *commandParent = TheWindowManager->createFromView(&commandView);
		m_commandWindowParent = commandParent;
		commandParent->winSetUserData(m_commandWindowUserData);
		commandParent->winSetStatus(WIN_STATUS_RVA0031C83D_200);
		commandParent->winClearStatus(WIN_STATUS_RVA0031C83D_10000);

		// get the command windows and save for easy access later
		Int i;
		AsciiString windowName;
		windowName.format("ControlBar.wnd:ButtonCommand");
		id = TheNameKeyGenerator->nameToKey(windowName.str());
		GameWindow *buttonTemplate = TheWindowManager->winGetWindowFromId(m_contextParent[CP_COMMAND], id);
		if (buttonTemplate)
			buttonTemplate->winSetStatus(WIN_STATUS_USE_OVERLAY_STATES);
		for (i = 0; i < MAX_COMMANDS_PER_SET; i++)
		{
			GadgetCreateView buttonView;
			buttonTemplate->snapshotCreateView(&buttonView, FALSE);
			buttonView.x = -1;
			buttonView.y = -1;
			buttonView.parent = commandParent;
			clearRva0031C83DView2C(buttonView);
			buttonView.width = 1;
			buttonView.height = 1;
			GameWindow *button = TheWindowManager->createFromView(&buttonView);
			m_commandWindows[i] = button;
			button->winSetStatus(WIN_STATUS_RVA0031C83D_20000000);
			button->winSetStatus(WIN_STATUS_RVA0031C83D_20000);
			button->winSetSize(1, 1);
			button->winSetPosition(-100, -100);
		}  // end for i

		// keep a pointer to the window making up the right HUD display
		id = TheNameKeyGenerator->nameToKey("ControlBar.wnd:RightHUD");
		m_rightHUDWindow = TheWindowManager->winGetWindowFromId(NULL, id);

		id = TheNameKeyGenerator->nameToKey("ControlBar.wnd:WinUnitSelected");
		m_rightHUDUnitSelectParent = TheWindowManager->winGetWindowFromId(NULL, id);

		id = TheNameKeyGenerator->nameToKey("ControlBar.wnd:CameoWindow");
		m_rightHUDCameoWindow = TheWindowManager->winGetWindowFromId(NULL, id);
		for (i = 0; i < MAX_RIGHT_HUD_UPGRADE_CAMEOS; i++)
		{
			windowName.format("ControlBar.wnd:UnitUpgrade%d", i + 1);
			id = TheNameKeyGenerator->nameToKey(windowName.str());
			m_rightHUDUpgradeCameos[i] =
				TheWindowManager->winGetWindowFromId(m_rightHUDWindow, id);
			m_rightHUDUpgradeCameos[i]->winSetStatus(WIN_STATUS_USE_OVERLAY_STATES);
		}

		// don't forget about the communicator button CCB
		id = TheNameKeyGenerator->nameToKey("ControlBar.wnd:PopupCommunicator");
		m_communicatorButton = TheWindowManager->winGetWindowFromId(NULL, id);
		setControlCommand(m_communicatorButton, findCommandButton("NonCommand_Communicator"));
		m_communicatorButton->winSetTooltipFunc(commandButtonTooltip);

		GameWindow *win = TheWindowManager->winGetWindowFromId(NULL, TheNameKeyGenerator->nameToKey("ControlBar.wnd:ButtonOptions"));
		win = TheWindowManager->winGetWindowFromId(NULL, TheNameKeyGenerator->nameToKey("ControlBar.wnd:ButtonIdleWorker"));
		if (win)
		{
			setControlCommand(win, findCommandButton("NonCommand_IdleWorker"));
			win->winSetTooltipFunc(commandButtonTooltip);
		}
		win = TheWindowManager->winGetWindowFromId(NULL, TheNameKeyGenerator->nameToKey("ControlBar.wnd:ButtonPlaceBeacon"));
		if (win)
		{
			setControlCommand(win, findCommandButton("NonCommand_Beacon"));
			win->winSetTooltipFunc(commandButtonTooltip);
		}
		win = TheWindowManager->winGetWindowFromId(NULL, TheNameKeyGenerator->nameToKey("ControlBar.wnd:ButtonGeneral"));
		if (win)
		{
			setControlCommand(win, findCommandButton("NonCommand_GeneralsExperience"));
			win->winSetTooltipFunc(commandButtonTooltip);
		}
		win = TheWindowManager->winGetWindowFromId(NULL, TheNameKeyGenerator->nameToKey("ControlBar.wnd:ButtonLarge"));
		if (win)
		{
			setControlCommand(win, findCommandButton("NonCommand_UpDown"));
			win->winSetTooltipFunc(commandButtonTooltip);
		}

		win = TheWindowManager->winGetWindowFromId(NULL, TheNameKeyGenerator->nameToKey("ControlBar.wnd:PowerWindow"));
		if (win)
		{
			win->winSetTooltipFunc(commandButtonTooltip);
		}
		win = TheWindowManager->winGetWindowFromId(NULL, TheNameKeyGenerator->nameToKey("ControlBar.wnd:MoneyDisplay"));
		if (win)
		{
			win->winSetTooltipFunc(commandButtonTooltip);
		}
		win = TheWindowManager->winGetWindowFromId(NULL, TheNameKeyGenerator->nameToKey("ControlBar.wnd:GeneralsExp"));
		if (win)
		{
			win->winSetTooltipFunc(commandButtonTooltip);
		}

		m_radarAttackGlowWindow = TheWindowManager->winGetWindowFromId(NULL, TheNameKeyGenerator->nameToKey("ControlBar.wnd:WinUAttack"));

		win = TheWindowManager->winGetWindowFromId(NULL, TheNameKeyGenerator->nameToKey(AsciiString("ControlBar.wnd:BackgroundMarker")));
		win->winGetScreenPosition(&m_controlBarForegroundMarkerPos.x, &m_controlBarForegroundMarkerPos.y);
		win = TheWindowManager->winGetWindowFromId(NULL, TheNameKeyGenerator->nameToKey(AsciiString("ControlBar.wnd:BackgroundMarker")));
		win->winGetScreenPosition(&m_controlBarBackgroundMarkerPos.x, &m_controlBarBackgroundMarkerPos.y);

		if (!m_videoManager)
			m_videoManager = new WindowVideoManager;
		if (!m_animateWindowManager)
			m_animateWindowManager = new AnimateWindowManager;
		if (!m_generalsScreenAnimate)
			m_generalsScreenAnimate = new AnimateWindowManager;
		if (!m_animateWindowManagerForGenShortcuts)
			m_animateWindowManagerForGenShortcuts = new AnimateWindowManager;

		m_genStarOn = TheMappedImageCollection ? TheMappedImageCollection->findImageByName("BarButtonGenStarON") : NULL;
		m_genStarOff = TheMappedImageCollection ? TheMappedImageCollection->findImageByName("BarButtonGenStarOFF") : NULL;
		m_lastFlashedAtPointValue = -1;
		m_genStarFlash = TRUE;

		m_rankVeteranIcon = TheMappedImageCollection ? TheMappedImageCollection->findImageByName("SSChevron1L") : NULL;
		m_rankEliteIcon = TheMappedImageCollection ? TheMappedImageCollection->findImageByName("SSChevron2L") : NULL;
		m_rankHeroicIcon = TheMappedImageCollection ? TheMappedImageCollection->findImageByName("SSChevron3L") : NULL;

		// Initialize the Observer controls
		initObserverControls();
		m_rva0031C83D29C = TRUE;

		// by default switch to the none context
		switchToContext(CB_CONTEXT_NONE, NULL);
	}

}  // end init
