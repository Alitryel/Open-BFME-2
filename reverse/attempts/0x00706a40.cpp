// ?_createObject@AptActionInterpreter@@AAEPAVAptObject@@PAVAptValue@@0PBVEAStringC@@H_N@Z
// partial score=0.42 date=2026-10-17
// ?_createObject@AptActionInterpreter@@AAEPAVAptObject@@PAVAptValue@@0PBVEAStringC@@H_N@Z
// partial score=0.59 date=2026-10-14
// ?_createObject@AptActionInterpreter@@AAEPAVAptObject@@PAVAptValue@@0PBVEAStringC@@H_N@Z
// partial score=0.59 date=2026-10-14
// ?_createObject@AptActionInterpreter@@AAEPAVAptObject@@PAVAptValue@@0PBVEAStringC@@H_N@Z
// partial score=0.59 date=2026-10-14
// Bank draft of the Apt object factory. Structure from WB 0x175F230 (3750B,
// 1.5x) and retail 0x00706A40 (2493B): type-name if/else chain over
// Sound/Array/String/Date/TextFormat/Color/MovieClip/XML/LoadVars/Error, then
// the shared prototype/hash/with-stack tail. Classes and call names follow the
// rowed Apt views in AptActionInterpreterConstantHandlers.cpp.
// cl: /O2 /MD /EHsc
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
#include <new>
extern "C" double __cdecl fmod(double,double);
#pragma intrinsic(fmod)
static __forceinline float bfme_fmodf(float x,float y) { return (float)fmod(x,y); }

class EAStringC;
class AptString;
class AptArray;
class AptNativeHash;
class AptCIH;
class AptObject;
class BfmeAptValue006DCD20;
class AptStringObject;
class AptSound;
class AptScriptColour;
class AptError;
class Rva006FBF90;
class Rva006FC130;
class Rva006FC1D0;
class Rva006FC240;
class Rva006F1E70;
class Rva006ECFC0Owner;
class Rva0070A5C0;
class Rva0070DFF0;
class Rva0070E060;
class Rva8D0D80Value;
class BfmeN1034;

class AptValue
{
    unsigned int m_valueFlags;
public:
    virtual void AddRef();
    virtual void Release();
    virtual void ForceDelete();
    virtual AptNativeHash *GetNativeHashVirtual();
    virtual bool ContainsNativeHashVirtual() const;
    virtual int getHasClass() const;
    virtual void setHasClass(int);
    bool isObject() const;
    bool isScriptFunction() const;
    bool isUndefined() const;
    bool isInteger() const;
    bool isFloat() const;
    bool isString() const;
    int toInteger() const;
    void toString(EAStringC &) const;
};

class EAStringC
{
    void *mpData;
public:
    bool rva006D3510(const char *) const;
    const char *rva00620090() const;
    EAStringC();
    EAStringC(const char *);
    EAStringC(const EAStringC &);
    ~EAStringC();
    EAStringC &operator=(const EAStringC &);
    EAStringC &clear();
};

class BfmeAptValue006DCD20
{
public:
    BfmeAptValue006DCD20 *rva006DCF60(bool);
    bool rva006DCA60() const;
    bool isUndefined() const;
    int isInteger() const;
    int isFloat() const;
    int isString() const;
    int isObject() const;
    int isScriptFunction() const;
    int toInteger() const;
    float rva006DD460();
    BfmeAptValue006DCD20 *checkedString();
};

class Rva006D2A60 { public: void *allocBlock(int); void freeBlock(void *,int); };
extern Rva006D2A60 *g_pChainBlockAllocatorF4;
extern AptValue *g_bfmeAptDefaultValueAtE18078;
extern void *g_e18650;

