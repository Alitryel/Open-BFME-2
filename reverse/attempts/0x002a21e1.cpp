// ?handleBuildPlacements@InGameUI@@IAEXXZ
// partial score=0.92766 date=2026-10-14
// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /D_OPERATOR_NEW_DEFINED_ /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /ICode/Libraries/Include/Lib /ICode/GameEngine/Include /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// stlport
// Private reconstruction: WB DAD2E0 + native2A21E1..2A3255. Not a recovery claim.

#include "ascii_string.h"
#include "unicode_string.h"
#include "Coord3D.h"
#include "Coord2D.h"
#include <vector>
#include <math.h>
#include "matrix3d.h"
void __cdecl Rva00030830GameFree(void *);
namespace _STL { template<> __forceinline void allocator<Coord3D>::deallocate(Coord3D *p,size_t) const {if(p)Rva00030830GameFree(p);} }
struct ICoord2D {int x,y;};
struct PlaceCoord : Coord3D {
 PlaceCoord(){} PlaceCoord(const Coord3D &v){x=v.x;y=v.y;z=v.z;}
 PlaceCoord(const PlaceCoord &v){x=v.x;y=v.y;z=v.z;} ~PlaceCoord(){}
};
struct RGBColor {float red,green,blue;};
static const RGBColor illegalBuildColor={1,0,0};
struct _MouseSixteen{int v[4];};
class Mouse{public:enum MouseCursor {CURSOR_BUILD=5,CURSOR_INVALID=12};
 void rva001EEBD5(UnicodeString,const _MouseSixteen*,const _MouseSixteen*);
 char unknown[0x4f0c];ICoord2D pos;
};extern Mouse *TheMouse;
class TerrainResourceBehaviorModuleData;
class ModuleData {public:
virtual void slot0();
virtual void slot4();
virtual void slot8();
virtual void slotC();
virtual void slot10();
virtual void slot14();
virtual void slot18();
virtual void slot1C();
virtual void slot20();
virtual void slot24();
virtual void slot28();
virtual void slot2C();
virtual void slot30();
virtual void slot34();
virtual void slot38();
virtual void slot3C();
virtual void slot40();
virtual void slot44();
virtual void slot48();
virtual void slot4C();
virtual void slot50();
virtual void slot54();
virtual void slot58();
virtual void slot5C();
 virtual const TerrainResourceBehaviorModuleData *resourceData()const;
 char unknown04[0x30-4];float placementRadius;
};
class TerrainResourceBehaviorModuleData {public:char unknown00[12];int maxIncome;};
class ModuleInfo{public:const void *first,*last,*cap;
 __declspec(noinline) const ModuleData *getNthData(int)const;
 int count()const{return ((const char*)last-(const char*)first)/20;}
};
class ThingTemplate {public:
 const ModuleData *rva0033B3D7()const;
 const ModuleData *rva0033B427(int)const;
 bool isEquivalentTo(const ThingTemplate*)const;
 char unknown00[0x108];unsigned char kinds[28];char unknown124[0x2e4-0x124];ModuleInfo modules;
 __forceinline bool hasKind(int i)const{return (kinds[i/8]&(1<<(i%8)))!=0;}
};
static const TerrainResourceBehaviorModuleData *rva0029B9E5(const ThingTemplate *type){
 const ModuleInfo &modules=type->modules;int count=modules.count();
 for(int i=0;i<count;++i){const ModuleData *data=modules.getNthData(i);if(data){const TerrainResourceBehaviorModuleData *result=data->resourceData();if(result)return result;}}
 return 0;
}
class Thing {public:__forceinline const ThingTemplate *getTemplate()const{return type;}void setOrientation(float);void setPositionZ(float);void *vtable;const ThingTemplate *type;char unknown08[0x38-8];Coord3D position;};
class ModelConditionFlags;
class Rva0028F59A {public:Rva0028F59A(int,int);unsigned int words[19];};
class Rva002707FA{public:void rva002707FA(unsigned char);};
class Drawable:public Thing{public:
 void setPosition(const Coord3D*);const Coord3D *getPosition()const;
 void setDrawableHidden(bool);void rva002791E7(const ModelConditionFlags&,unsigned,unsigned);
 void rva00275490(const RGBColor*);
 char unknown44[0xb0-0x44];float opacity;
};
class Player{public:__forceinline int getPlayerIndex()const{return index;}void rva002AF614(void*);char unknown00[0x54];int index;char unknown58[0x280-0x58];int color;};
class Object:public Thing{public:Player *getControllingPlayer()const;};
class Rva00293330{public:void *rva00293330(unsigned);};

