// ?Rva006ED845@@YAPAVAptValue@@XZ
// partial score=0.207 date=2026-10-17
// cl: /O2 /DNDEBUG /MD /EHsc
// Target 0x006EE3B0 (393B) and 0x006EE540 (373B), with entry/return boundaries
// confirmed in game.dat. reverse/string_xrefs.tsv names their callback slots
// gAptFuncs.pfnGetBytesTotal and gAptFuncs.pfnGetBytesLoaded; the matching
// ActionScript property names are also in R4PerfectHashWordSets.cpp. The
// target calls through those slots with a String path and converts the
// returned byte count to an Apt float. Slot identity is table evidence; the
// address-derived global names below do not claim an original source name.
// The +0x34 resource pointer and +8 EAStringC field follow the target loads.

extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;

class AptCIH;
class EAStringC;
class Rva006DBB30SarDwordField
{
public:
    int get() const;
};

class AptValue
{
public:
    AptCIH *c_cih(bool bUndefinedOK);
    bool isCIH(bool bUndefinedOK) const;
    bool isUndefined() const;
    bool getIsDefined() const;
    float toFloat() const;
    int toInteger() const;
    void toString(EAStringC &) const;
    AptValue *rva006DCF60(bool bUndefinedOK);
    int isCharacterInst() const;
    void *rva006E0F40() const;
};

class AptCIH
{
public:
    unsigned char prefix[0x4c];
    void *member4C;
    char unknown50[8];
    signed int depth:17;
    unsigned int unknownDepth17:15;
    void rva006E1DD0(void *);
    void *rva006E1170() const;
    void factorySetProperty(int, float, bool);
};

class EAStringC
{
public:
    class StringDataC
    {
    public:
        unsigned short m_uRefCount;
        unsigned short m_uSize;
        unsigned short m_uMaxSize;
        unsigned short m_uHash;
    };
    StringDataC *data;
public:
    EAStringC();
    EAStringC(const char *);
    EAStringC(const EAStringC &);
    EAStringC &clear();
    EAStringC &operator=(const EAStringC&);
    ~EAStringC();
    EAStringC &Rva006D4F00Append(const EAStringC &other);
    const char *rva00620090() const;
    int GetAt(int) const;
    unsigned int rva006D3750() const;
    int rva006D54B0(int,int);
};
extern EAStringC::StringDataC g_eaEmptyStringData;

class AptBasePtrStack
{
public:
    AptValue *At(int index);
};

class Rva006DB160
{
public:
    void *allocBlock(int size);
};

class BfmeSubmitter1283
{
public:
    void *bfmeSubmit1283(int, int, int, int, int, int, int, float *, int, int, int, int);
};

class Rva006E9A40List
{
public:
    void add(AptCIH *);
};

extern AptBasePtrStack g_aptBasePtrStackAtE182E0;
extern Rva006DB160 g_rva006DB160AtE176E8;
extern Rva006E9A40List *g_rva006E9A40ListAtE176D0;
extern char g_byteE1771C;
extern int g_aptFuncsAtE18078;

// externs referenced by pointer arithmetic in the disassembly
extern char g_aptValueTableAtDDC01C;

#define g_aptBasePtrStack (*(AptBasePtrStack*)0xe182e0)
#define g_allocBlock ((Rva006DB160*)0xe176e8)
#define g_aptList ((Rva006E9A40List*)0xe176d0)
#define g_bAtE1771C (*(char*)0xe1771c)

AptValue *Rva006ED845()
{
    AptValue *p0 = g_aptBasePtrStack.At(0);
    AptValue *esi = g_aptBasePtrStack.At(1);
    AptValue *edi = g_aptBasePtrStack.At(2);
    AptValue *ebp = g_aptBasePtrStack.At(3);
    AptValue *p4 = g_aptBasePtrStack.At(4);
    AptValue *p5 = g_aptBasePtrStack.At(5);
    int nBase = p4->toInteger();
    float f1 = ebp->toFloat();
    float f2 = edi->toFloat();
    float f3 = esi->toFloat();
    float f4 = p5->toFloat();

    EAStringC str;
    p0->toString(str);
    AptValue *rv = (AptValue*)g_allocBlock->allocBlock(0x40);
    if (rv == 0) {
        g_bfmeAptAssertAtE17734("AptValue", "alloc", 0x3c3);
        if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
    }
    rv = (AptValue*)(1 ? (int)rv : (int)rv);
    int n = (1 ? p0->rva006DCF60(false)->toInteger() : 0);
    float fsum = (float)(double)((f1+f2)+(f3+f4));
    float fresult = (float)n + fsum;
    *(volatile float*)&fresult = fresult;
    return (AptValue*)(int)fresult;
}
