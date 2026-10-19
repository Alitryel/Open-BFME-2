// ?getBestContactPoint@GeometryInfo@@QBE_NPAUCoord3D@@PBU2@PBDHH_N@Z
// partial score=0.6735615248150802 date=2026-10-16
// cl: /O2 /Ob2 /G6 /DNDEBUG /MD /EHs-c- /Ireference/shims/bfme2_ascii /ICode/Libraries/Include/Lib
// GeometryInfo::CollidesWith, retail 0x006BEB80..0x006BEEB5 (821 bytes, RET 0x14).
//
// Target evidence: WB assert strings name GeometryInfo::CollidesWith; the
// shape vector is begin/end at +0x2C/+0x30 of 36-byte GeometryShape records
// (type, height, major, minor, offset, AsciiString name, enabled, flag), each
// placed through the rowed transform 0x006BE190 and copied with the AsciiString
// copy constructor 0x004365F0 into a 52-byte contact (shape, position, angle).
// Pair tests are the rowed circle/box 0x006C0710, box/box 0x006C0630 and
// sphere/sphere 0x006C0790. The vertical rules are asymmetric in retail: the
// own top is compared against the other position's z less the other's extent
// (only for spheres), and the own centre against the other placed top.
// A shape type outside 0..2 leaves the running result untouched.
//
// Structural inference: the two vertical rejections are one combined
// condition. Two separate continues lay the x87 pop for the first rejection
// inline, which lets the compiler merge the four pair-test result stores;
// retail keeps that pop ahead of the join and duplicates the stores per case.
// ZH Geometry.cpp is a semantic guide only (enum order SPHERE, CYLINDER, BOX).
#include "ascii_string.h"
#include "Coord3D.h"
#include <float.h>
extern "C" int fprintf(void*,const char*,...);
extern "C" void *theLogicRandomLogFile;
extern bool g_bfmeDockingTraceActive;
struct GeometryContactRecord {Coord3D position; AsciiString label;};
struct Rva0087E900Coord { float x,y,z; };
struct Rva0087E900Shape { char pad[0x10]; Rva0087E900Coord offset; };
Rva0087E900Coord *Rva0087E900(Rva0087E900Coord *,const Rva0087E900Coord *,const Rva0087E900Shape *,float);
struct Rva00880D10Subject;
struct Rva00880D10Info;
struct BfmeCollisionShape;
bool rva00880D10(Rva00880D10Subject *,Rva00880D10Info *);
bool rva006C0630(Rva00880D10Info *,Rva00880D10Info *);
bool bfmeSphereOverlap(const BfmeCollisionShape *,const BfmeCollisionShape *);
struct Rva006BEB80Point:Rva0087E900Coord{Rva006BEB80Point(){} Rva006BEB80Point(const Rva0087E900Coord&r){x=r.x;y=r.y;z=r.z;} };
struct Rva006BEB80Offset:Coord3D{Rva006BEB80Offset(){} Rva006BEB80Offset(const Rva006BEB80Offset&r){x=r.x;y=r.y;z=r.z;} };
struct GeometryShape {
 int type; float height,major,minor; Rva006BEB80Offset offset; AsciiString name;
 bool enabled,flag;
 __declspec(dllimport) __forceinline GeometryShape(const GeometryShape &r):type(r.type),height(r.height),major(r.major),minor(r.minor),offset(r.offset),name(r.name),enabled(r.enabled),flag(r.flag) {}
};
struct GeometryContact {
 GeometryShape shape; Rva006BEB80Point position; float angle;
 __declspec(dllimport) __forceinline GeometryContact(const GeometryShape &s,const Rva0087E900Coord &p,float a):shape(s),position(p),angle(a){}
};
class GeometryInfo {
public:
 bool getBestContactPoint(Coord3D*,const Coord3D*,const char*,int,int,bool) const;
 float getMaxHeightAbovePosition()const;
 bool CollidesWith(const Coord3D &,float,const GeometryInfo &,const Coord3D &,float) const;
private:
 void *vptr; char prefix[0x28]; GeometryShape *begin,*end,*limit;
 GeometryContactRecord *contactsBegin,*contactsEnd,*contactsCapacity;
 Coord3D preferredPosition,defaultPosition;
};
static inline float topExtent(const GeometryShape &s) {
 float extent=0.0f;
 switch(s.type) { case 0: extent=s.major; break; case 1: case 2: extent=s.height; break; }
 return extent+s.offset.z;
}
static __forceinline bool overlap(GeometryContact &a,GeometryContact &b,bool cur) {
 switch(a.shape.type) {
 case 0: case 1:
  if(b.shape.type==2) return rva00880D10((Rva00880D10Subject *)&a,(Rva00880D10Info *)&b);
  return bfmeSphereOverlap((const BfmeCollisionShape *)&a,(const BfmeCollisionShape *)&b);
 case 2:
  if(b.shape.type==2) return rva006C0630((Rva00880D10Info *)&a,(Rva00880D10Info *)&b);
  return rva00880D10((Rva00880D10Subject *)&b,(Rva00880D10Info *)&a);
 }
 return cur;
}
bool GeometryInfo::CollidesWith(const Coord3D &p,float angle,const GeometryInfo &other,const Coord3D &q,float otherAngle) const {
 bool found=false;
 for(GeometryShape *s=begin;s!=end;++s) {
  if(!s->enabled) continue;
  if(found) break;
  Rva0087E900Coord temp;
  Rva006BEB80Point ownCenter=*Rva0087E900(&temp,(const Rva0087E900Coord *)&p,(const Rva0087E900Shape *)s,angle);
  GeometryContact a(*s,ownCenter,angle);
  float h=topExtent(*s);
  for(GeometryShape *t=other.begin;t!=other.end;++t) {
   if(!t->enabled) continue;
   if(found) break;
   Rva0087E900Coord temp2;
   Rva006BEB80Point otherCenter=*Rva0087E900(&temp2,(const Rva0087E900Coord *)&q,(const Rva0087E900Shape *)t,otherAngle);
   GeometryContact b(*t,otherCenter,otherAngle);
   float ht=topExtent(*t);
   float lower=0.0f;
   if(b.shape.type==0) lower=ht;
   if(ownCenter.z+h<q.z-lower || ownCenter.z>otherCenter.z+ht) continue;
   found=overlap(a,b,found);
  }
 }
 return found;
}

