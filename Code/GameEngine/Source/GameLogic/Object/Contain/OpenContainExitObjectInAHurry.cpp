// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /I.
// stlport
//
// ?exitObjectInAHurry@OpenContain@@UAEXPAVObject@@@Z, retail 0x004656DF..0x00465972
// (659 bytes, EH, RET 4).
//
// Provenance: the Zero Hour OpenContain::exitObjectInAHurry (GeneralsMD
// GameEngine/Source/GameLogic/Object/Contain/OpenContain.cpp) supplies the
// purpose and statement order. The ZH layout in OpenContain.cpp does not fit
// BFME2: retail's ExitInterface subobject sits at +0x30 (module data at
// [this-0x2C], owner at [this-0x28], removeFromContain slot 41 on the contain
// interface at [this-0x10]), so this unit spells only what the body reads.
// Target facts from the body:
// - door: the open-time (module data +0x78) is stored into the countdown at
//   +0x70 and, when nonzero, the inline condition swap (clear bit 22, set
//   bit 21 at owner +0x10C) calls the rowed notifier 0x0028AE6D;
// - exit paths (module data +0x74), the "ExitStart"/"ExitEnd" bone names,
//   the exit-path cycle at +0x6C and the rally point at +0xD0/+0xDC;
// - BFME2 replaces ZH's vehicle pathfind refresh with the rowed owner
//   helpers 0x0028AD7C / 0x0028ACDC, writes the ignore-collision frame at AI
//   +0x178 directly, and ends with 0x0028ACDC on the exiting object instead of
//   Pathfinder::updateGoal.
#include <vector>
#include "ascii_string.h"
#include "Code/Libraries/Include/Lib/Coord3D.h"
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
namespace _STL {template <> __declspec(noinline) void vector<Coord3D>::push_back(const Coord3D&);}
// /D_CRTIMP= keeps free a direct call; itoa stays an import-slot call.
extern "C" char *(__cdecl *_imp___itoa)(int,char*,int);
enum PathfindLayerEnum {LAYER_GROUND=0};
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
 void setLayer(PathfindLayerEnum);
 void rva0028AD7C();
 void rva0028ACDC(int);
 void *vtable;unsigned char *thingTemplate;char pad8[0x38-8];Coord3D position;float orientation;
 char pad48[0x10c-0x48];ConditionBits conditionBits;char pad11c[0x258-0x11c];AIUpdateInterface *ai;
};
template<class Tag,int N>class Slots:public Slots<Tag,N-1>{public:virtual void gap(Tag*,char(*)[N]);};template<class Tag>class Slots<Tag,1>{public:virtual void gap(Tag*,char(*)[1]);};
class AIUpdateInterface:public Slots<AIUpdateInterface,110>{
public:
 virtual bool isIdle() const;
 virtual void slot111();virtual void slot112();virtual void slot113();virtual void slot114();
 virtual void slot115();virtual void slot116();
 virtual void doQuickExit(const _STL::vector<Coord3D>*);
 void ignoreObstacle(const Object*);
 char pad4[0x178-4];unsigned int ignoreCollisionUntil;char pad17c[0x1cc-0x17c];
 LocomotorSet &locomotorSet(){return *(LocomotorSet*)((char*)this+0x1cc);}
};
class Pathfinder {public:void AddObjectToPathfindMap(Object*);bool adjustToPossibleDestination(Object*,const LocomotorSet&,Coord3D*);};
class AI {public:char pad[0x10];Pathfinder *pathfinder;};extern AI *TheAI;
extern GameLogic *TheGameLogic;
extern int BfmeLogicFramesPerSecond;
struct OpenContainModuleData {char pad[0x74];int numberOfExitPaths;unsigned int doorOpenTime;};
class OpenContainModule:public Slots<OpenContainModule,1>{public:OpenContainModuleData *moduleData;Object *owner;Object *getObject() const{return owner;}const OpenContainModuleData *getOpenContainModuleData() const{return moduleData;}char padC[0x20-0xc];};
class ContainModuleInterface:public Slots<ContainModuleInterface,41>{public:virtual void removeFromContain(Object*,bool);char pad4[0x10-4];};
class ExitInterface:public Slots<ExitInterface,1>{public:virtual void exitObjectInAHurry(Object*);};
class OpenContain:public OpenContainModule,public ContainModuleInterface,public ExitInterface{
public:
 virtual void removeFromContain(Object*,bool);
 virtual void exitObjectInAHurry(Object*);
 char pad34[0x6c-0x34];int whichExitPath;unsigned int doorCloseCountdown;
 char pad74[0xd0-0x74];Coord3D rallyPoint;bool rallyPointExists;
};
static __forceinline void concatChar(AsciiString &s,char c)
{
 ((StringBase<char>*)&s)->concat(&c,1);
}
void OpenContain::exitObjectInAHurry(Object *exitObj)
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
  Coord3D startPosition;
  Coord3D endPosition;
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
  exitObj->setLayer((PathfindLayerEnum)me->rva0028B511());
  _STL::vector<Coord3D> exitPath;
  exitPath.push_back(endPosition);
  AIUpdateInterface *ai=exitObj->ai;
  AIUpdateInterface *myAi=me->ai;
  TheAI->pathfinder->AddObjectToPathfindMap(exitObj);
  if(ai){
   if(myAi&&myAi->isIdle()&&(me->thingTemplate[0x109]&2)){
    me->rva0028AD7C();
    me->rva0028ACDC((int)&me->position);
   }
   ai->ignoreObstacle(0);
   ai->ignoreCollisionUntil=TheGameLogic->getFrame()+BfmeLogicFramesPerSecond;
   Pathfinder *pathfinder=TheAI->pathfinder;
   pathfinder->adjustToPossibleDestination(exitObj,ai->locomotorSet(),&endPosition);
  }
  exitPath.push_back(endPosition);
  if(rallyPointExists)
   exitPath.push_back(rallyPoint);
  if(ai){
   ai->doQuickExit(&exitPath);
   exitObj->rva0028ACDC((int)&endPosition);
  }
 }else{
  TheAI->pathfinder->AddObjectToPathfindMap(exitObj);
 }
}
