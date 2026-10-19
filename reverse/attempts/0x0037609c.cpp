// ?rva0037609C@Rva0037609C@@QAE_NPAXPBUCoord3D@@PAVRva00312C95@@PBE3_N@Z
// partial score=0.9 date=2026-10-19
// ?rva0037609C@Rva0037609C@@QAE_NPAXPBUCoord3D@@PAVRva00312C95@@PBE3_N@Z
// partial score=0.9 date=2026-10-19
// ?rva0037609C@Rva0037609C@@QAE_NPAXPBUCoord3D@@PAVRva00312C95@@PBE3_N@Z
// partial score=0.236 date=2026-10-17
// ?rva0037609C@Rva0037609C@@QAE_NPAXPBUCoord3D@@PAVRva00312C95@@PBE3_N@Z
// partial score=0.25 date=2026-10-14
// ?rva0037609C@Rva0037609C@@QAE_NPAXPBUCoord3D@@PAVRva00312C95@@PBE1_N@Z
// partial score=0.25 date=2026-10-14
// Bank draft of the AerialPathfinder path build at 0x0037609C (2148B, RET18).
// WB 0xF2A4B0 names it AerialPathfinder::computeAerialPath (match 7.567
// consts+strings). Structure from the retail body: destination adjust, the
// "setup" point/angle block, the 5x200 collision-test search with sin/cos
// probes, and the ProfileHighLevel report tail.
// cl: /O1 /arch:SSE /G7 /MD /EHsc
// Native reconstruction restores block lifetimes, receiver roles and collision transitions.
// The earlier draft description above is preserved as contributor evidence.
#include "../../Code/Libraries/Include/Lib/Coord3D.h"
#include "../../Code/Libraries/Include/Lib/Coord3DBase.h"
#include "../../reference/shims/bfme2_ascii/unicode_string.h"
#include "../../Code/Libraries/Source/profile/profile_highlevel.h"

inline void Coord3D::scale(float s) { x *= s; y *= s; z *= s; }
inline Coord3D &addCoord(Coord3D &p, const Coord3DBase &v) {
    p.x += v.x;
    p.y += v.y;
    p.z += v.z;
    return p;
}
inline void Coord3D::set(const Coord3DBase *v) {
    x = v->x;
    y = v->y;
    z = v->z;
}

inline float capExtension(float value) {
    float cap = 1500.0f;
    if (!(value > cap)) cap = value;
    return cap;
}
enum ObjectID {};
class Object {
public:
    void rva0028ACEE(int, int);
    void Get2DCenterVectorTo(Coord3D *, const Coord3D *) const;
    bool isSignificantlyAboveTerrain() const;
};
class LocomotorSet;
class GameLogic { public: Object *findObjectByID(ObjectID); };
class Pathfinder { public: bool AdjustDestination(Object *, const LocomotorSet &, Coord3D *, const Coord3D *); };
class AI;
struct AerialAIView { char pad[0x10]; Pathfinder *pathfinder; };
class GlobalData;
class InGameUI;
extern AI *TheAI;
extern GameLogic *TheGameLogic;
extern GlobalData *TheWritableGlobalData;
extern InGameUI *TheInGameUI;
class Thing { public: void getUnitDirectionVector3D(Coord3D &) const; };
class Rva006C65F0 {
public:
    Rva006C65F0(const char *, const char *, bool);
    ~Rva006C65F0();
private:
    ProfileHighLevel::Id id;
    __int64 start;
    Rva006C65F0 *previous;
};
class AerialPathfinder { public: int rva00375ED7(Object *, const Coord3D *, Coord3D *); };
class Rva00311DD9 { public: void rva00311B70(); };
class Rva00311F46 { public: bool find(const Coord3D &, float); };
class Rva00312C95 {
public:
    void rva00312118();
};
struct SplineState;
class Rva0022B3F6Subsystem { public: bool rva00311974(SplineState *, bool, float *); };
extern Rva0022B3F6Subsystem *TheSplineService;
class AerialRouteCalls {
public:
    virtual void slot0();
    virtual void slot4();
    virtual void prepare(int, int, float, float, int, int);
    virtual void clear();
    virtual void insert(Coord3D *);
    virtual void slot14();
    virtual void append(Coord3D *);
    char pad04[0x14];
    float time;
    char pad1c[0x2c];
    Coord3D result;
};
class AerialUIMessageCalls {
public:
    virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0c();
    virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1c();
    virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2c();
    virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3c();
    virtual void __cdecl message(UnicodeString);
};
extern "C" float __cdecl atan2f(float, float);
extern "C" double __cdecl sin(double);
extern "C" double __cdecl cos(double);
extern "C" int __cdecl strcmp(const char *, const char *);
float normalizeAngle(float);

