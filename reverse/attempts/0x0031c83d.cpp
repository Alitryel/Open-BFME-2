// ?rva0031C83D@ControlBar@@QAEXXZ
// partial score=0.56 date=2026-10-14
// ?rva0031C83D@Rva0031C83DHost@@QAEXXZ
// partial score=0.56 date=2026-10-14
// Bank draft of the ControlBar window-tree init at 0x0031C83D (2547B, RET0).
// Decoded from the retail body: the "ControlBar.wnd:*" nameToKey/window
// lookups, the 0x20-slot command window loop, the 5 UnitUpgrade slots, the
// command-button/tooltip bindings, the BackgroundMarker screen positions, the
// video/animate managers and the chevron image lookups.
// cl: /O2 /MD /EHsc
#include <new>

enum NameKeyType { NKT_NONE = 0 };

class NameKeyGenerator { public: NameKeyType nameToKey(const char *); };
extern NameKeyGenerator *g_rva00DF36A4;

class Rva0031C83DManager {
public:
    virtual void m0();
    virtual void m1();
    virtual void m2();
    virtual void m3();
    virtual void m4();
    virtual void m5();
    virtual void m6();
    virtual void m7();
    virtual void m8();
    virtual void m9();
    virtual void m10();
    virtual void m11();
    virtual void m12();
    virtual void m13();
    virtual void m14();
    virtual void m15();
    virtual void m16();
    virtual void m17();
    virtual void m18();
    virtual void m19();
    virtual void m20();
    virtual void m21();
    virtual void m22();
    virtual void m23();
    virtual void m24();
    virtual void m25();
    virtual void m26();
    virtual void m27();
    virtual void m28();
    virtual void m29();
    virtual void m30();
    virtual void m31();
    virtual void m32();
    virtual void m33();
    virtual void *m34(void *);
    virtual void m35();
    virtual void m36();
    virtual void m37();
    virtual void m38();
    virtual void m39();
    virtual void m40();
    virtual void m41();
    virtual void m42();
    virtual void m43();
    virtual void m44();
    virtual void m45();
    virtual void m46();
    virtual void m47();
    virtual void m48();
    virtual void m49();
    virtual void m50();
    virtual void m51();
    virtual void m52();
    virtual void m53();
    virtual void m54();
    virtual void m55();
    virtual void m56();
    virtual void m57();
    virtual void m58();
    virtual void m59();
    virtual void *m60(int, NameKeyType);
};

class ControlBar;
class Rva0031C83DScheme {
public:
    virtual void m0();
    virtual void m1();
    virtual void m2();
    virtual void m3();
    virtual void m4();
    virtual void m5();
    virtual void m6();
    virtual void m7();
    virtual void m8();
    virtual void m9();
    virtual void m10();
    virtual void m11();
    virtual void m12();
    virtual void m13();
    virtual void m14();
    virtual void m15();
    virtual int m16();
    virtual int m17();
};
template<class T> class StringBase
{
    friend class ControlBar;
private:
    StringBase(const char *);
    ~StringBase();
    void *m_data;
};

class AsciiString
{
public:
    void format(const char *, ...);
};

