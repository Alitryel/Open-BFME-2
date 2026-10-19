// ?getLinearPosition@@YA?AVCoord3D@@ABV?$vector@VCoord3D@@V?$allocator@VCoord3D@@@_STL@@@_STL@@HPBVObject@@@Z
// partial score=1.0 date=2026-10-19
// ?getLinearPosition@@YAAAUCoord3D@@AAU1@ABV?$vector@UCoord3D@@V?$allocator@UCoord3D@@@_STL@@@_STL@@HPBVObject@@@Z
// partial score=0.586 date=2026-10-17
// ?getLinearPosition@@YAAAUCoord3D@@AAU1@ABV?$vector@UCoord3D@@V?$allocator@UCoord3D@@@_STL@@@_STL@@HPBVObject@@@Z
// partial score=0.6 date=2026-10-15
// ?getLinearPosition@@YAAAUCoord3D@@AAU1@ABV?$vector@UCoord3D@@V?$allocator@UCoord3D@@@_STL@@@_STL@@HPBVObject@@@Z
// partial score=0.75252 date=2026-10-14
// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /Ireference/shims/bfmealloc /I.
// stlport
// WB BB9080 names getLinearPosition in Weapon.cpp. Native 2CB594..2CB65B:
// ECX vector, EAX index, EDI Object, ESI output. Caller 2CE497 establishes
// all four registers. The test caller below is a compiler lever, not a
// recovered Weapon::privateFireWeapon body; do not claim it as retail code.
// Native result construction is by value; the verified Coord3D owner supplies
// its copy constructor. See reverse/attempt_support/002cb594-return-value.md.
#include <vector>
#include <math.h>
#include "Code/Libraries/Include/Lib/Coord2D.h"
struct Coord3DBase { float x,y,z; };
class Coord3D : public Coord3DBase { public:
    Coord3D() {}
    Coord3D(const Coord3D &that) { x=that.x; y=that.y; z=that.z; }
    ~Coord3D() {}
};
class Matrix3D { public: float Get_Z_Rotation() const; float data[12]; };
class Object { public: char unknown[8]; Matrix3D matrix; Coord3D position; };
class TerrainLogic {
public:
    virtual void slot00(); virtual void slot04(); virtual void slot08();
    virtual void slot0c(); virtual void slot10(); virtual void slot14();
    virtual float getGroundHeight(float,float,Coord3D*) const;
};
extern TerrainLogic *TheTerrainLogic;
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
Coord3D linearPositionCompileProbe(
    const std::vector<Coord3D> &positions,int index,const Object *object)
{
    return getLinearPosition(positions,index,object);
}
