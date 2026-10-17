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
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
#include <new>

struct Coord3D
{
    float X, Y, Z;
    float length() const;
    void normalize();
};
enum ObjectID { };
class Object
{
public:
    void rva0028ACEE(int, int);
    void rva0028ACEE(const Coord3D *, int);
    void Get2DCenterVectorTo(Coord3D *, const Coord3D *) const;
    bool isSignificantlyAboveTerrain() const;
};
class LocomotorSet;
class SplineState;
class AerialPathfinder
{
public:
    int rva00375ED7(Object *, const Coord3D *, Coord3D *);
};
class Rva00312C95
{
public:
    void rva00312118();
};
class Rva0037609CRoute
{
public:
    virtual void r0();
    virtual void r1();
    virtual void r2(int, int, int, int, int, float, float, int);
    virtual void r3();
    virtual void r4(Coord3D *);
    virtual void r5();
    virtual void r6(Coord3D *);
    virtual void r7();
    virtual void r8();
    virtual void r9();
    virtual void r10();
    virtual void r11();
    virtual void r12();
    virtual void r13();
    virtual void r14();
    virtual void r15();
    virtual void r16(int);
};
class ProfileHighLevel
{
public:
    class Id
    {
    public:
        const char *GetUnit() const;
        const char *GetCurrentValue() const;
        const char *GetDescr() const;
    };
    static bool EnumProfile(unsigned int, Id &);
};
class Rva006C65F0
{
public:
    Rva006C65F0(const char *, const char *, bool);
    ~Rva006C65F0();
};
class Rva0022B3F6Subsystem
{
public:
    bool rva00311974(SplineState *, bool, float *);
};
class Rva00311F46
{
public:
    bool find(const Coord3D &, float);
};
class GameLogic { public: Object *findObjectByID(ObjectID); };
class Pathfinder { public: bool AdjustDestination(Object *, const LocomotorSet &, Coord3D *, const Coord3D *); };
class Thing
{
public:
    void getUnitDirectionVector3D(Coord3D &) const;
};

extern "C" float __cdecl atan2f(float, float);
float normalizeAngle(float);
extern "C" double __cdecl sin(double);
extern "C" double __cdecl cos(double);
extern "C" int __cdecl _ftol2(float);
extern "C" int __cdecl strcmp(const char *, const char *);
class UnicodeString { public: void format(const unsigned short *, ...); };
class Rva0037609C;
template<class T> class StringBase
{
    friend class Rva0037609C;
private:
    StringBase(const StringBase &);
    void releaseBuffer();
    void *m_data;
};

extern void *g_rva00DFE758;
extern void *g_rva00DFEDF0;
extern Rva0022B3F6Subsystem *g_rva00E0095C;
extern Object *g_rva00DFE78C;

class Rva0037609C
{
public:
    bool rva0037609C(void *thing, const Coord3D *dest, Rva00312C95 *route,
        const unsigned char *label, const unsigned char *firstPoint, bool adjust);

private:
    unsigned char m_pad0[0x258];
    void *m_258;			// +0x258
};

