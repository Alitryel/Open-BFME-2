// cl: /O2 /MD /EHsc
// Split from AptArrayConstructor.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
// AptArray default constructor: target InitArray702860 allocates44B and calls
// 6D91B0. Native ctor103B sets type22, native hash+8, array vtableCEA778,
// capacity+24, pointer+20 and length+28. Existing array accessors independently
// confirm these fields; later AptArray.cpp4416f7dfadc1781e supplies initializer
// order. Original AptValue.h504032fc6593aab6 gives protected value constructors.
// Reuse canonical base layouts. Inline base initializers reproduce the target
// compiler's inlining, including the temporary native-hash-base vtable store.
#include "AptScriptFunction.h"
// ?AptValueGC::AptValueGC present-unmatched
inline AptValueGC::AptValueGC(AptVirtualFunctionTable_Indices type) : AptValue(type) {}
// ?AptValueWithHash::AptValueWithHash present-unmatched
inline AptValueWithHash::AptValueWithHash(AptVirtualFunctionTable_Indices type,int n) : AptValueGC(type),mNativeHash(n) {}
// ?AptObject::AptObject present-unmatched
inline AptObject::AptObject(AptVirtualFunctionTable_Indices type,int n) : AptValueWithHash(type,n)
{
    mnImplementedObjects=0;
    mbHasClass=0;
    mbIsInMainInst=0;
}
class Rva006D2A60 { public: void *allocBlock(int); void freeBlock(void *,int); };
extern Rva006D2A60 *g_pChainBlockAllocatorF4;
extern AptValue *gpUndefinedValue;
class AptArray : public AptObject {
public:
    AptArray();
    void set(int,AptValue*);
    void _reserve(int);
    void toString(EAStringC &,const char * = ",");
    void rva006DA590(char *out,const char *szSeparator);
    void SetAt(int,AptValue*);
    static void *operator new(unsigned int n) { return g_pChainBlockAllocatorF4->allocBlock(n); }
    static AptValue *sMethod_concat(AptValue *,int);
    static AptValue *sMethod_join(AptValue *,int);
    static AptValue *sMethod_pop(AptValue *,int);
    static AptValue *sMethod_push(AptValue *,int);
    static AptValue *sMethod_shift(AptValue *,int);
    static AptValue *sMethod_unshift(AptValue *,int);
    static AptValue *sMethod_reverse(AptValue *,int);
    static AptValue *sMethod_sort(AptValue *,int);
    static AptValue *sMethod_splice(AptValue *,int);
    static AptValue *sMethod_slice(AptValue *,int);
    static AptValue *sMethod_sortOn(AptValue *,int);

    AptValue *At(int);
    AptValue *get(int i) { if(i>=0 && i<mnLength) { AptValue *v=At(i); if(!v) v=gpUndefinedValue; return v; } return gpUndefinedValue; }
    static void operator delete(void *p,unsigned int n) { g_pChainBlockAllocatorF4->freeBlock(p,n); }
    virtual AptValue *objectMemberLookup(AptValue *const,const EAStringC *const) const;
    virtual bool objectMemberSet(AptValue *const,const EAStringC *const,AptValue *const);
    virtual void RegisterReferences() const;
    virtual void DestroyGCPointers();
protected:
    virtual ~AptArray();
private:
    AptValue **mpValues;
    int mnCapacity,mnLength;
};
AptArray::AptArray() : AptObject((AptVirtualFunctionTable_Indices)22)
{
    mnCapacity=0;
    mpValues=0;
    mnLength=0;
}
#pragma comment(linker, "/alternatename:??0AptValue@@IAE@W4AptVirtualFunctionTable_Indices@@@Z=??0BfmeAptValue006DCD20@@QAE@H@Z")
#pragma comment(linker, "/alternatename:??1AptArray@@MAE@XZ=??1Rva006DA560@@UAE@XZ")
#pragma comment(linker, "/alternatename:?GetNativeHashVirtual@AptValueWithHash@@UAEPAUAptNativeHash@@XZ=?GetData@AptValueVector@@QAEPAPAPAVAptValue@@XZ")
#pragma comment(linker, "/alternatename:?ContainsNativeHashVirtual@AptValueWithHash@@UBE_NXZ=?do_always_noconv@?$codecvt@DDH@_STL@@MBE_NXZ")
#pragma comment(linker, "/alternatename:?getHasClass@AptObject@@UBEHXZ=?getBit8@Rva008993E0Owner@@QAEHXZ")
#pragma comment(linker, "/alternatename:?setHasClass@AptObject@@UAEXH@Z=?setBit8@Rva008993E0Owner@@QAEXH@Z")
#pragma comment(linker, "/alternatename:?objectMemberSet@AptArray@@UAE_NQAVAptValue@@QBVEAStringC@@0@Z=?rva006D9780@BfmeAptValue006DCD20@@QAE_NPAV1@PAVEAStringC@@0@Z")
#pragma comment(linker, "/alternatename:?DeleteThis@AptValue@@UAEXXZ=?rva006CBCF0@Rva006CBCF0@@QAEXXZ")
#pragma comment(linker, "/alternatename:?PreDestroy@AptValue@@UAEXXZ=?DX8_Assert@@YAXXZ")
#pragma comment(linker, "/alternatename:?IsGarbageCollected@AptValueGC@@UBE_NXZ=?do_always_noconv@?$codecvt@DDH@_STL@@MBE_NXZ")
#pragma comment(linker, "/alternatename:?RegisterReferences@AptArray@@UBEXXZ=?rva006D94A0@BfmeAptValue006DCD20@@QAEXXZ")
