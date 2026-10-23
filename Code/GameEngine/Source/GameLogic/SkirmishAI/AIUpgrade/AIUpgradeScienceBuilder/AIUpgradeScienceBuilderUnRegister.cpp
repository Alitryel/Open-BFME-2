// cl: /O1 /MD /EHs /arch:SSE /G7 /ICode/Libraries/Include /ICode/GameEngine/Source/Common
// Codegen shard: WB 01532F70 names UnRegister and asserts its object argument.
// Native 0059771B..005977D3 RET4 removes upgrade records by live Object lookup
// and building records by stored ID. A produced-object hit clears that child ID.
// The record is an accessed prefix for slot0 and flags 2C/34; its original
// type and full extent remain unresolved. Existing vector<void*> erase is
// the established generic pointer-vector provider, not an application type claim.
#include "GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
class Player;
class Object { public: char pad00[0x74]; ObjectID id; };
class Rva00506FE9Hit { public: void unRegisterWithBuilder(void *); };
struct ScienceUnregisterRecord { virtual void *destroy(unsigned); char pad04[4]; ObjectID id; char pad0C[0x24-0x0c]; ObjectID producedId; char pad28[4]; bool used; char pad2D[0x34-0x2d]; bool upgrading; };
namespace _STL { template<class T> class allocator {}; template<class T,class A=allocator<T> > class vector { public: T *erase(T *); T *begin,*end,*limit; }; }
class Object;
class BaseA
{
public:
    virtual void Register(Object *, void *) = 0;
    virtual void UnRegister(Object *) = 0;
    virtual ~BaseA();
    int m_04;
    int m_08;
};

class Rva00506B1B
{
public:
    virtual ~Rva00506B1B();
    virtual void rva00597fc5() = 0;
    virtual void shutdown() = 0;
    bool m_04;
};

class AIUpgradeScienceBuilder : public BaseA, public Rva00506B1B { Player *owner; char pad18[0x24-0x18]; _STL::vector<void *> upgrades,buildings; public:
    virtual void Register(Object *, void *);
    virtual void UnRegister(Object *);
    virtual ~AIUpgradeScienceBuilder();
    virtual void rva00597fc5();
    virtual void shutdown();
};
void AIUpgradeScienceBuilder::UnRegister(Object *object)
{
 void **i=upgrades.begin;
 while (i!=upgrades.end) {
  ScienceUnregisterRecord *item=(ScienceUnregisterRecord *)*i;
  if (TheGameLogic->findObjectByID(item->id)==object) {
   if (item->upgrading) ((Rva00506FE9Hit *)item)->unRegisterWithBuilder(owner);
   ::operator delete(item->destroy(0));
   i=upgrades.erase(i);
  } else ++i;
 }
 i=buildings.begin;
 while (i!=buildings.end) {
  ScienceUnregisterRecord *item=(ScienceUnregisterRecord *)*i;
  if (item->id==object->id) {
   if (item->used) ((Rva00506FE9Hit *)item)->unRegisterWithBuilder(owner);
   ::operator delete(item->destroy(0));
   i=buildings.erase(i);
  } else {
   if (item->producedId==object->id) {
    ((Rva00506FE9Hit *)item)->unRegisterWithBuilder(owner);
    item->producedId=INVALID_OBJECT_ID; item->used=false;
   }
   ++i;
  }
 }
}
