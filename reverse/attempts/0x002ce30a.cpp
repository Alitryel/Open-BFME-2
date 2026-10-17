// ?isGoalPosWithinAttackRange@Weapon@@QBE_NPBVObject@@PBUCoord3D@@01@Z
// partial score=0.102 date=2026-10-17
// cl: /DNDEBUG /MD
#include <math.h>

extern class GameLogic *TheGameLogic;

enum WeaponStatus
{
    READY_TO_FIRE,
    OUT_OF_AMMO,
    BETWEEN_FIRING_SHOTS,
    RELOADING_CLIP,
    PRE_ATTACK,
    WEAPON_STATUS_5
};

class ObjectFilter
{
public:
    bool isValid() const;
};

class WeaponTemplate;
class Object;
class Drawable;
class BuildListInfo;

struct Coord3D
{
    float x;
    float y;
    float z;
};

struct SavedWeaponState
{
    int m_key;
    int m_14;
    WeaponStatus m_status;
    int m_28;
    unsigned int m_18;
};

struct GameLogicFrame
{
    char m_pad00[0x40];
    unsigned int m_frame;
};

#define TheGameLogic (*(GameLogicFrame **)&TheGameLogic)

class WeaponTemplate
{
public:
    char m_pad00[0x0C];
    int m_key0C;
    char m_pad10[0x28 - 0x10];
    float m_range28;
    char m_pad2C[0x38 - 0x2C];
    float m_val38;
    int m_val40;
    char m_pad44[0x78 - 0x44];
    int m_flag78;
    char m_pad7C[0xE4 - 0x7C];
    int m_valueE4;
    char m_padE8[0x108 - 0xE8];
    int m_val108;
    char m_pad10C[0x120 - 0x10C];
    ObjectFilter m_ammo;
    char m_pad121[0x128 - 0x121];
    int m_val128;
    char m_pad12C[0x130 - 0x12C];
    unsigned char m_flag130;
    char m_pad131[0x144 - 0x131];
    int m_val144;
    char m_pad148[0x154 - 0x148];
    unsigned char m_flag154;
    char m_pad155[0x16E - 0x155];
    bool m_flag16E;
};

class Object
{
public:
    bool rva0028C15E(int a, int b, float *c, int d, int e) const;
    int getDesiredGatherers() const;
};

class WeaponBonus
{
public:
    float m_v[6];
};

class Weapon
{
public:
    WeaponStatus getStatus() const;
    WeaponStatus computeStatus(bool *cacheable) const;
    __declspec(noinline) void cacheStatus(WeaponStatus status) const;
    unsigned int getRemainingAmmo(bool countReloadingAsEmpty) const;
    bool isAmmoReady() const;
    void loadAmmoNow(const Object *sourceObj);
    void reloadAmmo(const Object *sourceObj);
    void rva002CE226(const Object *sourceObj, const SavedWeaponState *saved);
    void rva002CE280(float rate, bool flag);
    bool isGoalPosWithinAttackRange(const Object *o, const Coord3D *a, const Object *b, const Coord3D *c) const;
protected:
    void rebuildScatterTargets();
private:
    void computeBonus(const Object *o, unsigned int n, WeaponBonus &b) const;
    void rva002C9DF5(const Object *o, const void *x) const;
    void rva002CC4DD();
    char m_pad00[4];
    WeaponTemplate *m_template;
    char m_pad08[4];
    int m_key0C;
    int m_10;
    int m_14;
    unsigned int m_frame18;
    unsigned int m_frame1C;
    unsigned int m_frame20;
    int m_pad24;
    int m_28;
    int m_2C;
    int m_pad30[2];
    int m_38;
    int m_3C;
    int m_40;
    int *m_44;
    char m_pad48[8];
    int m_50;
    int m_54;
};

extern int GetGameLogicRandomValue(int a, int b, char *c, int d);

bool Weapon::isGoalPosWithinAttackRange(const Object *o, const Coord3D *a, const Object *b, const Coord3D *c) const
{
    struct PaddedBonus { WeaponBonus b; unsigned char pad[12]; } pbon;
    WeaponBonus &bon = pbon.b;
    for (int i = 0; i < 6; ++i)
        bon.m_v[i] = 1.0f;
    const Object *selfObj = o;
    unsigned int fr0 = TheGameLogic->m_frame;
    computeBonus(selfObj, fr0, bon);
    if (a != 0)
        *(volatile int*)a = 0;
    WeaponTemplate *tmpl = m_template;
    if (tmpl == 0)
        return false;
    float r = tmpl->m_range28;
    if (!(r > 0.0f))
        return false;
    if (b == 0)
        return false;
    {
        bool cacheable = false;
        WeaponStatus st;
        {
            st = computeStatus(&cacheable);
        }
        if (tmpl->m_flag130) {
            int n = *(volatile int*)&tmpl->m_val144;
            if (n < 1) n = 1;
            unsigned int fr = TheGameLogic->m_frame;
            *(volatile int*)&m_50 = (int)(fr + n);
        }
        if (st != READY_TO_FIRE && st != BETWEEN_FIRING_SHOTS)
            return false;
    }
    if (!isAmmoReady())
        return false;
    if (getRemainingAmmo(true) == 0)
        return false;
    int g = GetGameLogicRandomValue(0, 100, 0, 0);
    if (g < tmpl->m_val40)
        return false;
    return (c ? true : true);
}
