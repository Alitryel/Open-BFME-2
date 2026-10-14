// ?isAttackViewBlockedByObstacle@Pathfinder@@QAE_NPBVObject@@ABUCoord3D@@01@Z
// partial score=0.99705 date=2026-10-13
// ?isAttackViewBlockedByObstacle@Pathfinder@@QAE_NPBVObject@@ABUCoord3D@@01@Z
// partial score=0.8081 date=2026-10-13
// ?isAttackViewBlockedByObstacle@Pathfinder@@QAE_NPBVObject@@ABUCoord3D@@01@Z
template<class T> inline volatile T &__vref(T &x){return *(volatile T *)&x;}
// partial score=0.7984680613 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// BF1 575ba2b04 PathfinderIsAttackViewBlockedByObstacle semantic guide.
// Native2F314A..2F336A RET16; WB D3D500 names attack-view query.
struct Coord3DBase {float x,y,z;};
struct Coord3D:Coord3DBase
{
 void assign(const Coord3D &v){x=v.x;y=v.y;z=v.z;}
 float Normalize2D();
 Coord3D &operator-=(const Coord3DBase &v){x-=v.x;y-=v.y;z-=v.z;return *this;}
 ~Coord3D(){}
 Coord3D(){}
 Coord3D(const Coord3D &v){x=v.x;y=v.y;z=v.z;}
 Coord3D(float a,float b,float c) {x=a;y=b;z=c;}
 
}
;
enum PathfindLayerEnum 
{
 LAYER_GROUND=1
}
;
enum WeaponSlotType;
struct AttackViewTemplate 
{
 char padding[0x108];
 unsigned char flags[0x28];
 
}
;
class Weapon;
class Object 
{
 public:void *vtable;
 AttackViewTemplate *definition;
 const Weapon *getCurrentWeapon(WeaponSlotType *)const;
 int rva0028B511()const;
 
}
;
class Weapon 
{
 public:bool isClearGoalFiringLineOfSightTerrain(const Object *,const Coord3D &,const Coord3D &)const;
 int isClearGoalFiringLineOfSightTerrain(const Object *,const Coord3D *,const Object *);
 
}
;
struct AttackAiData 
{
 char pad[0x67];
 unsigned char useLOS;
 
}
;
class AI;
extern AI *TheAI;
struct AttackAIView 
{
 char pad[0x18];
 AttackAiData *data;
 
}
;
class TerrainLogic 
{
 public:PathfindLayerEnum getLayerForDestination(Object *,const Coord3D *);
 
}
;
extern TerrainLogic *TheTerrainLogic;
class Rva002E73D4 
{
 public:Rva002E73D4(int,int,int);
 int object,other,cell,skip;
 bool hitLayer;
 int count,run;
 
}
;
struct Rva002F18D4Info;
int Rva002E6E6CGet(int);
class Pathfinder 
{
 public:
 bool isAttackViewBlockedByObstacle(const Object *,const Coord3D &,const Object *,const Coord3D &);
 void *rva001E3647Pos(int,const Coord3D *);
 int iterateCellsAlongLine(const Coord3D *,const Coord3D *,PathfindLayerEnum,Rva002F18D4Info *);
 
}
;
bool Pathfinder::isAttackViewBlockedByObstacle(const Object *attacker,const Coord3D &attackerPos,const Object *victim,const Coord3D &victimPos)
{
 if(!((AttackAIView *)TheAI)->data->useLOS)return false;
 if(!victim || (!(attacker->definition->flags[7]&8)&&!(attacker->definition->flags[26]&0x40)))return false;
 {
  Weapon *w=(Weapon *)attacker->getCurrentWeapon(0);
  if(attacker->definition->flags[0]&4)w=0;
  if(w)
  {
   bool blocked; if(victim) blocked=!(unsigned char)w->isClearGoalFiringLineOfSightTerrain(attacker,&attackerPos,victim);else blocked=!w->isClearGoalFiringLineOfSightTerrain(attacker,attackerPos,victimPos);
   if(blocked)return true;
   
  }
 Coord3D pos;
  int attackerLayer=attacker->rva0028B511();
  PathfindLayerEnum layer=LAYER_GROUND;
  if(victim){layer=(PathfindLayerEnum)victim->rva0028B511();
  if(attackerLayer!=layer)
  {
   if((attackerLayer>=2&&attackerLayer<=15)||(layer>=2&&layer<=15))
   {
    float z=attackerPos.z;
    if(victimPos.z>z)z=victimPos.z;
    pos.assign(attackerPos);
    pos.z=z;
    PathfindLayerEnum a=TheTerrainLogic->getLayerForDestination(0,&pos);
    pos=victimPos;
    pos.z=z;
    PathfindLayerEnum b=TheTerrainLogic->getLayerForDestination(0,&pos);
    if(a==b)return true;
    
   }
   
  }
  }
  Rva002E73D4 info((int)attacker,(int)victim,(int)rva001E3647Pos(layer,&victimPos));
  if(!(unsigned char)Rva002E6E6CGet(attacker->rva0028B511()))
  {
   info.skip=3;
   if(layer==LAYER_GROUND)layer=(PathfindLayerEnum)attacker->rva0028B511();
   
  }
  pos.assign(attackerPos);pos-=victimPos;
  pos.Normalize2D();
  pos.x*=5.0f;
  pos.y*=5.0f;
  pos.z*=5.0f;
  pos.x=victimPos.x+pos.x;
  pos.y=victimPos.y+pos.y;
  pos.z=victimPos.z+pos.z;
  return iterateCellsAlongLine(&attackerPos,&pos,layer,(Rva002F18D4Info *)&info)!=0;
  
 }
 return false;
 
}