extern Coord3D GeometryContactOrigin;
extern unsigned g_Va00E0C150;
struct ContactPoint:Coord3D { ContactPoint(const Coord3D&r) {x=r.x;y=r.y;z=r.z;} };
static inline void contactCopy(Coord3D &out,const Coord3D &in){out.x=in.x;out.y=in.y;out.z=in.z;}
bool GeometryInfo::getBestContactPoint(Coord3D*out,const Coord3D*caller,const char*label,int preference,int seed,bool ignoreCollision)const {
 if(g_bfmeDockingTraceActive&&caller&&theLogicRandomLogFile)
  fprintf(theLogicRandomLogFile,"        GeometryInfo::getBestContactPoint, callerPos=%g,%g,%g, label=%s, pref=%d, seed=%d, skipCollideTest=%d, m_innermostContactPoint=%g,%g,%g",caller->x,caller->y,caller->z,label?label:"NONE",preference,seed,ignoreCollision?"TRUE":"FALSE",defaultPosition.x,defaultPosition.y,defaultPosition.z);
 contactCopy(*out,defaultPosition);
 switch(preference){
 case 3:{
  int count=contactsEnd-contactsBegin;
  if(count>=2){
   int index=seed%(count-1);
   ContactPoint first=contactsBegin[index].position;
   ContactPoint second=contactsBegin[index+1].position;
   float t=((seed>>8)&255)/255.0f;
   first.x*=t;first.y*=t;first.z*=t;
   float inverse=1.0f-t;second.x*=inverse;second.y*=inverse;second.z*=inverse;
   first.x+=second.x;first.y+=second.y;first.z+=second.z;
   contactCopy(*out,first);
  }
  float height=getMaxHeightAbovePosition();
  if(out->z>height)out->z=height;
  if(!ignoreCollision&&!CollidesWith(GeometryContactOrigin,0.0f,*(const GeometryInfo *)&g_Va00E0C150,*out,0.0f)){
   for(GeometryShape*shape=begin;shape!=end;++shape){
    if(!shape->enabled)continue;
    out->x=shape->offset.x;out->y=shape->offset.y;out->z=shape->height*0.5f+shape->offset.z;break;
   }
  }
  if(out->z>height){out->z=height;return true;}
  if(out->z<height*0.1f)out->z=height*0.1f;
  return true;
 }
 case 1:
  contactCopy(*out,preferredPosition);
  {float h=getMaxHeightAbovePosition(); if(out->z>h)out->z=h;}
  return true;
 case 0:{
  if(!caller)return false;
  int count=contactsEnd-contactsBegin;
  int best=count;float bestDistance=FLT_MAX;
  for(int i=0;i<count;++i){
   if(contactsBegin[i].label.compare(label?label:"")!=0)continue;
   ContactPoint pos=contactsBegin[i].position;
   if(pos.z>getMaxHeightAbovePosition())pos.z=getMaxHeightAbovePosition();
   if(!ignoreCollision&&!CollidesWith(GeometryContactOrigin,0.0f,*(const GeometryInfo *)&g_Va00E0C150,pos,0.0f))continue;
   float dx=pos.x-caller->x,dy=pos.y-caller->y,dz=pos.z-caller->z;
   float d=dx*dx+dy*dy+dz*dz;
   if(d<bestDistance){bestDistance=d;best=i;}
  }
  if(best==count)return false;
  contactCopy(*out,contactsBegin[best].position);
  if(out->z>getMaxHeightAbovePosition()){out->z=getMaxHeightAbovePosition();return true;}
  if(out->z<getMaxHeightAbovePosition()*0.1f)out->z=getMaxHeightAbovePosition()*0.1f;
  return true;
 }
 default:return false;
 }
}
