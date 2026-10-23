// cl: /O2 /DNDEBUG /MD

// FESL dotted-quad parse at 0x00655790 (92B). Direct reuse of
// Open-BFME-1 Code/GameEngine/Source/GameNetwork/Y2FeslAddressFormat.cpp
// (Rva007E8760Addr::parse at 0x7E86D0, 92B — size-diff zero). Parse packs
// %d.%d.%d.%d into this+8 (network order via shift-add) and stores the
// second argument at +0xC. Retail calls the sscanf import THUNK directly
// (E8 to 0x629892, not FF15 to the IAT), so the TU keeps BFME1's
// plain-extern sscanf decl (C `sscanf` decorates to `_sscanf`, resolving
// through the existing pin); stdio.h's dllimport spelling emits the
// indirect call and misses by one byte.

extern "C" int __cdecl sscanf(const char *buf, const char *fmt, ...);
extern "C" int __cdecl sprintf(char *buf, const char *fmt, ...);

struct Rva007EB810Diag
{
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void fail(const char *expr, const char *file, int line);
};

extern Rva007EB810Diag *Rva007EB810Get();

class Rva007E8760Addr
{
public:
    void format(char *destination, unsigned destinationSize);
    void parse(const char *addressText, int extra);

private:
    char m_pad[8];
    unsigned m_addr;
    int m_extra;
};

void Rva007E8760Addr::format(char *destination, unsigned destinationSize)
{
    if (destinationSize < 17)
        Rva007EB810Get()->fail(
            "false",
            "\\views\\feslbuild_main\\jabba\\fesl\\source\\address.cpp",
            49);
    unsigned packedAddress = m_addr;
    sprintf(destination, "%hu.%hu.%hu.%hu",
        (unsigned char)(packedAddress >> 24),
        (unsigned char)(packedAddress >> 16),
        (unsigned char)(packedAddress >> 8),
        (unsigned char)packedAddress);
}

void Rva007E8760Addr::parse(const char *addressText, int extra)
{
    int firstOctet, secondOctet, thirdOctet, fourthOctet;
    sscanf(addressText, "%d.%d.%d.%d", &firstOctet, &secondOctet, &thirdOctet, &fourthOctet);
    unsigned packedAddress = (unsigned)firstOctet;
    packedAddress = (packedAddress << 8) + (unsigned)secondOctet;
    packedAddress = (packedAddress << 8) + (unsigned)thirdOctet;
    packedAddress = (packedAddress << 8) + (unsigned)fourthOctet;
    m_addr = packedAddress;
    m_extra = extra;
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?parse@Rva00800780Addr@@QAEXPBDH@Z=?parse@Rva007E8760Addr@@QAEXPBDH@Z")
#pragma comment(linker, "/alternatename:?bfmeFmtVJJ@BfmeThingVJJ@@QAEXPADH@Z=?format@Rva007E8760Addr@@QAEXPADI@Z")
