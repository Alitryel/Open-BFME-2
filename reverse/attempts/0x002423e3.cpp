// ?deleteLoadScreen@GameLogic@@QAEXXZ
// partial score=0.038 date=2026-10-17
// cl: /O1 /G7 /DNDEBUG /MD /EHs /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist
// stlport
//
// Home unit: Code/GameEngine/Source/GameLogic/System/GameLogicInit.cpp
// ?deleteLoadScreen@GameLogic@@QAEXXZ @0x002423E3 1436B (SEH).
// Donor: BFME 1 game/GameEngine/Source/GameLogic/System/GameLogicInit.cpp
// (GameLogic::deleteLoadScreen). BFME 2 differs from the donor with moved
// field offsets and out-of-line setters (Rva001DBB82OneSetter::enable /
// Rva001DBB87ZeroSetter::disable). Field names stay offset names: only the
// donor knows their meaning.

// Missing: full definitions for AsciiString, GameWindowTransitionsHandler,
// Mouse, W3DDisplay, GameLogic members, TheGameLogic, Sleep and free-function
// callees (rva0023C7BB / rva0023C7D2 / rva0023DCCE / rva0023DC8E) plus ref1/ref2.

class AsciiString
{
public:
    AsciiString(const char *s = 0);
    bool isEmpty() const;
};

class GameWindowTransitionsHandler
{
public:
    unsigned char padH[0xFC + 4];
    int m_someField;
    int m_field115;
    virtual void unused0();
    virtual void unused1();
    virtual void unused2();
    virtual void unused3();
    virtual void unused4();
    virtual void unused5();
    virtual void unused6();
    virtual void unused7();
    virtual void unused8();
    virtual void unused9();
    virtual void unused10();
    virtual void unused11();
    virtual void unused12();
    virtual void unused13();
    virtual void unused14();
    virtual void unused15();
    virtual void unused16();
    virtual void unused17();
    virtual void unused18();
    virtual void unused19();
    virtual bool rva0025D2F6();
    virtual void unused21();
    virtual void unused22();
    virtual void unused23();
    virtual void unused24();
    virtual void unused25();
    virtual void unused26();
    virtual void unused27();
    virtual void unused28();
    virtual void unused29();
    virtual void unused30();
    virtual void unused31();
    virtual void unused32();
    virtual void unused33();
    virtual void unused34();
    virtual void unused35();
    virtual void unused36();
    virtual void unused37();
    virtual void unused38();
    virtual void unused39();
    virtual void unused40();
    virtual void unused41();
    virtual void unused42();
    virtual void unused43();
    virtual void unused44();
    virtual void unused45();
    virtual void unused46();
    virtual void unused47();
    virtual void unused48();
    virtual void unused49();
    virtual void unused50();
    virtual void unused51();
    virtual bool isFinished();
    virtual void incrementLock();
    virtual void setGroup(AsciiString, int);
    virtual void enable();
    virtual void reverse();
    virtual void reverse(AsciiString);
    virtual void decrementLock();
    virtual void disable();
};

class Mouse
{
public:
    void _bfme_setEngineVisibility(int);
};

class W3DDisplay
{
public:
    unsigned char padW[0x40];
    int m_frame;
    float m_frameTime;
    virtual void unused0();
    virtual void unused1();
    virtual void unused2();
    virtual void unused3();
    virtual void unused4();
    virtual void unused5();
    virtual void unused6();
    virtual void unused7();
    virtual void unused8();
    virtual void unused9();
    virtual void unused10();
    virtual void unused11();
    virtual void unused12();
    virtual void unused13();
    virtual void unused14();
    virtual void unused15();
    virtual void unused16();
    virtual void unused17();
    virtual void unused18();
    virtual void unused19();
    virtual void unused20();
    virtual void unused21();
    virtual void unused22();
    virtual void rva0025D2F6();
    bool isTransitioning();
    void update();
    void setGroup(AsciiString, int, int);
};

class GameLogic;

extern GameWindowTransitionsHandler *TheGameWindowTransitionsHandler;
extern Mouse *TheMouse;
extern W3DDisplay *TheW3DDisplay;
extern GameLogic *TheGameLogic;
extern int ref1;
extern int ref2;

void rva0023C7BB(int);
void rva0023C7D2();
void rva0023DCCE(AsciiString, int &, int &);
void rva0023DC8E(AsciiString);
void Sleep(int);

GameWindowTransitionsHandler *TheGameWindowTransitionsHandler;
Mouse *TheMouse;
W3DDisplay *TheW3DDisplay;

// ---- shim declarations for the callees named in the seat notes ----------
struct Rva0023C7D2
{
    void rva0023C7BB(int);
    void rva0023C7D2();
};

struct Rva001DBB82OneSetter
{
    void enable();
};

struct Rva001DBB87ZeroSetter
{
    void disable();
};

struct SubsystemInterface;

struct GameLogic
{
    unsigned char pad0[0x9c];
    unsigned char m_loadScreenActive;
    unsigned char pad0a;
    unsigned char m_fadeOut;
    unsigned char pad0b;
    unsigned char pad1[0x6E];
    int m_loadScreenState;
    int m_transitionActive;
    AsciiString m_someString;
    int m_someField90;
    unsigned char pad2[0xB28];
    unsigned char m_flag11C8;
    unsigned char pad3[3];
    void deleteLoadScreen();
    bool rva001DCD1C();
    void rva00222F55(int);
    void setGameMode(int, int);
};