class Cb00359D42;
class TerrainResourceManager{public:void enumerateRegisteredClaimants(int,Cb00359D42*);};


// BFME 2's native lookup at 0x00049DC5 uses the ObjectID enum and a map
// receiver at +0xB4. The provider's existing accessed prefix is shared here;
// complete GameLogic and map extents remain unreconstructed. Pointer-only
// callers do not construct these views or depend on their sizeof.
// Reference-backed consumers may already have the same ObjectID enum.
#ifndef _GAME_TYPE_H_
enum ObjectID
{
	INVALID_OBJECT_ID = 0
};
#endif

class TerrainResourceManager;
class Xfer;
class Object;
class Drawable;
class Rva00439E0C;
class AsciiString;
class CommandButton;
class WindowLayout;
class Rva0023E928;
class UnicodeString;

struct ObjectIdNode
{
	char pad[8];
	Object *object;
};

class ObjectIdMap
{
public:
	ObjectIdNode *find(const ObjectID &id);
};

// The network code reads the command timestamp at +0x38 and Zero Hour's
// frame counter at +0x40 (ConnectionManager::update 0x004D342A, among others).
// StealthUpdate::disguiseAsObject (0x00373DF0) reads the manager at +0x178
// whose call 0x00439E0C takes the disguised object. The spell store's show
// (finishShowPurchaseScience 0x0043CB48) reads the end flag at +0x6D and
// the game mode at +0x110.
// InGameUI::addFloatingText (0x002A0D19) gates on the byte at +0x9A, Zero
// Hour's getDrawIconUI.
// The object list head is at +0xAC: getFirstObject (0x0023CAD2) returns it and
// prepareLogicForObjectLoad (0x00242C86) walks it inline.
// ScoreKeeper::addObjectLost (0x0039CF73) tests the scoring byte at +0x98
// first, as Zero Hour's isScoringEnabled does.
// GameClient::update (0x0023BEE8) reads the byte at +0x125, next to the pause
// byte isGamePaused (0x0023CD97) returns from +0x124, and skips the drawable,
// terrain and display updates while it is set.
struct PlayerLeaveStatus;
class GameLogic
{
	char pad[0x38];
	unsigned int m_timestamp;
	char pad3C[0x40 - 0x3C];
	unsigned int m_frame;
	char pad44[0x6D - 0x44];

public:
	bool m_6d; // +0x6D

private:
	char pad6E[0x98 - 0x6E];
	bool m_isScoringEnabled; // +0x98
	char pad99[0x9A - 0x99];
	bool m_drawIconUI; // +0x9A
	char pad9B[0xAC - 0x9B];
	Object *m_firstObject; // +0xAC, the head getFirstObject returns
	char padB0[0xB4 - 0xB0];
	ObjectIdMap m_map;
	char padB5[0x110 - 0xB5];

public:
	int m_110; // +0x110

