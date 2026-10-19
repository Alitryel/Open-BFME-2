// ?updateFormationPreview@InGameUI@@QAEXXZ
// partial score=0.7090909090909091 date=2026-10-19
// ?updateFormationPreview@InGameUI@@QAEXXZ
// partial score=0.057 date=2026-10-17
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// stlport
// Native 002A4E1F..002A57BD and WB 00DC0B00 establish the complete preview flow.
// Native selection/hash behavior and offsets differ from the debug-build body.
#define _STLP_USE_STATIC_LIB
#define _STLP_USE_MALLOC
#define _CRTIMP
#define COORD2D_VIEW_DTOR
#include "../../Code/Libraries/Include/Lib/Coord2DCtorView.h"
#include "../../Code/Libraries/Include/Lib/Coord3D.h"
#include "../../Code/Libraries/Include/Lib/ICoord2D.h"
#include "../../Code/Libraries/Include/Lib/RGBColor.h"
#include <list>
#include <vector>
#include <string>
extern "C" double __cdecl sqrt(double);
extern "C" double __cdecl cos(double);
extern "C" double __cdecl sin(double);

class Thing { public: void setOrientation(float); };
class Drawable {
public:
 void setPosition(const Coord3D *);
 char prefix[0xB0]; float opacity;
};
struct ShadowView { char prefix[8]; Coord3D position; char gap14[12]; float angle; char gap24[0x58-0x24]; float width,height; };
class Rva0029A469 {
public:
 ShadowView *shadow;
 void rva0029A469(float);
 __forceinline float width() const { return shadow?shadow->width:0.0f; }
 __forceinline float height() const { return shadow?shadow->height:0.0f; }
 void setPosition(const Coord3D &p) { if(shadow)shadow->position=p; }
 void setOrientation(float a) { if(shadow)shadow->angle=a; }
 void setWidth(float w) { if(shadow){Coord2D size(w,shadow->height);shadow->width=size.x;shadow->height=size.y;} }
};
class ThingTemplate {public: char prefix[0x18]; float width;};
class Object {public:char prefix[0x438];unsigned char flags;};
class Player {public:char prefix[0x280];int color;};
class PlayerList {public:char prefix[0x10];Player *localPlayer;};
extern PlayerList *ThePlayerList;
class GameLogic {public:Object *findObjectByID(int);};
extern GameLogic *TheGameLogic;
template<int N>class PreviewSlots:public PreviewSlots<N-1>{public:virtual void slot(char(*)[N]);};
template<>class PreviewSlots<0>{};
class GameClient:public PreviewSlots<31>{public:virtual unsigned getFrame();};
extern GameClient *TheGameClient;
extern int BfmeClientFramesPerSecond;

