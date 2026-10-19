// ?findBestTarget@AITargetHeuristicEnemyStructure@@QAEXPAVAITarget@@PAVPlayer@@1@Z
// partial score=0.98 date=2026-10-19
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /ICode/GameEngine/Source/Common /ICode/Libraries/Include
// 0x005735C6 bank 2026-10-19 (claude-opus-5-5): hack-free at the old bank's nd 6 (volatile iterator,
// end pointer and previousDistance, _ReadWriteBarrier and the duplicated begin() are gone; WB loop shape).
// Left: (1) retail stores best=0 after the unit null test; every spelling that moves it there flips the
// whole allocation (424 B nd 118; 240 declaration orders, loop forms, key types, helpers, flags,
// vc71-sp1/ddk compilers ruled out) - same residue as 0x5A9F70; (2) the map tree dtor call resolves to
// 0x21B775 (map<int,int>) where retail calls 0x286852 (ledger name for map<int,void*>): a ledger/pin
// question. Home: a new AITargetHeuristicEnemyStructure.cpp or AITargetHeuristicTechBuilding.cpp
// (same flags, same nd); use g_00DFEEF8 there. Scratch: build/nbr/r3/5735c6/.
// stlport
#include "GameLogicObjectLookupView.h"
#include "Lib/Coord3D.h"
#include <map>
#include <vector>
class Player;
class Rva002A8F24 { public:void *rva002A8F24(Player *);char pad[0x884];float fallbackWeight;};
extern Rva002A8F24 *g_tacticalAIRegistry;
extern GameLogic *TheGameLogic;
class Rva005C4AD1LeaField {public:void *get()const;};
typedef _STL::vector<ObjectID> IdRange;
struct Record{Rva005C4AD1LeaField *units;void *reserved;Rva005C4AD1LeaField *structures;};
class Object{public:char pad[0x38];Coord3D pos;char pad44[0x74-0x44];ObjectID id;};
struct Thing;
class AITarget{public:void setTarget(Object*,float);};
class AITargetHeuristicEnemyStructure{public:int isValidTarget(Thing*,void*);void findBestTarget(AITarget*,Player*,Player*);};
void AITargetHeuristicEnemyStructure::findBestTarget(AITarget *target,Player *attacker,Player *defender){
 Record *a=(Record*)g_tacticalAIRegistry->rva002A8F24(attacker);
 IdRange *units=(IdRange*)a->units->get();
 Record *b=(Record*)g_tacticalAIRegistry->rva002A8F24(defender);
 IdRange *structures=(IdRange*)b->structures->get();
 _STL::map<int,int> counts;
 for(ObjectID *it=units->begin();it!=units->end();++it){
  Object *unit=TheGameLogic->findObjectByID(*it);
  int best=0;
  if(unit){
   float bestDistance=-1.0f;
   for(ObjectID *s=structures->begin();s!=structures->end();++s){
    Object *obj=TheGameLogic->findObjectByID(*s);
    if(obj && (unsigned char)isValidTarget((Thing*)obj,attacker)){
     float dx=obj->pos.x-unit->pos.x;float dy=obj->pos.y-unit->pos.y;
     float distance=dx*dx+dy*dy;
     if(bestDistance<0.0f || distance<bestDistance){bestDistance=distance;best=obj->id;}
    }
   }
  }
  if(best){_STL::map<int,int>::iterator i=counts.find(best);if(i!=counts.end())++i->second;else counts[best]=1;}
 }
 if(!counts.empty()){
  int bestId=0;
  int maximum=0;
  for(_STL::map<int,int>::iterator i=counts.begin();i!=counts.end();++i){
   if(i->second>maximum){bestId=i->first;maximum=i->second;}
  }
  target->setTarget(TheGameLogic->findObjectByID((ObjectID)bestId),g_tacticalAIRegistry->fallbackWeight);
 }
}
