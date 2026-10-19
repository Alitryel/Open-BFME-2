// cl: /O2 /MD /EHsc
#include "AptObject/AptScriptFunction.h"
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
    bool rva006D3510(const char *) const;
    const char *rva00620090() const;
    EAStringC(const EAStringC &);
    EAStringC &Rva006D4F00Append(const EAStringC &);
    EAStringC &Rva006D50A0Append(const char *);
    void __cdecl rva006D62C0(const char *, ...);
};
EAStringC rva006D5160(const char *, const EAStringC &);

class AptValue;
struct Rva006FF980Character
{
    char pad0[0x10];
    AptNativeHash *mpNativeHash; // +0x10
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
    int isNativeFunction() const;
    bool rva006DCA60() const;
    int isObject() const;
    int isInteger() const;
    int isFloat() const;
    int isString() const;
    int toInteger() const;
    float rva006DD460();
    BfmeAptValue006DCD20 *rva006DCF60(bool);
    BfmeAptValue006DCD20 *checkedString();
    int isScriptFunction() const;
    bool isUndefined() const;
    int rva006E03A0() const;
    BfmeAptValue006DCD20 *rva006DCF20();
    BfmeAptValue006DCD20 *rva006DCEE0();
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
    // The canonical AptValue base supplies the eight-byte vptr/flags prefix.
    EAStringC mName;                  // +0x08
    char padC[0x3C];
    AptCIH *mpParent;                 // +0x48
    Rva006FF980Character *mpCharacter; // +0x4C
    char pad50[0x8];
    int mnLevel : 17;                 // +0x58
    unsigned int state;              // +0x5C; retail tests bits 18..19
    const AptCIH *rva006E0CB0() const;
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

// The callback field at +0x20 and its context/count ABI are corroborated by
// the retail native-function constructor and this function's indirect call.
struct BfmeAptNativeFunctionView
{
    char opaque[0x20];
    AptValue *(__cdecl *function)(AptValue *, int);
};
class Rva006CD650
{
public:
    void *rva006CD650();
};
extern AptValue *gpUndefinedValue;
inline void *operator new(unsigned int, void *storage) { return storage; }

class AptBasePtrStack
{
public:
    int count, capacity;
    AptValue **items;
    BfmeAptValue006DCD20 *At(int);
    void rva006E3AA0(int);
    void rva006FE050(int);
    void rva006FE920();
    AptValue *rva006FE580(int);
    void PopAndPush(int, BfmeAptValue006DCD20 *);
    void rva006FDF30(BfmeAptValue006DCD20 *);
    // This is the inlined call-site form. The established out-of-line
    // PushNoInc provider has a different body; do not emit a competing copy.
    __declspec(dllimport) __forceinline void PushNoInc(AptValue *value)
    {
        APT_ASSERT(count < capacity, "m_nElements < m_nCapacity",
                   "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_AptBasePtrStack.h", 0x90)
        items[count++] = value;
    }
};
template<class T> struct AptValuePtrStack
{
    int count, capacity;
    AptValue **items;
    void push(AptValue *);
    void pop();
    __declspec(dllimport) __forceinline void popInline()
    {
        APT_ASSERT(count > 0, "size() > 0",
                   "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_AptValuePtrStack.h", 0x7D)
        items[count - 1]->Release();
        --count;
    }
};
struct AptActionInterpreter
{
    struct DebugCallStackInfo_t;
    AptBasePtrStack stack;
    char pad0C[0x24 - 12];
    AptValuePtrStack<AptValue> thisStack; // +0x24
    AptScriptFunctionBase *mpCurrentFunction; // +0x30
    char debug[12];
    AptConstantPool constantPool; // +0x40
    char pad48[0x60 - 0x48];
    int unwind; // +0x60

