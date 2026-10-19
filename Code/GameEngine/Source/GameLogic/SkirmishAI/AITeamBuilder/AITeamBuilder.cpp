// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHs /arch:SSE /G7 /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /ICode/GameEngine/Source/Common /ICode/Libraries/Include
// stlport
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <map>
#include "ascii_string.h"
#include <vector>
#include <set>
#include "GameLogicObjectLookupView.h"
// The lookup chain (ObjectIdMap::find 0x002888D4 and GameLogic::findObjectByID
// 0x00049DC5, rowed COMDAT copies, as in AIDozerManager.cpp) is visible in
// this unit: recruitUnDefined needs it for retail's frame and register roles.
struct AITeamBuilderLookupNode { AITeamBuilderLookupNode *next; ObjectID key; Object *object; };
struct AITeamBuilderLookupBuckets {
 AITeamBuilderLookupNode **begin,**end,**capacity;
 unsigned int size() const { return end-begin; }
 AITeamBuilderLookupNode *const &operator[](unsigned int i) const { return begin[i]; }
};
struct AITeamBuilderLookupMap { unsigned char hashEqual[4]; AITeamBuilderLookupBuckets buckets; };
inline ObjectIdNode *ObjectIdMap::find(const ObjectID &id) {
 AITeamBuilderLookupMap *map=(AITeamBuilderLookupMap*)this;
 unsigned int bucket=(unsigned int)id % map->buckets.size();
 AITeamBuilderLookupNode *node;
 for(node=map->buckets[bucket];node && node->key!=id;node=node->next) {}
 return (ObjectIdNode*)node;
}
inline Object *GameLogic::findObjectByID(ObjectID id)
{
	if (id == INVALID_OBJECT_ID)
		return 0;
	ObjectIdNode *node = m_map.find(id);
	if (node == 0)
		return 0;
	return node->object;
}

// _Rb_tree_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _RbVal, class _RbLeft, class _RbRight>
static inline bool operator!=(const _Rb_tree_iterator<_RbVal, _RbLeft> &a,
                              const _Rb_tree_iterator<_RbVal, _RbRight> &b)
{ return a._M_node != b._M_node; }
}
#pragma pointers_to_members(full_generality, multiple_inheritance)
class Player;
struct Coord3D;
struct AITeamRequirementView;
struct AITargetView;
struct Rva002A8AB1Record;
class Rva002A8F24 { public: Rva002A8AB1Record *rva002A8AB1(void *); void *rva002A8F24(Player *); void *rva002A8B73(void *,int); };
extern Rva002A8F24 *g_00DFEEF8;
extern GameLogic *TheGameLogic;
class TeamPrototype;
class Rva0039D769;
class Team {
public:
 char pad[0x30]; TeamPrototype *prototype30; char pad34[0x5d-0x34]; bool active; bool dirty;
 char pad5f[0x110-0x5f]; bool flag110; bool flag111;
 Team *dlink_next_TeamInstanceList() const;
 void disband();
};
template<class T> class DLINK_ITERATOR {
 typedef T *(T::*Next)() const;
 T *current;
 Next next;
public:
 DLINK_ITERATOR(T *p, Next f):current(p),next(f){}
 void advance() { if (current) current=((*current).*next)(); }
 bool done() const { return current==0; }
 T *cur() const { return current; }
};
class SkirmishAI { public: void Register(Team *); };
class Rva0039D5A9 { public: int rva0039D5A9(); };
struct Requirements {
 char pad[0x1a0]; int mode; unsigned maximum; unsigned minimum;
};
class TeamPrototype {
public:
 void rva003A0E08(const Rva0039D769 &);
 void addUnitInfo(const Rva0039D769 &);
 char prefix[0x12c]; Requirements requirements;
 char pad2d8[0x31c-0x2d8]; bool building; bool ready;
 char pad31e[0x334-0x31e]; Team *head;
 DLINK_ITERATOR<Team> iterate_TeamInstanceList() const { return DLINK_ITERATOR<Team>(head,&Team::dlink_next_TeamInstanceList); }
};
class AITeamBuilder {
public:
 void recruitPreDefined(Team*,int*,TeamPrototype*);
 bool defineUnitsNormal_old(TeamPrototype*);
 void recruitUnDefined(Team*,int*);
 void distanceSortUnits(void*,const void*,const Coord3D*);
 int getCurNumUnits(Team *);
 int doesTeamMeetThreat(Team *);
 bool rva0059A01C(Object*,const AITeamRequirementView*,const AITargetView*);
 void checkIdleTeams();
 char prefix00[0x14]; Player* owner14;
};
class Rva0059AC4D {
 char prefix[8]; _STL::vector<TeamPrototype *> prototypes;
 Player *owner; _STL::set<int> busy;
public:
 void update();
 void rva0059ABC9(void *);
 void rva0059AC4D(void *);
 Team *rva00599F74(TeamPrototype *);
 void rva0059A153(TeamPrototype *);
 void checkIdleTeams();
};


