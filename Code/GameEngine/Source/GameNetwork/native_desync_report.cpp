// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX
//
// BFME1 GameNetwork/native_desync_report.cpp donor for the per-frame client CRC
// guard: the constructor snapshots the current CRC when CRC checking is enabled
// and the game mode passes the 0x42219 gate, otherwise it starts from zero (the
// zeroing arm wants /O1's and-form compaction, retail `and [esi],0`). The
// report method repeats the gate, takes the CRC again and, in a multiplayer game
// (0x42235) where it differs, shows the in-game message and appends a line to
// CLIENT_DESYNC_<machine>.txt. WorldBuilder 0x00C97F10 gives the structure; its
// mode comparisons are the two rowed GameLogic gates.

#include "ascii_string.h"
#include "unicode_string.h"

class GameLogic
{
public:
    bool rva0042219(void);
    bool isInMultiplayerGame(void);
    unsigned int getCRC(int mode);
    unsigned char m_pad000[0x40];
    unsigned int m_frame;
};

class BFMEDesyncCheck
{
public:
    BFMEDesyncCheck();
    void writeReportIfMismatched();

private:
    unsigned int m_crcBeforeClientUpdate;
};

// IPEnumeration's 8-byte object: the address list and the Winsock flag.
class IPEnumeration
{
public:
    IPEnumeration();
    ~IPEnumeration();
    AsciiString getMachineName(void);

private:
    void *m_IPlist;
    bool m_isWinsockInitialized;
};

// The in-game UI's message slot (+0x40).
class DesyncInGameUI
{
public:
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual void slot05();
    virtual void slot06();
    virtual void slot07();
    virtual void slot08();
    virtual void slot09();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void message(UnicodeString text, ...);
};

struct DesyncSystemTime
{
    unsigned short year, month, dayOfWeek, day, hour, minute, second, milliseconds;
};
struct DesyncFile;
extern "C" {
    __declspec(dllimport) DesyncFile *__cdecl fopen(const char *, const char *);
    __declspec(dllimport) unsigned int __cdecl fwrite(const void *, unsigned int, unsigned int, DesyncFile *);
    __declspec(dllimport) int __cdecl fclose(DesyncFile *);
    __declspec(dllimport) void __stdcall GetLocalTime(DesyncSystemTime *);
}

extern unsigned char BfmeClientCRCCheckEnabled;
// BfmeClientCRCCheckEnabled: matched references place it at VA 0xe02d85 (zero-filled .bss).
unsigned char BfmeClientCRCCheckEnabled;
extern GameLogic *TheGameLogic;
class InGameUI;
extern InGameUI *TheInGameUI;

// ??0BFMEDesyncCheck@@QAE@XZ
BFMEDesyncCheck::BFMEDesyncCheck()
{
    if (BfmeClientCRCCheckEnabled != 0)
    {
        GameLogic *logic = TheGameLogic;
        if (logic->rva0042219())
        {
            m_crcBeforeClientUpdate = logic->getCRC(0);
            return;
        }
    }
    m_crcBeforeClientUpdate = 0;
}

// Both CRCs come from this machine. A difference means client work changed
// simulation state outside GameLogic::update; this is not a peer CRC exchange.
void BFMEDesyncCheck::writeReportIfMismatched()
{
    if (BfmeClientCRCCheckEnabled == 0)
        return;
    GameLogic *logic = TheGameLogic;
    if (!logic->rva0042219())
        return;
    unsigned int crc = logic->getCRC(0);
    if (TheGameLogic->isInMultiplayerGame() && m_crcBeforeClientUpdate != crc)
    {
        if (TheInGameUI)
            ((DesyncInGameUI *)TheInGameUI)->message(L"GameLogic changed outside of GameLogic::update()!");
        AsciiString filename;
        AsciiString report;
        IPEnumeration enumeration;
        filename.format("CLIENT_DESYNC_%s.txt", enumeration.getMachineName().str());
        DesyncFile *file = fopen(filename.str(), "a");
        DesyncSystemTime time;
        GetLocalTime(&time);
        unsigned int frame = TheGameLogic->m_frame;
        report.format("Desync detected on frame %d on %u-%u-%u %u:%u:%u\n\n",
            frame,
            time.month, time.day, time.year, time.hour, time.minute, time.second);
        fwrite(report.str(), 1, report.getLength(), file);
        fclose(file);
    }
}
