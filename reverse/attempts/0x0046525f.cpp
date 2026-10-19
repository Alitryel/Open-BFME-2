// ?exitObjectViaDoor@OpenContain@@UAEXPAVObject@@W4ExitDoorType@@@Z
// partial score=0.98 date=2026-10-19
// ?exitObjectViaDoor@OpenContain@@UAEXPAVObject@@W4ExitDoorType@@@Z
// partial score=0.985 date=2026-10-16
// W9-O3 2026-10-16: farm best + hatch fixes: g_00E03624 -> rowed datum BfmeAIExitDoorFlag (data_rows), rva0028ACDC row is QAEXH (int) -> (int)&coord cast (was unresolved). Size 1154 vs 1152, nd 12: (1) ai=exitObj->ai load one slot early in branch 1; (2) scale block: retail 'movaps t,50; mulss t,[delta.x/y]' after the target movsd copy, ours loads delta.x/y above the copy (+2 B). Inert: 50*x / x*50 / s local / const-ref s / direct target+=50*d / z-first orders.
// ?exitObjectViaDoor@OpenContain@@UAEXPAVObject@@W4ExitDoorType@@@Z
// partial score=0.985 date=2026-10-15
// ?exitObjectViaDoor@OpenContain@@UAEXPAVObject@@W4ExitDoorType@@@Z
// partial score=0.95 date=2026-10-14
// ?exitObjectViaDoor@OpenContain@@UAEXPAVObject@@W4ExitDoorType@@@Z
// partial score=0.95 date=2026-10-14 (self-contained BFME2-layout TU, same head as
// OpenContainExitObjectInAHurry.cpp; difflib ratio 0.959 vs retail, if-branch exact
// modulo the frame). Levers found: AI *theAI local before the startPosition copy
// (retail loads TheAI first); delta.normalize() then in-place delta.z/x/y*=50 and
// target+=delta (retail products held in xmm1..3); savedGoal x/y/z before delta.
// Remaining: (1) uniform one-DWORD frame shift (sub esp 0x54 vs 0x50): vector#2
// lands at -0x24 overlapping ai's dead home instead of delta's -0x38 slot; declaration
// order, function-level ai and scope moves do not change it; (2) x/y products load
// delta into regs before the movsd copy (retail: movaps 50 + mulss mem after it);
// (3) delta.x fld before/after the goalView load scheduling at the atan2 setup.
// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /I.
// 0x0046525F bank 2026-10-19 (claude-opus-5-5): same residue as the old bank (1154/1152 B) with fewer hacks:
// _ReadWriteBarrier removed (inert: the theAI/pf locals alone fix the getClosestPointOnLand pushes) and both
// goto done replaced by nesting. One hack left: the trailing dead `if (0) throw 1;` that fixes the frame (0x50);
// next step is the landed twin SiegeEngineContain::exitObjectViaDoor 0x47C4F2 recipe (visible
// Rva0035149F vector-copy chain, noinline-inline command wrappers incl. an rva0036EF09 body, throwing
// deallocator, /EHsc /D_STLP_NO_EXCEPTIONS) which removed the same extra frame there. Left: fld/mov swap at
// 0x4654FB and the scale block (retail multiplies delta.x/.y from memory after the target copy).
// Home: OpenContainExitObjectInAHurry.cpp. Scratch: build/nbr/r8/46525f/.
// stlport
#include <vector>
#include "ascii_string.h"
#include "Code/Libraries/Include/Lib/Coord3D.h"
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
namespace _STL {template <> __declspec(noinline) void vector<Coord3D>::push_back(const Coord3D&);}
// /D_CRTIMP= keeps free a direct call; itoa stays an import-slot call.
extern "C" char *(__cdecl *_imp___itoa)(int,char*,int);
enum PathfindLayerEnum {LAYER_GROUND=0};
enum ExitDoorType {DOOR_1=0};
enum CommandSourceType {CMD_FROM_AI=2};
double Rva000422A0Atan2(float,float);
extern bool BfmeAIExitDoorFlag;
class Rva0035149F;
class Matrix3D;
class LocomotorSet;
class ConditionBits {
public:
 unsigned int test(int bit) const{return words[bit>>5]&(1U<<(bit&0x1f));}
 void set(int bit){words[bit>>5]|=1U<<(bit&0x1f);}
 void clear(int bit){words[bit>>5]&=~(1U<<(bit&0x1f));}
 unsigned int words[4];
};
class Thing {public:void setPosition(const Coord3D*);void setOrientation(float);};
class AIUpdateInterface;
class Object:public Thing {
public:
 void rva0028AE6D();
 bool getSingleLogicalBonePosition(const char*,Coord3D*,Matrix3D*) const;
 int rva0028B511() const;
 void rva0028B4CE(PathfindLayerEnum);
 void rva0028AD7C();
 void rva0028ACDC(int);
 bool rva002931BA();
 const Coord3D *getPosition() const{return &position;}
 void *vtable;unsigned char *thingTemplate;char pad8[0x38-8];Coord3D position;float orientation;
 char pad48[0x10c-0x48];ConditionBits conditionBits;char pad11c[0x258-0x11c];AIUpdateInterface *ai;
};
template<class Tag,int N>class Slots:public Slots<Tag,N-1>{public:virtual void gap(Tag*,char(*)[N]);};template<class Tag>class Slots<Tag,1>{public:virtual void gap(Tag*,char(*)[1]);};
class AICommandInterface {public:void rva0036EE16(const Rva0035149F*,Object*,CommandSourceType);void rva0036EF09(const Rva0035149F*,Object*,float,CommandSourceType);};
struct AIGoalView {char pad[0x24];Coord3D goal;};
class AIUpdateInterface:public Slots<AIUpdateInterface,1>{
public:
 void ignoreObstacle(const Object*);
 char pad4[0x20-4];AICommandInterface commands;char pad21[0x30-0x21];AIGoalView *goalView;char pad34[0x148-0x34];Coord3D position148;char pad154[0x178-0x154];unsigned int ignoreCollisionUntil;char pad17c[0x1cc-0x17c];
 LocomotorSet &locomotorSet(){return *(LocomotorSet*)((char*)this+0x1cc);}
};
class Pathfinder {public:void AddObjectToPathfindMap(Object*);bool adjustToPossibleDestination(Object*,const LocomotorSet&,Coord3D*);bool getClosestPointOnLand(const Coord3D*,Object*,Coord3D*);};
class AI {public:char pad[0x10];Pathfinder *pathfinder;};extern AI *TheAI;
extern GameLogic *TheGameLogic;
extern int BfmeLogicFramesPerSecond;
struct OpenContainModuleData {char pad[0x74];int numberOfExitPaths;unsigned int doorOpenTime;};
class OpenContainModule:public Slots<OpenContainModule,1>{public:OpenContainModuleData *moduleData;Object *owner;Object *getObject() const{return owner;}const OpenContainModuleData *getOpenContainModuleData() const{return moduleData;}char padC[0x20-0xc];};
class ContainModuleInterface:public Slots<ContainModuleInterface,41>{public:virtual void removeFromContain(Object*,bool);char pad4[0x10-4];};
class ExitInterface:public Slots<ExitInterface,1>{public:virtual void exitObjectViaDoor(Object*,ExitDoorType);};
class OpenContain:public OpenContainModule,public ContainModuleInterface,public ExitInterface{
public:
 virtual void removeFromContain(Object*,bool);
 virtual void exitObjectViaDoor(Object*,ExitDoorType);
 char pad34[0x6c-0x34];int whichExitPath;unsigned int doorCloseCountdown;
 char pad74[0xd0-0x74];Coord3D rallyPoint;bool rallyPointExists;
};
static __forceinline void concatChar(AsciiString &s,char c)
{
 ((StringBase<char>*)&s)->concat(&c,1);
}
void OpenContain::exitObjectViaDoor(Object *exitObj,ExitDoorType exitDoor)
{
 removeFromContain(exitObj,false);
 Object *me=getObject();
 doorCloseCountdown=getOpenContainModuleData()->doorOpenTime;
 if(doorCloseCountdown){
  if(me->conditionBits.test(22)||!me->conditionBits.test(21)){
   me->conditionBits.clear(22);
   me->conditionBits.set(21);
   me->rva0028AE6D();
  }
 }
 int numberExits=getOpenContainModuleData()->numberOfExitPaths;
 if(numberExits>0){
  AsciiString startBone("ExitStart");
  AsciiString endBone("ExitEnd");
  Coord3D endPosition;
  AIUpdateInterface *ai;
  {
  Coord3D startPosition;
  if(numberExits>1){
   char suffix[8];
   _imp___itoa(whichExitPath,suffix,10);
   if(whichExitPath<10){
    concatChar(startBone,'0');
    concatChar(endBone,'0');
   }
   whichExitPath=whichExitPath%numberExits+1;
   startBone.concat(suffix);
   endBone.concat(suffix);
  }
  me->getSingleLogicalBonePosition(((StringBase<char>*)&startBone)->str(),&startPosition,0);
  me->getSingleLogicalBonePosition(((StringBase<char>*)&endBone)->str(),&endPosition,0);
  float exitAngle=me->orientation;
  exitObj->setPosition(&startPosition);
  exitObj->setOrientation(exitAngle);
  exitObj->rva0028B4CE((PathfindLayerEnum)me->rva0028B511());
  ai=exitObj->ai;
  TheAI->pathfinder->AddObjectToPathfindMap(exitObj);
  if(ai){
   ai->ignoreObstacle(exitObj);
   ai->ignoreCollisionUntil=TheGameLogic->getFrame()+BfmeLogicFramesPerSecond;
   Pathfinder *pathfinder=TheAI->pathfinder;
   pathfinder->adjustToPossibleDestination(exitObj,ai->locomotorSet(),&endPosition);
  }
  }
  _STL::vector<Coord3D> exitPath;
  exitPath.push_back(endPosition);
  exitPath.push_back(endPosition);
  if(rallyPointExists)
   exitPath.push_back(rallyPoint);
  if(ai){
   ai->commands.rva0036EE16((const Rva0035149F*)&exitPath,me,CMD_FROM_AI);
   exitObj->rva0028ACDC((int)&endPosition);
  }
 }else{
  if(me->thingTemplate[0x11f]&0x80){
   AIUpdateInterface *ai;
   Coord3D savedGoal,target,startPosition;
   float exitAngle;
   const Coord3D *pos=&me->position;
   startPosition.x=pos->x;
   startPosition.y=pos->y;
   startPosition.z=pos->z;
   AI *theAI=TheAI;
   Pathfinder *pf=theAI->pathfinder;
   if(pf->getClosestPointOnLand(pos,me,&startPosition)){
    ai=exitObj->ai;
    if(ai){
     {
     Coord3D delta,displacement;
     AIGoalView *goalView=ai->goalView;
     savedGoal.x=goalView->goal.x;
     savedGoal.y=goalView->goal.y;
     delta.x=startPosition.x-pos->x;
     savedGoal.z=goalView->goal.z;
     delta.y=startPosition.y-pos->y;
     delta.z=startPosition.z-pos->z;
     exitAngle=(float)Rva000422A0Atan2(delta.y,delta.x);
     const Coord3D *dest=&me->ai->position148;
     target.x=dest->x;
     target.y=dest->y;
     target.z=dest->z;
     displacement.x=target.x-pos->x;
     displacement.y=target.y-pos->y;
     displacement.z=target.z-pos->z;
     if(displacement.length()<50.0f){
      delta.normalize();
      delta.z*=50.0f;
      delta.x*=50.0f;
      delta.y*=50.0f;
      target=startPosition;
      target.x+=delta.x;
      target.y+=delta.y;
      target.z+=delta.z;
     }
     }
     exitObj->setPosition(&startPosition);
     exitObj->setOrientation(exitAngle);
     if(!exitObj->rva002931BA()){
      _STL::vector<Coord3D> exitPath;
      exitPath.push_back(target);
      exitPath.push_back(target);
      exitPath.push_back(savedGoal);
      if(BfmeAIExitDoorFlag)
       ai->commands.rva0036EF09((const Rva0035149F*)&exitPath,me,exitAngle,CMD_FROM_AI);
      else
       ai->commands.rva0036EE16((const Rva0035149F*)&exitPath,me,CMD_FROM_AI);
      target=savedGoal;
     }
     exitObj->rva0028ACDC((int)&target);
    }
   }
  }
  TheAI->pathfinder->AddObjectToPathfindMap(exitObj);
 }
 if (0) throw 1;
}