// Native599F74..599FAA54B; WB1529260 getTeamForAIPrototype asserts157..166.
// Head334 and callback5C4AF5 use the proven zero-adjusted8B member pointer.
Team *Rva0059AC4D::rva00599F74(TeamPrototype *prototype)
{
 Team *first=0;
 for(DLINK_ITERATOR<Team> it=prototype->iterate_TeamInstanceList(); !it.done(); it.advance()) {
  if (!first) first=it.cur();
 }
 return first;
}

// Native59A153..59A1BF,110B RET4; WB AITeamBuilder::unRegisterTeamPrototype.
// Find the prototype among the builder's, disband every live team of it
// (activating the idle ones first, as update does), then erase its entry.
void Rva0059AC4D::rva0059A153(TeamPrototype *prototype)
{
 // Retail's search is the folded 4-byte-element find (rowed under its int spelling).
 TeamPrototype **last=prototypes.end();
 TeamPrototype **found=(TeamPrototype **)_STL::find((int *)prototypes.begin(),(int *)last,(const int &)prototype);
 if (found!=last) {
  for (DLINK_ITERATOR<Team> it=(*found)->iterate_TeamInstanceList(); !it.done(); it.advance()) {
   Team *team=it.cur();
   if (!team->active) { team->dirty=true; team->active=true; }
   team->disband();
  }
  prototypes.erase(found);
 }
}

#include "GameLogicObjectLookupView.h"
#include "Lib/Coord3D.h"
// Both rowed native query providers walk seven words. The existing
// Thing::isAnyKindOf provider retains BitFlags<69> in its ABI spelling;
// the actual requirement storage and any() instantiation are BitFlags<218>.
template<int N> class BitFlags { public: bool any() const; unsigned int words[7]; };
class Thing { public: bool isAnyKindOf(const BitFlags<69>&) const; };
// The template's kind-of words at +0x108, tested through an int-returning
// word test that cl narrows to retail's byte test.
struct RecruitKindOfFlags { unsigned int m_words[3]; __forceinline int test(int b) const { return m_words[b >> 5] & (1u << (b & 31)); } };
struct RecruitThingTemplate { char prefix[0x64]; AsciiString name; char pad68[0x113-0x68]; unsigned char kind113;
 const AsciiString &getName() const { return name; }
 const RecruitKindOfFlags &kindOf() const { return *(const RecruitKindOfFlags *)((const char *)this + 0x108); } };
