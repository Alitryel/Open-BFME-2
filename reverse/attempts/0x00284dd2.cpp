// ?iterateTreesNearAPoint@TerrainLogic@@QAEXPBUCoord3D@@MPAVGeometryInfo@@PAVBfmeT1035@@_NH@Z
// partial score=0.784926204755221 date=2026-10-14
// ?iterateTreesNearAPoint@TerrainLogic@@QAEXPBUCoord3D@@MPAVGeometryInfo@@PAVBfmeT1035@@_NH@Z
// partial score=0.784926204755221 date=2026-10-14
// ?iterateTreesNearAPoint@TerrainLogic@@QAEXPBUCoord3D@@MPAVGeometryInfo@@PAVBfmeT1035@@_NH@Z
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Include/Lib
// BFME1 a7c38d3b TerrainRecordScan001AEFF0.cpp, adapted to pointer records.
// WB C52910 names TerrainLogic::iterateTreesNearAPoint. Native 284DD2..285177.
#include "Coord3D.h"
#include <math.h>
struct Bounds {Coord3D lo,hi;};
struct Rva0087DC00Vec {int x,y,z;};
class Rva0087DC00 {public:void get(Rva0087DC00Vec*);};
enum GeometryType {GEOMETRY_SPHERE,GEOMETRY_CYLINDER,GEOMETRY_BOX};
class GeometryInfo {public: GeometryInfo(GeometryType,bool,float,float,float);virtual ~GeometryInfo();
 bool CollidesWith(const Coord3D &,float,const GeometryInfo &,const Coord3D &,float) const;
 char pad04[12]; float radius;char pad14[0x5c-0x14];};
class BfmeX1035;
class BfmeT1035 {public:void bfmeUse1035(BfmeX1035 *,int);};
struct Record {Coord3D position;int key;char pad10[8];bool flag18;char pad19[15];int amount;bool flag2c,flag2d;short next;};
class TerrainLogic {public:
virtual void slot0();
virtual void slot1();
virtual void slot2();
virtual void slot3();
virtual void slot4();
virtual void slot5();
virtual void slot6();
virtual void slot7();
virtual void slot8();
virtual void slot9();
virtual void bounds(Bounds *);
 char pad04[0x578-4]; Record **begin,**end,**capacity;char pad584[4];short buckets[50*50];
 void iterateTreesNearAPoint(const Coord3D*,float,GeometryInfo*,BfmeT1035*,bool,int);
};
void TerrainLogic::iterateTreesNearAPoint(const Coord3D *position,float angle,
 GeometryInfo *geometry,BfmeT1035 *action,bool skipFlag18,int mode) {
 float radius=geometry->radius;
 Coord3D center;
 ((Rva0087DC00*)geometry)->get((Rva0087DC00Vec*)&center);
 center.x+=position->x;center.y+=position->y;center.z+=position->z;
 int count=end-begin;
 if(count==0)return;
 radius+=7.0f;
 Bounds extent;
 bounds(&extent);
 float x=center.x-radius,y=center.y-radius;
 if(x<extent.lo.x)x=extent.lo.x;
 if(y<extent.lo.y)y=extent.lo.y;
 if(x>extent.hi.x)x=extent.hi.x;
 if(y>extent.hi.y)y=extent.hi.y;
 int minX=int((float)floor(((x-extent.lo.x)/(extent.hi.x-extent.lo.x))*49.9f));
 int minY=int((float)floor(((y-extent.lo.y)/(extent.hi.y-extent.lo.y))*49.9f));
 x=center.x+radius;y=center.y+radius;
 if(x<extent.lo.x)x=extent.lo.x;
 if(y<extent.lo.y)y=extent.lo.y;
 if(x>extent.hi.x)x=extent.hi.x;
 if(y>extent.hi.y)y=extent.hi.y;
 int maxX=int((float)ceil(((x-extent.lo.x)/(extent.hi.x-extent.lo.x))*49.9f));
 int maxY=int((float)ceil(((y-extent.lo.y)/(extent.hi.y-extent.lo.y))*49.9f));
 for(int i=minX;i<maxX;++i) {
  for(int j=minY;j<maxY;++j) {
   int index=buckets[j*50+i];
   while(index!=-1 && index>=0 && index<count) {
    Record **base=begin;
    unsigned offset=index*sizeof(Record *);
    Record *record=base[index];
    if(!record->key) {index=record->next;continue;}
    if(skipFlag18 && base[index]->flag18) {index=record->next;continue;}
    if(mode==1) {if(!base[index]->flag2c) {index=record->next;continue;}}
    else if(mode==2) {if(!base[index]->flag2d) {index=record->next;continue;}}
    Coord3D delta; delta.x=base[index]->position.x; delta.y=base[index]->position.y; delta.z=base[index]->position.z;
    delta.x-=center.x;delta.y-=center.y;delta.z-=center.z;
    GeometryInfo cylinder(GEOMETRY_CYLINDER,false,20.0f,7.0f,7.0f);
    if(radius*radius>(delta.x*delta.x+delta.y*delta.y+delta.z*delta.z) &&
       geometry->CollidesWith(*position,angle,cylinder,begin[index]->position,0.0f))
     action->bfmeUse1035((BfmeX1035*)record,(int)&center);
    index=record->next;
   }
  }
 }
}
