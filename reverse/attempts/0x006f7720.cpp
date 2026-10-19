// ?rva006F7720Sub@AptAnimationPoolData@@QAEXPAXH@Z
// partial score=0.989 date=2026-10-19
// ?rva006F7720Sub@AptAnimationPoolData@@QAEXPAXH@Z
// partial score=0.779 date=2026-10-17
// ?rva006F7720Sub@AptAnimationPoolData@@QAEXPAXH@Z
// partial score=0.814 date=2026-10-15
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
// ?rva006F7720Sub@AptAnimationPoolData@@QAEXPAXH@Z
// partial score=0.85 date=2026-10-14
// ?rva006F7720Sub@AptAnimationPoolData@@QAEXPAXH@Z
// partial score=0.8 date=2026-10-09
// cl: /DNDEBUG /MD
// Native 6F7720..6F79A3 is 643B through RET8 (served636 extent cuts epilogue).
// Display-list visitor uses the owned112B/395B rendering callbacks, sorted
// 32-entry mask stack (owned7570/7600) and native AptDisplayList assertions.
// Layout and clipping-key comparisons are target evidence, not donor names.
// Flags storage is native .bss at RVA A17718; bit4 chooses clip-stack path.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char*,const char*,int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)
#define DISPLAY_ASSERT(test,text,line) if(!(test)){g_bfmeAptAssertAtE17734(text,"C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptDisplayList.cpp",line);if(g_bfmeAptBreakOnAssertAtDDC01C)__debugbreak();}
extern unsigned int g_bfmeExtra1282Flags;
class BfmeAptValue006DCD20 {public:bool isUndefined()const;};
class Rva006DBB30SarDwordField {public:int get()const;};
struct AptMaskInfo {int unknown00;int clipDepth;};
struct AptDisplayNode {char unknown00[0x4C];AptMaskInfo *info;AptDisplayNode *prev,*next; signed int depth:17;unsigned int flags:15;};
struct Rva006F7570Item;
class Rva006F7600 {
public:
 Rva006F7600():count(0){}
 ~Rva006F7600(){DISPLAY_ASSERT(count==0,"nElements == 0",0x537);}
 void rva006F7570(Rva006F7570Item*);
 void rva006F7600(int);
 AptDisplayNode *get(int i,int cachedCount){DISPLAY_ASSERT(i>=0 && i<cachedCount,"i >= 0 && i < nElements",0x555);return items[i];}
 __forceinline int removeFront(int n){int i=0;DISPLAY_ASSERT(n>0,"i >= 0 && i < nElements",0x54A);for(;i<n-1;++i){items[i]=items[i+1];n=count;}count=--n;return n;}
 AptDisplayNode *items[32];int count;
};
void rva006F7330(void*,void*,int);
void *rva006F73A0(void*,void*,int);
typedef void (__cdecl *AptDisplayVisitor)(void*,void*,int);
struct AptDisplayHead {AptDisplayNode *head;};
class AptAnimationPoolData {public:AptDisplayHead *list;void rva006F7720Sub(void*,int);};
void AptAnimationPoolData::rva006F7720Sub(void *context,int mode)
{
 AptDisplayNode *item=list->head->next;
 Rva006F7600 masks;
 int maskCount=masks.count;
 // Both visitors have the same native three-argument stack ABI; the clip
 // visitor's pointer result is discarded by this type-erased visitor API.
 AptDisplayVisitor visit;
 if(g_bfmeExtra1282Flags&4)visit=(AptDisplayVisitor)rva006F73A0;else visit=rva006F7330;
 _ReadWriteBarrier();
 while(item){
  if(!((BfmeAptValue006DCD20*)item)->isUndefined()){
   if(!item){g_bfmeAptAssertAtE17734("this","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h",0xD8);if(g_bfmeAptBreakOnAssertAtDDC01C)__debugbreak();}
   if(((Rva006DBB30SarDwordField*)item)->get()!=19 || ((BfmeAptValue006DCD20*)item)->isUndefined()){
    if(item->info->clipDepth>=0){masks.rva006F7570((Rva006F7570Item*)item);visit(context,item,1);maskCount=masks.count;}
    else {
     while(maskCount>0){
      int last=maskCount-1;
      if(masks.get(last,maskCount)->info->clipDepth>=item->depth)break;
      visit(context,masks.get(last,maskCount),-1);
      masks.rva006F7600(last);maskCount=masks.count;
     }
     visit(context,item,mode);
    }
   }
  }
  item=item->next;
 }
 while(maskCount>0){visit(context,masks.get(0,maskCount),-1);maskCount=masks.removeFront(maskCount);}
}
// Cached bounds follow retail EDI; front removal refreshes count in the shift loop.
// Remaining destructor count reload: reverse/attempt_support/0x006f7720-20261019-w3/readme.md.