class AIUpdateInterface { public: Object* getCurrentVictim() const; };
enum ObjectStatusTypes { STATUS_90=90 };
class Object {
public:
 void setTeam(Team*);
 bool testStatus(ObjectStatusTypes) const;
 Team *getTeam() const { return team; }
 const RecruitThingTemplate *getTemplate() const { return objectTemplate; }
 char pad00[4]; RecruitThingTemplate* objectTemplate;
 char pad08[0x38-8]; Coord3D position;
 char pad44[0x258-0x44]; AIUpdateInterface* ai;
 char pad25c[0x304-0x25c]; Team* team;
 char pad308[0x438-0x308]; unsigned char flag438;
 char pad439[0x4c0-0x439]; unsigned int frame4c0;
};
class Player { public: char prefix[0x2ec]; Team* defaultTeam; };
struct AITeamRequirementView {
 int first; char records04[0xa8]; unsigned recordCount; char padb0[0xf0-0xb0]; int priority;
 char padf4[0x198-0xf4]; int targetKind; char pad19c[0x1b4-0x19c]; BitFlags<218> required;
 BitFlags<218> forbidden;
};
struct AITargetView { int word0; int kind; int word8; Coord3D position; };
// This is an observed secondary-interface call, not a Snapshot override:
// native 59A06A adjusts Team by four and invokes slot eight for a float.
// Keep its unresolved interface identity separate from the Team list ABI.
class TeamPriorityCallView { public: virtual void slot0(); virtual void slot4(); virtual float priority(); };
struct TeamPriorityDataView { char prefix[0x111]; bool active; };
extern GameLogic* TheGameLogic;
extern int g_00E063E0;
// Native 0059A01C..0059A153 and WB0152A380 establish this three-argument
// recruitment predicate. WB only exposes inlined Vector3 names, so retain
// an address name for the outer method. Retail rejects unordered distance
// comparisons, then applies required/forbidden kinds, age, and victim gates.
bool AITeamBuilder::rva0059A01C(Object* obj,const AITeamRequirementView* req,const AITargetView* target) {
 Team* currentTeam;
 if(!obj || (obj->flag438&1) || (obj->objectTemplate->kind113&8))goto reject;
 currentTeam=obj->team;
 if(currentTeam!=owner14->defaultTeam) {
  if(!(((TeamPriorityDataView*)currentTeam)->active && ((TeamPriorityCallView*)((char*)currentTeam+4))->priority()<req->priority)) {
   if(!target||target->kind!=1)goto reject;
   Coord3D a={target->position.x,target->position.y,target->position.z};
   Coord3D b={obj->position.x,obj->position.y,obj->position.z};
   Coord3D delta={b.x-a.x,b.y-a.y,b.z-a.z};
   if(!(delta.z*delta.z+delta.y*delta.y+delta.x*delta.x<=1000000.0f))goto reject;
  }
 }
 if(req->required.any()&&!((Thing*)obj)->isAnyKindOf((const BitFlags<69>&)req->required))goto reject;
 if(req->forbidden.any()&&((Thing*)obj)->isAnyKindOf((const BitFlags<69>&)req->forbidden))goto reject;
 if(TheGameLogic->getFrame()-obj->frame4c0<(unsigned)g_00E063E0)goto reject;
 if(obj->ai->getCurrentVictim())goto reject;
 return true;
reject:
 return false;
}

class Rva005C4AD1LeaField { public: void* get() const; };

class Rva0039EA9C {
public:
 Rva0039EA9C(); ~Rva0039EA9C();
 int first; int second; int third;
 AsciiString name0c; AsciiString name10; int final14;
};

class Rva0039D7C1ByteField { public: unsigned char get() const; };
class Rva0039D7C8LeaGetter { public: void* get() const; };
struct TreeOpaqueMapped00372FF4 { unsigned int m_bits; };
typedef _STL::pair<const float, TreeOpaqueMapped00372FF4> DistanceValue;
typedef _STL::_Rb_tree<float, DistanceValue, _STL::_Select1st<DistanceValue>,
    _STL::less<float>, _STL::allocator<DistanceValue> > DistanceTree;
typedef _STL::map<int, void *> HeaderConstructor;

enum ScienceType { SCIENCE_0 = 0 };
typedef _STL::vector<ScienceType> IDVectorView;
// Existing owned providers keep their verified compiler settings.
namespace _STL {
template <> void IDVectorView::reserve(unsigned int);
template <> void IDVectorView::push_back(const ScienceType &);
}