struct IdNode {IdNode *next,*prev;int id;};
class Rva0029FB3BMember {public: IdNode *head; void *init(void *);};
class PoolMember {public:void Rva00268902() throw();};
class Rva001EB984Member {public:void *init(void *);};
class Rva001EB769 {public:void rva001EB769() throw();};
class SelectedIDs:public Rva0029FB3BMember {
public:
 SelectedIDs(const char &a){init((void*)&a);}
 ~SelectedIDs() throw(){reinterpret_cast<PoolMember*>(this)->Rva00268902();}
};
namespace _STL {
template<> list<Object*>::iterator list<Object*>::insert(list<Object*>::iterator,Object *const&);
}
class Rva001EB130Holder {public:void *head;};
class ObjectList:public Rva001EB130Holder {
public:
 ObjectList(const char &a){reinterpret_cast<Rva001EB984Member*>(this)->init((void*)&a);}
 ~ObjectList() throw(){reinterpret_cast<Rva001EB769*>(this)->rva001EB769();}
 void push_back(Object *const&o){_STL::list<Object*> &l=*reinterpret_cast<_STL::list<Object*>*>(this);l.insert(l.end(),o);}
};
struct Rva00422544List;
class Rva004233F5 {public:int rva004233F5(Rva00422544List*,float);};
struct Placement32 {ThingTemplate **type;int object;char gap8[8];ICoord2D position;char tail[8];};
class Formation {public:Placement32 *first,*last,*limit;};
class FormationAssistant {
public:
 char prefix[0x10];ThingTemplate *templates[4];char gap20[0x2C-0x20];float threshold,delay;
 bool getValidSelectedObjectsForPlayer(Player*,Rva0029FB3BMember*);
 Formation *rva00424E77(int,Rva001EB130Holder*,const Coord3D*);
};
class Rva0022AD10Subsystem;
extern Rva0022AD10Subsystem *TheFormationAssistant;
class Rva00423FBDThis {public:void Delete(_STL::basic_string<char,_STL::char_traits<char>,_STL::allocator<char> >*);};
class InGameUI : public PreviewSlots<51> {
public:
 class FormationPreviewPoolObject;
 virtual bool formationMode();
 Coord2D rva0029D9F9();
 void updateFormationPreview();
private:
 char prefix[0x59C-4];int selectionHash;
 struct BfmeE12View {int x,y;FormationPreviewPoolObject *pool;} *first,*last,*limit;
 unsigned expires;bool active;char gap5B1[3];FormationPreviewPoolObject *arrows[4];
 char gap5C4[0x98C-0x5C4];bool valid,directionValid;char gap98E[2];Coord3D start,end;Coord2D direction;int formation;
};
class InGameUI::FormationPreviewPoolObject {public:Drawable *drawable;Rva0029A469 *decal;bool assigned;};
class Rva002A3DD3 {
public:
 void rva002A3E24();
 void clearFormationPreviewDrawables();
 InGameUI::FormationPreviewPoolObject *rva002A3E5A(ThingTemplate*);
 void rva002A4BFC(Object*,ThingTemplate*,const ICoord2D*,RGBColor);
};
struct BfmeE12 {int id;float key,z;};
namespace _STL {template<> void vector<BfmeE12>::reserve(unsigned);}
static __forceinline float lengthSq(const Coord2D &p){return p.x*p.x+p.y*p.y;}
static __forceinline float length(const Coord2D &p){return (float)sqrt(lengthSq(p));}
static __forceinline void normalize(Coord2D &p){float inv=1.0f/length(p);p.x*=inv;p.y*=inv;}
static __forceinline void scale(Coord2D &p,float s){p.x*=s;p.y*=s;}
struct PreviewMatrix {
 float row[3][4];
 __forceinline PreviewMatrix(float angle) {
  float c=(float)cos(angle),s=(float)sin(angle);
  float x=0.0f,y=0.0f,z=1.0f;
  row[0][0]=x*x+(1.0f-x*x)*c;
  row[0][1]=x*y*(1.0f-c)-s*z;
  row[0][2]=z*x*(1.0f-c)+s*y;
  row[0][3]=0.0f;
  row[1][0]=x*y*(1.0f-c)+s*z;
  row[1][1]=y*y+(1.0f-y*y)*c;
  row[1][2]=y*z*(1.0f-c)-s*x;
  row[1][3]=0.0f;
  row[2][0]=z*x*(1.0f-c)-s*y;
  row[2][1]=y*z*(1.0f-c)+s*x;
  row[2][2]=z*z+(1.0f-z*z)*c;
  row[2][3]=0.0f;
 }
 void transform(float x,float y,float &outX,float &outY)const {
  outX=row[0][0]*x+row[0][1]*y+row[0][2]*0.0f+row[0][3];
  outY=row[1][0]*x+row[1][1]*y+row[1][2]*0.0f+row[1][3];
 }
};

