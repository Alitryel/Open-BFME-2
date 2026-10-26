// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /EHsc /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_STLP_NO_EXCEPTIONS
// Constructor and CRC dispatch retain unresolved provider contracts here.
// The independent version check stays in Rva0037BCC4_Unresolved.cpp.
// ?createRecorder@@YAPAVRecorderClass@@XZ @0x0037BCC4 53B
// Evidence: leaf lane; allocates 0xE7C via rowed ??2 0x0002FDA0 then pinned
// ctor 0x0037BB98 with null check and EH prolog; caller 0x0022F6A1 unclaimed;
// class layout copied from Rva0037BBEDDtor.cpp so sizeof is 0xE7C.
#include "ascii_string.h"
#include "unicode_string.h"
#include "GameLogicObjectLookupView.h"
template <> int StringBase<unsigned short>::compare(const StringBase<unsigned short> &) const throw();

class Rva0037BB53
{
public:
    Rva0037BB53();
    virtual ~Rva0037BB53();
    char m_pad[0xE3C - 4];
};

// Base ctor 0x001B4E63 / dtor 0x001B4E74 by their row names ??0/??1SubsystemInterface (SubsystemInterface.cpp).
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

// The CRC queue's list wrappers at 0x0037D097/0x0037BD64 are rowed (ICF-shared)
// under FXList's names; bind to those owners and cast at the call.
class FXNugget;
class FXList
{
public:
    void addFXNugget(FXNugget *nugget);
    int rva0037BD64();
};
class Rva0037D097CRCView;

class Rva0037B5DF;

class Rva0037BBED : public SubsystemInterface
{
public:
    Rva0037BBED();
    virtual ~Rva0037BBED();
    virtual void init();
    AsciiString rva0037B70A();
    bool rva0037CBB6(Rva0037B5DF &header);
    bool rva0037D0EF(UnicodeString filename);
    void rva0037D0A7(unsigned int crc, int player, bool fromPlayback, unsigned int frame);
private:
    Rva0037D097CRCView *m_0c;
    void *m_10;
    UnicodeString m_14;
    int m_18;
    int m_1c;
    UnicodeString m_20;
    Rva0037BB53 m_24;
    // Retail new pushes 0xE7C; the constructor explicitly clears the final +0xE78 word.
    int m_e60, m_e64, m_e68, m_e6c;
    unsigned char m_e70;
    char m_padE71[3];
    int m_e74;
    int m_frameE78;
};

class RecorderClass;
RecorderClass *createRecorder();

// Native Ghidra extent 0x0037BB98..0x0037BBED, 85 bytes, thiscall RET 0.
// The existing allocator and destructor establish this receiver and vtable.
// Two default UnicodeStrings and the +0x24 GameInfo-shaped member explain
// EH states 0..3; native calls identify its constructor and the reset worker.
// The ZH Recorder constructor has the same member/reset relationship; target
// offsets and the final +0xE78 clear are taken from retail rather than the donor.
Rva0037BBED::Rva0037BBED()
{
    m_frameE78 = 0;
    init();
}

// Native Ghidra extent 0x0037B326..0x0037B3D1, 171 bytes, thiscall RET 0.
// The recorder vtable at VA 0x00C18828 places this method in slot 1.
// ZH Recorder::init supplies the clear/reset/map/seed sequence; retail proves
// every receiver/global offset and the additional CRC/analysis state stores.
// Separate setMap calls preserve retail's two by-value argument temporaries.
class GlobalData;
extern GlobalData *TheWritableGlobalData;
extern int NET_CRC_INTERVAL;
unsigned int GetGameLogicRandomSeed();
class GameInfo {
public:
 virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
 virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
 virtual void reset();
 void clearSlotList(); void setMap(AsciiString s); void setSeed(int);
 char opaque04[0x34];
};

struct RecorderGlobalView {
    char opaque00[0x0C];
    AsciiString map0C;
    char opaque10[0xAC0-0x10];
    AsciiString pendingAC0;
};

class GameLogic;
extern GameLogic *TheGameLogic;
class Rva00241529CRCView
{
public:
    char opaque00[0x71];
    bool crcProcessing71;
};

// Native Ghidra 0x0037D0A7..0x0037D0EF; 72 bytes; thiscall RET 16.
// Reference: BFME 1 1399ad37d42ea52a63829e417c46a1ba9ed2cd20,
// game/GameEngine/Source/Common/System/RecorderHandleCRCMessage.cpp.
// The four argument roles and processing sequence follow that readable donor;
// retail proves +0xC receiver storage, +0x71 flag and all three call targets.
// Native rva0037BD64 already checks the queue before removing its front value.
// Its folded list wrappers are named opaquely here: the FXList ledger spelling
// at those addresses does not establish a recorder's CRC storage as FXList.
void Rva0037BBED::rva0037D0A7(unsigned int crc, int player, bool fromPlayback, unsigned int frame)
{
    if (fromPlayback)
        reinterpret_cast<FXList *>(m_0c)->addFXNugget(reinterpret_cast<FXNugget *>(crc));
    reinterpret_cast<FXList *>(m_0c)->rva0037BD64();
    if (frame > 0)
    {
        Rva00241529CRCView *logic = reinterpret_cast<Rva00241529CRCView *>(TheGameLogic);
        if (!logic->crcProcessing71)
            TheGameLogic->ProcessCRC(crc, player, frame, 0, false, 0);
    }
}