// The rowed destructor owns an eight-byte tree header/count pair. Native
// construction uses the existing map constructor with this same storage.
class Rva00599FAA : public HeaderConstructor
{
public:
    __forceinline Rva00599FAA() {}
    ~Rva00599FAA();
};

// Native 59A499..59A71C, 643B; WB015297E0 names recruitPreDefined (assert236..279).
// Runtime object offsets, requirement stride 0x18, priority 0x21C and call relationships
// are target evidence. ScienceType and the opaque map value retain existing ABI
// provider spellings; the stored values here are object IDs. Begin before end
// and a named squared distance before the pair preserve native register ordering.
void AITeamBuilder::recruitPreDefined(Team* team,int* count,TeamPrototype* remaining) {
 AITeamRequirementView* requirements=(AITeamRequirementView*)((char*)remaining+0x12c);
 if(requirements->priority<20)requirements->priority=20;
 void* stats=g_00DFEEF8->rva002A8F24(owner14);
 const IDVectorView* units=(const IDVectorView*)((Rva005C4AD1LeaField*)*(void**)stats)->get();
 IDVectorView sorted;
 TeamPrototype* prototype=team->prototype30;
 if(((Rva0039D7C1ByteField*)prototype)->get()) {
  Rva00599FAA distances;
  const ScienceType* it=units->begin();
  const ScienceType* end=units->end();
  for(;it!=end;++it) {
   Object* object=TheGameLogic->findObjectByID((ObjectID)*it);
   const Coord3D* center=(const Coord3D*)((Rva0039D7C8LeaGetter*)prototype)->get();
   Coord3D delta={center->x,center->y,center->z};
   delta.x-=object->position.x;delta.y-=object->position.y;delta.z-=object->position.z;
   float distance=delta.x*delta.x+delta.y*delta.y+delta.z*delta.z;
   TreeOpaqueMapped00372FF4 value; value.m_bits=*it;
   ((DistanceTree*)&distances)->insert_equal(DistanceValue(distance,value));
  }
  sorted.reserve(distances.size());
  DistanceTree* tree=(DistanceTree*)&distances;
  DistanceTree::iterator finish=tree->end();
  for(DistanceTree::iterator it=tree->begin();it._M_node!=finish._M_node;++it)sorted.push_back(*(const ScienceType*)&it->second.m_bits);
  units=&sorted;
 }
 AITargetView* target=(AITargetView*)g_00DFEEF8->rva002A8B73(owner14,requirements->targetKind);
 const ScienceType* end=units->end();
 for(const ScienceType* it=units->begin();it!=end;++it) {
  if(((Rva0039D5A9*)requirements)->rva0039D5A9()<=0)break;
  Object* obj=TheGameLogic->findObjectByID((ObjectID)*it);
  if(rva0059A01C(obj,requirements,target)) {
   bool recruited=false;
   for(unsigned i=0;i<requirements->recordCount&&!recruited;++i) {
    Rva0039EA9C* req=(Rva0039EA9C*)requirements->records04+i;
    if(((const StringBase<char>&)req->name10).compare((const StringBase<char>&)obj->objectTemplate->name)==0 && req->first>0) {
     obj->setTeam(team); ++*count;
     Rva0039EA9C used;
     used.first=1; used.second=1;
     used.name10=obj->objectTemplate->name;
     used.final14=req->final14;
     remaining->rva003A0E08((const Rva0039D769&)used);
     recruited=true;
    }
   }
  }
 }
}