    const unsigned char *runStream(const unsigned char *, AptCIH *, int,
                                   struct AptCharacterInst *);
    AptValue *getVariable(AptValue *, AptValue *, const EAStringC *, int=1, int=1, int=0);
    void callFunction(AptValue *, AptValue *, int);
private:
    static AptValue *getObject(AptValue *, AptValue *, const EAStringC *);
    AptObject *_createObject(AptValue *, AptValue *, const EAStringC *, int, bool);
};

// Retail's 20-byte local frame holds the pre-call stack count and this
// 16-byte workspace. Its pool result and execution state occupy the same
// eight bytes at non-overlapping times, below the saved constant pool.
// Explicit trivial-object lifetimes preserve that storage reuse with MSVC
// 7.1; independent locals reverse the two areas in otherwise identical code.
// This workspace is a reconstruction aid, not a claimed original type.
struct AptInterpreterCallFrame
{
    union {
        AptConstantPool pool;
        _AptScriptFunctionState state;
    } scratch;
    AptConstantPool savedPool;
};
typedef char AptInterpreterCallFrameSize[sizeof(AptInterpreterCallFrame) == 16 ? 1 : -1];

// ?callFunction@AptActionInterpreter@@QAEXPAVAptValue@@0H@Z
// Native RVA 0x00706660..0x00706946: all 742 bytes including RET 12.
// Original Redwood6 PDB/MAP establishes the three-argument method ABI;
// WB 0x0175EA50 corroborates dispatch, argument setup and cleanup order.
// Continues the banked reconstruction in reverse/re_attempts.log. Uses the
// canonical ScriptFunction layout and the existing providers' signatures;
// AL truncation matches the retail predicate tests without new symbol pins.
void AptActionInterpreter::callFunction(AptValue *context, AptValue *function, int nParams)
{
    int nStackElementsPre = stack.count - nParams;
    if (function && (unsigned char)((BfmeAptValue006DCD20 *)function)->isNativeFunction()) {
        AptInterpreterCallFrame nativeFrame;
        nativeFrame.savedPool = constantPool;
        stack.PopAndPush(nParams, (BfmeAptValue006DCD20 *)
            ((BfmeAptNativeFunctionView *)((BfmeAptValue006DCD20 *)function)->rva006DCF20())->function(context, nParams));
        constantPool = nativeFrame.savedPool;
    } else if (function && (unsigned char)((BfmeAptValue006DCD20 *)function)->isScriptFunction()) {
        AptInterpreterCallFrame frame;
        frame.savedPool = constantPool;
        AptScriptFunctionBase *pPrevFunction = mpCurrentFunction;
        mpCurrentFunction = (AptScriptFunctionBase *)((BfmeAptValue006DCD20 *)function)->rva006DCEE0();
        constantPool = *new (&frame.scratch.pool) AptConstantPool(mpCurrentFunction->GetConstantPool());
        if (((BfmeAptValue006DCD20 *)mpCurrentFunction->mpCIH)->isUndefined()
            || ((unsigned char)((BfmeAptValue006DCD20 *)mpCurrentFunction->mpCIH)->rva006E03A0()
                && (mpCurrentFunction->mpCIH->state & 0xC0000) == 0)
            || ((unsigned char)((BfmeAptValue006DCD20 *)mpCurrentFunction->mpCIH)->rva006E03A0()
                && (mpCurrentFunction->mpCIH->state & 0xC0000) == 0x80000)) {
            stack.rva006E3AA0(nParams);
            stack.rva006FDF30((BfmeAptValue006DCD20 *)gpUndefinedValue);
            mpCurrentFunction->mpCIH = (AptCIH *)gpUndefinedValue;
        } else {
            thisStack.push(context);
            mpCurrentFunction->AddRef();
            // The temporary pool has been copied; begin the execution-state
            // lifetime in its storage. Both union members are trivial.
            new (&frame.scratch.state) _AptScriptFunctionState;
            mpCurrentFunction->SetupBeforeExecution(&frame.scratch.state, context);
            int nFormalArgs = mpCurrentFunction->GetNumArguments();
            int nArgs = nFormalArgs < nParams ? nFormalArgs : nParams;
            int i;
            for (i = 0; i < nArgs; ++i) {
                AptValue *param = (AptValue *)stack.At(i);
                mpCurrentFunction->SetArgument(param, i);
            }
            for (; i < nFormalArgs; ++i)
                mpCurrentFunction->SetArgument(gpUndefinedValue, i);
            stack.rva006E3AA0(nParams);
            const AptCIH *root = mpCurrentFunction->mpParentAnim->rva006E0CB0();
            AptCharacterInst *character = root ? (AptCharacterInst *)((Rva006CD650 *)root)->rva006CD650() : 0;
            runStream(mpCurrentFunction->GetByteCodeBase(), mpCurrentFunction->mpCIH,
                      mpCurrentFunction->GetByteCodeSize(), character);
            mpCurrentFunction->CleanupAfterExecution(&frame.scratch.state);
            mpCurrentFunction->Release();
            thisStack.popInline();
        }
        mpCurrentFunction = pPrevFunction;
        constantPool = frame.savedPool;
    } else {
        stack.rva006E3AA0(nParams);
        stack.PushNoInc(gpUndefinedValue);
    }
    int nStackElementsPost = stack.count;
    if (unwind) {
        if (nStackElementsPost > nStackElementsPre)
            stack.rva006E3AA0(nStackElementsPost - nStackElementsPre);
    } else {
        APT_ASSERT(nStackElementsPost == nStackElementsPre || nStackElementsPost == nStackElementsPre + 1,
                   "nStackElementsPost == nStackElementsPre || nStackElementsPost == (nStackElementsPre+1)",
                   APT_INTERP_CPP, 0x837)
    }
}

// Apt object factory. Structure from WB 0x175F230 (3750B) and retail
// 0x00706A40 (2496B): type-name if/else chain over
// Sound/Array/String/Date/TextFormat/Color/MovieClip/XML/LoadVars/Error, then
// the shared prototype/hash/with-stack tail. Classes and call names follow the
// rowed Apt views in AptActionInterpreterConstantHandlers.cpp.
extern "C" double __cdecl fmod(double,double);
#pragma intrinsic(fmod)
static __forceinline float bfme_fmodf(float x,float y) { return (float)fmod(x,y); }
class BfmeN1034;
class Rva8D0D80Value;
class Rva006D2A60 { public: void *allocBlock(int); void freeBlock(void *,int); };
class Rva006DB160 { public: void *allocBlock(int); };
class Rva006DB270 { public: void freeBlock(void *,int); };
extern Rva006DB270 *g_pChainBlockAllocator;
extern Rva006D2A60 *g_pChainBlockAllocatorF4;
extern AptValue *gpGlobalGlobalObject;

class AptArray
{
    char m_storage[0x2c];
public:
    static void *operator new(unsigned int n) { return g_pChainBlockAllocatorF4->allocBlock(n); }
    static void operator delete(void *p,unsigned int n) { g_pChainBlockAllocatorF4->freeBlock(p,n); }
    AptArray();
    void set(int,AptValue *);
    AptValue *get(int);
};

class AptString : public AptValue
{
public:
    static AptString *Create();
    EAStringC str;
};

class Rva006FBDB0 : public EAStringC
{
public:
    Rva006FBDB0(EAStringC,int,int);
    static void *operator new(unsigned int n) { return ((Rva006DB160 *)g_pChainBlockAllocator)->allocBlock(n); }
    static void operator delete(void *p,unsigned int n) { g_pChainBlockAllocator->freeBlock(p,n); }
    int context,action;
};

template<class T> struct AptDebugStack
{
    void Rva006FE2F0(void *);
};

class Rva00706330Stack { public: void rva00706330(); };

class AptPrototype : public AptValueWithHash
{
    AptValue *mp__constructor__;
public:
    AptPrototype();
    static void *operator new(unsigned int n) { return g_pChainBlockAllocatorF4->allocBlock(n); }
    static void operator delete(void *p,unsigned int n) { g_pChainBlockAllocatorF4->freeBlock(p,n); }
};

class AptStringObject
{
    char m_storage[0x24];
public:
    static void *operator new(unsigned int n) { return g_pChainBlockAllocatorF4->allocBlock(n); }
    static void operator delete(void *p,unsigned int n) { g_pChainBlockAllocatorF4->freeBlock(p,n); }
    AptStringObject(AptString *);
};

class AptSound
{
    char m_storage[0x2c];
public:
    static void *operator new(unsigned int n) { return g_pChainBlockAllocatorF4->allocBlock(n); }
    static void operator delete(void *p,unsigned int n) { g_pChainBlockAllocatorF4->freeBlock(p,n); }
    AptSound(AptCIH *);
};

class AptScriptColour
{
    char m_storage[0x24];
public:
    static void *operator new(unsigned int n) { return g_pChainBlockAllocatorF4->allocBlock(n); }
    static void operator delete(void *p,unsigned int n) { g_pChainBlockAllocatorF4->freeBlock(p,n); }
    AptScriptColour(AptValue *const);
};

class AptError
{
    char m_storage[0x28];
public:
    static void *operator new(unsigned int n) { return g_pChainBlockAllocatorF4->allocBlock(n); }
    static void operator delete(void *p,unsigned int n) { g_pChainBlockAllocatorF4->freeBlock(p,n); }
    AptError(EAStringC);
};

class Rva006FBF90
{
    char m_storage[0x64];
public:
    static void *operator new(unsigned int n) { return g_pChainBlockAllocatorF4->allocBlock(n); }
    static void operator delete(void *p,unsigned int n) { g_pChainBlockAllocatorF4->freeBlock(p,n); }
    Rva006FBF90(int,int,int,int,int,int,int);
};
class Rva006FC130
{
    char m_storage[0x20];
public:
    static void *operator new(unsigned int n) { return g_pChainBlockAllocatorF4->allocBlock(n); }
    static void operator delete(void *p,unsigned int n) { g_pChainBlockAllocatorF4->freeBlock(p,n); }
    Rva006FC130();
};
class Rva006FC1D0
{
    char m_storage[0x24];
public:
    static void *operator new(unsigned int n) { return g_pChainBlockAllocatorF4->allocBlock(n); }
    static void operator delete(void *p,unsigned int n) { g_pChainBlockAllocatorF4->freeBlock(p,n); }
    Rva006FC1D0();
};
class Rva006FC240
{
    char m_storage[0x28];
public:
    static void *operator new(unsigned int n) { return g_pChainBlockAllocatorF4->allocBlock(n); }
    static void operator delete(void *p,unsigned int n) { g_pChainBlockAllocatorF4->freeBlock(p,n); }
    Rva006FC240();
};
class Rva006F1E70
{
    char m_storage[0x28];
public:
    static void *operator new(unsigned int n) { return g_pChainBlockAllocatorF4->allocBlock(n); }
    static void operator delete(void *p,unsigned int n) { g_pChainBlockAllocatorF4->freeBlock(p,n); }
    Rva006F1E70(BfmeAptValue006DCD20 *);
};
class Rva006ECFC0Owner
{
    char m_storage[0x40];
public:
    static void *operator new(unsigned int n) { return g_pChainBlockAllocatorF4->allocBlock(n); }
    static void operator delete(void *p,unsigned int n) { g_pChainBlockAllocatorF4->freeBlock(p,n); }

