// ?update@EmotionTrackerUpdate@@UAE?AW4UpdateSleepTime@@XZ
// partial score=0.86233 date=2026-10-19
// ?update@EmotionTrackerUpdate@@UAE?AW4UpdateSleepTime@@XZ
// partial score=0.083 date=2026-10-17
// ?update@EmotionTrackerUpdate@@UAE?AW4UpdateSleepTime@@XZ
// partial score=0.33 date=2026-10-14
// ?update@EmotionTrackerUpdate@@UAE?AW4UpdateSleepTime@@XZ
// partial score=0.33 date=2026-10-14
// Bank draft of the EmotionTrackerUpdate per-frame step at 0x004B1633 (2200B).
// WB 0x1230DD0 (EmotionTrackerUpdate::update) + retail. `this` is the module
// object; the owning Thing is at +4, the tracked Object at +8. The body walks
// the nugget vector at +0x90..+0x94, tests relationship/status/range filters
// and activates/deactivates nuggets through the rowed EmotionNugget calls.
        // fall through to the nugget scan
// cl: /O1 /arch:SSE /G7 /MD /EHsc
// stlport
// The inherited description above describes the earlier draft, not a proven layout.
// Native ECX is root+0x10; module data/object are at ECX-0xC/-8.
// Native scans EmotionSystem ObjectIDs before nested module-nugget eligibility scans.
// Current evidence and unresolved codegen: reverse/attempt_support/0x004b1633-20261019-w6/readme.md
/* Inherited draft field annotations, retained as unverified evidence.
    unsigned int m_frame;			// +0x40
    void *m_274;				// +0x274
    int m_c;					// +0x0c
    unsigned char m_38;			// +0x38
    int m_4;					// +0x04
    unsigned int m_14;				// +0x14
    Thing *m_4;					// +0x04
    Object *m_8;				// +0x08
    unsigned char m_14;				// +0x14
    unsigned char m_16;				// +0x16
    unsigned char m_17;				// +0x17
    unsigned char m_18;				// +0x18
    unsigned int m_20[12];			// +0x20
    unsigned int m_58;				// +0x58
    unsigned int m_60;				// +0x60
    EmotionNugget **m_90;			// +0x90 begin
    EmotionNugget **m_94;			// +0x94 end
    EmotionNugget *m_9c;			// +0x9c active nugget
    unsigned int m_a0;				// +0xa0
    unsigned int m_a4;				// +0xa4
    unsigned int m_a8;				// +0xa8
    unsigned int m_ac;				// +0xac
    unsigned char m_b0;				// +0xb0
    int m_b4;					// +0xb4
    int m_0;					// +0x00
    int m_4;					// +0x04
    Player *m_player;				// +0x08
    unsigned char m_c;				// +0x0c
*/
#define _STLP_USE_STATIC_LIB

#include "../../Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
#include "../../reference/shims/bfme2_ascii/ascii_string.h"
#include <vector>
#include "../../Code/Libraries/Include/Lib/Coord3D.h"
#include "../../Code/GameEngine/Source/Common/PartitionRangeQueryCallView.h"

enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1, UPDATE_SLEEP_FOREVER = 0x3fffffff };
enum ObjectStatusTypes {};
enum Relationship { REL_ENEMY = 0, REL_NEUTRAL = 1, REL_ALLY = 2 };