void GameLogic::deleteLoadScreen()
{
    char __gsbuf[12];
    *(volatile char *)&__gsbuf[0];
    *(volatile char *)&__gsbuf[11];
    if (m_loadScreenActive)
    {
        TheW3DDisplay->rva0025D2F6();
        if (TheGameWindowTransitionsHandler &&
            !TheGameWindowTransitionsHandler->isFinished())
        {
            int state = m_loadScreenState;
            if (state == 1 || state == 5 || state == 2)
            {
                W3DDisplay *disp = TheW3DDisplay;
                unsigned int fr = (unsigned int)disp->m_frame;
                if (fr < 6)
                {
                    if (fr >= 5)
                        rva0023C7BB(0x64);
                    else
                    {
                        rva0023C7BB((int)disp->m_frameTime);
                        *(volatile float*)&disp->m_frameTime = disp->m_frameTime + 0.25f;
                    }
                }
            }
        }
        return;
    }

    bool finished = false;
    m_loadScreenActive = 0;

    if (m_transitionActive &&
        TheW3DDisplay->isTransitioning() &&
        !TheGameLogic->m_flag11C8)
    {
        if (m_fadeOut)
        {
            TheGameWindowTransitionsHandler->incrementLock();
            TheGameWindowTransitionsHandler->setGroup(AsciiString("FadeWholeScreen"), 0);
            TheGameWindowTransitionsHandler->enable();
            TheGameWindowTransitionsHandler->reverse();
            TheGameWindowTransitionsHandler->decrementLock();

            while (TheW3DDisplay->isTransitioning() &&
                   TheW3DDisplay->m_frame < 100 &&
                   !TheGameWindowTransitionsHandler->isFinished())
            {
                TheW3DDisplay->update();
                Sleep(1);
            }

            TheW3DDisplay->rva0025D2F6();
            TheGameWindowTransitionsHandler->reverse(AsciiString("FadeWholeScreen"));
            TheGameWindowTransitionsHandler->reverse();
            TheGameWindowTransitionsHandler->disable();
            m_fadeOut = 0;
            finished = true;
        }
        else
        {
            switch (m_loadScreenState)
            {
            case 0:
                TheMouse->_bfme_setEngineVisibility(1);
                TheGameWindowTransitionsHandler->setGroup(AsciiString("FadeWholeScreen"), 0);
                TheGameWindowTransitionsHandler->enable();
                TheGameWindowTransitionsHandler->reverse();
                while (TheW3DDisplay->isTransitioning() &&
                       TheW3DDisplay->m_frame < 100 &&
                       !TheGameWindowTransitionsHandler->isFinished())
                {
                    TheW3DDisplay->update();
                    Sleep(5);
                }
                rva0023C7D2();
                if (!m_someString.isEmpty())
                {
                    TheGameWindowTransitionsHandler->disable();
                    TheGameWindowTransitionsHandler->setGroup(AsciiString("FadeWholeScreen"), 0);
                    TheGameWindowTransitionsHandler->reverse();
                    TheW3DDisplay->setGroup(m_someString, 1, 0xa0);
                }
                else
                {
                    TheW3DDisplay->rva0025D2F6();
                }
                finished = true;
                break;
            case 1:
                TheW3DDisplay->rva0025D2F6();
                TheGameWindowTransitionsHandler->disable();
                finished = true;
                break;
            case 4:
            case 7:
                TheGameWindowTransitionsHandler->setGroup(AsciiString("FadeWholeScreen"), 0);
                if (TheGameWindowTransitionsHandler->m_someField != 0)
                {
                    finished = true;
                    break;
                }
                TheGameWindowTransitionsHandler->enable();
                TheGameWindowTransitionsHandler->reverse();
                while (TheW3DDisplay->isTransitioning() &&
                       TheW3DDisplay->m_frame < 100 &&
                       !TheGameWindowTransitionsHandler->isFinished())
                {
                    TheW3DDisplay->update();
                    Sleep(1);
                }
                break;
            case 2:
            case 3:
                TheGameWindowTransitionsHandler->setGroup(AsciiString("FadeWholeScreen"), 0);
                TheGameWindowTransitionsHandler->enable();
                TheGameWindowTransitionsHandler->reverse();
                while (TheW3DDisplay->isTransitioning() &&
                       TheW3DDisplay->m_frame < 100 &&
                       !TheGameWindowTransitionsHandler->isFinished())
                {
                    TheW3DDisplay->update();
                    Sleep(5);
                }
                TheGameWindowTransitionsHandler->disable();
                finished = true;
                break;
            default:
                TheGameWindowTransitionsHandler->disable();
                finished = true;
                break;
            }
        }
    }

    if (m_transitionActive)
        rva0023C7D2();

    if (finished)
        TheMouse->_bfme_setEngineVisibility(1);

    TheGameWindowTransitionsHandler->m_field115 = 0;
    TheW3DDisplay->update();

    GameLogic *logic = TheGameLogic;
    if (logic)
    {
        bool inGame = logic->rva001DCD1C();
        if (inGame)
        {
            logic->rva00222F55(1);
            logic->setGameMode(0, 6);
        }
        else
        {
            logic->rva00222F55(0);
            logic->setGameMode(0, 5);
        }
    }

    AsciiString empty("");
    rva0023DCCE(empty, ref1, ref2);
    rva0023DC8E(empty);
    m_someField90 = 7;
}
