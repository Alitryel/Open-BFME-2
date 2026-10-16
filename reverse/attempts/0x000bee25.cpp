// ?rva000BEE25@Rva000B8F5AOuter@@QAEXPAXMHHH@Z
// partial score=0.9240816136964737 date=2026-10-16
// stlport
// cl: /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/shims/bfmealloc /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii
// Primary semantic references: pinned BF1 575ba2b04 ZH W3DModelDraw::doDrawModule
// completion/state selection and WW3D animobj.cpp::Compute_Current_Frame.
// Target-specific three-slot animation/blend handling is independently present
// in named WB944C80 W3DScriptedModelDraw::processAnimations and native BFDFE.
// Every accessed layout below is a scoped native ABI view; original field and
// secondary class names are unknown. Existing address-derived adjustment and
// state-application keys preserve their opaque argument contracts.
// The local completion function is compiled together with its caller: retail
// proves ECX object / ESI slot / caller-cleaned bool stack ABI, chosen by MSVC
// for this file-static C++ function. No ABI emulation or assembly is used.
// Volatile existing last-frame operand in the backward loop preserves retail's
// multiply then add and stack homes, without introducing an extra memory read.
// Named ping-pong intermediate and per-branch blend stores preserve native order;
// forceinline drawable getter retains pause payload DL and saved vtable EAX.
#include <math.h>
// File-static float min/max used by the frame-limit clamps below. MSVC emits
// them out of line (B2B87 min, B2B95 max, 14B each, the only copies in the
// image, no callers) with its private XMM0 + stack float ABI, beside this
// unit's other static helper B2E4C. Original names unknown.
static inline float Rva000B2B87FloatMin(float a,float b){return a<b?a:b;}
static inline float Rva000B2B95FloatMax(float a,float b){return a>b?a:b;}
extern int g_bfmeDisplayAnimationSyncClock;
class WW3D{static unsigned SyncTime,PreviousSyncTime;public:static unsigned Delta(){return SyncTime-PreviousSyncTime;}};
class AnimationMotion{public:virtual void v0();virtual void v1();virtual void v2();virtual void v3();virtual void v4();virtual int NumFrames();virtual float FrameRate();};
class RenderAnimationObj{public:virtual void v0();virtual void v1();virtual void v2();virtual int ClassID();};
class PauseAnimationIface{public:
virtual void v0();virtual void v1();virtual void v2();virtual void v3();virtual void v4();virtual void v5();virtual void v6();virtual void v7();virtual void v8();virtual void v9();virtual void v10();virtual void v11();virtual void v12();virtual void v13();virtual void v14();virtual void v15();virtual void v16();virtual void v17();virtual void v18();virtual void v19();virtual void v20();virtual void v21();virtual void v22();virtual void v23();virtual void v24();virtual void v25();virtual void v26();virtual void v27();virtual void Pause(bool);};