    Rva006ECFC0Owner(AptValue*,float,int,int,int,int,int,int,AptValue*,int,int,int,int);
};
class Rva006D6470Owner
{
    char m_storage[0x20];
public:
    static void *operator new(unsigned int n) { return g_pChainBlockAllocatorF4->allocBlock(n); }
    static void operator delete(void *p,unsigned int n) { g_pChainBlockAllocatorF4->freeBlock(p,n); }
    Rva006D6470Owner(int,int);
};
class Rva0070A5C0 { public: BfmeN1034 *rva0070A5C0(int); };
class Rva0070DFF0 { public: void rva0070DFF0(Rva8D0D80Value *, unsigned char); };
class Rva0070E060 { public: BfmeAptValue006DCD20 *rva0070E060(int *); };
EAStringC *Rva0070B4F0GetString(int);

#define TICK_ASSERT(good, test, line) do { \
    if (!(good)) { \
        g_bfmeAptAssertAtE17734(test, \
            "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptActionInterpreter.cpp", line); \
        if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak(); } } while (0)

// ?_createObject@AptActionInterpreter@@AAEPAVAptObject@@PAVAptValue@@0PBVEAStringC@@H_N@Z
AptObject *AptActionInterpreter::_createObject(AptValue *context, AptValue *with,
    const EAStringC *name, int nParams, bool runConstructor)
{
    AptValue *created = 0;
    AptValue *def = getVariable(context, with, name, 1, 1, 0);
    BfmeAptValue006DCD20 *defVal = (BfmeAptValue006DCD20 *)def;
    if (!defVal->isUndefined() && defVal->rva006DCA60())
    {
        if (name->rva006D3510("Sound"))
        {
            AptSound *p = new AptSound((AptCIH *)((BfmeAptValue006DCD20 *)context)->rva006DCF60(false));
            created = (AptValue *)p;
        }
        else if (name->rva006D3510("Array"))
        {
            AptArray *a = new AptArray();
            if (nParams == 1)
            {
                if (((unsigned char)((BfmeAptValue006DCD20 *)stack.rva006FE580(0))->isInteger() && ((BfmeAptValue006DCD20 *)stack.rva006FE580(0))->toInteger() >= 0) ||
                    ((unsigned char)((BfmeAptValue006DCD20 *)stack.rva006FE580(0))->isFloat() && bfme_fmodf(((BfmeAptValue006DCD20 *)stack.rva006FE580(0))->rva006DD460(), 1.0f) == 0.0f))
                {
                    int n = ((BfmeAptValue006DCD20 *)stack.rva006FE580(0))->toInteger();
                    TICK_ASSERT(n >= 0, "nElements >= 0", 0x925);
                    a->set(n - 1, gpUndefinedValue);
                    created = (AptValue *)a;
                    goto done;
                }
            }
            for (int i = 0; i < nParams; ++i)
                a->set(i, stack.rva006FE580(i));
            created = (AptValue *)a;
        }
        else if (name->rva006D3510("String"))
        {
            EAStringC text;
            AptString *str = AptString::Create();
            if (nParams == 1)
                ((AptValue *)stack.rva006FE580(0))->toString(text);
            str->str = text;
            def = (AptValue *)((Rva0070A5C0 *)gpGlobalGlobalObject)->rva0070A5C0((int)Rva0070B4F0GetString(0x9d));
            AptStringObject *obj = new AptStringObject(str);
            created = (AptValue *)obj;
        }
        else if (name->rva006D3510("Date"))
        {
            Rva006FBF90 *d = new Rva006FBF90(
                (nParams > 0) ? ((BfmeAptValue006DCD20 *)stack.rva006FE580(0))->toInteger() : -1,
                (nParams > 1) ? ((BfmeAptValue006DCD20 *)stack.rva006FE580(1))->toInteger() : -1,
                (nParams > 2) ? ((BfmeAptValue006DCD20 *)stack.rva006FE580(2))->toInteger() : -1,
                (nParams > 3) ? ((BfmeAptValue006DCD20 *)stack.rva006FE580(3))->toInteger() : -1,
                (nParams > 4) ? ((BfmeAptValue006DCD20 *)stack.rva006FE580(4))->toInteger() : -1,
                (nParams > 5) ? ((BfmeAptValue006DCD20 *)stack.rva006FE580(5))->toInteger() : -1,
                (nParams > 6) ? ((BfmeAptValue006DCD20 *)stack.rva006FE580(6))->toInteger() : -1);
            created = (AptValue *)d;
        }
        else if (name->rva006D3510("TextFormat"))
        {
            const int defaultZero = 0;
            const int defaultUnspecified = -1;
            Rva006ECFC0Owner *t = new Rva006ECFC0Owner(
                (nParams > 0) ? stack.rva006FE580(0) : gpUndefinedValue,
                (nParams > 1) ? ((BfmeAptValue006DCD20 *)stack.rva006FE580(1))->rva006DD460() : -1.0f,
                (nParams > 2) ? ((BfmeAptValue006DCD20 *)stack.rva006FE580(2))->toInteger() : defaultUnspecified,
                (nParams > 3) ? ((BfmeAptValue006DCD20 *)stack.rva006FE580(3))->toInteger() : defaultUnspecified,
                (nParams > 4) ? ((BfmeAptValue006DCD20 *)stack.rva006FE580(4))->toInteger() : defaultUnspecified,
                (nParams > 5) ? ((BfmeAptValue006DCD20 *)stack.rva006FE580(5))->toInteger() : defaultUnspecified,
                (nParams > 6) ? ((BfmeAptValue006DCD20 *)stack.rva006FE580(6))->toInteger() : defaultZero,
                (nParams > 7) ? ((BfmeAptValue006DCD20 *)stack.rva006FE580(7))->toInteger() : defaultZero,
                (nParams > 8) ? stack.rva006FE580(8) : gpUndefinedValue,
                (nParams > 9) ? ((BfmeAptValue006DCD20 *)stack.rva006FE580(9))->toInteger() : defaultUnspecified,
                (nParams > 0xa) ? ((BfmeAptValue006DCD20 *)stack.rva006FE580(0xa))->toInteger() : defaultUnspecified,
                (nParams > 0xb) ? ((BfmeAptValue006DCD20 *)stack.rva006FE580(0xb))->toInteger() : defaultUnspecified,
                (nParams > 0xc) ? ((BfmeAptValue006DCD20 *)stack.rva006FE580(0xc))->toInteger() : defaultUnspecified);
            created = (AptValue *)t;
        }
        else if (name->rva006D3510("Color"))
        {
            BfmeAptValue006DCD20 *arg = (BfmeAptValue006DCD20 *)stack.rva006FE580(0);
            if ((unsigned char)arg->isString())
            {
                EAStringC *s = (EAStringC *)((char *)arg->checkedString() + 8);
                AptValue *colour = getObject(context, 0, s);
                created = (AptValue *)new AptScriptColour(colour);
            }
            else
                created = (AptValue *)new AptScriptColour((AptValue *)arg);
        }
        else if (name->rva006D3510("MovieClip"))
        {
            Rva006FC130 *m = new Rva006FC130();
            created = (AptValue *)m;
        }
        else if (name->rva006D3510("XML"))
        {
            if (nParams == 1)
                created = (AptValue *)new Rva006F1E70((BfmeAptValue006DCD20 *)stack.rva006FE580(0));
            else
                created = (AptValue *)new Rva006F1E70(0);
        }
        else if (name->rva006D3510("LoadVars"))
        {
            Rva006FC1D0 *l = new Rva006FC1D0();
            created = (AptValue *)l;
        }
        else if (name->rva006D3510("Error"))
        {
            if (nParams == 1)
            {
                {
                EAStringC text;
                ((AptValue *)stack.rva006FE580(0))->toString(text);
                AptError *e = new AptError(text);
                created = (AptValue *)e;
                }
            }
            else
            {
                Rva006FC240 *e = new Rva006FC240();
                created = (AptValue *)e;
            }
        }
        else
        {
            Rva006D6470Owner *p = new Rva006D6470Owner(0x1b, 8);
            created = (AptValue *)p;
        }

    done:
        created->AddRef();
        AptNativeHash *hash = def->GetNativeHashVirtual();
        AptValue *proto = hash->mpPrototype;
        if (proto == 0)
        {
            AptPrototype *p = new AptPrototype();
            AptValue *old = *(AptValue **)((char *)p + 0x1c);
            *(AptValue **)((char *)p + 0x1c) = def;
            def->AddRef();
            if (old)
                old->Release();
            p->AddRef();
            if (hash->mpPrototype)
                hash->mpPrototype->Release();
            hash->mpPrototype = p;
            proto = p;
        }
        created->setHasClass(1);
        *(int *)((char *)created + 0x1c) |= 0x200;
        if (proto)
            proto->AddRef();
        if (*(AptValue **)((char *)created + 0x10))
            (*(AptValue **)((char *)created + 0x10))->Release();
        *(AptValue **)((char *)created + 0x10) = proto;

        if ((unsigned char)((BfmeAptValue006DCD20 *)def)->isObject() ||
            (unsigned char)((BfmeAptValue006DCD20 *)def)->isScriptFunction())
        {
            int nValues;
            BfmeAptValue006DCD20 *values = ((Rva0070E060 *)def)->rva0070E060(&nValues);
            if (nValues > 0)
                ((Rva0070DFF0 *)created)->rva0070DFF0((Rva8D0D80Value *)values, (unsigned char)nValues);
        }

        if (runConstructor)
        {
            AptValuePtrStack<AptValue> *ctorStack = (AptValuePtrStack<AptValue> *)((char *)this + 0x24);
            ctorStack->push(created);
            Rva006FBDB0 *info = new Rva006FBDB0(EAStringC(name->rva00620090()), (int)created, 0x10000000);
            ((AptDebugStack<DebugCallStackInfo_t> *)((char *)this + 0x34))->Rva006FE2F0(info);
            this->callFunction(created, def, nParams);
            this->stack.rva006FE920();
            ctorStack->pop();
            ((Rva00706330Stack *)((char *)this + 0x34))->rva00706330();
        }

        *(int *)((char *)created + 0x1c) &= ~0x200;
    }
    else
        stack.rva006FE050(nParams);
    return (AptObject *)created;
}

// Retail retains the created value and looked-up definition separately.
// Constructor execution is guarded by the fifth formal argument.

// Each pool new expression retains its constructor-failure sized delete.
