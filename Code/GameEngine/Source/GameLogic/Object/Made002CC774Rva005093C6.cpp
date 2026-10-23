// ?rva005093C6@Made002CC774@@QAEXPAUInput005093C6@@PBUCoord3D@@@Z
// retail 0x005093C6 (348B) RET8: damage-field nugget spawn helper in the
// Made002CC774 parser unit. Landed from the T1 farm exact scratch body
// (search/0x005093c6/best.cpp, 348/348 nd 0 in Lab2). Owner-unit neighbours
// are Made002CC774Parse.cpp (q4Notify002CC774 0x00509379) and the
// pathfinder/spawn providers the body calls; the farm split this function
// into the file-unit's second TU because the parser file's views cannot
// carry it without a rebuild.
// cl: /O1 /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii /G7
// ?rva005093C6@Made002CC774@@QAEXPAUInput005093C6@@PBUCoord3D@@@Z, retail 0x005093C6 (348B).
#include <string.h>
#include "ascii_string.h"
#include "../../Common/GameLogicObjectLookupView.h"
struct Coord3D;
class Player;
class Team;
class Module;
class WeaponTemplate;
class ThingTemplate;
struct CreateMask 

{
 unsigned int words[4];
 
}
;
enum NameKeyType 

{
 NAMEKEY_INVALID = 0 
 
}
;
class Thing 

{
 public: void setPosition(const Coord3D *);
 
}
;
class Object : public Thing

{
 friend class Made002CC774;
 protected:
 Module *findModule(NameKeyType) const;
 public:
 Player *getControllingPlayer() const;
 void setProducer(Object *);
 
}
;
enum ObjectID; class ThingFactory

{
 public:
 const ThingTemplate *findTemplate(const AsciiString &);
 Object *newObject(const ThingTemplate *, Team *, const CreateMask *, ObjectID);
 
}
;
extern ThingFactory *TheThingFactory;
extern GameLogic *TheGameLogic;
class NameKeyGenerator 

{
 public: NameKeyType nameToKey(const char *);
 
}
;
extern NameKeyGenerator *TheNameKeyGenerator;
class GlobalData;
extern GlobalData *TheWritableGlobalData;
struct GlobalDataView 

{
 char m_pad000[0x14];
 AsciiString m_name014;
 
}
;
struct PlayerView 

{
 char m_pad000[0x2EC];
 Team *m_team;
 
}
;
class Rva0048B9D0 

{
 public: void rva0048B9D0(const WeaponTemplate *);
 
}
;
class DeletionUpdate 

{
 public: void setLifetimeRange(unsigned int, unsigned int);
 
}
;
struct Input005093C6 

{
 char m_pad000[8];
 ObjectID m_objectID;
 
}
;
class Rva00507823

{
 public:
 virtual ~Rva00507823();
 private:
 char m_pad04[0x128 - 4];
 
}
;
class Made002CC774 : public Rva00507823

{
 public:
 void rva005093C6(Input005093C6 *input, const Coord3D *position);
 private:
 WeaponTemplate *m_weapon;
 unsigned int m_lifetime;
 AsciiString m_130;
 
}
;
void Made002CC774::rva005093C6(Input005093C6 *input, const Coord3D *position)

{
 const ThingTemplate *thingTemplate = TheThingFactory->findTemplate(((GlobalDataView *)TheWritableGlobalData)->m_name014);
 if (thingTemplate && m_weapon)
 
 {
  Object *producer = ((TheGameLogic) ? (TheGameLogic) : (TheGameLogic))->findObjectByID(input->m_objectID);
  if (producer)
  
  {
   CreateMask mask;
   memset(&mask, 0, sizeof(mask));
   Team *team = ((producer ? ((PlayerView *)producer->getControllingPlayer()) : ((PlayerView *)producer->getControllingPlayer())))->m_team;
   Object *obj = TheThingFactory->newObject(thingTemplate, team, &mask, (ObjectID)0);
   obj->setProducer(producer);
   obj->setPosition(position);
   static NameKeyType fireKey = TheNameKeyGenerator->nameToKey("FireWeaponUpdate");
   Rva0048B9D0 *fire = (Rva0048B9D0 *)obj->findModule(fireKey);
   DeletionUpdate *del = 0;
   if (fire)
   
   {
    static NameKeyType deleteKey = TheNameKeyGenerator->nameToKey("DeletionUpdate");
    del = (DeletionUpdate *)obj->findModule(deleteKey);
    
   }
   if (del == 0)
   
   {
    TheGameLogic->destroyObject(obj);
    
   }
   else
   
   {
    fire->rva0048B9D0(m_weapon);
    del->setLifetimeRange(m_lifetime, m_lifetime);
    
   }
   
  }
  
 }
 
}