struct AnimSlot{AnimationMotion*motion;float frame,previous,unused;int mode,direction;bool completed,flag;char pad[2];};
static __declspec(noinline) bool Rva000B2E4CComplete(RenderAnimationObj*obj,AnimSlot*s,bool finish){
 if(obj && obj->ClassID()==25 && s->motion){
 switch(s->mode){case 0:case 1:case 3:case 5:return finish?s->completed:false;case 2:if(s->frame>=s->motion->NumFrames()-1.0f)return true;return false;case 6:if(s->frame<=0.0f)return true;return false;}
 }return true;
}
class Rva000B4BED{public:void*rva000B4BED(const void*);};
class Rva0027532F{public:bool rva0027532F(bool);};
class Rva000B3C61{public:void rva000B3C61(int);void rva000B3CCF(int,int);};
class Rva000B3A68{public:unsigned char rva000B3A68();};
struct Arg000B5A72;
// BFE24 calls the recovered distance-opacity provider at B5A72. Its existing
// neutral argument type names the ABI only; this view does not assert layout.
class Rva000B5C41{public:void rva000B5C41();void rva000B5A72(Arg000B5A72*);}; // rva000B5A72 rowed 0x000B5A72
class Rva000B7074{public:void rva000B7074();};
class ModelConditionFlags{public:bool rva000B3EB3()const;private:unsigned bits[19];};
struct ModelStateView{int pad;ModelConditionFlags flags;char rest[0x5c-0x50];unsigned stateFlags;};
struct ModelDataView{char pad[0x6b];bool requirePower;};
__forceinline unsigned char Flag(unsigned value){return (value>>5)&1;}
class Rva000B8F5AOuter{public:bool rva000BF9FC(void*,bool,int);void rva000BEE25(void*,float,int,int,int);};
class HAnimClass;
class W3DScriptedModelDraw{public:void rva000B5D7F(HAnimClass*,unsigned char,int,float,float,float,unsigned char,float);void processAnimations();__forceinline Rva0027532F*GetDrawable(){return drawable;}
 char pad0[4];ModelDataView*data;Rva0027532F*drawable;char padc[0xc];ModelStateView*state;
 char pad1c[0x44-0x1c];int whichAnimation;bool changed;char pad49[7];RenderAnimationObj*render;
 char pad54[0x90-0x54];float blend,blendTotal,speed,multiplier;char pada0[0xb8-0xa0];unsigned lastSync;char padbc[0x110-0xbc];AnimSlot slots[3];
 char pad164[0x17c-0x164];char signature[0x4c];char pad1c8[3];bool transition;int nextState;char pad1d0[0x25c-0x1d0];bool firstFrame;char pad25d[0x28c-0x25d];bool pending;
 char pad28d[0x2d8-0x28d];bool reselect;
};
void W3DScriptedModelDraw::processAnimations(){
 if(!render || !state)return;
 ModelDataView*module=data;
 ((Rva000B5C41*)this)->rva000B5A72((Arg000B5A72*)module);
 if(!slots[0].motion && !slots[1].motion){
  if(transition){void*next=((Rva000B4BED*)module)->rva000B4BED(signature);if(next){pending=false;((Rva000B8F5AOuter*)this)->rva000BF9FC(next,0,0);}transition=false;nextState=0;}return;
 }
 unsigned delta=(unsigned)g_bfmeDisplayAnimationSyncClock-lastSync;lastSync=g_bfmeDisplayAnimationSyncClock;
 if(firstFrame){firstFrame=false;delta=WW3D::Delta();}
 ((PauseAnimationIface*)((char*)this+0xc))->Pause(!GetDrawable()->rva0027532F(module->requirePower));
 if(!slots[0].motion && slots[1].motion){
  ((Rva000B3C61*)this)->rva000B3CCF(0,1);
  if(slots[2].motion){
   ((Rva000B3C61*)this)->rva000B3CCF(1,2);
   float limit=slots[1].unused;
   float duration;
   if(limit>0.0f){float last=slots[1].motion->NumFrames()-1.0f;duration=Rva000B2B95FloatMax(1.0f,Rva000B2B87FloatMin(limit,last));}
   else{float last=slots[1].motion->NumFrames()-1.0f;duration=Rva000B2B95FloatMax(1.0f,Rva000B2B87FloatMin(5.0f,last));}
   blend=blendTotal=duration;
  }
 }
 for(int i=0;i<3;++i){AnimSlot&s=slots[i];if(s.motion){
  float step=s.motion->FrameRate()*multiplier*speed*delta*0.001f;
  float last=s.motion->NumFrames()-1.0f;
  s.previous=s.frame;s.completed=false;
  switch(s.mode){
  case 1:s.frame=step+s.frame;if(s.frame>last){s.frame-=int(s.frame/last)*last;s.completed=true;}break;
  case 2:s.frame=step+s.frame;if(s.frame>last){s.frame=last;s.completed=true;}break;
  case 3:{float frame=s.frame+s.direction*step;s.frame=frame;if(s.direction==1){if(frame>last){s.direction=-1;float repeated=int(frame/last)*last;repeated+=last;s.frame=repeated-frame;s.completed=true;}}else if(s.frame<0.0f){int repeats=(int)(fabs((double)s.frame)/last);if(repeats>0)s.frame+=repeats*last;s.frame=-s.frame;s.direction=1;s.completed=true;}break;}
  case 5:{s.frame-=step;if(s.frame<0.0f){float repeated=(int)(fabs((double)s.frame)/last)*(*(volatile float*)&last);repeated+=last;s.frame+=repeated;s.completed=true;}break;}
  case 6:s.frame-=step;if(s.frame<0.0f){s.frame=0.0f;s.completed=true;}break;
  }
 }}
 if(slots[0].motion && slots[1].motion){
  float step=slots[1].motion->FrameRate()*multiplier*speed*delta;
  blend-=step*0.001f;
  if(blend<0.0f){((Rva000B3C61*)this)->rva000B3CCF(0,1);if(slots[2].motion){
   ((Rva000B3C61*)this)->rva000B3CCF(1,2);
   float limit=slots[1].unused;
   if(limit>0.0f){float last=slots[1].motion->NumFrames()-1.0f;blend=blendTotal=Rva000B2B95FloatMax(1.0f,Rva000B2B87FloatMin(limit,last));}
   else{float last=slots[1].motion->NumFrames()-1.0f;blend=blendTotal=Rva000B2B95FloatMax(1.0f,Rva000B2B87FloatMin(5.0f,last));}
  }else blend=0.0f;}
 }
 if(!((Rva000B3A68*)this)->rva000B3A68() && Rva000B2E4CComplete(render,&slots[0],transition) && render && state && whichAnimation!=-1){
  if(transition){void*next=((Rva000B4BED*)module)->rva000B4BED(signature);if(next){nextState=0;pending=false;((Rva000B8F5AOuter*)this)->rva000BF9FC(next,0,0);if(!nextState)transition=false;return;}else{transition=false;nextState=0;}}
  ModelStateView*cur=state;
  if(!cur->flags.rva000B3EB3())((Rva000B8F5AOuter*)this)->rva000BEE25(cur,-1.0f,0,0,0);
  else if(Flag(cur->stateFlags)){((Rva000B8F5AOuter*)this)->rva000BEE25(cur,-1.0f,0,0,0);changed=true;}
 }
 if(reselect){reselect=false;((Rva000B8F5AOuter*)this)->rva000BEE25(0,-1.0f,0,0,0);}
 ((Rva000B5C41*)this)->rva000B5C41();((Rva000B7074*)this)->rva000B7074();
}

