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
// cl: /O1 /arch:SSE /G7 /MD /EHsc
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
#include <new>

enum UpdateSleepTime { UPDATE_SLEEP_NONE = 0 };

struct Coord3D { float X, Y, Z; };
enum ObjectID { };
enum Relationship { REL_ENEMY = 0, REL_NEUTRAL = 1, REL_ALLY = 2 };
class Object;
class Thing;
class ThingTemplate;
class GameWindow;
class EmotionNugget;
class Emotion;
class EmotionTrackerUpdate;
class Rva004B0FEB
{
public:
    Rva004B0FEB(EmotionTrackerUpdate *);
    ~Rva004B0FEB();
};

class Rva004DD2C0 { public: void rva004DD2C0(); };
class Rva004DCC84 { public: void rva004DCC84(Object *); };
class Rva004DD018 { public: bool rva004DD018(void *, void *, Object *); };
class Rva0028F326Owner { public: unsigned char rva0028F326(int, float); };
class Player;
class Rva006E34D0;
class GameLogic
{
public:
    Object *findObjectByID(ObjectID);
    unsigned int m_frame;			// +0x40
};
enum ObjectStatusTypes { };
class Object
{
public:
    float rva00263763(const void *) const;
    int rva0028B511() const;
    bool testStatus(ObjectStatusTypes) const;
    Player *getControllingPlayer() const;
    Relationship getRelationship(const Object *) const;
    float getShroudClearingRange() const;
    unsigned char m_pad4[0x274 - 4];
    void *m_274;				// +0x274
};
class Thing
{
public:
    unsigned char m_pad0[0xc];
    int m_c;					// +0x0c
    unsigned char m_pad10[0x38 - 0x10];
    unsigned char m_38;			// +0x38
};
class EmotionNugget
{
public:
    int m_4;					// +0x04
    unsigned char m_pad8[0x14 - 8];
    unsigned int m_14;				// +0x14
};
class Emotion : public EmotionNugget { public: bool rva004DCEC4(); };
class Rva2225E0Filter { public: bool accepts(Object *, Player *); };
class Rva00739830 { public: void rva00739830(void *, int); };
class EmotionTrackerUpdate;
template<class T> class StringBase
{
    friend class EmotionTrackerUpdate;
private:
    StringBase(const char *);
    ~StringBase();
    void *m_data;
};
class AsciiString;
class ThingFactory { public: const ThingTemplate *findTemplate(const void *); };
class ThingTemplate { public: bool isEquivalentTo(const ThingTemplate *) const; };
class Rva004B13D8 { public: int *rva004B13D8(); };
class EmotionTrackerUpdate
{
public:
    virtual UpdateSleepTime update();
    void PulseEmotion(int, void *, int);

private:
    unsigned char m_pad0[4];
    Thing *m_4;					// +0x04
    Object *m_8;				// +0x08
    unsigned char m_padC[0x14 - 0xc];
    unsigned char m_14;				// +0x14
    unsigned char m_15;
    unsigned char m_16;				// +0x16
    unsigned char m_17;				// +0x17
    unsigned char m_18;				// +0x18
    unsigned char m_pad19[0x20 - 0x19];
    unsigned int m_20[12];			// +0x20
    unsigned char m_pad50[0x58 - 0x50];
    unsigned int m_58;				// +0x58
    unsigned int m_5c;
    unsigned int m_60;				// +0x60
    unsigned char m_pad64[0x90 - 0x64];
    EmotionNugget **m_90;			// +0x90 begin
    EmotionNugget **m_94;			// +0x94 end
    unsigned char m_pad98[0x9c - 0x98];
    EmotionNugget *m_9c;			// +0x9c active nugget
    unsigned int m_a0;				// +0xa0
    unsigned int m_a4;				// +0xa4
    unsigned int m_a8;				// +0xa8
    unsigned int m_ac;				// +0xac
    unsigned char m_b0;				// +0xb0
    unsigned char m_padB1[0xb4 - 0xb1];
    int m_b4;					// +0xb4
};