	// Native AIUnitBuilder598052 and listener239457 compare this word.
	int m_114; // +0x114; precise mode meaning remains unresolved

private:
	char pad118[0x125 - 0x118];
	bool m_flag125;
	char pad126[0x170 - 0x126];
public: TerrainResourceManager *resourceManager;
private: char pad174[0x178 - 0x174];
	Rva00439E0C *m_manager178;
	char pad17C[0x1B8 - 0x17C];
	// Window cleanup 0x00376D49 owns this layout and clears the pending byte.
	// BFME1's closeWindows supplies its purpose; offsets are native BFME2.
	WindowLayout *m_background; // +0x1B8
	bool m_backgroundPending; // +0x1BC

public:
	bool rva00085124();	// 0x00085124; verified mode 4-or-7 predicate
	bool isInMultiplayerGame();	// 0x00042235
	bool rva0042219();	// 0x00042219, mode gate rejecting 9, 4 and 7
	bool rva001DCD1C();	// 0x001DCD1C, mode 8 or mode 9 with +0x114 != 3
	void rva0023CD9E(bool paused, int pauseMode, bool affectMouse);	// 0x0023CD9E
	Object *findObjectByID(ObjectID id);
	void rva0023CFE4(Xfer *xfer); // 0x0023CFE4, Version1 plus native snapshot at +0x184
	void rva0023D033(); // 0x0023D033, native +0x184 cleanup forwarder
	const AsciiString *rva0023D05F(int value);	// 0x0023D05F, +0x184 army name by id
	const AsciiString *rva0023D06A(int value);	// 0x0023D06A, +0x184 army banner name by id
	int rva0023D08B(int value);	// 0x0023D08B, existing +0x184 forwarder
	void rva0023D0C2(Object *obj, int handle);	// 0x0023D0C2
	void TransitionFromLivingWorldTacticalBattle(); // 0x0023D0CD; timeline continue callback
	Object *getFirstObject();	// 0x0023CAD2
	int rva0023CAD9();	// 0x0023CAD9, next ObjectID for Object::Object 0x00298EA9
	void registerObject(Object *obj);	// 0x00242AE9, called by Object::Object 0x00298EA9
	void destroyObject(Object *obj);	// 0x00242C09
	void sendObjectDestroyed(Object *obj);	// 0x0023CD67, called by Object::~Object 0x00299CE4
	void rva0023CF8B();	// 0x0023CF8B, called by AptLoadScreen::init 0x0043A5F6
	void deselectObject(Object *obj, unsigned int playerMask, bool affectClient);	// 0x0023C9F8
	void bindObjectAndDrawable(Object *obj, Drawable *draw);	// 0x0023CD4A
	void rva00376E92(bool first, bool second);	// 0x00376E92
	void rva00376D49();	// 0x00376D49, window cleanup, donor closeWindows
	void rva00248558(bool fromSave);	// 0x00248558, verified new-game/load pass
	unsigned char isGamePaused();	// 0x0023CD97
	void deleteLoadScreen();	// 0x002423E3
	void processDestroyList();	// 0x002413DF
	void prepareLogicForObjectLoad();	// 0x00242C86
	void processProgressComplete(int playerID);	// 0x0023D76E
	void CreateWOTRMPPlayers(); // 0x0023E99A; verified provider, campaign caller 0x0052C45E
	void setControlBarOverride(const AsciiString &commandSetName, int slot, const CommandButton *commandButton);	// 0x0024792F
	void rva00240866(Rva0023E928 *msg, bool frozen);	// 0x00240866, multiplayer save request handler
	void rva0023D30F(int a, int b, UnicodeString *name);	// 0x0023D30F, thiscall spelling of the stdcall Rva0023D30FCall
	bool isScoringEnabled() const { return m_isScoringEnabled; }
	bool getFlag125() const { return m_flag125; }
	unsigned int getTimestamp() const { return m_timestamp; }
	unsigned int getFrame() const { return m_frame; }
	bool getDrawIconUI() const { return m_drawIconUI; }
	Rva00439E0C *getManager178() const { return m_manager178; }
	PlayerLeaveStatus *getPlayerLeaveStatus(int playerIndex); // 0x0023D1E3, verified eight-slot status accessor
};

