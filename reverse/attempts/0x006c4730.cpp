// ?rva006C4730@GeneralAllocatorDebug@@QAEPAXPAXIH@Z
// partial score=0.97 date=2026-10-16
// ?rva006C4730@GeneralAllocatorDebug@@QAEPAXPAXIH@Z
// partial score=0.94 date=2026-10-14
// ?rva006C4730@GeneralAllocatorDebug@@QAEPAXPAXIH@Z
// partial score=0.8739254351 date=2026-10-10
// cl: /O2 /G6 /MD /EHsc /DNDEBUG
// Native 6C4730..6C4A4E is a complete RET12 debug-allocator reallocation.
// Family identity derives independently from the allocator diagnostic string
// and the shared +4E4 lock/+680 tracking/+684 hash views in verified owners.
// Record suffix arithmetic, 4-byte out pointer + 0x12C-byte build record, 1024-byte backup array,
// and all physical calls below derive from native and WB70BE40; names of
// unowned operations and records remain address-derived. No donor C++ body
// for this allocator implementation is present at BF1 revision575ba2b.
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
extern "C" __declspec(dllimport) void *memmove(void*,const void*,unsigned);
extern "C" void *memcpy(void*,const void*,unsigned);
struct Rva00030DD0Lock;
int Rva00030DD0AddRef(Rva00030DD0Lock*);
int Rva00030DF0Release(Rva00030DD0Lock*);
class Rva006C1F60 {public:void *rva00033ED0(unsigned,int);void rva006C33D0(int,int);};
class Rva00033150 {public:void rva00033150(int);};
namespace EA {namespace Allocator {class GeneralAllocator {public:void *rva000347A0(void*,unsigned,int);};}}
class Rva006C1850 {public:bool rva006C1850(unsigned,void**);};
struct Rva006C4730RecordInfo {void *source;};
struct Rva006C2270Slot {unsigned total,length,mode;};
struct Rva006C2270Record {
 unsigned initial;Rva006C2270Slot slots[14];
 unsigned inlineTotal,externalTotal,requestedSize,arg2,arg3,arg4,word520,word524;
 void*stack[24];
};
class Rva006C1D60 {public:bool rva006C1D60(unsigned,bool);};
class Rva006C39F0Owner {public:bool rva006C39F0(unsigned,unsigned,unsigned,void*);};
class Rva006C4730Guard {Rva00030DD0Lock*lock;public:Rva006C4730Guard(Rva00030DD0Lock*p):lock(p){if(lock)Rva00030DD0AddRef(lock);}~Rva006C4730Guard(){if(lock)Rva00030DF0Release(lock);}};
class GeneralAllocatorDebug {
public:
 void *rva006C4730(void *data,unsigned size,int flags);
 unsigned rva006C2510(char*,int,char**);
 void rva006C2270(Rva006C2270Record*,unsigned,unsigned,unsigned,unsigned);
 void rva006C26F0(void*,int);
 bool rva006C3D30(Rva006C2270Record*,void*,bool);
 void *rva006C25F0Run6(void*,int,int,int,unsigned*,int);
private:
 char prefix00[0x4E4];Rva00030DD0Lock*lock;
 char prefix4E8[0x548-0x4E8];unsigned head548[3];void *next554;
 char prefix558[0x680-0x558];bool tracking;
 char prefix681[3];unsigned hash684;
};
static __forceinline unsigned chunkCapacity(void *data)
{
 unsigned n=*((unsigned*)data-1);
 if(!(n&2))return(n&0x7FFFFFF8)+4;
 return n&0x7FFFFFF8;
}
static __forceinline void *mallocBackup(GeneralAllocatorDebug *self,unsigned n)
{
 void *p=((Rva006C1F60*)self)->rva00033ED0(n,0x80000000);
 if(p) {
  unsigned n=((unsigned*)p)[-1];
  char *end;
  if(!(n&2)) end=(char*)p+((n&0x7ffffff8)+4)-10;
  else end=(char*)p+(n&0x7ffffff8)-10;
  *(unsigned short*)end=0;
 }
 return p;
}
void *GeneralAllocatorDebug::rva006C4730(void *data,unsigned size,int flags)
{
 Rva006C4730Guard guard(lock);
 void *backupAllocation=0;
 void *backup=0;
 unsigned backupLength;
 void *oldChunk;
 Rva006C2270Record info;
 char localBackup[1024];
 unsigned extra;
 unsigned total;
 if(data) {
  oldChunk=(char*)data-8;
  Rva006C4730RecordInfo query;
  extra=rva006C2510((char*)data,0,(char**)&query.source);
  backupLength=extra;
  if(extra>992) {
   do {
    backup=backupAllocation=mallocBackup(this,extra+2);
    if(backupAllocation)break;
    if(next554==(void*)head548)return 0;
    ((Rva006C1F60*)this)->rva006C33D0(0,0);
   }while(true);
   *((unsigned*)backupAllocation-1)|=4;
  } else backup=localBackup;
  memmove(backup,query.source,extra);
  total=extra+size;
 } else {
  oldChunk=0;backupLength=0;backup=0;
  rva006C2270(&info,size,flags,8,0);
  total=size+info.inlineTotal;
 }
 rva006C26F0(oldChunk,0);
 void *result=((EA::Allocator::GeneralAllocator*)this)->rva000347A0(data,total,flags);
 while(!result) {
  if(next554==(void*)head548) goto failed;
  ((Rva006C1F60*)this)->rva006C33D0(0,0);
  result=((EA::Allocator::GeneralAllocator*)this)->rva000347A0(data,total,flags);
 }
 if(result) {
 if(data) {
  void *chunk=(char*)result-8;
  unsigned capacity=chunkCapacity((result ? result : result));
  if(backup)memcpy((char*)chunk+capacity-backupLength,backup,backupLength);
  else *(unsigned short*)((char*)chunk+capacity-2)=0;
  if(tracking) {
   void *record=0;
   if(((Rva006C1850*)&hash684)->rva006C1850((unsigned)data,&record)&&result!=data) {
    void *oldRecord=*(void**)record;
    ((Rva006C1D60*)this)->rva006C1D60((unsigned)data,false);
    if(!((Rva006C39F0Owner*)this)->rva006C39F0((unsigned)result,0,(unsigned)oldRecord,0)) {
     ((Rva00033150*)this)->rva00033150((int)result);result=0;
    }
   }
  }
  if(result) {
   unsigned *stored=(unsigned*)rva006C25F0Run6(result,2,0,0,0,2);
   if(stored)*stored=size;
   rva006C26F0((char*)result-8,1);
  }
 } else {
  if(rva006C3D30(&info,result,true)) rva006C26F0((char*)result-8,1);
  else {
   ((Rva00033150*)this)->rva00033150((int)result);result=0;
  }
 }
 }
 else {
failed:
  if(data)((Rva006C1D60*)this)->rva006C1D60((unsigned)data,true);
 }
 if(backupAllocation)((Rva00033150*)this)->rva00033150((int)backupAllocation);
 return result;
}
