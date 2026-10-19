// ?privateFireWeapon@Weapon@@QAE_NPBVObject@@PBUCoord3D@@0H1_N2IPAH@Z
// partial score=0.991623 date=2026-10-19
// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /Ireference/shims/bfmealloc /I.
// ?isGoalPosWithinAttackRange@Weapon@@QBE_NPBVObject@@PBUCoord3D@@01@Z
// partial score=0.102 date=2026-10-17
// cl: /DNDEBUG /MD
// stlport
// BFME1 a18d9ed50607e9175de4d6568798d7d73119de09 Weapon.cpp semantic donor.
// Native 002CE30A..002CE6C5 and WB BB7C40 establish the caller and target deltas.
#include <vector>
#include <math.h>
#include "Code/Libraries/Include/Lib/Coord2D.h"
struct Coord3DBase { float x,y,z; };
struct Coord3D : public Coord3DBase {
    Coord3D() {}
    Coord3D(const Coord3D &that) { x=that.x; y=that.y; z=that.z; }
    ~Coord3D() {}
};
class Matrix3D { public: float Get_Z_Rotation() const; float data[12]; };
class Drawable { public: int rva0027434D(int); };
class Object { public:
    Drawable *getDrawable() const;
    bool rva0028C15E(int,float*,int,int);
    char unknown[8]; Matrix3D matrix; Coord3D position;
};
class TerrainLogic {
public:
    virtual void slot00(); virtual void slot04(); virtual void slot08();
    virtual void slot0c(); virtual void slot10(); virtual void slot14();
    virtual float getGroundHeight(float,float,Coord3D*) const;
};
extern TerrainLogic *TheTerrainLogic;
class GameLogic { public: char pad[0x40]; unsigned frame; };
extern GameLogic *TheGameLogic;
class ObjectFilter { public: bool isValid() const; };
class WeaponBonus { public:
    WeaponBonus() { for(int i=0;i<6;++i) fields[i]=1.0f; }
    float fields[6];
};
enum WeaponStatus { READY_TO_FIRE, OUT_OF_AMMO, BETWEEN_FIRING_SHOTS, RELOADING_CLIP, PRE_ATTACK };
class Weapon;
class Rva002CA9CA { public: void rva002CAA9D(int,const void*,const void*,int); };
class WeaponTemplate {
public:
    int rva002C9322(const WeaponBonus&,float) const;
    void rva002CBBF5(Object*,int,int,int,Object*,int,const Coord3D*,int,bool,Weapon*,int);
    char pad00[0x28]; float requestAssistRange;
    char pad2c[0xc]; float scatterScalar;
    char pad3c[4]; std::vector<Coord2D> scatterTargets;
    std::vector<Coord3D> linearTargets;
    char pad58[0x108-0x58]; int shotsPerBarrel;
    char pad10c[0x14]; char ammoDescriptor[8]; int autoReloadMode;
    char pad12c[4]; bool leechRange;
    char pad131[0x144-0x131]; int timingExtra144;
    char pad148[0xc]; bool skipFirstLinear;
};
class Weapon {
public:
    bool privateFireWeapon(const Object*,const Coord3D*,const Object*,int,const Coord3D*,bool,bool,unsigned,int*);
    WeaponStatus getStatus() const;
    unsigned getRemainingAmmo(bool) const;
    void reloadAmmo(const Object*);
    void prepareProjectileStreamForFiring();
    void rva002C9DF5(const Object*,const void*) const;
protected:
    void computeBonus(const Object*,unsigned,WeaponBonus&) const;
public:
    char pad00[4]; WeaponTemplate *m_template; int owner; int m_wslot;
    WeaponStatus m_status; int m_ammoInClip; unsigned m_whenWeCanFireAgain;
    unsigned frame1c, frame20, pad24, m_whenLastReloadStarted, m_lastFireFrame;
    int pad30, m_maxShotCount, m_curBarrel, m_numShotsForCurBarrel;
    std::vector<int> m_scatterTargetsUnused;
    int pad4c; unsigned leechUntil; int m_linearIndex;
};
int GetGameLogicRandomValue(int,int,char*,int);
// Native 002CB594 and WB BB9080 establish return by value and the four entry registers.
// The real privateFireWeapon caller below replaces the prior compiler probe.
static __declspec(noinline) Coord3D getLinearPosition(
    const std::vector<Coord3D> &positions, int index, const Object *object)
{
    const Coord3D &point=positions[index];
    Coord2D point2={point.x,point.y};
    float px=point2.x,py=point2.y;
    float angle=object->matrix.Get_Z_Rotation();
    float sine=(float)(double)sin(angle);
    float cosine=(float)(double)cos(angle);
    Coord3D rotated;
    rotated.x=cosine*px-sine*py;
    rotated.y=sine*px+cosine*py;
    Coord3D position;
    position.x=object->position.x;
    position.y=object->position.y;
    position.x+=rotated.x;
    position.y+=rotated.y;
    float x=position.x;
    float y=position.y;
    position.z=TheTerrainLogic->getGroundHeight(x,y,0);
    return position;
}

