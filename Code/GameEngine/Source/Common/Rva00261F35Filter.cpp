// ?allow@Rva00261F35Filter@@UAE_NPAVObject@@@Z
// cl: /O1  /arch:SSE /DNDEBUG /MD /EHsc /G7 /ICode/Libraries/Include/Lib
// Retail 00261F35..00262002, RET4, vftable slot 1 of 0x0081A068 (slot 0 is
// the folded deleting dtor 0x00395A19, slot 2 0x0036CC7A), the same
// three-slot shape as the 0x00261D2E filter's 0x0081A05C. WB E5D950 is the
// debug twin. Target facts: radius at +8, position at +0xC; an Object
// carrying the CastleBehavior module (key 0x003955DA) passes when its 2D
// center distance is inside castle radius 0x00395A60 plus this radius;
// otherwise a temporary 20-high cylinder of this radius at the filter's
// position is collision-tested against the object's geometry. No original
// filter name is asserted by this address-derived view.
#include "Coord3D.h"

typedef float Real;
enum NameKeyType { NetworkNameKeyUnknown };
enum GeometryType { GEOMETRY_SPHERE, GEOMETRY_CYLINDER, GEOMETRY_BOX };
class Module;
class GeometryInfo {
public:
 GeometryInfo(GeometryType, bool, Real, Real, Real);
 virtual ~GeometryInfo();
 bool CollidesWith(const Coord3D&, Real, const GeometryInfo&, const Coord3D&, Real) const;
private:
 char data04[0x58];
};
#include "RTS/XYDistanceCallView.h"
class Rva00395A60 { public: float rva00395A60(); };
class CastleBehavior { public: static NameKeyType rva0003955DA(); };
class Rva00261F35Filter;
class Object {
 friend class Rva00261F35Filter;
public:
 virtual void unused();
protected:
 Module *findModule(NameKeyType) const;
public:
 char data04[0x38-4]; Coord3D position; Real angle;
 char data48[0xA8-0x48]; GeometryInfo geometry;
};
class Rva00261F35Filter {
public:
 virtual void slot0();
 virtual bool allow(Object*);
 void *next;
 Real radius;
 Coord3D position;
};
bool Rva00261F35Filter::allow(Object *other)
{
 Module *castle=other->findModule(CastleBehavior::rva0003955DA());
 if(castle) {
  Real dist=((Rva000CBA20*)other)->distSq((const Rva000CBA20Point*)&position);
  Real range=((Rva00395A60*)castle)->rva00395A60()+radius;
  if(dist<range*range)
   return true;
 } else {
  GeometryInfo geom(GEOMETRY_CYLINDER,false,20.0f,radius,radius);
  const GeometryInfo &otherGeom=other->geometry;
  Real otherAngle=other->angle;
  if(otherGeom.CollidesWith(other->position,otherAngle,geom,position,0.0f))
   return true;
 }
 return false;
}