// Target BEE25..BF7E8/WB92BE60: BFME2 extends the ZH adjustAnimation
// selection spine with script transitions, three lanes and weapon timing.
#include "ascii_string.h"
#include <vector>
class Debug {public:class Format {public:Format(const char*,...);char text[512];};};
class AdjustReport {public:
 virtual void s0();virtual void s1();virtual void s2();virtual void s3();virtual void s4();virtual void s5();virtual void s6();virtual void s7();virtual void s8();virtual void s9();virtual void s10();virtual void s11();virtual void s12();virtual void s13();virtual AdjustReport*text(const char*);virtual void s15();virtual void s16();virtual void s17();virtual void s18();virtual void finish(int);
 AdjustReport&operator<<(const Debug::Format&v){text((const char*)&v);return *this;}
};
class AdjustDebug {public:
 virtual void s0();virtual void s1();virtual void s2();virtual void s3();virtual void s4();virtual void s5();virtual void s6();virtual void s7();virtual void s8();virtual void s9();virtual void s10();virtual void s11();virtual void s12();virtual void s13();virtual void s14();virtual void s15();virtual void s16();virtual void s17();virtual void s18();virtual void s19();virtual void s20();virtual void s21();virtual void s22();virtual void s23();virtual void begin();virtual void s25();virtual void s26();virtual AdjustReport*report(int,int,int);
};
extern Debug*theDebug;bool bfmeRva000387C0();void _bfme_debugRecordCallsite(int);
#define ADDBG ((AdjustDebug*)theDebug)
#define ADSTART() _bfme_debugRecordCallsite(1);ADDBG->begin()
struct Coord3D;enum WeaponSlotType {WS0};enum WeaponStatus {WSTATUS0};
class Weapon {public:WeaponStatus computeStatus(bool*)const;int getPreAttackDelay(const class Object*,const Object*,const Coord3D*)const;int rva002C9D3B(const Object*,unsigned)const;};
class Rva002C9504BinarySubField {public:int get()const;};
struct AdjustTemplate {char pad[0x64];AsciiString name;};
class Object {public:Weapon*getCurrentWeapon(WeaponSlotType*);char pad[4];AdjustTemplate*templ;};
struct AdjustDrawable {char pad[0xfc];Object*object;__forceinline Object*getObject()const{return object;}};
struct Rva00334133Context;
class LuaScriptEngine {public:AsciiString rva00334133(const char*,unsigned long,Rva00334133Context*);};extern LuaScriptEngine*TheLuaScriptEngine;
class Rva000B7539 {public:~Rva000B7539();AsciiString previous,transition,animation;void*source;float fraction;bool finish;Rva000B7539():source(0),fraction(0),finish(false){} };
class Rva000B4926 {public:const AsciiString&rva000B4926()const;};
class HTreeClass;
class Rva000BE027Anim {public:HTreeClass*rva000BE027(const AsciiString&,const AsciiString&,bool,int);};
class Rva000B9A0E {public:void rva000B9A0E(void*,int,int);};
class Rva000B49F9 {public:unsigned char rva000B49F9();};
class AnimConditionInfo {public:int rva000B495B();int pickRandomAnimation(int,int);};
int __stdcall Rva000B3E96Get(int);
float GetGameClientRandomValueReal(float,float,char*,int);
struct AdjustAnimation {char names[12];AsciiString name,previousName;char pad14[4];float duration;int mode;float blend,minSpeed,maxSpeed;unsigned char flag;bool weaponTiming;char pad2e[0x40-0x2e];};
template<class T>struct AdjustVector {T*first,*last,*capacity;int size()const{return last-first;}T&operator[](int i){return first[i];}};
struct AdjustState {AsciiString name;char pad4[0x50-4];_STL::vector<AdjustAnimation>animations;unsigned flags;char pad60[12];AsciiString script;char pad70[0x9c-0x70];bool restart,allowRepeat;char pad9e[0xf8-0x9e];};
struct AdjustData {char pad[0x24];AdjustState*first,*last;char pad2c[0x134-0x2c];bool numbered,fixedNumber;};
struct AdjustModel {char pad[0x58];AsciiString name;char pad5c[0x14];AsciiString variant;};
class AdjustRender {public:
virtual void s0();virtual void s1();virtual void s2();virtual void s3();virtual void s4();virtual void s5();virtual void s6();virtual void s7();virtual void s8();virtual void s9();virtual void s10();virtual void s11();virtual void s12();virtual void s13();virtual void s14();virtual void s15();virtual void s16();virtual void s17();virtual void s18();virtual void s19();virtual void s20();virtual void s21();virtual void s22();virtual void s23();virtual void s24();virtual void s25();virtual void s26();virtual void s27();virtual void s28();virtual void s29();virtual void s30();virtual void s31();virtual void s32();virtual void s33();virtual void s34();virtual void s35();virtual void s36();virtual void s37();virtual void s38();virtual void s39();virtual void s40();virtual void s41();virtual void s42();virtual void s43();virtual void s44();virtual void s45();virtual void clear();};
class AdjustVirtual {public:virtual void s0();virtual void s1();virtual void s2();virtual void s3();virtual void s4();virtual void s5();virtual void s6();virtual void s7();virtual void s8();virtual void s9();virtual void s10();virtual void s11();virtual void s12();virtual void s13();virtual void s14();virtual void s15();virtual void s16();virtual void s17();virtual void s18();virtual void s19();virtual void s20();virtual void s21();virtual void s22();virtual void s23();virtual void s24();virtual void s25();virtual void s26();virtual void s27();virtual void s28();virtual void s29();virtual void s30();virtual void s31();virtual void s32();virtual void s33();virtual void s34();virtual void s35();virtual void s36();virtual void s37();virtual void s38();virtual void s39();virtual void s40();virtual void s41();virtual void s42();virtual void s43();virtual void s44();virtual void s45();virtual void s46();virtual void s47();virtual void s48();virtual void s49();virtual void s50();virtual void s51();virtual void s52();virtual void s53();virtual void s54();virtual void s55();virtual void s56();virtual void s57();virtual void s58();virtual void s59();virtual void s60();virtual void s61();virtual void s62();virtual void s63();virtual void s64();virtual void s65();virtual int maximum();virtual int randomFrame(int);};
class AdjustMotion {public:virtual void release();virtual void s1();virtual void s2();virtual void s3();virtual void s4();virtual int frames();int refs;};
struct AdjustView {__forceinline AdjustDrawable*getDrawable()const{return drawable;}void*vptr;AdjustData*data;AdjustDrawable*drawable;char padc[8];AdjustModel*model;AdjustState*state;char pad1c[0x44-0x1c];int selected;char pad48[8];AdjustRender*render;char pad54[0x88-0x54];int lastSelected;char pad8c[0xbc-0x8c];int numbering;char padc0[0x110-0xc0];AnimSlot slots[3];char pad164[0x1cb-0x164];bool transition;AdjustState*next;char pad1d0[0x28c-0x1d0];bool sequential;};
struct Rva000B2BE5Src
{
	char pad[0x114];
	unsigned char flag;
};


