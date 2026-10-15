// cl: /MD /EHsc
// ?rva006ff980@@YAXPAVAptValue@@AAVEAStringC@@H@Z
// retail 0x006FF980..0x006FFC2A (682 bytes), cdecl, recursive.
// Callers: the rowed path workers 0x006FFC30 and 0x006FFCE0, which pass
// (value, sBuf, 0) and (value, sBuf, 1). WB twin 0x0175DEB0
// (AptActionInterpreter.cpp assert lines 0x677/0x67C) supplies the flow.
// Target evidence: the retail assert text names the four CIH predicates
// (isButtonInst inlined with the AptCIH.h:0xB5 this-assert, as in the matched
// getVariable 0x006FFD80); the separator is "." for a dotted path and "/"
// otherwise; a parentless clip prints "_level%d" from the signed 17-bit field
// at +0x58; a named clip appends separator+name (+0x08); an unnamed one gets
// "instance%ld", stores it as its name and registers itself under it in the
// parent character's native hash (+0x4C, then +0x10). Field names are
// structural inferences; the function name is address-derived.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)
extern "C" int __cdecl sprintf(char *, const char *, ...);

#define APT_ASSERT(cond, text, file, line)                                     \
    if (!(cond)) {                                                             \
        g_bfmeAptAssertAtE17734(text, file, line);                             \
        if (g_bfmeAptBreakOnAssertAtDDC01C)                                    \
            __debugbreak();                                                    \
    }
#define APT_CIH_H "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h"
#define APT_INTERP_CPP "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptActionInterpreter.cpp"

class EAStringC
{
    void *mpData;
public:
    EAStringC();
    EAStringC(const char *value);
    ~EAStringC();
    EAStringC &operator=(const EAStringC &);
    bool IsEmpty() const;
    EAStringC &Rva006D4F00Append(const EAStringC &);
    EAStringC &Rva006D50A0Append(const char *);
    void __cdecl rva006D62C0(const char *, ...);
};
EAStringC rva006D5160(const char *, const EAStringC &);

class AptValue;
struct AptNativeHash
{
    void Set(const EAStringC *const, AptValue *const);
};
struct Rva006FF980Character
{
    char pad0[0x10];
    AptNativeHash *mpNativeHash; // +0x10
};
class AptValue
{
public:
    bool isUndefined() const;
};
class Rva006DBB30SarDwordField
{
public:
    int get() const; // 0x006DBB30
};
class BfmeAptValue006DCD20
{
public:
    int rva006E02B0() const; // rowed provider at 0x006E02B0; callers test AL
};
class AptCIH : public AptValue
{
public:
    bool IsSpriteInstBase() const; // 0x006CFCD0
    bool IsLevelInst() const;      // 0x006E03A0
    bool IsCharacterInst() const;  // 0x006E0200
    __forceinline bool isButtonInst() const
    {
        APT_ASSERT(this, "this", APT_CIH_H, 0xB5)
        return ((const Rva006DBB30SarDwordField *)this)->get() == 14 && !isUndefined();
    }
    // Keep the AL-test adapter inline without a competing external definition.
    __declspec(dllimport) __forceinline bool isTextInst() const
    {
        return (unsigned char)((const BfmeAptValue006DCD20 *)this)->rva006E02B0();
    }
    __forceinline AptCIH *c_characterInst()
    {
        APT_ASSERT(IsCharacterInst(), "isCharacterInst()", APT_CIH_H, 0xA5)
        return this;
    }
    char pad0[0x8];
    EAStringC mName;                  // +0x08
    char padC[0x3C];
    AptCIH *mpParent;                 // +0x48
    Rva006FF980Character *mpCharacter; // +0x4C
    char pad50[0x8];
    int mnLevel : 17;                 // +0x58
};

void rva006ff980(AptValue *pValue, EAStringC &sBuf, int bDotted)
{
    AptCIH *pContext = (AptCIH *)pValue;
    APT_ASSERT(pContext->IsSpriteInstBase() || pContext->isButtonInst() || pContext->IsLevelInst()
                   || pContext->isTextInst(),
               "pContext->isSpriteInstBase() || pContext->isButtonInst() || pContext->isLevelInst() || pContext->isTextInst()",
               APT_INTERP_CPP, 0x677)
    const char *sep = !bDotted ? "/" : ".";
    AptCIH *pParent = pContext->mpParent;
    if (!pParent) {
        APT_ASSERT(pContext->IsSpriteInstBase() || pContext->isButtonInst() || pContext->IsLevelInst()
                       || pContext->isTextInst(),
                   "pContext->isSpriteInstBase() || pContext->isButtonInst() || pContext->isLevelInst() || pContext->isTextInst()",
                   APT_INTERP_CPP, 0x67C)
        if ((bDotted == 0 && pContext->mnLevel != 0) || bDotted == 1) {
            char buf[16];
            sprintf(buf, "_level%d", pContext->mnLevel);
            EAStringC level(buf);
            sBuf = level;
        }
        return;
    }
    rva006ff980(pParent, sBuf, bDotted);
    if (!pContext->mName.IsEmpty()) {
        sBuf.Rva006D4F00Append(rva006D5160(sep, pContext->mName));
    } else {
        int id = pContext->mnLevel;
        EAStringC name;
        sBuf.Rva006D50A0Append(sep);
        name.rva006D62C0("instance%ld", id);
        sBuf.Rva006D4F00Append(name);
        pContext->mName = name;
        Rva006FF980Character *pCharacter = pParent->c_characterInst()->mpCharacter;
        AptNativeHash *pHash = pCharacter->mpNativeHash;
        pHash->Set(&name, pContext);
    }
}
