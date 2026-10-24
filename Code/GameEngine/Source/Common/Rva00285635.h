#pragma once
// Native base table BFB698: eleven pure slots then deleting destructor 285635.
// Full table and body evidence: reverse/attempt_support/firelogic-lifetime-link-20261024/readme.md
class LargeGroupAudioKeyMap;
struct Rva00SlotFloat2FromInts {
 float x,y;
 Rva00SlotFloat2FromInts(int ax,int ay) {x=(float)ax;y=(float)ay;}
};
class Rva00285635 {
public: Rva00285635(){}
public:
 virtual Rva00SlotFloat2FromInts vslot00()=0;
 virtual Rva00SlotFloat2FromInts vslot01()const=0;
 virtual unsigned char* vslot02()=0;
 virtual unsigned char const* vslot03()const=0;
 virtual unsigned char* vslot04()=0;
 virtual unsigned char const* vslot05()const=0;
 virtual short vslot06()const=0;
 virtual LargeGroupAudioKeyMap* vslot07()const=0;
 virtual bool vslot08()const=0;
 virtual bool vslot09()const=0;
 virtual int vslot10()const=0;
 virtual ~Rva00285635(){}
};
