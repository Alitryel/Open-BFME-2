// cl: /O1 /arch:SSE /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath
// ?computeCylinderEmissionPosition@@YGXPAVCoord3D@@PAVCoord2D@@MM@Z at 0x0055D686 size 81
// Evidence: REF table slot 0x0081C7E8 neighbours EmissionVolumeInfo; cylinder emission helper normalizes Coord2D then scales by radius and sets Z.

#include "coord3d.h"

struct XY
{
    float x;
    float y;
};

void __stdcall computeCylinderEmissionPosition(Coord3D *out, Coord2D *dir, float scale, float z)
{
    XY normalizedDirection;
    normalizedDirection.x = dir->x;
    normalizedDirection.y = dir->y;
    ((Coord2D *)&normalizedDirection)->normalize();
    XY scaledDirection;
    scaledDirection.x = normalizedDirection.x * scale;
    scaledDirection.y = normalizedDirection.y * scale;
    out->x = scaledDirection.x;
    out->y = scaledDirection.y;
    out->z = z;
}