class GadgetCreateView { public: GadgetCreateView(); int m_pad[8]; };
class WinInstanceData;
class GameWindow
{
public:
    int winGetPosition(int *, int *);
    int winGetScreenPosition(int *, int *);
    void winSetUserData(void *);
    unsigned int winSetStatus(unsigned int);
    unsigned int winClearStatus(unsigned int);
    int winSetSize(int, int);
    int winSetPosition(int, int);
    int winSetTooltipFunc(void (*)(GameWindow *, WinInstanceData *, unsigned int));
    void snapshotCreateView(GadgetCreateView *, bool);
};
class ControlBarSchemeManager { public: void init(); };
class Rva003200EB { public: Rva003200EB(); };
class Rva0031AC39 { public: void rva0031AC39(); };
class WindowVideoManager { public: WindowVideoManager(); };
class AnimateWindowManager { public: AnimateWindowManager(); };
class CommandButton;
class Image;
class ImageCollection { public: const Image *findImageByName(const AsciiString &); };
class Rva0030F45FView { public: const char *rva0030F45F(); };
class ControlBar
{
public:
    const CommandButton *findCommandButton(const AsciiString &);
    void setControlCommand(GameWindow *, const CommandButton *);
    void switchToContext(int, void *);
    void rva0031C83D();

private:
    unsigned char m_pad0[0xc];
    WindowVideoManager *m_c;			// +0x0c
    AnimateWindowManager *m_10;			// +0x10
    AnimateWindowManager *m_14;			// +0x14
    AnimateWindowManager *m_18;			// +0x18
    int m_1c, m_20;				// +0x1c/+0x20
    unsigned char m_pad24[0x44 - 0x24];
    void *m_44;					// +0x44
    GameWindow *m_48;				// +0x48
    GameWindow *m_4c;				// +0x4c
    GameWindow *m_50;				// +0x50
    GameWindow *m_54;				// +0x54
    GameWindow *m_58;				// +0x58
    GameWindow *m_5c;				// +0x5c
    GameWindow *m_60;				// +0x60
    GameWindow *m_64;				// +0x64
    GameWindow *m_68;				// +0x68
    unsigned char m_pad6c[0x84 - 0x6c];
    GameWindow *m_84;				// +0x84
    GameWindow *m_88;				// +0x88
    GameWindow *m_8c[5];			// +0x8c
    GameWindow *m_a0;				// +0xa0
    GameWindow *m_a4;				// +0xa4
    unsigned char m_padA8[0xdc - 0xa8];
    GameWindow *m_dc[0x20];			// +0xdc
    unsigned char m_pad15c[0x1dc - 0x15c];
    unsigned char m_1dc;			// +0x1dc
    unsigned char m_pad1dd[0x248 - 0x1dd];
    void *m_248, *m_24c;			// +0x248/+0x24c
    unsigned char m_pad250[0x278 - 0x250];
    unsigned char m_278;			// +0x278
    unsigned char m_pad279[0x27c - 0x279];
    int m_27c;					// +0x27c
    int m_280, m_284, m_288, m_28c;		// +0x280..+0x28c
    GameWindow *m_298;				// +0x298
    int m_29c;					// +0x29c
    void *m_2a0;				// +0x2a0
};

// Unrowed data cells (extern-only placeholders; the closers own their names).
extern void *g_rva00DFEF1C;
extern unsigned char g_rva00DFDCE0;
extern void *g_rva00DFDCDC;
extern void *g_rva00DFF078;
extern void *g_rva00DFE9D8;
extern void *g_rva00E01D00;
extern void *g_rva00E01D04;
extern void *g_rva00E01D08;
extern const char g_rva00BBAC1C;
void Rva0050DE39Init();
void bfmeTooltipCallback(GameWindow *, WinInstanceData *, unsigned int);

static void *winLookup(int parent, const char *name)
{
    NameKeyType key = g_rva00DF36A4->nameToKey(name);
    return ((Rva0031C83DManager *)g_rva00DFEF1C)->m60(parent, key);
}

static void *winCreate(void *view)
{
    return ((Rva0031C83DManager *)g_rva00DFEF1C)->m34(view);
}

static const char *nameText(const StringBase<char> &name)
{
    char *data = *(char **)&name;
    return data != 0 ? data + 8 : &g_rva00BBAC1C;
}

#define MAKE_COMMAND_BUTTON(self, window, commandName) do { \
    StringBase<char> name(commandName); \
    const CommandButton *button = (self)->findCommandButton(*(const AsciiString *)&name); \
    (self)->setControlCommand((window), button); \
    name.~StringBase<char>(); } while (0)

