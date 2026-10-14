// ?rva0044E85E@SpecialAbilityUpdate@@QAE_NPAUCoord3D@@M@Z
// cl: /O1 /arch:SSE /MD /GX /I.
// Native 0x0044E85E..0x0044E9C7; WorldBuilder twin 0x010E2370.
// The approach-target caller at 0x00450AE9 supplies an output coordinate and
// its module's range. Step back toward the object until a reachable bridge
// position is found. The output stays unchanged when no position qualifies.
//
// Both math definitions must remain visible, even though both calls stay
// out of line. With only Normalize visible, VC7.1 reverses the x/z register
// assignment throughout the scale and search loop. These are the existing
// GetLength (0x00005A26) and Normalize (0x00005A70) bodies, also byte-checked
// independently in this unit.
#include "Code/Libraries/Include/Lib/Coord3D.h"
#include <math.h>

__declspec(noinline) inline float Coord3D::GetLength() const
{
    float xv = x, yv = y, zv = z;
    return (float)sqrt(xv * xv + yv * yv + zv * zv);
}

__declspec(noinline) inline float Coord3D::Normalize()
{
    float len = GetLength();
    float scale = 1.0f / len;
    x *= scale;
    y *= scale;
    z *= scale;
    return len;
}

enum PathfindLayerEnum { LAYER_GROUND = 0, LAYER_BRIDGE = 1 };

class Object {
public:
    int rva0028B511() const;
    char m_pad00[0x38];
    Coord3D m_position;
    char m_pad44[0x258 - 0x44];
    void *m_ai;
};

class TerrainLogic {
public:
    PathfindLayerEnum getLayerForDestination(Object *, const Coord3D *);
};
extern TerrainLogic *TheTerrainLogic;

class Pathfinder {
public:
    bool QuickDoesPathExist(Object *, const Coord3D *, const Coord3D *, int);
};

class AI {
public:
    char m_pad00[0x10];
    Pathfinder *m_pathfinder;
};
extern AI *TheAI;

class SpecialAbilityUpdate {
public:
    bool rva0044E85E(Coord3D *pos, float range);
    char m_pad00[8];
    Object *m_object;
};

bool SpecialAbilityUpdate::rva0044E85E(Coord3D *pos, float range)
{
    Object *object = m_object;
    if (object->rva0028B511() > 1) return true;
    else {
        if (!object->m_ai) return false;
        else {
            Coord3D dir = *pos;
            Coord3D result = {pos->x, pos->y, pos->z};
            const Coord3D *objectPos = &object->m_position;
            dir.x -= objectPos->x;
            dir.y -= objectPos->y;
            dir.z = 0;
            int steps = (int)(range / 10.0f) - 1;
            dir.Normalize();
            dir.x *= 10.0f;
            dir.y *= 10.0f;
            dir.z *= 10.0f;

            bool found = false;
            for (int i = 0; i < steps; ++i) {
                result.x -= dir.x;
                result.y -= dir.y;
                result.z -= dir.z;
                if (TheTerrainLogic->getLayerForDestination(object, &result) != LAYER_BRIDGE)
                    continue;
                Pathfinder *finder = TheAI->m_pathfinder;
                if (finder->QuickDoesPathExist(object, objectPos, &result, 0)) {
                    found = true;
                    break;
                }
            }
            if (!found) return false;
            else {
                *pos = result;
                return true;
            }
        }
    }
}
