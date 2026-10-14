// ?rva000317F0@GeneralAllocator@Allocator@EA@@QAEXHI@Z
// partial score=0.7926309141 date=2026-10-14
// flags: region default (/O2)
// Native 317F0..31B58: one 13-case option switch, including the complete
// 13-entry target table at31B24. The preceding four CC bytes are padding.
// GeneralAllocator's established memory_pool.cpp layout and lock providers
// give the semantic/ABI guide; the original option enum/API spelling is unknown.
struct Rva00030DD0Lock { char section[0x18]; volatile int count; };
Rva00030DD0Lock *Rva00030D90Init(Rva00030DD0Lock *);
int Rva00030DD0AddRef(Rva00030DD0Lock *);
int Rva00030DF0Release(Rva00030DD0Lock *);
extern "C" __declspec(dllimport) void __stdcall DeleteCriticalSection(void *);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void *);
class Rva00031790 {
public:
 void *pointer;
 void *rva00031790(void *);
};
struct AllocatorOptionLock : Rva00031790 {
 AllocatorOptionLock(void *p) {rva00031790(p);}
 ~AllocatorOptionLock() {
  Rva00030DD0Lock *p=(Rva00030DD0Lock *)pointer;
  if(p){--p->count;LeaveCriticalSection(p);}
 }
};
class Rva00034C90 {public:void rva00033930();};
class Rva00030D10 {public:void rva00030D10(unsigned size);};
namespace EA { namespace Allocator {
class GeneralAllocator {
 char pad000[0x468];
 unsigned option468;
 bool state46C,option46D;
 char pad46E[0x22];
 unsigned option490,option494;
 bool option498;
 char pad499[0x1B];
 unsigned option4B4;
 char pad4B8[0x10];
 unsigned option4C8,option4CC;
 char pad4D0[4];
 unsigned granularity4D4,coreSize4D8,growSize4DC;
 bool option4E0;
 char pad4E1[3];
 Rva00030DD0Lock *lock;
 Rva00030DD0Lock lockStorage;
public:
 void rva000317F0(int option,unsigned value);
};
void GeneralAllocator::rva000317F0(int option,unsigned value) {
 switch(option) {
 case 1:
  if(value) {
   if(!lock)lock=Rva00030D90Init(&lockStorage);
  } else if(lock) {
   Rva00030DD0AddRef(lock);
   Rva00030DD0Lock *p=lock;
   lock=0;
   Rva00030DF0Release(p);
   DeleteCriticalSection(p);
  }
  break;
 case 2: {
  AllocatorOptionLock guard(lock);
  if(value) {
   if(!state46C && !option468)option468=1;
  } else option468=0;
  break;
 }
 case 3:option46D=value!=0;break;
 case 4:
  if(!value)coreSize4D8=0x1000000;
  else {
   if(value<=granularity4D4)value=granularity4D4;
   coreSize4D8=(value+granularity4D4-1)&~(granularity4D4-1);
  }
  break;
 case 5:
  if(!value)growSize4DC=0x400000;
  else {
   if(value<=granularity4D4)value=granularity4D4;
   growSize4DC=value;
   growSize4DC=(growSize4DC+granularity4D4-1)&~(granularity4D4-1);
   if(growSize4DC>coreSize4D8)growSize4DC=coreSize4D8;
  }
  break;
 case 6: {
  AllocatorOptionLock guard(lock);
  ((Rva00034C90*)this)->rva00033930();
  ((Rva00030D10*)this)->rva00030D10(value);
  break;
 }
 case 7:option4C8=value;break;
 case 8:option4CC=value;break;
 case 9:option494=value;break;
 case 10:option490=value;break;
 case 11:option498=value!=0;break;
 case 12:option4E0=value!=0;break;
 case 13:option4B4=value;break;
 }
}
}}