void InGameUI::updateFormationPreview() {
 Rva002A3DD3 *owner=reinterpret_cast<Rva002A3DD3*>(this);
 if(!formationMode()) {
  if((unsigned)(last-first)>0) {
   unsigned now=TheGameClient->getFrame();
   if(expires>now) {if(expires-now>500)expires=now;return;}
   float alpha=1.0f-(float)(now-expires)*(1.0f/(BfmeClientFramesPerSecond*0.5f));
   if(alpha<=0.0f){owner->rva002A3E24();return;}
   float one=1.0f;
   const float &clamped=alpha<one?alpha:one;alpha=clamped;
   for(BfmeE12View *it=first;it!=last;++it) {
    Drawable *d=it->pool?it->pool->drawable:0;
    if(d)d->opacity=alpha;
    Rva0029A469 *decal=it->pool?it->pool->decal:0;
    if(decal)decal->rva0029A469(alpha);
   }
   for(int i=0;i<4;++i)if(arrows[i] && arrows[i]->decal)arrows[i]->decal->rva0029A469(alpha);
  }
  return;
 }
 const Coord2D facing=rva0029D9F9();
 float facingSq=lengthSq(facing);
 float distance=length(facing);

 if(!active && facingSq<reinterpret_cast<FormationAssistant*>(TheFormationAssistant)->threshold*reinterpret_cast<FormationAssistant*>(TheFormationAssistant)->threshold) {
  float delay=reinterpret_cast<FormationAssistant*>(TheFormationAssistant)->delay;
  if((float)(TheGameClient->getFrame()-expires)/BfmeClientFramesPerSecond<delay)return;
 }
 active=true;
 char allocator;
 SelectedIDs ids(allocator);
 reinterpret_cast<FormationAssistant*>(TheFormationAssistant)->getValidSelectedObjectsForPlayer(ThePlayerList->localPlayer,&ids);
 ObjectList objects(allocator);
 int hash=0;
 for(IdNode *it=ids.head->next;it!=ids.head;it=it->next) {
  int id=it->id;
  hash=((hash&0xF8000000)>>27)^(hash<<5)^id;
  Object *obj=TheGameLogic->findObjectByID(id);
  if(obj && !(obj->flags&1))objects.push_back(obj);
 }
 if(hash!=selectionHash){owner->rva002A3E24();formation=-1;selectionHash=hash;}
 int type=reinterpret_cast<Rva004233F5*>(TheFormationAssistant)->rva004233F5(reinterpret_cast<Rva00422544List*>(&objects),distance);
 if(type!=formation) {
  formation=-1;
  Formation *plan=reinterpret_cast<FormationAssistant*>(TheFormationAssistant)->rva00424E77(type,&objects,&start);
  if(plan) {
   owner->clearFormationPreviewDrawables();valid=true;formation=type;
   reinterpret_cast<_STL::vector<BfmeE12>*>(&first)->reserve(plan->last-plan->first);
   RGBColor color;color.setFromInt(ThePlayerList->localPlayer->color);
   for(Placement32 *it=plan->first;it!=plan->last;++it) {
    Object *obj=TheGameLogic->findObjectByID(it->object);
    if(obj)owner->rva002A4BFC(obj,it->type[1],&it->position,color);
   }
   reinterpret_cast<Rva00423FBDThis*>(TheFormationAssistant)->Delete(reinterpret_cast<_STL::basic_string<char,_STL::char_traits<char>,_STL::allocator<char> >*>(plan));
  } else valid=false;
 }
 if((unsigned)(last-first)>0) {
  float angle=facing.toAngle();
  PreviewMatrix matrix(angle+1.5707964f);
  for(BfmeE12View *it=first;it!=last;++it) {
   float x,y;matrix.transform((float)it->x,(float)it->y,x,y);
   Coord3D pos={start.x+x,start.y+y,start.z};
   Drawable *d=it->pool?it->pool->drawable:0;
   if(d){d->setPosition(&pos);reinterpret_cast<Thing*>(d)->setOrientation(angle);}
   Rva0029A469 *decal=it->pool?it->pool->decal:0;
   if(decal){decal->setPosition(pos);decal->setOrientation(angle-1.5707964f);}
  }
  for(int i=0;i<4;++i)if(!arrows[i]) {
   FormationAssistant *fa=reinterpret_cast<FormationAssistant*>(TheFormationAssistant);
   ThingTemplate *templ=fa->templates[i];if(i==3)templ=fa->templates[2];
   if(templ)arrows[i]=owner->rva002A3E5A(templ);
  }
  float arrowWidth=0.0f,lineWidth=0.0f;
  if(arrows[2] && arrows[2]->decal)arrowWidth=arrows[2]->decal->width();
  if(arrows[1] && arrows[1]->decal)lineWidth=reinterpret_cast<FormationAssistant*>(TheFormationAssistant)->templates[1]->width;
  Coord2D unit(facing);double unitInverse=1.0f/sqrt((double)facingSq);unit.x=(float)(facing.x*unitInverse);unit.y=(float)(facing.y*unitInverse);
  Coord2D side(-facing.y,facing.x);
  float minimum=(lineWidth+arrowWidth)*0.5f;
  float sideSq=lengthSq(side);
  if((float)sqrt((double)sideSq)<minimum){float inverse=1.0f/(float)sqrt((double)sideSq);side.x*=inverse;side.y*=inverse;scale(side,minimum);}
  float offset=30.0f,frontOffset=30.0f;
  if(arrows[1]) {
   offset=arrows[1]->decal->height()*0.5f+30.0f;
   frontOffset=arrows[1]->decal->height()+30.0f;
   Rva0029A469 *decal=arrows[1]->decal;
   if(decal) {
    Coord3D pos={start.x+offset*unit.x,start.y+offset*unit.y,start.z};
    decal->setPosition(pos);decal->setOrientation(angle-1.5707964f);
    float width=length(side)*2.0f-arrowWidth;
    decal->setWidth(width);
   }
  }
  Coord2D tip(side);
  float tipLength=length(tip)-10.0f;
  normalize(tip);scale(tip,tipLength);
  if(arrows[2] && arrows[2]->decal) {
   Rva0029A469 *decal=arrows[2]->decal;
   Coord3D pos={start.x+offset*unit.x+tip.x,start.y+offset*unit.y+tip.y,start.z};
   decal->setPosition(pos);decal->setOrientation(angle+3.1415927f-1.5707964f);
  }
  if(arrows[3] && arrows[3]->decal) {
   Rva0029A469 *decal=arrows[3]->decal;
   Coord3D pos={start.x+offset*unit.x-tip.x,start.y+offset*unit.y-tip.y,start.z};
   decal->setPosition(pos);decal->setOrientation(angle-1.5707964f);
  }
  if(arrows[0]) {
   frontOffset+=arrows[0]->decal->height()*0.5f;
   Rva0029A469 *decal=arrows[0]->decal;
   if(decal) {
    Coord3D pos={start.x+frontOffset*unit.x,start.y+frontOffset*unit.y,end.z};
    decal->setPosition(pos);decal->setOrientation(angle-1.5707964f);
   }
  }
 }
}
