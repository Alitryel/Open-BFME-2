// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Include /Ireference/shims/bfmealloc /D_CRTIMP= /D_STLP_USE_STATIC_LIB
//
// AIRoamingDefenseTactic::roam (retail 0x005AAE3F..0x005AB085, 582 B).
// WB 0x151CEE0 carries the name (AIRoamingDefenseTactic.cpp:164/186 random
// calls). With live targets near the owner's centre (distance^2 < 810000)
// the object is sent to a random one; otherwise it is sent 400 units from the
// first bit-4 building, rotated by a random 0..6 angle.
//
// Evidence (target): native body and its rowed callees (player-AI lookup
// 0x002A8F24/0x002A8AB1, centre 0x004EBF4B, ID-set fields 0x005C4AD1,
// GameLogic::findObjectByID, the AI command 0x00295A0F). Vector3::Rotate_Z is
// spelled as the WB twin shows (s = sinf(angle), c = cosf(angle) as two
// statements, then the X-first two-argument rotate). Field and helper names
// stay address-derived where the original is unknown.
// stlport
#include <stdlib.h>
namespace _STL {void __cdecl free(void *); }
#define free _STL::free
#include <vector>
#undef free

#include <functional>
#include "Lib/Coord3D.h"
#include "../../../../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
namespace _STL {
 template<class T>struct hash;
 template<class K,class V,class H,class E,class A>class hash_map {public:unsigned int bucket_count()const;};
}
typedef _STL::hash_map<int,int,_STL::hash<int>,_STL::equal_to<int>,_STL::allocator<_STL::pair<const int,int> > > IntMap;
class Rva005C4AD1LeaField{public:void *get()const;};
struct RoamOwnerStats{char pad[8];Rva005C4AD1LeaField *all;IntMap *targets;};
struct Rva002A8AB1Record;
class Player;
class Rva002A8F24 {public:void *rva002A8F24(Player *);Rva002A8AB1Record *rva002A8AB1(void *);};
extern Rva002A8F24 *g_00DFEEF8;
class Rva004EBF4B{public:Coord3D rva004EBF4B();};
class Rva00295A0FCommands{public:void Rva00295A0FCommand(void*,int,int);};
struct RoamAI {char pad[0x20];Rva00295A0FCommands commands;};
struct RoamObjectTemplate{char pad[0x120];unsigned int bits;};
class Object{public:char pad0[4];RoamObjectTemplate *objectTemplate;char pad8[0x38-8];Coord3D position;char pad44[0x258-0x44];RoamAI *ai;};
int GetGameLogicRandomValue(int,int,char *,int);
#include <math.h>
// Arithmetic follows Zero Hour WWMath vector3.h; WB independently names
// Vector3 Distance2/Length2/Rotate_Z in the target caller.
struct RoamVector3 {
 float X,Y,Z;
 __forceinline RoamVector3(float x,float y,float z):X(x),Y(y),Z(z){}
 __forceinline float length2()const{return X*X+Y*Y+Z*Z;}
 __forceinline void rotate(float angle){float s=sinf(angle);float c=cosf(angle);rotate(s,c);}
 __forceinline void rotate(float s_angle,float c_angle){float tmp_x=X;float tmp_y=Y;X=c_angle*tmp_x-s_angle*tmp_y;Y=s_angle*tmp_x+c_angle*tmp_y;}
 __forceinline RoamVector3 &operator*=(float k){X=X*k;Y=Y*k;Z=Z*k;return *this;}
 __forceinline void scale(float f){X*=f;Y*=f;Z*=f;}
};
static __forceinline void RoamSet(Coord3D *p,float x,float y,float z){p->x=x;p->y=y;p->z=z;}
static __forceinline void RoamAdd(Coord3D *p,const Coord3D *q){p->x+=q->x;p->y+=q->y;p->z+=q->z;}
static __forceinline float RoamDistance2(const RoamVector3 &a,const RoamVector3 &b){RoamVector3 diff(0,0,0);diff.Z=a.Z-b.Z;diff.Y=a.Y-b.Y;diff.X=a.X-b.X;return diff.length2();}
class AIRoamingDefenseTactic {public:void roam(Object *);char pad[0x24];Player *owner;};
void AIRoamingDefenseTactic::roam(Object *obj)
{
 RoamOwnerStats *stats=(RoamOwnerStats *)g_00DFEEF8->rva002A8F24(owner);
 IntMap *targets=stats->targets;
 if(targets->bucket_count()>0){
  Rva002A8AB1Record *record=g_00DFEEF8->rva002A8AB1(owner);
  Coord3D center=((Rva004EBF4B *)record)->rva004EBF4B();
  _STL::vector<ObjectID> *ids=(_STL::vector<ObjectID> *)((Rva005C4AD1LeaField *)targets)->get();
  _STL::vector<Object *> nearby;
  _STL::vector<ObjectID>::iterator end=ids->end();
  for(_STL::vector<ObjectID>::iterator it=ids->begin();it!=end;++it){
   Object *target=TheGameLogic->findObjectByID(*it);
   if(target){
    if(RoamDistance2(RoamVector3(center.x,center.y,center.z),RoamVector3(target->position.x,target->position.y,target->position.z))<810000.0f)nearby.push_back(target);
   }
  }
  if(!nearby.empty()){
   Object *target=nearby[GetGameLogicRandomValue(0,nearby.size()-1,"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\SkirmishAI\\AITacticalAI\\AITacticsGenerator\\TargetlessTactics\\AIRoamingDefenseTactic.cpp",164)];
   RoamAI *ai=obj->ai;ai->commands.Rva00295A0FCommand(&target->position,0x7FFFFFFF,0);
  }
 }else{
  Object *building=0;
  _STL::vector<ObjectID> *ids=(_STL::vector<ObjectID> *)stats->all->get();
  _STL::vector<ObjectID>::iterator end=ids->end();
  for(_STL::vector<ObjectID>::iterator it=ids->begin();it!=end;++it){
   if(!building){
    Object *target=TheGameLogic->findObjectByID(*it);
    if(target && (target->objectTemplate->bits &4))building=target;
   }else break;
  }
  if(building){
   float angle=(float)GetGameLogicRandomValue(0,6,"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\SkirmishAI\\AITacticalAI\\AITacticsGenerator\\TargetlessTactics\\AIRoamingDefenseTactic.cpp",186);
   RoamVector3 relative(1.0f,0.0f,0.0f);
   relative.rotate(angle);
   relative*=400.0f;
   Coord3D point;
   RoamSet(&point,relative.X,relative.Y,relative.Z);
   RoamAdd(&point,&building->position);
   obj->ai->commands.Rva00295A0FCommand(&point,0x7FFFFFFF,0);
  }
 }
}