// Native 59A8D7..59AA37, 352B; WB names recruitUnDefined. The units (sorted
// by distance to the prototype's point when its flag is set) are recruited
// while the count stays under the requirement maximum (+0x1A4) when their
// template has kind bit 0x108&8 and they pass the rowed 0x0059A01C test; for
// requirement modes 0 and 1 (+0x1A0) a second pass takes kind bit 0x113&4.
void AITeamBuilder::recruitUnDefined(Team* teamToBuild,int* curNumUnits) {
 void* stats=g_00DFEEF8->rva002A8F24(owner14);
 Rva005C4AD1LeaField* unitStats=*(Rva005C4AD1LeaField**)stats;
 TeamPrototype* prototype=teamToBuild->prototype30;
 const AITeamRequirementView* requirements=(const AITeamRequirementView*)((const char*)prototype+0x12C);
 AITargetView* target=(AITargetView*)g_00DFEEF8->rva002A8B73(owner14,requirements->targetKind);
 const IDVectorView* units=(const IDVectorView*)unitStats->get();
 const IDVectorView* useUnits=units;
 IDVectorView sorted;
 if(((Rva0039D7C1ByteField*)prototype)->get()) {
  distanceSortUnits(&sorted,units,(const Coord3D*)((Rva0039D7C8LeaGetter*)prototype)->get());
  useUnits=&sorted;
 }
 const Requirements* limits=(const Requirements*)requirements;
 const ScienceType* end=useUnits->end();
 for(const ScienceType* it=useUnits->begin();it!=end;++it) {
  if((unsigned int)*curNumUnits>=limits->maximum)break;
  Object* obj=TheGameLogic->findObjectByID((ObjectID)*it);
  if(obj->objectTemplate->kindOf().test(3)&&rva0059A01C(obj,requirements,target)) {
   obj->setTeam(teamToBuild);
   ++*curNumUnits;
  }
 }
 if(limits->mode==0||limits->mode==1) {
  for(const ScienceType* it=useUnits->begin();it!=end;++it) {
   Object* obj=TheGameLogic->findObjectByID((ObjectID)*it);
   if(obj->objectTemplate->kindOf().test(90)&&rva0059A01C(obj,requirements,target)) {
    obj->setTeam(teamToBuild);
    ++*curNumUnits;
   }
  }
 }
}

#include <hash_map>
class Rva0039D761DwordClearer { public: void clear(); };
namespace _STL { template<> unsigned int hash_map<int,int>::bucket_count() const; }

// Native59A2BE..59A40D,335B; WB152ABC0 names defineUnitsNormal_old,
// AITeamBuilder.cpp381..389. Retail supplies the object/team/template offsets
// and the requirement-count/maximum accesses. IDVectorView keeps the existing
// folded ScienceType provider ABI; these stored words are object IDs.
// Keep the real vector copy constructor visible: an opaque specialization
// loses retail's begin-pointer lifetime through the loop and cleanup.
bool AITeamBuilder::defineUnitsNormal_old(TeamPrototype* prototype) {
 ((Rva0039D761DwordClearer*)prototype)->clear();
 void* stats=g_00DFEEF8->rva002A8F24(owner14);
 void* units=*(void**)stats;
 if(((_STL::hash_map<int,int>*)units)->bucket_count()>0) {
  IDVectorView ids(*(const IDVectorView*)((Rva005C4AD1LeaField*)units)->get());
  for(const ScienceType* id=ids.begin();id!=ids.end();++id) {
   if((unsigned)((Rva0039D5A9*)((char*)prototype+0x12c))->rva0039D5A9()>=prototype->requirements.maximum)break;
   Object* obj=TheGameLogic->findObjectByID((ObjectID)*id);
   if(obj && obj->getTeam()==owner14->defaultTeam &&
      (obj->objectTemplate->kindOf().test(3)||obj->objectTemplate->kindOf().test(90)) &&
      !obj->testStatus(STATUS_90)) {
    Rva0039EA9C record;
    record.first=1; record.second=1;
    record.name10=obj->getTemplate()->getName();
    record.final14=-1;
    prototype->addUnitInfo((const Rva0039D769&)record);
   }
  }
  if((int)((const AITeamRequirementView*)((const char*)prototype+0x12c))->recordCount>0)return true;
 }
 return false;
}