class GameLODManager;
extern GameLODManager *TheGameLODManager;

struct Rva000B2BA3LOD
{
	char m_pad0000[0x1774];
	int m_mode1774; // +0x1774
};

int __cdecl Rva000B2BA3Get(const Rva000B2BE5Src *p, bool *forced)
{
	int mode = reinterpret_cast<Rva000B2BA3LOD *>(TheGameLODManager)->m_mode1774;
	if (mode != 3 && p && (p->flag & 0x20))
	{
		if (forced)
			*forced = true;
		mode = 0;
	}
	switch (mode)
	{
	case 0:
		return 2;
	case 1:
		return 1;
	case 2:
	case 3:
		return 0;
	}
	return 0;
}

// ?Rva000B2BE5Get@@YAHPBURva000B2BE5Src@@H@Z, retail 0x000B2BE5..0x000B2BFF
// (26 bytes), cdecl: 2 for a drawable with the 0x20 status bit, else the
// fallback (callers 0x000BF33F 0x000BF4D2 0x000BF996 0x000C2ECC).
int __cdecl Rva000B2BE5Get(const Rva000B2BE5Src *p, int fallback)
{
	if (p && (p->flag & 0x20))
		return 2;
	return fallback;
}

struct AdjustLOD {char pad[0x1788];int limit;};
class HAnimClass;

