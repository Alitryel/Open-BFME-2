// cl: /O1 /arch:SSE /G7 /MD /EHsc /D_STLP_NO_EXCEPTIONS /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /ICode/Libraries/Include/Lib
// stlport
//
// ?rva004DFCE6@Rva004DFCE6@@QAEXPAVObject@@PAX@Z retail 0x004DFCE6..0x004DFE4F, 361 B, RET 8.
// Target evidence: thiscall with (Object *, getter) where the getter is a __cdecl
// position callback (call [ebp+0xC] with the object pushed); first entry seeds the
// sphere (radius = padding +0x14, center +0x08 = getter(obj)), otherwise unless the
// rowed containment test 0x004DFA43 passes it grows the sphere to cover the new point,
// then pushes the object onto the vector at +0x1C (rowed push_back 0x001F211B).
// WorldBuilder twin 0x0129CFF0 (unnamed; callee DefenseTreeItem<Object>::fullyContained
// for 0x004DFA43) supplies the statement shape: copy-constructed Coord3Ds and MathCoord3D.h
// in-place operators (Sub 0x420D30, Scale 0x421230, Add 0x420830 returning *this), here
// Lib/Coord3DCtorView.h with COORD3D_VIEW_INLINE. Class and member names are generated;
// the layout is target-measured.
#include <vector>
#define COORD3D_VIEW_INLINE
#include "Coord3DCtorView.h"
#include <math.h>
// coord3d.cpp's Coord3D::length (0x00003571) and ::normalize (0x000035B6), visible here
// so cl knows they keep no pointer to the direction vector (as AIAttackApproachComputePath.cpp).
__declspec(noinline) inline float Coord3D::length() const
{
    return (float)sqrt(x * x + y * y + z * z);
}

__declspec(noinline) inline void Coord3D::normalize()
{
    float len = length();
    if (len != 0.0f) {
        float scale = 1.0f / len;
        x *= scale;
        y *= scale;
        z *= scale;
    }
}
class Object;
namespace _STL { template <> void vector<Object *, allocator<Object *> >::push_back(Object *const &); }
class Rva004DFA43 { public: bool rva004DFA43(void*,void*); };
class Rva004DFCE6 {
public:
 void rva004DFCE6(Object*,void*);
 bool active00;
 float radius04;
 Coord3D center08;
 float padding14;
 bool selected18;
 _STL::vector<Object*> objects1C;
};
void Rva004DFCE6::rva004DFCE6(Object *object,void *callback)
{
 float padding=padding14;
 _STL::vector<Object*> *objects=&objects1C;
 if(objects->empty()) {
  radius04=padding14;
  center08=*reinterpret_cast<const Coord3D*(__cdecl *)(Object*)>(callback)(object);
 } else if(!reinterpret_cast<Rva004DFA43*>(this)->rva004DFA43(object,callback)) {
  Coord3D old(center08);
  Coord3D position(*reinterpret_cast<const Coord3D*(__cdecl *)(Object*)>(callback)(object));
  Coord3D direction(old);
  direction -= position;
  float distance=direction.length();
  direction.normalize();
  Coord3D opposite(direction);
  opposite.x=-opposite.x;opposite.y=-opposite.y;opposite.z=-opposite.z;
  direction *= radius04;
  float radius=(padding+radius04+distance)*0.5f;
  opposite *= radius;
  Coord3D edge(old += direction);
  center08=(edge += opposite);
  radius04=radius;
 }
 objects->push_back(object);
}