class AptArray : public AptValue
{
    char m_arrayState[32];
public:
    int mnCount;
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

class AptBasePtrStack
{
public:
    void rva006FE050(int);
    void rva006FE920();
    AptValue *rva006FE580(int);
    int count,capacity;
    AptValue **items;
};

template<class T> struct AptValuePtrStack
{
    int count,capacity; T **items;
    void push(T *);
    T *top();
    T *at(int);
    void pop();
};

class Rva006FBDB0 : public EAStringC
{
public:
    Rva006FBDB0(EAStringC,int,int);
    static void *operator new(unsigned int n) { return ((Rva006D2A60 *)g_pChainBlockAllocatorF4)->allocBlock(n); }
    int context,action;
};

struct DebugCallStackInfo_t;
template<class T> struct AptDebugStack
{
    void Rva006FE2F0(void *);
};

class Rva00706330Stack { public: void rva00706330(); };

class AptNativeHash
{
public:
    void Set(const EAStringC *const,AptValue *const);
    int mnTotalSize;
    void *mpData;
    AptValue *mp__proto__;
    AptValue *mpPrototype;
};

class AptPrototype : public AptValue
{
    AptNativeHash mNativeHash;
    AptValue *mp__constructor__;
public:
    AptPrototype();
    static void *operator new(unsigned int n) { return g_pChainBlockAllocatorF4->allocBlock(n); }
};

class AptStringObject
{
public:
    AptStringObject(AptString *);
};

class AptSound
{
public:
    AptSound(AptCIH *);
};

class AptScriptColour
{
public:
    AptScriptColour(AptValue *const);
};

class AptError
{
public:
    AptError(EAStringC);
};

class Rva006FBF90 { public: Rva006FBF90(int,int,int,int,int,int,int); };
class Rva006FC130 { public: Rva006FC130(); };
class Rva006FC1D0 { public: Rva006FC1D0(); };
class Rva006FC240 { public: Rva006FC240(); };
class Rva006F1E70 { public: Rva006F1E70(BfmeAptValue006DCD20 *); };
class Rva006ECFC0Owner
{
public:
    Rva006ECFC0Owner(AptValue*,float,int,int,int,int,int,int,AptValue*,int,int,int,int);
};
class Rva006D6470Owner { public: Rva006D6470Owner(int,int); };
class Rva0070A5C0 { public: void *rva0070A5C0(void *); };
class Rva0070DFF0 { public: void rva0070DFF0(Rva8D0D80Value *, unsigned char); };
class Rva0070E060 { public: BfmeAptValue006DCD20 *rva0070E060(int *); };
EAStringC *Rva0070B4F0GetString(int);

extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;

struct AptActionInterpreter
{
    AptBasePtrStack stack;					// +0x00
    AptValuePtrStack<AptValue> withStack;			// +0x0c
    unsigned char m_betweenWithAndThis[0x24-0x18];
    AptValuePtrStack<AptValue> thisStack;			// +0x24
    void *mpCurrentFunction;					// +0x30
    AptDebugStack<DebugCallStackInfo_t> debugCallStack;	// +0x34
    AptValue *getVariable(AptValue *, AptValue *, const EAStringC *, int=1, int=1, int=0);
    void callFunction(AptValue *, AptValue *, int);
private:
    static AptValue *getObject(AptValue *, AptValue *, const EAStringC *);
    AptObject *_createObject(AptValue *, AptValue *, const EAStringC *, int, bool);
};

#define TICK_ASSERT(good, test, line) do { \
    if (!(good)) { \
        g_bfmeAptAssertAtE17734(test, \
            "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptActionInterpreter.cpp", line); \
        if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak(); } } while (0)