static __forceinline unsigned char AdjustBit0(unsigned f){return f&1;}
static __forceinline unsigned char AdjustBit1(unsigned f){return (f>>1)&1;}
static __forceinline unsigned char AdjustBit2(unsigned f){return (f>>2)&1;}
void Rva000B8F5AOuter::rva000BEE25(void *old,float fraction,int preserve,int force,int reset){
 AdjustView*s=(AdjustView*)this;
 if(!s->state||!s->model)return;
 Object*object=s->getDrawable()->getObject();AdjustData*data=s->data;
 bool scripted=!((StringBase<char>*)&s->state->script)->isEmpty();
 int oldIndex=s->selected;
 if((unsigned char)reset){old=0;oldIndex=-1;s->lastSelected=0;}
 int count=s->state->animations.size();AdjustAnimation*info=0;
 if(count<=0&&!scripted){
  if(s->render){((Rva000B3C61*)this)->rva000B3C61(0);((Rva000B3C61*)this)->rva000B3C61(1);s->render->clear();}s->selected=-1;return;
 }
 if(!(unsigned char)preserve){
  if(s->render&&count==0){((Rva000B3C61*)this)->rva000B3C61(0);((Rva000B3C61*)this)->rva000B3C61(1);s->render->clear();}
  s->selected=-1;
  if(scripted){
   int chosen=-1;Rva000B7539 context;context.source=s->getDrawable();
   if(((AdjustState*)old)&&oldIndex>=0&&oldIndex<count)context.animation=((AdjustState*)old)->animations[oldIndex].previousName;
   if(((AdjustState*)old)&&((AdjustState*)old)!=s->state){context.previous=((AdjustState*)old)->name;context.fraction=fraction;}
   AsciiString result=TheLuaScriptEngine->rva00334133(s->state->script.str(),s->state->script.getLength(),(Rva00334133Context*)&context);
   if(s->transition&&!context.transition.isEmpty()){s->transition=false;s->next=0;}
   if(!context.transition.isEmpty()&&!s->transition){
    AdjustState*it;
    for(it=data->first;it!=data->last;++it){if(it->name.compareNoCase(context.transition)==0){s->transition=true;s->next=s->state;s->sequential=false;rva000BF9FC(it,false,0);return;}}
    if(bfmeRva000387C0()){ADSTART();const char*objectName=object?object->templ->name.str():"NoObject";const char*stateName=context.transition.str();AdjustReport*out=ADDBG->report(0,0,0);(*out<<Debug::Format("W3DScriptedModelDraw::adjustAnimation: Unable to find transition state named '%s' in '%s'",stateName,objectName)).finish(2);}
   }
   AnimSlot*slot=&s->slots[0];if(s->slots[1].motion)slot=&s->slots[1];
   if(((AdjustState*)old)&&context.finish&&!Rva000B2E4CComplete((RenderAnimationObj*)s->render,slot,false)){
    s->transition=true;s->next=s->state;slot->completed=false;
    ((Rva000B9A0E*)s->state)->rva000B9A0E(s->getDrawable()->getObject(),2,0);s->state=((AdjustState*)old);
    ((Rva000B9A0E*)s->state)->rva000B9A0E(s->getDrawable()->getObject(),1,0);s->selected=0;return;
   }
   if(!result.isEmpty()){
    for(int i=0;i<count;++i){if(s->state->animations[i].name.compareNoCase(result)==0){chosen=i;break;}}
    if(chosen==-1){if(bfmeRva000387C0()){ADSTART();ADDBG->report(0,0,0)->text("Cannot find animation named ")->text(result.str())->finish(2);}s->selected=0;}else s->selected=chosen;
   }
  }
  if(count<1){s->selected=-1;return;}
  if(count==1)s->selected=0;
  else if(s->sequential&&count>1)s->selected=(oldIndex+1)%count;
  else if(s->selected<0){int avoid=-1;if(((AdjustState*)old)==s->state&&!s->state->allowRepeat)avoid=oldIndex;
   int maximum=((AdjustVirtual*)this)->maximum();AnimConditionInfo*current=(AnimConditionInfo*)s->state;if(((Rva000B49F9*)current)->rva000B49F9())maximum=9999;
   s->selected=current->pickRandomAnimation(avoid,maximum);
  }
 }
 info=&s->state->animations[s->selected];
 if(!(unsigned char)force&&!(unsigned char)preserve&&((AdjustState*)old)==s->state&&!s->state->restart&&s->selected==oldIndex){if(((Rva000B3A68*)this)->rva000B3A68()||!Rva000B2E4CComplete((RenderAnimationObj*)s->render,&s->slots[0],false))return;}
 AdjustMotion*motion=0;
 if(data->fixedNumber)motion=(AdjustMotion*)((Rva000BE027Anim*)&s->state->animations[s->selected])->rva000BE027(s->model->name,s->model->variant,true,Rva000B2BA3Get((Rva000B2BE5Src*)s->getDrawable(),0));
 else if(data->numbered)motion=(AdjustMotion*)((Rva000BE027Anim*)&s->state->animations[s->selected])->rva000BE027(s->model->name,s->model->variant,true,Rva000B2BE5Get((Rva000B2BE5Src*)s->getDrawable(),s->numbering));
 else motion=(AdjustMotion*)((Rva000BE027Anim*)&s->state->animations[s->selected])->rva000BE027(s->model->name,s->model->variant,false,0);
 if(!motion&&bfmeRva000387C0()){ADSTART();const char*objectName=object?object->templ->name.str():"NoObject";const char*modelName=s->model->name.str();const char*animName=((Rva000B4926*)&s->state->animations[s->selected])->rva000B4926().str();AdjustReport*out=ADDBG->report(0,0,0);(*out<<Debug::Format("Unable to locate asset: %s for Model %s in %s",animName,modelName,objectName)).finish(2);}
 if(!motion&&(unsigned)s->state->animations.size()>1){
  for(unsigned i=0;i<(unsigned)s->state->animations.size();++i){if(i!=(unsigned)s->selected){
   if(data->fixedNumber)motion=(AdjustMotion*)((Rva000BE027Anim*)&s->state->animations[i])->rva000BE027(s->model->name,s->model->variant,true,Rva000B2BA3Get((Rva000B2BE5Src*)s->getDrawable(),0));
   else if(data->numbered)motion=(AdjustMotion*)((Rva000BE027Anim*)&s->state->animations[i])->rva000BE027(s->model->name,s->model->variant,true,Rva000B2BE5Get((Rva000B2BE5Src*)s->getDrawable(),s->numbering));
   else motion=(AdjustMotion*)((Rva000BE027Anim*)&s->state->animations[i])->rva000BE027(s->model->name,s->model->variant,false,0);
   if(motion){s->selected=i;break;}
  }}
 }
 s->lastSelected=s->selected;
 if(!motion)return;
 int start=0,direction=1;
 if((unsigned char)preserve){start=(int)s->slots[0].frame;direction=s->slots[0].direction;}
 else {
  if(((AnimConditionInfo*)s->state)->rva000B495B()==6||((AnimConditionInfo*)s->state)->rva000B495B()==5){start=motion->frames()-1;direction=-1;}
  if((unsigned char)force&&fraction>=0.0)start=(int)(fraction*motion->frames());
  else if(AdjustBit0(s->state->flags)){if(((Rva000B49F9*)s->state)->rva000B49F9()&&((AdjustLOD*)TheGameLODManager)->limit>0)start=Rva000B3E96Get(motion->frames());else start=((AdjustVirtual*)this)->randomFrame(motion->frames());}
  else if(AdjustBit1(s->state->flags))start=0;
  else if(AdjustBit2(s->state->flags))start=motion->frames()-1;
  else if((s->state->flags&0x1d0)&&((AdjustState*)old)&&((AdjustState*)old)!=s->state&&(((AdjustState*)old)->flags&0x1d0)&&(s->state->flags&((AdjustState*)old)->flags&0x1d0)&&fraction>=0.0)start=(int)(fraction*motion->frames());
 }
 float rate=1.0f;
 if(info->minSpeed!=1.0f||info->maxSpeed!=1.0f)rate=GetGameClientRandomValueReal(info->minSpeed,info->maxSpeed,"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngineDevice\\Source\\W3DDevice\\GameClient\\Drawable\\W3DScriptedModelDraw.cpp",0x1114);
 if(info->weaponTiming&&object){Weapon*w=object->getCurrentWeapon(0);if(w){int duration=(int)(info->duration*0.005f),time=duration;if(w->computeStatus(0)==3)time=((Rva002C9504BinarySubField*)w)->get();else{int before=w->getPreAttackDelay(object,0,0);time=before;time+=w->rva002C9D3B(object,0);}rate=(float)duration/(float)time;}}
 float blend=info->blend;int mode=info->mode;
 if(s->sequential){rate=1;start=0;blend=0;if(mode==2&&count==1)mode=1;}
 float end=(float)direction*-0.00001f;end+=(float)start;
 ((W3DScriptedModelDraw*)this)->rva000B5D7F((HAnimClass*)motion,info->flag,mode,blend,(float)start,end,0,rate);
 if(--motion->refs==0)motion->release();
}