void ControlBar::rva0031C83D()
{
    m_1dc = 0;
    ((void (__fastcall *)(void *))((*(void ***)this)[2]))(this);
    ((Rva0031AC39 *)this)->rva0031AC39();

    Rva003200EB *scheme = new Rva003200EB();
    m_44 = scheme;
    ((ControlBarSchemeManager *)scheme)->init();

    if (g_rva00DFEF1C == 0)
        return;

    m_48 = (GameWindow *)winLookup(0, "ControlBar.wnd:ControlBarParent");
    m_48->winGetPosition(&m_1c, &m_20);
    m_58 = (GameWindow *)winLookup(0, "ControlBar.wnd:UnderConstructionWindow");
    m_64 = (GameWindow *)winLookup(0, "ControlBar.wnd:OCLTimerWindow");
    m_54 = (GameWindow *)winLookup(0, "ControlBar.wnd:BeaconWindow");
    m_4c = (GameWindow *)winLookup(0, "ControlBar.wnd:CommandWindow");
    m_50 = (GameWindow *)winLookup(0, "ControlBar.wnd:ProductionQueueWindow");
    m_60 = (GameWindow *)winLookup(0, "ControlBar.wnd:ObserverPlayerListWindow");
    m_5c = (GameWindow *)winLookup(0, "ControlBar.wnd:ObserverPlayerInfoWindow");

    {
        GameWindow *cmd = m_4c;
        GadgetCreateView view;
        cmd->snapshotCreateView(&view, false);
        const char *name = ((Rva0030F45FView *)cmd)->rva0030F45F();
        int sub = ((Rva0031C83DScheme *)g_rva00DFE9D8)->m16();
        int sub2 = ((Rva0031C83DScheme *)g_rva00DFE9D8)->m17();
        view.m_pad[0] = (int)name;
        view.m_pad[1] = sub;
        view.m_pad[2] = sub2;
        view.m_pad[3] = 0x93ec21;
        view.m_pad[4] = 0;
        GameWindow *w = (GameWindow *)winCreate(&view);
        m_68 = w;
        w->winSetUserData(m_2a0);
        w->winSetStatus(0x200);
        w->winClearStatus(0x10000);
    }

    {
        StringBase<char> name("ControlBar.wnd:ButtonCommand");
        GameWindow *w = (GameWindow *)winLookup((int)m_4c, nameText(name));
        if (w != 0)
            w->winSetStatus(0x200000);
        name.~StringBase<char>();
    }

    m_84 = (GameWindow *)winLookup(0, "ControlBar.wnd:RightHUD");
    m_a0 = (GameWindow *)winLookup(0, "ControlBar.wnd:WinUnitSelected");
    m_88 = (GameWindow *)winLookup(0, "ControlBar.wnd:CameoWindow");

    {
        unsigned int i = 0;
        do
        {
            ++i;
            StringBase<char> up("ControlBar.wnd:UnitUpgrade%d");
            ((AsciiString *)&up)->format("ControlBar.wnd:UnitUpgrade%d", i);
            GameWindow *uw = (GameWindow *)winLookup((int)m_84, nameText(up));
            m_8c[i - 1] = uw;
            uw->winSetStatus(0x200000);
            up.~StringBase<char>();
        }
        while (i < 5);
    }

    m_a4 = (GameWindow *)winLookup(0, "ControlBar.wnd:PopupCommunicator");
    MAKE_COMMAND_BUTTON(this, m_a4, "NonCommand_Communicator");
    m_a4->winSetTooltipFunc(bfmeTooltipCallback);

    {
        GameWindow *w = (GameWindow *)winLookup(0, "ControlBar.wnd:ButtonOptions");
        w = (GameWindow *)winLookup(0, "ControlBar.wnd:ButtonIdleWorker");
        if (w != 0)
        {
            MAKE_COMMAND_BUTTON(this, w, "NonCommand_IdleWorker");
            w->winSetTooltipFunc(bfmeTooltipCallback);
        }
    }
    {
        GameWindow *w = (GameWindow *)winLookup(0, "ControlBar.wnd:ButtonPlaceBeacon");
        if (w != 0)
        {
            MAKE_COMMAND_BUTTON(this, w, "NonCommand_Beacon");
            w->winSetTooltipFunc(bfmeTooltipCallback);
        }
    }
    {
        GameWindow *w = (GameWindow *)winLookup(0, "ControlBar.wnd:ButtonGeneral");
        if (w != 0)
        {
            MAKE_COMMAND_BUTTON(this, w, "NonCommand_GeneralsExperience");
            w->winSetTooltipFunc(bfmeTooltipCallback);
        }
    }
    {
        GameWindow *w = (GameWindow *)winLookup(0, "ControlBar.wnd:ButtonLarge");
        if (w != 0)
        {
            MAKE_COMMAND_BUTTON(this, w, "NonCommand_UpDown");
            w->winSetTooltipFunc(bfmeTooltipCallback);
        }
    }
    {
        GameWindow *w = (GameWindow *)winLookup(0, "ControlBar.wnd:PowerWindow");
        if (w != 0)
            w->winSetTooltipFunc(bfmeTooltipCallback);
    }
    {
        GameWindow *w = (GameWindow *)winLookup(0, "ControlBar.wnd:MoneyDisplay");
        if (w != 0)
            w->winSetTooltipFunc(bfmeTooltipCallback);
    }
    {
        GameWindow *w = (GameWindow *)winLookup(0, "ControlBar.wnd:GeneralsExp");
        if (w != 0)
            w->winSetTooltipFunc(bfmeTooltipCallback);
    }
    m_298 = (GameWindow *)winLookup(0, "ControlBar.wnd:WinUAttack");

    {
        StringBase<char> marker("ControlBar.wnd:BackgroundMarker");
        GameWindow *w = (GameWindow *)winLookup(0, nameText(marker));
        w->winGetScreenPosition(&m_280, &m_284);
        marker.~StringBase<char>();
    }
    {
        StringBase<char> marker("ControlBar.wnd:BackgroundMarker");
        GameWindow *w = (GameWindow *)winLookup(0, nameText(marker));
        w->winGetScreenPosition(&m_288, &m_28c);
        marker.~StringBase<char>();
    }

    if (m_c == 0)
        m_c = new WindowVideoManager();
    if (m_10 == 0)
        m_10 = new AnimateWindowManager();
    if (m_18 == 0)
        m_18 = new AnimateWindowManager();
    if (m_14 == 0)
        m_14 = new AnimateWindowManager();

    if (g_rva00DFF078 != 0)
    {
        {
            StringBase<char> name("BarButtonGenStarON");
            m_248 = (void *)((ImageCollection *)g_rva00DFF078)->findImageByName(*(const AsciiString *)&name);
            name.~StringBase<char>();
        }
        {
            StringBase<char> name("BarButtonGenStarOFF");
            m_24c = (void *)((ImageCollection *)g_rva00DFF078)->findImageByName(*(const AsciiString *)&name);
            name.~StringBase<char>();
        }
        {
            StringBase<char> name("SSChevron1L");
            g_rva00E01D00 = (void *)((ImageCollection *)g_rva00DFF078)->findImageByName(*(const AsciiString *)&name);
            name.~StringBase<char>();
        }
        {
            StringBase<char> name("SSChevron2L");
            g_rva00E01D04 = (void *)((ImageCollection *)g_rva00DFF078)->findImageByName(*(const AsciiString *)&name);
            name.~StringBase<char>();
        }
        {
            StringBase<char> name("SSChevron3L");
            g_rva00E01D08 = (void *)((ImageCollection *)g_rva00DFF078)->findImageByName(*(const AsciiString *)&name);
            name.~StringBase<char>();
        }
    }

    m_27c = -1;
    m_278 = 1;
    Rva0050DE39Init();
    m_29c = 1;
    switchToContext(0, 0);
}
