// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /EHsc /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_STLP_NO_EXCEPTIONS
// Independent recorder version check. The constructor and CRC dispatcher
// retain their unresolved contracts in Rva0037BCC4DeferredCtorCRC.cpp.
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

class Rva0037D097CRCView
{
public:
    void rva0037D097(unsigned int crc);
    unsigned int rva0037BD64();
};

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

class GlobalData;
extern GlobalData *TheWritableGlobalData;

// Same 0x5C string-bearing header as the independently rowed destructor.
// Target accesses, not the donor layout, establish the six string offsets.
class Rva0037B5DF
{
public:
    ~Rva0037B5DF();
    char opaque00[0x20];
    AsciiString options20;
    int player24;
    UnicodeString filename28;
    bool forPlayback2C;
    char opaque2D[3];
    UnicodeString name30;
    char time34[0x10];
    UnicodeString version44;
    UnicodeString versionTime48;
    unsigned int iniCRC4C;
    char opaque50[8];
    UnicodeString string58;
};
class Version
{
public:
    UnicodeString getFullUnicodeVersion();
    UnicodeString getUnicodeBuildTime();
};
extern Version *TheVersion;
struct RecorderCRCGlobalView
{
    char opaque00[0xB04];
    unsigned int iniCRCB04;
};

// Native Ghidra 0x0037D0EF..0x0037D1E6; 247 bytes; thiscall RET 4.
// ZH Recorder::testVersionPlayback and BFME1 1399ad37 RecorderReadReplayHeader
// supply the comparison sequence. Target uses a Unicode filename and omits
// the donor's version-number/executable checks. The destructor proves header
// storage; retail proves forPlayback+2C, version+44/+48, and CRC+4C/global+B04.
bool Rva0037BBED::rva0037D0EF(UnicodeString filename)
{
    Rva0037B5DF header;
    header.forPlayback2C = true;
    header.filename28 = filename;
    bool success = rva0037CBB6(header);
    if (!success)
        return false;
    bool versionStringDiff = header.version44.compare(TheVersion->getFullUnicodeVersion()) != 0;
    bool versionTimeStringDiff = header.versionTime48.compare(TheVersion->getUnicodeBuildTime()) != 0;
    bool exeDifferent = versionStringDiff || versionTimeStringDiff;
    bool iniDifferent = header.iniCRC4C != reinterpret_cast<const RecorderCRCGlobalView *>(TheWritableGlobalData)->iniCRCB04;
    if (exeDifferent || iniDifferent)
        return true;
    return false;
}