extern GameLogic *TheGameLogic;
class PlayerList{public:int getPlayersWithRelationship(int,unsigned,bool);char unknown00[0x10];Player *local;};extern PlayerList *ThePlayerList;
class ResourceEntryCollector{public:void rva004E551E();void rva004E5559(const Coord3D*,float,int);};
class Rva004E54B8{public:void rva004E54B8();};
struct BfmeUiResourceEntryState {unsigned unknown00;void *head;};extern BfmeUiResourceEntryState BfmeUiResourceEntryCollectorState;
struct FeedbackParams {char storage[20];};
class PlaceTerrainResourceClaimantFeedback {public:
 PlaceTerrainResourceClaimantFeedback(FeedbackParams*,Drawable*,const TerrainResourceBehaviorModuleData*);
 void rva004E6693(ICoord2D*);void *impl;
};
class Rva004E63DB{public:void rva004E63DB();};
class Rva004E668E;
class Rva0029B5FD{public:void reset(Rva004E668E*);PlaceTerrainResourceClaimantFeedback *ptr;};
class View{public:virtual void slot0();
virtual void slot4();
virtual void slot8();
virtual void slotC();
virtual void slot10();
virtual void slot14();
virtual void slot18();
virtual void slot1C();
virtual void slot20();
virtual void slot24();
virtual void slot28();
virtual void slot2C();
virtual void slot30();
virtual void slot34();
virtual void slot38();
virtual void slot3C();
virtual void slot40();
virtual void slot44();
virtual void slot48();
virtual void slot4C();
virtual void slot50();
virtual void slot54();
virtual void slot58();
virtual void slot5C();
virtual void slot60();
virtual void slot64();
virtual void slot68();
virtual void slot6C();
virtual void slot70();
virtual void slot74();
virtual void slot78();
virtual void slot7C();
virtual void slot80();
virtual void slot84();
virtual void slot88();
virtual void slot8C();
virtual void slot90();
virtual void slot94();
virtual void slot98();
virtual void slot9C();
virtual void slotA0();
virtual void slotA4();
virtual void slotA8();
virtual void slotAC();
virtual void slotB0();
virtual void slotB4();
virtual void slotB8();
virtual void slotBC();
virtual void slotC0();
virtual void slotC4();
virtual void slotC8();
virtual void slotCC();
virtual void slotD0();
virtual void slotD4();
virtual void slotD8();
virtual void slotDC();
virtual void slotE0();
virtual void slotE4();
virtual void slotE8();
virtual void slotEC();
virtual void slotF0();
virtual void slotF4();
virtual void slotF8();
virtual void slotFC();
virtual void slot100();
virtual void slot104();
virtual void slot108();
virtual void slot10C();
virtual void slot110();
virtual void slot114();
virtual void slot118();
virtual void slot11C();
virtual void slot120();
virtual void slot124();
virtual void slot128();
virtual void slot12C();
virtual void slot130();
virtual void slot134();
virtual void slot138();
virtual void slot13C();
virtual void slot140();
virtual void slot144();
virtual void slot148();
virtual void slot14C();
virtual void slot150();
virtual void slot154();
virtual void slot158();
virtual void slot15C();
virtual void slot160();
virtual void slot164();
 virtual void screenToTerrain(const ICoord2D*,Coord3D*,bool=false);
};extern View *TheTacticalView;
class GlobalData{public:char unknown00[0xa94];int maxLineBuildObjects;};extern GlobalData *TheWritableGlobalData;
class GameClient{public:virtual void slot0();
virtual void slot4();
virtual void slot8();
virtual void slotC();
virtual void slot10();
virtual void slot14();
virtual void slot18();
virtual void slot1C();
virtual void slot20();
virtual void slot24();
virtual void slot28();
virtual void slot2C();
virtual void slot30();
virtual void slot34();
virtual void slot38();
virtual void slot3C();
virtual void slot40();
virtual void slot44();
virtual void slot48();
virtual void slot4C();
virtual void slot50();
virtual void slot54();
virtual void slot58();
virtual void slot5C();
virtual void slot60();
virtual void slot64();
virtual void slot68();
virtual void slot6C();
virtual void slot70();
 virtual void destroyDrawable(Drawable*);virtual void slot78();virtual unsigned getFrame();
};extern GameClient *TheGameClient;
class ThingFactory{public:void *newDrawable(void*,int,int);const ThingTemplate *findTemplate(const AsciiString&);};extern ThingFactory *TheThingFactory;
class SpecialPowerModule{public:virtual void slot0();
virtual void slot4();
virtual void slot8();
virtual void slotC();
virtual void slot10();
virtual void slot14();
virtual void slot18();
virtual void slot1C();
virtual void slot20();
virtual void slot24();
virtual void slot28();
virtual void slot2C();
 virtual bool getRadius(float*);
};
class Rva004D9A3C{public:Coord3D pos;float angle;char unknown10[12];};
class Rva0039205C{public:
 Rva0039205C(){count=0;array=0;flagC=false;flagD=false;status=-1;cost=0;unknown14=0;}
 ~Rva0039205C();void *rva00392CC5(unsigned);Rva004D9A3C *rva00392CF9(unsigned);float rva00392D1D(unsigned);int rva00392D71(int);
 unsigned count;int cost;Rva004D9A3C *array;bool flagC,flagD;int status;void *unknown14;
};
class BuildAssistant{public:virtual void slot0();
virtual void slot4();
virtual void slot8();
virtual void slotC();
virtual void slot10();
virtual void slot14();
virtual void slot18();
virtual void slot1C();
virtual void slot20();
virtual void slot24();
virtual void slot28();
virtual void slot2C();
virtual void slot30();
virtual void slot34();
virtual void slot38();
virtual void slot3C();
 virtual int isLocationLegalToBuild(const Coord3D*,const ThingTemplate*,float,int,Object*,Object*);
 virtual void slot44();virtual void slot48();virtual void slot4c();
 virtual bool getBuildPortData(Rva0039205C*,Object*,const Coord3D*,const Coord3D*,unsigned);
 virtual void slot54();virtual void slot58();virtual bool isBuildPort(const ThingTemplate*,Object*);
 bool getPortTransform(const Coord3D*,const ThingTemplate*,float,float*,Coord3D*);
};extern BuildAssistant *TheBuildAssistant;
class Rva0029A94F{public:void rva0029A94F();};
class TerrainType {public:AsciiString getTexture()const;};
class BuildListInfo{friend class InGameUI;public:const Coord3D *getLocation()const{return &location;} float getAngle()const{return angle;} BuildListInfo();
 AsciiString buildingName,templateName;Coord3D location;Coord2D rally;float angle;char tail[0x80-0x24];
 protected:virtual ~BuildListInfo();
};
class Rva00396A5C{public:int rva00396A5C(Player*);};
class SidesList{public:bool rva0032BD25(int,int,BuildListInfo*);};extern SidesList *TheSidesList;
class TerrainLogic{public:virtual void slot0();
virtual void slot4();
virtual void slot8();
virtual void slotC();
virtual void slot10();
virtual void slot14();
 virtual float getGroundHeight(float,float,void*);
};extern TerrainLogic *TheTerrainLogic;
class TerrainVisual{public:virtual void slot0();
virtual void slot4();
virtual void slot8();
virtual void slotC();
virtual void slot10();
virtual void slot14();
virtual void slot18();
virtual void slot1C();
virtual void slot20();
virtual void slot24();
virtual void slot28();
virtual void slot2C();
 virtual void addFactionBibDrawable(Drawable*,bool,float);virtual void removeFactionBibDrawable(Drawable*);virtual void removeAllBibs();
};extern TerrainVisual *TheTerrainVisual;
class GhostObjectManager{public:__forceinline int getLocalPlayerIndex()const{return playerIndex;}void *vtable;int playerIndex;};extern GhostObjectManager *TheGhostObjectManager;
bool Rva0030596CIntersects(void*,PlaceCoord,float);float normalizeAngle(float);
struct CommandButton{char unknown00[0x1c];unsigned command;};
struct PlaceIcon {Drawable *drawable;float angle;};
class InGameUI{public:virtual void slot0();
virtual void slot4();
virtual void slot8();
virtual void slotC();
virtual void slot10();
virtual void slot14();
virtual void slot18();
virtual void slot1C();
virtual void slot20();
virtual void slot24();
virtual void slot28();
virtual void slot2C();
virtual void slot30();
virtual void slot34();
virtual void slot38();
virtual void slot3C();
virtual void slot40();
virtual void slot44();
virtual void slot48();
virtual void slot4C();
virtual void slot50();
virtual void slot54();
virtual void slot58();
virtual void slot5C();
virtual void slot60();
virtual void slot64();
virtual void slot68();
virtual void slot6C();
virtual void slot70();
virtual void slot74();
virtual void slot78();
virtual void slot7C();
virtual void slot80();
virtual void slot84();
virtual void slot88();
virtual void slot8C();
virtual void slot90();
virtual void slot94();
virtual void slot98();
virtual void slot9C();
virtual void slotA0();
virtual void slotA4();
virtual void slotA8();
virtual void slotAC();
virtual void slotB0();
virtual void slotB4();
virtual void slotB8();
virtual void slotBC();
 virtual CommandButton *getPendingCommand();
 virtual void slotC4();
virtual void slotC8();
virtual void slotCC();
virtual void slotD0();
virtual void slotD4();
virtual void slotD8();
virtual void slotDC();
virtual void slotE0();
 virtual ObjectID getPendingPlaceSourceObjectID();
 virtual void slotE8();virtual void slotEC();virtual bool isPlacementAnchored();virtual void getPlacementPoints(ICoord2D*,ICoord2D*);
 virtual void slotF8();virtual bool canPlacePort();virtual void setCanPlacePort(bool);
 protected:void handleBuildPlacements();public:
 char unknown04[0x53c-4];const ThingTemplate *pendingType;void *unknown540;PlaceIcon *icons;
 char unknown548[0x554-0x548];bool useFeedbackPoint;char unknown555[3];ICoord2D feedbackPoint;
 char unknown560[0x574-0x560];FeedbackParams resourcePoint;Rva0029B5FD feedback;
 char unknown58c[0x9c8-0x58c];int feedbackState;
 protected:void setMouseCursor(Mouse::MouseCursor);
};
void InGameUI::handleBuildPlacements(){
 TheMouse->rva001EEBD5(UnicodeString::TheEmptyString,0,0);
 Object *builder=TheGameLogic->findObjectByID(getPendingPlaceSourceObjectID());
 if(!builder || (!builder->getTemplate()->hasKind(14)&&!builder->getTemplate()->hasKind(156)))return;
 if(!pendingType)return;
 bool isPort=TheBuildAssistant->isBuildPort(pendingType,builder);
 const ModuleData *castle=pendingType->rva0033B3D7();
 ICoord2D loc;PlaceCoord world;float angle=icons[0].angle;
 if(isPlacementAnchored()){
  ICoord2D start,end;getPlacementPoints(&start,&end);loc=start;
  if(start.x!=end.x||start.y!=end.y){PlaceCoord worldStart,worldEnd;TheTacticalView->screenToTerrain(&start,&worldStart);TheTacticalView->screenToTerrain(&end,&worldEnd);Coord2D v;v.x=worldEnd.x-worldStart.x;v.y=worldEnd.y-worldStart.y;angle=v.toAngle();}
 }else{
  const ICoord2D *mousePos=&TheMouse->pos;loc=*mousePos;
  if(feedbackState==2){feedbackState=0;TerrainResourceManager *manager=TheGameLogic->resourceManager;
   const TerrainResourceBehaviorModuleData *data=rva0029B9E5(pendingType);
   if(data&&data->maxIncome>0&&manager){feedback.reset((Rva004E668E*)new PlaceTerrainResourceClaimantFeedback(&resourcePoint,icons[0].drawable,data));
    ((ResourceEntryCollector*)&BfmeUiResourceEntryCollectorState)->rva004E551E();int mask=0;
    if(ThePlayerList&&ThePlayerList->local)mask=ThePlayerList->getPlayersWithRelationship(ThePlayerList->local->getPlayerIndex(),3,false);
    manager->enumerateRegisteredClaimants(mask,(Cb00359D42*)&BfmeUiResourceEntryCollectorState);
    ((Rva004E54B8*)&BfmeUiResourceEntryCollectorState)->rva004E54B8();
   }
  }
  if(isPort){
   if(!canPlacePort()){setCanPlacePort(true);((Rva0029A94F*)this)->rva0029A94F();}
   else{
    unsigned int last=TheWritableGlobalData->maxLineBuildObjects-1;
    if(feedbackState==1){feedbackState=0;SpecialPowerModule *module=(SpecialPowerModule*)((Rva00293330*)builder)->rva00293330(getPendingCommand()?getPendingCommand()->command:0xfffffe);
     if(module){_STL::vector<Coord3D> positions;float radius=0;
      if(module->getRadius(&radius)){Player *player=builder->getControllingPlayer();if(player){int color=player->color;player->rva002AF614(&positions);
       ((ResourceEntryCollector*)&BfmeUiResourceEntryCollectorState)->rva004E551E();
       for(_STL::vector<Coord3D>::iterator it=positions.begin();it!=positions.end();++it)((ResourceEntryCollector*)&BfmeUiResourceEntryCollectorState)->rva004E5559(&*it,radius,color);
       ((Rva004E54B8*)&BfmeUiResourceEntryCollectorState)->rva004E54B8();
      }}
     }
    }
    PlaceCoord builderPos(builder->position),mouseWorld;TheTacticalView->screenToTerrain(&loc,&mouseWorld);
    CommandButton *button=getPendingCommand();unsigned command=button?button->command:0xfffffe;
    Rva0039205C info;
    if(!TheBuildAssistant->getBuildPortData(&info,builder,&builderPos,&mouseWorld,command)){
     for(int i=0;i<TheWritableGlobalData->maxLineBuildObjects;++i){if(!icons[i].drawable){if(icons[last].drawable){((Rva002707FA*)icons[last].drawable)->rva002707FA(0);icons[last].drawable->setDrawableHidden(true);}break;}
      ((Rva002707FA*)icons[i].drawable)->rva002707FA(0);icons[i].drawable->setDrawableHidden(true);
     }return;
    }
    UnicodeString text;text.format((const unsigned short*)L"%d",info.cost);
    _MouseSixteen color={{32,255,128,255}},shadow={{0,0,0,255}};TheMouse->rva001EEBD5(text,&color,&shadow);
    RGBColor tint=illegalBuildColor;
    switch(info.status){
     case 0:setMouseCursor(Mouse::CURSOR_BUILD);break;
     case 10:setMouseCursor(Mouse::CURSOR_BUILD);tint.blue=tint.red=tint.green=0.5f;if(TheGameClient->getFrame()&4)tint.green=1.3f;break;
     case 9:setMouseCursor(Mouse::CURSOR_INVALID);tint.red=0;if(TheGameClient->getFrame()&4)tint.blue=1.7f;break;
     case 7:setMouseCursor(Mouse::CURSOR_INVALID);tint.red=0;if(TheGameClient->getFrame()&4)tint.green=1.0f;break;
     default:setMouseCursor(Mouse::CURSOR_INVALID);if(TheGameClient->getFrame()&4)tint.green=0.8f;break;
    }
    int count=(unsigned)(TheWritableGlobalData->maxLineBuildObjects-1)<info.count-1?(TheWritableGlobalData->maxLineBuildObjects-1):info.count-1;
    if(info.status==10)++count;
    for(int i=0;i<count;++i){
     if(icons[i].drawable&&!icons[i].drawable->getTemplate()->isEquivalentTo((const ThingTemplate*)info.rva00392CC5(i))){TheGameClient->destroyDrawable(icons[i].drawable);icons[i].drawable=0;}
     if(!icons[i].drawable){const ThingTemplate *type=(const ThingTemplate*)info.rva00392CC5(i);if(type)icons[i].drawable=(Drawable*)TheThingFactory->newDrawable((void*)type,8,-1);if(!icons[i].drawable)continue;}
     icons[i].drawable->setPosition((const Coord3D*)info.rva00392CF9(i));icons[i].drawable->opacity=0.45f;icons[i].drawable->setOrientation(info.rva00392D1D(i));icons[i].angle=info.rva00392D1D(i);
     ((Rva002707FA*)icons[i].drawable)->rva002707FA(1);icons[i].drawable->setDrawableHidden(false);
     icons[i].drawable->rva002791E7((const ModelConditionFlags&)Rva0028F59A(0,108),1,0);
     if(info.status==10)icons[i].drawable->rva00275490(&tint);else if(info.rva00392D71(i))icons[i].drawable->rva00275490(&tint);else if(info.status!=0)icons[i].drawable->rva00275490(&illegalBuildColor);else icons[i].drawable->rva00275490(0);
    }
    if(icons[last].drawable&&!icons[last].drawable->getTemplate()->isEquivalentTo((const ThingTemplate*)info.rva00392CC5(count))){TheGameClient->destroyDrawable(icons[last].drawable);icons[last].drawable=0;}
    if(!icons[last].drawable){const ThingTemplate *type=(const ThingTemplate*)info.rva00392CC5(count);if(type)icons[last].drawable=(Drawable*)TheThingFactory->newDrawable((void*)type,8,-1);}
    if(icons[last].drawable){icons[last].drawable->setPosition((const Coord3D*)info.rva00392CF9(count));icons[last].drawable->opacity=0.45f;icons[last].drawable->setOrientation(info.rva00392D1D(count));icons[last].drawable->setDrawableHidden(false);((Rva002707FA*)icons[last].drawable)->rva002707FA(1);icons[last].angle=info.rva00392D1D(count);
     if(info.rva00392D71(count))icons[last].drawable->rva00275490(&tint);else if(info.status!=0)icons[last].drawable->rva00275490(&illegalBuildColor);else icons[last].drawable->rva00275490(0);
    }
    for(int i=((count-1>=0)?count-1:0)+1;i<TheWritableGlobalData->maxLineBuildObjects-1;++i){
     if(!icons[i].drawable){const ThingTemplate *type=(const ThingTemplate*)info.rva00392CC5(i);if(type)icons[i].drawable=(Drawable*)TheThingFactory->newDrawable((void*)type,8,-1);}
     if(icons[i].drawable){((Rva002707FA*)icons[i].drawable)->rva002707FA(0);icons[i].drawable->setDrawableHidden(true);icons[i].drawable->setPositionZ(-5000.0f);}
    }
   }
  }
 }
 TheTacticalView->screenToTerrain(&loc,&world);
 float displayAngle=angle;
 if(castle){int i=0;BuildListInfo info;int side=((Rva00396A5C*)castle)->rva00396A5C(builder->getControllingPlayer());
  while(TheSidesList->rva0032BD25(side,i++,&info)){
   const ThingTemplate *type=TheThingFactory->findTemplate(((TerrainType*)&info)->getTexture());if(!type)continue;
   if(icons[i].drawable&&!icons[i].drawable->getTemplate()->isEquivalentTo(type)){TheGameClient->destroyDrawable(icons[i].drawable);icons[i].drawable=0;}
   if(!icons[i].drawable)icons[i].drawable=(Drawable*)TheThingFactory->newDrawable((void*)type,8,-1);
   if(!icons[i].drawable)continue;
   Matrix3D matrix(true);Vector3 center(world.x,world.y,world.z);
   matrix.In_Place_Pre_Rotate_Z(angle);matrix.Set_Translation(center);
   Vector3 v(info.getLocation()->x,info.getLocation()->y,info.getLocation()->z);Matrix3D::Transform_Vector(matrix,v,&v);
   PlaceCoord pos;pos.x=v.X;pos.y=v.Y;pos.z=v.Z;
   pos.z=TheTerrainLogic->getGroundHeight(pos.x,pos.y,0);
   float buildingAngle=angle;buildingAngle+=info.getAngle();buildingAngle=normalizeAngle(displayAngle);
   icons[i].drawable->setPosition(&pos);icons[i].drawable->opacity=0.45f;icons[i].drawable->setOrientation(displayAngle);icons[i].angle=buildingAngle;
   ((Rva002707FA*)icons[i].drawable)->rva002707FA(1);icons[i].drawable->setDrawableHidden(false);icons[i].drawable->rva002791E7((const ModelConditionFlags&)Rva0028F59A(0,108),1,0);
  }
  for(;i<TheWritableGlobalData->maxLineBuildObjects;++i)if(icons[i].drawable){TheGameClient->destroyDrawable(icons[i].drawable);icons[i].drawable=0;}
 }
 if(pendingType->hasKind(188)){float newAngle=0;PlaceCoord newWorld;newWorld.x=newWorld.y=newWorld.z=0;
  if(TheBuildAssistant->getPortTransform(&world,pendingType,angle,&newAngle,&newWorld)){displayAngle=newAngle;world=newWorld;}
 }
 if(isPort)return;if(!icons[0].drawable)return;
 icons[0].angle=angle;icons[0].drawable->setPosition(&world);icons[0].drawable->setOrientation(displayAngle);
 if(feedbackState==1){feedbackState=0;const ModuleData *data=pendingType->rva0033B427(0);
  if(data){_STL::vector<Coord3D> positions;float radius=data->placementRadius;Player *player=builder->getControllingPlayer();
   if(player){int color=player->color;player->rva002AF614(&positions);((ResourceEntryCollector*)&BfmeUiResourceEntryCollectorState)->rva004E551E();
    for(_STL::vector<Coord3D>::iterator it=positions.begin();it!=positions.end();++it)((ResourceEntryCollector*)&BfmeUiResourceEntryCollectorState)->rva004E5559(&*it,radius,color);
    ((Rva004E54B8*)&BfmeUiResourceEntryCollectorState)->rva004E54B8();
   }
  }
 }
 if(feedback.ptr){feedback.ptr->rva004E6693(useFeedbackPoint?&feedbackPoint:0);((Rva004E63DB*)feedback.ptr)->rva004E63DB();}
 if(TheGameClient->getFrame()&1){TheTerrainVisual->removeAllBibs();bool anyIllegal=false;
  for(int i=0;i<TheWritableGlobalData->maxLineBuildObjects;++i){if(!icons[i].drawable)continue;int code=0;
   if(castle){const ThingTemplate *type=icons[i].drawable->getTemplate();if(type&&type->hasKind(120)){code=TheBuildAssistant->isLocationLegalToBuild(icons[i].drawable->getPosition(),icons[i].drawable->getTemplate(),icons[i].angle,0x48f,builder,0);if(code!=0)anyIllegal=true;}}
   else code=TheBuildAssistant->isLocationLegalToBuild(icons[i].drawable->getPosition(),icons[i].drawable->getTemplate(),icons[i].angle,0x48f,builder,0);
   if(TheGhostObjectManager->getLocalPlayerIndex()==builder->getControllingPlayer()->getPlayerIndex()&&Rva0030596CIntersects((void*)icons[i].drawable->getTemplate(),*icons[i].drawable->getPosition(),icons[i].angle))code=8;
   if(code!=0){if(code==9){RGBColor tint={0,0,0.5f};if(TheGameClient->getFrame()&4)tint.blue=1.7f;icons[i].drawable->rva00275490(&tint);}else icons[i].drawable->rva00275490(&illegalBuildColor);}
   else if(anyIllegal)icons[i].drawable->rva00275490(&illegalBuildColor);else icons[i].drawable->rva00275490(0);
   if(code!=0)TheTerrainVisual->addFactionBibDrawable(icons[i].drawable,code!=0&&code!=9,0);else TheTerrainVisual->removeFactionBibDrawable(icons[i].drawable);
  }
 }
}
