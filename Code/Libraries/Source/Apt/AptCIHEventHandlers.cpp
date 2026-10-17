// cl: /MD
// APT0.19.03 Xbox final PDB/MAP supplies AptCIH method spellings.
// Target caller6EE6C0 asserts pContext->isCIH(), obtains its CIH at6EE713,
// checks it using AptCIH.h, and keeps that object in ESI for calls6EF199 /
// 6EF1B6 /6EF218 /6EF27E to the two bodies below. Target virtual slot0C
// returns the hash; its flags at+10 agree with AptNativeHashBFME2.cpp.
// Only accessed vslots3/8 and the hash field are modeled; other slot prototypes are placeholders. This does not
// claim the complete donor class layout or identities of unused virtual slots.
// Native 0x006E0560..0x006E05A5 is a complete 69-byte CIH forwarding
// entry (RET12, then INT3 padding). Its this input is used only for the
// isCharacterInst assertion; all three stack arguments are passed unchanged
// to the independently recovered property-set worker at 0x006EE6C0.
// The assertion supplies AptCIH.cpp:599. The address-derived member view
// records the observed ECX/stack ABI. Vtable CE8C24 slot8 at CE8C44
// independently points to this full entry; the original method name is unknown.
class AptValue;
class EAStringC;
class BfmeAptValue006DCD20 { public: int isCharacterInst() const; };
extern bool rva006EE6C0(AptValue *, const EAStringC *, AptValue *);
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)

struct AptNativeHash { unsigned char unaccessed[16]; int eventFlags; };
class AptCIH {
    virtual void unused0();
    virtual void unused1();
    virtual void unused2();
    virtual AptNativeHash *GetNativeHashVirtual();
    virtual void unused4();
    virtual void unused5();
    virtual void unused6();
    virtual void unused7();
public:
    void SetEventHandler(int mask);
    void RemoveEventHandler(int mask);
    virtual bool rva006E0560(AptValue *, const EAStringC *, AptValue *);
};
void AptCIH::SetEventHandler(int mask) { AptNativeHash *hash=GetNativeHashVirtual(); hash->eventFlags |= mask; }
void AptCIH::RemoveEventHandler(int mask) { AptNativeHash *hash=GetNativeHashVirtual(); hash->eventFlags &= ~mask; }

bool AptCIH::rva006E0560(AptValue *context, const EAStringC *name, AptValue *value)
{
    if ((unsigned char)((BfmeAptValue006DCD20 *)this)->isCharacterInst() == 0) {
        g_bfmeAptAssertAtE17734("isCharacterInst()",
            "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptCIH.cpp", 599);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __debugbreak();
    }
    return rva006EE6C0(context, name, value);
}