AptObject *AptActionInterpreter::_createObject(AptValue *context, AptValue *with,
    const EAStringC *name, int nParams, bool runConstructor)
{
    _ReadWriteBarrier();
    _ReadWriteBarrier();
    AptValue *def = getVariable(context, with, name, 1, 1, 0);
    BfmeAptValue006DCD20 *defVal = (BfmeAptValue006DCD20 *)def;
    bool isUndef = defVal->isUndefined();
    if (isUndef ||
        !defVal->rva006DCA60())
    {
        stack.rva006FE050(nParams);
        return 0;
    }

    AptValue *created = 0;
    AptValue *createdObj = 0;

    if (name->rva006D3510("Sound"))
    {
        AptSound *p = (AptSound *)g_pChainBlockAllocatorF4->allocBlock(0x2c);
        if (p)
            p = new (p) AptSound((AptCIH *)((BfmeAptValue006DCD20 *)context)->rva006DCF60(false));
        created = (AptValue *)p;
    }
    else if (name->rva006D3510("Array"))
    {
        AptArray *a = (AptArray *)g_pChainBlockAllocatorF4->allocBlock(0x2c);
        if (a)
            a = new (a) AptArray();
        if (nParams == 1)
        {
            BfmeAptValue006DCD20 *p0 = (BfmeAptValue006DCD20 *)stack.rva006FE580(0);
            if ((p0->isInteger() && p0->toInteger() >= 0) ||
                (p0->isFloat() && bfme_fmodf(p0->rva006DD460(), 1.0f) == 0.0f))
            {
                int n = p0->toInteger();
                TICK_ASSERT(n >= 0, "nElements >= 0", 0x925);
                a->set(n - 1, g_bfmeAptDefaultValueAtE18078);
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
        text.clear();
        AptString *str = AptString::Create();
        if (nParams == 1)
            ((AptValue *)stack.rva006FE580(0))->toString(text);
        str->str = text;
        ((Rva0070A5C0 *)g_e18650)->rva0070A5C0(Rva0070B4F0GetString(0x9d));
        AptStringObject *obj = (AptStringObject *)g_pChainBlockAllocatorF4->allocBlock(0x24);
        if (obj)
            obj = new (obj) AptStringObject(str);
        created = (AptValue *)obj;
    }
    else if (name->rva006D3510("Date"))
    {
        Rva006FBF90 *d = (Rva006FBF90 *)g_pChainBlockAllocatorF4->allocBlock(0x64);
        if (d)
        {
            int a6 = (nParams > 6) ? ((BfmeAptValue006DCD20 *)stack.rva006FE580(6))->toInteger() : -1;
            int a5 = (nParams > 5) ? ((BfmeAptValue006DCD20 *)stack.rva006FE580(5))->toInteger() : -1;
            int a4 = (nParams > 4) ? ((BfmeAptValue006DCD20 *)stack.rva006FE580(4))->toInteger() : -1;
            int a3 = (nParams > 3) ? ((BfmeAptValue006DCD20 *)stack.rva006FE580(3))->toInteger() : -1;
            int a2 = (nParams > 2) ? ((BfmeAptValue006DCD20 *)stack.rva006FE580(2))->toInteger() : -1;
            int a1 = (nParams > 1) ? ((BfmeAptValue006DCD20 *)stack.rva006FE580(1))->toInteger() : -1;
            int a0 = (nParams > 0) ? ((BfmeAptValue006DCD20 *)stack.rva006FE580(0))->toInteger() : -1;
            d = new (d) Rva006FBF90(a0, a1, a2, a3, a4, a5, a6);
        }
        created = (AptValue *)d;
    }
    else if (name->rva006D3510("TextFormat"))
    {
        Rva006ECFC0Owner *t = (Rva006ECFC0Owner *)g_pChainBlockAllocatorF4->allocBlock(0x40);
        if (t)
        {
            int i12 = (nParams > 0xc) ? ((BfmeAptValue006DCD20 *)stack.rva006FE580(0xc))->toInteger() : -1;
            int i11 = (nParams > 0xb) ? ((BfmeAptValue006DCD20 *)stack.rva006FE580(0xb))->toInteger() : -1;
            int i10 = (nParams > 0xa) ? ((BfmeAptValue006DCD20 *)stack.rva006FE580(0xa))->toInteger() : -1;
            int i9 = (nParams > 9) ? ((BfmeAptValue006DCD20 *)stack.rva006FE580(9))->toInteger() : -1;
            AptValue *p8 = (nParams > 8) ? stack.rva006FE580(8) : g_bfmeAptDefaultValueAtE18078;
            int i7 = (nParams > 7) ? ((BfmeAptValue006DCD20 *)stack.rva006FE580(7))->toInteger() : 0;
            int i6 = (nParams > 6) ? ((BfmeAptValue006DCD20 *)stack.rva006FE580(6))->toInteger() : 0;
            int i5 = (nParams > 5) ? ((BfmeAptValue006DCD20 *)stack.rva006FE580(5))->toInteger() : -1;
            int i4 = (nParams > 4) ? ((BfmeAptValue006DCD20 *)stack.rva006FE580(4))->toInteger() : -1;
            int i3 = (nParams > 3) ? ((BfmeAptValue006DCD20 *)stack.rva006FE580(3))->toInteger() : -1;
            int i2 = (nParams > 2) ? ((BfmeAptValue006DCD20 *)stack.rva006FE580(2))->toInteger() : -1;
            float f1 = (nParams > 1) ? ((BfmeAptValue006DCD20 *)stack.rva006FE580(1))->rva006DD460() : -1.0f;
            AptValue *p0 = (nParams > 0) ? stack.rva006FE580(0) : g_bfmeAptDefaultValueAtE18078;
            t = new (t) Rva006ECFC0Owner(p0, f1, i2, i3, i4, i5, i6, i7, p8, i9, i10, i11, i12);
        }
        created = (AptValue *)t;
    }
    else if (name->rva006D3510("Color"))
    {
        BfmeAptValue006DCD20 *arg = (BfmeAptValue006DCD20 *)stack.rva006FE580(0);
        AptValue *colour = (AptValue *)arg;
        if (arg->isString())
        {
            EAStringC *s = (EAStringC *)((char *)arg->checkedString() + 8);
            colour = getObject(context, with, s);
        }
        AptScriptColour *c = (AptScriptColour *)g_pChainBlockAllocatorF4->allocBlock(0x24);
        if (c)
            c = new (c) AptScriptColour(colour);
        created = (AptValue *)c;
    }
    else if (name->rva006D3510("MovieClip"))
    {
        Rva006FC130 *m = (Rva006FC130 *)g_pChainBlockAllocatorF4->allocBlock(0x20);
        if (m)
            m = new (m) Rva006FC130();
        created = (AptValue *)m;
    }
    else if (name->rva006D3510("XML"))
    {
        Rva006F1E70 *x = (Rva006F1E70 *)g_pChainBlockAllocatorF4->allocBlock(0x28);
        if (x)
        {
            if (nParams == 1)
                x = new (x) Rva006F1E70((BfmeAptValue006DCD20 *)stack.rva006FE580(0));
            else
                x = new (x) Rva006F1E70(0);
        }
        created = (AptValue *)x;
    }
    else if (name->rva006D3510("LoadVars"))
    {
        Rva006FC1D0 *l = (Rva006FC1D0 *)g_pChainBlockAllocatorF4->allocBlock(0x24);
        if (l)
            l = new (l) Rva006FC1D0();
        created = (AptValue *)l;
    }
    else if (name->rva006D3510("Error"))
    {
        if (nParams == 1)
        {
            {
            EAStringC text;
            text.clear();
            ((AptValue *)stack.rva006FE580(0))->toString(text);
            AptError *e = (AptError *)g_pChainBlockAllocatorF4->allocBlock(0x28);
            if (e)
                e = new (e) AptError(text);
            created = (AptValue *)e;
            }
        }
        else
        {
            Rva006FC240 *e = (Rva006FC240 *)g_pChainBlockAllocatorF4->allocBlock(0x28);
            if (e)
                e = new (e) Rva006FC240();
            created = (AptValue *)e;
        }
    }
    else
    {
        Rva006D6470Owner *p = (Rva006D6470Owner *)g_pChainBlockAllocatorF4->allocBlock(0x20);
        if (p)
            p = new (p) Rva006D6470Owner(8, 0x1b);
        created = (AptValue *)p;
    }

done:
    created = createdObj;
    AptNativeHash *hash = ((AptValue *)with)->GetNativeHashVirtual();
    AptValue *proto = hash->mpPrototype;
    created->AddRef();
    if (proto == 0)
    {
        AptPrototype *p = (AptPrototype *)g_pChainBlockAllocatorF4->allocBlock(0x20);
        if (p)
            p = ::new (p) AptPrototype();
        AptValue *old = *(AptValue **)((char *)p + 0x1c);
        *(AptValue **)((char *)p + 0x1c) = with;
        with->AddRef();
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

    if (with->isObject() || with->isScriptFunction())
    {
        int nValues = 0;
        BfmeAptValue006DCD20 *values = ((Rva0070E060 *)with)->rva0070E060(&nValues);
        if (nValues > 0)
            ((Rva0070DFF0 *)created)->rva0070DFF0((Rva8D0D80Value *)values, (unsigned char)nValues);
    }

    if ((runConstructor ? true : true))
    {
        AptActionInterpreter *self = (1 ? this : this);
        AptValuePtrStack<AptValue> *ctorStack = (AptValuePtrStack<AptValue> *)((char *)self + 0x24);
        ctorStack->push(created);
        Rva006FBDB0 *info = (Rva006FBDB0 *)g_pChainBlockAllocatorF4->allocBlock(0xc);
        if (info)
            info = ::new (info) Rva006FBDB0(EAStringC(name->rva00620090()), 0x10000000, 0);
        ((AptDebugStack<DebugCallStackInfo_t> *)((char *)self + 0x34))->Rva006FE2F0(info);
        self->callFunction(created, with, (int)context);
        self->stack.rva006FE920();
        ctorStack->pop();
        ((Rva00706330Stack *)((char *)self + 0x34))->rva00706330();
    }

    *(int *)((char *)created + 0x1c) &= ~0x200;
    return (AptObject *)created;
}