// return true if we auto-reloaded our clip after firing.
//DECLARE_PERF_TIMER(fireWeapon)
bool Weapon::privateFireWeapon(const Object *sourceObj,const Coord3D *sourcePos,
    const Object *victimObj,int victimID,const Coord3D *victimPos,
    bool ignoreRanges,bool special,unsigned extraBonusFlags,int *projectileID)
{
    //CRCDEBUG_LOG(("Weapon::privateFireWeapon() for %s\n", DescribeObject(sourceObj).str()));
    //USE_PERF_TIMER(fireWeapon)
    WeaponBonus bonus;
    computeBonus(sourceObj,extraBonusFlags,bonus);
    if(projectileID) *projectileID=0;
    if(!m_template) return false;
    // If we are a networked weapon, tell everyone nearby they might want to get in on this shot
    if(m_template->requestAssistRange && victimObj)
        rva002C9DF5(sourceObj,victimObj);
    //For weapon templates that have the leech range weapon flag set, it essentially grants
    //the weapon unlimited range for the remainder of the attack. While it's triggered here
    //it's the AIAttackState machine that actually uses and resets this value.
    //This makes the ASSUMPTION that it is IMPOSSIBLE TO FIRE A WEAPON WITHOUT BEING IN AN AIATTACKSTATE
    //
    // @todo srj -- this isn't a universally true assertion! eg, FireWeaponDie lets you do this easily.
    //
    if(m_template->leechRange) {
        int delay=m_template->timingExtra144;
        int one=1;
        const int &leechDelay=std::max(delay,one);
        leechUntil=TheGameLogic->frame+leechDelay;
    }
    if(getStatus()!=READY_TO_FIRE) return false;
    prepareProjectileStreamForFiring();
    unsigned now=TheGameLogic->frame;
    bool reloaded=false;
    float factor=1.0f;
    if(sourceObj) ((Object*)sourceObj)->rva0028C15E(21,&factor,0,1);
    int delay=m_template->rva002C9322(bonus,factor);
    if(getRemainingAmmo(false)>0) {
        int barrelCount=sourceObj->getDrawable()->rva0027434D(m_wslot);
        if(m_curBarrel>=barrelCount) {
            m_curBarrel=0;
            m_numShotsForCurBarrel=m_template->shotsPerBarrel;
        }
        if(special) {
            ((Rva002CA9CA*)m_template)->rva002CAA9D((int)this,sourceObj,victimObj,(int)&bonus);
        } else if(m_template->linearTargets.size() && sourceObj) {
            delay=0;
            int iteration=0;
            while(!delay) {
                if(iteration++==m_template->linearTargets.size()) break;
                Coord3D targetPos=getLinearPosition(m_template->linearTargets,m_linearIndex,sourceObj);
                if(!m_template->skipFirstLinear || m_linearIndex!=0)
                    m_template->rva002CBBF5((Object*)sourceObj,(int)sourcePos,m_wslot,m_curBarrel,
                        (Object*)victimObj,victimID,&targetPos,(int)&bonus,ignoreRanges,this,(int)projectileID);
                delay=*(const unsigned int*)&m_template->linearTargets[m_linearIndex].z;
                m_linearIndex=(m_linearIndex+1)%m_template->linearTargets.size();
            }
        } else if(m_scatterTargetsUnused.size()) {
            // If I have a set scatter pattern, I need to offset the target by a random pick from that pattern
            if(victimObj) {
                victimPos=&victimObj->position;
                victimObj=0;
            }
            Coord3D targetPos=*victimPos; // need to copy, as this pointer is actually inside somebody potentially
            int randomPick=GetGameLogicRandomValue(0,m_scatterTargetsUnused.size()-1,
                "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Weapon.cpp",3261);
            int targetIndex=m_scatterTargetsUnused[randomPick];
            float scatterTargetScalar=m_template->scatterScalar;// essentially a radius, but operates only on this scatterTarget table
            const Coord2D &point=m_template->scatterTargets[targetIndex];
            Coord2D scatterOffset={point.x,point.y};
            scatterOffset.x*=scatterTargetScalar;
            scatterOffset.y*=scatterTargetScalar;
            targetPos.x+=scatterOffset.x;
            targetPos.y+=scatterOffset.y;
            targetPos.z=TheTerrainLogic->getGroundHeight(targetPos.x,targetPos.y,0);
            // To erase from a vector, put the last on the one you used and pop the back.
            m_scatterTargetsUnused[randomPick]=m_scatterTargetsUnused.back();
            m_scatterTargetsUnused.pop_back();
            m_template->rva002CBBF5((Object*)sourceObj,(int)sourcePos,m_wslot,m_curBarrel,
                (Object*)victimObj,victimID,&targetPos,(int)&bonus,ignoreRanges,this,(int)projectileID);
        } else {
            m_template->rva002CBBF5((Object*)sourceObj,(int)sourcePos,m_wslot,m_curBarrel,
                (Object*)victimObj,victimID,victimPos,(int)&bonus,ignoreRanges,this,(int)projectileID);
        }
        m_lastFireFrame=now;
        --m_ammoInClip;
        --m_maxShotCount;
        --m_numShotsForCurBarrel;
        if(m_numShotsForCurBarrel<=0) {
            ++m_curBarrel;
            m_numShotsForCurBarrel=m_template->shotsPerBarrel;
        }
        if(getRemainingAmmo(false)<=0) {
            if(!m_template->autoReloadMode) {
                reloadAmmo(sourceObj);
                reloaded=true;
            } else {
                if(m_status!=OUT_OF_AMMO) m_status=OUT_OF_AMMO;
                if(!((const ObjectFilter*)m_template->ammoDescriptor)->isValid())
                    m_whenWeCanFireAgain=0x7fffffff;
                //CRCDEBUG_LOG(("Just set m_whenWeCanFireAgain to %d in Weapon::privateFireWeapon 1\n", m_whenWeCanFireAgain));
            }
        } else {
            if(m_status!=BETWEEN_FIRING_SHOTS) m_status=BETWEEN_FIRING_SHOTS;
            //CRCDEBUG_LOG(("Weapon::privateFireWeapon() just set m_status to BETWEEN_FIRING_SHOTS\n"));
            m_whenLastReloadStarted=now;
            m_whenWeCanFireAgain=now+delay;
            //CRCDEBUG_LOG(("Just set m_whenWeCanFireAgain to %d (delay is %d) in Weapon::privateFireWeapon\n", m_whenWeCanFireAgain, delay));
            if(m_template->timingExtra144>0)
                frame20=TheGameLogic->frame+m_template->timingExtra144;
        }
    }
    return reloaded;
}
