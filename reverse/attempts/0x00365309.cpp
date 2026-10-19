// ?rva00365309@Path@@QAE_NPAVObject@@PAVPathNode@@PBUCoord3D@@PAUDirectionOptions@@HM_N@Z
// partial score=0.985 date=2026-10-19
// ?rva00365309@Path@@QAE_NPAVObject@@PAVPathNode@@PBUCoord3D@@PAUDirectionOptions@@HM_N@Z
// partial score=0.979 date=2026-10-16
// ?rva00365309@Path@@QAE_NPAVObject@@PAVPathNode@@PBUCoord3D@@PAUDirectionOptions@@HM_N@Z
// partial W9-O1 2026-10-16: WB 0x00F1FC60-shaped rebuild, 2177/2177 B, frame 0x78 exact, nn 24 (scheduling only).
// Levers: start/dest/delta/center/end as member-wise Coord3D copies (Coord3DCtorView + COORD3D_VIEW_INLINE
// sub/add/scale); the delta block-scoped (it escapes into the opaque Coord3D::length, so only a block lets
// center share its slot: frame 0x84 -> 0x78); the same-unit angle helper 0x363B4B visible as an
// inline noinline copy (keeps cdecl; a static copy gets a private register ABI); WB Rotate_Z
// (sin then cos, tmp_x/tmp_y), radial sign Cross_Product_Z(second, first); node->getLayer() accessor
// (evaluated before the pathfinder load); copy-then-zero radials; dest.add + scale(0.5).
// The rowed IsLinePassable placeholder types its 6th argument void*, but WB 0xF21CC8 shows BFME 2
// passes the Bool parameter through unconverted; the call reads the bool's argument word as retail does.
// Residue: x87 result stores (cos) scheduled before independent SSE loads at the Rotate_Z sites,
// one xorps/movss pair, the loop-tail mov esi placement and the dest.add x-term order.
// permute.py 1466 trials: no gain. Lands together with 0x365E98 (needs this body visible).
// cl: /ICode/Libraries/Include /O1 /DNDEBUG /MD /arch:SSE /G7 /EHsc
// 0x00365309 bank 2026-10-19 (claude-opus-5-5): hack-free 2177/2177, nd 31 (was 37 with an artificial
// ~Vector3). WB F1FC60: only Coord3D locals carry EH states, so the real empty Coord3D dtor
// (COORD3D_VIEW_DTOR, 0x000B3FD0) replaces the fake Vector3 one; PathNode gets class-scoped pooled
// operator new/delete (new PathNode(...); delete saved;) as WB shows, which closed the final midpoint
// (ctor keeps throw(): retail has no EH frame for it). Left: the cos fstp scheduled before 1-3 SSE ops at
// all four Rotate_Z sites, one zero-register reload order after the radial Inv_Sqrt, loop-tail
// options/node reload order. Home: likely a new Pathfinder unit beside rva00365E98Rva00365E98Farm.cpp
// (same flags). Scratch: build/nbr/r7/365309/.
// Native365309..365B8A RET28; WB F1FC60 confirms curve construction.
// ZH Vector3 math and Path/PathNode ownership are semantic guides. Native
// provides portal20, optimized-link8, options0/1/4/8, and all call addresses.
#define COORD3D_VIEW_INLINE
#define COORD3D_VIEW_DTOR
#include "Lib/Coord3DCtorView.h"
#include <math.h>
#include <new>
enum PathfindLayerEnum {LAYER_GROUND=1};
struct Rva0028AC4EEntry;
class Object {public:const Rva0028AC4EEntry *rva0028AC4E()const;};
class Rva001E3F27FloatChaseField {public:float get()const;};
class Rva00065964ObjectPool {public:void *rva002635C2()throw();};
extern Rva00065964ObjectPool g_pathNodePool;
void FreePooledNode(void *);
class PathNode {public:
 static void *operator new(size_t){return g_pathNodePool.rva002635C2();}
 static void operator delete(void *p){FreePooledNode(p);}
 PathNode(const Coord3D *,PathfindLayerEnum)throw();
 PathfindLayerEnum getLayer()const{return layer;}
 PathNode *next,*previous,*nextOptimized;Coord3D pos;PathfindLayerEnum layer;bool canOptimize;char pad1D[3];int portalID;
};
class WWMath {public:static float __fastcall Inv_Sqrt(float);};
class Vector3 {public:
 float X,Y,Z;
 __forceinline Vector3(){} __forceinline Vector3(const Vector3 &v){X=v.X;Y=v.Y;Z=v.Z;} __forceinline Vector3(float x,float y,float z):X(x),Y(y),Z(z){} 
 __forceinline float Length2()const{return X*X+Y*Y+Z*Z;}
 __forceinline void Normalize(){float len2=Length2();if(len2!=0.0f){float oolen=WWMath::Inv_Sqrt(len2);X*=oolen;Y*=oolen;Z*=oolen;}}
 __forceinline void Scale(float s){X*=s;Y*=s;Z*=s;}
 __forceinline void Rotate_Z(float s_angle,float c_angle){float tmp_x=X;float tmp_y=Y;X=c_angle*tmp_x-s_angle*tmp_y;Y=s_angle*tmp_x+c_angle*tmp_y;}
 __forceinline void Rotate_Z(float angle){float s=(float)sin((double)angle);float c=(float)cos((double)angle);Rotate_Z(s,c);}
 static __forceinline float Cross_Product_Z(const Vector3 &a,const Vector3 &b){return a.X*b.Y-a.Y*b.X;}
};
struct Rva00363B4BVector {float x,y,z;};
float ACos(float);
inline __declspec(noinline) float rva00363B4BAngle(const Rva00363B4BVector *a, const Rva00363B4BVector *b)
{
    float dot = a->z * b->z + a->y * b->y + a->x * b->x;
    if (dot > 1.0f) dot = 1.0f;
    if (dot < -1.0f) dot = -1.0f;
    if (dot >= 0.99f) return 0.0f;
    return ACos(dot);
}
static __forceinline float angleBetween(const Vector3 &a,const Vector3 &b){return rva00363B4BAngle((const Rva00363B4BVector *)&a,(const Rva00363B4BVector *)&b);}
struct DirectionOptions {bool flag0,flag1;float value4;bool flag8;};
class Pathfinder {public:
 bool IsValidMovementPositionForObject(const Coord3D *,int,int,const Object *);
 int IsLinePassable(void *,void *,PathfindLayerEnum,const Coord3D *,const Coord3D *,void *,int,int);
};
class AI {public:char pad00[0x10];Pathfinder *finder;Pathfinder *pathfinder()const{return finder;}};
extern AI *TheAI;
class Path {public:
 bool rva00365309(Object *,PathNode *,const Coord3D *,DirectionOptions *,int,float,bool);
 void rva003649B1(const PathNode *);
 void rva002655E3(const Coord3D *,PathfindLayerEnum,int);
 void rva00364AA2(PathNode *,PathNode *,PathNode *,float);
 int rva003641AE(float,float);
};
bool Path::rva00365309(Object *obj,PathNode *node,const Coord3D *input,DirectionOptions *options,int surfaces,float maxAngle,bool blocked)
{
 PathNode *next=node->nextOptimized;
 if(node->portalID!=0x7fffffff || !next){if(!options->flag0)rva003649B1(node);return true;}
 float radius=options->value4;
 Coord3D start=node->pos;
 Coord3D dest=next->pos;
 {
  Coord3D delta=dest;
  delta.sub(&start);
  float halfLength=delta.length()*0.5f;
  if(halfLength<radius)radius=halfLength;
 }
 Vector3 direction(input->x,input->y,input->z);
 direction.Normalize();
 Vector3 towards(dest.x-start.x,dest.y-start.y,dest.z-start.z);
 towards.Normalize();
 float sign=Vector3::Cross_Product_Z(direction,towards)>0.0f?1:-1;
 bool positive=true;
 float bend=angleBetween(direction,towards);
 if(bend<0.19634955f || bend>maxAngle){if(!options->flag0)rva003649B1(node);return true;}
 float rotation=1.5707963705062866f;
 if(options->flag1){
  if(bend<1.5707963705062866){options->flag1=false;if(options->flag0)return false;}
  else sign=-sign;
 }
 if(sign<0.0f){positive=false;bend=-bend;rotation=-rotation;}
 Vector3 offset=direction;
 offset.Rotate_Z(rotation);
 offset.Scale(radius);
 if(!options->flag0)rva003649B1(node);
 Coord3D center=node->pos;
 center.x+=offset.X;center.y+=offset.Y;
 Vector3 toDest(dest.x,dest.y,dest.z);
 toDest.X-=center.x;toDest.Y-=center.y;
 Vector3 radial=toDest;
 radial.Rotate_Z(-rotation);
 radial.Normalize();
 radial.Scale(radius);
 Coord3D end=center;
 end.x+=radial.X;end.y+=radial.Y;
 offset.Scale(-1.0f);
 Vector3 firstRadial=offset;firstRadial.Z=0.0f;firstRadial.Normalize();
 Vector3 secondRadial=radial;secondRadial.Z=0.0f;secondRadial.Normalize();
 float sweep=angleBetween(firstRadial,secondRadial);
 float radialSign=Vector3::Cross_Product_Z(secondRadial,firstRadial)>0.0f?1:-1;
 if(radialSign==sign)sweep=6.2831855f-sweep;
 Vector3 remainder(dest.x,dest.y,0.0f);
 remainder.X-=end.x;remainder.Y-=end.y;
 remainder.Normalize();
 remainder.Rotate_Z(-rotation);
 float extra=angleBetween(remainder,secondRadial);
 sweep+=extra;
 if(options->flag1)sweep=6.2831855f-sweep;
 if(sweep>4.712389f){sweep-=6.2831855f;if(sweep<0.0f)sweep=0.0f;}
 int segments=rva003641AE(sweep,radius);
 if(segments<2)return true;
 if(!positive)sweep=-sweep;
 float step=sweep/(float)segments;
 for(int i=1;i<=segments;i++){
  Vector3 point=offset;
  point.Rotate_Z((float)i*step);
  Coord3D position=center;
  position.x+=point.X;position.y+=point.Y;position.z=start.z;
  if(options->flag0){
   if(!TheAI->pathfinder()->IsValidMovementPositionForObject(&position,node->getLayer(),surfaces,obj))return false;
   if(i==segments && !(unsigned char)TheAI->pathfinder()->IsLinePassable(obj,(void *)surfaces,node->getLayer(),&position,&dest,*(void *const *)&blocked,0,0))return false;
  } else {
   rva002655E3(&position,node->getLayer(),0x7fffffff);
   node->pos=position;
  }
 }
 if(!options->flag0 && !options->flag8){
  PathNode *saved=new PathNode(&node->pos,LAYER_GROUND);
  dest.add(&node->pos);
  dest.scale(0.5f);
  node->pos=dest;
  const Rva0028AC4EEntry *entry=obj->rva0028AC4E();if(entry)radius=((const Rva001E3F27FloatChaseField *)entry)->get();
  rva00364AA2(saved,node,next,radius);delete saved;
 }
 return true;
}