class Player { public: __forceinline int getPlayerIndex() const { return index; } char pad[0x54]; int index; };
class ThingTemplate {
public:
    bool isEquivalentTo(const ThingTemplate *) const;
    char pad[0x113]; unsigned char flags113;
    char pad114[0x11a-0x114]; unsigned char flags11a;
};
class Object {
public:
    const Coord3D *getPosition() const { return &pos; }
    ObjectID getID() const { return id; }
    bool status6() const { return (status94 & 0x40)!=0; }
    float rva00263763(const void *) const;
    int rva0028B511() const;
    bool testStatus(ObjectStatusTypes) const;
    Player *getControllingPlayer() const;
    Relationship getRelationship(const Object *) const;
    float getShroudClearingRange() const;
    char pad0[4]; ThingTemplate *m_template;
    char pad8[0x38-8]; Coord3D pos;
    char pad44[0x74-0x44]; ObjectID id;
    char pad78[0x94-0x78]; unsigned int status94;
    char pad98[0x274-0x98]; Object *m_274;
    char pad278[0x454-0x278]; bool flag454;
};
class Rva0028F326Owner { public: unsigned char rva0028F326(unsigned int, float); };
class Rva2225E0Filter { public: bool accepts(Object *, Player *); void *value; };
struct EmotionUpdateData {
    char pad0[8]; float range; int interval;
    char pad10[4]; Rva2225E0Filter filter14,filter18,filter1c;
    float range20,range24,probability;
};
struct EmotionEntry { char pad0[4]; int kind; };
struct Rva004DD018Arg;
class EmotionNugget {
public:
    bool CanBeActivatedFor(int,int,Rva004DD018Arg *);
    char pad0[4]; EmotionEntry *entry;
};
class Emotion : public EmotionNugget { public: bool rva004DCEC4(); };
class Rva004DD2C0 { public: void rva004DD2C0(); };
class Rva004DCC84 { public: void rva004DCC84(Object *,int); };
class Rva004B13D8 { public: EmotionNugget *rva004B13D8(); };
class EmotionTrackerUpdate;
class PartitionFilter {
public:
    PartitionFilter():next(0) {}
    virtual ~PartitionFilter() {}
    virtual bool Allow(Object *) = 0;
    virtual int getPlayerMask();
    PartitionFilter &And(PartitionFilter &);
    PartitionFilter *next;
};
class Rva000421C8;

class EmotionTrackerUpdate {
public:
    class TauntPointFilter;
    virtual UpdateSleepTime update();
    void PulseEmotion(int,void *,int);
    char pad4[0x14-4];
    bool flags[12];
    unsigned int expiry[12];
    ObjectID targetID[12];
    EmotionNugget **begin, **end, **capacity;
    EmotionNugget *active;
    int countdown;
    char pad94[0xa0-0x94];
    int forcedKind,forcedFrames;
    ObjectID forcedTarget;
    unsigned int nextFrame;
    bool foundLatch;
};
class EmotionTrackerUpdate::TauntPointFilter:public PartitionFilter {
public:
    TauntPointFilter(EmotionTrackerUpdate *);
    virtual bool Allow(Object *);
    virtual int getPlayerMask();
    EmotionTrackerUpdate *module;
    Object *object;
    Player *player;
    int enemyCount,allyCount;
    Object *cached;
    bool tested;
};
class RvaDistanceFilter:public PartitionFilter {
public:
    RvaDistanceFilter(Object *o,float r):object(o),flag(true),range(r) {}
    virtual bool Allow(Object *);
    Object *object;
    bool flag;
    float range;
};
class RvaPlayerFilter:public PartitionFilter {
public:
    RvaPlayerFilter(Player *p):player(p),flag(false) {}
    virtual bool Allow(Object *);
    Player *player;
    bool flag;
};
class PlayerList { public: int getPlayersWithRelationship(int,unsigned int,bool); };
struct BfmePointFD;
class Rva00739830 { public: int rva00739830(const BfmePointFD *,int,unsigned int) const; };
struct EmotionSystemView { char pad[0x24]; _STL::vector<ObjectID> objects; };
class EmotionSystem;
class GlobalData;
class TerrainLogic;
class ThingFactory { public: const ThingTemplate *findTemplate(const AsciiString &); };
class TerrainView {
public:
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual void v3(); virtual void v4(); virtual void v5();
    virtual float height(float,float,int);
};
class DebugDrawView {
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void va(); virtual void vb();
    virtual void circle(const Coord3D *,float,unsigned long);
};
extern GameLogic *TheGameLogic;
extern EmotionSystem *TheEmotionSystem;
extern GlobalData *TheWritableGlobalData;
extern TerrainLogic *TheTerrainLogic;
extern DebugDrawView *g_rva00DFEA3C;
extern PartitionManager *ThePartitionManager;
extern PartitionManager *TheShroudManager;
extern PlayerList *ThePlayerList;
extern ThingFactory *TheThingFactory;
extern int g_rva00DBA4E4;
float GetGameLogicRandomValueReal(float,float,char *,int);

