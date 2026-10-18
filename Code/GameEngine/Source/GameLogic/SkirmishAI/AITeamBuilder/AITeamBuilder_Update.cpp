// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHs /arch:SSE /G7 /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /ICode/GameEngine/Source/Common /ICode/Libraries/Include
// stlport
// Split from AITeamBuilder.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
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
 char prefix[0x12c]; Requirements requirements;
 char pad2d8[0x31c-0x2d8]; bool building; bool ready;
 char pad31e[0x334-0x31e]; Team *head;
 DLINK_ITERATOR<Team> iterate_TeamInstanceList() const { return DLINK_ITERATOR<Team>(head,&Team::dlink_next_TeamInstanceList); }
};
class AITeamBuilder {
public:
 void recruitPreDefined(Team*,int*,TeamPrototype*);
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
// Native59AC6E..59ADB9,331B; WB1528FA0 AITeamBuilder::update (assert125).
// The two prototype passes, owner14, active/ready31C/31D, Team flags5D/5E
// and110/111, set18 and every call are corroborated by retail. Keep the
// existing address-derived receiver and recruited-helper ABIs. Threat
// provider is presently typed int; this call site consumes its low byte.
void Rva0059AC4D::update()
{
 for (_STL::vector<TeamPrototype *>::iterator it=prototypes.begin(); it!=prototypes.end(); ++it) {
  TeamPrototype *prototype=*it;
  if (prototype->building) {
   int mode=*(int *)((char *)prototype+0x2cc);
   switch(mode) {
    case 2: rva0059AC4D(prototype); break;
    default: rva0059ABC9(prototype); break;
   }
  }
 }
 for (_STL::vector<TeamPrototype *>::iterator it=prototypes.begin(); it!=prototypes.end(); ++it) {
  TeamPrototype *prototype=*it;
  if (prototype->building) {
   Requirements *requirements=&prototype->requirements;
   Team *team=rva00599F74(prototype);
   if (team) {
    int count=((AITeamBuilder *)this)->getCurNumUnits(team);
    if ((unsigned)count >= requirements->minimum &&
        ((Rva0039D5A9 *)requirements)->rva0039D5A9()==0 &&
        (requirements->mode==1 || (unsigned)count>=requirements->maximum ||
         (unsigned char)((AITeamBuilder *)this)->doesTeamMeetThreat(team))) {
     team->flag110=true;
     team->flag111=false;
     if (!team->active) { team->dirty=true; team->active=true; }
     SkirmishAI *ai=(SkirmishAI *)g_00DFEEF8->rva002A8AB1(owner);
     ai->Register(team);
     prototype->building=false;
     prototype->ready=true;
    }
   }
  }
 }
 for (_STL::set<int>::iterator it=busy.begin(); it!=busy.end();) {
  if (!TheGameLogic->findObjectByID((ObjectID)*it)) busy.erase(it++);
  else ++it;
 }
 ((AITeamBuilder *)this)->checkIdleTeams();
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
 const RecruitKindOfFlags &kindOf() const { return *(const RecruitKindOfFlags *)((const char *)this + 0x108); } };
class AIUpdateInterface { public: Object* getCurrentVictim() const; };
class Object {
public:
 void setTeam(Team*);
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