struct AerialShapeBits {
    unsigned data;
    bool test(unsigned bit) const { return (data & (1U << bit)) != 0; }
};

class Rva0037609C {
private:
    unsigned char m_pad0[0x258];
    void *m_258;			// +0x258
public:
    bool rva0037609C(void *, const Coord3D *, Rva00312C95 *, const unsigned char *, const unsigned char *, bool);
};

bool Rva0037609C::rva0037609C(void *thing, const Coord3D *dest, Rva00312C95 *route,
    const unsigned char *label, const unsigned char *firstPointRaw, bool adjust)
{
    {
        Rva006C65F0 whole("computeAerialPath", "The whole thing.", true);
        unsigned char *self = (unsigned char *)thing;
        void *ai = *(void **)(self + 0x258);
        if (!ai)
            return false;
        Coord3D target;
        target.x = dest->x;
        target.y = dest->y;
        target.z = dest->z;
        if (adjust) {
            Object *obj = TheGameLogic->findObjectByID((ObjectID)*(unsigned *)(self + 0x74));
            if (!obj)
                return false;
            Pathfinder *pf = ((AerialAIView *)TheAI)->pathfinder;
            float z = target.z;
            pf->AdjustDestination(obj, *(const LocomotorSet *)((char *)ai + 0x1cc), &target, 0);
            target.z = z;
            obj->rva0028ACEE((int)&target, 1);
        }
        Coord3D center;
        center.x = *(float *)(self + 0x38);
        center.y = *(float *)(self + 0x3c);
        center.z = *(float *)(self + 0x40);
        Coord3D delta;
        ((Object *)thing)->Get2DCenterVectorTo(&delta, &target);
        float distance = delta.length();
        float extension;
        Coord3D push;
        {
            Rva006C65F0 setup("setup", "setting up first points", true);
            Coord3D p;
            ((Thing *)thing)->getUnitDirectionVector3D(p);
            extension = distance * 3.0f;
            p.scale(-(extension > 1500.0f ? 1500.0f : extension));
            addCoord(p, asBase(center));
            bool above = ((Object *)thing)->isSignificantlyAboveTerrain();
            if (((const AerialShapeBits *)label)->test(2) && above)
                p.z -= capExtension(extension);
            else if (((const AerialShapeBits *)label)->test(7)) {
                p.z = 1000.0f;
                p.x = center.x;
                p.y = center.y;
            }
            ((AerialRouteCalls *)route)->clear();
            ((AerialRouteCalls *)route)->append(&p);
            ((AerialRouteCalls *)route)->append(&center);
            if (firstPointRaw) {
                ((AerialRouteCalls *)route)->append(&target);
                target = *(const Coord3D *)firstPointRaw;
            }
        }
        if (((const AerialShapeBits *)label)->test(0)) {
            ((AerialRouteCalls *)route)->append(&center);
            ((AerialRouteCalls *)route)->append(&target);
        } else {
            Rva006C65F0 terminal("calc terminal points", "calc terminal points", true);
            int radius = (int)(50.0 > (distance * 0.25 > 150.0 ? 150.0 : distance * 0.25) ? 50.0 : (distance * 0.25 > 150.0 ? 150.0 : distance * 0.25));
            Coord3D probe;
            probe.set(&asBase(delta));
            probe.normalize();
            probe.scale((float)radius);
            addCoord(probe, asBase(target));
            bool collides = ((AerialPathfinder *)this)->rva00375ED7((Object *)thing, &probe, &push) != 0;
            if (collides) {
                float base = atan2f(delta.x, delta.y);
                Coord3D &q = delta;
                Coord3D second;
                bool tryPlus = true;
                bool tryMinus = true;
                bool havePoint = false;
                bool haveSecond = false;
                float step = 0.2f;
                for (float angle = 0; angle < 3.1415927f; angle += step) {
                    if (tryPlus) {
                        float a = normalizeAngle(base + angle);
                        q.x = sin(a) * (float)radius + target.x;
                        q.y = cos(a) * (float)radius + target.y;
                        q.z = target.z;
                        if (!((AerialPathfinder *)this)->rva00375ED7((Object *)thing, &q, &push)) {
                            q.x = sin(a + 2 * step) * (float)radius + target.x;
                            q.y = cos(a + 2 * step) * (float)radius + target.y;
                            tryPlus = false;
                            if (havePoint) {
                                haveSecond = true;
                                second = q;
                                break;
                            }
                            havePoint = true;
                            probe = q;
                        }
                    }
                    if (tryMinus) {
                        float a = normalizeAngle(base - angle);
                        q.x = sin(a) * (float)radius + target.x;
                        q.y = cos(a) * (float)radius + target.y;
                        q.z = target.z;
                        if (!((AerialPathfinder *)this)->rva00375ED7((Object *)thing, &q, &push)) {
                            q.x = sin(a - 2 * step) * (float)radius + target.x;
                            q.y = cos(a - 2 * step) * (float)radius + target.y;
                            tryMinus = false;
                            if (havePoint) {
                                haveSecond = true;
                                second = q;
                                break;
                            }
                            havePoint = true;
                            probe = q;
                        }
                    }
                }
                if (haveSecond)
                    ((AerialRouteCalls *)route)->append(&second);
            }
            if (((const AerialShapeBits *)label)->test(1))
                probe.z -= capExtension(extension);
            ((AerialRouteCalls *)route)->append(&target);
            ((AerialRouteCalls *)route)->append(&probe);
        }
        {
            Rva006C65F0 collision("collision", "Collision test for terrain and objects", true);
            ((AerialRouteCalls *)route)->prepare(1, 4000, 1000.0f, 1000.0f, 0, 0);
            route->rva00312118();
            int repairs = 0;
            ((AerialRouteCalls *)route)->time = 0;
            int inside = 0;
            float start = 0;
            float finish = 0;
            push.x = push.y = push.z = 0;
            int steps = 0;
            while (repairs < 5) {
                float closest = 999999.0f;
                ((AerialRouteCalls *)route)->time += *(float *)(self + 0xbc) * 0.5f;
                if (!TheSplineService->rva00311974((SplineState *)route, false, 0))
                    break;
                if (++steps > 200)
                    break;
                Coord3D *result = &((AerialRouteCalls *)route)->result;
                bool hit = ((AerialPathfinder *)this)->rva00375ED7((Object *)thing, result, &push) != 0;
                if (hit && inside == 0) {
                    inside = 1;
                    start = ((AerialRouteCalls *)route)->time;
                }
                if (inside && !hit) {
                    inside = 0;
                    finish = ((AerialRouteCalls *)route)->time;
                    float middle = (finish + start) * 0.5f;
                    ((AerialRouteCalls *)route)->time = middle;
                    if (TheSplineService->rva00311974((SplineState *)route, false, &closest)) {
                        Coord3D p;
                        p.x = result->x;
                        p.y = result->y;
                        p.z = result->z;
                        if (((AerialPathfinder *)this)->rva00375ED7((Object *)thing, &p, &push)) {
                            p.x += push.x;
                            p.y += push.y;
                            p.z += push.z;
                            if (!((Rva00311F46 *)route)->find(p, *(float *)(self + 0xbc)))
                                ((AerialRouteCalls *)route)->insert(&p);
                            ((Rva00311DD9 *)route)->rva00311B70();
                            ((AerialRouteCalls *)route)->prepare(1, 4000, 1000.0f, 1000.0f, 0, 0);
                            route->rva00312118();
                            ++repairs;
                            ((AerialRouteCalls *)route)->time = *(float *)(self + 0xbc) + middle;
                        }
                    }
                }
            }
        }
    }
    if (*(int *)((char *)TheWritableGlobalData + 0x9b8) == 5) {
        ProfileHighLevel::Id id;
        for (unsigned i = 0; ProfileHighLevel::EnumProfile(i, id); ++i) {
            UnicodeString str;
            str.format((const unsigned short *)L"%S took %S %S.", id.GetDescr(), id.GetCurrentValue(), id.GetUnit());
            if (strcmp(id.GetUnit(), "calls") != 0)
                ((AerialUIMessageCalls *)TheInGameUI)->message(str);
        }
    }
    return true;
}