UpdateSleepTime EmotionTrackerUpdate::update()
{
    EmotionUpdateData *data=*(EmotionUpdateData **)((char *)this-0xc);
    if(!data) return (UpdateSleepTime)0x3fffffff;
    Object *obj=*(Object **)((char *)this-8);
    if(!obj) return (UpdateSleepTime)0x3fffffff;
    if(obj->m_274) {
        if(active) {
            ((Rva004DD2C0 *)active)->rva004DD2C0();
            active=0;
        }
        return (UpdateSleepTime)1;
    }
    if(forcedFrames>0) --forcedFrames;
    if(*((unsigned char *)TheWritableGlobalData+0xe9c)) {
        Coord3D pos;
        pos.x=obj->pos.x; pos.y=obj->pos.y; pos.z=obj->pos.z;
        pos.z=((TerrainView *)TheTerrainLogic)->height(pos.x,pos.y,0);
        if(data->interval) g_rva00DFEA3C->circle(&pos,data->range,0xff0000ff);
        if(data->range20!=0.0f) g_rva00DFEA3C->circle(&pos,data->range20,0xff00ffff);
        if(data->range24!=0.0f) g_rva00DFEA3C->circle(&pos,data->range24,0xffff0000);
    }
    Object *closest=0;
    float closestDist=3.402823466e+38f;
    --countdown;
    if(countdown<=0 && data->interval && forcedFrames==0) {
        countdown=data->interval;
        TauntPointFilter filter((EmotionTrackerUpdate *)((char *)this-0x10));
        RvaDistanceFilter distance(obj,data->range);
        RvaPlayerFilter player(obj->getControllingPlayer());
        filter.And(distance);
        filter.And(player);
        if(!obj->testStatus((ObjectStatusTypes)0x44))
            closest=ThePartitionManager->getClosestObject(&obj->pos,data->range,0,(Rva000421C8 *)&filter);
        if(!closest) {
            if(filter.tested) {
                flags[9]=true; flags[3]=false; flags[0]=false;
            } else {
                flags[9]=false; flags[3]=false; flags[0]=false;
            }
        } else if(!data->filter1c.accepts(closest,0) &&
                  !data->filter14.accepts(closest,0) &&
                  !data->filter18.accepts(closest,0)) {
            flags[9]=false;
            flags[0]=true;
            flags[3]=false;
        } else {
            flags[9]=false;
            flags[0]=false;
            flags[3]=true;
            closestDist=obj->rva00263763(closest);
        }
    }
    bool rangeEnabled=(data->range20>0.0f || data->range24>0.0f);
    Object *bestNeutral=0;
    Object *bestAlly=0;
    if(rangeEnabled && forcedFrames==0) {
        bool found=false;
        int enemyCount=0,allyCount=0;
        Player *player=obj->getControllingPlayer();
        if(player) {
            unsigned allies=ThePlayerList->getPlayersWithRelationship(player->getPlayerIndex(),3,false);
            unsigned enemies=ThePlayerList->getPlayersWithRelationship(player->getPlayerIndex(),4,false);
            enemyCount=((Rva00739830 *)TheShroudManager)->rva00739830(
                (const BfmePointFD *)(*(Object **)((char *)this-8))->getPosition(),1,enemies);
            allyCount=((Rva00739830 *)TheShroudManager)->rva00739830(
                (const BfmePointFD *)(*(Object **)((char *)this-8))->getPosition(),1,allies);
        }
        float shroudRange=obj->getShroudClearingRange();
        float shroudDist=shroudRange*shroudRange;
        if(shroudDist<closestDist) closestDist=shroudDist;
        EmotionSystemView *system=(EmotionSystemView *)TheEmotionSystem;
        float neutralDist=data->range20*data->range20;
        float allyDist=data->range24*data->range24;
        const _STL::vector<ObjectID> &objects=system->objects;
        for(_STL::vector<ObjectID>::const_iterator it=objects.begin();it!=objects.end();++it) {
            Object *other=TheGameLogic->findObjectByID(*it);
            if(!other || !other->flag454) continue;
            Relationship rel=obj->getRelationship(other);
            if((other->m_template->flags11a & 1) &&
               (rel!=REL_ALLY || data->filter18.accepts(other,0))) {
                float dist=obj->rva00263763(other);
                if(dist<allyDist &&
                   (data->filter14.accepts(other,0) || data->filter18.accepts(other,0)) &&
                   ((Rva0028F326Owner *)obj)->rva0028F326((unsigned int)other,data->range24)) {
                    if(other->status6() ||
                       (*(Object **)((char *)this-8))->rva0028B511()==other->rva0028B511()) {
                        EmotionNugget **n=begin;
                        while(n!=end && ((*n)->entry->kind!=4 ||
                              !(*n)->CanBeActivatedFor(enemyCount,allyCount,(Rva004DD018Arg *)other))) ++n;
                        if(n!=end) {
                            bestAlly=other;
                            allyDist=dist;
                            continue;
                        }
                    }
                }
                if(dist<closestDist &&
                   (data->filter14.accepts(other,0) || data->filter18.accepts(other,0) || data->filter1c.accepts(other,0)) &&
                   ((Rva0028F326Owner *)obj)->rva0028F326((unsigned int)other,obj->getShroudClearingRange())) {
                    EmotionNugget **n=begin;
                    while(n!=end && ((*n)->entry->kind!=3 ||
                          !(*n)->CanBeActivatedFor(enemyCount,allyCount,(Rva004DD018Arg *)other))) ++n;
                    if(n!=end) {
                        closest=other;
                        closestDist=dist;
                        if(other->status6() ||
                           other->rva0028B511()==(*(Object **)((char *)this-8))->rva0028B511()) {
                            flags[0]=false;
                            flags[3]=true;
                        } else {
                            flags[0]=true;
                            flags[3]=false;
                        }
                    }
                }
            }
            if(other!=obj && (other->m_template->flags113 & 4)) {
                const ThingTemplate *tmpl=TheThingFactory->findTemplate(AsciiString("NeutralGollum"));
                if(tmpl && tmpl->isEquivalentTo(other->m_template)) continue;
                if(rel==REL_ALLY) {
                    float dist=obj->rva00263763(other);
                    if(dist<neutralDist &&
                       ((Rva0028F326Owner *)obj)->rva0028F326((unsigned int)other,data->range20)) {
                        bestNeutral=other;
                        neutralDist=dist;
                        found=true;
                    }
                }
            }
        }
        if(!found) foundLatch=false;
        unsigned frame=TheGameLogic->getFrame();
        if(frame>nextFrame && bestNeutral && !foundLatch) {
            nextFrame=frame+g_rva00DBA4E4*0x3c;
            flags[2]=true;
            foundLatch=true;
        } else flags[2]=false;
        if(!flags[4] || targetID[4]==0 || frame>expiry[4]) flags[4]=(bestAlly!=0);
    }
    if(!obj->testStatus((ObjectStatusTypes)0x46) &&
       GetGameLogicRandomValueReal(0.0f,1.0f,
           "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Update\\EmotionTrackerUpdate.cpp",0x25e)<data->probability &&
       obj->rva0028B511()==1)
        ((EmotionTrackerUpdate *)((char *)this-0x10))->PulseEmotion(8,0,1);
    EmotionNugget *selected=((Rva004B13D8 *)((char *)this-0x10))->rva004B13D8();
    bool changed=false;
    if(selected && closest && (selected->entry->kind==0 || selected->entry->kind==3) &&
       closest->getID()!=targetID[selected->entry->kind]) {
        Object *oldObj=TheGameLogic->findObjectByID(targetID[selected->entry->kind]);
        Object *newObj=TheGameLogic->findObjectByID(closest->getID());
        if(oldObj && oldObj->m_274) oldObj=oldObj->m_274;
        if(newObj && newObj->m_274) newObj=newObj->m_274;
        if(oldObj!=newObj) changed=true;
    }
    if(selected==active && !changed) {
        if(active && !((Emotion *)active)->rva004DCEC4()) {
            ((Rva004DD2C0 *)active)->rva004DD2C0();
            active=0;
        }
    } else {
        if(active) ((Rva004DD2C0 *)active)->rva004DD2C0();
        active=selected;
        if(active) {
            int kind=active->entry->kind;
            if(kind==0 || kind==3) {
                if(closest) targetID[kind]=closest->getID();
            } else if(kind==2) {
                if(bestNeutral) targetID[2]=bestNeutral->getID();
            } else if(kind==4) {
                if(bestAlly) targetID[4]=bestAlly->getID();
            }
            if(forcedFrames>0)
                ((Rva004DCC84 *)active)->rva004DCC84(TheGameLogic->findObjectByID(forcedTarget),forcedFrames);
            else
                ((Rva004DCC84 *)active)->rva004DCC84(TheGameLogic->findObjectByID(targetID[active->entry->kind]),0);
        }
    }
    for(int i=0;i<12;++i) {
        if(expiry[i] && TheGameLogic->getFrame()>=expiry[i]) {
            flags[i]=false;
            expiry[i]=0;
        }
    }
    return (UpdateSleepTime)1;
}