extern unsigned char g_rva00DFE758[];
extern GameLogic *g_rva00DFE78C;
extern void *g_rva00DFF000;
extern int g_rva00DBA4E4;
extern int g_rva00DB3C00;
extern int g_rva00DFEDF0;
extern void *g_rva00DFEC50;
extern void *g_rva00DFEA3C;
extern void *g_rva00DFE748;
extern void *g_rva00DFEEE8;
class PartitionFilter
{
public:
    int m_0;					// +0x00
    int m_4;					// +0x04
    Player *m_player;				// +0x08
    unsigned char m_c;				// +0x0c
    unsigned char m_pad[0x3c - 0xd];
    PartitionFilter &And(PartitionFilter &other);
};
class PartitionManager
{
public:
    Object *getClosestObject(const Coord3D *pos, float radius, int flags, PartitionFilter *filter);
};
class PlayerList
{
public:
    int getPlayersWithRelationship(int player, unsigned int relationship, bool flag);
};
class Rva00739830View
{
public:
    int rva00739830(const void *point, int players, int unknown);
};
float GetGameLogicRandomValueReal(float, float, char *, int);

UpdateSleepTime EmotionTrackerUpdate::update()
{
    EmotionTrackerUpdate *self = (EmotionTrackerUpdate *)((char *)this - 0xc);
    Thing *thing = *(Thing **)((char *)self + 8);
    if (thing == 0)
        return (UpdateSleepTime)0x3fffffff;
    Object *obj = *(Object **)((char *)self + 0xc);
    if (obj == 0)
        return (UpdateSleepTime)0x3fffffff;

    if (obj->m_274 != 0)
    {
        if (m_9c != 0)
        {
            ((Rva004DD2C0 *)m_9c)->rva004DD2C0();
            m_9c = 0;
        }
        return (UpdateSleepTime)1;
    }

    --m_a0;
    if (m_b4 > 0)
        --m_b4;

    if (g_rva00DFE758[0xe9c] != 0)
    {
        Coord3D tpos = *(Coord3D *)((char *)obj + 0x38);
        float dx = tpos.X;
        float dy = tpos.Y;
        float dz = tpos.Z;
        ((void (__fastcall *)(void *, int, int, float, float, float))((*(void ***)g_rva00DFEC50)[0x18 / 4]))(
            g_rva00DFEC50, 0, 0, dz, dx, dy);
        if (thing->m_c != 0)
            ((void (__fastcall *)(void *, unsigned long, void *, float *))((*(void ***)g_rva00DFEA3C)[0x30 / 4]))(
                g_rva00DFEA3C, 0xff0000ff, g_rva00DFEA3C, &dz);
        if (*(float *)((char *)thing + 0x20) != 0.0f)
            ((void (__fastcall *)(void *, unsigned long, void *, float *))((*(void ***)g_rva00DFEA3C)[0x30 / 4]))(
                g_rva00DFEA3C, 0xff00ffff, g_rva00DFEA3C, &dz);
        if (*(float *)((char *)thing + 0x24) != 0.0f)
            ((void (__fastcall *)(void *, unsigned long, void *, float *))((*(void ***)g_rva00DFEA3C)[0x30 / 4]))(
                g_rva00DFEA3C, 0xffff0000, g_rva00DFEA3C, &dz);
    }

    {
    unsigned int a0 = m_a0 - 1;
    m_a0 = a0;
    if (a0 == 0 && thing->m_c != 0 && m_b4 == 0)
    {
        m_a0 = thing->m_c;
        Rva004B0FEB profiler(this);
        (void)profiler;
        Object *closest = 0;
        if (!obj->testStatus((ObjectStatusTypes)0x44))
        {
            Player *player = obj->getControllingPlayer();
            {
            PartitionFilter filter;
            filter.m_0 = 0xc0719c;
            filter.m_4 = (int)obj;
            filter.m_c = 1;
            {
            PartitionFilter f1;
            f1.m_0 = 0;
            f1.m_4 = 0xbf8fe4;
            f1.m_player = player;
            f1.m_c = 0;
            filter.And(f1);
            }
            {
            PartitionFilter f2;
            f2.m_0 = 0;
            f2.m_4 = 0xbf8fe4;
            f2.m_player = player;
            f2.m_c = 0;
            filter.And(f2);
            }
            Coord3D pos;
            *(unsigned int *)&pos.X = *(unsigned int *)((char *)obj + 0x38);
            *(unsigned int *)&pos.Y = *(unsigned int *)((char *)obj + 0x3c);
            *(unsigned int *)&pos.Z = *(unsigned int *)((char *)obj + 0x40);
            closest = ((PartitionManager *)g_rva00DFE748)->getClosestObject(
                &pos, *(float *)((char *)thing + 8), 0, &filter);
            }
        }
        if (closest != 0)
        {
            if (!((Rva2225E0Filter *)((char *)thing + 0x1c))->accepts(closest, 0) &&
                !((Rva2225E0Filter *)((char *)thing + 0x14))->accepts(closest, 0) &&
                !((Rva2225E0Filter *)((char *)thing + 0x18))->accepts(closest, 0))
            {
                m_14 = 1;
                m_17 = 0;
                m_15 = 0;
            }
            else
            {
                m_14 = 0;
                m_17 = 1;
                m_15 = 0;
                float partitionDist = obj->rva00263763(closest); (void)partitionDist;
            }
        }
        else
        {
            m_14 = 0;
            m_17 = 0;
            m_15 = g_rva00DFE758[0] ? 1 : 0;
        }
    }
    }

    int playerPlayers = 0;
    (void)playerPlayers;
    {
        unsigned int *player = (unsigned int *)obj->getControllingPlayer();
        if (player != 0)
        {
            int pid = (int)player[0x54 / 4];
            playerPlayers = ((PlayerList *)g_rva00DFEEE8)->getPlayersWithRelationship(
                pid, 3, false);
            int other = ((PlayerList *)g_rva00DFEEE8)->getPlayersWithRelationship(
                pid, 4, false);
            ((Rva00739830View *)((char *)thing + 0x38))->rva00739830(
                (void *)0, other, 1);
        }
    }

    EmotionNugget *bestEnemy = 0;
    EmotionNugget *bestNeutral = 0;
    EmotionNugget *bestAlly = 0;
    bool foundAny = false;
    float bestEnemyDist = 0.0f;
    float bestNeutralDist = 0.0f;
    float bestAllyDist = 0.0f;
    int frame = 0;
    (void)frame;

    if (m_9c != 0 && m_b4 == 0)
    {
        // fall through to the nugget scan
    }

    for (EmotionNugget **it = m_90; it != m_94; ++it)
    {
        EmotionNugget *nugget = *it;
        Object *target = g_rva00DFE78C->findObjectByID((ObjectID)*(unsigned int *)((char *)nugget + 0x74));
        if (target == 0)
            continue;
        if (*(unsigned char *)((char *)target + 0x454) == 0)
            continue;
        int rel = obj->getRelationship(target);
        int state = nugget->m_4;
        (void)state;
        if (*(unsigned char *)(*(unsigned int *)((char *)target + 4) + 0x11a) & 1)
        {
            if (rel == REL_ALLY)
            {
                if (!((Rva2225E0Filter *)((char *)thing + 0x18))->accepts(target, 0))
                    continue;
            }
            float dist = obj->rva00263763(target);
            if (bestAllyDist < dist)
            {
                if (((Rva2225E0Filter *)((char *)thing + 0x14))->accepts(target, 0) ||
                    ((Rva2225E0Filter *)((char *)thing + 0x18))->accepts(target, 0))
                {
                    if (((Rva0028F326Owner *)target)->rva0028F326((int)0, 0.0f))
                    {
                        if (((Rva004DD018 *)nugget)->rva004DD018((void *)frame, (void *)4, target))
                        {
                            bestAlly = nugget;
                            bestAllyDist = dist;
                            foundAny = true;
                        }
                    }
                }
            }
        }
        if (rel == REL_ENEMY)
        {
            if (((Rva2225E0Filter *)((char *)thing + 0x14))->accepts(target, 0) ||
                ((Rva2225E0Filter *)((char *)thing + 0x18))->accepts(target, 0) ||
                ((Rva2225E0Filter *)((char *)thing + 0x1c))->accepts(target, 0))
            {
                float dist = obj->getShroudClearingRange();
                if (dist > bestEnemyDist)
                {
                    if (((Rva004DD018 *)nugget)->rva004DD018((void *)frame, (void *)3, target))
                    {
                        bestEnemy = nugget;
                        bestEnemyDist = dist;
                        foundAny = true;
                    }
                }
            }
        }
        if (rel == REL_NEUTRAL && *(unsigned int *)((char *)target + 4) != 0 &&
            (*(unsigned char *)(*(unsigned int *)((char *)target + 4) + 0x113) & 4))
        {
            const ThingTemplate *tmpl = 0;
            (void)tmpl;
            float dist = obj->rva00263763(target);
            if (dist > bestNeutralDist && ((Rva0028F326Owner *)target)->rva0028F326((int)0, 0.0f))
            {
                bestNeutral = nugget;
                bestNeutralDist = dist;
                foundAny = true;
            }
        }
    }

    if (!foundAny)
        m_b0 = 0;
    _ReadWriteBarrier();
    _ReadWriteBarrier();

    if (g_rva00DFE78C->m_frame > m_ac && bestEnemy != 0 && m_b0 == 0)
    {
        m_ac = g_rva00DFE78C->m_frame + g_rva00DBA4E4 * 0x3c;
        m_16 = 1;
        m_b0 = 1;
    }
    else
    {
        m_16 = 0;
    }

    if (m_18 != 0 && m_60 != 0 && g_rva00DFE78C->m_frame <= m_20[4])
    {
    }
    else
    {
        m_18 = bestEnemy != 0;
    }

    if (!obj->testStatus((ObjectStatusTypes)0x46))
    {
        if (GetGameLogicRandomValueReal(0.0f, 1.0f, 0, 0) > *(float *)((char *)thing + 0x28) &&
            obj->rva0028B511() == 1)
        {
            PulseEmotion(8, 0, 1);
        }
    }

    int *newNugget = ((Rva004B13D8 *)((char *)this))->rva004B13D8();
    foundAny = false;
    if (newNugget != 0 && bestAlly != 0)
    {
        int idx = newNugget[1];
        if (idx != 0 && idx != 3)
        {
            if (idx == 2)
            {
                if (bestNeutral != 0)
                    m_58 = *(unsigned int *)((char *)bestNeutral + 0x74);
            }
            else if (idx == 4)
            {
                if (bestEnemy != 0)
                    m_60 = *(unsigned int *)((char *)bestEnemy + 0x74);
            }
            if (bestAlly != 0)
                m_20[idx] = *(unsigned int *)((char *)bestAlly + 0x74);
        }
    }

    {
        EmotionNugget *prev = m_9c;
        if (newNugget == (int *)prev)
        {
            if (!foundAny)
            {
                if (prev != 0)
                {
                    if (!((Emotion *)prev)->rva004DCEC4())
                    {
                        ((Rva004DD2C0 *)m_9c)->rva004DD2C0();
                        m_9c = 0;
                    }
                }
            }
        }
        else
        {
            if (prev != 0)
                ((Rva004DD2C0 *)prev)->rva004DD2C0();
            m_9c = (EmotionNugget *)newNugget;
            if (newNugget != 0)
            {
                int idx = newNugget[1];
                Object *act = 0;
                if (idx != 0 && idx != 3)
                {
                    if (idx == 2 && bestNeutral != 0)
                        act = g_rva00DFE78C->findObjectByID((ObjectID)*(unsigned int *)((char *)bestNeutral + 0x74));
                    else if (idx == 4 && bestEnemy != 0)
                        act = g_rva00DFE78C->findObjectByID((ObjectID)*(unsigned int *)((char *)bestEnemy + 0x74));
                }
                if (act == 0 && idx != 0 && idx != 3)
                    act = g_rva00DFE78C->findObjectByID((ObjectID)*(unsigned int *)((char *)bestAlly + 0x74));
                ((Rva004DCC84 *)m_9c)->rva004DCC84(act);
            }
        }
    }

    for (int i = 0; i < 12; ++i)
    {
        if (m_20[i] != 0 && g_rva00DFE78C->m_frame > m_20[i])
        {
            m_14 = 0;
            m_20[i] = 0;
        }
    }
    return (UpdateSleepTime)1;
}
