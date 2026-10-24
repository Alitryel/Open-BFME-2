#pragma once
// Native FireLogicSystem::BurningCell; address-derived class spelling retained.
// Tables BFB700/BFB6F0 and size20 are independently verified in retail.
#include "Rva00285635.h"
#define BFME_SNAPSHOT_NAME_SLOT
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"
typedef Rva00285635 Rva00285BECBase;
class __declspec(novtable) Rva00285BECSnapshotBase:public Snapshot {
public:
 virtual ~Rva00285BECSnapshotBase(){}
 virtual void loadPostProcess(){}
 virtual const char*GetSnapshotName()const;
 virtual void xfer(Xfer*);
};
class Rva00285BEC:public Rva00285BECBase,public Rva00285BECSnapshotBase {
public:
 struct Pair080C {
  int m_00,m_04;
  Pair080C(){}
  Pair080C(int a,int b):m_00(a),m_04(b){}
  Pair080C(Pair080C const&s):m_00(s.m_00),m_04(s.m_04){}
 };
 Rva00285BEC(int,int);
 Rva00285BEC(Rva00285BEC const&);
 virtual ~Rva00285BEC();
 virtual Rva00SlotFloat2FromInts vslot00();
 virtual Rva00SlotFloat2FromInts vslot01()const;
 virtual unsigned char* vslot02();
 virtual unsigned char const* vslot03()const;
 virtual unsigned char* vslot04();
 virtual unsigned char const* vslot05()const;
 virtual short vslot06()const;
 virtual LargeGroupAudioKeyMap* vslot07()const;
 virtual bool vslot08()const;
 virtual bool vslot09()const;
 virtual int vslot10()const;
 Pair080C m_08;
 int m_10;
};
