// ?rva00035540@GeneralAllocator@Allocator@EA@@QAE_NP6A_NPBUBlockInfo@23@PAX@Z1HHHH@Z
// partial score=1.0 date=2026-10-14
// cl: /O2 /GB /Ob2 /MD /EHsc
// Native35540..355DA,154B,RET24; six trailingCC before owned lock355E0.
// PANS snapshot signature and ReportNext-like32F60 bind the allocator family.
// Native callback is cdecl bool(const BlockInfo*,void*), not a virtual object:
// push context / push BlockInfo / call arg1 / add esp8 / consume AL.
// Original method name and four ReportBegin argument types remain unrecovered.
class Rva000353B0 {
public: void *rva00034d10(int,int,int,int);
};
class Rva00033E90 {
public: void freeBlock(void*);
};
struct ReportSnapshot {
    unsigned int magic;
    char unknown04[8];
    bool retained;
    bool inUse;
    char unknown0E[0x20-0x0E];
    unsigned int cursor;
};
namespace EA { namespace Allocator {
struct BlockInfo;
class GeneralAllocator {
public:
    const BlockInfo *rva00032F60(void *,int);
    bool rva00035540(bool (__cdecl *callback)(const BlockInfo*,void*),void *context,int flags,int arg4,int arg5,int arg6);
};
bool GeneralAllocator::rva00035540(bool (__cdecl *callback)(const BlockInfo*,void*),void *context,int flags,int arg4,int arg5,int arg6)
{
    bool result=false;
    if (callback) {
        ReportSnapshot *snapshot=(ReportSnapshot*)((Rva000353B0*)this)->rva00034d10(flags,arg4,arg5,arg6);
        if(snapshot) {
            result=true;
            snapshot->inUse=true;
            const BlockInfo *block=rva00032F60(snapshot,flags);
            while(result && block) {
                result=callback(block,context);
                block=rva00032F60(snapshot,flags);
            }
            if(snapshot->magic==0x534E4150) {
                if(snapshot->inUse) {
                    if(!snapshot->retained)
                        ((Rva00033E90*)this)->freeBlock(snapshot);
                } else snapshot->cursor=0;
            }
        }
    }
    return result;
}
}}
