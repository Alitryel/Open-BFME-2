// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHs /arch:SSE /G7 /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /ICode/GameEngine/Source/Common /ICode/Libraries/Include
// stlport
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <map>
#include <hash_map>
#include "ascii_string.h"
#include <vector>
#include <set>
#include "Lib/Coord3D.h"
#include "GameLogicObjectLookupView.h"

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

namespace _STL { template<> unsigned int hash_map<int,int>::bucket_count() const; }

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

enum ObjectStatusTypes { STATUS_90 = 90 };
struct RecruitKindOfFlags { unsigned int m_words[3]; __forceinline int test(int b) const { return m_words[b >> 5] & (1u << (b & 31)); } };
struct RecruitThingTemplate { char prefix[0x64]; AsciiString name; char pad68[0x113-0x68]; unsigned char kind113;
 const AsciiString &getName() const { return name; }
 const RecruitKindOfFlags &kindOf() const { return *(const RecruitKindOfFlags *)((const char *)this + 0x108); } };

class AIUpdateInterface;
class Team;
class Object {
public:
 void setTeam(Team*);
 bool testStatus(ObjectStatusTypes) const;
 char pad00[4]; RecruitThingTemplate* objectTemplate;
 char pad08[0x38-8]; Coord3D position;
 char pad44[0x74-0x44]; int objectID;
 char pad78[0x258-0x78]; AIUpdateInterface* ai;
 char pad25c[0x304-0x25c]; Team* team;
 char pad308[0x438-0x308]; unsigned char flag438;
 char pad439[0x4c0-0x439]; unsigned int frame4c0;
};

class Player { public: char prefix[0x2ec]; Team* defaultTeam; };

class AITeamBuilder {
public:
 void checkIdleTeams();
 char prefix00[0x14]; Player* owner14;
 _STL::set<int> idleIDs;
};

struct IdleTargetPoint { int word0; Coord3D position; };
struct IdleTargetList { char prefix[0x20]; _STL::vector<IdleTargetPoint*> points; };
struct Rva002A8AB1Record { char prefix[0x164]; IdleTargetList* targetList; };
class Rva002A8F24 { public: Rva002A8AB1Record *rva002A8AB1(void *); void *rva002A8F24(Player *); };
extern Rva002A8F24 *g_00DFEEF8;

extern GameLogic *TheGameLogic;
extern int g_00E063E0;

class Rva0025BFF8 { public: Object* rva0025BFF8(int); };
class Rva00295A0FCommands { public: void Rva00295A0FCommand(void*,int,int); };
int GetGameLogicRandomValue(int,int,char*,int);

static inline Object **FillObjectPointers(Object **first, unsigned int n, Object * const &value)
{
    for (; n > 0; --n, ++first)
        *first = value;
    return first;
}

namespace _STL {

// Retail calls _M_clear out of line (0x0007FAB3) rather than expanding it.
template <> __declspec(noinline) void vector<Object *>::_M_clear();

template <> void vector<Object *>::_M_insert_overflow(Object **__position, Object * const &__x,
    const __true_type &, unsigned int __fill_len, bool __atend)
{
    const unsigned int __old_size = size();
    const unsigned int __len = __old_size + (max)(__old_size, __fill_len);
    pointer __new_start = __len ? (pointer)allocator<char>::allocate(__len * sizeof(Object *), 0) : 0;
    pointer __new_finish = (pointer)__copy_trivial(this->_M_start, __position, __new_start);
    __new_finish = FillObjectPointers(__new_finish, __fill_len, __x);
    if (!__atend)
        __new_finish = (pointer)__copy_trivial(__position, this->_M_finish, __new_finish);
    _M_clear();
    _M_set(__new_start, __new_finish, __new_start + __len);
}

template <> void vector<Object *>::_M_clear()
{
    _Destroy(this->_M_start, this->_M_finish);
    this->_M_end_of_storage.deallocate(this->_M_start, this->_M_end_of_storage._M_data - this->_M_start);
}

}

void AITeamBuilder::checkIdleTeams() {
 void* stats=g_00DFEEF8->rva002A8F24(owner14);
 void* units=*(void**)stats;
 int count=((_STL::hash_map<int,int>*)units)->bucket_count();
 if(count>0) {
  _STL::vector<Object*> idle;
  Team* defaultTeam=owner14->defaultTeam;
  for(int i=0;i<count;++i) {
   Object* obj=((Rva0025BFF8*)units)->rva0025BFF8(i);
   RecruitThingTemplate* tmpl = obj->objectTemplate;
   RecruitThingTemplate* tmplCopy = obj->objectTemplate;
   if((tmpl->kindOf().test(3)&&!tmplCopy->kindOf().test(7))||tmpl->kindOf().test(90)) {
    if(obj->team==defaultTeam&&!obj->testStatus(STATUS_90)) {
     int id=obj->objectID;
     if(idleIDs.find(id)==idleIDs.end()&&TheGameLogic->getFrame()-obj->frame4c0>=(unsigned)g_00E063E0) {
      Object* recruit=obj;
      idle.push_back(recruit);
     }
    }
   }
  }
  IdleTargetList* list=g_00DFEEF8->rva002A8AB1(owner14)->targetList;
  if(!idle.empty() && !list->points.empty()) {
   Object** idleBegin=&idle[0];
   int idx=GetGameLogicRandomValue(0,idle.size()-1,"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\SkirmishAI\\AITeamBuilder\\AITeamBuilder.cpp",0x251);
   Object* obj=idleBegin[idx];
   _STL::vector<IdleTargetPoint*>& pts=list->points;
   int last=pts.size()-1;
   IdleTargetPoint* point=pts[last];
   int id=obj->objectID;
   idleIDs.insert(id);
   AIUpdateInterface* ai=obj->ai;
   ((Rva00295A0FCommands*)((char*)ai+0x20))->Rva00295A0FCommand(&point->position,0x7fffffff,0);
  }
 }
}