bool Rva0037609C::rva0037609C(void *thing, const Coord3D *dest, Rva00312C95 *route,
    const unsigned char *label, const unsigned char *firstPointRaw, bool adjust)
{
    unsigned char *self = (unsigned char *)thing;
    Rva006C65F0 whole("computeAerialPath", "The whole thing.", true);
    Coord3D target = { 0 };
    target.X = dest->X;
    target.Y = dest->Y;
    target.Z = dest->Z;
    void *pathfinder = *(void **)(self + 0x258);
    if (pathfinder == 0)
    {
        whole.~Rva006C65F0();
        return false;
    }
    if (adjust)
    {
        Object *obj = ((GameLogic *)g_rva00DFE78C)->findObjectByID((ObjectID)*(unsigned int *)(self + 0x74));
        if (obj == 0)
        {
            whole.~Rva006C65F0();
            return false;
        }
        const LocomotorSet *ls = *(const LocomotorSet *const *)((unsigned char *)pathfinder + 0x1cc);
        ((Pathfinder *)pathfinder)->AdjustDestination(obj, *ls, &target, 0);
        ((Object *)obj)->rva0028ACEE(&target, 1);
    }

    Coord3D center;
    ((Object *)self)->Get2DCenterVectorTo(&center, &target);
    float distance;
    {
        distance = center.length();
    }

    {
        Rva006C65F0 setup("setup", "setting up first points", true);
        Coord3D dir;
        dir.X = 0.0f; dir.Y = 0.0f; dir.Z = 0.0f;
        ((Thing *)self)->getUnitDirectionVector3D(dir);
        float radius = distance * 3.0f;
        if (radius > 1500.0f)
            radius = 1500.0f;
        float step = -radius;
        float px = step * dir.X + *(float *)(self + 0x38);
        float py = step * dir.Y + *(float *)(self + 0x3c);
        float pz = step * dir.Z + *(float *)(self + 0x40);
        if (*(unsigned int *)(self + 0xbc), ((Object *)self)->isSignificantlyAboveTerrain())
        {
            if (radius <= 1500.0f)
                pz -= radius;
        }
        else if (*(unsigned int *)label & 0x80)
        {
            pz = 1000.0f;
            px = *(float *)(self + 0x38);
            py = *(float *)(self + 0x3c);
        }
        Coord3D p;
        p.X = px; p.Y = py; p.Z = pz;

        ((Rva0037609CRoute *)route)->r3();
        ((Rva0037609CRoute *)route)->r6(&p);
        ((Rva0037609CRoute *)route)->r6(&center);
        if (firstPointRaw != 0)
        {
            ((Rva0037609CRoute *)route)->r6((Coord3D *)firstPointRaw);
            center = *(const Coord3D *)firstPointRaw;
        }
        setup.~Rva006C65F0();
    }

    if (*(unsigned int *)label & 1)
    {
        ((Rva0037609CRoute *)route)->r6(&center);
        ((Rva0037609CRoute *)route)->r6(&target);
    }
    else
    {
        Rva006C65F0 terminal("terminal points", "calc terminal points", true);
        float d = *(float *)((char *)&target + 0) - center.X;
        float v = *(float *)((char *)&target + 0);
        (void)v;
        float scaled = 0.0f;
        {
            float tmp = d * 0.25f;
            if (tmp <= 50.0f)
                scaled = tmp < 50.0f ? 50.0f : tmp;
            else
                scaled = tmp > 150.0f ? 150.0f : tmp;
        }
        int steps = _ftol2(scaled);
        Coord3D probe;
        probe = center;
        probe.normalize();
        float r = (float)steps;
        probe.X = probe.X * r + center.X;
        probe.Y = probe.Y * r + center.Y;
        probe.Z = probe.Z * r + center.Z;
        float radius = r;
        {
            Coord3D out;
            if (((AerialPathfinder *)route)->rva00375ED7((Object *)thing, &probe, &out))
            {
                float base = atan2f(center.Y, center.X);
                bool tryPlus = true;
                bool tryMinus = true;
                bool havePoint = false;
                float angle = 0.0f;
                float best = 0.0f;
                (void)best;
                for (;;)
                {
                    if (tryPlus)
                    {
                        float a = normalizeAngle(angle + base);
                        Coord3D q;
                        q.X = sin(a) * radius + center.X;
                        q.Y = cos(a) * radius + center.Y;
                        q.Z = probe.Z;
                        if (!((AerialPathfinder *)route)->rva00375ED7((Object *)thing, &q, &out))
                        {
                            if (!havePoint)
                            {
                                center = q;
                                havePoint = true;
                            }
                            tryPlus = false;
                        }
                        else
                        {
                            float a2 = normalizeAngle(angle + base + 0.4f);
                            Coord3D q2;
                            q2.X = sin(a2) * radius + center.X;
                            q2.Y = cos(a2) * radius + center.Y;
                            _ReadWriteBarrier();
                            q2.Z = probe.Z;
                            if (!havePoint)
                            {
                                center = q2;
                                havePoint = true;
                            }
                            tryPlus = false;
                        }
                    }
                    if (tryMinus)
                    {
                        float a = normalizeAngle(base - angle);
                        Coord3D q;
                        q.X = sin(a) * radius + center.X;
                        q.Y = cos(a) * radius + center.Y;
                        q.Z = probe.Z;
                        if (!((AerialPathfinder *)route)->rva00375ED7((Object *)thing, &q, &out))
                        {
                            if (!havePoint)
                            {
                                center = q;
                                havePoint = true;
                            }
                            tryMinus = false;
                        }
                        else
                        {
                            float a2 = normalizeAngle(base - angle - 0.4f);
                            Coord3D q2;
                            q2.X = sin(a2) * radius + center.X;
                            q2.Y = cos(a2) * radius + center.Y;
                            q2.Z = probe.Z;
                            if (!havePoint)
                            {
                                center = q2;
                                havePoint = true;
                            }
                            tryMinus = false;
                        }
                    }
                    angle += 0.2f;
                    if (angle >= 3.1415927f)
                        break;
                }
            }
        }
        if (*(unsigned int *)label & 2)
        {
            if (radius > 1500.0f)
                radius = 1500.0f;
            probe.Z -= radius;
        }
        ((Rva0037609CRoute *)route)->r6(&target);
        ((Rva0037609CRoute *)route)->r6(&center);
        terminal.~Rva006C65F0();
    }

    {
        Rva006C65F0 collision("collision", "Collision test for terrain and objects", true);
        ((Rva0037609CRoute *)route)->r2(1, 0xfa0, 0, 0, 0, 1000.0f, 1000.0f, 0);
        ((Rva00312C95 *)route)->rva00312118();
        float best = 0.0f;
        (void)best;
        int steps = 0;
        for (int outer = 0; outer < 5; ++outer)
        {
            float closest = 999999.0f;
            float radius = *(float *)(self + 0xbc) * 0.5f + *(float *)((char *)route + 0x18);
            *(float *)((char *)route + 0x18) = radius;
            if (!g_rva00E0095C->rva00311974((SplineState *)route, false, &closest))
                break;
            if (++steps > 200)
                break;
            Coord3D p;
            if (((AerialPathfinder *)route)->rva00375ED7((Object *)thing, &target, &p))
            {
                if (!*(int *)label)
                    *(float *)((char *)route + 0x18) = radius;
            }
            if (!((Rva00311F46 *)route)->find(p, 0.0f))
            {
                ((Rva0037609CRoute *)route)->r4(&p);
            }
            (void)steps;
        }
        collision.~Rva006C65F0();
    }

    if (*(int *)((char *)g_rva00DFE758 + 0x9b8) == 5)
    {
        ProfileHighLevel::Id id;
        for (unsigned int i = 0; ProfileHighLevel::EnumProfile(i, id); ++i)
        {
            char text[32];
            UnicodeString str;
            str.format((const unsigned short *)L"%S took %S %S.",
                text, id.GetDescr(), id.GetCurrentValue(), id.GetUnit());
            if (strcmp("calls", id.GetUnit()) != 0)
            {
                StringBase<unsigned short> copy(*(StringBase<unsigned short> *)&str);
                ((void (__fastcall *)(void *, int))((*(void ***)g_rva00DFEDF0)[0x40 / 4]))(g_rva00DFEDF0, 1);
                copy.releaseBuffer();
            }
        }
    }
    return true;
}
