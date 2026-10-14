// ?getLinearPosition@@YAAAUCoord3D@@AAU1@ABV?$vector@UCoord3D@@V?$allocator@UCoord3D@@@_STL@@@_STL@@HPBVObject@@@Z
// partial score=0.75252 date=2026-10-14
// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /Ireference/shims/bfmealloc /I.
// stlport
// WB BB9080 names getLinearPosition in Weapon.cpp. Native 2CB594..2CB65B:
// ECX vector, EAX index, EDI Object, ESI output. Caller 2CE497 establishes
// all four registers. The test caller below is a compiler lever, not a
// recovered Weapon::privateFireWeapon body; do not claim it as retail code.
#include <vector>
#include <math.h>
#include "Code/Libraries/Include/Lib/Coord3D.h"
class Matrix3D { public: float Get_Z_Rotation() const; float data[12]; };
class Object { public: char unknown[8]; Matrix3D matrix; Coord3D position; };
class TerrainLogic {
public:
    virtual void slot00(); virtual void slot04(); virtual void slot08();
    virtual void slot0c(); virtual void slot10(); virtual void slot14();
    virtual float getGroundHeight(float,float,void*) const;
};
extern TerrainLogic *TheTerrainLogic;
static __declspec(noinline) Coord3D &getLinearPosition(Coord3D &out,
    const std::vector<Coord3D> &positions, int index, const Object *object)
{
    const Coord3D &point=positions[index];
    float px=point.x, py=point.y;
    float angle=object->matrix.Get_Z_Rotation();
    float sine=(float)sin(angle);
    float cosine=(float)cos(angle);
    float x=object->position.x+(cosine*px-sine*py);
    float y=object->position.y+(cosine*py+sine*px);
    out.z=TheTerrainLogic->getGroundHeight(x,y,0);
    out.x=x; out.y=y;
    return out;
}
Coord3D &linearPositionCompileProbe(Coord3D &out,
    const std::vector<Coord3D> &positions,int index,const Object *object)
{
    return getLinearPosition(out,positions,index,object);
}
