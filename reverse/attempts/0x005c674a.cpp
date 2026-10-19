// ?rva005C674A@Rva005C674A@@QAEXXZ
// partial score=0.9145299145299145 date=2026-10-19
// ?rva005C674A@Rva005C674A@@QAEXXZ
// partial score=0.714 date=2026-10-17
// ?rva005C674A@Rva005C674A@@QAEXXZ
// partial score=0.9 date=2026-10-14
// ?rva005C674A@Rva005C674A@@QAEXXZ
// partial score=0.820314917892695 date=2026-10-11
// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /ICode/Libraries/Include/Lib /ICode/Libraries/Source/WWVegas/WWLib /ICode
// stlport
#include <map>
#include <math.h>
#include "Coord2D.h"
// The duration role is inferred from target accesses; its original name is unknown.
float radialAnimationDuration;
struct RadialIntPoint {int x,y;};
class Rva005C6599 {public:void rva005C6599(float,float);};
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
class RadialAptPlayerView {public:
virtual void slot00();virtual void slot01();virtual void slot02();virtual void slot03();
virtual void slot04();virtual void slot05();virtual void slot06();virtual void slot07();
virtual void slot08();virtual void slot09();virtual void slot10();virtual void slot11();
virtual void slot12();virtual void slot13();virtual void slot14();virtual void slot15();
virtual const Coord2D*getScale();
};

// WB MathCoord2D::Rotate and retail both include sin/cos calls followed
// by FSINCOS. VC7 has no C++ intrinsic for the latter; this bounded x87
// helper models that math codegen blocker, rather than lifting the body.
static __forceinline void rotateRadialDirection(Coord2D &v,float angle) {
 float sine=(float)sin(angle),cosine=(float)cos(angle);
 __asm {
 fld angle
 fsincos
 fstp cosine
 fstp sine
 }
 const float oldY=v.y,oldX=v.x;
 float x=oldX*cosine-oldY*sine;
 v.y=oldX*sine+oldY*cosine;v.x=x;
}
class Rva005C674A {public:
 virtual void slot0();virtual void slot1();
 virtual void position(int,const RadialIntPoint&,const RadialIntPoint&);
 virtual void enable(int,bool);virtual void slot4();virtual void update();
 bool active;char pad5[3];int count;RadialIntPoint center,size;
 unsigned radius;unsigned unknown20;unsigned elapsed;
 float scale,step;
 _STL::map<int,int> buttons;
 void rva005C674A();
};
void Rva005C674A::rva005C674A(){
 if(count<=0)return;
 update();if(!active)return;
 Coord2D dir;dir.x=0.0f;dir.y=(float)(count<=1?0:-1);
 if(count>1){
  float fraction=1.0f;
  if(radialAnimationDuration!=0.0f){
   float e=(float)elapsed;
   float num=radialAnimationDuration<e?radialAnimationDuration:e;
   fraction=num/radialAnimationDuration;
  } else {
   fraction=1.0f;
  }
  rotateRadialDirection(dir,1.0f-fraction);
 }
 for(int i=0;i<count;++i){
  RadialIntPoint extent;
  extent.x=(int)(((float)size.x-1.0f)*(scale>1.0f?1.0f:scale)+1.0f);
  extent.y=(int)(((float)size.y-1.0f)*(scale>1.0f?1.0f:scale)+1.0f);
  float distance=((float)radius-0.1f)*scale+0.1f;
  Coord2D offset;offset.x=dir.x;offset.y=dir.y;
  offset.x*=distance;offset.y*=distance;
  int x=(int)((float)center.x+offset.x);
  int y=(int)((float)center.y+offset.y);
  _STL::map<int,int>::iterator b=buttons.find(i);
  if(b!=buttons.end()) {
   const Coord2D *result=((RadialAptPlayerView*)g_bfmeAptWindowManager)->getScale();
   Coord2D factor;factor.x=result->x;factor.y=result->y;
   ((Rva005C6599*)b->second)->rva005C6599((float)x*factor.x,(float)y*factor.y);
  }
  RadialIntPoint location;location.x=x-extent.x/2;location.y=y-extent.y/2;
  position(i,location,extent);
  rotateRadialDirection(dir,step);
  enable(i,(float)elapsed>=0.0f);
 }
 if((float)elapsed>radialAnimationDuration)active=false;
}

// Native 005C674A..005C6A40 is thiscall with no arguments; the WB Draw name remains a lead.
// Operand and alias evidence: reverse/attempt_support/rva005c674a-20261019.md.
